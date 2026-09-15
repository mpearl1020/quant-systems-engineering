// Copyright 2026 Matthew Pearl

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "market_replay/market_event.hpp"

namespace market_replay {

std::unordered_map<std::string, TickerStats> compute_market_data_statistics(
    const std::vector<MarketEvent>& market_events) {
  std::unordered_map<std::string, TickerStats> statistics;

  auto compute_stats_start_time = std::chrono::steady_clock::now();

  // compute statistics
  for (const MarketEvent& market_event : market_events) {
    const std::string& ticker = market_event.symbol;
    const Side side = market_event.side;
    const double price = market_event.price;
    const uint32_t quantity = market_event.quantity;

    auto [it, _] = statistics.try_emplace(ticker);
    TickerStats& ticker_stats = it->second;

    SideStats& buy_stats = ticker_stats.buy_stats;
    SideStats& sell_stats = ticker_stats.sell_stats;

    if (side == Side::Buy) {
      buy_stats.count++;
      buy_stats.price_sum += price;
      buy_stats.min_price = std::min(buy_stats.min_price, price);
      buy_stats.max_price = std::max(buy_stats.max_price, price);
      buy_stats.volume_sum += quantity;
      buy_stats.min_volume = std::min(buy_stats.min_volume, quantity);
      buy_stats.max_volume = std::max(buy_stats.max_volume, quantity);
    } else {
      sell_stats.count++;
      sell_stats.price_sum += price;
      sell_stats.min_price = std::min(sell_stats.min_price, price);
      sell_stats.max_price = std::max(sell_stats.max_price, price);
      sell_stats.volume_sum += quantity;
      sell_stats.min_volume = std::min(sell_stats.min_volume, quantity);
      sell_stats.max_volume = std::max(sell_stats.max_volume, quantity);
    }
  }

  auto compute_stats_end_time = std::chrono::steady_clock::now();
  auto elapsed_compute_stats_time =
      compute_stats_end_time - compute_stats_start_time;

  double compute_stats_time =
      std::chrono::duration<double>(elapsed_compute_stats_time).count();
  std::cout << "\nComputed market event statistics in " << compute_stats_time
            << " seconds\n";

  return statistics;
}

void print_market_statistics(
    const std::unordered_map<std::string, TickerStats>& market_statistics) {
  std::vector<std::string> tickers;
  for (const auto& [ticker, _] : market_statistics) {
    tickers.push_back(ticker);
  }

  std::sort(tickers.begin(), tickers.end());

  for (const std::string& ticker : tickers) {
    const TickerStats& ticker_stats = market_statistics.at(ticker);

    const SideStats& buy_stats = ticker_stats.buy_stats;
    const SideStats& sell_stats = ticker_stats.sell_stats;

    std::cout << "symbol " << ticker << ":\n";
    if (buy_stats.count > 0) {
      std::cout << '\t' << buy_stats.count
                << " BUY transactions with min price: " << buy_stats.min_price
                << ", max price: " << buy_stats.max_price
                << ", avg. price: " << buy_stats.price_sum / buy_stats.count
                << " and min vol: " << buy_stats.min_volume
                << ", max vol: " << buy_stats.max_volume << ", avg. vol: "
                << static_cast<double>(buy_stats.volume_sum) / buy_stats.count
                << "\n";
    }
    if (sell_stats.count > 0) {
      std::cout << '\t' << sell_stats.count
                << " SELL transactions with min price: " << sell_stats.min_price
                << ", max price: " << sell_stats.max_price
                << ", avg. price: " << sell_stats.price_sum / sell_stats.count
                << " and min vol: " << sell_stats.min_volume
                << ", max vol: " << sell_stats.max_volume << ", avg. vol: "
                << static_cast<double>(sell_stats.volume_sum) / sell_stats.count
                << '\n';
    }
  }
}

}  // namespace market_replay
