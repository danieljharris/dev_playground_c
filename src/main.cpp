#include <spdlog/spdlog.h>
#include "expected/expected.h"
#include "seed/seed.h"
#include "structures/structures.h"
#include "trade/trade.h"
#include "questions/questions.h"
#include "raii/raii.h"
#include "straylight/straylight.h"

int main() {
    // spdlog::set_level(spdlog::level::debug);
    spdlog::info("Dev Playground C++ is Starting...");

    // Expected expectedObj;
    // Structures structures;
    // Trade trade;
    // Questions questions;
    
    // auto raii1 = Raii::create(1);
    // if (raii1) spdlog::info("Raii created successfully with initValue of 1");
    // else spdlog::error("Raii failed to create with initValue of 1");
    // auto raii2 = Raii::create(-1);
    // if (raii2) spdlog::info("Raii created successfully with initValue of -1");
    // else spdlog::error("Raii failed to create with initValue of -1");

    Straylight straylight;

    return 0;
}
