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
	size_t get_count() {
		return _variants.size();
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

		_variants[name] = setting_variant(value);
		if (_sync_task) {
            _sync_task(name);
        }
	}

	const variants_map_t& get_variants() const {
		return _variants;
	}

private:
	variants_map_t _variants;
	std::function<void(xstring)> _sync_task;
};

settings_vars_t::settings_vars_t() {
	static_assert(sizeof(settings_vars_impl_t) <= sizeof(_data), "settings_vars_t size is not 88 bytes");
	_impl = new(_data) settings_vars_impl_t();
}

bool settings_vars_t::is_defined(const xstring &name) {
	return impl().is_defined(name);
}

void settings_vars_t::clear() {
	impl()._variants.clear();
}

setting_variant_type settings_vars_t::type(const xstring &name) {
	auto var = impl().get_variant(name);
	return (var.has_value() ? (setting_variant_type)var.value().index() : setting_none);
}

void settings_vars_t::set_sync_task(std::function<void(xstring)> task) {
	impl()._sync_task = task;
}

void settings_vars_t::foreach_vars(std::function<void(xstring, const setting_variant &)> task) {
	for (const auto& it: impl()._variants) {
		task(it.first, it.second);
	}
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

void settings_vars_t::insert(const settings_vars_t &vars) {
	for (const auto &v : vars.impl()._variants) {
		impl()._variants.insert({ v.first, v.second });
	}
}

std::string settings_vars_t::save() const {
	std::string result;
	result.reserve(1024);
	
	for (const auto& [key, value] : impl().get_variants()) {
		result += key.c_str();
		result += "=";
		
		switch (value.index()) {
		case setting_bool: {
				result += "b:";
				result += std::get<bool>(value) ? "1" : "0";
				break;
			}
		case setting_float: {
				result += "f:";
				result += std::to_string(std::get<float>(value));
				break;
			}
		case setting_vec2i: {
				const vec2i& v = std::get<vec2i>(value);
				result += "v:";
				result += std::to_string(v.x);
				result += ",";
				result += std::to_string(v.y);
				break;
			}
		case setting_string: {
				const xstring& s = std::get<xstring>(value);
				result += "s:";
				for (size_t i = 0; i < s.size(); ++i) {
					char c = s.c_str()[i];
					if (c == '\\' || c == '\n' || c == '=') {
						result += '\\';
					}
					result += c;
				}
				break;
			}
		}
		result += "\n";
	}
	
	return result;
}

void settings_vars_t::load(const std::string& data) {
	if (data.empty()) {
		return;
	}
	
	size_t pos = 0;
	size_t line_start = 0;
	
	while (pos <= data.size()) {
		fixed_memory_resource<char, 1024> string_alloc;

		size_t line_end = data.find('\n', pos);
		if (line_end == std::string::npos) {
			line_end = data.size();
		}
		
		if (line_end > line_start) {
			size_t eq_pos = data.find('=', line_start);
			if (eq_pos != std::string::npos && eq_pos < line_end) {
				std::pmr::string key(&string_alloc);
				key = data.substr(line_start, eq_pos - line_start).c_str();
				
				size_t colon_pos = data.find(':', eq_pos);
				if (colon_pos != std::string::npos && colon_pos < line_end) {
					char type = data[eq_pos + 1];
					std::pmr::string value_str(&string_alloc);
					value_str  = data.substr(colon_pos + 1, line_end - colon_pos - 1);
					
					switch (type) {
					case 'b': { // bool
							bool val = (value_str == "1");
							set(key.c_str(), setting_variant(val));
							break;
						}
					case 'f': { // float
							float val = atof(value_str.c_str());
							set(key.c_str(), setting_variant(val));
							break;
						}
					case 'v': { // vec2i
							size_t comma = value_str.find(',');
							if (comma != std::string::npos) {
								int x = atoi(value_str.substr(0, comma).c_str());
								int y = atoi(value_str.substr(comma + 1).c_str());
								set(key.c_str(), setting_variant(vec2i{x, y}));
							}
							break;
						}
					case 's': { // string
							std::pmr::string unescaped(&string_alloc);
							unescaped.reserve(value_str.size());
							for (size_t i = 0; i < value_str.size(); ++i) {
								if (value_str[i] == '\\' && i + 1 < value_str.size()) {
									++i;
								}
								unescaped += value_str[i];
							}
							xstring unescaped_xx = unescaped.c_str();
							set(key.c_str(), setting_variant(unescaped_xx));
							break;
						}
					}
				}
			}
		}
		
		pos = line_end + 1;
		line_start = pos;
	}
}

globals_settings_t::globals_settings_t() {
	set_sync_task([this] (xstring name) {
		const auto &xvar = this->get(name);
		sync_with_js(name, xvar);
	});
}

void globals_settings_t::load_global(pcstr name) {
	_initialized = true;
	_variantsDirty = false;

	g_config_arch.r_objects(name, [&] (pcstr key, archive arch) {
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
static void svarprintf(js_State *state, const char *v) {
	svardata.append(v);
}

void globals_settings_t::sync_with_js(const xstring &name, const setting_variant &value) {
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

void globals_settings_t::sync_global(pcstr filename, pcstr name) {
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