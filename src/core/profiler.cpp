#include "profiler.h"

#include "dev/debug.h"

#if defined( TRACY_MEMORY_ENABLE )

bool TracyProfilerAvailable = true;

void *operator new(std::size_t count) {
	auto ptr = malloc(count);
	if (TracyProfilerAvailable) {
		TracyAllocS(ptr, count, 20);
	}
	return ptr;
}

void *operator new[](std::size_t count) {
	auto ptr = malloc(count);
	if (TracyProfilerAvailable) {
		TracyAllocS(ptr, count, 20);
	}
	return ptr;
}

void operator delete(void *ptr) noexcept {
	if (TracyProfilerAvailable) {
		TracyFreeS(ptr, 20);
	}
	free(ptr);
}

void operator delete[](void *ptr) noexcept {
	if (TracyProfilerAvailable) {
		TracyFreeS(ptr, 20);
	}
	free(ptr);
}

// Sized delete operators (C++14)
void operator delete(void *ptr, std::size_t) noexcept {
	if (TracyProfilerAvailable) {
		TracyFreeS(ptr, 20);
	}
	free(ptr);
}

void operator delete[](void *ptr, std::size_t) noexcept {
	if (TracyProfilerAvailable) {
		TracyFreeS(ptr, 20);
	}
	free(ptr);
}

declare_console_command_p(profile_memory) {
	std::string args; is >> args;
	TracyProfilerAvailable = atoi(args.empty() ? (pcstr)"0" : args.c_str());
};
#endif // !TRACY_NO_CALLSTACK