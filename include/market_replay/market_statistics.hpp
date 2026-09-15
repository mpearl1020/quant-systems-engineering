// Copyright 2026 Matthew Pearl

#ifndef MARKET_REPLAY_MARKET_STATISTICS_HPP_
#define MARKET_REPLAY_MARKET_STATISTICS_HPP_

#include <string>
#include <unordered_map>
#include <vector>

#include "market_replay/market_event.hpp"

namespace market_replay {
std::unordered_map<std::string, TickerStats> compute_market_data_statistics(
    const std::vector<MarketEvent>& market_events);

void print_market_statistics(
    const std::unordered_map<std::string, TickerStats>& market_statistics);
}  // namespace market_replay

#endif  // MARKET_REPLAY_MARKET_STATISTICS_HPP_
