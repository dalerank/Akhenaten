# Editor Bridge / Ferry allow flags (UB1 / BR1)

| Slot | Lang 67 | Types |
|------|---------|--------|
| **28** | Bridge | `{BUILDING_LOW_BRIDGE}` only |
| **29** | Ferry Landing | `{BUILDING_FERRY}` |

**SHIP_BRIDGE = none** — no editor slot; `BUILDING_UNUSED_SHIP_BRIDGE_83` is not a
consumer of UB1 (**SB0=A** locked 2026-08-01). Do not map Bridge → 83.
Engine/load/undo may still know type 83 (C3 leftover); campaign menu and
`buildings[]` must not. Place regression: `tests/136_ship_bridge_placement.js`.
Enhanced menu (if ever) = PC2 only — not remake-close.

Merge: **UB-A** (JS `buildings[]` / `use_building` = menu; map editor flags = audit).
Menu smoke: `tests/115_bridge_menu_smoke.js` (Perwadjyt REMAP + Bridges/Nekhen day-0;
also asserts type 83 never allowed).

Source: campaign `data/maps/m_NNN_*.map` + Cleop `Maps/{Alexandria,Bridges}.map`.
Wiki Dev Ref: Low Bridge listed where JS unlocks it (2026-07-31 BR2); Ship Bridge
note on buildings index (2026-08-01).

| ID | Src | Bridge | Ferry | JS triage |
|----|-----|--------|-------|-----------|
| 0 Nubt | map | 0 | 0 | OK (no unlock) |
| 1 Thinis tut | map | 0 | 0 | OK |
| 2 Perwadjyt | map | 0 | 0 | **REMAP** — tutorial `use_building` Low Bridge + Ferry |
| 3 Nekhen | map | 1 | 1 | OK |
| 4 Men-nefer | map | 1 | 0 | Bridge OK |
| 5 Timna | map | 1 | 0 | Bridge OK |
| 6 Behdet | map | 1 | 1 | OK |
| 7 Abedju | map | 1 | 1 | OK |
| 8 Selima | map | 1 | 0 | Bridge OK |
| 9 Abu | map | 1 | 0 | Bridge OK; JS Ferry = REMAP (map OFF) |
| 10 Saqqara | map | 1 | 1 | OK |
| 11 Serabit | map | 1 | 1 | OK (Ferry synced; map has no river) |
| 12 Meidum | map | 1 | 0 | Bridge OK; JS Ferry = REMAP |
| 13 Buhen | map | 1 | 1 | OK |
| 14 S. Dahshur | map | 1 | 1 | OK |
| 15 N. Dahshur | map | 1 | 1 | OK |
| 16 Iunet | map | 1 | 1 | OK |
| 17 On | map | 1 | 0 | Bridge OK; JS Ferry = REMAP |
| 18 Rostja | map | 1 | 1 | OK |
| 19 Bahariya | map | 1 | 0 | Bridge OK |
| 20 Djedu | map | 1 | 1 | OK |
| 21 Dunqul | map | 1 | 1 | OK (Ferry synced) |
| 22 Dakhla | map | 1 | 1 | OK (Ferry synced) |
| 23–31 | map | 1 | 1 | OK |
| 38–40 Valley | map | 1 | 0 | Bridge OK; JS Ferry = REMAP |
| 41 Sumur | map | 1 | 1 | OK |
| 42 Qadesh | map | 1 | 1 | OK (Ferry synced) |
| 45 Pi-Yer | map | 1 | 1 | OK |
| 128 Alexandria | Cleop map | 1 | 1 | OK |
| 129 Bridges | Cleop map | 1 | 1 | OK |

## Open / out of scope

- Cleo **32–37 / 43–44** — no mission JS yet
- Custom **130–135** — minimal sandbox `buildings[]` (SKIP)
- Ferry REMAP cleanup (Abu / Meidum / On / Valley keep JS Ferry despite map OFF)
- Ship Bridge in player menu — Enhanced / PC2 only (not OG parity)
