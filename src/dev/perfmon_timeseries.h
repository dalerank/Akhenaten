#pragma once

#include <algorithm>
#include <vector>

namespace Perfmon
{
    template<typename T>
    class TimeSeries
    {
    public:
        explicit TimeSeries(size_t numSamples)
            : _head(0), _numSamples(numSamples), _dirty(true)
        {
            _values.resize(_numSamples, (T)0);
            _sortedValues.resize(_numSamples, (T)0);
        }

        T Push(T v) noexcept
        {
            const T lrv = _values[_head];

            _values[_head++] = v;
            if (_head >= _numSamples)
                _head = 0;

            Invalidate();

            return lrv;
        }

        size_t GetNumSamples() const noexcept { return _numSamples; }

        const T* GetSamples() const noexcept { return _values.data(); }

        size_t GetHead() const noexcept { return _head; }

        T GetMostRecentSample() const noexcept
        {
            return _values[(_head + _numSamples - 1) % _numSamples];
        }

        T Min() const noexcept { return P0(); }
        T Max() const noexcept { return P100(); }

        T P0() const noexcept
        {
            Validate();
            return _sortedValues[0];
        }

        T P25() const noexcept
        {
            Validate();
            return _sortedValues[_numSamples / 4];
        }

        T P50() const noexcept
        {
            Validate();
            return _sortedValues[_numSamples / 2];
        }

        T P75() const noexcept
        {
            Validate();
            return _sortedValues[3 * _numSamples / 4];
        }

        T P100() const noexcept
        {
            Validate();
            return _sortedValues[_numSamples - 1];
        }

    private:
        void Validate() const noexcept
        {
            if (!_dirty)
                return;

            std::copy(_values.begin(), _values.end(), _sortedValues.begin());
            std::sort(_sortedValues.begin(), _sortedValues.end());

            _dirty = false;
        }

        void Invalidate() noexcept { _dirty = true; }

        std::vector<T> _values;
        mutable std::vector<T> _sortedValues;
        size_t _head;
        size_t _numSamples;
        mutable bool _dirty;
    };
}
