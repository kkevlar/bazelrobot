

cc_library(
    name = "wiring_hdr",
    hdrs = ["wiring.h"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "drive_hdr",
    hdrs = ["drive.h"],
    deps = [":wiring_hdr",],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "drive_c_as_hdr",
    textual_hdrs = ["drive.c"],
    deps = [
        ":drive_hdr",
            ":wheel_hdr"],
    visibility = ["//visibility:public"],
)


cc_library(
    name = "drive",
    srcs = ["drive.c"],
    deps = [
        ":drive_hdr",
            ":wheel_hdr"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "wheel_hdr",
    hdrs = ["wheel.h"],
    deps = [],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "wheel",
    srcs = ["wheel.c"],
    deps = [":wheel_hdr"],
    visibility = ["//visibility:public"],
)


