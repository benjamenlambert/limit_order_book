project(src)

set(HEADER_FILES
        HistoricalData.h
        MarketData.h
        Event.h
        Order.h
        OrderBook.h
        OrderUpdate.h
        PriceLevel.h
        Side.h
        )

set(SOURCE_FILES
        HistoricalData.cpp
        MarketData.cpp
        Event.cpp
        Order.cpp
        OrderBook.cpp
        PriceLevel.cpp
        Side.cpp
        )

add_library(src STATIC ${SOURCE_FILES} ${HEADER_FILES})