#include "city/buildings_chunks.h"

#include "city/buildings.h"
#include "io/io_buffer.h"

void building_count_industry_chunk::bind_data(io_buffer* iob, size_t version) {
    iob->bind____skip(sizeof(int32_t) * RESOURCES_MAX);
    iob->bind____skip(sizeof(int32_t) * RESOURCES_MAX);

    //    // culture 1
    //    data.buildings[BUILDING_BOOTH].total = culture1->read_i32();
    //    data.buildings[BUILDING_BOOTH].active = culture1->read_i32();
    //    data.buildings[BUILDING_BANDSTAND].total = culture1->read_i32();
    //    data.buildings[BUILDING_BANDSTAND].active = culture1->read_i32();
    //    data.buildings[BUILDING_PAVILLION].total = culture1->read_i32();
    //    data.buildings[BUILDING_PAVILLION].active = culture1->read_i32();
    //    data.buildings[BUILDING_SENET_HOUSE].total = culture1->read_i32();
    //    data.buildings[BUILDING_SENET_HOUSE].active =
    //    culture1->read_i32();
    //    data.buildings[BUILDING_SCRIBAL_SCHOOL].total =
    //    culture1->read_i32();
    //    data.buildings[BUILDING_SCRIBAL_SCHOOL].active =
    //    culture1->read_i32(); data.buildings[BUILDING_LIBRARY].total =
    //    culture1->read_i32(); data.buildings[BUILDING_LIBRARY].active =
    //    culture1->read_i32();
    //    data.buildings[BUILDING_MENU_WATER_CROSSINGS].total =
    //    culture1->read_i32();
    //    data.buildings[BUILDING_MENU_WATER_CROSSINGS].active =
    //    culture1->read_i32(); data.buildings[BUILDING_DENTIST].total =
    //    culture1->read_i32(); data.buildings[BUILDING_DENTIST].active =
    //    culture1->read_i32();
    //    data.buildings[BUILDING_MENU_MONUMENTS].total =
    //    culture1->read_i32();
    //    data.buildings[BUILDING_MENU_MONUMENTS].active =
    //    culture1->read_i32(); data.buildings[BUILDING_APOTHECARY].total =
    //    culture1->read_i32(); data.buildings[BUILDING_APOTHECARY].active =
    //    culture1->read_i32(); data.buildings[BUILDING_MORTUARY].total =
    //    culture1->read_i32(); data.buildings[BUILDING_MORTUARY].active =
    //    culture1->read_i32(); data.buildings[BUILDING_TEMPLE_OSIRIS].total
    //    = culture1->read_i32(); data.buildings[BUILDING_TEMPLE_RA].total =
    //    culture1->read_i32(); data.buildings[BUILDING_TEMPLE_PTAH].total =
    //    culture1->read_i32(); data.buildings[BUILDING_TEMPLE_SETH].total =
    //    culture1->read_i32(); data.buildings[BUILDING_TEMPLE_BAST].total =
    //    culture1->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_OSIRIS].total =
    //    culture1->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_RA].total =
    //    culture1->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_PTAH].total =
    //    culture1->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_SETH].total =
    //    culture1->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_BAST].total =
    //    culture1->read_i32(); data.buildings[BUILDING_ORACLE].total =
    //    culture1->read_i32();
    //
    //    // culture 2
    //    data.buildings[BUILDING_JUGGLER_SCHOOL].total =
    //    culture2->read_i32();
    //    data.buildings[BUILDING_JUGGLER_SCHOOL].active =
    //    culture2->read_i32(); data.buildings[BUILDING_CONSERVATORY].total
    //    = culture2->read_i32();
    //    data.buildings[BUILDING_CONSERVATORY].active =
    //    culture2->read_i32(); data.buildings[BUILDING_DANCE_SCHOOL].total
    //    = culture2->read_i32();
    //    data.buildings[BUILDING_DANCE_SCHOOL].active =
    //    culture2->read_i32(); data.buildings[BUILDING_CHARIOT_MAKER].total
    //    = culture2->read_i32();
    //    data.buildings[BUILDING_CHARIOT_MAKER].active =
    //    culture2->read_i32();
    //
    //    // culture 3
    //    data.buildings[BUILDING_TEMPLE_OSIRIS].active =
    //    culture3->read_i32(); data.buildings[BUILDING_TEMPLE_RA].active =
    //    culture3->read_i32(); data.buildings[BUILDING_TEMPLE_PTAH].active
    //    = culture3->read_i32();
    //    data.buildings[BUILDING_TEMPLE_SETH].active =
    //    culture3->read_i32(); data.buildings[BUILDING_TEMPLE_BAST].active
    //    = culture3->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_OSIRIS].active =
    //    culture3->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_RA].active =
    //    culture3->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_PTAH].active =
    //    culture3->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_SETH].active =
    //    culture3->read_i32();
    //    data.buildings[BUILDING_TEMPLE_COMPLEX_BAST].active =
    //    culture3->read_i32();
    //
    //    // military
    //    data.buildings[BUILDING_MILITARY_ACADEMY].total =
    //    military->read_i32();
    //    data.buildings[BUILDING_MILITARY_ACADEMY].active =
    //    military->read_i32(); data.buildings[BUILDING_RECRUITER].total =
    //    military->read_i32(); data.buildings[BUILDING_RECRUITER].active =
    //    military->read_i32();
    //
    //    // support
    //    data.buildings[BUILDING_BAZAAR].total = support->read_i32();
    //    data.buildings[BUILDING_BAZAAR].active = support->read_i32();
    //    data.buildings[BUILDING_WATER_LIFT].total = support->read_i32();
    //    data.buildings[BUILDING_WATER_LIFT].active = support->read_i32();
    //    data.buildings[BUILDING_MENU_BEAUTIFICATION].total =
    //    support->read_i32();
    //    data.buildings[BUILDING_MENU_BEAUTIFICATION].active =
    //    support->read_i32();
}
