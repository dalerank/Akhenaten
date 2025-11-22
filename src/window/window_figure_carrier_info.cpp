#include "window/window_figure_info.h"

#include "figuretype/figure_cartpusher.h"
#include "figuretype/figure_storageyard_cart.h"
#include "figuretype/figure_docker.h"
#include "window/building/figures.h"
#include "graphics/image.h"
#include "graphics/graphics.h"
#include "grid/figure.h"
#include "game/game.h"

struct figure_carrier_info_window : public figure_info_window_t<figure_carrier_info_window> {
    virtual void init(object_info &c) override;
    virtual bool check(object_info &c) override {
        return !!c.figure_get<figure_cartpusher>();
    }
};

figure_carrier_info_window figure_carrier_infow;

void figure_carrier_info_window::init(object_info &c) {
    figure_info_window::init(c);

    figure_cartpusher *f = c.figure_get<figure_cartpusher>();
    
    if (f->action_state() != ACTION_132_DOCKER_IDLING && f->base.resource_id) {
        int resource_img = image_id_resource_icon(f->base.resource_id);
        ui["items"].text_var("@I%u& %u %s %s", resource_img, f->base.resource_amount_full, ui::str(129, 20), ui::str(23, f->base.resource_id));
    }

    ui["debug_stuck"] = "";
    if (f->base.movement_ticks_watchdog > 0 || f->base.direction == DIR_FIGURE_CAN_NOT_REACH) {
        pcstr stuck_reason = "";
        pcstr action_name = "";
        
        // Determine stuck reason
        if (f->base.direction == DIR_FIGURE_REROUTE) {
            stuck_reason = "Rerouting...";
        } else if (f->base.direction == DIR_FIGURE_CAN_NOT_REACH) {
            stuck_reason = "Cannot reach destination";
        } else if (f->base.tile == f->base.previous_tile && f->base.wait_ticks > 0) {
            stuck_reason = "Waiting at building";
        } else if (f->base.tile == f->base.previous_tile) {
            stuck_reason = "Blocked - no movement";
        }
        
        // Determine current action
        switch (f->action_state()) {
            case ACTION_8_RECALCULATE: action_name = "Recalculating route"; break;
            case ACTION_9_CARTPUSHER_DELIVERING_GOODS: action_name = "Delivering goods"; break;
            case ACTION_10_CARTPUSHER_DELIVERING_FOOD: action_name = "Delivering food"; break;
            case ACTION_11_CARTPUSHER_DELIVERING_GOLD: action_name = "Delivering gold"; break;
            case ACTION_20_CARTPUSHER_INITIAL: action_name = "Initial state"; break;
            case ACTION_21_CARTPUSHER_DELIVERING_TO_WAREHOUSE: action_name = "To warehouse"; break;
            case ACTION_22_CARTPUSHER_DELIVERING_TO_GRANARY: action_name = "To granary"; break;
            case ACTION_23_CARTPUSHER_DELIVERING_TO_WORKSHOP: action_name = "To workshop"; break;
            case ACTION_27_CARTPUSHER_RETURNING: action_name = "Returning home"; break;
            case ACTION_51_CARTPUSHER_DELIVERING_RESOURCE: action_name = "Delivering resource"; break;
            case ACTION_53_CARTPUSHER_RETURNING_EMPTY: action_name = "Returning empty"; break;
            case ACTION_54_CARTPUSHER_GETTING_FOOD: action_name = "Getting food"; break;
            case ACTION_57_CARTPUSHER_GETTING_RESOURCE: action_name = "Getting resource"; break;
            default: action_name = "Unknown action"; break;
        }
        
        ui["debug_stuck"].text_var("STUCK: Watchdog=%u | %s | %s", 
            f->base.movement_ticks_watchdog, action_name, stuck_reason);
    }

    if (!f->base.has_home()) {
        return;
    }

    building *source_building = f->home();
    building *target_building = f->destination();

    ui["phrase"] = f->phrase_key();
}
