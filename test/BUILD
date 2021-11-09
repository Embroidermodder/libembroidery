package(
    default_visibility = ["//visibility:public"],
    licenses = ["notice"],
)
cc_library(
    name = "test_header",
    hdrs = ["tests.h"],
    srcs = ["tests.c"],
    deps = ["//:libembroidery"],
)
cc_test(
    name = "embroider-test",
    srcs = ["formats.cc"],
    deps = ["//test:test_header",
        "@com_google_googletest//:gtest",
        "@com_google_googletest//:gtest_main"],
)
