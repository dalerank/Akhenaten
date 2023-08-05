#include "io/log.h"

#include <algorithm>
#include <iostream>
#include <unordered_map>

namespace {

const std::unordered_map<std::string, SDL_LogPriority> PRIORITY_DICT = {{"verbose", SDL_LOG_PRIORITY_VERBOSE},
                                                                        {"debug", SDL_LOG_PRIORITY_DEBUG},
                                                                        {"info", SDL_LOG_PRIORITY_INFO},
                                                                        {"warn", SDL_LOG_PRIORITY_WARN},
                                                                        {"error", SDL_LOG_PRIORITY_ERROR},
                                                                        {"critical", SDL_LOG_PRIORITY_CRITICAL}};

const std::unordered_map<SDL_LogPriority, char const*> PRIORITY_PREFIX = {{SDL_LOG_PRIORITY_VERBOSE, ""},
                                                                          {SDL_LOG_PRIORITY_DEBUG, "debug: "},
                                                                          {SDL_LOG_PRIORITY_INFO, ""},
                                                                          {SDL_LOG_PRIORITY_WARN, "warn: "},
                                                                          {SDL_LOG_PRIORITY_ERROR, "error: "},
                                                                          {SDL_LOG_PRIORITY_CRITICAL, "critical: "}};

char const* get_prefix_of(SDL_LogPriority priority) {
    auto it = PRIORITY_PREFIX.find(priority);
    if (it != PRIORITY_PREFIX.end()) {
        return it->second;
    }

    throw std::runtime_error("Unknown SDL_LogPriority level");
}

SDL_LogPriority get_log_priority() {
    if (char const* priority_ptr = std::getenv("SDL_LOG_PRIORITY")) {
        auto priority_str = std::string(priority_ptr);
        std::transform(priority_str.begin(), priority_str.end(), priority_str.begin(), [](unsigned char c) {
            return std::tolower(c);
        });

        auto it = PRIORITY_DICT.find(priority_str);
        if (it != PRIORITY_DICT.end())
            return it->second;

        std::cerr << "Unknown SDL_LOG_PRIORITY value, VERBOSE will be used" << std::endl;
        return SDL_LOG_PRIORITY_VERBOSE;
    }

    return SDL_LOG_PRIORITY_INFO;
}

} // namespace

namespace logs {

void initialize() {
    SDL_LogSetOutputFunction(Logger::write, nullptr);
    SDL_LogSetAllPriority(get_log_priority());
}

} // namespace logs

Logger::Logger() {
    file_stream_.open("ozymandias-log.txt", std::fstream::out | std::fstream::trunc);
}

Logger::~Logger() {
    file_stream_.close();
}

void Logger::write(void* /* userdata */, int /* category */, SDL_LogPriority priority, char const* message) {
    static Logger logger;
    char const* const prefix = get_prefix_of(priority);

    Logger::write_to_output_(prefix, message);
    logger.write_to_file_(prefix, message);
}

void Logger::write_to_file_(char const* prefix, char const* message) {
    file_stream_ << prefix << message << std::endl;
}

void Logger::write_to_output_(char const* prefix, char const* message) {
    std::cout << prefix << message << std::endl;
}
