# Scenario Subsystem

Mission configuration, win criteria, timed events (invasions, requests, disasters), and map entry/exit points.

## Key Files

| File | Purpose |
|------|---------|
| `scenario.h` | `scenario_data_t` — mission config: name, climate, difficulty, win criteria, monuments |
| `scenario_event_manager.h` | `event_manager_t` — event storage, processing, request lifecycle, distant battles |
| `map.h` | Map entry/exit points, herd spawns, invasion zones, fishing points |
| `request.h` | `scenario_request` — resource requests with state machine |
| `types.h` | Event type enums |
| `earthquake.h / invasion.h / distant_battle.h` | Specific event parameter structures |
| `*_change.h` (price, demand, farao) | Timed game-state changes |
| `editor.h / editor_events.h` | Mission editor infrastructure |

## Mission Structure

- **Metadata**: name, subtitle, brief, climate, difficulty, player rank
- **Win Criteria**: population/culture/prosperity/monuments thresholds, time limits, housing requirements
- **Finance**: initial funds, rescue loans
- **Empire**: trade routes, distant battle definitions
- **Events**: managed by `event_manager_t`, time-triggered via game tick

## Event System

### Event types
Requests, invasions, earthquakes, floods, trade disruptions, wage changes, plagues, pharaoh demands.

### Trigger modes
- `EVENT_TRIGGER_ONCE`
- `EVENT_TRIGGER_RECURRING`
- `EVENT_TRIGGER_BY_RATING`
- `EVENT_TRIGGER_ONLY_VIA_EVENT`

### `event_ph_t` structure
- type + subtype + trigger type + state
- Time-based: year/month with deadline calculation
- Action chains: `on_completed / on_refusal / on_toolate / on_defeat` → references another event

### Request lifecycle (`scenario_request`)
State machine: `initial → in_progress → (completed | failed | overdue)`
- Tracks months_to_comply, visible state, resource requirements
- Sender can be empire city or pharaoh

## Map Integration

- Entry/exit points for land troops and river units (separate)
- Invasion landing zones (land + sea)
- Herd spawn points (predators + prey)
- Fishing points for food production

## Cross-Subsystem Connections

- **`city/`** — win criteria checked against city ratings/population; events modify city state
- **`grid/`** — map entry/exit, invasion zones, herd spawn points written to grid at scenario load
- **`empire/`** — trade routes and distant battle definitions
- **`io/`** — scenario data serialized as IO chunk

## Invariants

- Scenario data is loaded once and treated as mostly immutable during gameplay
- Event state machine is one-way (no rollback)
- Action chains reference events by index — don't reorder events in config
