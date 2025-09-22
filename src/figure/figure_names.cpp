#include "figure/figure_names.h"
#include "io/io_buffer.h"

#include "core/random.h"

struct figure_name_data_t {
    int32_t citizen_male;
    int32_t nobles;
    int32_t citizen_female;
    int32_t tax_collector;
    int32_t engineer;
    int32_t fireman;
    int32_t javelin_thrower;
    int32_t cavalry;
    int32_t legionary;
    int32_t juggler;
    int32_t musician;
    int32_t dancer;
    int32_t senet_player;
    int32_t enemy_barbarian;
    int32_t enemy_assyrian;
    int32_t enemy_canaanite;
    int32_t enemy_egyptian;
    int32_t enemy_hittite;
    int32_t enemy_hyksos;
    int32_t enemy_kushite;
    int32_t enemy_libian;
    int32_t enemy_nubian;
    int32_t enemy_persian;
    int32_t enemy_phoenician;
    int32_t enemy_roman;
    int32_t enemy_seapeople;
    int32_t trader;
    int32_t ship;
    int32_t warship;
    int32_t enemy_warship;
};

figure_name_data_t g_figure_name_data;

static int8_t init_name() {
    random_generate_next();
    return random_byte() & 0xf;
}

void figure_name_init() {
    auto &data = g_figure_name_data;
    data.citizen_male = init_name();
    data.nobles = init_name();
    data.citizen_female = init_name();
    data.tax_collector = init_name();
    data.engineer = init_name();
    data.fireman = init_name();
    data.javelin_thrower = init_name();
    data.cavalry = init_name();
    data.legionary = init_name();
    data.juggler = init_name();
    data.musician = init_name();
    data.dancer = init_name();
    data.senet_player = init_name();
    data.enemy_barbarian = init_name();
    data.enemy_assyrian = init_name();
    data.enemy_canaanite = init_name();
    data.enemy_egyptian = init_name();
    data.enemy_hittite = init_name();
    data.enemy_hyksos = init_name();
    data.enemy_kushite = init_name();
    data.enemy_libian = init_name();
    data.enemy_nubian = init_name();
    data.enemy_persian = init_name();
    data.enemy_phoenician = init_name();
    data.enemy_roman = init_name();
    data.enemy_seapeople = init_name();
    data.trader = init_name();
    data.ship = init_name();
    data.warship = init_name();
    data.enemy_warship = init_name();
}

static int get_next_name(int32_t& field, int offset, int max) {
    int name = offset + field;
    field = field + 1;
    if (field >= max) {
        field = 0;
    }

    return name;
}

