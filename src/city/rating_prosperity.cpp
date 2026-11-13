#include "city/city.h"

#include "core/calc.h"
#include "game/game.h"
#include "scenario/scenario.h"
#include "building/building_house.h"
#include "building/building_temple_complex.h"
#include "building/monuments.h"

// OG city_ratings_update_prosperity / city_ratings_prosperity_explanation terms, in scripts/city/ratings.js.
struct prosperity_rating_params_t {
    svector<int, 12> months;
    int finance_profit;
    int finance_construction_profit;
    int finance_loss;
    int finance_construction_loss;
    int trade;
    int workers_needed;
    int unemployment_low;
    int unemployment_low_change;
    svector<int, 8> unemployment_limits;
    svector<int, 8> unemployment_changes;
    int food_types_min;
    int few_food_types_change;
    svector<int, 8> wage_above;
    svector<int, 8> wage_above_changes;
    svector<int, 8> wage_below;
    svector<int, 8> wage_below_changes;
    int ra_oracle_wage_bonus;
    int huts_share;
    int huts_change;
    int manors_share;
    int manors_change;
    int tribute_not_paid_change;
    int senet_change;
    int completed_monument_change;
};
ANK_CONFIG_STRUCT(prosperity_rating_params_t, months, finance_profit, finance_construction_profit, finance_loss,
  finance_construction_loss, trade, workers_needed, unemployment_low, unemployment_low_change, unemployment_limits,
  unemployment_changes, food_types_min, few_food_types_change, wage_above, wage_above_changes, wage_below,
  wage_below_changes, ra_oracle_wage_bonus, huts_share, huts_change, manors_share, manors_change,
  tribute_not_paid_change, senet_change, completed_monument_change)
prosperity_rating_params_t ANK_VARIABLE(prosperity_rating);

namespace {

    // OG TEMPLE_COMPLEX_RA_WAGE_BONUS is subtracted from the wage difference.
    int temple_complex_wage_bonus() {
        const building_id complex_id = g_city.buildings.temple_complex_id(BUILDING_TEMPLE_COMPLEX_RA);
        if (!complex_id) {
            return 0;
        }
        auto* complex = building_get(complex_id)->dcast_temple_complex();
        return (complex && complex->has_upgrade(etc_upgrade_oracle)) ? prosperity_rating.ra_oracle_wage_bonus : 0;
    }

    bool is_og_pyramid_or_sphinx(e_building_type type) {
        switch (type) {
        case BUILDING_SPHINX:
        case BUILDING_SMALL_BENT_PYRAMID:
        case BUILDING_MEDIUM_BENT_PYRAMID:
        case BUILDING_SMALL_MUDBRICK_PYRAMID:
        case BUILDING_MEDIUM_MUDBRICK_PYRAMID:
        case BUILDING_LARGE_MUDBRICK_PYRAMID:
        case BUILDING_MUDBRICK_PYRAMID_COMPLEX:
        case BUILDING_GRAND_MUDBRICK_PYRAMID_COMPLEX:
        case BUILDING_SMALL_STEPPED_PYRAMID:
        case BUILDING_MEDIUM_STEPPED_PYRAMID:
        case BUILDING_LARGE_STEPPED_PYRAMID:
        case BUILDING_STEPPED_PYRAMID_COMPLEX:
        case BUILDING_GRAND_STEPPED_PYRAMID_COMPLEX:
        case BUILDING_SMALL_PYRAMID:
        case BUILDING_MEDIUM_PYRAMID:
        case BUILDING_LARGE_PYRAMID:
        case BUILDING_PYRAMID_COMPLEX:
        case BUILDING_GRAND_PYRAMID_COMPLEX:
        case BUILDING_SMALL_MASTABA:
        case BUILDING_MEDIUM_MASTABA:
        case BUILDING_LARGE_MASTABA:
            return true;
        default:
            return false;
        }
    }

