#include "platform/platform.h"

#ifndef GAME_PLATFORM_ANDROID

#include "core/app.h"
#include "core/memory_manager.h"
#include "core/xvalue.h"
#include "game/game.h"
#include "game/game_events.h"
#include "input/keys.h"
#include "widget/debug_console.h"

#include "imgui.h"

#include <algorithm>
#include <unordered_map>
#include <vector>

struct game_memorymon_t {
    bool visible = false;
    void draw();
};

void game_memorymon_t::draw() {
    if (!visible) {
        return;
    }

    ImGui::SetNextWindowSize(ImVec2(460, 420), ImGuiCond_FirstUseEver);
    if (ImGui::Begin("Memory##memorymon", &visible)) {
        const double inv_mib = 1.0 / (1024.0 * 1024.0);
        const int64_t total_bytes = g_memory.total();
        const auto &allocs = g_memory.pack_texture_allocs();

        ImGui::Text("Total: %.2f MiB", total_bytes * inv_mib);
        ImGui::Separator();

        if (ImGui::BeginTable("memory_buckets", 3, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
            ImGui::TableSetupColumn("Bucket");
            ImGui::TableSetupColumn("MiB", ImGuiTableColumnFlags_WidthFixed, 80.0f);
            ImGui::TableSetupColumn("Bytes", ImGuiTableColumnFlags_WidthFixed, 120.0f);
            ImGui::TableHeadersRow();

            for (int i = 0; i < MEMORY_BUCKET_COUNT; ++i) {
                const auto bucket = (e_memory_bucket)i;
                const int64_t bytes = g_memory.used(bucket);
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::TextUnformatted(memory_manager_t::bucket_name(bucket));
                ImGui::TableNextColumn();
                ImGui::Text("%.2f", bytes * inv_mib);
                ImGui::TableNextColumn();
                ImGui::Text("%lld", (long long)bytes);
            }
            ImGui::EndTable();
        }

        ImGui::Separator();
        ImGui::Text("pack_textures allocations (%d)", (int)allocs.size());

        struct group_t {
            xstring name;
            int64_t bytes = 0;
            std::vector<const memory_pack_alloc_t *> pages;
        };

        std::unordered_map<xstring, size_t> index_by_name;
        std::vector<group_t> groups;
        groups.reserve(allocs.size());
        for (const auto &a : allocs) {
            auto it = index_by_name.find(a.name);
            if (it == index_by_name.end()) {
                index_by_name.emplace(a.name, groups.size());
                groups.push_back(group_t{a.name, a.bytes, {&a}});
            } else {
                auto &g = groups[it->second];
                g.bytes += a.bytes;
                g.pages.push_back(&a);
            }
        }
        std::sort(groups.begin(), groups.end(),
                  [](const group_t &a, const group_t &b) { return a.bytes > b.bytes; });

        if (ImGui::BeginTable("pack_allocs", 3,
                              ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_ScrollY,
                              ImVec2(0, 0))) {
            ImGui::TableSetupColumn("Name");
            ImGui::TableSetupColumn("Size", ImGuiTableColumnFlags_WidthFixed, 100.0f);
            ImGui::TableSetupColumn("MiB", ImGuiTableColumnFlags_WidthFixed, 80.0f);
            ImGui::TableHeadersRow();

            for (auto &g : groups) {
                std::sort(g.pages.begin(), g.pages.end(),
                          [](const memory_pack_alloc_t *a, const memory_pack_alloc_t *b) {
                              return a->bytes > b->bytes;
                          });

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                const bool open = ImGui::TreeNodeEx(g.name.c_str(), ImGuiTreeNodeFlags_SpanFullWidth,
                                                    "%s (%d)", g.name.c_str(), (int)g.pages.size());
                ImGui::TableNextColumn();
                ImGui::TextDisabled("-");
                ImGui::TableNextColumn();
                ImGui::Text("%.2f", g.bytes * inv_mib);

                if (open) {
                    for (const auto *page : g.pages) {
                        ImGui::TableNextRow();
                        ImGui::TableNextColumn();
                        ImGui::TextDisabled("  page");
                        ImGui::TableNextColumn();
                        ImGui::Text("%dx%d", page->width, page->height);
                        ImGui::TableNextColumn();
                        ImGui::Text("%.2f", page->bytes * inv_mib);
                    }
                    ImGui::TreePop();
                }
            }
            ImGui::EndTable();
        }
    }
    ImGui::End();
}

void ANK_REGISTER_APPLICATION_MODULE(register_memorymon_module) {
    auto &module = xvalue<game_memorymon_t>::ref();
    game.add_debug_ui_draw_handler([&module]() { module.draw(); });

    events::subscribe_permanent([&module](event_debug_hotkey ev) {
        if (ev.key == KEY_F4) {
            module.visible = true;
        }
    });

    bind_debug_command("memorymon", [&module](console_args &, console_output &out) {
        module.visible = !module.visible;
        out.println(module.visible ? "memorymon on" : "memorymon off");
    });
}

#endif // !GAME_PLATFORM_ANDROID
