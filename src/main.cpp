#include <iostream>
#include "MarketData.h"

int main() {

    MarketData data;

    //data.ReadCSV("../data/data.csv"); // Partial file
    data.ReadCSV("../data/data_headers.csv", true); // Partial file with headers
    //data.ReadCSV("../data/res_20190610.csv", true); // Full file

    return 0;
}
