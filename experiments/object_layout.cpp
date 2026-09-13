// Copyright 2026 Matthew Pearl

#include <iostream>

#include "market_replay/market_event.hpp"

void printMarketEventSizes() {
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MarketEvent Struct "
               "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  std::size_t marketEventStructSize{sizeof(market_replay::MarketEvent)};

  std::size_t timestampMemberSize{
      sizeof(market_replay::MarketEvent::timestamp)};
  std::size_t symbolMemberSize{sizeof(market_replay::MarketEvent::symbol)};
  std::size_t sideMemberSize{sizeof(market_replay::MarketEvent::side)};
  std::size_t priceMemberSize{sizeof(market_replay::MarketEvent::price)};
  std::size_t quantityMemberSize{sizeof(market_replay::MarketEvent::quantity)};

  std::size_t totalStructMemberSize = timestampMemberSize + symbolMemberSize +
                                      sideMemberSize + priceMemberSize +
                                      quantityMemberSize;

  std::cout << "overall market event struct size: " << marketEventStructSize
            << " bytes\n";
  std::cout << "\ttimestamp member size: " << timestampMemberSize << " bytes\n";
  std::cout << "\tsymbol member size: " << symbolMemberSize << " bytes\n";
  std::cout << "\tside member size: " << sideMemberSize << " bytes\n";
  std::cout << "\tprice member membersize: " << priceMemberSize << " bytes\n";
  std::cout << "\tquantity member size: " << quantityMemberSize << " bytes\n\n";

  std::cout << "sum of market event struct member sizes: "
            << totalStructMemberSize << " bytes\n";
  std::cout << "additional struct memory = total - sum of member sizes = "
            << marketEventStructSize << " bytes - " << totalStructMemberSize
            << " bytes = " << marketEventStructSize - totalStructMemberSize
            << " bytes\n";
}

void printSideStatsSizes() {
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ SideStats Struct "
               "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  std::size_t sideStatstructSize{sizeof(market_replay::SideStats)};

  std::size_t countMemberSize{sizeof(market_replay::SideStats::count)};
  std::size_t priceSumMemberSize{sizeof(market_replay::SideStats::priceSum)};
  std::size_t minPriceMemberSize{sizeof(market_replay::SideStats::minPrice)};
  std::size_t maxPriceMemberSize{sizeof(market_replay::SideStats::maxPrice)};
  std::size_t volumeSumMemberSize{sizeof(market_replay::SideStats::volumeSum)};
  std::size_t minVolumeMemberSize{sizeof(market_replay::SideStats::minVolume)};
  std::size_t maxVolumeMemberSize{sizeof(market_replay::SideStats::maxVolume)};

  std::size_t totalStructMemberSize = countMemberSize + priceSumMemberSize +
                                      minPriceMemberSize + maxPriceMemberSize +
                                      volumeSumMemberSize +
                                      minVolumeMemberSize + maxVolumeMemberSize;

  std::cout << "overall side stats struct size: " << sideStatstructSize
            << " bytes\n";
  std::cout << "\tcount member size: " << countMemberSize << " bytes\n";
  std::cout << "\tprice sum member size: " << priceSumMemberSize << " bytes\n";
  std::cout << "\tmin price member size: " << minPriceMemberSize << " bytes\n";
  std::cout << "\tmax price member membersize: " << maxPriceMemberSize
            << " bytes\n";
  std::cout << "\tvolume sum member size: " << volumeSumMemberSize
            << " bytes\n";
  std::cout << "\tmin volume member size: " << minVolumeMemberSize
            << " bytes\n";
  std::cout << "\tmax volume member size: " << maxVolumeMemberSize
            << " bytes\n\n";

  std::cout << "sum of side stats struct member sizes: "
            << totalStructMemberSize << " bytes\n";
  std::cout << "additional struct memory = total - sum of member sizes = "
            << sideStatstructSize << " bytes - " << totalStructMemberSize
            << " bytes = " << sideStatstructSize - totalStructMemberSize
            << " bytes\n";
}

void printTickerStatsSizes() {
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ TickerStats Struct "
               "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
  std::size_t tickerStatsStructSize{sizeof(market_replay::TickerStats)};

  std::size_t buyStatsMemberSize{sizeof(market_replay::TickerStats::buyStats)};
  std::size_t sellStatsMemberSize{
      sizeof(market_replay::TickerStats::sellStats)};

  std::size_t totalStructMemberSize = buyStatsMemberSize + sellStatsMemberSize;

  std::cout << "overall ticker stats struct size: " << tickerStatsStructSize
            << " bytes\n";
  std::cout << "\tbuy stats member size: " << buyStatsMemberSize << " bytes\n";
  std::cout << "\tsell stats member size: " << sellStatsMemberSize
            << " bytes\n\n";

  std::cout << "sum of ticker stats struct member sizes: "
            << totalStructMemberSize << " bytes\n";
  std::cout << "additional struct memory = total - sum of member sizes = "
            << tickerStatsStructSize << " bytes - " << totalStructMemberSize
            << " bytes = " << tickerStatsStructSize - totalStructMemberSize
            << " bytes\n";
}

void printMarketEventAddresses() {
  std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MarketEvent Addresses "
               "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";

  const market_replay::MarketEvent sampleMarketEvent{
      1000000004, "AAPL", market_replay::Side::Buy, 430.16, 4890};

  std::cout << "MarketEvent addres: " << &sampleMarketEvent << '\n';
  std::cout << "\ttimestamp member value: " << sampleMarketEvent.timestamp
            << "\n\ttimestamp member address: " << &sampleMarketEvent.timestamp
            << "\n\n";
  std::cout << "\tsymbol member value: " << sampleMarketEvent.symbol
            << "\n\tsymbol member address: " << &sampleMarketEvent.symbol
            << "\n\n";
  std::cout << "\tside member value: "
            << (sampleMarketEvent.side == market_replay::Side::Buy ? "Buy"
                                                                   : "Sell")
            << "\n\tside member address: " << &sampleMarketEvent.side << "\n\n";
  std::cout << "\tprice member value: " << sampleMarketEvent.price
            << "\n\tprice member address: " << &sampleMarketEvent.price
            << "\n\n";
  std::cout << "\tquantity member value: " << sampleMarketEvent.quantity
            << "\n\tquantity member address: " << &sampleMarketEvent.quantity
            << "\n";
}

int main() {
  printMarketEventSizes();
  std::cout << '\n';

  printSideStatsSizes();
  std::cout << '\n';

  printTickerStatsSizes();
  std::cout << '\n';

  printMarketEventAddresses();

  return 0;
}
