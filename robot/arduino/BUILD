

load(
    "@platformio_rules//platformio:platformio.bzl",
    "platformio_library",
    "platformio_project",
)

platformio_library(
    name = "switch",
    src = "switch.cc",
    hdr = "//robot/hwhdrs:switch_h_fg",
)

platformio_project(
    name = "switch_project",
    src = "switchmain.cc",
    board = "uno",
    framework = "arduino",
    platform = "atmelavr",
    deps = [
        ":switch",
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

genrule(
   name = "drive",
   srcs = ["//robot/logic:drive_c_fg"],
   outs = ["drive.ino"],
   cmd_bash = "cp $(SRCS) $(OUTS)",
   
    
    )

