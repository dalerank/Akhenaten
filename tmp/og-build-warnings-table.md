# Construction warnings: OG table → ak (T9 / G11)

OG reference: `D:/Work/tutankhamun/src/game/building/construction_warnings.c` (below `cw.c`), called from
`construction_place.c:793 run_warnings()` for every site building (`place_site_building`), from
`construction_place.c:229-235` for house plots, `:853` for the water lift and `:1301` for venues.
OG text = `Pharaoh_Text.eng` group 19, index = warning id − 2 (our key table: `{key, group:19, id: index}`).

OG rules that hold for the whole pass:
- the pass is skipped in the editor; `city_warning_shown` is reset per placement and set by any warning;
  the checks marked **gated** fire only when no warning was shown before them in this placement;
- order: house food, workers, granary, (booth, bandstand, pavilion), fort, military, recruiter, tower, well,
  workshops…, ptolemaic, venue schools, road access;
- venues (booth, bandstand, pavilion) do not go through `run_warnings`: they only get the venue-school check,
  so the single-school checks `cw.c:233-252` are unreachable;
- thresholds (`construction_warning_rules`): min population 300, min workers needed 10, max unemployment 10 %,
  min food produced 96 %, road warning only while fewer than 3 problem messages;
- "imported" = trade status import or import-as-needed; "can import" = an open trading city sells it;
  "could import" (OG `..._potentially`) = a trading city sells it, open or not.

Status before T9: **same** / **differs** / **missing**. The "after" column is the state on `fix/build-warnings-og`: the checks live in
`src/building/construction/construction_warnings.cpp`, the tables in `src/scripts/building/construction_warnings.js`
(`construction_warning_rules`).

## General checks

| # | OG id (our key) | OG text | OG condition | Buildings | ak before T9 | Status | After |
|---|---|---|---|---|---|---|---|
| 1 | 11 `#needs_road_access` | Needs road access | `cw.c:81-141` no adjacent road; storage yard also passes on its 3×3 area; temple complexes never warn; shrines use #2; only while problem messages < 3 | every site building except the exempt list `cw.c:87-118` (statues, well, forts, gatehouses, triumphal arch, crude hut, altar/oracle, pyramid, sphinx, caesareum, library, abu simbel, lighthouse, mausoleum, obelisks, sun temple, royal tombs) | `building_impl.cpp:93` (exempt list = `road_access.cpp:586` flags: house, wall, monument, beautification + granary, dock, ferry, gatehouses); `build_planner.cpp:1131` warns for temple complexes; `building_storage_yard.cpp:998` (3×3 only); `monument_abu_simbel.cpp:693`, `monument_alexandria_library.cpp:1196`, `monument_mausoleum.cpp:1120`, `monument_pharos_lighthouse.cpp:381` warn | differs: exempt list (granary/dock/ferry/statues-as-beautification), temple complex and 4 Ptolemaic monuments warn, no problem-message gate | same: `road_access_exempt`, `road_access_area` (storage yard 3×3); OG drag-tool types (roads, walls, ditches, dike, plaza, gardens, bridges, festival square) are in the exempt list too |
| 2 | 207 `#shrines_near_road_required` | Shrines must be within two spaces of a road | `cw.c:132-138` no adjacent road and no road on the 8-tile cross (±1, ±2 on each axis) `road_access.c:166` | 5 shrines | `shrine_*.js:26` road within square radius 2 (diagonals count) | differs: diagonals | same: cross pattern in C++, `shrines` |
| 3 | 17 `#city_needs_more_workers` | Your city needs more workers | `cw.c:144` **gated**; model laborers > 0; workers needed ≥ 10; not the well | site buildings with laborers, water lift | `building_impl.cpp:97` | differs: not gated, venues warn too | same |
| 4 | 104 `#no_troops_for_defense` | — | `cw.c:173-224` an invasion is running, no legions and no warships | temples, temple complexes, shrines, bandstand, booth, senet house, pavilion, conservatory, dance school, juggler school, police, mansions, architect, tax collector, roadblock, firehouse, courthouse, palaces, zoo | `zoo.js:80` only (and the zoo stops there) | missing (all but the zoo); zoo differs | same: `defense`; zoo no longer stops there |

