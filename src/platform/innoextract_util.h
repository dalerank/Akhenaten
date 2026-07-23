#pragma once

#include "core/xstring.h"

namespace innoextract {

xstring find_binary();
xstring binary_directory();
xstring pharaoh_data_directory();
xstring default_extract_directory();
bool has_pharaoh_data(pcstr dir);
bool has_required_game_files(pcstr dir);
pcstr required_game_files_help();
bool extract_installer(pcstr setup_exe, pcstr out_dir, xstring *error_out = nullptr);
xstring find_extracted_game_path(pcstr out_dir);
xstring find_installer_exe(pcstr installer_dir);
xstring installer_pending_bootstrap();
xstring try_bootstrap_pharaoh_data(xstring *error_out = nullptr);

// Non-blocking extract for UI (options_window). Poll each frame while running.
bool extract_job_start(pcstr setup_exe, pcstr out_dir, xstring *error_out = nullptr);
bool extract_job_running();
float extract_job_progress(); // 0..1
// When !extract_job_running() after a start, call once to read success/error.
bool extract_job_take_result(xstring *error_out = nullptr);

} // namespace innoextract
