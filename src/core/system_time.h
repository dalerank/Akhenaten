#pragma once

#include "platform/platform.h"

using time_millis = uint32_t;

time_millis time_get_millis(void);
void time_set_millis(time_millis millis);

struct timer {
	inline timer() : _start(0) {}
	inline void	start() { _start = platform.get_qpc(); }
	inline uint64_t	get_elapsed_ticks() const { return platform.get_qpc() - _start; }
	inline uint64_t	get_elapsed_mcs() const { return get_elapsed_ticks() * uint64_t(1000000) / platform.qpc_per_second; }	// mcs
	inline uint32_t get_elapsed_ms() const { return uint32_t(get_elapsed_ticks() * uint64_t(1000) / platform.qpc_per_second); }	// ms
	inline float get_elapsed_sec() const { return float(double(get_elapsed_ticks()) / double(platform.qpc_per_second)); }
	inline bool started() const { return _start != 0; }
	inline void reset() { _start = 0; }

protected:
	uint64_t _start;
};

struct startstop_timer {
	inline startstop_timer() : _start(uint64_t(-1)), _stop(uint64_t(-1)) {}
	inline void start() { _start = platform.get_qpc(); _stop = uint64_t(-1); }
	inline void stop() { _stop = platform.get_qpc(); }
	inline uint64_t get_elapsed_ticks() const {
		if (_start == uint64_t(-1))
			return 0;

		if (_stop == uint64_t(-1))
			return platform.get_qpc() - _start;

		return _stop - _start;
	}

	inline uint64_t get_elapsed_mcs() const { return get_elapsed_ticks() * uint64_t(1000000) / platform.qpc_per_second; }	// mcs
	inline uint32_t get_elapsed_ms() const { return uint32_t(get_elapsed_ticks() * uint64_t(1000) / platform.qpc_per_second); }	// ms
	inline float get_elapsed_sec() const { return float(double(get_elapsed_ticks()) / double(platform.qpc_per_second)); }

protected:
	uint64_t _start;
	uint64_t _stop;
};
