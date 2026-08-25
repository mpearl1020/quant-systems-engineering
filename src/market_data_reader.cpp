// Copyright 2026 Matthew Pearl

#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>

#include "market_replay/market_event.hpp"

namespace market_replay {

constexpr size_t kTimestampIdx = 0;
constexpr size_t kSymbolIdx = 1;
constexpr size_t kSideIdx = 2;
constexpr size_t kPriceIdx = 3;
constexpr size_t kQuantityIdx = 4;

std::vector<MarketEvent> readMarketDataFromCSV(const std::string& csvPath) {
  std::ifstream marketDataFile{csvPath};

  if (!marketDataFile) {
    std::cerr << "issue opening file\n";
    return {};
  }

  std::vector<MarketEvent> marketEvents;
  std::string dataLine;

  std::getline(marketDataFile, dataLine);  // discard CSV header

  size_t csvLineNumber = 1;

  while (std::getline(marketDataFile, dataLine)) {
    ++csvLineNumber;
    std::vector<std::string> lineElements =
        dataLine | std::views::split(',') |
        std::ranges::to<std::vector<std::string>>();

    if (lineElements.size() != 5) {
      std::cout << "[WARNING] Skipping CSV row " << csvLineNumber
                << " that doesn't contain 5 elements\n";
      continue;
    }

    MarketEvent marketEvent{};
    try {
      marketEvent.timestamp = std::stoull(lineElements[kTimestampIdx]);
      marketEvent.symbol = lineElements[kSymbolIdx];

      if (lineElements[kSideIdx] == "BUY") {
        marketEvent.side = Side::Buy;
      } else if (lineElements[kSideIdx] == "SELL") {
        marketEvent.side = Side::Sell;
      } else {
        std::cout << "[WARNING] Skipping CSV row " << csvLineNumber
                  << ". Transaction side must be in {BUY, SELL}, got "
                  << lineElements[kSideIdx] << '\n';
        continue;
      }

      marketEvent.price = std::stod(lineElements[kPriceIdx]);
      marketEvent.quantity = std::stoul(lineElements[kQuantityIdx]);
    } catch (const std::exception& e) {
      std::cout << "[WARNING] Parsing skipped due to malformed CSV data on row "
                << csvLineNumber
                << ". See exception message for more details: " << e.what()
                << '\n';
      continue;
    }

    marketEvents.push_back(marketEvent);
  }

  return marketEvents;
}

}