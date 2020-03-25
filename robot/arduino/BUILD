
load(
    "@platformio_rules//platformio:platformio.bzl",
    "platformio_library",
    "platformio_project",
)

platformio_library(
    name = "liquidcrystal",
    src = "@liquidcrystal_i2c//:LiquidCrystal_I2C.cpp",
    hdr = "@liquidcrystal_i2c//:LiquidCrystal_I2C.h",
)

platformio_library(
    name = "ms_servo",
    src = "@adafruit_motor_shield//:Adafruit_MS_PWMServoDriver.cpp",
    hdr = "@adafruit_motor_shield//:Adafruit_MS_PWMServoDriver.h",
)

platformio_library(
    name = "motorshield",
    src = "@adafruit_motor_shield//:Adafruit_MotorShield.cpp",
    hdr = "@adafruit_motor_shield//:Adafruit_MotorShield.h",
    add_hdrs = ["@adafruit_motor_shield//:Adafruit_MS_PWMServoDriver.h"],
    deps = [":ms_servo"],
)
platformio_library(
    name = "echo",
    src = "echo.cpp",
    hdr = "//robot/hwhdrs:echo_h_fg",
)
platformio_library(
    name = "inotime",
src = "inotime.cpp",
    hdr = "//robot/hwhdrs:inotime_h_fg",
)
platformio_library(
    name = "shoot",
    src = "shoot.cpp",
    hdr = "//robot/hwhdrs:shoot_h_fg",
    deps = [":motorshield",],
)
platformio_library(
    name = "switch",
    src = "switch.cpp",
    hdr = "//robot/hwhdrs:switch_h_fg",
)
platformio_library(
    name = "inorandom",
    src = "inorandom.cpp",
    hdr = "//robot/hwhdrs:inorandom_h_fg",
)
platformio_library(
    name = "collect",
    src = "//robot/logic:collect_c_fg",
    hdr = "//robot/logic:collect_h_fg",
)
platformio_library(
    name = "aim",
    src = "//robot/logic:aim_c_fg",
    hdr = "//robot/logic:aim_h_fg",
)
platformio_library(
    name = "control",
    src = "//robot/logic:control_c_fg",
    hdr = "//robot/logic:control_h_fg",
)
platformio_library(
    name = "drive",
    src = "//robot/logic:drive_c_fg",
    hdr = "//robot/logic:drive_h_fg",
)
platformio_library(
    name = "fold",
    src = "//robot/logic:fold_c_fg",
    hdr = "//robot/logic:fold_h_fg",
)


platformio_library(
    name = "wheel",
    src = "wheel.cpp",
    hdr = "//robot/hwhdrs:wheel_h_fg",
    add_hdrs = ["@adafruit_motor_shield//:Adafruit_MS_PWMServoDriver.h",
                "@adafruit_motor_shield//:Adafruit_MotorShield.h",
                "//robot/logic:robottypes_h_fg",],
)

platformio_library(
    name = "lcd",
    src = "lcd.cpp",
    hdr = "//robot/hwhdrs:lcd_h_fg",
    add_hdrs = ["@liquidcrystal_i2c//:LiquidCrystal_I2C.h",],
)

platformio_library(
    name = "robottypes",
    hdr = "//robot/logic:robottypes_h_fg",
)

platformio_project(
    name = "roborodentia",
    src = "main.cpp",
    board = "uno",
    framework = "arduino",
    platform = "atmelavr",
    deps = [
        ":inotime",
        ":inorandom",
        ":echo",
        ":ms_servo",
        ":motorshield",
        ":liquidcrystal",
        ":robottypes",
        ":switch",
        ":lcd",
        ":shoot",
        ":wheel",
        ":collect",
        ":drive",
        ":aim",
        ":control",
        ":fold",
    ],
    # If you need to you can pass multiple string key-value pairs directly
    # to PlatformIO. All of these will appear under the environment section in
    # the generated platformio.ini file. That would be "[env:megaatmega2560]" in
    # this example. For the available options see:
    # http://docs.platformio.org/en/stable/projectconf.html
    environment_kwargs = {
        "board_f_cpu": "16000000L",
    }
)



