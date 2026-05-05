# City Subsystem

The city simulation aggregate root. Owns all macro-level state: population, labor, finance, religion, sentiment, resources, buildings registry.

## Key Files

| File | Purpose |
|------|---------|
| `city.h / .cpp` | `city_t` — aggregate root, update_day/week/month/year orchestration |
| `buildings.h` | Template API for building iteration and queries |
| `city_buildings.h / .cpp` | Building registry, active counts per type |
| `city_population.h / .cpp` | Population dynamics: aging, births/deaths, migration |
| `city_labor.h / .cpp` | Worker allocation across 10 labor categories |
| `city_finance.h / .cpp` | Treasury, taxes, wages, tribute, interest |
| `city_resource.h / .cpp` | Food/goods storage, consumption, production tracking |
| `city_religion.h / .cpp` | 5 god moods (Osiris, Ptah, Ra, Seth, Bast), blessings/curses |
| `city_sentiment.h / .cpp` | Happiness value, contribution breakdown |
| `ratings.h / .cpp` | Culture, prosperity, monument ratings |
| `coverage.h` | Entertainment/education/health/religion service coverage |
| `city_figures.h / .cpp` | Enemy/soldier/rioter counters |
| `city_migration.h / .cpp` | Immigration/emigration mechanics |
| `city_health.h / .cpp` | Disease, health value, mortuary coverage |

## Global Access

```cpp
g_city   // single city_t instance, accessed everywhere
```

## Update Cycle

```
city_t::update_day(t)    // sentiment, criminals, plague, environment, buildings, figures
city_t::update_week(t)   // resource consumption
city_t::update_month(t)  // ratings, finance, migration, health, buildings, festivals
```
Each subsystem within `city_t` hooks into the appropriate frequency.

## Building Query API

Template-heavy API in `buildings.h`:
```cpp
buildings_valid_do<building_granary>([](auto &b) { /* iterate */ });
auto *b = building_first<building_market>([](auto &b) { return b.has_goods(); });
buildings_get(array, BUILDING_GRANARY, BUILDING_STORAGEYARD);
```

## Event Bus

City state changes emit typed events:
```cpp
g_city_events.post(event_finance_changed{amount});
```
Subscribers (UI, scripts) react without polling. Treasury wrapper auto-emits on write.

## Key Subsystems

**Population** — 10 age buckets, circular history (2400 months), immigration caps per reason.

**Labor** — 10 fixed categories, priority-based allocation. Buildings declare `labor_category` in static params.

**Finance** — `city_finance_t::treasury` emits events on change. Monthly: taxes, wages, tribute, interest, festival costs.

**Religion** — 5 gods hardcoded. God effects: Osiris=double farms, Ra=trade bonuses, Seth=military buffs, Ptah=workshops, Bast=health/crime.

**Sentiment** — 8+ contribution factors (wages, jobs, food, taxes, huts, religion, monuments). Calculated daily/monthly.

**Resources** — Granaries (food months) separate from storage yards (goods). Mothballed/stockpiled flags for production control.

## Invariants

- `g_city` is the only city instance — never instantiate `city_t` directly
- No subsystem modifies another directly; use events for cross-subsystem side effects
- Population cannot exceed housing capacity
- Religion is always 5 gods — no dynamic god registration
