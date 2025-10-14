#include <spdlog/spdlog.h>
#include "expected/expected.h"

int main() {
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Dev Playground C++ is Starting...");

    Expected expectedObj;

    return 0;
}
