#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <numeric>
#include <cmath>
#include <unordered_map>

double euclidian_distance(const std::vector<std::pair<float, float>> &rating);
double cosine_similarity(const std::vector<std::pair<float, float>> &rating);
void selectionSort(int x[], int y[], int n);
void swap(int* ap, int* bp);
struct userNode
{
    std::unordered_map<int,float> ratedMoviesMap;
    double avgRating;
};

class dataSet{
public:
    double printAvgRating(int userID);
    void calcAvgRating();
    void exportToFile();
    void import_test();
    void import_and_save();
    void printSaved();
    void setFileName();
    void printTop10Users();
    void printTop10Movies();
    int getUniqueMovieCount();
    int getUniqueUserCount();
    dataSet();
private:
    std::unordered_map<int,std::vector<int>*> dataMovieMap;
    std::unordered_map<int,userNode*> dataUserMap;
    std::vector<std::pair<int,float>> exportData;
    std::string fileName;
};
