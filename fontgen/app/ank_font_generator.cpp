#include "../fgen/Atlas.hpp"

int main() {
    using colors_t = uint8_t[4];
    struct font_config_t {
        int size;
        colors_t color;
        const char *name;
    };

    struct font_symbol_t {
        uint32_t begin, end;
        const char *fontfile;
    };

    font_config_t configs[] = {
        font_config_t{ 10, { 0x00, 0x00, 0x00, 0xFF }, "FONT_SMALL_PLAIN" }, // Black small
        font_config_t{ 14, { 0x00, 0x00, 0x00, 0xFF }, "FONT_NORMAL_BLACK_ON_LIGHT" }, // Black normal
        font_config_t{ 14, { 0xFF, 0xFF, 0xFF, 0xFF }, "FONT_NORMAL_WHITE_ON_DARK" }, // White normal
        font_config_t{ 14, { 0xFF, 0xFF, 0x00, 0xFF }, "FONT_NORMAL_YELLOW" }, // Yellow normal
        font_config_t{ 14, { 0x00, 0x00, 0xFF, 0xFF }, "FONT_NORMAL_BLUE" }, // Blue normal
        font_config_t{ 18, { 0x00, 0x00, 0x00, 0xFF }, "FONT_LARGE_BLACK_ON_LIGHT" }, // Black normal
        font_config_t{ 18, { 0x00, 0x00, 0x00, 0xFF }, "FONT_LARGE_BLACK_ON_DARK" }, // Black normal 2
        font_config_t{ 10, { 0x00, 0x00, 0x00, 0xFF }, "FONT_SMALL_OUTLINED" }, // Black small 2
        font_config_t{ 14, { 0x00, 0x00, 0x00, 0xFF }, "FONT_NORMAL_BLACK_ON_DARK" }, // Black normal 2
        font_config_t{ 10, { 0x00, 0x00, 0x00, 0xFF }, "FONT_SMALL_SHADED" } // Black normal 2
    };

    font_symbol_t symbols[] = {
        { 0x0410, 0x044F, "fonts/corri.ttf"}, // Cyrillic
        { 0x00C4, 0x00C4, "fonts/swansea.ttf"}, // Ä
        { 0x00E4, 0x00E4, "fonts/swansea.ttf"}, // ä
        { 0x00D6, 0x00D6, "fonts/swansea.ttf"}, // Ö
        { 0x00F6, 0x00F6, "fonts/swansea.ttf"}, // ö
        { 0x00DC, 0x00DC, "fonts/swansea.ttf"}, // Ü
        { 0x00FC, 0x00FC, "fonts/swansea.ttf"}, // ü
        { 0x00C9, 0x00C9, "fonts/swansea.ttf"}, // É
        { 0x00E9, 0x00E9, "fonts/swansea.ttf"}, // é
        { 0x00C0, 0x00C0, "fonts/swansea.ttf"}, // À
        { 0x00E0, 0x00E0, "fonts/swansea.ttf"}, // à
        { 0x00C8, 0x00C8, "fonts/swansea.ttf"}, // È
        { 0x00E8, 0x00E8, "fonts/swansea.ttf"}, // è
        { 0x00D9, 0x00D8, "fonts/swansea.ttf"}, // Ù
        { 0x00F9, 0x00F9, "fonts/swansea.ttf"}, // ù
    };

	int index = 0;
	FILE *config_file = fopen("fonts.js", "w");
    fprintf(config_file, "log_info(\"akhenaten: pharaoh_custom_pack started\")\n\n");
	fprintf(config_file, "external_font_symbols = [\n");

    for (const auto &config : configs) {
        for (const auto &symbol : symbols) {
            for (uint32_t i = symbol.begin; i <= symbol.end; ++i) {
                Trex::Charset charset;
                charset.AddCodepoint(i);
                Trex::Atlas atlas(symbol.fontfile, config.size, charset, Trex::RenderMode::COLOR, 1, true, (uint8_t*)config.color);

                char buffer[64];
                snprintf(buffer, sizeof(buffer), "fonts_%05d.png", index);
                atlas.SaveToFile(buffer);

                char utf8_char[8];
                int utf8_len = 0;

                if (i <= 0x7F) {
                    utf8_char[0] = (char)i;
                    utf8_len = 1;
                } else if (i <= 0x7FF) {
                    utf8_char[0] = 0xC0 | (i >> 6);
                    utf8_char[1] = 0x80 | (i & 0x3F);
                    utf8_len = 2;
                } else if (i <= 0xFFFF) {
                    utf8_char[0] = 0xE0 | (i >> 12);
                    utf8_char[1] = 0x80 | ((i >> 6) & 0x3F);
                    utf8_char[2] = 0x80 | (i & 0x3F);
                    utf8_len = 3;
                }
                utf8_char[utf8_len] = '\0';

                const uint32_t sHeight = atlas.GetBitmap().Height();
                const int bearingY = atlas.GetGlyphs().GetGlyphByIndex(0).bearingY;
                const int bearingX = atlas.GetGlyphs().GetGlyphByIndex(0).bearingX;
                fprintf(config_file, "  { symbol:\"%s\", pack:PACK_CUSTOM_FONT, id:%d, offset:%d, font:%s, bearing:[%d, %d] },\n",
                    utf8_char,
                    0,
                    index,
                    config.name,
                    bearingX,
                    bearingY);

                index++;
            }
        }
    }

    fprintf(config_file, "]\n");
    fclose(config_file);

    FILE *pack_json_file = fopen("pharaoh_fonts_pack.js", "w");
    fprintf(pack_json_file, "log_info(\"akhenaten: pharaoh_fonts_pack started\")\n\n");
    fprintf(pack_json_file, "pharaoh_fonts_pack = [\n");
    fprintf(pack_json_file, "{ name:\"fonts\", prefix:\"fonts_\", start_index:0, finish_index:%d },\n", (index - 1));
    fprintf(pack_json_file, "]\n");

	return 0;
}
