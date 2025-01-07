#include "figuretype/festival_guy.h"

#include "core/random.h"
#include "building/count.h"
#include "city/buildings.h"

figures::model_t<figure_festival_guy> festival_guy_m;

void figure_festival_guy::on_create() {
}

void figure_festival_guy::figure_action() {
    building* b = home();
    switch (b->type) {
    default:
        assert(false);
        break;

    case BUILDING_TEMPLE_OSIRIS:
    case BUILDING_TEMPLE_COMPLEX_OSIRIS:
        image_set_animation("priest_osiris");
        break;
    case BUILDING_TEMPLE_RA:
    case BUILDING_TEMPLE_COMPLEX_RA:
        image_set_animation("priest_ra");
        break;
    case BUILDING_TEMPLE_PTAH:
    case BUILDING_TEMPLE_COMPLEX_PTAH:
        image_set_animation("priest_ptah");
        break;
    case BUILDING_TEMPLE_SETH:
    case BUILDING_TEMPLE_COMPLEX_SETH:
        image_set_animation("priest_seth");
        break;
    case BUILDING_TEMPLE_BAST:
    case BUILDING_TEMPLE_COMPLEX_BAST:
        image_set_animation("priest_bast");
        break;
    case BUILDING_JUGGLER_SCHOOL:
        image_set_animation("juggler");
        break;
    case BUILDING_CONSERVATORY:
        image_set_animation("musician");
        break;
    case BUILDING_DANCE_SCHOOL:
        image_set_animation("dancer");
        break;
    }

    switch (action_state()) {
    case 9: // is "dancing" on tile
        base.festival_remaining_dances--;
        advance_action(10);
        break;
    case 10: // goes to random spot on the square

        // still going to the square center, first
        if (base.terrain_usage == TERRAIN_USAGE_ROADS) {
            if (do_goto(base.destination_tile, TERRAIN_USAGE_ROADS, 10))
                base.terrain_usage = TERRAIN_USAGE_ANY;
        } else {
            //                use_cross_country = true; // todo?
            if (base.routing_path_id) {
                do_goto(base.destination_tile, TERRAIN_USAGE_ANY, 11);
            } else {
                bool has_square = building_count_total(BUILDING_FESTIVAL_SQUARE);
                if (base.festival_remaining_dances == 0 || !has_square) {
                    return poof();
                }

                // choose a random tile on the festival square
                tile2i festival = city_building_get_festival_square_position();
                int rand_x, rand_y;
                int rand_seed = random_short();
                do {
                    int random_tile = rand_seed % 25;
                    rand_x = festival.x() + random_tile % 5;
                    rand_y = festival.y() + random_tile / 5;
                    rand_seed++;
                } while (rand_x == tilex() && rand_y == tiley());

                do_goto(map_point(rand_x, rand_y), TERRAIN_USAGE_ANY, 11);
            }
        }
        break;
    case 11: // reached a random spot on the square, now what?
        advance_action(9);
        break;
    }
}
