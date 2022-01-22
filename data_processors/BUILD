load("@rules_cc//cc:defs.bzl", "cc_library")

cc_library(
    name = "middleware_data_processors",
    srcs = glob(["*.cpp"]),
    hdrs = glob(["*.h"]),
    linkopts = ["-lpthread"],
    deps = [
            "@com_google_googletest//:gtest_main",
             "//utils:ancho_net_middleware_utils",
             "//commons:commons",
             "//message_handlers:message_handlers",
           ],
)