## House plots

| # | OG id (our key) | OG text | OG condition | ak before T9 | Status | After |
|---|---|---|---|---|---|---|
| 5 | 94 `#people_eating_more_than_produced` | People already eat more food than they produce. | `cw.c:285` **gated**; population ≥ 300; kingdom does not supply grain; food supply % of food consumed last month < 96 | `building_house.cpp:1254` key `#people_eat_more_than_produce` (id 18), population ≥ 200, produced ≤ 95 %; never runs (plots skip `on_place_checks`) | differs (dead, key, thresholds) | same (supply = food produced last month; OG estimates the supply from the producers, T1) |
| 6 | 92 `#too_few_jobs_for_population` | There are already too few jobs… | `cw.c:152` custom map or not the first mission; population ≥ 300; unemployment > 10 % | — | missing | same |
| 7 | 93 `#low_food_levels` | Our food levels are low. | `cw.c:163` population ≥ 300; granary food ≤ half the monthly need | — | missing | same |
| 8 | 62 `#plots_too_far_from_road` | Plots too far from road | `construction_place.c:216,235` no road within radius 2 of a plot | `build_planner.cpp:257` | same | same |

## Venues, granary, military buildings

| # | OG id (our key) | OG text | OG condition | Buildings | ak before T9 | Status | After |
|---|---|---|---|---|---|---|---|
| 9 | 19 `#build_bazaars_to_distribute_food` | Build Bazaars to distribute the food stored here | `cw.c:226` **gated**; no active bazaar | granary | `granary.js:79` | differs: not gated | same: `requires_building` |
| 10 | 44 `#build_juggling_school` | Build a Juggling School to send performers here | `cw.c:233` unreachable (venues skip `run_warnings`) | booth | `booth.js:42`, `bandstand.js:44`, `building_pavilion.cpp:132` (active count) | differs: OG never shows it | not shown |
| 11 | 45 `#build_conservatory` | Build a Conservatory to have musicians here | `cw.c:240` unreachable | bandstand | `bandstand.js:44`, `building_pavilion.cpp:132` | differs | not shown |
| 12 | 46 `#build_dance_school` | Build a Dance School | `cw.c:247` unreachable | pavilion | `building_pavilion.cpp:132` | differs | not shown |
| 13 | 208 `#build_jugglers_school` | Build a Juggler's School to provide performers for this venue | `cw.c:754` no juggler school built (total) | booth, bandstand, pavilion | — | missing | same: `venue_schools` |
| 14 | 209 `#venue_build_conservatory` | Build a Conservatory to supply musicians for this venue | `cw.c:760` no conservatory (total) | bandstand, pavilion | — (no key) | missing | same |
| 15 | 210 `#venue_build_dance_school` | Build a Dance School to train dancers for this venue | `cw.c:763` no dance school (total) | pavilion | — (no key) | missing | same |
| 16 | 42 `#needs_recruiter_to_conscript` | Needs a working Recruiter to conscript soldiers | `cw.c:254` **gated**; no active recruiter | 3 forts | `building_fort.cpp:162` | differs: not gated | same: `requires_building` |
| 17 | 43 `#soldiers_need_supplies_of_weapons` | Some soldiers will need supplies of weapons | `cw.c:263` **gated**; no weapons in storage yards | recruiter | `recruiter.js:28` | differs: not gated | same: `requires_stock` |
| 18 | 41 `#must_be_next_to_wall_for_patrol` | Must be next to a Wall to send out a patrol | `cw.c:270` **gated**; no wall on the ring around the tower | 3 towers | `building_tower.cpp:30` shows `#warning_shipwright_needed` when the tower *is* next to a wall | differs (inverted, wrong key) | same: `wall_patrol_types` |
| 19 | 38 `#needs_access_to_water_lift` | Needs access to a full Water Lift | `cw.c:278` well origin without groundwater — unreachable, `construction_place.c:1050` refuses the well first | well | `well.js:58`, `water_supply.js:46` `#needs_groundwater` after placement — also unreachable (planner refuses, `build_planner.cpp:690`) | same (dead in both) | dead JS removed |
| — | (ak only) `#warning_shipwright_needed` | — | — | gatehouses (`gatehouse_common.js:212`, shown when next to a wall) | not OG | — | removed |

