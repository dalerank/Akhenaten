#pragma once

#include "dynamic_atlas.h"
#include "core/custom_span.hpp"
#include <vector>

/**
 * @file text_shaper.h
 * @brief Text shaping and layout engine using HarfBuzz for complex text rendering
 * 
 * This module provides text shaping capabilities for the dynamic font system. It uses
 * the HarfBuzz library to perform advanced text layout, including:
 * - Complex script shaping (Arabic, Indic, etc.)
 * - Contextual glyph substitution
 * - Glyph positioning and kerning
 * - Support for multiple text encodings (ASCII, UTF-8, UTF-32, Unicode codepoints)
 * 
 * The shaping process converts text strings into positioned glyphs ready for rendering,
 * taking into account font features, ligatures, and language-specific layout rules.
 */

// Forward declarations for HarfBuzz types
struct hb_glyph_info_t;
struct hb_glyph_position_t;
struct hb_buffer_t;
struct hb_font_t;

namespace DynamicFont {
    /**
     * @brief Represents a single glyph with its positioning and advance information
     * 
     * This structure contains all the information needed to render a single glyph,
     * including its position relative to the baseline and how much to advance the
     * cursor for the next glyph. All measurements are in font units.
     */
    struct ShapedGlyph {
        float xOffset;   ///< Horizontal offset from the current pen position (for positioning)
        float yOffset;   ///< Vertical offset from the baseline (for positioning)
        float xAdvance;  ///< Horizontal advance to move the pen for the next glyph
        float yAdvance;  ///< Vertical advance to move the pen for the next glyph (typically 0 for LTR text)

        Glyph info;      ///< Glyph information from the atlas (texture coordinates, metrics, etc.)
    };

    /// @brief A collection of shaped glyphs representing laid-out text
    using ShapedGlyphs = std::vector<ShapedGlyph>;

    /**
     * @brief Metrics for measuring the bounds and advance of shaped text
     * 
     * Provides comprehensive measurements of shaped text, including both the visual bounds
     * (width/height) and the typographic advance. The visual bounds represent the actual
     * ink extent of the text, while the advance represents where the cursor should be
     * positioned after rendering the text.
     */
    struct TextMeasurement {
        float width, height;     ///< Visual dimensions of the text bounding box (measured from top-left corner)
        float xOffset, yOffset;  ///< Offset from baseline origin to the top-left corner of the bounding box
        float xAdvance, yAdvance;///< Cursor advance from baseline origin (includes trailing whitespace/advance)
    };

    /**
     * @brief Text shaping engine that converts text strings into positioned glyphs
     * 
     * TextShaper uses the HarfBuzz text shaping library to perform complex text layout.
     * It handles various text encodings and applies font features, ligatures, kerning,
     * and script-specific shaping rules.
     * 
     * @par Usage Example:
     * @code
     * TextShaper shaper(myAtlas);
     * auto glyphs = shaper.ShapeUtf8("Hello, World!");
     * auto metrics = TextShaper::Measure(glyphs);
     * // Use glyphs for rendering...
     * @endcode
     * 
     * @note This class manages HarfBuzz resources (buffer and font) internally.
     *       It is not copyable but can be moved if needed.
     */
    class TextShaper {
    public:
        /**
         * @brief Constructs a TextShaper with the given font atlas
         * @param atlas Reference to the font atlas containing glyph information
         */
        explicit TextShaper(const Atlas &atlas);
        
        /**
         * @brief Destructor - cleans up HarfBuzz resources
         */
        ~TextShaper();

        /**
         * @brief Shapes ASCII text into positioned glyphs
         * @param text Span of ASCII characters
         * @return Vector of shaped glyphs ready for rendering
         * @note ASCII is a subset of UTF-8, so this delegates to ShapeUtf8
         */
        ShapedGlyphs ShapeAscii(span_const<char> text) {
            // UTF-8 encoding of ASCII characters is the same as ASCII encoding.
            return ShapeUtf8(text);
        }
        
        /**
         * @brief Shapes UTF-8 encoded text into positioned glyphs
         * @param text Span of UTF-8 encoded characters
         * @return Vector of shaped glyphs ready for rendering
         */
        ShapedGlyphs ShapeUtf8(span_const<char> text);
        
        /**
         * @brief Shapes UTF-32 encoded text into positioned glyphs
         * @param text Span of UTF-32 encoded characters (char32_t)
         * @return Vector of shaped glyphs ready for rendering
         */
        ShapedGlyphs ShapeUtf32(span_const<char32_t> text);
        
        /**
         * @brief Shapes Unicode codepoints directly into positioned glyphs
         * @param codepoints Span of Unicode codepoint values
         * @return Vector of shaped glyphs ready for rendering
         */
        ShapedGlyphs ShapeUnicode(span_const<uint32_t> codepoints);

        /**
         * @brief Gets the metrics of the underlying font
         * @return Font metrics including ascender, descender, line height, etc.
         */
        FontMetrics GetFontMetrics() const;

        /**
         * @brief Measures the bounds and advance of shaped text
         * @param glyphs The shaped glyphs to measure
         * @return TextMeasurement containing dimensions, offsets, and advances
         * @note This is a static method as it only operates on shaped glyph data
         */
        static TextMeasurement Measure(const ShapedGlyphs &);

    private:
        /**
         * @brief Retrieves glyph information from the atlas by glyph index
         * @param glyphIndex The glyph index in the font
         * @return Glyph structure with atlas coordinates and metrics
         */
        Glyph GetAtlasGlyph(uint32_t glyphIndex);
        
        /**
         * @brief Extracts shaped glyphs from the HarfBuzz buffer
         * @return Vector of shaped glyphs with positioning information
         */
        ShapedGlyphs GetShapedGlyphs();
        
        /**
         * @brief Converts HarfBuzz glyph info and position to ShapedGlyph
         * @param glyphInfo HarfBuzz glyph information structure
         * @param glyphPos HarfBuzz glyph position structure
         * @return ShapedGlyph with combined information from both sources
         */
        ShapedGlyph GetShapedGlyph(const hb_glyph_info_t &glyphInfo, const hb_glyph_position_t &glyphPos);
        
        /**
         * @brief Resets the HarfBuzz buffer for reuse
         */
        void ResetBuffer();

        Atlas::Glyphs m_Glyphs;                  ///< Cache of glyphs from the atlas
        std::shared_ptr<const Font> m_AtlasFont; ///< Reference to the font from the atlas

        hb_buffer_t *m_Buffer; ///< HarfBuzz text buffer for shaping operations
        hb_font_t *m_Font;     ///< HarfBuzz font object
    };
} // namespace DynamicFont

