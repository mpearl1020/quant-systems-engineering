// Copyright 2026 Matthew Pearl

#include <iostream>

#include "market_replay/market_event.hpp"

void print_market_event_sizes() {
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MarketEvent Struct "
               "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  std::size_t market_event_struct_size{sizeof(market_replay::MarketEvent)};

  std::size_t timestamp_member_size{
      sizeof(market_replay::MarketEvent::timestamp)};
  std::size_t symbol_member_size{sizeof(market_replay::MarketEvent::symbol)};
  std::size_t side_member_size{sizeof(market_replay::MarketEvent::side)};
  std::size_t price_member_size{sizeof(market_replay::MarketEvent::price)};
  std::size_t quantity_member_size{
      sizeof(market_replay::MarketEvent::quantity)};

  std::size_t total_struct_member_size =
      timestamp_member_size + symbol_member_size + side_member_size +
      price_member_size + quantity_member_size;

  std::cout << "overall market event struct size: " << market_event_struct_size
            << " bytes\n";
  std::cout << "\ttimestamp member size: " << timestamp_member_size
            << " bytes\n";
  std::cout << "\tsymbol member size: " << symbol_member_size << " bytes\n";
  std::cout << "\tside member size: " << side_member_size << " bytes\n";
  std::cout << "\tprice member membersize: " << price_member_size << " bytes\n";
  std::cout << "\tquantity member size: " << quantity_member_size
            << " bytes\n\n";

  std::cout << "sum of market event struct member sizes: "
            << total_struct_member_size << " bytes\n";
  std::cout << "additional struct memory = total - sum of member sizes = "
            << market_event_struct_size << " bytes - "
            << total_struct_member_size << " bytes = "
            << market_event_struct_size - total_struct_member_size
            << " bytes\n";
}

void print_side_stats_sizes() {
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SideStats Struct "
               "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  std::size_t side_stats_struct_size{sizeof(market_replay::SideStats)};

  std::size_t count_member_size{sizeof(market_replay::SideStats::count)};
  std::size_t price_sum_member_size{
      sizeof(market_replay::SideStats::price_sum)};
  std::size_t min_price_member_size{
      sizeof(market_replay::SideStats::min_price)};
  std::size_t max_price_member_size{
      sizeof(market_replay::SideStats::max_price)};
  std::size_t volume_sum_member_size{
      sizeof(market_replay::SideStats::volume_sum)};
  std::size_t min_volume_member_size{
      sizeof(market_replay::SideStats::min_volume)};
  std::size_t max_volume_member_size{
      sizeof(market_replay::SideStats::max_volume)};

  std::size_t total_struct_member_size =
      count_member_size + price_sum_member_size + min_price_member_size +
      max_price_member_size + volume_sum_member_size + min_volume_member_size +
      max_volume_member_size;

  std::cout << "overall side stats struct size: " << side_stats_struct_size
            << " bytes\n";
  std::cout << "\tcount member size: " << count_member_size << " bytes\n";
  std::cout << "\tprice sum member size: " << price_sum_member_size
            << " bytes\n";
  std::cout << "\tmin price member size: " << min_price_member_size
            << " bytes\n";
  std::cout << "\tmax price member membersize: " << max_price_member_size
            << " bytes\n";
  std::cout << "\tvolume sum member size: " << volume_sum_member_size
            << " bytes\n";
  std::cout << "\tmin volume member size: " << min_volume_member_size
            << " bytes\n";
  std::cout << "\tmax volume member size: " << max_volume_member_size
            << " bytes\n\n";

  std::cout << "sum of side stats struct member sizes: "
            << total_struct_member_size << " bytes\n";
  std::cout << "additional struct memory = total - sum of member sizes = "
            << side_stats_struct_size << " bytes - " << total_struct_member_size
            << " bytes = " << side_stats_struct_size - total_struct_member_size
            << " bytes\n";
}

void print_ticker_stats_sizes() {
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ TickerStats Struct "
               "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  std::size_t ticker_stats_struct_size{sizeof(market_replay::TickerStats)};

  std::size_t buy_stats_member_size{
      sizeof(market_replay::TickerStats::buy_stats)};
  std::size_t sell_stats_member_size{
      sizeof(market_replay::TickerStats::sell_stats)};

  std::size_t total_struct_member_size =
      buy_stats_member_size + sell_stats_member_size;

  std::cout << "overall ticker stats struct size: " << ticker_stats_struct_size
            << " bytes\n";
  std::cout << "\tbuy stats member size: " << buy_stats_member_size
            << " bytes\n";
  std::cout << "\tsell stats member size: " << sell_stats_member_size
            << " bytes\n\n";

  std::cout << "sum of ticker stats struct member sizes: "
            << total_struct_member_size << " bytes\n";
  std::cout << "additional struct memory = total - sum of member sizes = "
            << ticker_stats_struct_size << " bytes - "
            << total_struct_member_size << " bytes = "
            << ticker_stats_struct_size - total_struct_member_size
            << " bytes\n";
}

void print_market_event_addresses() {
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MarketEvent Addresses "
               "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

  const market_replay::MarketEvent sample_market_event{
      1000000004, "AAPL", market_replay::Side::Buy, 430.16, 4890};

  std::cout << "MarketEvent addres: " << &sample_market_event << '\n';
  std::cout << "\ttimestamp member value: " << sample_market_event.timestamp
            << "\n\ttimestamp member address: "
            << &sample_market_event.timestamp << "\n\n";
  std::cout << "\tsymbol member value: " << sample_market_event.symbol
            << "\n\tsymbol member address: " << &sample_market_event.symbol
            << "\n\n";
  std::cout << "\tside member value: "
            << (sample_market_event.side == market_replay::Side::Buy ? "Buy"
                                                                     : "Sell")
            << "\n\tside member address: " << &sample_market_event.side
            << "\n\n";
  std::cout << "\tprice member value: " << sample_market_event.price
            << "\n\tprice member address: " << &sample_market_event.price
            << "\n\n";
  std::cout << "\tquantity member value: " << sample_market_event.quantity
            << "\n\tquantity member address: " << &sample_market_event.quantity
            << "\n";
}

int main() {
  print_market_event_sizes();
  std::cout << '\n';

  print_side_stats_sizes();
  std::cout << '\n';

  print_ticker_stats_sizes();
  std::cout << '\n';

  print_market_event_addresses();

  return 0;
}
