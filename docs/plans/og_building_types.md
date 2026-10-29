# Pharaoh OG building types (0…236)

Recovered from `akhenatren-rm`:
- `BUILDING_TYPE_COUNT` = `0xED` (**237** slots, ids 0…236) — `src/game/building/building_state.c`
- `building_properties` @ `0x005D06DC` — size / fire_proof / image_group / labor
- Display names: Pharaoh_Text **group 28** (`localization_base_en.js`)
- Internal names: Akhenaten `building_type.h` where numeric IDs match OG
- Akhenaten matches OG numeric IDs for small/large obelisk (`0xCF`/`0xD0`) and sun temple
  (`0xD5`). See `akhenatren-rm/docs/drafts/monuments.md`.

**Notes**
- All five pyramid styles (bent / mudbrick / stepped / true / mastaba) share type `0xB7` in OG;
  Akhenaten keeps a remake split (`241+`) — intentional divergence.
- Types 0x91–0xA0 are C3 leftovers (menu force-off); Pharaoh shrines are 0x8C–0x90,
  big temples 0x97–0x9B.
- Group 28 leaves obelisks / sun temple as "unused …"; names filled from monument code.
- Remake-only: types ≥ 237 (meadow farms, part runtime-ids, DIKE, FOOD_MILL, …) plus pyramid split.

