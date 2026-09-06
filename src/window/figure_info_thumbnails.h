#pragma once

#include "core/svector.h"
#include "figure/figure_type.h"
#include "widget/figure_snapshot.h"

class figure_info_thumbnails {
public:
    void clear();
    void prepare_thumbnail(int index, figure_id id);
    // Puts the normal city frame back after the per-figure captures.
    void finish();
    int texture(int index) const;

private:
    static constexpr int MAX_THUMBNAILS = 7;
    static constexpr int THUMBNAIL_SIZE = 48;

    svector<figure_snapshot, MAX_THUMBNAILS> figure_images_;
};

extern figure_info_thumbnails g_figure_info_thumbnails;
