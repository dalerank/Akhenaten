#pragma once

#include "core/archive.h"
class building_impl;

namespace buildings {

    typedef building_impl *(*create_building_function_cb)(e_building_type, building &);
    typedef void (*load_building_static_params_cb)();

    using BuildingCtorIterator = FuncLinkedList<create_building_function_cb>;
    using BuildingParamIterator = FuncLinkedList<load_building_static_params_cb>;

    template<typename T>
    struct model_t {
        using building_type = T;
        static constexpr e_building_type TYPE = T::TYPE;
        static constexpr pcstr CLSID = T::CLSID;

        static typename T::static_params &static_params() {
            static typename T::static_params _instance;
            return _instance;
        }

        model_t() {
            static_params().name = CLSID;
            static_params().type = TYPE;

            static BuildingCtorIterator ctor_handler(&create);
            static BuildingParamIterator static_params_handler(&static_params_load);

            static typename T::preview planer_renderer;

            building_static_params::register_model(TYPE, static_params());
            building_planer_renderer::register_model(TYPE, planer_renderer);
        }

        static void static_params_load() {
            building_static_params &base = building_static_params::ref(TYPE);

            const bool loaded = g_config_arch.r(CLSID, base);
            assert(loaded);

            g_config_arch.r(CLSID, static_params());

            base.initialize();
        }

        static building_impl *create(e_building_type e, building &b) {
            if (e == TYPE) {
                return b.template acquire_impl<building_type>();
            }
            return nullptr;
        }
    };

} // buildings