#include "graphics/fontgen/Atlas.hpp"
#include "graphics/fontgen/Charset.hpp"
#include "graphics/fontgen/Font.hpp"
#include "widget/debug_console.h"
#include "imgui/imgui.h"
#include "js/js_game.h"
#include "content/atlas_packer.h"
#include "platform/renderer.h"
#include "game/game.h"
#include "graphics/imagepak_holder.h"

#include <memory>

static int g_current_font_size = 14;
static int g_current_codepoint_start = 0x0410; // Cyrillic А
static int g_current_codepoint_end = 0x044F;   // Cyrillic я
static char g_preview_text[256] = "AbcdefABCDEF";
static bool g_show_atlas = false;

image_packer font_packer;

pcstr g_font_paths[] = {
    "../data/swansea.ttf",
    "../data/corri.ttf",
    "data/swansea.ttf",
    "data/corri.ttf",
};

struct cached_symbold {

};

std::unordered_map<uint32_t, cached_symbold> g_cached_symbols;

ANK_REGISTER_PROPS_ITERATOR(config_load_font_preview_properties);
void config_load_font_preview_properties(bool header) {
    if (header) {
        return;
    }

    bool font_preview_open = ImGui::TreeNodeEx("Font Preview", ImGuiTreeNodeFlags_DefaultOpen, "Font Preview");
    if (!font_preview_open) {
        return;
    }

    ImGui::Text("Font Generator - Runtime Preview");
    ImGui::Separator();
    
    ImGui::SliderInt("Font Size", &g_current_font_size, 8, 48);
    
    ImGui::InputInt("Start Codepoint (hex)", &g_current_codepoint_start, 1, 16, ImGuiInputTextFlags_CharsHexadecimal);
    ImGui::InputInt("End Codepoint (hex)", &g_current_codepoint_end, 1, 16, ImGuiInputTextFlags_CharsHexadecimal);
    
    g_current_codepoint_start = std::max(0, std::min(0xFFFF, g_current_codepoint_start));
    g_current_codepoint_end = std::max(g_current_codepoint_start, std::min(0xFFFF, g_current_codepoint_end));
    
    auto &font_pack = g_image_data->pak_list[PACK_CUSTOM_FONT];
    if (ImGui::InputText("Preview Text", g_preview_text, sizeof(g_preview_text))) {
        int entries_num = strlen(g_preview_text);

        vec2i max_texture_sizes = graphics_renderer()->get_max_image_size();
        int init_result = font_packer.init(entries_num + 1, max_texture_sizes);

        font_pack.handle->images_array.clear();

        auto load_letter_img = [&] (uint32_t symdeck, const Trex::Atlas::Bitmap& bm, int i, int group_id, int atlas_rect_id, int8_t bx, int8_t by) {
            image_t img;
            img.pak_name = font_pack.handle->name;
            img.sgx_index = i;
            img.data_length = -1;
            img.uncompressed_length = -1;
            img.unk00 = -1;
            img.start_index = font_pack.handle->global_image_index_offset;
            img.offset_mirror = 0;

            uint32_t Rmask = 0x000000FF;
            uint32_t Gmask = 0x0000FF00;
            uint32_t Bmask = 0x00FF0000;
            uint32_t Amask = 0xFF000000;

            SDL_Surface *surface = SDL_CreateRGBSurface(SDL_SWSURFACE, bm.Width(), bm.Height(), 32, Rmask, Gmask, Bmask, Amask);
            size_t byteToCopy = bm.Width() * bm.Height() * 4;
            memcpy(surface->pixels, bm.Data().data(), byteToCopy);

            img.width = surface ? surface->w : 0;
            img.height = surface ? surface->h : 0;
            img.temp.surface = (void *)surface;
            img.temp.bearing_x = bx;
            img.temp.bearing_y = by;
            img.temp.symdeck = symdeck;

            img.unk01 = -1;
            img.unk02 = -1;
            img.unk03 = -1;
            img.animation.num_sprites = -1;
            img.animation.unk04 = -1;
            img.animation.sprite_offset = { -1, -1 };
            img.animation.unk05 = -1;
            img.animation.unk06 = -1;
            img.animation.unk07 = -1;
            img.animation.unk08 = -1;
            img.animation.unk09 = -1;
            img.animation.can_reverse = false;
            img.animation.unk10 = -1;
            img.type = -1;
            img.is_fully_compressed = false;
            img.is_external = false;
            img.has_isometric_top = false;
            img.unk11 = -1;
            img.unk12 = -1;
            img.bmp.group_id = group_id;
            img.bmp.name = "custom_font";
            img.bmp.entry_index = 0;
            img.unk13 = -1;
            img.animation.speed_id = 1;
            img.unk14 = -1;
            img.unk15 = -1;
            img.unk16 = -1;
            img.unk17 = -1;
            img.unk18 = -1;
            img.unk19 = -1;
            img.unk20 = -1;

            image_packer_rect *rect = &font_packer.rects[atlas_rect_id];
            rect->input.width = img.width;
            rect->input.height = img.height;

            font_pack.handle->images_array.push_back(img);
        };

        int cp_index = 0;
        //for (uint32_t cp = g_current_codepoint_start; cp <= g_current_codepoint_end; ++cp, ++cp_index) {
        for (uint32_t i = 0; i <= entries_num; ++i, ++cp_index) {
            Trex::Charset charset;
            uint32_t cp = g_preview_text[i];
            charset.AddCodepoint(cp);

            uint8_t colors[] = { 0, 0, 0, 255 };
            Trex::Atlas atlas(g_font_paths[0], g_current_font_size, charset, Trex::RenderMode::COLOR, 1, false, colors);

            char utf8_char[8];
            int utf8_len = 0;

            if (cp <= 0x7F) {
                utf8_char[0] = (char)cp;
                utf8_len = 1;
            } else if (cp <= 0x7FF) {
                utf8_char[0] = 0xC0 | (cp >> 6);
                utf8_char[1] = 0x80 | (cp & 0x3F);
                utf8_len = 2;
            } else if (cp <= 0xFFFF) {
                utf8_char[0] = 0xE0 | (cp >> 12);
                utf8_char[1] = 0x80 | ((cp >> 6) & 0x3F);
                utf8_char[2] = 0x80 | (cp & 0x3F);
                utf8_len = 3;
            }
            utf8_char[utf8_len] = '\0';

            const int bearingX = atlas.GetGlyphs().GetGlyphByIndex(0).bearingX;
            const int bearingY = atlas.GetGlyphs().GetGlyphByIndex(0).bearingY;

            load_letter_img(cp, atlas.GetBitmap(), cp_index, 0, cp_index, bearingX, bearingY);
        }

        font_packer.options.fail_policy = IMAGE_PACKER_NEW_IMAGE;
        font_packer.options.reduce_image_size = 1;
        font_packer.options.sort_by = IMAGE_PACKER_SORT_BY_AREA;

        image_packer_pack(&font_packer);
        font_pack.handle->cleanup_and_destroy();
        font_pack.handle->atlas_pages.reserve(font_packer.result.pages_needed);
        for (uint32_t i = 0; i < font_packer.result.pages_needed; ++i) {
            atlas_data_t atlas_data;
            atlas_data.width = i == font_packer.result.pages_needed - 1 ? font_packer.result.last_image_width : max_texture_sizes.x;
            atlas_data.height = i == font_packer.result.pages_needed - 1 ? font_packer.result.last_image_height : max_texture_sizes.y;
            atlas_data.bmp_size = atlas_data.width * atlas_data.height;
            atlas_data.temp.pixel_buffer = new color[atlas_data.bmp_size];
            memset(atlas_data.temp.pixel_buffer, 0, atlas_data.bmp_size * sizeof(uint32_t));
            atlas_data.texture = nullptr;
            font_pack.handle->atlas_pages.push_back(atlas_data);
        }

        // finish filling in image and atlas information
        for (int i = 0; i < entries_num; i++) {
            image_t &img = font_pack.handle->images_array.at(i);

            image_packer_rect &rect = font_packer.rects[i];
            img.atlas.index = rect.output.image_index;
            atlas_data_t *p_data = &font_pack.handle->atlas_pages.at(img.atlas.index);
            img.atlas.p_atlas = p_data;
            img.atlas.offset = rect.output.pos;

            // load and convert image bitmap data
            image_copy_to_atlas(img);

            int image_id = font_pack.handle->global_image_index_offset + i;
            font_set_letter_id(FONT_SMALL_PLAIN, img.temp.symdeck, image_id, { img.temp.bearing_x, img.temp.bearing_y });
        }

        // create textures from atlas data
        for (int i = 0; i < font_pack.handle->atlas_pages.size(); ++i) {
            atlas_data_t &atlas_data = font_pack.handle->atlas_pages.at(i);
            atlas_data.texture = graphics_renderer()->create_texture_from_buffer(atlas_data.temp.pixel_buffer, atlas_data.width, atlas_data.height);
            assert(atlas_data.texture != nullptr);

            // delete temp data buffer in the atlas
            delete atlas_data.temp.pixel_buffer;
            atlas_data.temp.pixel_buffer = nullptr;
        }

        // remove pointers to raw data buffer in the images
        for (int i = 0; i < font_pack.handle->images_array.size(); ++i) {
            image_t &img = font_pack.handle->images_array.at(i);
            SDL_FreeSurface((SDL_Surface *)img.temp.surface);
            img.temp.surface = nullptr;
        }

        image_packer_reset(font_packer);
    }
    ImGui::Checkbox("Show Atlas Texture", &g_show_atlas);
    
    ImGui::Separator();
    
    ImGui::TextColored(ImVec4(0, 1, 0, 1), "Font loaded: %s", g_font_paths);                       
        
    if (g_show_atlas) {
        painter ctx = game.painter();
        const auto &atlas = font_pack.handle->atlas_pages.front();
        
        ImageDraw::fill_rect({ 0, 0 }, { atlas.width, atlas.height }, COLOR_YELLOW);
        ctx.draw(atlas.texture, { 0, 0 }, {0, 0}, {atlas.width, atlas.height}, COLOR_MASK_NONE, 1.f, 1.f, 0, 0);
    }
    
    ImGui::TreePop();
}
