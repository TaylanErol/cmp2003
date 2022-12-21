#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
//test

void selectionSort(int arr[], int arr2[], int n);
void swap(int *xp, int *yp);

struct node
{
    int itemID;
    float rating;
    node *link;
    node();
};

class dataSet{
public:
    void import_and_print();
    void import_and_save();
    void printSaved();
    void setFileName();
    void printTop10Users();
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
    std::multimap<int,node*> dataMap;
    std::string fileName;
};
