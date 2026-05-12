#include "graphics/font.h"
#include "content/vfs.h"
#include "core/bstring.h"
#include "core/custom_span.hpp"
#include "fontgen/dynamic_atlas.h"
#include "window/popup_dialog.h"

#include <vector>

template<typename TSymbols>
inline void add_symbols_to_font_packer(image_packer &font_packer,
                                       imagepak_handle font_pack,
                                       span_const<uint8_t> font_data,
                                       font_config fconfig,
                                       const TSymbols &utf8_symbols,
                                       int &cp_index) {
    for (const auto &codepoint : utf8_symbols) {
        DynamicFont::Charset charset;
        charset.AddCodepoint(codepoint);

        uint8_t colors[4] = {
            uint8_t((fconfig.color >> 16) & 0xff),
            uint8_t((fconfig.color >> 8) & 0xff),
            uint8_t((fconfig.color >> 0) & 0xff),
            uint8_t((fconfig.color >> 24) & 0xff)
        };
        DynamicFont::Atlas atlas(font_data, fconfig.size, charset, DynamicFont::RenderMode::COLOR, 0, true, colors, fconfig.bold, fconfig.shadow_offset);

        const auto &bitmap = atlas.GetBitmap();

        image_t img;
        img.pak_name = font_pack.handle->name;
        img.sgx_index = cp_index;
        img.data_length = -1;
        img.uncompressed_length = -1;
        img.unk00 = -1;
        img.start_index = font_pack.handle->global_image_index_offset;
        img.offset_mirror = 0;

        uint32_t Rmask = 0x000000FF;
        uint32_t Gmask = 0x0000FF00;
        uint32_t Bmask = 0x00FF0000;
        uint32_t Amask = 0xFF000000;

        SDL_Surface *surface = SDL_CreateRGBSurface(SDL_SWSURFACE, bitmap.Width(), bitmap.Height(), 32, Rmask, Gmask, Bmask, Amask);
        if (surface) {
            size_t byteToCopy = bitmap.Width() * bitmap.Height() * 4;
            memcpy(surface->pixels, bitmap.Data().data(), byteToCopy);
        }

        img.width = surface ? surface->w : 0;
        img.height = surface ? surface->h : 0;
        img.temp.surface = (void *)surface;
        const auto &glyph = atlas.GetGlyphs().GetGlyphByIndex(0);
        img.temp.bearing_x = glyph.bearingX;
        img.temp.bearing_y = glyph.bearingY;
        img.temp.symdeck = codepoint;
        img.temp.font_type = fconfig.type;

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
        img.bmp.group_id = 0;
        img.bmp.name = "custom_font";
        img.bmp.entry_index = 0;
        img.unk13 = -1;
        img.animation.speed_id = 1;
        img.unk14 = -1;
        img.unk15 = -1;
        img.unk16 = -1;
        img.unk17 = -1;
        img.unk18 = -1;
        img.unk20 = -1;

        image_packer_rect *rect = &font_packer.rects[cp_index];
        rect->input.width = img.width;
        rect->input.height = img.height;

        font_pack.handle->images_array.push_back(img);
        cp_index++;
    }
}


bool fill_font_packer_android(image_packer &font_packer,
                              imagepak_handle font_pack,
                              const font_configs_t &font_configs,
                              const font_utf8_symbols_t &utf8_symbols,
                              vfs::path symbols_font,
                              int &cp_index) {
    std::vector<uint8_t> resolved_font_data;
    {
        const bool is_app_data_font = (symbols_font == "data/neucha.ttf");
        if (is_app_data_font) {
            auto data = vfs::internal_resource_open(symbols_font.c_str());
            if (data.first && data.second > 0) {
                const auto *font_bytes = static_cast<const uint8_t *>(data.first);
                resolved_font_data.assign(font_bytes, font_bytes + data.second);
            }
        }

        if (resolved_font_data.empty()) {
            vfs::reader font_reader = vfs::file_open(symbols_font, "rb");
            if (!font_reader) {
                vfs::path fallback_font_path = symbols_font.resolve();
                font_reader = vfs::file_open(fallback_font_path, "rb");
            }

            if (!font_reader) {
                bstring512 message_text;
                message_text.printf("The specified font symbols file could not be opened:%s", symbols_font.c_str());
                popup_dialog::show_ok("Data issue", message_text.c_str());
                return false;
            }

            const auto *font_bytes = static_cast<const uint8_t *>(font_reader->data());
            resolved_font_data.assign(font_bytes, font_bytes + font_reader->size());
        }
    }

    for (const auto &fconfig : font_configs) {
        add_symbols_to_font_packer(font_packer, font_pack, make_span(resolved_font_data), fconfig, utf8_symbols, cp_index);
        font_definition_ref(fconfig.type)->line_height = fconfig.line_height;
    }
    return true;
}
