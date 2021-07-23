#include "animation.h"

#include "building/industry.h"
#include "building/model.h"
#include "core/calc.h"
#include "core/image.h"
#include "game/animation.h"
#include "map/sprite.h"
#include "core/game_environment.h"

int building_animation_offset(building *b, int image_id, int grid_offset, int max_frames) {
    if (building_is_workshop(b->type) && (b->loads_stored <= 0 || b->num_workers <= 0))
        return 0;

    switch (b->type) {
        case BUILDING_WAREHOUSE_SPACE:
            return 0;
            break;
        case BUILDING_FOUNTAIN:
            if (b->num_workers <= 0 || !b->has_water_access)
                return 0;
            break;
        case BUILDING_RESERVOIR:
            if (GAME_ENV == ENGINE_ENV_PHARAOH) {
                if (b->num_workers <= 0) {
                    return 0;
                }
                else if (!b->has_water_access) {
                    return 0;
                }
            }
            break;
//        case BUILDING_PREFECTURE: // police house
//        case BUILDING_ENGINEERS_POST:
//        case BUILDING_FIREHOUSE:
//        case BUILDING_WATER_SUPPLY:
//        case BUILDING_PHYSICIAN:
//        case BUILDING_APOTHECARY:
//        case BUILDING_DENTIST:
//        case BUILDING_MORTUARY:
//        case BUILDING_MARKET:
//        case BUILDING_WAREHOUSE: // b->num_workers < model_get_building(b->type)->laborers
//        case BUILDING_GRANARY: // b->num_workers < model_get_building(b->type)->laborers
//        case BUILDING_IRON_MINE:
//        case BUILDING_CLAY_PIT:
//        case BUILDING_TIMBER_YARD:
//        case BUILDING_THEATER:
//        case BUILDING_CHARIOT_MAKER:
//        case BUILDING_HIPPODROME:
//        case BUILDING_TEMPLE_OSIRIS:
//        case BUILDING_TEMPLE_RA:
//        case BUILDING_TEMPLE_SETH:
//        case BUILDING_TEMPLE_PTAH:
//        case BUILDING_TEMPLE_BAST:
//        case BUILDING_VILLAGE_PALACE:
//        case BUILDING_TOWN_PALACE:
//        case BUILDING_CITY_PALACE:
//            if (b->num_workers <= 0)
//                return 0;
//            break;
        case BUILDING_MARBLE_QUARRY:
        case BUILDING_GLADIATOR_SCHOOL:
            if (b->num_workers <= 0) {
                if (GAME_ENV == ENGINE_ENV_PHARAOH)
                    return 0;
                map_sprite_animation_set(grid_offset, 1);
                return 1;
            } break;
        case BUILDING_DOCK:
            if (b->data.dock.num_ships <= 0) {
                map_sprite_animation_set(grid_offset, 1);
                return 1;
            } break;
        default:
            if (b->main()->num_workers <= 0)
                return 0;
            break;
    }

    const image *img = image_get(image_id);
    if (!max_frames)
        max_frames = img->num_animation_sprites;
    if (!game_animation_should_advance(img->animation_speed_id))
        return map_sprite_animation_at(grid_offset) & 0x7f;

    // advance animation
    int new_sprite = 0;
    int is_reverse = 0;
    if (b->type == BUILDING_WINE_WORKSHOP) {
        // exception for wine...
        int pct_done = calc_percentage(b->data.industry.progress, 400);
        if (pct_done <= 0)
            new_sprite = 0;
        else if (pct_done < 4)
            new_sprite = 1;
        else if (pct_done < 8)
            new_sprite = 2;
        else if (pct_done < 12)
            new_sprite = 3;
        else if (pct_done < 96) {
            if (map_sprite_animation_at(grid_offset) < 4)
                new_sprite = 4;
            else {
                new_sprite = map_sprite_animation_at(grid_offset) + 1;
                if (new_sprite > 8)
                    new_sprite = 4;
            }
        } else {
            // close to done
            if (map_sprite_animation_at(grid_offset) < 9)
                new_sprite = 9;
            else {
                new_sprite = map_sprite_animation_at(grid_offset) + 1;
                if (new_sprite > 12)
                    new_sprite = 12;
            }
        }
    } else if (img->animation_can_reverse) {
        if (map_sprite_animation_at(grid_offset) & 0x80)
            is_reverse = 1;

        int current_sprite = map_sprite_animation_at(grid_offset) & 0x7f;
        if (is_reverse) {
            new_sprite = current_sprite - 1;
            if (new_sprite < 1) {
                new_sprite = 1;
                is_reverse = 0;
            }
        } else {
            new_sprite = current_sprite + 1;
            if (new_sprite > max_frames) {
                new_sprite = max_frames;
                is_reverse = 1;
            }
        }
    } else {
        // Absolutely normal case
        new_sprite = map_sprite_animation_at(grid_offset) + 1;
        if (new_sprite > max_frames)
            new_sprite = 1;
    }

    map_sprite_animation_set(grid_offset, is_reverse ? new_sprite | 0x80 : new_sprite);
    return new_sprite;
}
