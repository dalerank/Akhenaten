# Campaign mission maps

Shipped `FILE_FORMAT_MAP_FILE` maps for campaign scenarios (terrain, image,
elevation, moisture, fertility, vegetation, scenario_info, empire blobs, …).

Naming matches `src/scripts/mission/m_NNN_*.js` (scenarios **0–52**).

Each campaign mission sets `map_file : "data/maps/m_NNN_….map"`.
`GamestateIO::load_mission` loads that map only — there is no `mission1.pak`
fallback. Custom Cleopatra maps (ids 128+) use Cleop `Maps/` via
`__game_load_map`, not this folder.

Deployed at build time to `<binary>/Data/maps` (MSVC) or `<binary>/data/maps`.
