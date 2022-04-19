#include "chunks.h"

static void default_bind(io_buffer *io) {
    io->bind(BIND_SIGNATURE_NONE);
}

io_buffer *iob_none = new io_buffer(default_bind);

io_buffer *iob_ = new io_buffer([](io_buffer *iob) {

});


io_buffer *iob_junk1 = new io_buffer(default_bind);

io_buffer *iob_junk2 = new io_buffer(default_bind);

io_buffer *iob_junk7a = new io_buffer(default_bind);
io_buffer *iob_junk7b = new io_buffer(default_bind);

io_buffer *iob_junk8a = new io_buffer(default_bind);
io_buffer *iob_junk8b = new io_buffer(default_bind);
io_buffer *iob_junk8c = new io_buffer(default_bind);

io_buffer *iob_junk9a = new io_buffer(default_bind);
io_buffer *iob_junk9b = new io_buffer(default_bind);
io_buffer *iob_junk9c = new io_buffer(default_bind);

io_buffer *iob_junk10a = new io_buffer(default_bind);
io_buffer *iob_junk10b = new io_buffer(default_bind);
io_buffer *iob_junk10c = new io_buffer(default_bind);

io_buffer *iob_junk11 = new io_buffer(default_bind);

io_buffer *iob_junk14 = new io_buffer(default_bind);

io_buffer *iob_junk16 = new io_buffer(default_bind);

io_buffer *iob_junk17 = new io_buffer(default_bind);

io_buffer *iob_junk18 = new io_buffer(default_bind);

io_buffer *iob_bizarre_ordered_fields_1 = new io_buffer(default_bind);
io_buffer *iob_bizarre_ordered_fields_2 = new io_buffer(default_bind);
io_buffer *iob_bizarre_ordered_fields_3 = new io_buffer(default_bind);
io_buffer *iob_bizarre_ordered_fields_4 = new io_buffer(default_bind);