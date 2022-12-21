#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
//test

struct node
{
    int userID;
    int itemID;
    float rating;
    node *link;
    node();
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
    int searchUser(int user);
    std::string getFileName();
    dataSet();
    //private al test icin konuldu

private:
    int userCount;
    int movieCount;
    int rowCount;
    std::multimap<int,node*> dataMap;
    std::vector<node*> mainDataPointerVector;
    std::string fileName;

};
