#include "term_project.h"

int main() {
    dataSet myDataSet;
    myDataSet.import_and_save();
    //konsola yazdirmak uzun suruyor
    //myDataSet.printSaved();
    myDataSet.printTop10Users();
    myDataSet.printTop10Movies();
    return 0;
}
