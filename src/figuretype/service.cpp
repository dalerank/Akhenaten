#include "service.h"

#include "building/building.h"
#include "building/building_bazaar.h"
#include "figure/combat.h"
#include "figure/image.h"
#include "figure/movement.h"
#include "figure/route.h"
#include "core/profiler.h"
#include "graphics/image.h"
#include "graphics/image_groups.h"
#include "grid/building.h"
#include "grid/road_access.h"
#include "config/config.h"

void figure::scribal_school_teacher_action() {
    switch (action_state) {
    case FIGURE_ACTION_125_ROAMING:
        roam_length++;
        if (roam_length >= max_roam_length) {
            advance_action(FIGURE_ACTION_126_ROAMER_RETURNING);
        }

        break;

    case FIGURE_ACTION_126_ROAMER_RETURNING:
        ; // nothing here
        break;
    
    }
}