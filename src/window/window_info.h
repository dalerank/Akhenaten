#pragma once

#include "grid/point.h"
#include "city/city.h"
#include "core/variant.h"
#include "graphics/elements/ui.h"

struct object_info;
struct tooltip_context;

struct common_info_window : public ui::widget {
    virtual pcstr section() const { return ""; }
    virtual bool check(object_info &c) { return false; }
    virtual int get_height_id(object_info &c) { return 0; }
    virtual void window_info_background(object_info &c) { update_buttons(c); }
    virtual void window_info_foreground(object_info &c);
    virtual int window_info_handle_mouse(const mouse *m, object_info &c) { return 0; }
    virtual textid get_tooltip(object_info &c) { return {0, 0}; }
    virtual void update_buttons(object_info &c);

    using widget::load;
    virtual void load(archive arch, pcstr section) override;
    virtual void init(object_info &c);

    void draw_tooltip(tooltip_context *c);

    static int backside_texture;

    template<typename T>
    bstring1024 format(const T *o, pcstr fmt) {
        if (!fmt || !*fmt) {
            return {};
        }

        struct kv {
            bstring64 key;
            bstring1024 value;
            pstr data() { return key.data(); }
            kv &operator=(pcstr v) { key = v; return *this; }
            void resize(size_t s) { key.resize(s); }
            pcstr c_str() const { return key.c_str(); }
        };
        svector<kv, 32> items;

        const char *start = fmt;
        while ((start = strstr(start, "${")) != NULL) {  // Find the start of "${"
            const char *end = ::strchr(start, '}'); // Find the closing '}'
            if (end != NULL) {
                const int length = end - start + 1;

                auto &item = items.emplace_back();
                item.key.ncat(start, length);

                // Move the pointer past the current block
                start = end + 1;
            } else {
                break; // Exit if no closing '}' is found
            }
        }

        for (auto &item : items) {
            if (strncmp(item.key, "${", 2) != 0) {
                continue;
            }

            pcstr scopeend = item.key.strchr('}');
            if (scopeend == nullptr) {
                continue;
            }

            item.key.resize(scopeend - item.key + 1);

            int group, id;
            uint32_t args_handled = sscanf(item.key.c_str(), "${%d.%d}", &group, &id);
            if (args_handled == 2) {
                item.value = ui::str(group, id);
                continue;
            }

            bstring128 loc("#");
            args_handled = sscanf(item.key.c_str(), "${loc.%[^}]}", loc.data() + 1);
            if (args_handled == 1) {
                item.value = lang_text_from_key(loc.c_str());
                continue;
            }

            bstring128 domain, prop;
            args_handled = sscanf(item.key.c_str(), "${%[^.].%[^}]}", domain.data(), prop.data());
            if (args_handled == 2) {
                bvariant bvar = o->get_property(xstring(domain), xstring(prop));
                if (bvar.is_empty()) {
                    bvar = city_get_property(xstring(domain), xstring(prop));
                }

                if (!bvar.is_empty()) {
                    item.value = bvar.to_str();
                }
            }
        }

        bstring1024 result = fmt;
        for (const auto &item : items) {
            if (item.value.len()) {
                result.replace_str(item.key, item.value);
            }
        }

        return result;
    }
};

void window_info_show(const tile2i& point, bool avoid_mouse = false);
int window_building_info_get_type();
void window_building_info_show_storage_orders();
void window_building_register_handler(common_info_window *handler);
void window_figure_register_handler(common_info_window *handler);