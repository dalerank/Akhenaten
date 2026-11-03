#include "figure_enemy_chariot.h"

#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "js/js_game.h"

std::array<vec2i, 8> ANK_VARIABLE(enemy_chariot_cart_offsets);

REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_assyrian_chariot)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_hyksos_chariot)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_egyptian_chariot)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_canaanite_chariot)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_kushite_chariot)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_hittite_chariot)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_persian_chariot)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_libian_chariot)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_nubian_chariot)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_phoenician_chariot)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_roman_chariot)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_seapeople_chariot)
REPLICATE_STATIC_PARAMS_FROM_CONFIG(figure_kingdome_mounted)

void figure_enemy_chariot::on_create() {
    figure_enemy::on_create();
    // OG pulls_cart: cart is drawn via has_cart() / draw_cart_sprite.
    base.use_cart = true;
}

void figure_enemy_chariot::update_chariot_cart() {
    // OG enemy_set_cart: CHARIOT_CART + frame*8 + dir, enemy_cart_offsets[dir].
    int dir = base.figure_image_normalize_direction(
        base.direction < 8 ? base.direction : base.previous_tile_direction);
    if (base.in_attack()) {
        dir = base.figure_image_normalize_direction(base.attack_direction);
    }

    const int cart_base = image_id_from_group(GROUP_FIGURE_CHARIOT_CART);
    if (cart_base < 0) {
        base.cart_image_id = 0;
        return;
    }

    base.cart_image_id = (uint16_t)(cart_base + base.animctx.frame * 8 + dir);
    if (dir >= 0 && dir < (int)enemy_chariot_cart_offsets.size()) {
        base.cart_offset = enemy_chariot_cart_offsets[dir];
    }
}

void figure_enemy_chariot::update_animation() {
    figure_enemy_fast_sword::update_animation();
    update_chariot_cart();
}
