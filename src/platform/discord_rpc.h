#pragma once

#include "platform/platform.h"
#include "core/xstring.h"
#include <memory>

#if defined(GAME_PLATFORM_WIN) || defined(GAME_PLATFORM_LINUX)

struct discord_rpc_t {
    discord_rpc_t();
    ~discord_rpc_t();

    discord_rpc_t(const discord_rpc_t&) = delete;
    discord_rpc_t& operator=(const discord_rpc_t&) = delete;
    discord_rpc_t(discord_rpc_t&&) = delete;
    discord_rpc_t& operator=(discord_rpc_t&&) = delete;

    void init(const char* app_id);
    void shutdown();
    void tick();
    void set_activity(const xstring& details, const xstring& state);
    void clear_activity();

private:
    struct impl;
    std::unique_ptr<impl> d;
};

#endif // GAME_PLATFORM_WIN || GAME_PLATFORM_LINUX
