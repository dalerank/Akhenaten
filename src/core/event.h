#pragma once

struct game_event
{
    const char *name;
    const char *source;

    game_event(const char *name, const char *source): name(name), source(source) {};
};
