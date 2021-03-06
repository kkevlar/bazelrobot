workspace(name = "myproject")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "new_git_repository")

# Group the sources of the library so that CMake rule have access to it
all_content = """filegroup(name = "all", srcs = glob(["**"]), visibility = ["//visibility:public"])"""

# Rule repository
http_archive(
   name = "rules_foreign_cc",
   strip_prefix = "rules_foreign_cc-master",
   url = "https://github.com/bazelbuild/rules_foreign_cc/archive/master.zip",
   sha256 = "a2e43b2141cddce94999e26de8075031394ac11fb8075de8aa0b8e13905715ed",
)

git_repository(
    name = "platformio_rules",
    remote = "http://github.com/kkevlar/platformio_rules.git",
    branch = "master",
)

new_git_repository(
    name = "adafruit_motor_shield",
    remote = "https://github.com/kkevlar/Adafruit_Motor_Shield_V2_Library",
    commit = "2749a413728570b4c35efc9cdf1119e899264569",
    shallow_since = "1584911129 -0700",
    build_file_content = """
exports_files(["Adafruit_MotorShield.cpp"])
exports_files(["Adafruit_MotorShield.h"])

# you can also create targets
cc_library(
    name = "motorshield_library",
    srcs = ["Adafruit_MotorShield.cpp"],
    hdrs = ["Adafruit_MotorShield.h"],
)
exports_files(["Adafruit_MS_PWMServoDriver.h"])
exports_files(["Adafruit_MS_PWMServoDriver.cpp"])

# you can also create targets
cc_library(
    name = "servo_motorshield_library",
    srcs = ["Adafruit_MS_PWMServoDriver.cpp"],
    hdrs = ["Adafruit_MS_PWMServoDriver.h"],
)
""",
)

new_git_repository(
    name = "liquidcrystal_i2c",
    remote = "http://github.com/kkevlar/LiquidCrystal_I2C.git",
    commit = "c976ad2dc682d40d994797761f39d4d9f0cc8196",
    shallow_since = "1554826820 -0400",
    build_file_content = """
exports_files(["LiquidCrystal_I2C.h"])
exports_files(["LiquidCrystal_I2C.cpp"])

# you can also create targets
cc_library(
    name = "liquidcrystal_library",
    srcs = ["LiquidCrystal_I2C.cpp"],
    hdrs = ["LiquidCrystal_I2C.h"],
)
""",
)

load("@rules_foreign_cc//:workspace_definitions.bzl", "rules_foreign_cc_dependencies")

# Call this function from the WORKSPACE file to initialize rules_foreign_cc
#  dependencies and let neccesary code generation happen
#  (Code generation is needed to support different variants of the C++ Starlark API.).
#
#  Args:
#    native_tools_toolchains: pass the toolchains for toolchain types
#      '@rules_foreign_cc//tools/build_defs:cmake_toolchain' and
#      '@rules_foreign_cc//tools/build_defs:ninja_toolchain' with the needed platform constraints.
#      If you do not pass anything, registered default toolchains will be selected (see below).
#
#    register_default_tools: if True, the cmake and ninja toolchains, calling corresponding
#      preinstalled binaries by name (cmake, ninja) will be registered after
#      'native_tools_toolchains' without any platform constraints.
#      The default is True.
rules_foreign_cc_dependencies([])


load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
http_archive(
    name = "cmocka",
   build_file_content = all_content,
   strip_prefix = "cmocka-1.1.5",
    urls = ["https://cmocka.org/files/1.1/cmocka-1.1.5.tar.xz"],
    sha256 = "f0ccd8242d55e2fd74b16ba518359151f6f8383ff8aef4976e48393f77bba8b6",
)

