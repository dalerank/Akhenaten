#pragma once

#include <string>
#include <chrono>

#include "core/xstring.h"

class settings_vars_impl_t;

class settings_vars_t final {
	friend class settings_vars_impl_t;
	char _data[608];

	settings_vars_impl_t &impl() {
		return *(settings_vars_impl_t *)_data;
	}

public:
	settings_vars_t() {}

	bool is_defined(const xstring &name);

	void init();

	// call if you need certainly immediatly sync, better to make task in thread
	void sync(pcstr filename);

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

	xstring get_string(const xstring &name, const xstring &def = "");
	void set_string(const xstring &name, const xstring &value);
};