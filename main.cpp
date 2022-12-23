#include "term_project.h"
#include <chrono>

int main() {
    // Using time point and system_clock
    std::chrono::time_point<std::chrono::system_clock> start, end;

    start = std::chrono::system_clock::now();
    dataSet myDataSet;
    myDataSet.import_and_save();
    myDataSet.import_test();
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);

    std::cout << "finished computation at " << std::ctime(&end_time)
              << "elapsed time: " << elapsed_seconds.count() << "s\n";

    //myDataSet.printSaved();
    //std::cout<< myDataSet.getUniqueUserCount() << " \n";
    //std::cout<< myDataSet.getUniqueMovieCount() << " \n";
   /* myDataSet.calcSimilarityIndex();
    myDataSet.import_test();*/

    return 0;
}
