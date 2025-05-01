#include "settings_vars.h"

#include <unordered_map>
#include <optional>

#include "content/vfs.h"
#include "core/log.h"
#include "js/js_game.h"
#include "mujs/mujs.h"


class settings_vars_impl_t {
	friend class settings_vars_t;
	settings_vars_impl_t() {
	}

	using variants_map_t = std::unordered_map<xstring, setting_variant>;

public:
	void reset() {
		if (!_initialized) {
			return;
		}
		_initialized = false;
	}

	size_t get_count() {
		return _variants.size();
	}

	void sync_global(pcstr filename, pcstr name) {
		save_global(filename, name);
	}

	void set_autosync_delay(const settings_vars_t::delay_t delay) {
		bool forceSync = false;
		{
			forceSync = (delay < _storageSyncDelay);
			_storageSyncDelay = delay;
		}

		if (forceSync) {
			//_backgroundQueueExecutor->Force();
		}
	}

	bool is_defined(xstring name) {
		return _variants.find(name) != _variants.end();
	}

	std::optional<setting_variant> get_variant(const xstring &name) {
		auto it = _variants.find(name);
		if (it == _variants.end()) {
			return {};
		}
		return it->second;
	}

	setting_variant get(const xstring &name, const setting_variant &def) {
		auto it = _variants.find(name);
		if (it == _variants.end()) {
			return def;
		}

		return it->second;
	}

	template<typename T>
	std::optional<T> get(const xstring &name) {
		auto it = _variants.find(name);
		if (it == _variants.end()) {
			return {};
		}

		if (!std::holds_alternative<T>(it->second)) {
		    return {};
        }

		return std::get<T>(it->second);
	}

	template<typename T>
	void set(const xstring &name, const T& value) {
		auto it = _variants.find(name);
		if (it != _variants.end()) {
			if (it->second == setting_variant(value)) {
				return;
			}
		}

		_variantsDirty = true;
		_variants[name] = setting_variant(value);
		if (_sync_task) {
            _sync_task(name);
        }
		sync_with_js(name, _variants[name]);
	}

	void sync_with_js(const xstring &name, const setting_variant& value) {
		switch (value.index()) {
		case setting_bool:
			g_config_arch.w_property("game_settings", name.c_str(), std::get<bool>(value));
			break;

		case setting_float:
			g_config_arch.w_property("game_settings", name.c_str(), std::get<float>(value));
			break;

		case setting_vec2i:
            g_config_arch.w_property("game_settings", name.c_str(), std::get<vec2i>(value));
            break;

		case setting_string:
            g_config_arch.w_property("game_settings", name.c_str(), std::get<xstring>(value));
            break;
		}
	}

	void initialize() {
		_initialized = true;
		_variantsDirty = false;

		g_config_arch.r_objects("game_settings", [&] (pcstr key, archive arch) {
			auto value = arch.to_variant();
			switch (value.index()) {
			case archive::e_variant_type::vt_none:
				// logs::error("Unable to load settings %s", key);
				break;

			case archive::e_variant_type::vt_float:
				{
                    float val = std::get<float>(value);
                    set(key, val);
                }
				break;

			case archive::e_variant_type::vt_bool:
				{
                    bool val = std::get<bool>(value);
                    set(key, val);
                }
				break;

			case archive::e_variant_type::vt_string:
				{
                    xstring val = std::get<xstring>(value);
                    set(key, val);
                }
				break;
					
			case archive::e_variant_type::vt_vec2i:
				{
					vec2i val = std::get<vec2i>(value);
					set(key, val);
				}
				break;

			case archive::e_variant_type::vt_array:
				break;

			case archive::e_variant_type::vt_object:
				{
					
				}
				break;
			}
		});		
	}

	static inline std::string svardata;
	static void svarprintf(js_State *state, const char* v) {
		svardata.append(v);
    }

	void save_global(pcstr filename, pcstr name) {
		if (!_variantsDirty) {
			return;
		}

		vfs::path fs_file = vfs::content_path(filename);
		FILE *fp = vfs::file_open_os(fs_file, "wt");
		if (!fp) {
			logs::error("Unable to write settings file %s", fs_file.c_str());
			return;
		}

		svardata = "log_info(\"akhenaten: akhenaten.conf started\")\n";
		svardata.append("var game_settings = ");

		js_State *state = (js_State *)g_config_arch.state;
		js_setdumping(state, &svarprintf);
		js_getglobal(state, name);
		if (js_isobject(state, -1)) {
			js_dumpobject_ex(state, -1);
		}
		js_pop(state, 1);

		fprintf(fp, "%s", svardata.c_str());
		svardata.clear();
		_variantsDirty = false;
			
		vfs::file_close(fp);
	}

private:
	settings_vars_t::delay_t _storageSyncDelay = std::chrono::milliseconds(100);

	variants_map_t _variants;
	bool _variantsDirty = false;
	bool _syncScheduled = false;
	bool _initialized = false;
	std::function<void(xstring)> _sync_task;
};

settings_vars_t::settings_vars_t() {
	static_assert(sizeof(settings_vars_impl_t) <= sizeof(_data), "settings_vars_t size is not 608 bytes");
	_impl = new(_data) settings_vars_impl_t();
}

bool settings_vars_t::is_defined(const xstring &name) {
	return impl().is_defined(name);
}

void settings_vars_t::init() {
	impl().initialize();
}

setting_variant_type settings_vars_t::type(const xstring &name) {
	auto var = impl().get_variant(name);
	return (var.has_value() ? (setting_variant_type)var.value().index() : setting_none);
}

void settings_vars_t::sync_global(pcstr filename, pcstr name) {
	impl().sync_global(filename, name);
}

void settings_vars_t::set_sync_task(std::function<void(xstring)> task) {
	impl()._sync_task = task;
}

void settings_vars_t::set_autosync_delay(const delay_t delay) {
	(void)delay;
}

bool settings_vars_t::get_bool(const xstring &name, bool def) {
	auto v = impl().get<bool>(name);
	return v.value_or(def);
}

void settings_vars_t::set_bool(const xstring &name, bool value) {
	impl().set(name, value);
}

int settings_vars_t::get_int(const xstring &name, int def) {
	auto v = impl().get<float>(name);
	return int(v.value_or(def));
}

void settings_vars_t::set_int(const xstring &name, int value) {
	float v = float(value);
	impl().set(name, v);
}

int64_t settings_vars_t::get_int64(const xstring &name, int64_t def) {
	auto v = impl().get<float>(name);
	return int64_t(v.value_or(def));
}

void settings_vars_t::set_int64(const xstring &name, int64_t value) {
	float v = float(value);
	impl().set(name, v);
}

float settings_vars_t::get_float(const xstring &name, float def) {
	auto v = impl().get<float>(name);
	return v.value_or(def);
}

void settings_vars_t::set_float(const xstring &name, float value) {
	impl().set(name, value);
}

void settings_vars_t::set(const xstring &name, const setting_variant &value) {
    impl().set(name, value);
}

setting_variant settings_vars_t::get(const xstring &name, const setting_variant &def) {
	return impl().get(name, def);
}

xstring settings_vars_t::get_string(const xstring &name, const xstring &def) {
	auto v = impl().get<xstring>(name);
	return v.value_or(def);
}

void settings_vars_t::set_string(const xstring &name, const xstring &value) {
	impl().set(name, value);
}