log_info("akhenaten: city floods started")

city.floods = extend(__city_floods, {
    state_is: function(state) {
        return this.state == state
    },

    expected_quality: __city_floods_expected_quality,
    expected_month: __city_floods_expected_month,
})
