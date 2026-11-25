#pragma once

#include "core/vfs/dir.h"
#include "core/vfs/path.h"

#include <map>
#include <set>
#include <vector>

namespace vfs {

    class ZipArchive;

    struct vfs_t {
        struct path_uri {
            path original;
            path lowered;
        };

        vfs_t();

        bool verbose_log = false;
        std::vector<ZipArchive*> mounted_archives;
        std::map<size_t, path_uri> path_cache;
        std::set<size_t> path_missing;
        path user_data_folder;
        path exe_dir;
        dir_listing listing = {};
        int listing_capacity = 0;

        ZipArchive* find_archive(const path& filepath) const;
        void cache_path(pcstr entry);
    };

    vfs_t& vfs();

} // namespace vfs
