#include "utils/log/Logger.h"
#include "utils/time/delay.h"
#include "peripherals/device/motors/DCSteppingMotor.h"
#include "peripherals/device/motors/SimpleDCMotor.h"
#include "peripherals/device/MT6701/MT6701.h"
#include "peripherals/device/linearSlider/LinearSlider.h"
#include "peripherals/device/motors/servo/MG995.h"
#include "controller/core/WriterBot.h"
#include "global/global.h"
#include "bluetooth/Bleprph_Init.h"

extern "C"
{
    void app_main(void);
}

void app_main(void)
{
    Logger.info("进入app_main函数，初始化蓝牙协议栈\n");
    Bleprph_Init();
    delay(1000);

    WriterBotInstance = new WriterBot(33, 32, 25, 5, 21, 0,
                                      17, 18, 19, 4, 22, 1,
                                      26);
    delay(1000);
    WriterBotInstance->dropPen();
    delay(500);
    WriterBotInstance->moveToPosition(5, 5);
    delay(2000);
    WriterBotInstance->liftPen();
    WriterBotInstance->moveToPosition(0, 0);
}
