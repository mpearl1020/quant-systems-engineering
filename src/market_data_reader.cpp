// Copyright 2026 Matthew Pearl

#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

#include "market_replay/market_event.hpp"

namespace market_replay {

constexpr size_t k_timestamp_idx = 0;
constexpr size_t k_symbol_idx = 1;
constexpr size_t k_side_idx = 2;
constexpr size_t k_price_idx = 3;
constexpr size_t k_quantity_idx = 4;

std::vector<MarketEvent> read_market_data_from_csv(
    const std::string& csv_path) {
  std::ifstream market_data_file{csv_path};

  if (!market_data_file) {
    std::cerr << "issue opening file\n";
    return {};
  }

  std::vector<MarketEvent> market_events;
  std::string data_line;

  std::getline(market_data_file, data_line);  // discard CSV header

  size_t csv_line_number = 1;

  while (std::getline(market_data_file, data_line)) {
    ++csv_line_number;
    std::vector<std::string> line_elements =
        data_line | std::views::split(',') |
        std::ranges::to<std::vector<std::string>>();

    if (line_elements.size() != 5) {
      std::cout << "[WARNING] Skipping CSV row " << csv_line_number
                << " that doesn't contain 5 elements\n";
      continue;
    }

    MarketEvent market_event{};
    try {
      market_event.timestamp = std::stoull(line_elements[k_timestamp_idx]);
      market_event.symbol = line_elements[k_symbol_idx];

      if (line_elements[k_side_idx] == "BUY") {
        market_event.side = Side::Buy;
      } else if (line_elements[k_side_idx] == "SELL") {
        market_event.side = Side::Sell;
      } else {
        std::cout << "[WARNING] Skipping CSV row " << csv_line_number
                  << ". Transaction side must be in {BUY, SELL}, got "
                  << line_elements[k_side_idx] << '\n';
        continue;
      }

      market_event.price = std::stod(line_elements[k_price_idx]);
      market_event.quantity = std::stoul(line_elements[k_quantity_idx]);
    } catch (const std::exception& e) {
      std::cout << "[WARNING] Parsing skipped due to malformed CSV data on row "
                << csv_line_number
                << ". See exception message for more details: " << e.what()
                << '\n';
      continue;
    }

    market_events.push_back(market_event);
  }

  return market_events;
}

}  // namespace market_replay