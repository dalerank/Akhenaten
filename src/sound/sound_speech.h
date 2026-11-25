#pragma once

#include "content/vfs.h"
#include "core/svector.h"
#include "core/xstring.h"

struct sound_speech_t {
    svector<xstring, 8> dirs;
    xstring walker_dir;

    bool play_file(xstring filename);
    bool file_exist(xstring filename, vfs::path& fs_path);
    void stop();

private:
    bool try_rel(pcstr rel, vfs::path& fs_path);
    static bool ieq_prefix(pcstr path, pcstr prefix);
    vfs::path normalize_rel(pcstr filename) const;
};

sound_speech_t& sound_speech();
