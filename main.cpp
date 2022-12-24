#include "term_project.h"
#include <chrono>

int main() {
    dataSet myDataSet;
    myDataSet.import_and_save();
    //myDataSet.printSaved();
    myDataSet.import_test();
    myDataSet.exportToFile();



    return 0;
}
