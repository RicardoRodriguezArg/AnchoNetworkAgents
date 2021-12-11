cc_test(
    name = "communication_tests",
    srcs = glob(["*.cpp"]),
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "@com_google_googletest//:gtest_main",
        "//utils:ancho_net_middleware_utils",
    ],
)
