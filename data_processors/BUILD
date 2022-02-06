load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "data_processors",
    srcs = glob(["*.cpp"]),
    hdrs = glob(["*.h"]),
    linkopts = ["-lpthread"],
    visibility = ["//agents_middleware:__pkg__",
                  "//devices_proxys:__pkg__",
                 ]
            )
