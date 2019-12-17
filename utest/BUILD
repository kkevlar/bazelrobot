
cc_library(
    name = "libtestdrive",
    srcs = ["test_drive.c"],
    deps = [
        "//cmocka:cmocka",
        "//FOLD:drive_c_as_hdr",
        "//FOLD:wheel_hdr",
        ],
)

cc_test(
    name = "drive",
    deps = [
        ":libtestdrive",
    ],
)

