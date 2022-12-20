#include <iostream>
#include <fstream>
#include <string>
//test
class dataSet{
public:
    void import_file();
    void setFileName();
    int getRowCount();
    int getMovieCount();
    int getUserCount();
    std::string getFileName();
    dataSet();
private:
    int userCount;
    int movieCount;
    int rowCount;
    std::string fileName;

};
