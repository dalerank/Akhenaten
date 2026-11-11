#include "figure/figure_names.h"
#include "io/io_buffer.h"
#include "js/js_game.h"
#include "core/random.h"
#include "core/stable_array.h"

using bstring32_vec = std::vector<bstring32>;
template<> inline void archive::r<bstring32_vec>(pcstr name, bstring32_vec &v) { r_array_str(name, v); }

struct random_names_t { 
    e_figure_type type;
    bstring32_vec names;
    bstring32_vec prefixes;
    bstring32_vec middles;
    bstring32_vec postfixes;
    bool empty_name;
    uint32_t id;
};
ANK_CONFIG_STRUCT(random_names_t, type, names, prefixes, middles, postfixes, empty_name)

struct figure_name_generator_t {
    bstring32_vec prefixes;
    bstring32_vec middles;
    bstring32_vec male_postfixes;
    bstring32_vec female_postfixes;

    template<typename T>
    bstring32 get_name(const T& p, const T& m, const T& f) {
        int prefix_idx = rand() % p.size();
        int middle_idx = rand() % m.size();
        int postfix_idx = rand() % f.size();

        bstring32 generated_name;
        generated_name.printf("%s%s%s", p[prefix_idx].c_str(), m[middle_idx].c_str(), f[postfix_idx].c_str());

        return generated_name;
    } 

    bstring32 get_male_name() {
        return get_name(prefixes, middles, male_postfixes);
    }

    bstring32 get_female_name() {
        return get_name(prefixes, middles, female_postfixes);
    }
};
ANK_CONFIG_STRUCT(figure_name_generator_t, prefixes, middles, male_postfixes, female_postfixes)

template<>
struct stable_array_max_elements<random_names_t> {
    enum { max_elements = FIGURE_MAX };
};

template<>
struct std::hash<random_names_t> {
    [[nodiscard]] size_t operator()(const random_names_t &g) const noexcept {
        return g.type;
    }
};

stable_array<random_names_t> ANK_VARIABLE(figure_names);
figure_name_generator_t ANK_VARIABLE(figure_name_generator);

enum {
    FIGURE_NAME_COUNTERS = 41,
    FIGURE_NAME_GROUP_FIRST = 254,
    FIGURE_NAME_GROUP_COUNTER_BASE = 294,
    FIGURE_NAME_GROUP_ENEMY_EXTRA_FIRST = 300,
    FIGURE_NAME_GROUP_ENEMY_EXTRA_LAST = 303,
    FIGURE_NAME_COUNTER_MASK = 0xF,
    FIGURE_NAME_SAVED_SLOT_FIRST = 40,
    FIGURE_NAME_SAVED_SLOT_LAST = 20,
};

struct figure_name_group_t {
    int type;
    int16_t group;
    int16_t count;
};

static int32_t g_figure_name_counters[FIGURE_NAME_COUNTERS];

// OG figure_core.c figure_name_groups. Keyed by the save-compatible type id: 54..56 are OG ENEMY_EGYPTIAN_*.
static const figure_name_group_t og_name_groups[] = {
  {FIGURE_IMMIGRANT, 0xFE, 0x80},
  {FIGURE_EMIGRANT, 0xFE, 0x80},
  {FIGURE_HOMELESS, 0xFF, 0x20},
  {FIGURE_CART_PUSHER, 0xFE, 0x80},
  {FIGURE_LABOR_SEEKER, 0xFE, 0x80},
  {FIGURE_TAX_COLLECTOR, 0x115, 0x10},
  {FIGURE_ARCHITECT, 0x113, 0x10},
  {FIGURE_STORAGEYARD_CART, 0xFE, 0x80},
  {FIGURE_FIREMAN, 0x112, 0x10},
  {FIGURE_JUGGLER, 0x107, 0x20},
  {FIGURE_MUSICIAN, 0x108, 0x20},
  {FIGURE_DANCER, 0x109, 0x10},
  {FIGURE_SENET_PLAYER, 0x107, 0x20},
  {FIGURE_TRADE_CARAVAN, 0x106, 0x10},
  {FIGURE_TRADE_SHIP, 0x105, 0x10},
  {FIGURE_TRADE_CARAVAN_DONKEY, 0x106, 0x10},
  {FIGURE_PROTESTER, 0x100, 0x10},
  {FIGURE_ROBBER, 0x100, 0x10},
  {FIGURE_MARKET_TRADER, 0x103, 0x20},
  {FIGURE_TEACHER, 0x10F, 0x20},
  {FIGURE_LIBRARIAN, 0x10F, 0x20},
  {FIGURE_DENTIST, 0x110, 0x20},
  {FIGURE_PHYSICIAN, 0x110, 0x20},
  {FIGURE_HERBALIST, 0x110, 0x20},
  {FIGURE_EMBALMER, 0x111, 0x10},
  {FIGURE_WORKER, 0xFE, 0x80},
  {FIGURE_DOCKER, 0xFE, 0x80},
  {FIGURE_MARKET_BUYER, 0x103, 0x20},
  {FIGURE_NOBLES, 0x101, 0x20},
  {FIGURE_TOWER_SENTRY, 0x118, 0x20},
  {FIGURE_RIOTER, 0xFE, 0x80},
  {FIGURE_ENEMY_KINGDOME_JAVELIN, 0xFE, 0x80},
  {FIGURE_ENEMY_KINGDOME_MOUNTED, 0xFE, 0x80},
  {FIGURE_DELIVERY_BOY, 0x104, 0x10},
  {FIGURE_OSTRICH_HUNTER, 0x102, 0x10},
  {FIGURE_LUMBERJACK, 0xFE, 0x80},
  {FIGURE_FERRY_BOAT, 0x117, 0x10},
  {FIGURE_CARPENTER, 0xFE, 0x80},
  {FIGURE_BRICKLAYER, 0xFE, 0x80},
  {FIGURE_STONEMASON, 0xFE, 0x80},
  {FIGURE_LABORER, 0xFE, 0x80},
  {FIGURE_WATER_CARRIER, 0xFE, 0x80},
  {FIGURE_CONSTABLE, 0x114, 0x10},
  {FIGURE_MAGISTRATE, 0x116, 0x10},
  {FIGURE_REED_GATHERER, 0xFE, 0x80},
  {FIGURE_ENEMY_TRANSPORT, 0x121, 0x10},
  {FIGURE_ENEMY_WARSHIP, 0x121, 0x10},
  {FIGURE_SLED_PULLER, 0xFE, 0x80},
  {FIGURE_PLAGUED_CITIZEN, 0xFE, 0x80},
  {FIGURE_BEDOUIN_INFANTRY, 0x122, 0x10},
  {FIGURE_EGYPTIAN_WARSHIP, 0x121, 0x10},
  {FIGURE_EGYPTIAN_TRANSPORT, 0x121, 0x10},
  {FIGURE_ZOOKEEPER, 0x107, 0x20},
  {FIGURE_TOMB_ARTISAN, 0xFE, 0x80},
};

