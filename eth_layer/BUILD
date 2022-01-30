load("@rules_cc//cc:defs.bzl", "cc_binary")

cc_library(
    name = "communication_layer",
   srcs = glob(["*.cpp"]),
    hdrs = glob(["*.h"]),
    linkopts = ["-lpthread"],
     visibility = ["//agent_server:__pkg__",
                 
                 ]
)
