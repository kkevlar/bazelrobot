

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
    name = "drive_h_fg",
    srcs = [
        "drive.h",
    ],
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
    name = "collect_hdr",
    hdrs = ["collect.h"],
    deps = [":robottypes_hdr",],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "collect_c_as_hdr",
    textual_hdrs = ["collect.c"],
    deps = [
        ":collect_hdr",
        "//robot/hwhdrs:wheel_hdr"],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "collect_c_fg",
    srcs = [
        "collect.c",
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "collect_h_fg",
    srcs = [
        "collect.h",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "collect",
    srcs = ["collect.c"],
    deps = [
        ":collect_hdr",
        "//robot/hwhdrs:wheel_hdr"],
    visibility = ["//visibility:public"],
)


cc_library(
    name = "fold_hdr",
    hdrs = ["fold.h"],
    deps = [":robottypes_hdr",],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "fold_c_as_hdr",
    textual_hdrs = ["fold.c"],
    deps = [
        ":fold_hdr",
        "//robot/hwhdrs:wheel_hdr"],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "fold_c_fg",
    srcs = [
        "fold.c",
    ],
    visibility = ["//visibility:public"],
)

filegroup(
    name = "fold_h_fg",
    srcs = [
        "fold.h",
    ],
    visibility = ["//visibility:public"],
)

cc_library(
    name = "fold",
    srcs = ["fold.c"],
    deps = [
        ":fold_hdr",
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

filegroup(
    name = "control_h_fg",
    srcs = [
        "control.h",
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




