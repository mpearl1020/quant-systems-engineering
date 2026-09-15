// Copyright 2026 Matthew Pearl

#ifndef MARKET_REPLAY_MARKET_DATA_READER_HPP_
#define MARKET_REPLAY_MARKET_DATA_READER_HPP_

#include <string>
#include <vector>

#include "market_replay/market_event.hpp"

namespace market_replay {

std::vector<MarketEvent> read_market_data_from_csv(const std::string& csv_path);

}  // namespace market_replay

#endif  // MARKET_REPLAY_MARKET_DATA_READER_HPP_
