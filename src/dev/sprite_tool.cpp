#include "imgui.h"
#include "imgui_internal.h"
#include "widget/debug_console.h"
#include "graphics/imagepak_holder.h"

#include "dev/debug.h"

ANK_REGISTER_PROPS_ITERATOR(dev_sprite_tool);

bool game_debug_show_properties_object(imagepak_handle &ipak) {
    ImGui::PushID(0x82000000 | ipak.id);

    ImGui::TableNextRow();
    ImGui::TableSetColumnIndex(0);
    ImGui::AlignTextToFramePadding();
    bool common_open = ImGui::TreeNodeEx((void*)ipak.name.c_str(), ImGuiTreeNodeFlags_None, "%s (%s%d)", ipak.name.c_str(), ipak.handle ? "" : "unloaded,", ipak.entries_num - 201);
    ImGui::TableSetColumnIndex(1);

    bool go = true;
    if (common_open) {
        image_data_touch(ipak);

        const auto &names = ipak.handle->names();
        const auto &ids = ipak.handle->image_ids(); 
        for (int16_t i = 0, size = ids.size(); i < size && go; ++i) {
            ImGui::PushID(0x83000000 + i);

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::AlignTextToFramePadding();
            image_t* img = const_cast<image_t*>(image_get(image_desc{ipak.id, i, 0}));

            bool hdr_last = false;
            int hdr_last_index = 0;
            const image_t *hdr_next_section_img = const_cast<image_t *>(image_next_close_get(image_desc{ ipak.id, i, 0 }, hdr_last, hdr_last_index));
            const int section_len = hdr_last ? (hdr_last_index - img->sgx_index) : (hdr_next_section_img->sgx_index - img->sgx_index);

            bool anim_open = ImGui::TreeNodeEx(img, ImGuiTreeNodeFlags_None, "%s (%d)", img->bmp.name.c_str(), section_len);
            ImGui::TableSetColumnIndex(1);

            const int ioffset = ids[i];

            if (anim_open) {
                if (img && img->atlas.p_atlas) {
                    ImGui::PushID(0x88000000 + i);
                    ImGui::TableNextRow();
                    ImGui::TableSetColumnIndex(0);
                    ImGui::AlignTextToFramePadding();
                    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Bullet;
                    ImGui::TreeNodeEx("Field", flags, "Image");
                    ImGui::TableSetColumnIndex(1);
                    ImGui::SetNextItemWidth(-FLT_MIN);

                    ImGui::Text("id:%d", i);
                    ImGui::SameLine(); ImGui::SetNextItemWidth(60); ImGui::Text("%s", e_pack_type_tokens.name((e_pack)ipak.id));
                    ImGui::SameLine(); ImGui::Text("index:%d", ipak.index);
                    ImGui::SameLine(); ImGui::Text("i_offset:%d", ioffset);
                    int item_current = img->debug.animate;
                    pcstr animate_mode[] = { "None", "Figure", "Simple", "Raw" };
                    ImGui::SameLine(); ImGui::Text("mode"); ImGui::SameLine(); ImGui::SetNextItemWidth(100); ImGui::Combo("##animate", &item_current, animate_mode, std::size(animate_mode));
                    img->debug.animate = item_current;
                    ImGui::SameLine(); ImGui::Text("sprites:%d", img->animation.num_sprites);
                    ImGui::SameLine(); ImGui::Text("max_frame"); ImGui::SetNextItemWidth(30); ImGui::SameLine(); ImGui::InputScalar("##max_frame", ImGuiDataType_U8, (void *)&img->debug.max_frame);
                    ImGui::SameLine(); ImGui::Text("frame:%d", img->debug.frame);

                    const vec2i tx_offset = img->atlas.offset;
                    ImGui::SameLine(); ImGui::Text("offset:%d, %d", tx_offset.x, tx_offset.y);

                    auto maxImageSize = [] (const image_t *img, vec2i msize) {
                        if (img->mirrored_img != 0) {
                            img = img->mirrored_img;                            
                        }
                        msize.x = (img->width < msize.x ? msize.x : img->width);
                        msize.y = (img->height < msize.y ? msize.y : img->height);
                    };

                    auto drawImage = [] (const image_t *img, int idx, vec2i msize) {
                        if (img->mirrored_img != 0) {
                            img = img->mirrored_img;
                            assert(img);
                        }
                        const vec2i tx_offset = img->atlas.offset;
                        const vec2i atlas_size(img->atlas.p_atlas->width, img->atlas.p_atlas->height);
                        ImVec2 uv_min(tx_offset.x / (float)atlas_size.x, tx_offset.y / (float)atlas_size.y);
                        ImVec2 uv_max((tx_offset.x + img->width) / (float)atlas_size.x, (tx_offset.y + img->height) / (float)atlas_size.y);
                        
                        ImGui::BeginChild(bstring32("##imageframe%d", idx), ImVec2(msize.x, msize.y), true);
                        ImVec2 cursor = ImGui::GetCursorPos();
                        ImGui::Image(img->atlas.p_atlas->texture, ImVec2(img->width, img->height), uv_min, uv_max);

                        if (img->has_isometric_top && img->isometric_top) {
                            int py = HALF_TILE_HEIGHT_PIXELS * (img->isometric_size() + 1) - img->height;
                            ImGui::SetCursorPos(cursor);
                            image_t *imgt = img->isometric_top;

                            const vec2i tx_offset_t = imgt->atlas.offset;
                            const vec2i atlas_size_t(imgt->atlas.p_atlas->width, imgt->atlas.p_atlas->height);
                            ImVec2 uv_min_t(tx_offset_t.x / (float)atlas_size_t.x, tx_offset_t.y / (float)atlas_size_t.y);
                            ImVec2 uv_max_t((tx_offset_t.x + imgt->width) / (float)atlas_size_t.x, (tx_offset_t.y + imgt->height) / (float)atlas_size_t.y);

                            ImGui::Image(imgt->atlas.p_atlas->texture, ImVec2(imgt->width, imgt->height), uv_min_t, uv_max_t);
                        }

                        ImGui::EndChild();
                    };

                    if (img->debug.animate == 1 || img->debug.animate == 2) {
                        static uint8_t animate_duration = 4;
                        ImGui::Text("duration"); ImGui::SameLine(); ImGui::SetNextItemWidth(60); ImGui::InputScalar("##duration", ImGuiDataType_U8, (void *)&animate_duration);
                        vec2i msize(60, 60);

                        int max_index = ipak.handle->get_entry_count();
                        for (int dir = 0; dir < 8; ++dir) {
                            int next_dir = img->debug.frame * 8 + dir;
                            int next_index = img->sgx_index + next_dir;
                            if (next_index >= max_index) {
                                img->debug.frame = 0;
                                break;
                            }
                            const image_t *animg = image_get(image_desc{ ipak.id, i, int16_t(img->debug.frame * 8 + dir) });
                            maxImageSize(animg, msize);
                        }

                        msize.x += 16;
                        msize.y += 16;
                        const int dir_max = (img->debug.animate == 1) ? 8 : 1;
                        for (int dir = 0; dir < dir_max; ++dir) {
                            const image_t *animg = (img->debug.animate == 1)
                                ? image_get(image_desc{ ipak.id, i, int16_t(img->debug.frame * 8 + dir) })
                                : image_get(image_desc{ ipak.id, i, int16_t(img->debug.frame) });
                            drawImage(animg, dir, msize);
                            ImGui::SameLine();
                        }

                        const int max_frame = (img->debug.max_frame == 0xff) ? 12 : img->debug.max_frame;
                        ++img->debug.frame_tick;
                        if (img->debug.frame_tick > animate_duration) {
                            img->debug.frame_tick = 0;
                            ++img->debug.frame;
                            if (img->debug.frame >= max_frame) {
                                img->debug.frame = 0;
                            }
                        }
                    } else if (img->debug.animate == 3) {
                        bool last = false;
                        int last_index = 0;
                        const image_t *next_section_img = const_cast<image_t *>(image_next_close_get(image_desc{ ipak.id, i, 0 }, last, last_index));
                        const int section_len = last ? (last_index - img->sgx_index) : (next_section_img->sgx_index - img->sgx_index);
                        
                        int sumsize = 0;
                        for (int imgi = 0; imgi < section_len; ++imgi) {
                            const image_t *animg = img + imgi;
                            drawImage(animg, imgi, vec2i(animg->width + 16, animg->height + 16));
                            if ((imgi == 0 || imgi % 8 != 0) && (sumsize < screen_width() / 2)) {
                                sumsize += animg->width;
                                ImGui::SameLine();
                            } else {
                                sumsize = 0;
                            }
                        }
                    } else {
                        drawImage(img, 0, vec2i(img->width + 16, img->height + 16));
                    }

                    ImGui::NextColumn();
                    ImGui::PopID();
                }

                ImGui::TreePop();
            }
            ImGui::PopID();
        }

        ImGui::TreePop();
    }

    ImGui::PopID();
    return false;
}


void dev_sprite_tool(bool header) {
    static bool _debug_sprites_open = false;

    if (header) {
        ImGui::Checkbox("Sprites", &_debug_sprites_open);
        return;
    } 

    if (_debug_sprites_open && ImGui::BeginTable("split", 2, ImGuiTableFlags_BordersOuter | ImGuiTableFlags_Resizable)) {
        for (auto &imgpak : g_image_data->pak_list) {
            if (imgpak.name.empty()) {
                continue;
            }

            const bool stop = game_debug_show_properties_object(imgpak);
            if (stop) {
                break;
            }
        }
        ImGui::EndTable();
    }
}