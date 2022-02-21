cc_test(
    name = "message_handlers_tests",
    srcs = glob(["*.cpp"]),
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "@com_google_googletest//:gtest_main",
        "//utils:ancho_net_middleware_utils",
        "//common:agents_common",
        "//message_handlers:message_handlers",
    ],
)
