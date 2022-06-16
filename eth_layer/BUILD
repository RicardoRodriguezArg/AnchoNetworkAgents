load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_library(
    name = "ancho_net_middleware_eth_layer",
    srcs = glob(["*.cpp"]),
    hdrs = glob(["*.h"]),
    visibility = [
                  "//eth_layer/test:__pkg__",
                  "//builder:__pkg__",
                  ],
    deps = ["//commons:commons",
            "@com_github_google_glog//:glog",
           ]
)
