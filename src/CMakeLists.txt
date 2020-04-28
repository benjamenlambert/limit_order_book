project(src)

set(HEADER_FILES
        Order.h
        OrderBook.h
        OrderUpdate.h
        PriceLevel.h
        Side.h
        Utilities.h
        )

set(SOURCE_FILES
        Order.cpp
        OrderBook.cpp
        PriceLevel.cpp
        Side.cpp
        Utilities.cpp
        )

add_library(src STATIC ${SOURCE_FILES} ${HEADER_FILES})