    // OG city_has_completed_monument: a finished pyramid-family monument (mastabas included) or Sphinx.
    bool city_has_completed_monument() {
        bool found = false;
        buildings_valid_do([&found](building& b) {
            if (found || !b.is_main() || !is_og_pyramid_or_sphinx(b.type)) {
                return;
            }
            auto* m = b.dcast_monument();
            found = m && m->is_finished();
        });
        return found;
    }

    struct prosperity_inputs {
        int income;
        int expenses;
        int construction_last_year;
        int construction_this_year;
        int imports;
        int exports;
        bool workers_needed;
        int unemployment;
        int food_types;
        int wages;
        int huts_share;
        int manors_share;
        bool tribute_not_paid;
        bool senet_shows;
        bool completed_monument;
    };

    prosperity_inputs collect_prosperity_inputs(city_t& city) {
        const auto& last = city.finance.last_year;
        prosperity_inputs in;
        in.income = last.income.gold_delivered + last.income.donated + last.income.taxes + last.income.exports;
        in.construction_last_year = last.expenses.construction;
        in.construction_this_year = city.finance.this_year.expenses.construction;
        in.expenses = last.expenses.mayour_salary + last.expenses.interest + last.expenses.wages + last.expenses.imports
                      + in.construction_last_year;
        in.imports = last.expenses.imports;
        in.exports = last.income.exports;
        in.workers_needed = city.labor.workers_needed >= 1;
        in.unemployment = city.labor.unemployment_percentage;
        in.food_types = city.resource.food_types_eaten_max();
        in.wages
          = (city.finance.wage_rate_paid_last_year / 12) - city.finance.wages_kingdome - temple_complex_wage_bonus();
        in.huts_share = calc_percentage(city.population.people_in_shanties, city.population.current);
        in.manors_share = calc_percentage(city.population.people_in_manors, city.population.current);
        in.tribute_not_paid = city.finance.tribute_not_paid_last_year;
        in.senet_shows = city.entertainment.senet_house_plays > 0;
        in.completed_monument = city_has_completed_monument();
        return in;
    }


    struct prosperity_change_t {
        int change = 0;
        int severity = 0;
        e_prosperity_reason reason = e_prosperity_reason_finances;

        // A term that lowers the rating explains it when it is the most severe so far.
        void add(int delta, e_prosperity_reason r) {
            change += delta;
            raise(-delta, r);
        }
        void raise(int level, e_prosperity_reason r) {
            if (severity < level) {
                severity = level;
                reason = r;
            }
        }
    };

    // OG computes the change twice: the rating uses last year's construction in the fallback finance terms,
    // the advisor explanation this year's.
    prosperity_change_t prosperity_change(const prosperity_inputs& in, int fallback_construction) {
        const auto& p = prosperity_rating;
        prosperity_change_t c;
        if ((in.income - in.expenses) >= 1) {
            c.change = p.finance_profit;
        } else if (((fallback_construction / 2) - in.expenses + in.income) >= 1) {
            c.change = p.finance_construction_profit;
        } else if ((in.income - in.expenses) < 0) {
            c.add(p.finance_loss, e_prosperity_reason_finances);
        } else if ((fallback_construction - in.expenses + in.income) < 0) {
            c.add(p.finance_construction_loss, e_prosperity_reason_finances);
        }

        if (in.imports < in.exports) {
            c.change += p.trade;
        } else {
            if (in.exports < in.imports) {
                c.change -= p.trade;
            }
            c.raise(p.trade, e_prosperity_reason_trade);
        }

        if (!in.workers_needed) {
            if (in.unemployment < p.unemployment_low) {
                c.change += p.unemployment_low_change;
            } else {
                int delta = 0;
                for (size_t i = 0; i < p.unemployment_limits.size() && i < p.unemployment_changes.size(); ++i) {
                    if (in.unemployment >= p.unemployment_limits[i]) {
                        delta = p.unemployment_changes[i];
                    }
                }
                c.change += delta;
                c.raise(std::max(-delta, 1), e_prosperity_reason_unemployment);
            }
        } else {
            c.add(p.workers_needed, e_prosperity_reason_workers_needed);
        }

        if (in.food_types < p.food_types_min) {
            c.change += p.few_food_types_change;
        }

        bool wage_done = false;
        for (size_t i = 0; i < p.wage_above.size() && i < p.wage_above_changes.size() && !wage_done; ++i) {
            if (in.wages >= p.wage_above[i]) {
                c.change += p.wage_above_changes[i];
                wage_done = true;
            }
        }
        for (size_t i = 0; i < p.wage_below.size() && i < p.wage_below_changes.size() && !wage_done; ++i) {
            if (in.wages < p.wage_below[i]) {
                c.add(p.wage_below_changes[i], e_prosperity_reason_wages);
                wage_done = true;
            }
        }

        if (in.huts_share > p.huts_share) {
            c.add(p.huts_change, e_prosperity_reason_too_many_huts);
        }
        if (in.manors_share > p.manors_share) {
            c.change += p.manors_change;
        }
        if (in.tribute_not_paid) {
            c.add(p.tribute_not_paid_change, e_prosperity_reason_tribute_not_paid);
        }
        if (in.senet_shows) {
            c.change += p.senet_change;
        }
        if (in.completed_monument) {
            c.change += p.completed_monument_change;
        }
        return c;
    }

} // namespace

