#include "dynamic_atlas.h"

#include "dynamic_font.h"
#include <ft2build.h>
#include <freetype/ftoutln.h>
#include <freetype/ftglyph.h>
#if __has_include(<freetype/ftsdfrend.h>)
#define AKHN_HAVE_FT_SDF 1
#include <freetype/ftsdfrend.h>
#endif

#include FT_FREETYPE_H
#include FT_SYNTHESIS_H
#include <cstdint>
#include <vector>
#include <string_view>
#include <stdexcept>
#include <map>
#include <cassert>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#define	STB_IMAGE_WRITE_STATIC
#include <stb_image_write.h>

namespace DynamicFont {
    // RAII wrapper for FreeType glyph
    class Atlas::FreeTypeGlyph {
    public:
        FreeTypeGlyph(uint32_t codepoint, FT_GlyphSlot glyphSlot) : codepoint{ codepoint } {
            assert((glyphSlot != nullptr) && "Glyph slot is null");
            assert((glyphSlot->format == FT_GLYPH_FORMAT_BITMAP) && "Glyph format must be a bitmap");

            metrics = glyphSlot->metrics;
            glyphIndex = glyphSlot->glyph_index;

            FT_Glyph genericGlyph;
            FT_Error error = FT_Get_Glyph(glyphSlot, &genericGlyph);
            assert(!error && "Failed to get a glyph");

            glyph = (FT_BitmapGlyph)genericGlyph;
        }

        ~FreeTypeGlyph() {
            FT_Done_Glyph((FT_Glyph)glyph);
        }

        FreeTypeGlyph(const FreeTypeGlyph &) = delete;
        FreeTypeGlyph &operator=(const FreeTypeGlyph &) = delete;

        FreeTypeGlyph(FreeTypeGlyph &&other) noexcept : codepoint{ other.codepoint },
            glyph{ std::exchange(other.glyph, nullptr) },
            metrics{ other.metrics },
            glyphIndex{ other.glyphIndex } {
        }
        FreeTypeGlyph &operator=(FreeTypeGlyph &&other) noexcept {
            codepoint = other.codepoint;
            glyph = std::exchange(other.glyph, nullptr);
            metrics = other.metrics;
            glyphIndex = other.glyphIndex;
            return *this;
        }

        const unsigned char &ByteAt(int x, int y) const {
            return Data()[y * Stride() + x];
        }

        unsigned char *Data() const {
            return glyph->bitmap.buffer;
        }

        unsigned int Width() const // in pixels
        {
            if (glyph->bitmap.pixel_mode == FT_PIXEL_MODE_LCD) {
                return glyph->bitmap.width / 3;
            }
            return glyph->bitmap.width;
        }
        unsigned int Height() const // in pixels
        {
            return glyph->bitmap.rows;
        }
        int Stride() const // in bytes
        {
            return glyph->bitmap.pitch;
        }
        int Channels() const {
            switch (glyph->bitmap.pixel_mode) {
            case FT_PIXEL_MODE_GRAY:
                return 1;
            case FT_PIXEL_MODE_LCD:
                return 3;
            case FT_PIXEL_MODE_BGRA:
                return 4;
            default:
                assert(false && "Unsupported pixel mode");
                return 1;
            }
        }

        uint8_t ColorRed(int x, int y) const {
            int offset = 0;
            switch (glyph->bitmap.pixel_mode) {
            case FT_PIXEL_MODE_BGRA: offset = 2; break;
            }

            return ByteAt(x * Channels() + offset, y);
        }

        uint8_t ColorGreen(int x, int y) const {
            int offset = 0;
            switch (glyph->bitmap.pixel_mode) {
            case FT_PIXEL_MODE_LCD:
            case FT_PIXEL_MODE_BGRA: offset = 1; break;
            }
            return ByteAt(x * Channels() + offset, y);
        }
        
        uint8_t ColorBlue(int x, int y) const {
            int offset = 0;
            switch (glyph->bitmap.pixel_mode) {
            case FT_PIXEL_MODE_LCD: offset = 2; break;
            }

            return ByteAt(x * Channels() + offset, y);
        }
        
