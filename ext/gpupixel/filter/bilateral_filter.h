#pragma once

#include "filter_group.h"
#include "../core/gpupixel_macros.h"

NS_GPUPIXEL_BEGIN

class BilateralMonoFilter;
using BilateralMonoFilterPtr = std::shared_ptr<BilateralMonoFilter>;

class BilateralMonoFilter : public Filter {
public:
    enum Type { HORIZONTAL, VERTICAL };

    static BilateralMonoFilterPtr create(Type type = HORIZONTAL);
    bool init();

    virtual bool proceed(bool bUpdateTargets = true, int64_t frameTime = 0) override;

    void setTexelSpacingMultiplier(float multiplier);
    void setDistanceNormalizationFactor(float value);

protected:
    BilateralMonoFilter(Type type);
    Type _type;
    float _texelSpacingMultiplier;
    float _distanceNormalizationFactor;
};

class BilateralFilter : public FilterGroup {
public:
    virtual ~BilateralFilter();

    static std::shared_ptr<BilateralFilter> create();
    bool init();

    void setTexelSpacingMultiplier(float multiplier);
    void setDistanceNormalizationFactor(float value);

protected:
    BilateralFilter();

private:
    // friend BilateralMonoFilter;
    BilateralMonoFilterPtr _hBlurFilter;
    BilateralMonoFilterPtr _vBlurFilter;
};

NS_GPUPIXEL_END
