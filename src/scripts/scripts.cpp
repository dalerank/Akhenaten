#include "content/vfs.h"

#include "cmrc/cmrc.hpp"

CMRC_DECLARE(ozymandias);

namespace vfs {

constexpr pcstr internal_scripts_path = "src/scripts/";

std::pair<void*, uint32_t> internal_file_open(pcstr path) {
	if (!path || !*path) {
		return {nullptr, 0};
	}

	auto fs = cmrc::ozymandias::get_filesystem();

	bstring256 fs_path(internal_scripts_path, (*path == ':') ? (path + 1) : path);
	if (!fs.exists(fs_path.c_str())) {
		return {nullptr, 0};
	}

	auto fd1 = fs.open(fs_path.c_str());
	return {(void*)fd1.begin(), (uint32_t)fd1.size()};
}

}