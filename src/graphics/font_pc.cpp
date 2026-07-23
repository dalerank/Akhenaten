#include "graphics/font.h"
#include "content/vfs.h"
#include "core/bstring.h"
#include "core/log.h"
#include "fontgen/dynamic_atlas.h"

template<typename TSymbols>
inline void add_symbols_to_font_packer(image_packer &font_packer,
                                       imagepak_handle font_pack,
                                       pcstr symbols_font,
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
        // padding=0, fit=true to create bitmaps with exact glyph dimensions
        DynamicFont::Atlas atlas(symbols_font, fconfig.size, charset, DynamicFont::RenderMode::COLOR, 0, true, colors, fconfig.bold, fconfig.shadow_offset);

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

bool fill_font_packer_pc(image_packer &font_packer,
                         imagepak_handle font_pack,
                         const font_configs_t &font_configs,
                         const font_utf8_symbols_t &utf8_symbols,
                         vfs::path symbols_font,
                         int &cp_index) {
    vfs::path resolved_font_path = symbols_font.resolve();
    if (!vfs::file_exists(resolved_font_path)) {
        logs::warn("font: TTF not found: %s", resolved_font_path.c_str());
        return false;
    }

    for (const auto &fconfig : font_configs) {
        add_symbols_to_font_packer(font_packer, font_pack, resolved_font_path.c_str(), fconfig, utf8_symbols, cp_index);
        font_definition_ref(fconfig.type)->line_height = fconfig.line_height;
    }
    return true;
}
