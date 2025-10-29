#include "content/vfs.h"

#include "cmrc/cmrc.hpp"
#include "js/js_game.h"
#include "core/log.h"
#include <filesystem>

CMRC_DECLARE(akhenaten);

namespace fs = std::filesystem;

namespace vfs {

    constexpr pcstr internal_scripts_path = "src/scripts/";

    std::pair<void *, uint32_t> internal_file_open(pcstr path) {
        if (!path || !*path) {
            return { nullptr, 0 };
        }

        auto fs = cmrc::akhenaten::get_filesystem();

        bstring256 fs_path(internal_scripts_path, (*path == ':') ? (path + 1) : path);
        if (!fs.exists(fs_path.c_str())) {
            return { nullptr, 0 };
        }

        auto fd1 = fs.open(fs_path.c_str());
        return { (void *)fd1.begin(), (uint32_t)fd1.size() };
    }

    // Helper function to unpack a directory recursively
    void unpack_directory(const cmrc::embedded_filesystem &filesystem, const std::string &internal_path, const fs::path &output_base, int &files_unpacked, int &files_failed) {
        for (auto &&entry : filesystem.iterate_directory(internal_path)) {
            std::string filename = entry.filename();
            std::string full_internal_path = internal_path + filename;

            if (entry.is_directory()) {
                // Create subdirectory and recurse
                fs::path subdir = output_base / filename;
                fs::create_directories(subdir);
                logs::info("Created directory: %s", subdir.string().c_str());

                // Recurse into subdirectory
                unpack_directory(filesystem, full_internal_path + "/", subdir, files_unpacked, files_failed);

            } else if (entry.is_file()) {
                // Open the embedded file
                auto file = filesystem.open(full_internal_path);

                // Create output file path
                fs::path output_file = output_base / filename;

                // Write file to disk
                std::ofstream out(output_file, std::ios::binary);
                if (!out) {
                    logs::error("Failed to create file: %s", output_file.string().c_str());
                    files_failed++;
                    continue;
                }

                out.write(file.begin(), file.size());
                out.close();

                logs::info("Unpacked: %s (%zu bytes)", full_internal_path.c_str(), file.size());
                files_unpacked++;
            }
        }
    }

    // Function to unpack embedded scripts to disk
    xstring platform_unpack_scripts() {
        logs::info("=== Starting to unpack embedded scripts ===");

        auto filesystem = cmrc::akhenaten::get_filesystem();

        // Get base path for writing files
        pcstr base_path = vfs::platform_file_manager_get_base_path();
        if (!base_path) {
            logs::error("Failed to get base path for unpacking scripts");
            return xstring{};
        }

        // Create output directory
        fs::path output_dir = fs::path(base_path) / "Scripts";
        fs::create_directories(output_dir);
        logs::info("Output directory: %s", output_dir.string().c_str());

        // Unpack all scripts
        constexpr const char *scripts_path = "src/scripts/";
        int files_unpacked = 0;
        int files_failed = 0;

        vfs::unpack_directory(filesystem, scripts_path, output_dir, files_unpacked, files_failed);

        logs::info("=== Unpack complete! ===");
        logs::info("Files unpacked: %d", files_unpacked);
        logs::info("Files failed: %d", files_failed);
        logs::info("Location: %s", output_dir.string().c_str());

        return xstring(output_dir.string().c_str());
    }
}

