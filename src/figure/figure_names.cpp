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

static int8_t init_name() {
    random_generate_next();
    return random_byte() & 0xf;
}

void figure_name_init() {
    for (auto &t : figure_names) {
        t.id = init_name();
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

    // Otherwise use predefined names
    if (!figure_name.names.empty()) {
        figure_name.id = rand() % figure_name.names.size();
        return figure_name.names[figure_name.id].c_str();
    }

    // If we have parts for generation, create name from three parts
    if (figure_name.names.empty() && 
        !figure_name.prefixes.empty() && 
        !figure_name.middles.empty() && 
        !figure_name.postfixes.empty()) {
        
        bstring32 generated_name = figure_name_generator.get_name(figure_name.prefixes, figure_name.prefixes, figure_name.postfixes);
        
        return generated_name;
    }

    return figure_name_generator.get_male_name();
}

io_buffer* iob_figure_names = new io_buffer([](io_buffer* iob, size_t version) {
    int tmp;
    iob->bind(BIND_SIGNATURE_INT32, &tmp);
    iob->bind(BIND_SIGNATURE_INT32, &tmp);
    iob->bind(BIND_SIGNATURE_INT32, &tmp);
    iob->bind(BIND_SIGNATURE_INT32, &tmp);
    iob->bind(BIND_SIGNATURE_INT32, &tmp);
    iob->bind(BIND_SIGNATURE_INT32, &tmp);
    iob->bind(BIND_SIGNATURE_INT32, &tmp);
    iob->bind(BIND_SIGNATURE_INT32, &tmp);
    iob->bind(BIND_SIGNATURE_INT32, &tmp);
    iob->bind(BIND_SIGNATURE_INT32, &tmp);
    iob->bind(BIND_SIGNATURE_INT32, &tmp);
    iob->bind(BIND_SIGNATURE_INT32, &tmp);
    iob->bind(BIND_SIGNATURE_INT32, &tmp);
    iob->bind(BIND_SIGNATURE_INT32, &tmp);
    iob->bind(BIND_SIGNATURE_INT32, &tmp);
    iob->bind(BIND_SIGNATURE_INT32, &tmp);
    iob->bind(BIND_SIGNATURE_INT32, &tmp);
    iob->bind(BIND_SIGNATURE_INT32, &tmp);
    iob->bind(BIND_SIGNATURE_INT32, &tmp);
    iob->bind(BIND_SIGNATURE_INT32, &tmp);
    iob->bind(BIND_SIGNATURE_INT32, &tmp);
});