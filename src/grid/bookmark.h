#ifndef MAP_BOOKMARK_H
#define MAP_BOOKMARK_H

#include "core/buffer.h"

void map_bookmarks_clear(void);

void map_bookmark_save(int number);

bool map_bookmark_go_to(int number);

#endif // MAP_BOOKMARK_H