        uint8_t ColorAlpha(int x, int y) const {
            if (glyph->bitmap.pixel_mode == FT_PIXEL_MODE_BGRA) {
                return ByteAt(x * Channels() + 3, y);
            }
            if (glyph->bitmap.pixel_mode == FT_PIXEL_MODE_LCD) {
                return 255;
            }

            return ByteAt(x * Channels(), y);
        }

        int Index() const { return glyphIndex; }

    private:
        uint32_t codepoint{};
        FT_BitmapGlyph glyph{};
        FT_Glyph_Metrics metrics{};
        uint32_t glyphIndex{};
        friend class Atlas::Glyphs;
    };

    namespace {
        // Note: calling this function will invalidate the previous FT_GlyphSlot returned.
        FT_GlyphSlot LoadGlyphWithoutRender(FT_Face fontFace, uint32_t codepoint, bool color = false) {
            FT_Int32 flags = color ? FT_LOAD_COLOR : FT_LOAD_DEFAULT;
            FT_Error error = FT_Load_Char(fontFace, codepoint, flags);
            assert(!error && "Error: could not load and render char");

            return fontFace->glyph;
        }

        FT_GlyphSlot LoadGlyphWithGrayscaleRender(FT_Face fontFace, uint32_t codepoint, bool bold) {
            auto glyph = LoadGlyphWithoutRender(fontFace, codepoint, false);

            // Apply bold effect before rendering if requested
            if (bold && glyph->format == FT_GLYPH_FORMAT_OUTLINE) {
                // Embolden by approximately 1/16th of em size (adjustable strength)
                FT_Pos strength = fontFace->size->metrics.x_ppem * 64 / 16;
                FT_Outline_Embolden(&glyph->outline, strength);
            }

            FT_Error error = FT_Render_Glyph(glyph, FT_RENDER_MODE_NORMAL);            
            assert(!error && "Error: could not load and render char");

            return glyph;
        }

        FT_GlyphSlot LoadGlyphWithColorRender(FT_Face fontFace, uint32_t codepoint, bool bold) {
            auto glyph = LoadGlyphWithoutRender(fontFace, codepoint, true);

            // Apply bold effect before rendering if requested
            if (bold && glyph->format == FT_GLYPH_FORMAT_OUTLINE) {
                FT_Pos strength = fontFace->size->metrics.x_ppem * 64 / 16;
                FT_Outline_Embolden(&glyph->outline, strength);
            }

            FT_Error error = FT_Render_Glyph(glyph, FT_RENDER_MODE_NORMAL);
            assert(!error && "Error: could not load and render char");
            return glyph;
        }

        FT_GlyphSlot LoadGlyphWithSdfRender(FT_Face fontFace, uint32_t codepoint, bool bold) {
#ifdef AKHN_HAVE_FT_SDF
            // Use bsdf renderer instead of sdf renderer.
            // See: https://freetype.org/freetype2/docs/reference/ft2-base_interface.html#ft_render_mode
            // First I need to render the glyph with normal mode, then render it with sdf mode.
            auto glyph = LoadGlyphWithGrayscaleRender(fontFace, codepoint, bold);

            // But the bsdf renderer cannot handle the glyph with zero width or height (e.g. space).
            // It is a result of a bug in FreeType. It is already fixed on master branch. (86d0ca24)
            // In the future the `bool isGlyphEmpty` check will not be needed.
            FT_Error error{};
            bool isGlyphEmpty = glyph->bitmap.width == 0 || glyph->bitmap.rows == 0;
            if (!isGlyphEmpty)
                error = FT_Render_Glyph(glyph, FT_RENDER_MODE_SDF);
            assert(!error && "Error: could not load and render char");
            return glyph;
#else
            // Fallback to grayscale render when SDF renderer is unavailable
            return LoadGlyphWithGrayscaleRender(fontFace, codepoint, bold);
#endif
        }

        FT_GlyphSlot LoadGlyphWithSubpixelRender(FT_Face fontFace, uint32_t codepoint) {
            auto glyphNormal = LoadGlyphWithoutRender(fontFace, codepoint);
            auto normalWidth = glyphNormal->bitmap.width;

            FT_Load_Char(fontFace, codepoint, FT_LOAD_DEFAULT);
            FT_Render_Glyph(fontFace->glyph, FT_RENDER_MODE_LCD);

            auto &glyph = fontFace->glyph;

            return fontFace->glyph;
        }

