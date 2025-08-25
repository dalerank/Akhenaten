#include "../fgen/Atlas.hpp"

int main() {
	const char* FONT_PATH = "fonts/corri.ttf";

    using colors_t = uint8_t[4];
    struct font_config_t {
        int size;
        colors_t color;
        const char *name;
    };

    struct font_symbol_t {
        uint32_t begin, end;
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
        { 0x0410, 0x044F }, // Cyrillic
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
                Trex::Atlas atlas(FONT_PATH, config.size, charset, Trex::RenderMode::COLOR, 1, true, (uint8_t*)config.color);

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