## Raw material of a workshop (`hint_raw_material`)

OG pattern `cw.c:297-305`: no active producer of the input **and** none of the input **and** none of the product in
storage yards → warn "needs X", then one of: build the producer (city can produce the raw) / set up a trade route
(no open trading city sells it) / instruct the Overseer (sold but not imported). One hint at most.

| # | OG ids (our keys) | Building | OG | ak before T9 | Status | After |
|---|---|---|---|---|---|---|
| 20 | 27 `#needs_barley`, 34 `#build_barley_farm`, 31, 32 | brewery | `cw.c:307` | `workshop.js:51` no beer-stock check; route only if a closed city sells it | differs | same: `raw_materials` |
| 21 | 28 `#building_needs_flax`, 35 `#build_flax_farm`, 31, 32 | weaver | `cw.c:312` | `weaver.js:44` all three hints at once, no linen-stock check | differs | same |
| 22 | 30 `#needs_gems`, 37 `#build_gem_mine`, 31, 32 | jeweler | `cw.c:317` | `workshop.js:143` all hints at once, no product check | differs | same |
| 23 | 29 `#building_needs_clay`, 36 `#build_clay_pit`, 31, 32 | potter | `cw.c:322` | `pottery.js:58` route only if a closed city sells it | differs | same |
| 24 | 80 `#building_needs_reeds`, 81 `#build_reed_gatherer`, 31, 32 | papyrus maker | `cw.c:327` | `papyrus_maker.js:46` all hints at once, no papyrus-stock check | differs | same |
| 25 | 261 `#building_needs_henna`, 262 `#build_henna_farm`, 264 `#import_henna_trade_route`, 263 `#import_henna_overseer` | paint maker | `cw.c:332` | `paint_workshop.js:48` | same | same (moved to the table) |
| 26 | 82 `#building_needs_straw`, 83 `#build_grain_farm`, 31, 32 (active grain farm or straw in yards) | cattle ranch | `cw.c:342` | `cattle_ranch.js:60` route only if a closed city sells straw | differs | same |
| 27 | 143 `#building_needs_wood`, 144 `#build_wood_cutter`, 31, 32 | carpenters guild | `cw.c:560` | — | missing | same |
| 28 | 164 `#monument_needs_sandstone`, 165 `#build_sandstone_quarry`, 31, 32 | sun temple, mausoleum | `cw.c:711` | — | missing | same |
| 29 | 157 `#monument_needs_plain_stone`, 151 `#build_stone_quarry`, 31, 32 | stepped pyramid style | `cw.c:676,701` | — | missing | same (small/medium/large stepped pyramid + complexes) |
| 30 | 163 `#monument_needs_bricks`, 160 `#build_brickworks`, 31, 32 | mastaba style | `cw.c:676,704` | `mastaba.js:381` only `#needs_groundwater` (ak extra) | missing | same (3 mastabas; groundwater hint kept) |
| 31 | 242 `#monument_needs_marble`, 31, 32 (yards only, no producer) | lighthouse, caesareum, library of Alexandria | `cw.c:743` | `caesareum.js:74` only | missing (lighthouse, library) | same |
| 32 | 241 `#monument_needs_copper`, 31, 32 | library of Alexandria | `cw.c:722,748` | — | missing | same |
| 33 | 248 `#monument_needs_granite`, 31, 32 | caesareum | `cw.c:722,750` | `caesareum.js:85` | same | same (moved to the table) |
| — | 26 `#building_needs_copper_ore`, 33 `#build_copper_mine` | weaponsmith | not in OG (`weaponsmith.js:44`, ak extra, all hints at once) | — | ak only, kept |
| — | `#needs_papyrus` + papyrus hints | industry office (Cleopatra admin) | not in OG (`industry_office.js:73`) | — | ak only, kept |
| — | `#warning_shipwright_needed` | fishing / warship wharf | not in OG (`fishing_wharf.js:45`, `warship_wharf.js:68`) | — | ak only, kept |

