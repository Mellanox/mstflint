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

cc_test(
    name = "boost-filesystem-test-bin",
    size = "small",
    srcs = [
        "filesystem-test.cpp",
    ],
    copts = [
        "-Wall",
        "-Wextra",
        "-Wpedantic",
    ],
    defines = ["USE_BOOST"],
    tags = ["manual"],
    deps = [
        ":filesystem",
        "@com_google_googletest//:gtest_main",
        "@boost//:filesystem",
    ],
)

sh_test(
    name = "filesystem-test",
    size = "small",
    srcs = [
        "filesystem-test.sh",
    ],
    args = ["filesystem-test-bin"],
    data = [
        ":filesystem-test-bin",
    ],
)

sh_test(
    name = "boost-filesystem-test",
    size = "small",
    srcs = [
        "filesystem-test.sh",
    ],
    args = ["boost-filesystem-test-bin"],
    data = [
        ":boost-filesystem-test-bin",
    ],
)
