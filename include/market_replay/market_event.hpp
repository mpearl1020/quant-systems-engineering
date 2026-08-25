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
  double priceSum{};
  double minPrice{std::numeric_limits<double>::infinity()};
  double maxPrice{};
  uint64_t volumeSum{};
  uint32_t minVolume{std::numeric_limits<uint32_t>::max()};
  uint32_t maxVolume{};
};

struct TickerStats {
  SideStats buyStats{};
  SideStats sellStats{};
};

}  // namespace market_replay

#endif  // MARKET_REPLAY_MARKET_EVENT_HPP_
