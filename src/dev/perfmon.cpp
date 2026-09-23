#include "platform/platform.h"

#ifndef GAME_PLATFORM_ANDROID

#include "core/app.h"
#include "core/xvalue.h"
#include "dev/perfmon_nanoprofiler.h"
#include "dev/perfmon_widget.h"
#include "game/game.h"
#include "game/game_events.h"
#include "graphics/residency_atlas.h"
#include "input/keys.h"
#include "js/js.h"
#include "widget/debug_console.h"

#include "imgui.h"


struct game_perfmon_t {
    Perfmon::PerfmonWidget widget;
    bool metrics_registered = false;
    bool visible = false;
    double game_update_ms = 0.0;
    double draw_ms = 0.0;

    void ensure_metrics();
    void set_phase_ms(double update_ms, double draw_phase_ms);
    void draw();
};

void game_perfmon_t::ensure_metrics() {
    if (metrics_registered) {
        return;
    }
    metrics_registered = true;

    Perfmon::PerfMetricSettings frameSettings;
    frameSettings.goodValue = 12.0;
    frameSettings.badValue = 33.0;

    widget.RegisterMetric(Perfmon::Metric(
        "Frame (ImGui dt, ms)",
        []() -> double {
            float dt = ImGui::GetIO().DeltaTime;
            return dt > 1e-6 ? (double)(dt * 1000.0f) : 0.0;
        },
        frameSettings,
        { 8.0, 16.0, 33.0, 50.0, 100.0 }));

    Perfmon::PerfMetricSettings phaseSettings;
    phaseSettings.goodValue = 8.0;
    phaseSettings.badValue = 24.0;

    widget.RegisterMetric(Perfmon::Metric(
        "game.update (ms)",
        []() { return xvalue<game_perfmon_t>::ref().game_update_ms; },
        phaseSettings,
        { 4.0, 8.0, 16.0, 33.0, 66.0 }));

    widget.RegisterMetric(Perfmon::Metric(
        "draw phase (ms)",
        []() { return xvalue<game_perfmon_t>::ref().draw_ms; },
        phaseSettings,
        { 4.0, 8.0, 16.0, 33.0, 66.0 }));

    Perfmon::PerfMetricSettings memSettings;
    memSettings.goodValue = 4.0;
    memSettings.badValue = 48.0;

    widget.RegisterMetric(Perfmon::Metric(
        "mujs heap (MB, main alloc)",
        []() -> double {
            constexpr double kInv = 1.0 / (1024.0 * 1024.0);
            return (double)js_mujs_heap_bytes() * kInv;
        },
        memSettings,
        { 1.0, 4.0, 8.0, 16.0, 32.0, 64.0 }));

    Perfmon::PerfMetricSettings atlasFillSettings;
    atlasFillSettings.goodValue = 25.0;
    atlasFillSettings.badValue = 90.0;

    widget.RegisterMetric(Perfmon::Metric(
        "residency atlas fill (%)",
        []() { return res_atlas::fill_percent(); },
        atlasFillSettings,
        { 10.0, 25.0, 50.0, 75.0, 100.0 }));

    Perfmon::PerfMetricSettings atlasTimeSettings;
    atlasTimeSettings.goodValue = 0.5;
    atlasTimeSettings.badValue = 4.0;

    widget.RegisterMetric(Perfmon::Metric(
        "residency atlas pack+blit (ms)",
        []() { return res_atlas::frame_time_ms(); },
        atlasTimeSettings,
        { 0.25, 0.5, 1.0, 2.0, 4.0, 8.0 }));
}

void game_perfmon_t::set_phase_ms(double update_ms, double draw_phase_ms) {
    game_update_ms = update_ms;
    draw_ms = draw_phase_ms;
}

void game_perfmon_t::draw() {
    if (!visible) {
        return;
    }

    ensure_metrics();

    ImGuiIO &io = ImGui::GetIO();
    widget.Update(io.DeltaTime);

    ImGui::SetNextWindowSize(ImVec2(520, 400), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Performance##perfmon", &visible)) {
        widget.DrawGUI();
    }
    ImGui::End();
}

void ANK_REGISTER_APPLICATION_MODULE(register_perfmon_module) {
    auto &module = xvalue<game_perfmon_t>::ref();
    game.add_frame_phase_ms_handler([&module](double game_update_ms, double draw_ms) {
        module.set_phase_ms(game_update_ms, draw_ms);
    });
    game.add_debug_ui_draw_handler([&module]() { module.draw(); });
    game.add_frame_serial_part_handler([]() { Perfmon::NanoProfiler::Clear(); });

    events::subscribe_permanent([&module](event_debug_hotkey ev) {
        if (ev.key == KEY_F4) {
            module.visible = true;
        }
    });

    bind_debug_command("perfmon", [&module](console_args &, console_output &out) {
        module.visible = !module.visible;
        out.println(module.visible ? "perfmon on" : "perfmon off");
    });
}

#endif // !GAME_PLATFORM_ANDROID