int figure_name_get(int type, int enemy) {
    auto &data = g_figure_name_data;
    switch (type) {
    case FIGURE_TAX_COLLECTOR:
        return get_next_name(data.tax_collector, 132, 32);

    case FIGURE_ARCHITECT:
        return get_next_name(data.engineer, 165, 32);

    case FIGURE_FIREMAN:
    case FIGURE_TOWER_SENTRY:
        return get_next_name(data.fireman, 198, 32);

    case FIGURE_JUGGLER:
        return get_next_name(data.juggler, 330, 32);

    case FIGURE_MUSICIAN:
        return get_next_name(data.musician, 363, 32);

    case FIGURE_DANCER:
        return get_next_name(data.dancer, 396, 16);

    case FIGURE_SENET_PLAYER:
        return get_next_name(data.senet_player, 413, 16);

    case FIGURE_TRADE_CARAVAN:
    case FIGURE_TRADE_CARAVAN_DONKEY:
        return get_next_name(data.trader, 562, 16);

    case FIGURE_TRADE_SHIP:
    case FIGURE_FISHING_BOAT:
        return get_next_name(data.ship, 579, 16);

    case FIGURE_MARKET_TRADER:
    case FIGURE_MARKET_BUYER:
        return get_next_name(data.citizen_female, 99, 32);

    case FIGURE_SCRIBER:
    case FIGURE_DELIVERY_BOY:
    case FIGURE_HERBALIST:
    case FIGURE_WATER_CARRIER:
    case FIGURE_WORKER:
    default:
        return get_next_name(data.citizen_male, 1, 64);

    case FIGURE_PRIEST:
    case FIGURE_TEACHER:
    case FIGURE_MISSIONARY:
    case FIGURE_LIBRARIAN:
    case FIGURE_EMBALMER:
    case FIGURE_PHYSICIAN:
    case FIGURE_NOBLES:
        return get_next_name(data.nobles, 66, 32);

    case FIGURE_ARCHER:
    case FIGURE_ENEMY_KINGDOME_JAVELIN:
        return get_next_name(data.javelin_thrower, 231, 32);

    case FIGURE_FCHARIOTEER:
    case FIGURE_ENEMY_KINGDOME_MOUNTED:
        return get_next_name(data.cavalry, 264, 32);

    case FIGURE_INFANTRY:
    case FIGURE_ENEMY_KINGDOME_INFANTRY:
        return get_next_name(data.legionary, 297, 32);

    case FIGURE_INDIGENOUS_NATIVE:
    case FIGURE_NATIVE_TRADER:
        return get_next_name(data.enemy_barbarian, 430, 32);

    case FIGURE_ENEMY_EGYPTIAN_SPEAR:
    case FIGURE_ENEMY_EGYPTIAN_SWORD:
    case FIGURE_ENEMY_EGYPTIAN_FAST_SWORD:
    case FIGURE_ENEMY_EGYPTIAN_CAMEL:
    case FIGURE_ENEMY_EGYPTIAN_ELEPHANT:
    case FIGURE_ENEMY_EGYPTIAN_CHARIOT:
    case FIGURE_ENEMY_EGYPTIAN_FAST_SPEAR:
    case FIGURE_ENEMY_EGYPTIAN_HEAVY_SWORD:
    case FIGURE_ENEMY_EGYPTIAN_HEAVY_SPEAR:
    case FIGURE_ENEMY_EGYPTIAN_MOUNTED_ARCHER:
    case FIGURE_ENEMY_EGYPTIAN_AXE:
        switch (enemy) {
        //case ENEMY_8_GREEK:
        //    return get_next_name(&data.enemy_greek, 463, 32);

        case ENEMY_3_EGYPTIAN:
            return get_next_name(data.enemy_egyptian, 496, 32);

        //case ENEMY_1_NUMIDIAN:
        //case ENEMY_5_PERGAMUM:
        //case ENEMY_10_CARTHAGINIAN:
        //    return get_next_name(&data.enemy_arabian, 529, 32);

        //case ENEMY_7_ETRUSCAN:
        //    return get_next_name(&data.fireman, 198, 32);

        default:
            return get_next_name(data.enemy_barbarian, 430, 32);
        }

    case FIGURE_EXPLOSION:
    case FIGURE_STANDARD_BEARER:
    case FIGURE_FISHING_POINT:
    case FIGURE_FISHING_SPOT:
    case FIGURE_CREATURE:
    case FIGURE_CHARIOR_RACER:
        return 0;
    }
}

io_buffer* iob_figure_names = new io_buffer([](io_buffer* iob, size_t version) {
    auto &data = g_figure_name_data;
    iob->bind(BIND_SIGNATURE_INT32, &data.citizen_male);
    iob->bind(BIND_SIGNATURE_INT32, &data.nobles);
    iob->bind(BIND_SIGNATURE_INT32, &data.citizen_female);
    iob->bind(BIND_SIGNATURE_INT32, &data.tax_collector);
    iob->bind(BIND_SIGNATURE_INT32, &data.engineer);
    iob->bind(BIND_SIGNATURE_INT32, &data.fireman);
    iob->bind(BIND_SIGNATURE_INT32, &data.javelin_thrower);
    iob->bind(BIND_SIGNATURE_INT32, &data.cavalry);
    iob->bind(BIND_SIGNATURE_INT32, &data.legionary);
    iob->bind(BIND_SIGNATURE_INT32, &data.juggler);
    iob->bind(BIND_SIGNATURE_INT32, &data.musician);
    iob->bind(BIND_SIGNATURE_INT32, &data.dancer);
    iob->bind(BIND_SIGNATURE_INT32, &data.senet_player);
    iob->bind(BIND_SIGNATURE_INT32, &data.enemy_barbarian);
    iob->bind(BIND_SIGNATURE_INT32, &data.enemy_assyrian);
    iob->bind(BIND_SIGNATURE_INT32, &data.enemy_egyptian);
    iob->bind(BIND_SIGNATURE_INT32, &data.enemy_canaanite);
    iob->bind(BIND_SIGNATURE_INT32, &data.trader);
    iob->bind(BIND_SIGNATURE_INT32, &data.ship);
    iob->bind(BIND_SIGNATURE_INT32, &data.warship);
    iob->bind(BIND_SIGNATURE_INT32, &data.enemy_warship);
});