## Two inputs (`cw.c:367-438`, `631-674`)

OG pattern: both inputs produced or both in stock (or, for workshops, the product in stock) → nothing; first input
missing → "needs A and B" or "needs A" with the hints of the missing inputs; only the second missing → "needs B".
With both missing the hints use the resource-specific texts (lamps swap the oil and pottery texts).

| # | OG ids (our keys) | Building | OG | ak before T9 | Status | After |
|---|---|---|---|---|---|---|
| 34 | 145 `#building_needs_clay_and_straw`, 29, 82, 36, 83, 146/147 clay, 148/149 straw, 31, 32 | brickworks | `cw.c:367` | — | missing | same: `two_inputs` |
| 35 | 253 `#building_needs_oil_and_pottery`, 263 `#building_needs_oil`, 264 `#building_needs_pottery`, 254 `#build_potter`, 255-258, 31, 32 | lamp maker | `cw.c:403` | `lamp_workshop.js:82` | same | same (moved to the table) |
| 36 | 150 `#monument_needs_stone_and_limestone`, 151-157 | bent and true pyramids | `cw.c:631,693` | — | missing | same |
| 37 | 159 `#monument_needs_bricks_and_limestone`, 158, 160-163, 152-156 | mud-brick pyramids | `cw.c:631,697` | — | missing | same |

## Finished goods a service building consumes (`cw.c:447-558`)

OG pattern: some product in yards → nothing; else "needs X"; any raw producer built → stop; then if the raw can be
had (our city sells it or a trading city could) and no producer of X is built: "build the maker" when X cannot be
imported at all, else the "build the maker or import" texts; if the raw could be imported and a maker exists: the raw
import texts; else the generic import texts for X when it could be imported.

