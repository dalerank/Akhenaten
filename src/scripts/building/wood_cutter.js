log_info("akhenaten: building_wood_cutter started")

[es=building]
building_wood_cutter {
  type: BUILDING_WOOD_CUTTERS
  animations {
    preview { pos : [0, 0], pack:PACK_GENERAL, id:65 }
    base { pos : [0, 0], pack:PACK_GENERAL, id:65 }
    work { pos : [30, -17], pack:PACK_GENERAL, id:65, offset:1, max_frames:12, duration:4 }
  }
  overlay_anims {
    wood {
      pos : [65, 3]
      pack:PACK_GENERAL
      id:202
      resource : RESOURCE_TIMBER
      default_active : true
    }
  }
  output {
    resource : RESOURCE_TIMBER
  }
  flags {
    is_harvester: true
    is_industry: true
    work_anim: true
  }
  building_size : 2
  meta { text_id:120, help_link:"message_building_woodcutter_and_reed_gatherer" }
  info_sound : "Wavs/lumber.wav"
  sound_channel : SOUND_CHANNEL_CITY_NONE
  labor_category : LABOR_CATEGORY_INDUSTRY_COMMERCE
  min_houses_coverage : 100
  max_storage_amount : 200
  max_gatherers : 1
  cost [ 10, 20, 40, 80, 140 ]
  desirability { value[-4], step[1], step_size[1], range[3] }
  laborers[8], fire_risk[4], damage_risk[3]
}

function wood_cutter_has_lumberjack_capacity(b) {
    var max_gatherers = dcy_get(building_wood_cutter.max_gatherers)
    var gatherers = b.get_figures_number(FIGURE_LUMBERJACK)
    var carry = figure_lumberjack.max_amount
    var max_loads = 500 / carry
    return gatherers < max_gatherers
        && gatherers + Math.floor(b.stored_resource(RESOURCE_TIMBER) / carry) < (max_loads - gatherers)
}

function wood_cutter_can_spawn_lumberjack(b) {
    return b.citizen_found_terrain(TERRAIN_TREE) && wood_cutter_has_lumberjack_capacity(b)
}

[es=(building_wood_cutter, spawn_figure)]
function building_wood_cutter_spawn_figure(ev) {
    var b = city.get_building(ev.bid)
    b.check_labor_problem()
    if (b.is_enemies_nearby()) {
        return
    }

    if (b.has_road_access) {
        b.common_spawn_labor_seeker(building_wood_cutter.min_houses_coverage)
        var spawn_delay = b.figure_spawn_timer()
        if (spawn_delay == -1) {
            return
        }

        b.figure_spawn_delay += 1
        if (b.figure_spawn_delay > spawn_delay) {
            b.figure_spawn_delay = 0
            if (wood_cutter_can_spawn_lumberjack(b)) {
                var fid = b.create_figure_generic(FIGURE_LUMBERJACK, ACTION_1_LUMBERJACK_RECALCULATE, BUILDING_SLOT_SERVICE)
                if (fid) {
                    city.get_figure(fid).wait_ticks = fid % 30
                }
            }
        }
    }

    b.common_spawn_goods_output_cartpusher()
}

[es=(building_wood_cutter, update_animation)]
function building_wood_cutter_on_update_animation(ev) {
    var b = city.get_building(ev.bid)
    if (!b.play_animation) {
        return
    }
    if (b.stored_resource(RESOURCE_TIMBER) >= building_wood_cutter.max_storage_amount) {
        b.play_animation = false
    }
}
