
package(
    default_visibility = ["//visibility:public"],
    licenses = ["notice"],
)

cc_library(
    name = "libembroidery",
    srcs = ["compress.c",
    "fills.c",
    "image.c",
    "formats.c",
    "thread-color.c",
    "utility.c"],
    hdrs = ["embroidery.h"],
)

cc_binary(
    name = "embroider",
    srcs = ["embroider-main.c"],
    visibility = ["//visibility:public"],
    deps = [
        ":libembroidery",
    ],
)

exports_files(["LICENSE"])