| id | hex | size | internal name | display (g28) |
|---:|:---:|----:|---|---|
| 0 | 0x00 | 0 | `BUILDING_NONE` | Nowhere |
| 1 | 0x01 | 0 | `BUILDING_RESERVED_1` | Undo |
| 2 | 0x02 | 0 | `BUILDING_MENU_FARMS` | Farm |
| 3 | 0x03 | 0 | `BUILDING_MENU_RAW_MATERIALS` | Raw Materials |
| 4 | 0x04 | 0 | `BUILDING_MENU_CONSTURCTION_GUILDS` | Construction Guilds |
| 5 | 0x05 | 1 | `BUILDING_ROAD` | Road |
| 6 | 0x06 | 1 | `BUILDING_MUD_WALL` | Mud Wall |
| 7 | 0x07 | 2 | `BUILDING_WATER_LIFT` | Water Lift |
| 8 | 0x08 | 1 | `BUILDING_IRRIGATION_DITCH` | Irrigation Ditch |
| 9 | 0x09 | 0 | `BUILDING_CLEAR_LAND` | Dig |
| 10 | 0x0A | 1 | `BUILDING_HOUSE_CRUDE_HUT` | House1 |
| 11 | 0x0B | 1 | `BUILDING_HOUSE_STURDY_HUT` | House2 |
| 12 | 0x0C | 1 | `BUILDING_HOUSE_MEAGER_SHANTY` | House3 |
| 13 | 0x0D | 1 | `BUILDING_HOUSE_COMMON_SHANTY` | House4 |
| 14 | 0x0E | 1 | `BUILDING_HOUSE_ROUGH_COTTAGE` | House5 |
| 15 | 0x0F | 1 | `BUILDING_HOUSE_ORDINARY_COTTAGE` | House6 |
| 16 | 0x10 | 1 | `BUILDING_HOUSE_MODEST_HOMESTEAD` | House7 |
| 17 | 0x11 | 1 | `BUILDING_HOUSE_SPACIOUS_HOMESTEAD` | House8 |
| 18 | 0x12 | 1 | `BUILDING_HOUSE_MODEST_APARTMENT` | House9 |
| 19 | 0x13 | 1 | `BUILDING_HOUSE_SPACIOUS_APARTMENT` | House10 |
| 20 | 0x14 | 2 | `BUILDING_HOUSE_COMMON_RESIDENCE` | House11 |
| 21 | 0x15 | 2 | `BUILDING_HOUSE_SPACIOUS_RESIDENCE` | House12 |
| 22 | 0x16 | 2 | `BUILDING_HOUSE_ELEGANT_RESIDENCE` | House13 |
| 23 | 0x17 | 2 | `BUILDING_HOUSE_FANCY_RESIDENCE` | House14 |
| 24 | 0x18 | 3 | `BUILDING_HOUSE_COMMON_MANOR` | House15 |
| 25 | 0x19 | 3 | `BUILDING_HOUSE_SPACIOUS_MANOR` | House16 |
| 26 | 0x1A | 3 | `BUILDING_HOUSE_ELEGANT_MANOR` | House17 |
| 27 | 0x1B | 3 | `BUILDING_HOUSE_STATELY_MANOR` | House18 |
| 28 | 0x1C | 4 | `BUILDING_HOUSE_MODEST_ESTATE` | House19 |
| 29 | 0x1D | 4 | `BUILDING_HOUSE_PALATIAL_ESTATE` | House20 |
| 30 | 0x1E | 1 | `BUILDING_BANDSTAND` | Bandstand |
| 31 | 0x1F | 1 | `BUILDING_BOOTH` | Booth |
| 32 | 0x20 | 4 | `BUILDING_SENET_HOUSE` | Senet House |
| 33 | 0x21 | 2 | `BUILDING_PAVILLION` | Pavilion |
| 34 | 0x22 | 3 | `BUILDING_CONSERVATORY` | Conservatory |
| 35 | 0x23 | 4 | `BUILDING_DANCE_SCHOOL` | Dance School |
| 36 | 0x24 | 2 | `BUILDING_JUGGLER_SCHOOL` | Juggler School |
| 37 | 0x25 | 3 | `BUILDING_BULLFIGHT_SCHOOL` | Senet Master |
| 38 | 0x26 | 1 | `BUILDING_PLAZA` | Plaza |
| 39 | 0x27 | 1 | `BUILDING_GARDENS` | Gardens |
| 40 | 0x28 | 3 | `BUILDING_FORT_CHARIOTEERS` | Charioteers |
| 41 | 0x29 | 1 | `BUILDING_SMALL_STATUE` | Small Statue |
| 42 | 0x2A | 2 | `BUILDING_MEDIUM_STATUE` | Medium Statue |
| 43 | 0x2B | 3 | `BUILDING_LARGE_STATUE` | Large Statue |
| 44 | 0x2C | 3 | `BUILDING_FORT_ARCHERS` | Archers |
| 45 | 0x2D | 3 | `BUILDING_FORT_INFANTRY` | Infantry |
| 46 | 0x2E | 1 | `BUILDING_APOTHECARY` | Apothecary |
| 47 | 0x2F | 2 | `BUILDING_MORTUARY` | Mortuary |
| 48 | 0x30 | 0 | `BUILDING_MENU_MONUMENTS` | Monuments |
| 49 | 0x31 | 1 | `BUILDING_DENTIST` | Dentist |
| 50 | 0x32 | 3 | `BUILDING_DISTRIBUTION_CENTER_UNUSED` | Storage Yard |
| 51 | 0x33 | 2 | `BUILDING_SCRIBAL_SCHOOL` | Scribal School |
| 52 | 0x34 | 0 | `BUILDING_MENU_WATER_CROSSINGS` | Water Crossings |
| 53 | 0x35 | 3 | `BUILDING_LIBRARY` | Library |
| 54 | 0x36 | 4 | `BUILDING_FORT_GROUND` | Fort |
| 55 | 0x37 | 1 | `BUILDING_POLICE_STATION` | Police Station |
| 56 | 0x38 | 3 | `BUILDING_RESERVED_TRIUMPHAL_ARCH_56` | unused 921 |
| 57 | 0x39 | 3 | `BUILDING_MENU_FORTS` | Fort |
| 58 | 0x3A | 2 | `BUILDING_MUD_GATEHOUSE` | Mud Gatehouse |
| 59 | 0x3B | 2 | `BUILDING_MUD_TOWER` | Mud Tower |
| 60 | 0x3C | 3 | `BUILDING_TEMPLE_OSIRIS` | Temple to Osiris |
| 61 | 0x3D | 3 | `BUILDING_TEMPLE_RA` | Temple to Ra |
| 62 | 0x3E | 3 | `BUILDING_TEMPLE_PTAH` | Temple to Ptah |
| 63 | 0x3F | 3 | `BUILDING_TEMPLE_SETH` | Temple to Seth |
| 64 | 0x40 | 3 | `BUILDING_TEMPLE_BAST` | Temple to Bast |
| 65 | 0x41 | 3 | `BUILDING_TEMPLE_COMPLEX_OSIRIS` | Temple Complex to Osiris |
| 66 | 0x42 | 3 | `BUILDING_TEMPLE_COMPLEX_RA` | Temple Complex to Ra |
| 67 | 0x43 | 3 | `BUILDING_TEMPLE_COMPLEX_PTAH` | Temple Complex to Ptah |
| 68 | 0x44 | 3 | `BUILDING_TEMPLE_COMPLEX_SETH` | Temple Complex to Seth |
| 69 | 0x45 | 3 | `BUILDING_TEMPLE_COMPLEX_BAST` | Temple Complex to Bast |
| 70 | 0x46 | 2 | `BUILDING_BAZAAR` | Bazaar |
| 71 | 0x47 | 4 | `BUILDING_GRANARY` | Granary |
| 72 | 0x48 | 1 | `BUILDING_STORAGE_YARD` | Storage Yard |
| 73 | 0x49 | 1 | `BUILDING_STORAGE_ROOM` | Storage Yards |
| 74 | 0x4A | 3 | `BUILDING_SHIPWRIGHT` | Shipwright |
| 75 | 0x4B | 3 | `BUILDING_DOCK` | Dock |
| 76 | 0x4C | 2 | `BUILDING_FISHING_WHARF` | Fishing Wharf |
| 77 | 0x4D | 3 | `BUILDING_PERSONAL_MANSION` | Personal Mansion |
| 78 | 0x4E | 4 | `BUILDING_FAMILY_MANSION` | Family Mansion |
| 79 | 0x4F | 5 | `BUILDING_DYNASTY_MANSION` | Dynasty Mansion |
| 80 | 0x50 | 2 | `BUILDING_RESERVER_MISSION_POST_80` | unused 945 |
| 81 | 0x51 | 1 | `BUILDING_ARCHITECT_POST` | Architect's Post |
| 82 | 0x52 | 1 | `BUILDING_LOW_BRIDGE` | Bridge |
| 83 | 0x53 | 1 | `BUILDING_UNUSED_SHIP_BRIDGE_83` | unused 948 |
| 84 | 0x54 | 0 | `BUILDING_VILLAGE_PALACE` | Village Palace |
| 85 | 0x55 | 5 | `BUILDING_TOWN_PALACE` | Town Palace |
| 86 | 0x56 | 2 | `BUILDING_TAX_COLLECTOR` | Tax Collector |
| 87 | 0x57 | 0 | `BUILDING_TAX_COLLECTOR_UPGRADED` | Tax Collector |
| 88 | 0x58 | 1 | `BUILDING_UNUSED_NATIVE_HUT_88` | Nothing |
| 89 | 0x59 | 2 | `BUILDING_UNUSED_NATIVE_MEETING_89` | Nothing |
| 90 | 0x5A | 2 | `BUILDING_RESERVED_90` | Water Lift |
| 91 | 0x5B | 0 | `BUILDING_MENU_BEAUTIFICATION` | Beautification |
| 92 | 0x5C | 1 | `BUILDING_WELL` | Well |
| 93 | 0x5D | 1 | `BUILDING_UNUSED_NATIVE_CROPS_93` | Nothing |
| 94 | 0x5E | 4 | `BUILDING_MILITARY_ACADEMY` | Academy |
| 95 | 0x5F | 3 | `BUILDING_RECRUITER` | Recruiter |
| 96 | 0x60 | 0 | `BUILDING_MENU_TEMPLES` | Temples |
| 97 | 0x61 | 0 | `BUILDING_MENU_TEMPLE_COMPLEX` | Temple Complex |
| 98 | 0x62 | 2 | `BUILDING_ORACLE` | Oracle |
| 99 | 0x63 | 1 | `BUILDING_BURNING_RUIN` | Burning ruin |
| 100 | 0x64 | 3 | `BUILDING_BARLEY_FARM` | Barley |
| 101 | 0x65 | 3 | `BUILDING_FLAX_FARM` | Flax |
| 102 | 0x66 | 3 | `BUILDING_GRAIN_FARM` | Grain |
| 103 | 0x67 | 3 | `BUILDING_LETTUCE_FARM` | Lettuce |
| 104 | 0x68 | 3 | `BUILDING_POMEGRANATES_FARM` | Pomegranates |
| 105 | 0x69 | 3 | `BUILDING_CHICKPEAS_FARM` | Chickpeas |
| 106 | 0x6A | 2 | `BUILDING_STONE_QUARRY` | Plain Stone Quarry |
| 107 | 0x6B | 2 | `BUILDING_LIMESTONE_QUARRY` | Limestone Quarry |
| 108 | 0x6C | 2 | `BUILDING_WOOD_CUTTERS` | Wood Cutter |
| 109 | 0x6D | 2 | `BUILDING_CLAY_PIT` | Clay Pit |
| 110 | 0x6E | 2 | `BUILDING_BREWERY_WORKSHOP` | Brewery |
| 111 | 0x6F | 2 | `BUILDING_WEAVER_WORKSHOP` | Weaver |
| 112 | 0x70 | 2 | `BUILDING_WEAPONSMITH` | Weaponsmith |
| 113 | 0x71 | 2 | `BUILDING_JEWELS_WORKSHOP` | Jeweler |
| 114 | 0x72 | 2 | `BUILDING_POTTERY_WORKSHOP` | Potter |
| 115 | 0x73 | 2 | `BUILDING_HUNTING_LODGE` | Hunting Lodge |
| 116 | 0x74 | 1 | `BUILDING_UNUSED_116` | Nothing |
| 117 | 0x75 | 1 | `BUILDING_UNUSED_117` | Nothing |
| 118 | 0x76 | 1 | `BUILDING_UNUSED_118` | Nothing |
| 119 | 0x77 | 1 | `BUILDING_UNUSED_119` | Nothing |
| 120 | 0x78 | 1 | `BUILDING_UNUSED_120` | unused 985 |
| 121 | 0x79 | 1 | `BUILDING_UNUSED_121` | Crack (not used?) |
| 122 | 0x7A | 1 | `BUILDING_UNUSED_122` | unused 987 |
| 123 | 0x7B | 1 | `BUILDING_UNUSED_123` | Nothing |
| 124 | 0x7C | 1 | `BUILDING_UNUSED_124` | Nothing |
| 125 | 0x7D | 1 | `BUILDING_UNUSED_125` | Nothing |
| 126 | 0x7E | 1 | `BUILDING_UNUSED_126` | Nothing |
| 127 | 0x7F | 1 | `BUILDING_UNUSED_127` | Nothing |
| 128 | 0x80 | 1 | `BUILDING_UNUSED_128` | Nothing |
| 129 | 0x81 | 2 | `BUILDING_UNUSED_129` | Nothing |
| 130 | 0x82 | 1 | `BUILDING_UNUSED_130` | TXT_BUILDING_130 |
| 131 | 0x83 | 1 | `BUILDING_UNUSED_131` | TXT_BUILDING_131 |
| 132 | 0x84 | 1 | `BUILDING_UNUSED_132` | TXT_BUILDING_132 |
| 133 | 0x85 | 1 | `BUILDING_UNUSED_133` | TXT_BUILDING_133 |
| 134 | 0x86 | 1 | `BUILDING_MENU_EDUCATION` | TXT_BUILDING_134 |
| 135 | 0x87 | 0 | `BUILDING_ACADEMY` | TXT_BUILDING_135 |
| 136 | 0x88 | 2 | `BUILDING_FERRY` | Ferry Landing |
| 137 | 0x89 | 1 | `BUILDING_UNUSED_137` | TXT_BUILDING_137 |
| 138 | 0x8A | 1 | `BUILDING_ROADBLOCK` | Roadblock |
| 139 | 0x8B | 1 | `BUILDING_UNUSED_139` | TXT_BUILDING_139 |
| 140 | 0x8C | 1 | `BUILDING_SHRINE_OSIRIS` | Shrine to Osiris |
| 141 | 0x8D | 1 | `BUILDING_SHRINE_RA` | Shrine to Ra |
| 142 | 0x8E | 1 | `BUILDING_SHRINE_PTAH` | Shrine to Ptah |
| 143 | 0x8F | 1 | `BUILDING_SHRINE_SETH` | Shrine to Seth |
| 144 | 0x90 | 1 | `BUILDING_SHRINE_BAST` | Shrine to Bast |
| 145 | 0x91 | 1 | `BUILDING_C3_SHRINE_STATUE_1` | Shrine to  |
| 146 | 0x92 | 1 | `BUILDING_C3_SHRINE_STATUE_2` | Shrine to |
| 147 | 0x93 | 1 | `BUILDING_C3_SHRINE_STATUE_3` | Shrine to  |
| 148 | 0x94 | 1 | `BUILDING_C3_SHRINE_STATUE_4` | Shrine to  |
| 149 | 0x95 | 1 | `BUILDING_C3_SHRINE_STATUE_5` | Shrine to |
| 150 | 0x96 | 0 | `BUILDING_MENU_SHRINES` | Shrines |
| 151 | 0x97 | 3 | `BUILDING_BIG_TEMPLE_OSIRIS` | Temple to Osiris |
| 152 | 0x98 | 3 | `BUILDING_BIG_TEMPLE_RA` | Temple to Ra |
| 153 | 0x99 | 3 | `BUILDING_BIG_TEMPLE_PTAH` | Temple to Ptah |
| 154 | 0x9A | 3 | `BUILDING_BIG_TEMPLE_SETH` | Temple to Seth |
| 155 | 0x9B | 3 | `BUILDING_BIG_TEMPLE_BAST` | Temple to Bast |
| 156 | 0x9C | 3 | `BUILDING_C3_GOD_STATUE_5` | God 5 |
| 157 | 0x9D | 3 | `BUILDING_C3_GOD_STATUE_6` | God 6 |
| 158 | 0x9E | 3 | `BUILDING_C3_GOD_STATUE_7` | God 7 |
| 159 | 0x9F | 3 | `BUILDING_C3_GOD_STATUE_8` | God 8 |
| 160 | 0xA0 | 3 | `BUILDING_C3_GOD_STATUE_9` | God 9 |
| 161 | 0xA1 | 2 | `BUILDING_GOLD_MINE` | Gold Mine |
| 162 | 0xA2 | 2 | `BUILDING_GEMSTONE_MINE` | Gemstone Mine |
| 163 | 0xA3 | 1 | `BUILDING_ORDINARY_ROCK` | Ordinary rock |
| 164 | 0xA4 | 1 | `BUILDING_OREBEARING_ROCK` | Ore-bearing rock |
| 165 | 0xA5 | 1 | `BUILDING_UNUSED_165` | Unused 1030 |
| 166 | 0xA6 | 1 | `BUILDING_UNUSED_166` | Unused 1031 |
| 167 | 0xA7 | 1 | `BUILDING_FIREHOUSE` | Firehouse |
| 168 | 0xA8 | 1 | `BUILDING_BRICK_WALL_LANG` | Brick Wall |
| 169 | 0xA9 | 1 | `BUILDING_BRICK_WALL` | Wall |
| 170 | 0xAA | 2 | `BUILDING_CLAY_GATEHOUSE` | Brick Gatehouse |
| 171 | 0xAB | 2 | `BUILDING_BRICK_GATEHOUSE` | Gatehouse |
| 172 | 0xAC | 2 | `BUILDING_BRICK_TOWER` | Brick Tower |
| 173 | 0xAD | 2 | `BUILDING_CLAY_TOWER` | Tower |
| 174 | 0xAE | 0 | `BUILDING_MENU_MUD_STRUCTURES` | Mud structures |
| 175 | 0xAF | 0 | `BUILDING_MENU_BRICK_STRUCTURES` | Brick structures |
| 176 | 0xB0 | 0 | `BUILDING_MENU_DEFENSES` | Defensive Structures |
| 177 | 0xB1 | 2 | `BUILDING_CARPENTERS_GUILD` | Carpenters' Guild |
| 178 | 0xB2 | 2 | `BUILDING_BRICKLAYERS_GUILD` | Bricklayers' Guild |
| 179 | 0xB3 | 2 | `BUILDING_STONEMASONS_GUILD` | Stonemasons' Guild |
| 180 | 0xB4 | 2 | `BUILDING_WATER_SUPPLY` | Water Supply |
| 181 | 0xB5 | 2 | `BUILDING_TRANSPORT_WHARF` | Transport Wharf |
| 182 | 0xB6 | 3 | `BUILDING_WARSHIP_WHARF` | Warship Wharf |
| 183 | 0xB7 | 2 | `BUILDING_PYRAMID` | Pyramid |
| 184 | 0xB8 | 3 | `BUILDING_COURTHOUSE` | Courthouse |
| 185 | 0xB9 | 4 | `BUILDING_MILITARY_ACADEMY_2` | Military academy 2 |
| 186 | 0xBA | 4 | `BUILDING_MILITARY_ACADEMY_3` | Military academy 3 |
| 187 | 0xBB | 4 | `BUILDING_VILLAGE_PALACE_UP` | Village Palace |
| 188 | 0xBC | 5 | `BUILDING_TOWN_PALACE_UP` | Town Palace |
| 189 | 0xBD | 6 | `BUILDING_CITY_PALACE` | City Palace |
| 190 | 0xBE | 2 | `BUILDING_BAZAAR_UP` | Bazaar 2 |
| 191 | 0xBF | 4 | `BUILDING_GRANARY_UP` | Granary 2 |
| 192 | 0xC0 | 3 | `BUILDING_DOCK_UP` | Dock 2 |
| 193 | 0xC1 | 1 | `BUILDING_STORAGE_YARD_UP` | Storage Yard 2 |
| 194 | 0xC2 | 3 | `BUILDING_CATTLE_RANCH` | Cattle Ranch |
| 195 | 0xC3 | 2 | `BUILDING_REED_GATHERER` | Reed Gatherer |
| 196 | 0xC4 | 3 | `BUILDING_FIGS_FARM` | Fig Farm |
| 197 | 0xC5 | 1 | `BUILDING_MARSHLAND` | Marshland |
| 198 | 0xC6 | 1 | `BUILDING_SAND_DUNES` | Sand dunes |
| 199 | 0xC7 | 2 | `BUILDING_WORK_CAMP` | Work Camp |
| 200 | 0xC8 | 2 | `BUILDING_MUD_GATEHOUSE_UP` | Mud gatehouse |
| 201 | 0xC9 | 2 | `BUILDING_BRICK_GATEHOUSE_UP` | Brick gatehouse |
| 202 | 0xCA | 2 | `BUILDING_DECORATIVE_GATEHOUSE` | Gatehouse |
| 203 | 0xCB | 2 | `BUILDING_PAPYRUS_WORKSHOP` | Papyrus Maker |
| 204 | 0xCC | 2 | `BUILDING_BRICKS_WORKSHOP` | Brickworks |
| 205 | 0xCD | 4 | `BUILDING_CHARIOTS_WORKSHOP` | Chariot Maker |
| 206 | 0xCE | 2 | `BUILDING_PHYSICIAN` | Physician |
| 207 | 0xCF | 3 | `BUILDING_SMALL_OBELISK` | Small Obelisk |
| 208 | 0xD0 | 5 | `BUILDING_LARGE_OBELISK` | Large Obelisk |
| 209 | 0xD1 | 5 | `BUILDING_FESTIVAL_SQUARE` | Festival Square |
| 210 | 0xD2 | 6 | `BUILDING_SPHINX` | Sphinx |
| 211 | 0xD3 | 0 | `BUILDING_TEMPLE_COMPLEX_UPGRADE_A` | Temple Complex upgrade |
| 212 | 0xD4 | 0 | `BUILDING_TEMPLE_COMPLEX_UPGRADE_B` | Temple Complex upgrade |
| 213 | 0xD5 | 1 | `BUILDING_SUN_TEMPLE` | Sun Temple |
| 214 | 0xD6 | 1 | `BUILDING_DISEMBARK_POINT` | Disembark point |
| 215 | 0xD7 | 1 | `BUILDING_PYRAMID_ENTRY_TILE` | Pyramid entry tile |
| 216 | 0xD8 | 2 | `BUILDING_GRANITE_QUARRY` | Granite Quarry |
| 217 | 0xD9 | 2 | `BUILDING_COPPER_MINE` | Copper Mine |
| 218 | 0xDA | 2 | `BUILDING_PYRAMID_COMPLEX_TEMPLE` | Pyramid complex temple |
| 219 | 0xDB | 2 | `BUILDING_PYRAMID_COMPLEX_B` | Pyramid complex part B |
| 220 | 0xDC | 2 | `BUILDING_PYRAMID_COMPLEX_C` | Pyramid complex part C |
| 221 | 0xDD | 2 | `BUILDING_SANDSTONE_QUARRY` | Sandstone Quarry |
| 222 | 0xDE | 1 | `BUILDING_MAUSOLEUM` | Mausoleum |
| 223 | 0xDF | 1 | `BUILDING_CLIFF` | Cliff |
| 224 | 0xE0 | 3 | `BUILDING_HENNA_FARM` | Henna |
| 225 | 0xE1 | 1 | `BUILDING_ALEXANDRIA_LIBRARY` | Alexandria's Library |
| 226 | 0xE2 | 6 | `BUILDING_ZOO` | Zoo |
| 227 | 0xE3 | 1 | `BUILDING_CAESAREUM` | Caesareum |
| 228 | 0xE4 | 1 | `BUILDING_PHAROS_LIGHTHOUSE` | Pharos Lighthouse |
| 229 | 0xE5 | 1 | `BUILDING_SMALL_ROYAL_TOMB` | Small Royal Burial Tomb |
| 230 | 0xE6 | 1 | `BUILDING_ABU_SIMBEL` | Abu Simbel |
| 231 | 0xE7 | 2 | `BUILDING_ARTISANS_GUILD` | Artisans' Guild |
| 232 | 0xE8 | 2 | `BUILDING_LAMP_WORKSHOP` | Lamp Maker |
| 233 | 0xE9 | 2 | `BUILDING_PAINT_WORKSHOP` | Paint Maker |
| 234 | 0xEA | 0 | `BUILDING_MEDIUM_ROYAL_TOMB` | Medium Royal Burial Tomb |
| 235 | 0xEB | 0 | `BUILDING_LARGE_ROYAL_TOMB` | Large Royal Burial Tomb |
| 236 | 0xEC | 0 | `BUILDING_GRAND_ROYAL_TOMB` | Grand Royal Burial Tomb |