        Atlas::FreeTypeGlyph LoadGlyph(FT_Face fontFace, uint32_t codepoint, RenderMode mode, bool bold) {
            switch (mode) {
            case RenderMode::DEFAULT:
                return Atlas::FreeTypeGlyph{ codepoint, LoadGlyphWithGrayscaleRender(fontFace, codepoint, bold) };
            case RenderMode::COLOR:
                return Atlas::FreeTypeGlyph{ codepoint, LoadGlyphWithColorRender(fontFace, codepoint, bold) };
            case RenderMode::SDF:
                return Atlas::FreeTypeGlyph{ codepoint, LoadGlyphWithSdfRender(fontFace, codepoint, bold) };
            case RenderMode::LCD:
                return Atlas::FreeTypeGlyph{ codepoint, LoadGlyphWithSubpixelRender(fontFace, codepoint) };
            default:
                assert(false && "Unsupported render mode");
                return Atlas::FreeTypeGlyph{ codepoint, LoadGlyphWithGrayscaleRender(fontFace, codepoint, bold) };
            }
        }

        std::vector<Atlas::FreeTypeGlyph> LoadAllGlyphs(FT_Face fontFace, const Charset &charset, RenderMode mode, bool bold) {
            std::vector<Atlas::FreeTypeGlyph> allGlyphs;
            allGlyphs.reserve(charset.Size());
            for (uint32_t codepoint : charset.Codepoints()) {
                allGlyphs.push_back(LoadGlyph(fontFace, codepoint, mode, bold));
            }

            return allGlyphs;
        }

        /**
        * Try to fill all glyphs into the atlas with the given size.
        * Return true if all glyphs can fit into the atlas.
        *
        * @param ftGlyphs - FreeType glyphs to be placed into the atlas.
        * @param atlasSize - Size of the atlas in pixels.
        * @param padding - Padding between glyphs in pixels.
        *
        * @return True if all glyphs can fit into the atlas, false otherwise.
        */
        bool IsAtlasSizeEnough(const std::vector<Atlas::FreeTypeGlyph> &ftGlyphs, unsigned int atlasSize, int padding) {
            int x = 0;
            int y = 0;
            unsigned int maxHeight = 0;
            for (const auto &glyph : ftGlyphs) {
                unsigned int glyphWidth = glyph.Width() + padding * 2;
                unsigned int glyphHeight = glyph.Height() + padding * 2;

                maxHeight = std::max(maxHeight, glyphHeight);
                if (x + glyphWidth > atlasSize) // Next row
                {
                    x = 0;
                    y += static_cast<int>(maxHeight);
                    maxHeight = glyphHeight;
                }
                if (y + glyphHeight > atlasSize) {
                    return false;
                }
                x += static_cast<int>(glyphWidth);
            }
            return true;
        }

        /**
        * Get the smallest atlas size that can fit all glyphs.
        *
        * @param glyphsMetrics - Metrics of the glyphs to be placed into the atlas.
        * @param padding - Padding between glyphs in pixels.
        *
        * @return The smallest atlas size in pixels that can fit all glyphs.
        *         The atlas size is always a square with the power of 2.
        */
        Size GetAtlasSize(const std::vector<Atlas::FreeTypeGlyph> &glyphsMetrics, int padding, bool fit) {
            int atlasSize = 8; // Start with 128x128
            if (fit) {
                auto &glyph = glyphsMetrics.front();
                return Size{ int(glyph.Width()) + padding * 2, int(glyph.Height()) + padding * 2 };
            } else {
                while (!IsAtlasSizeEnough(glyphsMetrics, atlasSize, padding)) {
                    atlasSize *= 2;
                }
            }

            return Size{ atlasSize, atlasSize };
        }

