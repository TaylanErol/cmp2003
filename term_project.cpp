#include "term_project.h"

node::node(){
    link = nullptr;
}

void dataSet::import_and_print(){
    // file pointer
    std::ifstream fin;

    // !!!daha guzel bir cozum bulunabilir!!! dosyanin basindaki UserID,ItemID gibi gelen aciklamalardan kurtulmak icin
    std::string firstCellPurge;

    //1. 2. 3. hucredeki verileri icine alacak
    std::string getcell1;
    std::string getcell2;
    std::string getcell3;
    this->setFileName();
    // verilen dosyayi ac
    fin.open(fileName);

    // dosya aciliyormu kontrol etmek icin
    if(!fin.is_open()) std::cout << "ERROR: File couldn't be opened!" << '\n';

    //dosyanin basindaki ilk satiri cope at
    getline(fin,firstCellPurge,'\n');

    //dosya sonuna kadar devam eder
    while(fin.peek()!=EOF){

        getline(fin,getcell1,',');
        getline(fin,getcell2,',');
        getline(fin,getcell3,'\n');

        //printlemeden once stringi floata cevirir
        std::cout << "USERID: "<< std::stof(getcell1) <<'\n';
        std::cout << "ITEMID: "<< std::stof(getcell2) << '\n';
        std::cout << "RATING: "<< std::stof(getcell3) << '\n';
        std::cout << "-------------------" << '\n';
    }

    //dosyayi kapatir
    fin.close();
}

void dataSet::setFileName(){
    std::cout << "Dosya adi girin: " << "\n";
    std::cin >> fileName;
}

std::string dataSet::getFileName() {
    return fileName;
}

dataSet::dataSet() {
    userCount = 0;
    movieCount = 0;
    rowCount = 0;
    fileName = "";

}

//kaydetmek dusundugumden hizli calisiyor mutluyum :))
void dataSet::import_and_save(){
    //bu fonksiyon import file ile benzerlik gostermektedir ancak icindekileri yazdirmak yerine kaydeder
    // file pointer
    std::ifstream fin;
    // !!!daha guzel bir cozum bulunabilir!!! dosyanin basindaki UserID,ItemID gibi gelen aciklamalardan kurtulmak icin
    std::string firstCellPurge;

    //1. 2. 3. hucredeki verileri icine alacak
    std::string getcell1;
    std::string getcell2;
    std::string getcell3;
    this->setFileName();
    // verilen dosyayi ac
    fin.open(fileName);

    // dosya aciliyormu kontrol etmek icin
    if(!fin.is_open()) std::cout << "ERROR: File couldn't be opened!" << '\n';

    //dosyanin basindaki ilk satiri cope at
    getline(fin,firstCellPurge,'\n');

    //dosya sonuna kadar devam eder
    while(fin.peek()!=EOF) {

        getline(fin, getcell1, ',');
        getline(fin, getcell2, ',');
        getline(fin, getcell3, '\n');

        //Black Magic
        node *row = new node;
        row->itemID = std::stoi(getcell2);
        row->rating = std::stof(getcell3);
        dataMap.insert(std::pair<int, node *>(std::stoi(getcell1), row));

    }

    //dosyayi kapatir
    fin.close();
}

//konsola yazdirmak bi 6-7 dk suruyor
void dataSet::printSaved(){

    std::multimap <int,node*>::const_iterator it;
    for (it = dataMap.begin(); it != dataMap.end(); ++it)
    {
        std::cout << "USERID: "<< it->first <<'\n';
        std::cout << "ITEMID: "<< it->second->itemID << '\n';
        std::cout << "RATING: "<< it->second->rating << '\n';
        std::cout << "~~~~~~~~~~~~~~~~" << '\n';
    }
}

void dataSet::printTop10Users() {
    std::multimap <int,node*>::const_iterator it;
    int topUserID[10] = {0,0,0,0,0,0,0,0,0,0};
    int topUserCount[10] = {0,0,0,0,0,0,0,0,0,0};
    int itPrev = -1;
    for (it = dataMap.begin(); it != dataMap.end(); ++it)
    {
        if(it->first != itPrev) {
            if(dataMap.count(it->first) > topUserCount[0]) {
                topUserID[0] = it->first;
                topUserCount[0] = dataMap.count(it->first);
                selectionSort(topUserCount,topUserID, 10);
            }
        }
        itPrev = it->first;
    }
    for (int i = 0; i < 10; ++i) {
        std::cout << "[" << topUserID[i] << "," << topUserCount[i] << "]";
    }
    std::cout << "\n";
}

void dataSet::printTop10Movies(){
    std::multimap <int,node*>::const_iterator it;
    std::multimap <int,node*>::const_iterator it2;
    int topMovieID[10] = {0,0,0,0,0,0,0,0,0,0};
    int topMovieCount[10] = {0,0,0,0,0,0,0,0,0,0};
    for (it = dataMap.begin(); it != dataMap.end(); ++it)
    {
        int count = 0;
        for (it2 = dataMap.begin(); it2 != dataMap.end(); ++it2)
        {
            if(it2->second->itemID == it->second->itemID) {
                count++;
            }
                if(topMovieCount[0] < count){
                    topMovieID[0] = it->second->itemID;
                    topMovieCount[0] = count;
                    selectionSort(topMovieCount, topMovieID, 10);
            }
        }
    }
    for (int i = 0; i < 10; ++i) {
        std::cout << "[" << topMovieID[i] << "," << topMovieCount[i] << "]";
    }
    std::cout << "\n";
}

//TAKEN FROM GEEKS FOR GEEKS
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

//TAKEN FROM GEEKS FOR GEEKS
void selectionSort(int arr[], int arr2[], int n)
{
    int i, j, min_idx;

    // One by one move boundary of
    // unsorted subarray
    for (i = 0; i < n-1; i++)
    {

        // Find the minimum element in
        // unsorted array
        min_idx = i;
        for (j = i+1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        // Swap the found minimum element
        // with the first element
        if(min_idx!=i) {
            swap(&arr[min_idx], &arr[i]);
            swap(&arr2[min_idx], &arr2[i]);
        }
    }
}