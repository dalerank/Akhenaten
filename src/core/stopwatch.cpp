#include "stopwatch.h"

#include "core/log.h"

#include <algorithm>
#include <cinttypes>
#include <cmath>
#include <cstring>

template <typename T>
const T& clamp(const T& x, const T& upper, const T& lower) {
    return std::min<int>(upper, std::max<int>(x, lower));
}

size_t stopwatch::STAMPS() {
    return stamps.size() - 1;
}
void stopwatch::START() {
    stamps.clear();
    repeats = 0;
    index = 0;
    RECORD("<none>");
}
void stopwatch::RECORD(std::string str) {
    if (index >= stamps.size()) {
        std::vector<std::chrono::time_point<std::chrono::system_clock>> nv;
        stamps.push_back(nv);
        if (index > 0)
            names.push_back(str);
    }
    auto& array = stamps.at(index);
    int a = array.size();
    const auto tp = std::chrono::system_clock::now();
    array.push_back(tp);
    int b = array.size();
    index++;
}
uint64_t stopwatch::GET(int a, int b) {
    if (stamps.size() == 0)
        return 0;

    a = clamp<int>(a, (int)stamps.size() - 1, 0);
    b = clamp<int>(b, (int)stamps.size() - 1, 0);
    if (a == b)
        return 0;

    uint64_t ms = 0;
    auto arr_a = &stamps.at(a);
    auto arr_b = &stamps.at(b);
    int arr_a_size = (int)arr_a->size();
    int arr_b_size = (int)arr_b->size();

    int repeats_proper = repeats + 1;
    repeats_proper = std::min<int>(repeats_proper, std::min<int>(arr_a_size, arr_b_size));

    for (int i = 0; i < repeats_proper; ++i) {
        auto s_a = arr_a->at(i);
        auto s_b = arr_b->at(i);
        auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(s_b - s_a);
        ms += dur.count();
    }

    return ms / repeats_proper;
}
uint64_t stopwatch::GET(int a) {
    return GET(a, a + 1);
}
uint64_t stopwatch::STOP(std::string str) {
    RECORD(str);
    return GET(stamps.size() - 2);
}
void stopwatch::REPEAT() {
    if (index > 1) {
        index = 0;
        repeats++;
        RECORD("<none>");
    }
}
void stopwatch::LOG() {
    for (int i = 0; i < STAMPS(); ++i) {
        auto ms = GET(i);
        char bar[200] = "";
        for (int j = 0; j < std::min<int>(2.5 * log(ms + 1), 199); ++j)
            strcat(bar, "!");
        strcat(bar, "\0");
        logs::info("%02i %20s : %4" PRIu64 " %s\n", i, names.at(i).c_str(), ms, bar);
    }
}