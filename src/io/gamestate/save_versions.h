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
//  176 akhenaten: wall_material_grid (mud/brick terrain walls)
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
constexpr uint32_t latest_save_version = 189;
