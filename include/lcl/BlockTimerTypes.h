#pragma once

#include <chrono>

#include "BlockTimer.h"

namespace lcl
{

//! @brief Block timer using system clock
using BlockTimerSystem = BlockTimer<std::chrono::system_clock>;

//! @brief Block timer using high resolution clock
using BlockTimerHighRes = BlockTimer<std::chrono::high_resolution_clock>;

}
