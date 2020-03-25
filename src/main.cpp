#include "HistoricalData.h"

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
    //std::vector<std::vector<std::string>> csv = data.ReadCSV("../data/data_headers.csv", true); // Partial file with headers
    std::vector<std::vector<std::string>> csv = data.ReadCSV("../data/res_20190610.csv", true); // Full file

    std::cout << "CSV contains " << csv.size() << " rows." << std::endl;

    // Output csv contents
    /*
    int num_rows = csv.size();
    int num_cols = csv[0].size();

    for (int i = 0; i < num_rows; i++) {
        for (int j = 0; j < num_cols; j++)
            std::cout << csv[i][j] << " ";
        std::cout << std::endl;
    }
    for (int i = 0; i < num_rows; i++) {
        std::cout << "Timestamp : " << data.ProcessLine(csv[i]).timestamp_ << " Price : " << data.ProcessLine(csv[i]).price_ << std::endl;
    }
     */

    return 0;
}