| # | OG ids (our keys) | Building | OG | ak before T9 | Status | After |
|---|---|---|---|---|---|---|
| 38 | 137 `#building_needs_beer`, 138 `#build_brewery`, 191 `#build_brewery_or_import_beer`, 192 `#build_brewery_or_import_beer_route`, 168/169 barley | senet house | `cw.c:447` | `senet_house.js:53` all hints at once, keys `#need_beer`/`#need_brewery`/`#build_senet_master` (ak only) | differs | same: `finished_goods`; ak-only `#build_senet_master`, `#need_beer`, `#need_brewery` removed |
| 39 | 139 `#needs_papyrus`, 140 `#build_papyrus_maker`, 193 `#build_papyrus_maker_or_import`, 194 `#build_papyrus_maker_or_import_route`, 170/171 reeds (only "import", not "import as needed", counts) | scribal school, library | `cw.c:502` | `scribal_school.js:48` all hints at once; library — | differs / missing | same |
| 40 | 141 `#building_needs_linen`, 142 `#build_weaver`, 195 `#build_weaver_or_import_linen`, 196 `#build_weaver_or_import_linen_route`, 174/175 flax | mortuary | `cw.c:534` | `mortuary.js:86` all hints at once | differs | same |
| 41 | 270 `#building_needs_clay_and_paint`, 36, 146/147, 269 `#build_paint_maker`, 267/268, 263/264 | artisans guild | `cw.c:576` | `config.js:211` | same | same (JS) |
| 42 | 237 `#building_needs_game_meat`, 238 `#build_hunting_lodge`, 239 `#build_hunting_lodge_or_import` (tests meat, not game meat), 240 `#game_meat_import_trade_route`, then straw 82/83/148/149 | zoo | `cw.c:473` | `zoo.js:74` stops after the no-troops warning; stocks counted with granaries | differs | same (JS; troops check moved to #4) |

## Localization keys of group 19

| Lang index (OG id) | Text | Our key before T9 | After |
|---|---|---|---|
| 186 (188) | Fort: Infantry … cannot produce or import weapons | `#mausoleum_needs_sandstone` | `#building_removed_fort_infantry_weapons` |
| 187 (189) | Fort: Charioteers … cannot produce or import chariots | `#build_brewery_or_import_beer` | `#building_removed_fort_charioteers_chariots` |
| 188 (190) | You need 240 blocks of sandstone to build a mausoleum | `#build_papyrus_maker_or_import` | `#mausoleum_needs_sandstone` |
| 189 (191) | Build a Brewery, or order that beer be imported. | `#build_weaver_or_import_linen` | `#build_brewery_or_import_beer` |
| 190 (192) | Build a Brewery or set up a trade route to import beer. | `#tax_collector_robbed` | `#build_brewery_or_import_beer_route` |
| 191 (193) | Build a Papyrus Maker, or order that it be imported. | `#courthouse_robbed` | `#build_papyrus_maker_or_import` |
| 192 (194) | Build a Papyrus Maker, or open a trade route to import papyrus. | `#mansion_destroyed` | `#build_papyrus_maker_or_import_route` |
| 193 (195) | Build a Weaver, or order that linen be imported. | — | `#build_weaver_or_import_linen` |
| 194 (196) | Build a Weaver or set up a trade route to import linen. | — | `#build_weaver_or_import_linen_route` |
| 195 (197) | Thieves just robbed a Tax Collector's office! | — | `#tax_collector_robbed` |
| 196 (198) | Thieves just robbed a Courthouse! | — | `#courthouse_robbed` |
| 197 (199) | Your Mansion was destroyed and plundered! | — | `#mansion_destroyed` |
| 207 (209) | Build a Conservatory to supply musicians for this venue | — | `#venue_build_conservatory` |
| 208 (210) | Build a Dance School to train dancers for this venue | — | `#venue_build_dance_school` |

So before T9 the robber warnings (`figure_robber.cpp:164,167`) showed brewery/papyrus texts and the mausoleum
sandstone refusal (`monument_mausoleum.cpp:1030`) showed a fort text.

## Helper semantics

| OG | ak | Note |
|---|---|---|
| `empire_can_produce_resource` raw → our city sells it; products → chain (`empire.c:183`) | `city_t::can_produce_resource` = our city sells it | the OG product chain only matters for pottery (lamps); pottery `can_produce` here = our city sells pottery — kept, see "Remaining" |
| `empire_can_import_resource` open trading city sells it **and** route limit > 0 | `empire_t::can_import_resource(r, true)` | no route-limit test in ak — kept |
| `storage_stored` = storage yards with road access | `city_resources_t::yards_stored` | same idea |

## Counts (before T9)

42 OG rows: same 6 (#8, #19, #25, #33, #35, #41), differs 21, missing 15.
After T9: 42 of 42 rows follow the OG condition and texts (#10-#12 are correctly never shown, #19 stays dead);
see "Remaining" for what is still approximate. Covered by integral tests 540 (road access, statue exemption, booth,
pavilion, granary, recruiter, house plots) and 541 (weaver, product stock, carpenters, brickworks, mortuary, senet,
library), plus the existing 186 (shrines), 258 (pottery), 285 (cattle), 357 (lamps), 388 (paint), 421 (artisans).

## Remaining

- #5 food supply uses food produced last month; OG estimates the supply from working producers (`food_supply.c:36`),
  which is task T1 (`city/city_food_supply.cpp`). Switch once T1 lands.
- `can_produce` of products (pottery for the lamp maker, bricks for mastabas and mud-brick pyramids) is "our city
  sells it", not the OG chain `empire.c:183`.
- #6 "first mission" = normal campaign mode with `campaign_scenario_id == 0` (OG `mission_id != 0`).
- #1 problem-message gate uses `city_message_problem_area_count()`, which ak refreshes when the problem button is used.
- `can_import` ignores the route limit.
- ak-only hints kept: weaponsmith copper, industry office papyrus, wharf shipwright, mastaba / stepped pyramid
  groundwater, brewery water (gameplay option).
- The editor never runs these checks (it places through `construction_place`, not `construction_finalize`), so the
  OG editor guard needs no counterpart.
- ak keeps the warning list newest-first and drops the oldest when full; OG drops new warnings when its slots are full.
