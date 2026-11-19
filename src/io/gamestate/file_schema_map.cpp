#include "file_schemas.h"

#include "io/chunk_serializer.h"
#include "city/city_floods_chunks.h"
#include "core/random_chunks.h"
#include "empire/empire_object_chunks.h"
#include "empire/trade_prices_chunks.h"
#include "io/gamestate/presentation_chunks.h"
#include "grid/elevation_chunks.h"
#include "grid/floodplain_chunks.h"
#include "grid/image_chunks.h"
#include "grid/moisture_chunks.h"
#include "grid/property_chunks.h"
#include "grid/random_chunks.h"
#include "grid/terrain_chunks.h"
#include "grid/vegetation_chunks.h"
#include "io/gamestate/chunks.h"
#include "scenario/scenario_chunks.h"
#include "scenario/scenario_event_manager_chunks.h"

void file_schema_map(const int file_version) {
    g_chunk_io.push_chunk<scenario_mission_index_chunk>(4, false);
    g_chunk_io.push_chunk<file_version_chunk>(4, false);
    g_chunk_io.push_chunk<chunks_schema_chunk>(6004, false);

    g_chunk_io.push_chunk<image_grid_chunk>(207936, false);
    g_chunk_io.push_chunk<edge_grid_chunk>(51984, false);
    g_chunk_io.push_chunk<terrain_grid_chunk>(207936, false);
    g_chunk_io.push_chunk<bitfields_grid_chunk>(51984, false);
    g_chunk_io.push_chunk<random_grid_chunk>(51984, false);
    g_chunk_io.push_chunk<elevation_grid_chunk>(51984, false);

    g_chunk_io.push_chunk<random_iv_chunk>(8, false);
    g_chunk_io.push_chunk<city_view_camera_chunk>(8, false);
    g_chunk_io.push_chunk<scenario_info_chunk>(1592, false);

    g_chunk_io.push_chunk<soil_fertility_grid_chunk>(51984, false);
    g_chunk_io.push_chunk<scenario_events_chunk>(18600, false);
    g_chunk_io.push_chunk<scenario_events_extra_chunk>(28, false);
    g_chunk_io.push_chunk<junk11_chunk>(1280, true);
    g_chunk_io.push_chunk<empire_map_objects_chunk>(file_version < 160 ? 15200 : 19600, true);
    g_chunk_io.push_chunk<empire_map_routes_chunk>(16200, true);
    g_chunk_io.push_chunk<vegetation_growth_chunk>(51984, false); // not sure what's the point of this in MAP...

    g_chunk_io.push_chunk<floodplain_settings_chunk>(file_version < 147 ? 32 : 36, true);
    g_chunk_io.push_chunk<trade_prices_chunk>(288, false);
    g_chunk_io.push_chunk<moisture_grid_chunk>(51984, true);
}
