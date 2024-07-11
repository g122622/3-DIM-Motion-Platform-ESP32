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
    delay(3000);

    // int count = 90;
    // DCSteppingMotor motor(27, 26, 25, 16, 17);
    // while (1)
    // {
    //     printf("count: %d\n", count);
    //     motor.setAngle(count);
    //     delay(3000);
    //     count += 10;
    // }

    // MT6701 mt6701X(5, 21, 0);
    // MT6701 mt6701Y(4, 22, 1);
    // int tickCount = 0;
    // while (1)
    // {
    //     float angleX = mt6701X.readAngle();
    //     float angleY = mt6701Y.readAngle();
    //     printf("[main] angleX: %f, angleY: %f\n", angleX, angleY);
    //     tickCount++;
    //     delay(10);
    // }

    WriterBotInstance = new WriterBot(33, 32, 25, 5, 21, 0,
                                      17, 18, 19, 4, 22, 1,
                                      26);
    delay(1000);
    WriterBotInstance->dropPen();
    delay(500);
    WriterBotInstance->moveToPosition(5, 5);
    delay(2000);
    WriterBotInstance->liftPen();
    WriterBotInstance->moveToPosition(1, 1);

    // LinearSlider sliderX(33, 32, 25, 5, 21, 0);
    // LinearSlider sliderY(17, 18, 19, 4, 22, 1);
    // sliderY.setPosition(1.1);
    // sliderX.setPosition(1.1);
    // delay(5000);
    // sliderY.setPosition(2.1);
    // sliderX.setPosition(2.1);
    // delay(5000);
    // sliderY.setPosition(1.1);
    // sliderX.setPosition(1.1);
    // delay(5000);
    // sliderY.setPosition(0.1);
    // sliderX.setPosition(0.1);
    // delay(5000);
    // sliderY.setPosition(2.1);
    // sliderX.setPosition(2.1);
    // delay(5000);

    // LinearSlider sliderX(33, 32, 25, 5, 21, 0);
    // sliderX.setPosition(1.1);
    // delay(5000);
    // sliderX.setPosition(2.1);
    // delay(5000);
    // sliderX.setPosition(1.1);
    // delay(5000);
    // sliderX.setPosition(0.1);
    // delay(5000);
    // sliderX.setPosition(2.1);
    // delay(5000);

    // LinearSlider sliderY(17, 18, 19, 4, 22, 1);
    // while (1)
    // {
    //     sliderY.setPosition(0.1);
    //     delay(3000);
    //     sliderY.setPosition(1.1);
    //     delay(3000);
    //     sliderY.setPosition(2.1);
    //     delay(3000);
    //     sliderY.setPosition(3.1);
    //     delay(3000);
    //     sliderY.setPosition(4.1);
    //     delay(3000);
    //     sliderY.setPosition(5.1);
    //     delay(3000);
    // }

    // MG995 servo(18);
    // servo.setAngle(90);
    // printf("1\n");
    // delay(3000);
    // servo.setAngle(0);
    // printf("2\n");
    // delay(3000);
    // servo.setAngle(90);
    // printf("3\n");
    // delay(3000);
    // servo.setAngle(180);
    // printf("4\n");
    // delay(3000);
    // servo.setAngle(90);
    // printf("5\n");
    // delay(3000);
    // servo.setAngle(0);
    // printf("6\n");
    // delay(3000);

    // MG995 servo(18);
    // servo.setAngle(90);
    // printf("90\n");
    // delay(3000);

    // servo.setAngle(91);
    // printf("91\n");
    // delay(3000);

    // servo.setAngle(92);
    // printf("92\n");
    // delay(3000);

    // servo.setAngle(93);
    // printf("93\n");
    // delay(3000);

    // servo.setAngle(94);
    // printf("94\n");
    // delay(3000);

    // servo.setAngle(95);
    // printf("95\n");
    // delay(3000);

    // servo.setAngle(85);
    // printf("85\n");
    // delay(3000);
}