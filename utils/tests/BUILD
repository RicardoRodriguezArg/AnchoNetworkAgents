cc_test(
    name = "communication_tests",
    srcs = ["main.cpp","utils_tests_pack_unpack.cpp"],
    copts = ["-Iexternal/gtest/include"],
    deps = [
        "@com_google_googletest//:gtest_main",
        "//utils:ancho_net_middleware_utils",
    ],
)