        Atlas::Bitmap BuildAtlasBitmap(
            Atlas::Glyphs &glyphs, const std::vector<Atlas::FreeTypeGlyph> &ftGlyphs, Size atlasSize, int padding, int channels, uint8_t *colors, int shadowOffset) {
            Atlas::Bitmap bitmap(atlasSize.width, atlasSize.height, channels);

            int atlasX = 0;
            int atlasY = 0;
            int maxHeight = 0;
            for (const auto &glyph : ftGlyphs) {
                unsigned int glyphWidth = glyph.Width();
                unsigned int glyphHeight = glyph.Height();

                int glyphWidthPadding = static_cast<int>(glyphWidth) + padding * 2 + shadowOffset;
                int glyphHeightPadding = static_cast<int>(glyphHeight) + padding * 2 + shadowOffset;

                maxHeight = std::max(maxHeight, glyphHeightPadding);
                // If we are out of atlas bounds, go to the next line
                if (atlasX + glyphWidthPadding * channels > atlasSize.width * channels) {
                    atlasX = 0;
                    atlasY += maxHeight;
                    maxHeight = glyphHeightPadding;
                }

                // Copy glyph bitmap to atlas bitmap
                int glyphXPosInBitmap = atlasX / channels + padding; // in pixels
                int glyphYPosInBitmap = atlasY + padding;

                bitmap.Draw(glyphXPosInBitmap, glyphYPosInBitmap, glyph, colors, shadowOffset);
                glyphs.Add(glyphXPosInBitmap, glyphYPosInBitmap, glyph);

                atlasX += glyphWidthPadding * channels;
            }

            return bitmap;
        }

        Charset GetFullCharsetFilled(Font &font) {
            Charset charset;
            charset.AddCodepoint(0xFFFF); // Add unknown glyph. It will have index 0.

            FT_UInt nextGlyphIndex;
            FT_ULong codepoint = FT_Get_First_Char(font.face, &nextGlyphIndex);

            while (nextGlyphIndex != 0) {
                charset.AddCodepoint(codepoint);
                codepoint = FT_Get_Next_Char(font.face, codepoint, &nextGlyphIndex);
            }

            return charset;
        }

        int GetChannels(RenderMode mode) {
            switch (mode) {
            case RenderMode::DEFAULT: return 1;
            case RenderMode::COLOR: return 4;
            case RenderMode::SDF: return 1;
            case RenderMode::LCD: return 3;
            default: 
                assert(false && "Unknown render mode");
                return 1;
            }
        }
    } // namespace

    void Atlas::Glyphs::Add(int bitmapX, int bitmapY, const FreeTypeGlyph &ftGlyph) {
        Glyph glyph;

        glyph.codepoint = ftGlyph.codepoint;
        glyph.glyphIndex = ftGlyph.glyphIndex;
        glyph.x = bitmapX;
        glyph.y = bitmapY;
        glyph.width = ftGlyph.Width();
        glyph.height = ftGlyph.Height();
        glyph.bearingX = (int)(ftGlyph.metrics.horiBearingX / 64);
        glyph.bearingY = (int)(ftGlyph.metrics.horiBearingY / 64);

        m_Glyphs[ftGlyph.glyphIndex] = glyph;
    }

    const Glyph &Atlas::Glyphs::GetGlyphByCodepoint(uint32_t codepoint) const {
        return GetGlyphByIndex(m_Font->GetGlyphIndex(codepoint));
    }

    const Glyph &Atlas::Glyphs::GetGlyphByIndex(uint32_t index) const {
        auto it = m_Glyphs.find(index);
        return (it != m_Glyphs.end()) ? it->second : m_Glyphs.at(m_UnknownGlyphIndex);
    }

    void Atlas::Glyphs::SetUnknownGlyph(uint32_t codepoint) const {
        auto index = m_Font->GetGlyphIndex(codepoint);
        SetUnknownGlyphIndex(index);
    }

    const Glyph &Atlas::Glyphs::GetUnknownGlyph() const {
        return GetGlyphByIndex(m_UnknownGlyphIndex);
    }

    void Atlas::Glyphs::SetUnknownGlyphIndex(uint32_t index) const {
        auto it = m_Glyphs.find(index);
        if (it != m_Glyphs.end()) {
            m_UnknownGlyphIndex = index;
        }
    }

    Atlas::Bitmap::Bitmap(unsigned int width, unsigned int height, unsigned int channels)
        : m_Width(width), m_Height(height), m_Channels(channels) {
        m_Data.resize(width * height * channels);

        int fillColor = Channels() > 1 ? 0 : 255;
        std::fill(m_Data.begin(), m_Data.end(), fillColor);
    }

