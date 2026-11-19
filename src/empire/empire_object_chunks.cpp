#include "empire/empire_object_chunks.h"

#include "empire/empire.h"
#include "empire/empire_object.h"
#include "core/log.h"
#include "io/chunk_serializer.h"
#include "io/io_buffer.h"

void empire_map_objects_chunk::bind_data(io_buffer* iob, size_t version) {
    logs::info("iob_empire_map_objects");
    for (int i = 0; i < empire_t::MAX_MAP_OBJECTS; i++) {
        full_empire_object* full = g_empire.ref_full_object(i);
        empire_object* obj = &full->obj;
        obj->id = i;
        //
        iob->bind(BIND_SIGNATURE_UINT8, &obj->type);
        iob->bind(BIND_SIGNATURE_UINT8, &full->in_use);
        iob->bind(BIND_SIGNATURE_UINT8, &obj->animation_index);
        iob->bind____skip(1);
        iob->bind(BIND_SIGNATURE_INT16, &obj->pos.x);
        iob->bind(BIND_SIGNATURE_INT16, &obj->pos.y);
        iob->bind(BIND_SIGNATURE_INT16, &obj->width);
        iob->bind(BIND_SIGNATURE_INT16, &obj->height);
        iob->bind(BIND_SIGNATURE_INT16, &obj->image_id);
        iob->bind(BIND_SIGNATURE_INT16, &obj->expanded_image_id);
        iob->bind____skip(1);
        iob->bind(BIND_SIGNATURE_UINT8, &obj->distant_battle_travel_months);
        iob->bind____skip(1);
        iob->bind(BIND_SIGNATURE_UINT8, &obj->text_align);
        iob->bind(BIND_SIGNATURE_INT16, &obj->expanded_pos.x);
        iob->bind(BIND_SIGNATURE_INT16, &obj->expanded_pos.y);
        iob->bind(BIND_SIGNATURE_UINT8, &full->city_type);
        iob->bind(BIND_SIGNATURE_UINT8, &full->city_name_id);
        iob->bind_u8(obj->trade_route_id);
        iob->bind(BIND_SIGNATURE_UINT8, &full->trade_route_open);
        iob->bind(BIND_SIGNATURE_INT16, &full->trade_route_cost);

        for (int r = 0; r < EMPIRE_OBJ_MAX_SOLD_RESOURCES; r++) {
            iob->bind(BIND_SIGNATURE_UINT8, &full->city_sells_resource[r]);
        }
        iob->bind____skip(8);
        for (int r = 0; r < EMPIRE_OBJ_MAX_BOUGHT_RESOURCES; r++) {
            iob->bind(BIND_SIGNATURE_UINT8, &full->city_buys_resource[r]);
        }

        iob->bind(BIND_SIGNATURE_UINT8, &obj->invasion_path_id);
        iob->bind(BIND_SIGNATURE_UINT8, &obj->invasion_years);

        // TODO: WRITE
        if (g_chunk_io.get_file_version() < 160) {
            iob->bind____skip(2);
            iob->bind(BIND_SIGNATURE_UINT32, &full->trade40);
            iob->bind(BIND_SIGNATURE_UINT32, &full->trade25);
            iob->bind(BIND_SIGNATURE_UINT32, &full->trade15);
        } else {
            for (int r = 0; r < RESOURCES_MAX; r++) {
                iob->bind(BIND_SIGNATURE_UINT8, &full->trade_demand[r]);
            }
        }
    }
}

void empire_map_routes_chunk::bind_data(io_buffer* iob, size_t version) {
    logs::info("iob_empire_map_routes");
    for (int id = 0; id < empire_t::MAX_ROUTE_OBJECTS; id++) {
        map_route_object& obj = g_empire.ref_route_object(id);

        iob->bind(BIND_SIGNATURE_UINT32, &obj.unk_header[0]); // 05 00 00 00
        iob->bind(BIND_SIGNATURE_UINT32, &obj.unk_header[1]); // 00 00 00 00

        for (int i = 0; i < 50; i++) {
            iob->bind(BIND_SIGNATURE_UINT16, &obj.points[i].p.x);
            iob->bind(BIND_SIGNATURE_UINT16, &obj.points[i].p.y);
            iob->bind(BIND_SIGNATURE_UINT8, &obj.points[i].is_in_use);
            iob->bind____skip(1);
        }
        iob->bind(BIND_SIGNATURE_UINT32, &obj.length);

        iob->bind(BIND_SIGNATURE_UINT32, &obj.unk_00); // 00 00 00 00
        iob->bind(BIND_SIGNATURE_UINT32, &obj.unk_01); // FF FF FF FF

        iob->bind(BIND_SIGNATURE_UINT8, &obj.route_type); // 1 = land; 2 = sea;
        iob->bind(BIND_SIGNATURE_UINT8, &obj.num_points);
        iob->bind(BIND_SIGNATURE_UINT8, &obj.in_use);

        iob->bind(BIND_SIGNATURE_UINT8, &obj.unk_03);

        // Not stored in pak/save — only set from JS empire_routes.
        obj.deviation = 0;
        obj.path_length = obj.calc_length();
    }
}
