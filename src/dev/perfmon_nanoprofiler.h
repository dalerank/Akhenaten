#pragma once

#include <vector>
#include "platform/platform.h"

#ifndef GAME_PLATFORM_ANDROID

namespace Perfmon
{
    class NanoProfiler
    {
    public:
        struct Sample
        {
            const char* name = nullptr;
            int parent = -1;
            double beginTime = 0.0;
            double endTime = 0.0;
        };

        struct SampleScope
        {
            explicit SampleScope(const char* name) { BeginSample(name); }
            ~SampleScope() { EndSample(); }
        };

        static int BeginSample(const char* name);
        static void EndSample();
        static void Clear();
        static const std::vector<Sample>& GetSamples();
        static const std::vector<Sample>& GetBufferSamples();

    private:
        static std::vector<Sample>& GetSamplesInternal();
        static std::vector<Sample>& GetBufferSamplesInternal();
        static double GetTime();
        static int _top;
    };
}

#define NANO_PROFILE_BEGIN(NAME) Perfmon::NanoProfiler::BeginSample(NAME)
#define NANO_PROFILE_END() Perfmon::NanoProfiler::EndSample()
#define NANO_PROFILE_SCOPE(NAME) Perfmon::NanoProfiler::SampleScope PP_CONCAT(_nano_prof_scope_, __LINE__)(NAME)
#define PP_CONCAT(a, b) PP_CONCAT_INNER(a, b)
#define PP_CONCAT_INNER(a, b) a##b

#else

#define NANO_PROFILE_BEGIN(...)
#define NANO_PROFILE_END()
#define NANO_PROFILE_SCOPE(...)
#define PP_CONCAT(...)
#define PP_CONCAT_INNER(...)

#endif
