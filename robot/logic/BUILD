

cc_library(
    name = "robottypes_hdr",
    hdrs = ["robottypes.h"],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "robottypes_h_fg",
    srcs = [
        "robottypes.h",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "drive_hdr",
    hdrs = ["drive.h"],
    deps = [":robottypes_hdr",],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "drive_c_as_hdr",
    textual_hdrs = ["drive.c"],
    deps = [
        ":drive_hdr",
        "//robot/hwhdrs:wheel_hdr"],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "drive_c_fg",
    srcs = [
        "drive.c",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "drive",
    srcs = ["drive.c"],
    deps = [
        ":drive_hdr",
        "//robot/hwhdrs:wheel_hdr"],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "control_hdr",
    hdrs = ["control.h"],
    deps = [
        ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "control_c_as_hdr",
    textual_hdrs = ["control.c"],
    deps = [
        ":control_hdr",
        "//robot/hwhdrs:echo_hdr",
        ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "control_c_fg",
    srcs = [
        "control.c",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "control",
    srcs = ["control.c"],
    deps = [
        ":control_hdr",
        "//robot/hwhdrs:echo_hdr",
        ],
    visibility = ["//visibility:public"],
)

#cc_library(
#   name = "all_hdr",
#   deps = [
#       "wiring_hdr",
#       "drive_hdr",
#       "collect_hdr",
#       "control_hdr",
#       "main_hdr",
#           ],
#    )




