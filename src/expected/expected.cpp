#include "expected.h"

using std::string;
using std::expected;
using std::unexpected;

auto processInput(int input) -> expected<int, string> {
    if (input < 0) return unexpected<string>("Negative input not allowed");
    return input * 2;
}

Expected::Expected() {
    spdlog::info("Expected object created");

    expected<int, string> result = processInput(42);

    if (result) {
        spdlog::info("Processing succeeded: {}", *result);
    } else {
        spdlog::error("Processing failed: {}", result.error());
    }

    expected<int, string> failedResult = processInput(-1);
    if (failedResult) {
        spdlog::info("Processing succeeded: {}", *failedResult);
    } else {
        spdlog::error("Processing failed: {}", failedResult.error());
    }
}
