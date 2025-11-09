#pragma once
#include <memory>
#include <vector>
#include <map>
#include <string>
#include "dynamic_font.h"
#include "atlas_charset.h"
#include "content/dir.h"

namespace DynamicFont {
    struct Glyph {
        unsigned int codepoint; // Unicode codepoint
        unsigned int glyphIndex; // Index of the glyph in the font
        int x, y; // Top left corner of the glyph in the atlas
        unsigned int width, height;
        int bearingX, bearingY;
    };

    struct Size {
        int width;
        int height;
    };

    enum class RenderMode { DEFAULT, COLOR, SDF, LCD };

    class Atlas {
    public:
        Atlas(const std::string &fontPath, int fontSize, const Charset &, RenderMode, int padding, bool fit, uint8_t *colors, bool bold, int shadowOffset = 0);
        Atlas(span_const<uint8_t> fontData, int fontSize, const Charset &, RenderMode, int padding, bool fit, bool bold, int shadowOffset = 0);

        class FreeTypeGlyph;
        class Bitmap;
        class Glyphs;

        const Bitmap &GetBitmap() const { return m_Bitmap; }
        const Glyphs &GetGlyphs() const { return m_Glyphs; }

        std::shared_ptr<const Font> GetFont() const { return m_Font; }
        void SaveToFile(const vfs::path &path) const;

        class Glyphs {
        public:
            Glyphs(const std::shared_ptr<const Font> font)
                : m_Font(font) {
            }
            const std::map<uint32_t, Glyph> &Data() const { return m_Glyphs; }
            bool Empty() const { return m_Glyphs.empty(); }

            void SetUnknownGlyph(uint32_t codepoint) const;
            void SetUnknownGlyphIndex(uint32_t index) const;
            const Glyph &GetUnknownGlyph() const;
            const Glyph &GetGlyphByCodepoint(uint32_t codepoint) const;
            const Glyph &GetGlyphByIndex(uint32_t index) const;
            void Add(int bitmapX, int bitmapY, const FreeTypeGlyph &);
        private:

            std::map<uint32_t, Glyph> m_Glyphs{};
            std::shared_ptr<const Font> m_Font{};
            mutable uint32_t m_UnknownGlyphIndex = 0;
        };

        class Bitmap {
        public:
            Bitmap() = default;
            Bitmap(unsigned int width, unsigned int height, unsigned int channels);

            const std::vector<uint8_t> &Data() const { return m_Data; }
            unsigned int Width() const { return m_Width; }
            unsigned int Height() const { return m_Height; }
            unsigned int Channels() const { return m_Channels; }

            void Draw(int x, int y, const FreeTypeGlyph &, uint8_t *colors, int shadowOffset = 0);
        private:
            std::vector<uint8_t> m_Data{};
            unsigned int m_Width{};
            unsigned int m_Height{};
            unsigned int m_Channels{};
        };

    private:
        void InitializeAtlas(const Charset &, RenderMode, int padding, bool fit, bool bold, int shadowOffset);
        void InitializeDefaultGlyphIndex();

        std::shared_ptr<Font> m_Font;
        Bitmap m_Bitmap;
        Glyphs m_Glyphs;
        uint8_t m_Color[4] = { 0, 0, 0, 0 };
        int m_ShadowOffset = 0;
    };
}