bool city_t::is_prosperity_update_month(int month) const {
    for (const int m : prosperity_rating.months) {
        if (m == month) {
            return true;
        }
    }
    return false;
}

void city_t::update_prosperity_rating() {
    const prosperity_inputs in = collect_prosperity_inputs(*this);
    const int change = prosperity_change(in, in.construction_last_year).change;

    ratings.prosperity += change;
    if (ratings.prosperity_max < ratings.prosperity) {
        ratings.prosperity = ratings.prosperity_max;
    }
    ratings.prosperity = calc_bound(ratings.prosperity, 0, 100);

    update_prosperity_explanation();
}

// OG city_ratings_prosperity_explanation: the trend of the change and its most severe reason.
void city_t::update_prosperity_explanation() {
    const prosperity_inputs in = collect_prosperity_inputs(*this);
    const prosperity_change_t c = prosperity_change(in, in.construction_this_year);
    const int change = c.change;

    if (change == 0 || (ratings.prosperity < 1 && game.simtime.year == g_scenario.start_year)) {
        ratings.prosperity_explanation = e_prosperity_reason_none;
        ratings.prosperity_trend = e_prosperity_same;
        return;
    }

    if (change < 1) {
        ratings.prosperity_trend = e_prosperity_falling;
        ratings.prosperity_explanation = c.reason;
        return;
    }

    ratings.prosperity_trend = e_prosperity_rising;
    const int max = ratings.prosperity_max;
    if ((ratings.prosperity + change) <= max) {
        ratings.prosperity_explanation = (c.severity == 0) ? e_prosperity_reason_none : c.reason;
        return;
    }

    if (ratings.prosperity <= max) {
        ratings.prosperity_trend = (max <= ratings.prosperity) ? e_prosperity_same : e_prosperity_rising;
        ratings.prosperity_explanation = e_prosperity_reason_at_cap;
        return;
    }

    ratings.prosperity_trend = e_prosperity_falling;
    ratings.prosperity_explanation = e_prosperity_reason_at_cap;
}

// OG city_ratings_prosperity_cap: the house models' prosperity weighted by the people living in them.
void city_t::calculate_max_prosperity() {
    int total = 0;
    int people = 0;
    for (int i = 1; i < MAX_BUILDINGS; i++) {
        auto house = building_get(i)->dcast_house();
        if (house && house->state() != BUILDING_STATE_UNUSED && house->hsize()) {
            const int population = house->house_population();
            total += house->model().prosperity * population;
            people += population;
        }
    }

    ratings.prosperity_max = (people > 0) ? (total / people) : 0;
}
