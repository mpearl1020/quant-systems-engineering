// Copyright 2026 Matthew Pearl

#ifndef MARKET_REPLAY_MARKET_REPLAY_HPP_
#define MARKET_REPLAY_MARKET_REPLAY_HPP_

#include <vector>

#include "market_replay/market_event.hpp"

namespace market_replay {
void replay_market_events(
    const std::vector<market_replay::MarketEvent>& market_events);
}

#endif  // MARKET_REPLAY_MARKET_REPLAY_HPP_
