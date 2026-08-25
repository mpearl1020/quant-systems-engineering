// Copyright 2026 Matthew Pearl

#ifndef MARKET_REPLAY_MARKET_REPLAY_HPP_
#define MARKET_REPLAY_MARKET_REPLAY_HPP_

#include <vector>

#include "market_replay/market_event.hpp"

namespace market_replay {
void replayMarketEvents(
    const std::vector<market_replay::MarketEvent>& marketEvents);
}

#endif  // MARKET_REPLAY_MARKET_REPLAY_HPP_
