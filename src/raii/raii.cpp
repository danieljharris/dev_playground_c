#include "raii.h"

Raii::Raii() {}

expected<Raii, string> Raii::create(int initValue) {
    if (initValue > 0) return Raii();
    return unexpected("Invalid Init Value");
}