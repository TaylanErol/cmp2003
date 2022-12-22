#include "term_project.h"

int main() {
    dataSet myDataSet;
    myDataSet.import_and_save();
    myDataSet.printTop10Users();
    std::cout<< myDataSet.getUniqueUserCount() << " \n";
    std::cout<< myDataSet.getUniqueMovieCount() << " \n";
   /* myDataSet.calcSimilarityIndex();
    myDataSet.import_test();*/

    return 0;
}
