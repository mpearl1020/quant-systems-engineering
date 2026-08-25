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
      market_replay::readMarketDataFromCSV(path);

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
      market_replay::readMarketDataFromCSV(path);

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
      market_replay::readMarketDataFromCSV(path);
  auto marketStatistics = computeMarketDataStatistics(events);

  const market_replay::TickerStats& aaplStats = marketStatistics.at("AAPL");
  const market_replay::SideStats& aaplBuyStats = aaplStats.buyStats;
  const market_replay::SideStats& aaplSellStats = aaplStats.sellStats;

  REQUIRE(aaplBuyStats.count == 2);
  REQUIRE(aaplBuyStats.priceSum == Catch::Approx(321.00));
  REQUIRE(aaplBuyStats.minPrice == Catch::Approx(100.50));
  REQUIRE(aaplBuyStats.maxPrice == Catch::Approx(220.50));
  REQUIRE(aaplBuyStats.volumeSum == 350);
  REQUIRE(aaplBuyStats.minVolume == 100);
  REQUIRE(aaplBuyStats.maxVolume == 250);
  REQUIRE(aaplBuyStats.priceSum / aaplBuyStats.count == Catch::Approx(160.50));
  REQUIRE(static_cast<double>(aaplBuyStats.volumeSum) / aaplBuyStats.count ==
          Catch::Approx(175.0));

  REQUIRE(aaplSellStats.count == 4);
  REQUIRE(aaplSellStats.priceSum == Catch::Approx(489.00));
  REQUIRE(aaplSellStats.minPrice == Catch::Approx(101.00));
  REQUIRE(aaplSellStats.maxPrice == Catch::Approx(143.00));
  REQUIRE(aaplSellStats.volumeSum == 1020);
  REQUIRE(aaplSellStats.minVolume == 120);
  REQUIRE(aaplSellStats.maxVolume == 500);
  REQUIRE(aaplSellStats.priceSum / aaplSellStats.count ==
          Catch::Approx(122.25));
  REQUIRE(static_cast<double>(aaplSellStats.volumeSum) / aaplSellStats.count ==
          Catch::Approx(255.0));

  const market_replay::TickerStats& msftStats = marketStatistics.at("MSFT");
  const market_replay::SideStats& msftBuyStats = msftStats.buyStats;
  const market_replay::SideStats& msftSellStats = msftStats.sellStats;

  REQUIRE(msftBuyStats.count == 2);
  REQUIRE(msftBuyStats.priceSum == Catch::Approx(111.00));
  REQUIRE(msftBuyStats.minPrice == Catch::Approx(50.25));
  REQUIRE(msftBuyStats.maxPrice == Catch::Approx(60.75));
  REQUIRE(msftBuyStats.volumeSum == 700);
  REQUIRE(msftBuyStats.minVolume == 300);
  REQUIRE(msftBuyStats.maxVolume == 400);
  REQUIRE(msftBuyStats.priceSum / msftBuyStats.count == Catch::Approx(55.50));
  REQUIRE(static_cast<double>(msftBuyStats.volumeSum) / msftBuyStats.count ==
          Catch::Approx(350.0));

  REQUIRE(msftSellStats.count == 0);

  const market_replay::TickerStats& tslaStats = marketStatistics.at("TSLA");
  const market_replay::SideStats& tslaBuyStats = tslaStats.buyStats;
  const market_replay::SideStats& tslaSellStats = tslaStats.sellStats;

  REQUIRE(tslaBuyStats.count == 0);

  REQUIRE(tslaSellStats.count == 1);
  REQUIRE(tslaSellStats.priceSum == Catch::Approx(230.00));
  REQUIRE(tslaSellStats.minPrice == Catch::Approx(230.00));
  REQUIRE(tslaSellStats.maxPrice == Catch::Approx(230.00));
  REQUIRE(tslaSellStats.volumeSum == 130);
  REQUIRE(tslaSellStats.minVolume == 130);
  REQUIRE(tslaSellStats.maxVolume == 130);
  REQUIRE(tslaSellStats.priceSum / tslaSellStats.count ==
          Catch::Approx(230.00));
  REQUIRE(static_cast<double>(tslaSellStats.volumeSum) / tslaSellStats.count ==
          Catch::Approx(130.0));
}