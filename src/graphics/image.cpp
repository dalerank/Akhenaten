#include "image.h"
#include "io/imagepaks/imagepak.h"
#include "image_groups.h"
#include "font.h"

static struct {
    bool fonts_enabled;
    int font_base_offset;

    std::vector<imagepak**> pak_list;

    imagepak *main;
    imagepak *terrain;
    imagepak *unloaded;
    imagepak *sprmain;
    imagepak *sprambient;

    imagepak *expansion;
    imagepak *sprmain2;

    std::vector<imagepak*> temple_paks;
    std::vector<imagepak*> monument_paks;
    std::vector<imagepak*> enemy_paks;
    std::vector<imagepak*> font_paks;

    imagepak *temple;
    imagepak *monument;
    imagepak *enemy;
    imagepak *empire;
    imagepak *font;

    color_t *tmp_image_data;
} data;

// These functions are actually related to the imagepak class I/O, but it made slightly more
// sense to me to have here as "core" image struct/class & game graphics related functions.

bool set_pak_in_collection(int pak_id, imagepak **pak, std::vector<imagepak*> *collection) {
    if (pak_id >= collection->size())
        return false;
    *pak = collection->at(pak_id);
    return true;
}
bool image_set_font_pak(encoding_type encoding) {
    // TODO?
    if (encoding == ENCODING_CYRILLIC)
        return false;
    else if (encoding == ENCODING_TRADITIONAL_CHINESE)
        return false;
    else if (encoding == ENCODING_SIMPLIFIED_CHINESE)
        return false;
    else if (encoding == ENCODING_KOREAN)
        return false;
    else {
//        free(data.font);
//        free(data.font_data);
//        data.font = 0;
//        data.font_data = 0;
        data.fonts_enabled = NO_EXTRA_FONT;
        return true;
    }
}
bool image_set_enemy_pak(int enemy_id) {
    return set_pak_in_collection(enemy_id, &data.enemy, &data.enemy_paks);
}
bool image_set_temple_complex_pak(int temple_id) {
    return set_pak_in_collection(temple_id, &data.temple, &data.temple_paks);
}
bool image_set_monument_pak(int monument_id) {
    return set_pak_in_collection(monument_id, &data.monument, &data.monument_paks);
}
bool image_load_paks() {
    data.fonts_enabled = false;
    data.font_base_offset = 0;

    // add paks to parsing list cache
    data.pak_list.push_back(&data.sprmain);
    data.pak_list.push_back(&data.unloaded);
    data.pak_list.push_back(&data.main);
    data.pak_list.push_back(&data.terrain);
    data.pak_list.push_back(&data.temple);
    data.pak_list.push_back(&data.sprambient);
    data.pak_list.push_back(&data.font);
    data.pak_list.push_back(&data.empire);
    data.pak_list.push_back(&data.sprmain2);
    data.pak_list.push_back(&data.expansion);
    data.pak_list.push_back(&data.monument);

    const char *filename_555;
    const char *filename_sgx;

    // Pharaoh loads every image into a global listed cache; however, some
    // display systems use discordant indexes; The sprites cached in the
    // save files, for examples, appear to start at 700 while the terrain
    // system displays them starting at the immediate index after the first
    // pak has ended (683).
    // Moreover, the monuments, temple complexes, and enemies all make use
    // of a single shared index, which is swapped in "real time" for the
    // correct pak in use by the mission, or even depending on buildings
    // present on the map, like the Temple Complexes.
    // What an absolute mess!

    data.unloaded = new imagepak("Pharaoh_Unloaded", 0, true);                 // 0     --> 682
    data.sprmain = new imagepak("SprMain", 700);                                            // 700   --> 11007
    // <--- original enemy pak in here                                                                              // 11008 --> 11866
    data.main = new imagepak("Pharaoh_General", 11906 -200);                                // 11906 --> 11866
    data.terrain = new imagepak("Pharaoh_Terrain", 14452 -200);                             // 14252 --> 15767 (+64)
    // <--- original temple complex pak here
    data.sprambient = new imagepak("SprAmbient", 15831);                                    // 15831 --> 18765
    data.font = new imagepak("Pharaoh_Fonts", 18765, false, true);       // 18765 --> 20305
    data.empire = new imagepak("Empire", 20305);                                            // 20305 --> 20506 (+177)
    data.sprmain2 = new imagepak("SprMain2", 20683);                                        // 20683 --> 23035
    data.expansion = new imagepak("Expansion", 23035);                                      // 23035 --> 23935 (-200)
    // <--- original pyramid pak in here                                                                            // 23735 --> 24163

    // the 5 Temple Complex paks.
    data.temple_paks.push_back(new imagepak("Temple_nile", 15591));
    data.temple_paks.push_back(new imagepak("Temple_ra", 15591));
    data.temple_paks.push_back(new imagepak("Temple_ptah", 15591));
    data.temple_paks.push_back(new imagepak("Temple_seth", 15591));
    data.temple_paks.push_back(new imagepak("Temple_bast", 15591));

    // the various Monument paks.
    data.monument_paks.push_back(new imagepak("Mastaba", 23735));
    data.monument_paks.push_back(new imagepak("Pyramid", 23735));
    data.monument_paks.push_back(new imagepak("bent_pyramid", 23735));

    // the various Enemy paks.
    static const char* enemy_file_names_ph[14] = {
            "Assyrian",
            "Egyptian",
            "Canaanite",
            "Enemy_1",
            "Hittite",
            "Hyksos",
            "Kushite",
            "Libian",
            "Mitani",
            "Nubian",
            "Persian",
            "Phoenician",
            "Roman",
            "SeaPeople"
    };
    for (int i = 0; i < 14; ++i) {
        if (enemy_file_names_ph[i] != "")
            data.enemy_paks.push_back(new imagepak(enemy_file_names_ph[i], 11026));
    }

    // (set the first in the bunch as active initially, just for defaults)
    data.temple = data.temple_paks.at(0);
    data.monument = data.monument_paks.at(0);
    data.enemy = data.enemy_paks.at(0);

    return true;
}

