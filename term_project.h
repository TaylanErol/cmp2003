#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//test

struct node
{
    int userID;
    int itemID;
    float rating;
    node *link;
};

class dataSet{
public:
    void import_file();
    void import_and_save();
    void printSaved();
    void setFileName();
    int getRowCount();
    int getMovieCount();
    int getUserCount();
    std::string getFileName();
    dataSet();
    //private al test icin konuldu

private:
    int userCount;
    int movieCount;
    int rowCount;
    std::vector<node*> mainDataPointerVector;
    std::string fileName;

};
