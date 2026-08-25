// Copyright 2026 Matthew Pearl

#include <chrono>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "market_replay/market_data_reader.hpp"
#include "market_replay/market_replay.hpp"
#include "market_replay/market_statistics.hpp"

int main() {
  std::cout << "Enter a market data file path: ";
  std::string csvPath;
  std::getline(std::cin, csvPath);

  std::cout << "Reading market data file...\n";

  auto readStartTime = std::chrono::steady_clock::now();
  std::vector<market_replay::MarketEvent> marketEvents =
      market_replay::readMarketDataFromCSV(csvPath);
  auto readEndTime = std::chrono::steady_clock::now();
  auto elpasedReadTime = readEndTime - readStartTime;

  size_t numMarketEvents = marketEvents.size();
  double readTime = std::chrono::duration<double>(elpasedReadTime).count();
  std::cout << "Read and saved " << numMarketEvents << " marketEvents in "
            << readTime << " seconds\n";

  while (true) {
    std::cout << "\nChoose a menu option\n\t1. Replay market events\n\t2. "
                 "Compute statistics\n\t3. Exit\n";

    int menuOption;
    while (!(std::cin >> menuOption) ||
           (menuOption != 1 && menuOption != 2 && menuOption != 3)) {
      std::cout << "Invalid input. Please enter a valid menu option (1, 2, 3) ";

      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (menuOption == 1) {
      market_replay::replayMarketEvents(marketEvents);
    } else if (menuOption == 2) {
      const std::unordered_map<std::string, market_replay::TickerStats>
          marketStatistics =
              market_replay::computeMarketDataStatistics(marketEvents);
      market_replay::printMarketStatistics(marketStatistics);
    } else if (menuOption == 3) {
      std::cout << "Exiting...\n";
      break;
    }
  }

  return 0;
}
