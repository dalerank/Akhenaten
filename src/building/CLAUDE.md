# Building Subsystem

Owns all building instances, their behavior, static configuration, and construction logic.

## Key Files

| File | Purpose |
|------|---------|
| `building.h / .cpp` | Main building instance: state, tile, size, orientation, figure slots, stores |
| `building_impl.h / .cpp` | Abstract base for building behavior (virtual hooks) |
| `building_type.h` | Enum of 300+ building types |
| `building_static_params.h` | Immutable per-type config (cost, labor, animations, desirability) |
| `building_model.h` | Factory registration and model lookup |
| `building_fwd.h` | Core enums: states, flags, slots |
| `building_cast.h` | Type-safe downcast system |
| `building_house.h` | Housing evolution and demands |
| `building_industry.h` | Base for production buildings |
| `building_storage.h` | Storage yard/room resource routing |
| `construction/build_planner.h` | UI placement preview and validation |
| `monuments.h` | Monument multi-phase construction |

## Core Classes

**`building`** — instance data: type, tile, state, orientation, figure slots (4), resource stores, animation contexts, runtime_data buffer (186 bytes).

**`building_impl`** — virtual behavior: `on_create`, `on_place`, `spawn_figure`, `update_day/week/month/year`, `draw_ornaments_and_animations_height`, `draw_postrender_effects`.

**`building_static_params`** — immutable per-type data from config: labor_category, size, cost, animations, desirability/crime decay profiles, planner rules, resource input/output.

## Patterns

### Adding a new building type
1. Add enum value to `building_type.h`
2. Create `building_mytype.h/.cpp` inheriting from appropriate base
3. Use `BUILDING_METAINFO(BUILDING_MYTYPE, building_mytype, base_class)` macro
4. Implement virtual hooks as needed
5. Define nested `runtime_data_t` (max 186 bytes, enforced by `static_assert`)
6. Add config entry for static params

### Type-safe access
```cpp
auto *farm = b->dcast<building_farm>();   // nullptr if wrong type
auto *farm = b->dcast_farm();             // convenience shorthand
// NEVER: static_cast<building_farm*>(b)
```

### Figure spawning
Buildings manage up to 4 figure slots. Spawn in `spawn_figure()` override:
```cpp
create_figure_generic(FIGURE_WORKER, ACTION_GO, SLOT_SERVICE);
create_roaming_figure(FIGURE_ENTERTAINER, ACTION_ROAM, SLOT_SERVICE);
create_figure_with_destination(FIGURE_CARTPUSHER, dest_tile, SLOT_CARTPUSHER);
```

### Exposing a `building` field to JS
Prefer the generic property mechanism over hand-written bindings:
1. Add the field to `ANK_CONFIG_PROPERTY(building, ...)` in `building.h`.
2. Declare it in `src/scripts/building/prototype.js` as an empty descriptor: `Building.property.my_field = { }`.

An empty `{ }` descriptor is **not** a no-op — it routes through the shared
`building_proto___property_getter/__property_setter`, which read/write the struct
field by name via `archive_helper`. This works for primitive fields (bool, int, enum).

Only write a dedicated `__my_getter`/`__my_setter` C++ function + `jsB_propf`
registration when the value is **computed** and cannot be modelled any other way.
Don't add custom get/set bindings for a primitive field — add it to
`ANK_CONFIG_PROPERTY` instead.

For per-building quantities that behave like an inventory count but aren't a real
traded resource (e.g. brewery water), prefer a **pseudo-resource**: add an id past
`RESOURCES_MAX` (like `RESOURCE_DEBEN`/`RESOURCE_TROOPS`/`RESOURCE_WATER`), override
`stored_amount(e_resource)` in the building to intercept it, and read it from JS via
the existing `b.stored_resource(RESOURCE_X)` — no new binding needed. Pseudo-resources
don't leak into trade/overlays/warehouses (those iterate `< RESOURCES_MAX`), and
`base.storage` is a sparse key-value store so ids past the max are safe.

### Animation state
Buildings expose a runtime `bool play_animation` flag (not a virtual predicate).
Override `virtual void update_animation()` to set `base.play_animation`, call the
parent's `update_animation()` first, then `es(__func__)` at the end to let JS
scripts override the decision (e.g. brewery rules live in `scripts/building/workshop.js`).
`update_animation()` is invoked before `update_graphic()` in `on_place`,
`on_post_load`, and `update_day`. Rendering (`animation_offset`,
`update_graphic_work_anim`) reads `base.play_animation` directly.

### Lifecycle
`initialize → on_create → on_place → on_place_checks → update_day/week/month/year → on_destroy`

### Building state machine
`e_building_state`: `VALID`, `CREATED`, `RUBBLE`, `MOTHBALLED`, `DELETED_BY_PLAYER`, `DELETED_BY_GAME`

## Cross-Subsystem Connections

- **`city/`** — `city_buildings_t` owns the building registry; labor pool queries
- **`figure/`** — buildings spawn and track figures via figure slots
- **`grid/`** — occupancy map, desirability influence, road access, crime
- **`game/resource.h`** — `e_resource` enum, `building_store` resource quantities
- **`overlays/`** — desirability/crime/labor overlay registration

## Invariants

- Building `tile` = top-left corner of footprint; `size` determines extent
- Max 186 bytes per `runtime_data` buffer — checked by `static_assert`
- `static_params` are immutable after startup — never write to them
- Always use `dcast<T>()` for downcasts, never `static_cast`
- Multi-part buildings (monuments, temple complexes) linked via `next_part_building_id`
