// Copyright 2026 Matthew Pearl

/*
To run tests:
1. In project root: cmake --build build --target market_replay_tests
2. cd build
3. ctest --output-on-failure
*/

#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <string>
#include <vector>

#include "market_replay/market_data_reader.hpp"
#include "market_replay/market_event.hpp"
#include "market_replay/market_replay.hpp"
#include "market_replay/market_statistics.hpp"

TEST_CASE("Valid market data CSV is parsed correctly") {
  const std::string path = "tests/data/valid_market_data.csv";

  const std::vector<market_replay::MarketEvent> events =
      market_replay::read_market_data_from_csv(path);

  REQUIRE(events.size() == 9);

  REQUIRE(events[0].timestamp == 1000);
  REQUIRE(events[0].symbol == "AAPL");
  REQUIRE(events[0].side == market_replay::Side::Buy);
  REQUIRE(events[0].price == 100.50);
  REQUIRE(events[0].quantity == 100);

  REQUIRE(events[1].timestamp == 1001);
  REQUIRE(events[1].symbol == "AAPL");
  REQUIRE(events[1].side == market_replay::Side::Sell);
  REQUIRE(events[1].price == 101.00);
  REQUIRE(events[1].quantity == 200);

  REQUIRE(events[2].timestamp == 1002);
  REQUIRE(events[2].symbol == "MSFT");
  REQUIRE(events[2].side == market_replay::Side::Buy);
  REQUIRE(events[2].price == 50.25);
  REQUIRE(events[2].quantity == 300);
}

TEST_CASE("Market data CSV with invalid rows skipped correctly") {
  const std::string path = "tests/data/invalid_market_data.csv";

  const std::vector<market_replay::MarketEvent> events =
      market_replay::read_market_data_from_csv(path);

  REQUIRE(events.size() == 3);

  REQUIRE(events[0].timestamp == 1000);
  REQUIRE(events[0].symbol == "AAPL");
  REQUIRE(events[0].side == market_replay::Side::Buy);
  REQUIRE(events[0].price == 100.50);
  REQUIRE(events[0].quantity == 100);

  REQUIRE(events[1].timestamp == 1001);
  REQUIRE(events[1].symbol == "AAPL");
  REQUIRE(events[1].side == market_replay::Side::Sell);
  REQUIRE(events[1].price == 101.00);
  REQUIRE(events[1].quantity == 200);

  REQUIRE(events[2].timestamp == 1003);
  REQUIRE(events[2].symbol == "MSFT");
  REQUIRE(events[2].side == market_replay::Side::Buy);
  REQUIRE(events[2].price == 50.25);
  REQUIRE(events[2].quantity == 300);
}

TEST_CASE("compute statistics correctly") {
  const std::string path = "tests/data/valid_market_data.csv";

  const std::vector<market_replay::MarketEvent> events =
      market_replay::read_market_data_from_csv(path);
  auto market_statistics = compute_market_data_statistics(events);

  const market_replay::TickerStats& aapl_stats = market_statistics.at("AAPL");
  const market_replay::SideStats& aapl_buy_stats = aapl_stats.buy_stats;
  const market_replay::SideStats& aapl_sell_stats = aapl_stats.sell_stats;

  REQUIRE(aapl_buy_stats.count == 2);
  REQUIRE(aapl_buy_stats.price_sum == Catch::Approx(321.00));
  REQUIRE(aapl_buy_stats.min_price == Catch::Approx(100.50));
  REQUIRE(aapl_buy_stats.max_price == Catch::Approx(220.50));
  REQUIRE(aapl_buy_stats.volume_sum == 350);
  REQUIRE(aapl_buy_stats.min_volume == 100);
  REQUIRE(aapl_buy_stats.max_volume == 250);
  REQUIRE(aapl_buy_stats.price_sum / aapl_buy_stats.count ==
          Catch::Approx(160.50));
  REQUIRE(static_cast<double>(aapl_buy_stats.volume_sum) /
              aapl_buy_stats.count ==
          Catch::Approx(175.0));

  REQUIRE(aapl_sell_stats.count == 4);
  REQUIRE(aapl_sell_stats.price_sum == Catch::Approx(489.00));
  REQUIRE(aapl_sell_stats.min_price == Catch::Approx(101.00));
  REQUIRE(aapl_sell_stats.max_price == Catch::Approx(143.00));
  REQUIRE(aapl_sell_stats.volume_sum == 1020);
  REQUIRE(aapl_sell_stats.min_volume == 120);
  REQUIRE(aapl_sell_stats.max_volume == 500);
  REQUIRE(aapl_sell_stats.price_sum / aapl_sell_stats.count ==
          Catch::Approx(122.25));
  REQUIRE(static_cast<double>(aapl_sell_stats.volume_sum) /
              aapl_sell_stats.count ==
          Catch::Approx(255.0));

  const market_replay::TickerStats& msft_stats = market_statistics.at("MSFT");
  const market_replay::SideStats& msft_buy_stats = msft_stats.buy_stats;
  const market_replay::SideStats& msft_sell_stats = msft_stats.sell_stats;

  REQUIRE(msft_buy_stats.count == 2);
  REQUIRE(msft_buy_stats.price_sum == Catch::Approx(111.00));
  REQUIRE(msft_buy_stats.min_price == Catch::Approx(50.25));
  REQUIRE(msft_buy_stats.max_price == Catch::Approx(60.75));
  REQUIRE(msft_buy_stats.volume_sum == 700);
  REQUIRE(msft_buy_stats.min_volume == 300);
  REQUIRE(msft_buy_stats.max_volume == 400);
  REQUIRE(msft_buy_stats.price_sum / msft_buy_stats.count ==
          Catch::Approx(55.50));
  REQUIRE(static_cast<double>(msft_buy_stats.volume_sum) /
              msft_buy_stats.count ==
          Catch::Approx(350.0));

  REQUIRE(msft_sell_stats.count == 0);

  const market_replay::TickerStats& tsla_stats = market_statistics.at("TSLA");
  const market_replay::SideStats& tsla_buy_stats = tsla_stats.buy_stats;
  const market_replay::SideStats& tsla_sell_stats = tsla_stats.sell_stats;

  REQUIRE(tsla_buy_stats.count == 0);

  REQUIRE(tsla_sell_stats.count == 1);
  REQUIRE(tsla_sell_stats.price_sum == Catch::Approx(230.00));
  REQUIRE(tsla_sell_stats.min_price == Catch::Approx(230.00));
  REQUIRE(tsla_sell_stats.max_price == Catch::Approx(230.00));
  REQUIRE(tsla_sell_stats.volume_sum == 130);
  REQUIRE(tsla_sell_stats.min_volume == 130);
  REQUIRE(tsla_sell_stats.max_volume == 130);
  REQUIRE(tsla_sell_stats.price_sum / tsla_sell_stats.count ==
          Catch::Approx(230.00));
  REQUIRE(static_cast<double>(tsla_sell_stats.volume_sum) /
              tsla_sell_stats.count ==
          Catch::Approx(130.0));
}