    void DrawRGBA(std::vector<uint8_t> &data, const Atlas::FreeTypeGlyph &glyph, size_t atlasIdx, int glyphX, int glyphY, uint8_t *color) {
        assert(glyph.Channels() == 4 || glyph.Channels() == 1);
        uint8_t r = glyph.ColorRed(glyphX, glyphY);
        uint8_t g = glyph.ColorGreen(glyphX, glyphY);
        uint8_t b = glyph.ColorBlue(glyphX, glyphY);
        uint8_t a = glyph.ColorAlpha(glyphX, glyphY);

        if (glyph.Channels() == 1) {
            // For grayscale glyphs, the alpha is the coverage
            // If color is specified, apply it with the alpha from the glyph
            if (color && color[3] > 0) {
                // To avoid color halo around text, interpolate RGB from black to target color
                // based on alpha. This works with standard SDL_BLENDMODE_BLEND.
                // For low alpha (anti-aliased edges), RGB gradually transitions from black to color
                float alpha_normalized = a / 255.0f;
                // Apply a power curve to make the transition more aggressive
                float color_factor = alpha_normalized * alpha_normalized;
                r = static_cast<uint8_t>(color[0] * color_factor);
                g = static_cast<uint8_t>(color[1] * color_factor);
                b = static_cast<uint8_t>(color[2] * color_factor);
            } else {
                // No color specified, invert to get white text
                r = 255 - r;
                g = 255 - g;
                b = 255 - b;
            }
        } else {
            // For color glyphs (e.g., emoji), use as-is or apply color override
            if (color && color[3] > 0) {
                float alpha_normalized = a / 255.0f;
                float color_factor = alpha_normalized * alpha_normalized;
                r = static_cast<uint8_t>(color[0] * color_factor);
                g = static_cast<uint8_t>(color[1] * color_factor);
                b = static_cast<uint8_t>(color[2] * color_factor);
            }
        }

        data[atlasIdx + 0] = r;
        data[atlasIdx + 1] = g;
        data[atlasIdx + 2] = b;
        data[atlasIdx + 3] = a;
    }

    void DrawGray(std::vector<uint8_t> &data, const Atlas::FreeTypeGlyph &glyph, size_t atlasIdx, int glyphX, int glyphY) {
        assert(glyph.Channels() == 1);
        uint8_t gray = glyph.ByteAt(glyphX, glyphY);
        data[atlasIdx] = 255 - gray;
    }

    void DrawRGB(std::vector<uint8_t> &data, const Atlas::FreeTypeGlyph &glyph, size_t atlasIdx, int glyphX, int glyphY) {
        assert(glyph.Channels() == 3);
        data[atlasIdx + 0] = glyph.ColorRed(glyphX, glyphY);
        data[atlasIdx + 1] = glyph.ColorGreen(glyphX, glyphY);
        data[atlasIdx + 2] = glyph.ColorBlue(glyphX, glyphY);
    }

    void Atlas::Bitmap::Draw(int x, int y, const Atlas::FreeTypeGlyph &glyph, uint8_t *colors, int shadowOffset) {
        int bitmapWidth = Width();
        int bitmapChannels = Channels();

        unsigned int glyphHeight = glyph.Height();
        unsigned int glyphWidth = glyph.Width();
        int glyphChannels = glyph.Channels();

        // Draw shadow first (if shadowOffset > 0)
        if (shadowOffset > 0 && bitmapChannels == 4) {
            uint8_t shadowColor[4] = { 0, 0, 0, 128 }; // Semi-transparent black shadow
            for (unsigned int glyphY = 0; glyphY < glyphHeight; ++glyphY) {
                unsigned int atlasBitmapRow = (y + glyphY + shadowOffset) * bitmapWidth * bitmapChannels;
                for (unsigned int glyphX = 0; glyphX < glyphWidth; ++glyphX) {
                    unsigned int atlasBitmapIndex = atlasBitmapRow + (x + shadowOffset) * bitmapChannels + glyphX * bitmapChannels;
                    // Draw shadow with reduced alpha
                    uint8_t glyphAlpha = glyph.ByteAt(glyphX, glyphY);
                    if (glyphAlpha > 0) {
                        uint8_t shadowAlpha = (glyphAlpha * shadowColor[3]) / 255;
                        m_Data[atlasBitmapIndex + 0] = shadowColor[0];
                        m_Data[atlasBitmapIndex + 1] = shadowColor[1];
                        m_Data[atlasBitmapIndex + 2] = shadowColor[2];
                        m_Data[atlasBitmapIndex + 3] = std::max(m_Data[atlasBitmapIndex + 3], shadowAlpha);
                    }
                }
            }
        }

        // Copy glyph bitmap to atlas bitmap (main glyph on top of shadow)
        for (unsigned int glyphY = 0; glyphY < glyphHeight; ++glyphY) {
            unsigned int atlasBitmapRow = (y + glyphY) * bitmapWidth * bitmapChannels;
            for (unsigned int glyphX = 0; glyphX < glyphWidth; ++glyphX) {
                unsigned int atlasBitmapIndex = atlasBitmapRow + x * bitmapChannels + glyphX * bitmapChannels;
                switch (bitmapChannels) {
                case 1:
                    DrawGray(m_Data, glyph, atlasBitmapIndex, glyphX, glyphY);
                    break;
                case 3:
                    DrawRGB(m_Data, glyph, atlasBitmapIndex, glyphX, glyphY);
                    break;
                case 4:
                    DrawRGBA(m_Data, glyph, atlasBitmapIndex, glyphX, glyphY, colors);
                    break;
                default:
                    assert(false && "Unsupported number of channels");
                }
            }
        }
    }

