#include "settings_vars.h"

#include <variant>
#include <unordered_map>
#include <optional>

#include "content/vfs.h"
#include "core/log.h"
#include "js/js_game.h"
#include "mujs/mujs.h"

#define READER_LOCK(macLockName) // ThreadSafety::ReaderLock macLockName(_mutex)
#define WRITER_LOCK(macLockName) // ThreadSafety::WriterLock macLockName(_mutex)

class settings_vars_impl_t {
	friend class settings_vars_t;
	settings_vars_impl_t() {
	}

	void Finalize() {
		{
			WRITER_LOCK(writeLock);
			_finalized = true;
		}
		//_backgroundQueueExecutor->WaitAsync();
	}

	using variant_t = std::variant<bool, float, vec2i, xstring>;
	using variants_map_t = std::unordered_map<xstring, variant_t>;
public:
	void reset() {
		{
			READER_LOCK(readLock);
			if (_finalized) {
				return;
			}
			if (!_initialized) {
				return;
			}
		}

		//_backgroundQueueExecutor->WaitAsync();

		{
			WRITER_LOCK(writeLock);
			_initialized = false;
		}
	}

	size_t get_count() {
		READER_LOCK(readLock);
		//if (!IsInitialized(readLock)) {
		//	return 0;
		//}
		return _variants.size();
	}

	void sync(pcstr filename) {
		{
			READER_LOCK(readLock);
			//if (!IsInitialized(readLock)) {
			//	return;
			//}
		}
		save(filename);
	}

	void set_autosync_delay(const settings_vars_t::delay_t delay) {
		bool forceSync = false;
		{
			WRITER_LOCK(writeLock);
			forceSync = (delay < _storageSyncDelay);
			_storageSyncDelay = delay;
		}

		if (forceSync) {
			//_backgroundQueueExecutor->Force();
		}
	}

	bool is_defined(xstring name) {
		READER_LOCK(readLock);
		//if (!IsInitialized(readLock)) {
		//	return false;
		//}
		return _variants.find(name) != _variants.end();
	}

	std::optional<variant_t> get_variant(xstring &name) {
		READER_LOCK(readLock);
		//if (!IsInitialized(readLock)) {
		//	return {};
		//}
		auto it = _variants.find(name);
		if (it == _variants.end()) {
			return {};
		}
		return it->second;
	}

	template<typename T>
	std::optional<T> get(const xstring &name) {
		READER_LOCK(readLock);
		//if (!IsInitialized(readLock)) {
		//	return {};
		//}
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
		{
			READER_LOCK(readLock);
			//if (!IsInitialized(readLock)) {
			//	return;
			//}

			auto it = _variants.find(name);
			if (it != _variants.end()) {
				if (it->second == variant_t(value)) {
					return;
				}
			}
		}

		WRITER_LOCK(writeLock);
		_variantsDirty = true;
		_variants[name] = variant_t(value);
	}

	void initialize() {
		WRITER_LOCK(writeLock);

		_initialized = true;
		_variantsDirty = false;
		_variants.clear();

		g_config_arch.r_objects("game_settings", [&] (pcstr key, archive arch) {
			auto value = arch.r_variant("value");
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
				break;
			}
		});		
	}

	static inline std::string svardata;
	static void svarprintf(js_State *state, const char* v) {
		svardata.append(v);
    }

	void save(pcstr filename) {
		int loadResult;
		{
			READER_LOCK(readLock);
			loadResult = _loadResult;
		}

		{
			WRITER_LOCK(writeLock);
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
			svardata.append("var game_settings = {\n");

			js_State *state = (js_State *)g_config_arch.state;
			js_setdumping(state, &svarprintf);
			js_getglobal(state, "game_settings");
			if (js_isobject(state, -1)) {
				js_dumpobject_ex(state, -1);
			}
			js_pop(state, 1);

			fprintf(fp, "%s", svardata.c_str());
			svardata.clear();
			_variantsDirty = false;
			
			vfs::file_close(fp);
		}
	}

private:
	settings_vars_t::delay_t _storageSyncDelay = std::chrono::milliseconds(100);

	variants_map_t _variants;
	int _loadResult = -1;
	bool _variantsDirty = false;
	bool _syncScheduled = false;
	bool _initialized = false;
	bool _finalized = false;
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

void settings_vars_t::sync(pcstr filename) {
	impl().sync(filename);
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

xstring settings_vars_t::get_string(const xstring &name, const xstring &def) {
	auto v = impl().get<xstring>(name);
	return v.value_or(def);
}

void settings_vars_t::set_string(const xstring &name, const xstring &value) {
	impl().set(name, value);
}