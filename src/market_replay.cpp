// Copyright 2026 Matthew Pearl

#include <iostream>
#include <string>
#include <vector>

#include "market_replay/market_event.hpp"

namespace market_replay {

void replay_market_events(const std::vector<MarketEvent>& market_events) {
  for (const MarketEvent& market_event : market_events) {
    std::string side_string = (market_event.side == Side::Buy) ? "BUY" : "SELL";
    std::cout << side_string << ' ' << market_event.quantity << ' '
              << market_event.symbol << " @ " << market_event.price
              << " at time " << market_event.timestamp << '\n';
  }
}

}  // namespace market_replay
