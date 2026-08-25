// Copyright 2026 Matthew Pearl

#include <iostream>
#include <string>
#include <vector>

#include "market_replay/market_event.hpp"

namespace market_replay {

void replayMarketEvents(const std::vector<MarketEvent>& marketEvents) {
  for (const MarketEvent& marketEvent : marketEvents) {
    std::string sideString = (marketEvent.side == Side::Buy) ? "BUY" : "SELL";
    std::cout << sideString << ' ' << marketEvent.quantity << ' '
              << marketEvent.symbol << " @ " << marketEvent.price << " at time "
              << marketEvent.timestamp << '\n';
  }
}

}  // namespace market_replay
