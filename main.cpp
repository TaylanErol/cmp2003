#include "term_project.h"
#include <chrono>

int main() {
    dataSet myDataSet;
    myDataSet.import_and_save();
    auto start = std::chrono::steady_clock::now();
    myDataSet.printTop10Movies();
    myDataSet.printTop10Users();
    //myDataSet.printSaved();
    myDataSet.import_test();
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    myDataSet.exportToFile();



    return 0;
}
