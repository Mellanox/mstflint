load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

package(
    default_visibility = ["//visibility:public"],
)

cc_library(
    name = "common-headers",
    hdrs = [
        "bit_slice.h",
        "compatibility.h",
        "tools_utils.h",
        "tools_version.h",
    ],
    include_prefix = "common",
)

cc_library(
    name = "filesystem",
    srcs = [
        "filesystem.cpp",
    ],
    hdrs = [
        "filesystem.h",
    ],
    copts = [
        "-Wall",
        "-Wextra",
        "-Wpedantic",
    ],
    deps = [
        "@boost//:filesystem",
    ],
)

cc_test(
    name = "filesystem-test-bin",
    size = "small",
    srcs = [
        "filesystem-test.cpp",
    ],
    copts = [
        "-Wall",
        "-Wextra",
        "-Wpedantic",
    ],
    tags = ["manual"],
    deps = [
        ":filesystem",
        "@com_google_googletest//:gtest_main",
    ],
)

sh_test(
    name = "filesystem-test",
    size = "small",
    srcs = [
        "filesystem-test.sh",
    ],
    data = [
        ":filesystem-test-bin",
    ],
)
