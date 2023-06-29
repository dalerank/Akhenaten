#ifndef OZYMANDIAS_STOPWATCH_H
#define OZYMANDIAS_STOPWATCH_H

#include <chrono>
#include <vector>
#include <string>

class stopwatch {
private:
    std::vector<std::vector<std::chrono::time_point<std::chrono::system_clock>>> stamps;
    int index = 0;
    int repeats = 0;
    std::vector<std::string> names;
public:
    size_t STAMPS();
    void START();
    void RECORD(std::string str = "-");
    uint64_t GET(int a, int b);
    uint64_t GET(int a);
    uint64_t STOP(std::string str = "-");
    void REPEAT();
    void LOG();
};

#endif //OZYMANDIAS_STOPWATCH_H
