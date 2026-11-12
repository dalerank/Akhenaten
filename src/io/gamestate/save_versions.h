#pragma once

#include <cstdint>

// file versions found so far:
//  144 (Bridges.map only)
//  146 (NAFTA.map and Warfare.map only)
//  147 (most of the older campaign scenarios)
//  149 (later campaign scenarios and maps)
//  150 (later campaign scenarios and maps)
//  160 (post-Cleopatra campaign scenarios, patched Bubastis scenario)
//  161 akhenaten: save foods in houses
//  162 akhenaten: save g_terrain_floodplain_growth
//  163 akhenaten: save bazaar_days in house
//  164 akhenaten: save water_supply in house
//  165 akhenaten: save house health option
//  167 akhenaten: save sandstone terrain values
//  168 akhenaten: save stone terrain values
//  169 akhenaten: save golden terrain values
//  170 akhenaten: save enemy armies props
//  171 akhenaten: bridge_part / bridge_type grids
//  172 akhenaten: B2 invasion event pending (deprecated stub)
//  173 akhenaten: invasion_runtime — bind resolve + history ring
//  174 akhenaten: house zookeeper coverage (Cleopatra Zoo)
//  175 akhenaten: storage Empty All order snapshot
//  176 akhenaten: wall_material_grid (mud/brick/strong terrain walls)
//  177 akhenaten: invasion auto-resolve pending queue
//  178 akhenaten: (reserved / in-tree)
//  179 akhenaten: monument funeral_done (pyramid append; mastaba reclaims skip byte)
//  180 akhenaten: monument preexisting (pyramid append; mastaba/sphinx/obelisk reclaim skip)
//  181 akhenaten: house frog_infest_days (Cleopatra Plague of Frogs / CF1)
//  182 akhenaten: pyramid complex causeway_length / causeway_dir
//  183 akhenaten: campaign_carry_troops (Cleopatra fort carry CO2)
//  184 akhenaten: campaign_carry_monuments (Cleopatra monument carry CO1)
//  185 akhenaten: (reserved / in-tree)
//  186 akhenaten: labor STORAGE category priority (enhanced labor split LC4)
//  188 akhenaten: recorded cart trails (pool + last-4 building rings)
//  189 akhenaten: sectioned .svx container (chunk layout unchanged)
//  190 akhenaten: bazaar second_trader_id (OG fancy second market trader)
//  191 akhenaten: mastaba OG block-engine fields on monument runtime (og_main/og_part)
//  192 akhenaten: pyramid OG block-engine fields on monument runtime (og_main/og_part)
//  193 akhenaten: sphinx work spots (work + figure) on each sphinx part runtime
//  194 akhenaten: bookmarks in the OG layout (int32 grid offset + reserved int32)
//  195 akhenaten: shipyard saves the ship under repair (repair_fid)
//  196 akhenaten: compact pyramid/mastaba runtime (resources on the main part only, no ramp draw cache)
//  197 akhenaten: (unused)
//  198 akhenaten: "mods" chunk — ids + versions of the mods enabled when the game was saved
//  199 akhenaten: city_data chunk in the OG city_player layout
//  200 akhenaten: cloud positions in their own "clouds" chunk; building_list_small bytes 0..63 written as zero
constexpr uint32_t latest_save_version = 200;
