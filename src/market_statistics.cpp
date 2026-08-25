// Copyright 2026 Matthew Pearl

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "market_replay/market_event.hpp"

namespace market_replay {

std::unordered_map<std::string, TickerStats> computeMarketDataStatistics(
    const std::vector<MarketEvent>& marketEvents) {
  std::unordered_map<std::string, TickerStats> statistics;

  auto computeStatsStartTime = std::chrono::steady_clock::now();

  // compute statistics
  for (const MarketEvent& marketEvent : marketEvents) {
    const std::string& ticker = marketEvent.symbol;
    const Side side = marketEvent.side;
    const double price = marketEvent.price;
    const uint32_t quantity = marketEvent.quantity;

    auto [it, _] = statistics.try_emplace(ticker);
    TickerStats& tickerStats = it->second;

    SideStats& buyStats = tickerStats.buyStats;
    SideStats& sellStats = tickerStats.sellStats;

    if (side == Side::Buy) {
      buyStats.count++;
      buyStats.priceSum += price;
      buyStats.minPrice = std::min(buyStats.minPrice, price);
      buyStats.maxPrice = std::max(buyStats.maxPrice, price);
      buyStats.volumeSum += quantity;
      buyStats.minVolume = std::min(buyStats.minVolume, quantity);
      buyStats.maxVolume = std::max(buyStats.maxVolume, quantity);
    } else {
      sellStats.count++;
      sellStats.priceSum += price;
      sellStats.minPrice = std::min(sellStats.minPrice, price);
      sellStats.maxPrice = std::max(sellStats.maxPrice, price);
      sellStats.volumeSum += quantity;
      sellStats.minVolume = std::min(sellStats.minVolume, quantity);
      sellStats.maxVolume = std::max(sellStats.maxVolume, quantity);
    }
  }

  auto computeStatsEndTime = std::chrono::steady_clock::now();
  auto elapsedComputeStatsTime = computeStatsEndTime - computeStatsStartTime;

  double computeStatsTime =
      std::chrono::duration<double>(elapsedComputeStatsTime).count();
  std::cout << "\nComputed market event statistics in " << computeStatsTime
            << " seconds\n";

  return statistics;
}

void printMarketStatistics(
    const std::unordered_map<std::string, TickerStats>& marketStatistics) {
  std::vector<std::string> tickers;
  for (const auto& [ticker, _] : marketStatistics) {
    tickers.push_back(ticker);
  }

  std::sort(tickers.begin(), tickers.end());

  for (const std::string& ticker : tickers) {
    const TickerStats& tickerStats = marketStatistics.at(ticker);

    const SideStats& buyStats = tickerStats.buyStats;
    const SideStats& sellStats = tickerStats.sellStats;

    std::cout << "symbol " << ticker << ":\n";
    if (buyStats.count > 0) {
      std::cout << '\t' << buyStats.count
                << " BUY transactions with min price: " << buyStats.minPrice
                << ", max price: " << buyStats.maxPrice
                << ", avg. price: " << buyStats.priceSum / buyStats.count
                << " and min vol: " << buyStats.minVolume
                << ", max vol: " << buyStats.maxVolume << ", avg. vol: "
                << static_cast<double>(buyStats.volumeSum) / buyStats.count
                << "\n";
    }
    if (sellStats.count > 0) {
      std::cout << '\t' << sellStats.count
                << " SELL transactions with min price: " << sellStats.minPrice
                << ", max price: " << sellStats.maxPrice
                << ", avg. price: " << sellStats.priceSum / sellStats.count
                << " and min vol: " << sellStats.minVolume
                << ", max vol: " << sellStats.maxVolume << ", avg. vol: "
                << static_cast<double>(sellStats.volumeSum) / sellStats.count
                << '\n';
    }
  }
}

}  // namespace market_replay
