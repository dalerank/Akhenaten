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
class settings_vars_t final {
	char _data[160];
	settings_vars_impl_t *_impl = nullptr;

	inline settings_vars_impl_t &impl() { return *_impl; }

public:
	settings_vars_t();

	bool is_defined(const xstring &name);

	void load_global(pcstr name);
	void sync_global(pcstr filename, pcstr name);

	setting_variant_type type(const xstring &name);

	// call if you need certainly immediatly sync, better to make task in thread
	void set_sync_task(std::function<void(xstring)> task);

	// settup pause before saving data to file
	using delay_t = std::chrono::duration<int64_t, std::milli>;
	void set_autosync_delay(const delay_t delay);

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
};

namespace archive_helper {
	inline void reader(archive arch, pcstr name, settings_vars_t &v) { arch.r_variants(name, v); }
}