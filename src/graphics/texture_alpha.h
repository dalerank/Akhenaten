#pragma once

#include <SDL.h>

// Pak, font and generated textures hold alpha that the painter treats as premultiplied.
// Textures decoded straight from PNG keep straight alpha and must blend as SDL_BLENDMODE_BLEND.
namespace texture_alpha {

    inline void* straight_tag() {
        static char tag;
        return &tag;
    }

    inline void mark_straight(SDL_Texture* texture) {
        if (texture) {
            SDL_SetTextureUserData(texture, straight_tag());
        }
    }

    inline bool is_straight(SDL_Texture* texture) {
        return texture && SDL_GetTextureUserData(texture) == straight_tag();
    }

} // namespace texture_alpha
