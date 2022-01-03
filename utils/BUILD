load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_library(
    name = "ancho_net_middleware_utils",
    srcs = ["utils.cpp"],
    hdrs = ["utils.h"],
    visibility = ["//agent_server:__pkg__",
                  "//utils/tests:__pkg__"
                  ],
    deps = ["//common:commons",]
)
