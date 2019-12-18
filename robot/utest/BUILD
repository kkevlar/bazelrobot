
cc_library(
    name = "libtestsanity",
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

