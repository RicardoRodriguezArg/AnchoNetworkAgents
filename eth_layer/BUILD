load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "eth_layer",
    srcs = glob(["*.cpp"]),
    hdrs = glob(["*.h"]),
    linkopts = ["-lpthread"],
     visibility = ["//agent_server:__pkg__",
                   "//builder:__pkg__",
                  ],
    deps = [
             "//commons:commons",
             "//utils:ancho_net_middleware_utils",
             "@com_github_google_glog//:glog",
           ],
)
