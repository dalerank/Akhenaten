#pragma once

#include <string>
#include <chrono>
#include <variant>

#include "core/vec2i.h"
#include "core/xstring.h"
#include "core/archive.h"

class settings_vars_impl_t;

enum setting_variant_type {
    setting_bool,
    setting_float,
    setting_vec2i,
    setting_string,
	setting_none,
};;

using setting_variant = std::variant<bool, float, vec2i, xstring>;
class settings_vars_t {
	char _data[144];
	settings_vars_impl_t *_impl = nullptr;

protected:
	inline settings_vars_impl_t &impl() { return *_impl; }
	inline const settings_vars_impl_t &impl() const { return *_impl; }

public:
	settings_vars_t();

	bool is_defined(const xstring &name);
	void clear();

	setting_variant_type type(const xstring &name);

	void set_sync_task(std::function<void(xstring)> task);
	void foreach_vars(std::function<void(xstring, const setting_variant&)> task);

	bool get_bool(const xstring &name, bool def = false);
	void set_bool(const xstring &name, bool value);

	int get_int(const xstring &name, int def = 0);
	void set_int(const xstring &name, int value);

	int64_t get_int64(const xstring &name, int64_t def = 0);
	void set_int64(const xstring &name, int64_t value);

	float get_float(const xstring &name, float def = 0);
	void set_float(const xstring &name, float value);

	void set(const xstring &name, const setting_variant &value);
	setting_variant get(const xstring &name, const setting_variant &def = setting_variant{});

	xstring get_string(const xstring &name, const xstring &def = "");
	void set_string(const xstring &name, const xstring &value);

	std::string save() const;
	void load(const std::string& data);
};

class globals_settings_t final : public settings_vars_t {
	bool _variantsDirty = false;
	bool _initialized = false;

	void sync_with_js(const xstring &name, const setting_variant &value);

public:
	globals_settings_t();

	void load_global(pcstr name);
	void sync_global(pcstr filename, pcstr name);
};

namespace archive_helper {
	template<>
	inline void reader<settings_vars_t>(archive arch, settings_vars_t &v) { arch.r_variants_impl(arch, v); }
}