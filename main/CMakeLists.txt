idf_component_register(SRCS 
"main.cpp"
"utils/time/delay.cpp"
"utils/log/Logger.cpp"
"peripherals/interface/I2C/I2C.cpp"
"peripherals/device/MT6701/MT6701.cpp"
"utils/math/MathHelper.cpp"
"controller/PID/PIDController.cpp"
"peripherals/interface/PWM/PWM.cpp"
"peripherals/interface/GPIO/GPIO.cpp"
"peripherals/device/motors/DCSteppingMotor.cpp"
"peripherals/device/motors/SimpleDCMotor.cpp"
"peripherals/device/LinearSlider/LinearSlider.cpp"
"peripherals/device/motors/servo/MG995.cpp"
"controller/core/WriterBot.cpp"
"bluetooth/gatt_server.cpp"
"global/global.cpp"
"controller/command/CommandManager.cpp"
"peripherals/device/LED/LED.cpp"
"storage/NVSStorage.cpp"
"peripherals/interface/ADC/ADC.cpp"
                    INCLUDE_DIRS ".")
