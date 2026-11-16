#include "js/test/js_test_common.h"

#include "building/building.h"
#include "city/city.h"
#include "city/city_buildings.h"
#include "content/vfs.h"
#include "figure/figure.h"
#include "io/gamestate/boilerplate.h"
#include "io/og_save/og_save.h"

#include <algorithm>
#include <cstring>
#include <filesystem>
#include <string>
#include <vector>

namespace {

    // A v160 image the way the original writes it: compressed chunks stored raw (CHUNK_STORED) or as an all-zero
    // header, with the chunk schema describing every chunk.
    std::vector<uint8_t> synthetic_image(int32_t treasury) {
        std::vector<std::vector<uint8_t>> chunks(og::CHUNK_COUNT);
        for (int i = 0; i < og::CHUNK_COUNT; ++i) {
            const og::chunk_spec& spec = og::chunk_info(i);
            chunks[i].assign((size_t)spec.element_size * spec.count, 0);
        }
        const int32_t version = og::SAVE_VERSION;
        const int32_t count = og::CHUNK_COUNT;
        std::memcpy(chunks[og::CHUNK_FILE_VERSION].data(), &version, 4);
        std::memcpy(chunks[og::CHUNK_SCHEMA_COUNT].data(), &count, 4);
        auto* schema = reinterpret_cast<og::chunk_schema_record*>(chunks[og::CHUNK_SCHEMA].data());
        for (int i = 0; i < og::CHUNK_COUNT; ++i) {
            const og::chunk_spec& spec = og::chunk_info(i);
            schema[i] = {spec.compressed ? 1 : 0, 0, spec.element_size, spec.count, 0};
        }
        const int32_t current = 1;
        std::memcpy(chunks[og::CHUNK_CITY_CURRENT_PLAYER].data(), &current, 4);
        auto* players = reinterpret_cast<og::city_player*>(chunks[og::CHUNK_CITY_PLAYERS].data());
        players[1].treasury = treasury;
        auto* buildings = reinterpret_cast<og::building*>(chunks[og::CHUNK_BUILDINGS].data());
        buildings[5].state = 1;
        buildings[5].type = 10;

        std::vector<uint8_t> image;
        for (int i = 0; i < og::CHUNK_COUNT; ++i) {
            const auto& raw = chunks[i];
            if (og::chunk_info(i).compressed) {
                const bool zero = std::all_of(raw.begin(), raw.end(), [](uint8_t b) { return b == 0; });
                const uint32_t header = zero ? 0u : 0x80000000u;
                image.insert(image.end(), (const uint8_t*)&header, (const uint8_t*)&header + 4);
                if (zero) {
                    continue;
                }
            }
            image.insert(image.end(), raw.begin(), raw.end());
        }
        return image;
    }

    std::string expect_error(const std::vector<uint8_t>& image, const char* what) {
        og::savegame s;
        std::string error;
        if (og::read_savegame(image.data(), image.size(), s, error)) {
            return std::string(what) + " was accepted;";
        }
        logs::info("[og-save] synthetic %s refused: %s", what, error.c_str());
        return "";
    }

} // namespace

// Reader checks on a synthetic image (no Pharaoh data needed): a valid image reads back its values, and a
// truncated image, a wrong version, a schema that disagrees with the v160 table and trailing bytes are refused.
// Returns "" on success, else the failed checks.
static pcstr __test_og_reader_synthetic() {
    static std::string result;
    result.clear();

    const std::vector<uint8_t> image = synthetic_image(123456);
    og::savegame s;
    std::string error;
    if (!og::read_savegame(image.data(), image.size(), s, error)) {
        result = "valid image refused: " + error;
        return result.c_str();
    }
    if (s.player().treasury != 123456 || s.buildings.size() != 4000 || s.buildings[5].type != 10
        || s.figures.size() != 2000 || s.players.size() != 2) {
        result += "values differ;";
    }

    std::vector<uint8_t> truncated(image.begin(), image.end() - 100);
    result += expect_error(truncated, "truncated image");

    std::vector<uint8_t> version = image;
    const int32_t old_version = 150;
    std::memcpy(version.data() + 4, &old_version, 4);
    result += expect_error(version, "version 150");

    std::vector<uint8_t> schema = image;
    const int32_t wrong_count = 99;
    std::memcpy(schema.data() + 12 + 20 * og::CHUNK_BUILDINGS + 12, &wrong_count, 4);
    result += expect_error(schema, "schema mismatch");

    std::vector<uint8_t> trailing = image;
    trailing.push_back(0);
    result += expect_error(trailing, "trailing bytes");

    return result.c_str();
}
ANK_FUNCTION(__test_og_reader_synthetic);

