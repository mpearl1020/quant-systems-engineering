// Copyright 2026 Matthew Pearl

#ifndef MARKET_REPLAY_MARKET_STATISTICS_HPP_
#define MARKET_REPLAY_MARKET_STATISTICS_HPP_

#include <string>
#include <unordered_map>
#include <vector>

#include "market_replay/market_event.hpp"

namespace market_replay {
std::unordered_map<std::string, TickerStats> computeMarketDataStatistics(
    const std::vector<MarketEvent>& marketEvents);

void printMarketStatistics(
    const std::unordered_map<std::string, TickerStats>& marketStatistics);
}  // namespace market_replay

#endif  // MARKET_REPLAY_MARKET_STATISTICS_HPP_
