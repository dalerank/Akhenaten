#include "dev/perfmon.h"

#ifndef GAME_PLATFORM_ANDROID

#include "dev/perfmon_nanoprofiler.h"
#include "dev/perfmon_widget.h"
#include "game/game.h"
#include "widget/debug_console.h"

#include "imgui.h"

#include <iostream>

namespace
{
    Perfmon::PerfmonWidget g_perfmon;
    bool g_perfmon_registered = false;
    double g_game_update_ms = 0.0;
    double g_draw_ms = 0.0;

    void ensure_metrics()
    {
        if (g_perfmon_registered)
            return;
        g_perfmon_registered = true;

        Perfmon::PerfMetricSettings frameSettings;
        frameSettings.goodValue = 12.0;
        frameSettings.badValue = 33.0;

        g_perfmon.RegisterMetric(Perfmon::Metric(
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

        g_perfmon.RegisterMetric(Perfmon::Metric(
            "game.update (ms)",
            []() { return g_game_update_ms; },
            phaseSettings,
            { 4.0, 8.0, 16.0, 33.0, 66.0 }));

        g_perfmon.RegisterMetric(Perfmon::Metric(
            "draw phase (ms)",
            []() { return g_draw_ms; },
            phaseSettings,
            { 4.0, 8.0, 16.0, 33.0, 66.0 }));
    }
} // namespace

void game_perfmon_overlay_init()
{
    bind_debug_command("perfmon", [](std::istream &, std::ostream &os) {
        game.debug_perfmon = !game.debug_perfmon;
        os << (game.debug_perfmon ? "perfmon on\n" : "perfmon off\n");
    });
}

void game_perfmon_set_phase_ms(double game_update_ms, double draw_ms)
{
    g_game_update_ms = game_update_ms;
    g_draw_ms = draw_ms;
}

void game_perfmon_draw()
{
    if (!game.debug_perfmon)
        return;

    ensure_metrics();

    ImGuiIO& io = ImGui::GetIO();
    g_perfmon.Update(io.DeltaTime);

    ImGui::SetNextWindowSize(ImVec2(520, 400), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Performance##perfmon", &game.debug_perfmon)) {
        g_perfmon.DrawGUI();
    }
    ImGui::End();
}

void game_perfmon_frame_mark_end()
{
    Perfmon::NanoProfiler::Clear();
}

#endif // !GAME_PLATFORM_ANDROID
