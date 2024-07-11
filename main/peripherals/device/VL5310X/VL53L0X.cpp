/*
 * File: \VL53L0X.h
 * Project: vl5310x
 * Created Date: 2024-05-26 21:55:41
 * Author: Guoyi
 * -----
 * Last Modified: 2024-05-26 22:45:16
 * Modified By: Guoyi
 * -----
 * Copyright (c) 2024 Guoyi Inc.
 *
 * ------------------------------------
 */

#include "./VL53L0X.h"
#include "./VL53L0X_IMPL.h"

#define LONG_RANGE

VL53L0X::VL53L0X()
{
    impl = VL53L0X_IMPL();
    impl._i2c.init(22, 21);
    impl.setTimeout(500);
    if (!impl.init())
    {
        printf("Failed to detect and initialize VL53L0X!\n");
        return;
    }
#if defined LONG_RANGE
    // lower the return signal rate limit (default is 0.25 MCPS)
    impl.setSignalRateLimit(0.1);
    // increase laser pulse periods (defaults are 14 and 10 PCLKs)
    impl.setVcselPulsePeriod(VL53L0X_IMPL::VcselPeriodPreRange, 18);
    impl.setVcselPulsePeriod(VL53L0X_IMPL::VcselPeriodFinalRange, 14);
#endif

#if defined HIGH_SPEED
    // reduce timing budget to 20 ms (default is about 33 ms)
    impl.setMeasurementTimingBudget(20000);
#elif defined HIGH_ACCURACY
    // increase timing budget to 200 ms
    impl.setMeasurementTimingBudget(200000);
#endif
}

/*
 * Performs a single-shot range measurement and returns the reading in millimeters.
 */
uint16_t VL53L0X::readDistance()
{
    uint16_t res = impl.readRangeSingleMillimeters();
    if (impl.timeoutOccurred())
    {
        printf("TIMEOUT \n");
    }
    return res;
}
