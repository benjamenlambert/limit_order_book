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
    std::vector<std::vector<std::string>> csv = data.ReadCSV("../data/20190612_9990.csv", true); // Partial file with headers
    //std::vector<std::vector<std::string>> csv = data.ReadCSV("../data/res_20190610.csv", true); // Full file

    int num_rows = csv.size();

    std::cout << "CSV contains " << num_rows << " rows.\n\n" << std::endl;

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

    int adds = 0;
    int removes = 0;
    int mods = 0;
    int price_changes = 0;

    for (int i = 0; i < num_rows; i++) {
        OrderUpdate update(std::stoull(csv[i][0]), csv[i][1][0], csv[i][2][0],
                std::stoi(csv[i][3]), std::stoi(csv[i][4]), std::stoi(csv[i][5]));

        if (update.GetAction() == 'a') {
            Order order(update);

            level.AddOrder(update.GetID(), order);
            //std::cout << "Adding order " << update.id_ << " with price " << update.price_ << std::endl;
            //std::cout << "Price level contains " << level.NumOrders() << " orders." << std::endl;
            adds ++;
        }
        else if (update.GetAction() == 'd') {
            level.RemoveOrder(update.GetID());
            //std::cout << "Deleting order " << update.id_ << " with price " << update.price_ << std::endl;
            //std::cout << "Price level contains " << level.NumOrders() << " orders." << std::endl;
            removes ++;
        }
        else {
            //std::cout << "Modifying order " << update.id_;
            //std::cout << " Previous qty = " << level.GetOrder(update.id_).GetQty();
            int prev_price = level.GetOrder(update.GetID()).GetPrice();
            //std::cout << " Previous price = " << prev_price << std::endl;

            level.ModifyOrder(update);

            //std::cout << "New qty = " << level.GetOrder(update.id_).GetQty();
            int new_price = level.GetOrder(update.GetID()).GetPrice();
            //std::cout << " New price = " << new_price << std::endl;
            //std::cout << "Price level contains " << level.NumOrders() << " orders." << std::endl;

            if (new_price != prev_price) {
                std::cout << "***** PRICE CHANGE ***** PRICE CHANGE ***** PRICE CHANGE *****" << std::endl;
                price_changes ++;
            }
            mods ++;
        }
    }

    std::cout << "************ REPORT ************" << std::endl;
    std::cout << "*                              *" << std::endl;
    std::cout << "* " << adds << " add order messages.     *" << std::endl;
    std::cout << "* " << removes << " remove order messages.  *" << std::endl;
    std::cout << "* " << mods << " modify qty messages.     *" << std::endl;
    std::cout << "* " << price_changes << " modify price messages.     *" << std::endl;
    std::cout << "* " << (adds + removes + mods)  << " total messages.        *" << std::endl;
    std::cout << "*                              *" << std::endl;
    std::cout << "********************************" << std::endl;

    //std::cout << "Price level contains the following " << level.NumOrders() << " orders:" << std::endl;

    //for (auto &iter: level.GetOrders()) {
    //    std::cout << "id: " << iter.first << " Qty: " << iter.second.GetQty() << std::endl;
    //}

    return 0;
}
