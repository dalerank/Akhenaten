#pragma once
// ImGui performance widget from https://github.com/zenkovich/imgui_perfmon (MIT)

#include "dev/perfmon_timeseries.h"
#include "dev/perfmon_nanoprofiler.h"
#include "imgui.h"

#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

namespace Perfmon
{
    enum class PerfStatus { Good, Normal, Bad };

    struct PerfMetricSettings
    {
        double goodValue = 0.0;
        double badValue = 0.0;
        float badValueWeight = 1.0f;
        float normalValueWeight = 1.0f;
        float goodValueWeight = 1.0f;
    };

    struct Metric : public PerfMetricSettings
    {
        std::string name;
        std::function<double()> getSampleFunc;
        double baselineValue = 0.0;

    public:
        static constexpr int kNumSamples = 130;

        Metric() = default;
        Metric(const std::string& name, std::function<double()> getSampleFunc, PerfMetricSettings perfSettings, std::vector<double> targetValues);

        PerfStatus GetStatus() const;
        void Update(float dt);
        const TimeSeries<double>& GetSamplesData() const { return _samplesData; }
        double GetTargetValue() const { return _targetValue; }

    private:
        float _timeSinceLastUpdate = 0.0f;
        float _updateInterval = 0.0f;
        double _targetValue = 0.0;
        std::vector<double> _targetValues;
        TimeSeries<double> _samplesData = TimeSeries<double>(kNumSamples);
    };

    struct EntityCountMetric : public PerfMetricSettings
    {
        std::string name;
        int count = 0;
        int baselineCount = 0;
        std::function<int()> getEntityCount;

    public:
        EntityCountMetric() = default;
        EntityCountMetric(const std::string& name, std::function<int()> getEntityCount, PerfMetricSettings perfSettings);
    };

    class PerfmonWidget
    {
    public:
        void DrawGUI();
        void Update(float dt);
        void RegisterMetric(Metric metric);
        void RegisterCounterMetric(EntityCountMetric metric);

    private:
        static constexpr int kNanoProfilerNumSamples = 140;

        struct ProfileSample
        {
            const char* name;
            size_t hash = 0;
            double time = 0.0;
            int parent = -1;
        };

        struct NanoProfileFrame
        {
            std::vector<ProfileSample> samples;
            double totalTime = 0.0;
        };

        PerfStatus _overallStatus = PerfStatus::Good;
        std::vector<Metric> _metrics;
        std::vector<EntityCountMetric> _entityCounters;
        std::unordered_map<const char*, int> _samplesMap;
        float _timeSinceLastEntitiesCount = 0.0f;
        float _entitiesCountUpdateInterval = 0.3f;
        std::vector<NanoProfileFrame> _nanoProfilerSamplesHistory;
        int _nanoProfilerDetailFrame = -1;
        std::unordered_map<const char*, ImColor> _nanoProfilerColors;
        int _lastNanoProfilerColorIndex = 0;
        bool _enableBaseline = false;

        void DrawOverallStatus();
        void DrawNanoProfiler();
        void DrawEntitiesCounters();
        void DrawMetric(Metric& metric);
        void DrawMetricRecentValue(Metric& metric);
        void DrawGraphic(const TimeSeries<double>& data, double goodMetric, double badMetric, double targetMetric);
        void DrawEntityCount(EntityCountMetric& metric);
        void GetNanoProfilerSamplesFrame();
        void UpdateEntitiesCount(float dt);
        void CountEntities();
        PerfStatus GetOverallStatus() const;
        void ToggleBaseline();
    };
} // namespace Perfmon