    Atlas::Atlas(const std::string &fontPath, int fontSize, const Charset &charset, RenderMode mode, int padding, bool fit, uint8_t *colors, bool bold, int shadowOffset)
        : m_Font(std::make_shared<Font>(fontPath.c_str())), m_Glyphs(m_Font), m_ShadowOffset(shadowOffset) {
        m_Font->SetSize(Pixels{ fontSize });
        if (colors) {
            m_Color[0] = colors[0];
            m_Color[1] = colors[1];
            m_Color[2] = colors[2];
            m_Color[3] = colors[3];
        }
        InitializeAtlas(charset, mode, padding, fit, bold, shadowOffset);
    }

    Atlas::Atlas(span_const<uint8_t> fontData, int fontSize, const Charset &charset, RenderMode mode, int padding, bool fit, bool bold, int shadowOffset)
        : m_Font(std::make_shared<Font>(fontData)), m_Glyphs(m_Font), m_ShadowOffset(shadowOffset) {
        m_Font->SetSize(Pixels{ fontSize });
        InitializeAtlas(charset, mode, padding, fit, bold, shadowOffset);
    }

    void Atlas::InitializeAtlas(const Charset &charset, RenderMode mode, int padding, bool fit, bool bold, int shadowOffset) {
        const Charset filledCharset = charset.IsFull() ? GetFullCharsetFilled(*m_Font) : charset;

        auto ftGlyphs = LoadAllGlyphs(m_Font->face, filledCharset, mode, bold);
        auto atlasSize = GetAtlasSize(ftGlyphs, padding + shadowOffset, fit);

        auto bitmap = BuildAtlasBitmap(m_Glyphs, ftGlyphs, atlasSize, padding, GetChannels(mode), m_Color[3] ? m_Color : nullptr, shadowOffset);
        this->m_Bitmap = std::move(bitmap);

        InitializeDefaultGlyphIndex();
    }

    void Atlas::InitializeDefaultGlyphIndex() {
        if (m_Glyphs.Empty()) {
            assert(false && "Error: cannot set default glyph in empty atlas");
        }

        m_Glyphs.SetUnknownGlyphIndex(m_Glyphs.Data().begin()->first); // Set first glyph as default
        m_Glyphs.SetUnknownGlyphIndex(0); // Try to set 'undefined character code' as default
        m_Glyphs.SetUnknownGlyph(0xFFFD); // Try to set 'unicode replacement character' as default
    }

    void Atlas::SaveToFile(const vfs::path &path) const {
        const int channels = m_Bitmap.Channels();
        const int width = static_cast<int>(m_Bitmap.Width());
        const int height = static_cast<int>(m_Bitmap.Height());

        if (path.ends_with(".png")) {
            stbi_write_png(path.c_str(), width, height, channels, m_Bitmap.Data().data(), 0);
        } else if (path.ends_with(".bmp")) {
            stbi_write_bmp(path.c_str(), width, height, channels, m_Bitmap.Data().data());
        } else {
            assert(false && "Error: unsupported file format");
        }
    }
}

