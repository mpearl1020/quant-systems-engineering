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
  std::string csv_path;
  std::getline(std::cin, csv_path);

  std::cout << "Reading market data file...\n";

  auto read_start_time = std::chrono::steady_clock::now();
  std::vector<market_replay::MarketEvent> market_events =
      market_replay::read_market_data_from_csv(csv_path);
  auto read_end_time = std::chrono::steady_clock::now();
  auto elapsed_read_time = read_end_time - read_start_time;

  size_t num_market_events = market_events.size();
  double read_time = std::chrono::duration<double>(elapsed_read_time).count();
  std::cout << "Read and saved " << num_market_events << " marketEvents in "
            << read_time << " seconds\n";

  while (true) {
    std::cout << "\nChoose a menu option\n\t1. Replay market events\n\t2. "
                 "Compute statistics\n\t3. Exit\n";

    int menu_option;
    while (!(std::cin >> menu_option) ||
           (menu_option != 1 && menu_option != 2 && menu_option != 3)) {
      std::cout << "Invalid input. Please enter a valid menu option (1, 2, 3) ";

      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (menu_option == 1) {
      market_replay::replay_market_events(market_events);
    } else if (menu_option == 2) {
      const std::unordered_map<std::string, market_replay::TickerStats>
          market_statistics =
              market_replay::compute_market_data_statistics(market_events);
      market_replay::print_market_statistics(market_statistics);
    } else if (menu_option == 3) {
      std::cout << "Exiting...\n";
      break;
    }
  }

  return 0;
}
