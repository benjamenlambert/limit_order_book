#include "HistoricalData.h"
#include "Order.h"
#include "PriceLevel.h"

int main() {

    HistoricalData data;

    // Create a pointer to a csv created in heap memory in ReadCSV
    /*
    std::vector<std::vector<std::string>> *csv = data.ReadCSV("../data/data_headers.csv", true); // Partial file

    std::cout << "CSV file contains:" << std::endl;

    int num_rows = csv->size();
    int num_cols = (*csv)[0].size();

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++)
            std::cout << (*csv)[i][j] << " ";
        std::cout << std::endl;
    }

    delete(csv);
    csv = nullptr;
*/

    // Copy csv from ReadCSV stack
    //data.ReadCSV("../data/hash_data.csv"); // Partial file
    std::vector<std::vector<std::string>> csv = data.ReadCSV("../data/data_9990.csv", true); // Partial file with headers
    //std::vector<std::vector<std::string>> csv = data.ReadCSV("../data/res_20190610.csv", true); // Full file

    int num_rows = csv.size();

    std::cout << "CSV contains " << num_rows << " rows." << std::endl;

     // Output csv contents
    /*
    int num_cols = csv[0].size();

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++)
            std::cout << csv[i][j] << " ";
        std::cout << std::endl;
    }
     */

    PriceLevel level;

    for (int i = 0; i < num_rows; i++) {
        OrderUpdate update(std::stoull(csv[i][0]), csv[i][1][0], csv[i][2][0],
                std::stoi(csv[i][3]), std::stoi(csv[i][4]), std::stoi(csv[i][5]));

        level.AddOrder(update);
    }

    std::cout << "Price level contains " << level.NumOrders() << " orders." << std::endl;

    for (auto &iter: level.GetOrders()) {
        std::cout << "id: " << iter.first << " Qty: " << iter.second.GetQty() << std::endl;
    }

    return 0;
}
