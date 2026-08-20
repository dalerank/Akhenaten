#pragma once

#include "content/file_formats.h"

// Chunk push lists for each on-disk format. GamestateIO passes these to g_chunk_io.
void file_schema(e_file_format file_format, const int file_version);
void file_schema_family_marker(e_file_format file_format, const int file_version);

void file_schema_map(const int file_version);
void file_schema_sav(const int file_version);
void file_schema_svx(const int file_version);
