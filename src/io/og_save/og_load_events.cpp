#include "io/og_save/og_load.h"

#include "core/log.h"
#include "scenario/scenario.h"
#include "scenario/scenario_event_manager.h"

#include <algorithm>
#include <cstring>
#include <vector>

// The events themselves come from our mission script; the save only says how far each one got. An OG event
// (tutankhamun scenario_event_types.h) is matched to ours by type and start date, item and amount, preferring the
// same index, and its progress is copied over.
namespace og {

    namespace {

        // A recurring event moves its year forward each time it fires, so the year is compared only on the first pass.
        bool same_event(const event_ph_t& ours, const scenario_event& og, bool with_year) {
            return ours.type == og.type && ours.time.month == og.month
                   && (!with_year || ours.time.year == og.year.value) && ours.item.value == og.item.value
                   && ours.amount.value == og.amount.value;
        }

        event_ph_t* find_event(int og_index, const scenario_event& og, std::vector<bool>& taken) {
            auto& events = g_scenario.events;
            const int count = events.events_count();
            for (bool with_year : {true, false}) {
                if (og_index < count && !taken[og_index] && same_event(*events.at(og_index), og, with_year)) {
                    taken[og_index] = true;
                    return events.at(og_index);
                }
                for (int i = 0; i < count; ++i) {
                    if (!taken[i] && same_event(*events.at(i), og, with_year)) {
                        taken[i] = true;
                        return events.at(i);
                    }
                }
            }
            return nullptr;
        }

    } // namespace

    void load_events(const savegame& s, load_report& report) {
        const auto& raw = s.chunks[CHUNK_SCENARIO_EVENTS];
        int32_t og_count = 0;
        std::memcpy(&og_count, raw.data(), sizeof(og_count));
        const auto* og_events = reinterpret_cast<const scenario_event*>(raw.data() + sizeof(int32_t));
        og_count = std::min<int32_t>(og_count, SCENARIO_MAX_EVENTS);

        std::vector<bool> taken(g_scenario.events.events_count(), false);
        for (int i = 0; i < og_count; ++i) {
            const scenario_event& og = og_events[i];
            if (og.type == EVENT_TYPE_NONE) {
                continue;
            }
            event_ph_t* ours = find_event(i, og, taken);
            if (!ours) {
                logs::info("[og-save] unmapped event %d: type %d %d/%d item %d amount %d has no match in the mission",
                  i, og.type, og.month, og.year.value, og.item.value, og.amount.value);
                report.events_unmatched++;
                continue;
            }
            ours->time.year = og.year.value;
            ours->event_state = (e_event_state)(og.state & 0xFF);
            ours->is_overdue = ((og.state >> 8) & 0xFF) != 0;
            ours->event_trigger_type = (e_event_trigger_type)(og.flags & 0xFF);
            ours->quest_months_left = (uint8_t)og.months_left;
            ours->is_active = og.is_active != 0;
            ours->can_comply_dialog_shown = og.can_comply_shown != 0;
            ours->invasion_warnings_shown = og.invasion_warnings_shown;
            report.events_synced++;
        }
    }

} // namespace og