static figure_name_group_t og_name_group(int type) {
    for (const auto& g : og_name_groups) {
        if (g.type == type) {
            return g;
        }
    }
    return {type, 0, 0};
}

static int32_t* og_name_counter(int16_t group) {
    const bool regular = group >= FIGURE_NAME_GROUP_FIRST && group <= FIGURE_NAME_GROUP_COUNTER_BASE;
    const bool enemy_extra
      = group >= FIGURE_NAME_GROUP_ENEMY_EXTRA_FIRST && group <= FIGURE_NAME_GROUP_ENEMY_EXTRA_LAST;
    if (regular) {
        return &g_figure_name_counters[FIGURE_NAME_GROUP_COUNTER_BASE - group];
    }
    if (enemy_extra) {
        return &g_figure_name_counters[FIGURE_NAME_GROUP_ENEMY_EXTRA_LAST - group];
    }
    return nullptr;
}

// OG figure_name_set: hand out the group's counter value, then step it with wrap at the group size.
static int og_name_next(int type) {
    const figure_name_group_t g = og_name_group(type);
    int32_t* counter = g.count > 0 ? og_name_counter(g.group) : nullptr;
    if (!counter) {
        return -1;
    }
    const int32_t name = *counter;
    *counter = (name + 1) < g.count ? name + 1 : 0;
    return name;
}

int figure_name_counter(int slot) {
    return (slot >= 0 && slot < FIGURE_NAME_COUNTERS) ? g_figure_name_counters[slot] : -1;
}

int figure_name_counter_slot(int type) {
    const figure_name_group_t g = og_name_group(type);
    int32_t* counter = g.count > 0 ? og_name_counter(g.group) : nullptr;
    return counter ? (int)(counter - g_figure_name_counters) : -1;
}

void figure_name_init() {
    // OG scenario_start.c figure_name_init: slots seeded high to low, one crt_rand each.
    for (int i = FIGURE_NAME_COUNTERS - 1; i >= 0; i--) {
        g_figure_name_counters[i] = anti_scum_random_15bit() & FIGURE_NAME_COUNTER_MASK;
    }
    for (auto &t : figure_names) {
        t.id = 0;
    }
}

int figure_get_next_name(int32_t& field, int offset, int max) {
    int name = offset + field;
    field = field + 1;
    if (field >= max) {
        field = 0;
    }

    return name;
}

bstring32 figure_name_get(int type) {
    auto &figure_name = figure_names[type];
    
    if (figure_name.empty_name) {
        return 0;
    }

    const int og_name = og_name_next(type);

    if (!figure_name.names.empty()) {
        const uint32_t count = (uint32_t)figure_name.names.size();
        if (og_name >= 0) {
            figure_name.id = (uint32_t)og_name % count;
        } else {
            figure_name.id = (figure_name.id + 1) % count;
        }
        return figure_name.names[figure_name.id].c_str();
    }

    // If we have parts for generation, create name from three parts
    if (figure_name.names.empty() && 
        !figure_name.prefixes.empty() && 
        !figure_name.middles.empty() && 
        !figure_name.postfixes.empty()) {
        
        bstring32 generated_name = figure_name_generator.get_name(figure_name.prefixes, figure_name.middles, figure_name.postfixes);
        
        return generated_name;
    }

    return figure_name_generator.get_male_name();
}

// OG io_data.c: this 84-byte chunk holds counter slots 40 down to 20 (groups 254..274). Slots 0..3 and 4..19
// live in other OG chunks that are not bound here yet.
io_buffer* iob_figure_names = new io_buffer([](io_buffer* iob, size_t version) {
    for (int slot = FIGURE_NAME_SAVED_SLOT_FIRST; slot >= FIGURE_NAME_SAVED_SLOT_LAST; slot--) {
        iob->bind(BIND_SIGNATURE_INT32, &g_figure_name_counters[slot]);
    }
});