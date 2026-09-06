#pragma once

#include "grid/point.h"

// One figure rendered into its own small texture.
//
// The city is drawn once with the camera snapped to the figure, the figure is cropped out of
// that frame and the camera is put back before the call returns. Capture copies from the
// current render target, so it may only run from the city draw path -- never from input
// handling, where it would paint mid-frame ahead of the normal city blit.
class figure_snapshot {
public:
    figure_snapshot() = default;
    ~figure_snapshot() { reset(); }

    figure_snapshot(figure_snapshot&& other) noexcept { swap(other); }
    figure_snapshot& operator=(figure_snapshot&& other) noexcept {
        if (this != &other) {
            reset();
            swap(other);
        }
        return *this;
    }

    figure_snapshot(const figure_snapshot&) = delete;
    figure_snapshot& operator=(const figure_snapshot&) = delete;

    // Crop origin relative to the figure's screen position that puts it in the middle.
    static vec2i centered_offset(int size) { return {-size / 2, -size / 2}; }

    // Re-renders into the texture this snapshot already owns. Keeps the previous image when
    // the figure is gone or landed outside the viewport, so the panel never flashes empty.
    // Returns true when a new image was taken.
    bool capture(int figure_id, int size, vec2i crop_offset);

    bool capture(int figure_id, int size) { return capture(figure_id, size, centered_offset(size)); }

    int texture_id() const { return texture_id_; }
    bool valid() const { return texture_id_ != 0; }

    void reset();

private:
    void swap(figure_snapshot& other) noexcept;

    int texture_id_ = 0;
    int size_ = 0;
};