static imagepak *pak_from_collection_id(int collection, int pak_cache_idx) {
    switch (collection) {
        case IMAGE_COLLECTION_UNLOADED:
            return data.unloaded;
        case IMAGE_COLLECTION_TERRAIN:
            return data.terrain;
        case IMAGE_COLLECTION_GENERAL:
            return data.main;
        case IMAGE_COLLECTION_SPR_MAIN:
            return data.sprmain;
        case IMAGE_COLLECTION_SPR_AMBIENT:
            return data.sprambient;
        case IMAGE_COLLECTION_EMPIRE:
            return data.empire;
            /////
        case IMAGE_COLLECTION_FONT:
            if (pak_cache_idx < 0 || pak_cache_idx >= data.font_paks.size())
                return data.font;
            else
                return data.font_paks.at(pak_cache_idx);
            return data.font;
            /////
        case IMAGE_COLLECTION_TEMPLE:
            if (pak_cache_idx < 0 || pak_cache_idx >= data.temple_paks.size())
                return data.temple;
            else
                return data.temple_paks.at(pak_cache_idx);
        case IMAGE_COLLECTION_MONUMENT:
            if (pak_cache_idx < 0 || pak_cache_idx >= data.monument_paks.size())
                return data.monument;
            else
                return data.monument_paks.at(pak_cache_idx);
        case IMAGE_COLLECTION_ENEMY:
            if (pak_cache_idx < 0 || pak_cache_idx >= data.enemy_paks.size())
                return data.enemy;
            else
                return data.enemy_paks.at(pak_cache_idx);
            /////
        case IMAGE_COLLECTION_EXPANSION:
            return data.expansion;
        case IMAGE_COLLECTION_EXPANSION_SPR:
            return data.sprmain2;
            /////
    }
    return nullptr;
}
int image_id_from_group(int collection, int group, int pak_cache_idx) {
    imagepak *pak = pak_from_collection_id(collection, pak_cache_idx);
    if (pak == nullptr)
        return -1;
    return pak->get_global_image_index(group);
}
const image_t *image_get(int id, int mode) {
    const image_t *img;
    for (int i = 0; i < data.pak_list.size(); ++i) {
        imagepak *pak = *(data.pak_list.at(i));
        if (pak == nullptr)
            continue;
        img = (pak)->get_image(id);
        if (img != nullptr)
            return img;
    }
    // default (failure)
    return nullptr;
}
const image_t *image_letter(int letter_id) {
    if (data.fonts_enabled == FULL_CHARSET_IN_FONT)
        return data.font->get_image(data.font_base_offset + letter_id);
    else if (data.fonts_enabled == MULTIBYTE_IN_FONT && letter_id >= IMAGE_FONT_MULTIBYTE_OFFSET)
        return data.font->get_image(data.font_base_offset + letter_id - IMAGE_FONT_MULTIBYTE_OFFSET);
    else if (letter_id < IMAGE_FONT_MULTIBYTE_OFFSET)
        return image_get(image_id_from_group(GROUP_FONT) + letter_id);
    else
        return nullptr;
}
const image_t *image_get_enemy(int id) {
    return data.enemy->get_image(id);
}