// The OG saves the test runs on, joined by '|': tests/fixtures/og_saves/*.sav (relative to the working directory, as
// CI runs the suite from the repository root), then every Save/<player>/*.sav of the Pharaoh install except the
// family.sav dynasty stubs.
static pcstr __test_og_save_files() {
    static std::string result;
    result.clear();
    namespace fs = std::filesystem;
    std::error_code ec;
    std::vector<std::string> files;
    auto add_dir = [&](const fs::path& dir) {
        std::vector<std::string> found;
        for (const auto& e : fs::directory_iterator(dir, ec)) {
            if (e.is_regular_file() && e.path().extension() == ".sav" && e.path().filename() != "family.sav") {
                found.push_back(fs::absolute(e.path(), ec).generic_string());
            }
        }
        std::sort(found.begin(), found.end());
        files.insert(files.end(), found.begin(), found.end());
    };

    add_dir(fs::path("tests") / "fixtures" / "og_saves");
    const fs::path root(vfs::content_path(vfs::SAVE_FOLDER).c_str());
    if (fs::is_directory(root, ec)) {
        for (const auto& player : fs::directory_iterator(root, ec)) {
            if (player.is_directory()) {
                add_dir(player.path());
            }
        }
    }
    for (const auto& f : files) {
        result += (result.empty() ? "" : "|") + f;
    }
    return result.c_str();
}
ANK_FUNCTION(__test_og_save_files);

// What stage 1 reads from an OG save: "version,treasury,population,buildings_in_use,figures_alive" or "error:...".
// Buildings leave out the temple complex altars and oracles, which the converter does not carry over.
static pcstr __test_og_read_summary(pcstr path) {
    static std::string result;
    og::savegame s;
    std::string error;
    if (!og::read_savegame_file(path, s, error)) {
        result = "error:" + error;
        return result.c_str();
    }
    int buildings = 0;
    for (size_t i = 1; i < s.buildings.size(); ++i) {
        const auto& b = s.buildings[i];
        buildings += (b.state == 1 && b.type != 211 && b.type != 212) ? 1 : 0;
    }
    int figures = 0;
    for (const auto& f : s.figures) {
        figures += (f.state == 1) ? 1 : 0;
    }
    result = std::to_string(s.version) + "," + std::to_string(s.player().treasury) + ","
             + std::to_string(s.player().population) + "," + std::to_string(buildings) + "," + std::to_string(figures);
    return result.c_str();
}
ANK_FUNCTION_1(__test_og_read_summary);

// Loads an OG save from an absolute path through the converter, as the load dialog does for Save/<player>/*.sav.
static bool __test_og_load(pcstr path) {
    return GamestateIO::load_og_savegame(path, true);
}
ANK_FUNCTION_1(__test_og_load);

// The loaded city in the same shape as __test_og_read_summary, version replaced by 0.
static pcstr __test_city_og_summary() {
    static std::string result;
    int buildings = 0;
    for (auto& b : city_buildings()) {
        buildings += (b.id > 0 && b.state == BUILDING_STATE_VALID) ? 1 : 0;
    }
    int figures = 0;
    for (int i = 1; i < MAX_FIGURES; ++i) {
        figures += figure_get(i)->state == FIGURE_STATE_ALIVE ? 1 : 0;
    }
    result = "0," + std::to_string(g_city.finance.treasury.value) + "," + std::to_string(g_city.population.current)
             + "," + std::to_string(buildings) + "," + std::to_string(figures);
    return result.c_str();
}
ANK_FUNCTION(__test_city_og_summary);
