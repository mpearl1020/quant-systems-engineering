// Copyright 2026 Matthew Pearl

#ifndef MARKET_REPLAY_MARKET_EVENT_HPP_
#define MARKET_REPLAY_MARKET_EVENT_HPP_

#include <cstdint>
#include <limits>
#include <string>

namespace market_replay {

enum class Side { Buy, Sell };

struct MarketEvent {
  uint64_t timestamp;
  std::string symbol;
  Side side;
  double price;
  uint32_t quantity;
};

struct SideStats {
  uint64_t count{};
  double price_sum{};
  double min_price{std::numeric_limits<double>::infinity()};
  double max_price{};
  uint64_t volume_sum{};
  uint32_t min_volume{std::numeric_limits<uint32_t>::max()};
  uint32_t max_volume{};
};

struct TickerStats {
  SideStats buy_stats{};
  SideStats sell_stats{};
};

}  // namespace market_replay

#endif  // MARKET_REPLAY_MARKET_EVENT_HPP_
