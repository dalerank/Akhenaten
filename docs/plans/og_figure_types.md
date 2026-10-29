# Pharaoh OG figure types (0…109)

Recovered from `akhenatren-rm` — `figure_type_debug_names` @ `0x005DC444`
(action table `0x005DC28C`). See also `akhenatren-rm/docs/drafts/figure.md`.

**110 types.** No type ≥ 110 exists in the original; Akhenaten extras
(PHARAOH, GOVERNOR, DRUNKARD, expanded enemy blocks, …) are port additions.

Akhenaten `e_figure_type` is aligned with these ids for 0…109 (2026-10).
Port-only types sit at 110+: e.g. `FIGURE_SCRIBER = 181` (was wrongly 29).
`FIGURE_FISHING_POINT = 95` is OG `FIG_JUMPING_FISH`; `FIGURE_SEAGULLS = 65`.

| id | hex | internal name | role |
|---:|:---:|---|---|
| 0 | 0x00 | `FIG_NULL` | empty / none |
| 1 | 0x01 | `FIG_IMMIGRANT` | immigrant |
| 2 | 0x02 | `FIG_EMMIGRANT` | emigrant |
| 3 | 0x03 | `FIG_VAGRANT` | homeless / vagrant |
| 4 | 0x04 | `FIG_CART` | cartpusher |
| 5 | 0x05 | `FIG_GHOST` | labor seeker |
| 6 | 0x06 | `FIG_EXPLOSION` | explosion cloud |
| 7 | 0x07 | `FIG_TAXMAN` | tax collector |
| 8 | 0x08 | `FIG_ENGINEER` | engineer |
| 9 | 0x09 | `FIG_WAREHOUSEMAN` | storage yard cartpusher |
| 10 | 0x0A | `FIG_FIREMAN` | fireman |
| 11 | 0x0B | `FIG_LEG_MISS` | legion missile |
| 12 | 0x0C | `FIG_LEG_AUX` | legion light / aux |
| 13 | 0x0D | `FIG_LEG_HEAVY` | legion heavy |
| 14 | 0x0E | `FIG_STANDARD` | military standard |
| 15 | 0x0F | `FIG_JUGGLER` | juggler |
| 16 | 0x10 | `FIG_MUSICIAN` | musician |
| 17 | 0x11 | `FIG_DANCER` | dancer |
| 18 | 0x12 | `FIG_BULLFIGHTER` | bullfighter |
| 19 | 0x13 | `FIG_CARAVAN` | trade caravan |
| 20 | 0x14 | `FIG_JUNK` | trade ship |
| 21 | 0x15 | `FIG_VAN_FOLLOWER` | caravan donkey |
| 22 | 0x16 | `FIG_SIMPLE_CRIME` | protestor |
| 23 | 0x17 | `FIG_THIEF` | thief / criminal |
| 24 | 0x18 | `FIG_TOMB_ROBBER` | tomb robber |
| 25 | 0x19 | `FIG_FISHING_BOAT` | fishing boat |
| 26 | 0x1A | `FIG_MARKET_GIRL` | market trader |
| 27 | 0x1B | `FIG_PRIEST` | priest |
| 28 | 0x1C | `FIG_BUBBLES` | bubbles |
| 29 | 0x1D | `FIG_TEACHER` | teacher |
| 30 | 0x1E | `FIG_LIBRARIAN` | librarian |
| 31 | 0x1F | `FIG_DENTIST` | dentist |
| 32 | 0x20 | `FIG_PHYSICIAN` | physician |
| 33 | 0x21 | `FIG_APOTHECARY` | apothecary |
| 34 | 0x22 | `FIG_EMBALMER` | embalmer |
| 35 | 0x23 | `FIG_WORKER` | worker |
| 36 | 0x24 | `FIG_MAP_FLAG` | editor map flag |
| 37 | 0x25 | `FIG_FLOTSAM` | flotsam |
| 38 | 0x26 | `FIG_DOCKER` | docker |
| 39 | 0x27 | `FIG_BUYER` | market buyer |
| 40 | 0x28 | `FIG_PATRICIAN` | patrician |
| 41 | 0x29 | `FIG_BARBARIAN` | indigenous native |
| 42 | 0x2A | `FIG_WALLGUY` | tower sentry |
| 43 | 0x2B | `FIG_ENEMY_MISS` | enemy missile |
| 44 | 0x2C | `FIG_ENEMY_AUX` | enemy light |
| 45 | 0x2D | `FIG_ENEMY_HEAVY` | enemy heavy |
| 46 | 0x2E | `FIG_ENEMY_CAMEL` | enemy camel |
| 47 | 0x2F | `FIG_ENEMY_ELEPHANT` | enemy elephant |
| 48 | 0x30 | `FIG_BARB_CHARIOT` | barbarian chariot |
| 49 | 0x31 | `FIG_BARB_LIGHT` | barbarian light |
| 50 | 0x32 | `FIG_BARB_HEAVY` | barbarian heavy |
| 51 | 0x33 | `FIG_BARB_MISS` | barbarian missile |
| 52 | 0x34 | `FIG_BARB_HORSE` | barbarian mounted |
| 53 | 0x35 | `FIG_BARB_HEAVY2` | barbarian heavy 2 |
| 54 | 0x36 | `FIG_EGYPT_AUX` | Egyptian light |
| 55 | 0x37 | `FIG_EGYPT_MISS` | Egyptian missile |
| 56 | 0x38 | `FIG_EGYPT_HEAVY` | Egyptian heavy |
| 57 | 0x39 | `FIG_ENEMY_LEG_HEAVY` | enemy legion heavy |
| 58 | 0x3A | `FIG_BARB_DONKEY` | native trader |
| 59 | 0x3B | `FIG_ARROW` | arrow |
| 60 | 0x3C | `FIG_PLAYER_MISSILE` | player javelin |
| 61 | 0x3D | `FIG_BOLT` | bolt |
| 62 | 0x3E | `FIG_BALLISTA` | ballista |
| 63 | 0x3F | `FIG_CREATURE` | creature stub |
| 64 | 0x40 | `FIG_MISSIONARY` | missionary |
| 65 | 0x41 | `FIG_SEAGULLS` | seagulls |
| 66 | 0x42 | `FIG_GRANARY_BOY` | delivery boy |
| 67 | 0x43 | `FIG_SHIPWRECK` | shipwreck |
| 68 | 0x44 | `FIG_BIRDS` | birds |
| 69 | 0x45 | `FIG_OSTRICH` | ostrich |
| 70 | 0x46 | `FIG_ANTELOPE` | antelope |
| 71 | 0x47 | `FIG_ENEMY_MISSILE` | enemy spear |
| 72 | 0x48 | `FIG_CHARIOT_RACERS` | chariot racers (no-op handler) |
| 73 | 0x49 | `FIG_HUNTER` | hunter |
| 74 | 0x4A | `FIG_HUNTER_SPEAR` | hunter spear |
| 75 | 0x4B | `FIG_LUMBERJACK` | lumberjack |
| 76 | 0x4C | `FIG_FERRY_BOAT` | ferry boat |
| 77 | 0x4D | `FIG_TRANSPORT` | transport ship |
| 78 | 0x4E | `FIG_WARSHIP` | warship |
| 79 | 0x4F | `FIG_CARPENTER` | carpenter |
| 80 | 0x50 | `FIG_BRICK_LAYER` | bricklayer |
| 81 | 0x51 | `FIG_STONE_MASON` | stonemason |
| 82 | 0x52 | `FIG_CROC` | crocodile |
| 83 | 0x53 | `FIG_HYENA` | hyena |
| 84 | 0x54 | `FIG_HIPPO` | hippo |
| 85 | 0x55 | `FIG_LABORER` | laborer / work camp |
| 86 | 0x56 | `FIG_PULLED_STONE` | sled (pulled stone) |
| 87 | 0x57 | `FIG_WATER_CARRIER` | water carrier |
| 88 | 0x58 | `FIG_POLICEMAN` | constable / policeman |
| 89 | 0x59 | `FIG_MAGISTRATE` | magistrate |
| 90 | 0x5A | `FIG_REED_CUTTER` | reed gatherer |
| 91 | 0x5B | `FIG_FESTIVAL_PRIEST` | festival priest |
| 92 | 0x5C | `FIG_ENEMY_TRANSPORT` | enemy transport |
| 93 | 0x5D | `FIG_ENEMY_WARSHIP` | enemy warship |
| 94 | 0x5E | `FIG_FUNERAL_WALKER` | funeral walker (no-op in OG) |
| 95 | 0x5F | `FIG_JUMPING_FISH` | fishing spot / jumping fish |
| 96 | 0x60 | `FIG_STONE_PULLER` | sled puller |
| 97 | 0x61 | `FIG_SHOWMAN` | showman |
| 98 | 0x62 | `FIG_PLAGUE_DUDE` | plague citizen |
| 99 | 0x63 | `FIG_BEDOUIN` | bedouin |
| 100 | 0x64 | `FIG_EGYPT_WARSHIP` | Egyptian warship |
| 101 | 0x65 | `FIG_EGYPT_TRANSPORT` | Egyptian transport |
| 102 | 0x66 | `FIG_ASP` | asp |
| 103 | 0x67 | `FIG_LION` | lion |
| 104 | 0x68 | `FIG_SCORPION` | scorpion |
| 105 | 0x69 | `FIG_ZOOKEEPER` | zookeeper (shares entertainer handler) |
| 106 | 0x6A | `FIG_FROG` | frog |
| 107 | 0x6B | `FIG_LOCUST` | locust |
| 108 | 0x6C | `FIG_ARTISAN` | tomb artisan |
| 109 | 0x6D | `FIG_MUMMY` | mummy |

## Shared handlers (OG)

- `0x0048E9E0` — soldiers: types **11, 12, 13**
- `0x00490E00` — entertainers: types **15–18** and **105** (zookeeper)
- `0x0051F780` — no-op: types **0**, **72**, **94**
- Types **43…57** and **99** call shared `enemy_action` `0x004991A0`
