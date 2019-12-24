
cc_library(
    name = "libtestsanity",
    copts = ["-Wall","-Wextra","-Werror","-g",],
    srcs = ["test_sanity.c"],
    deps = [
        "//cmocka:cmocka",
        ],
)

cc_test(
    name = "sanity",
    deps = [
        ":libtestsanity",
    ],
)

cc_library(
    name = "libtestdrive",
    srcs = ["test_drive.c"],
    copts = ["-Wall","-Wextra","-Werror","-g",],
    deps = [
        "//cmocka:cmocka",
        "//robot/logic:drive_c_as_hdr",
        "//robot/hwhdrs:wheel_hdr",
        ],
)

cc_test(
    name = "drive",
    deps = [
        ":libtestdrive",
    ],
)

cc_library(
    name = "libtestcontrol",
    srcs = ["test_control.c"],
    copts = ["-Wall","-Wextra","-Werror","-g",],
    deps = [
        "//cmocka:cmocka",
        "//robot/logic:control_c_as_hdr",
        ],
)

cc_test(
    name = "control",
    deps = [
        ":libtestcontrol",
    ],
)

