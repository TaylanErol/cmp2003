#include "term_project.h"

//WIP!!!
void dataSet::import_file(){
    // file pointer
    std::ifstream fin;

    // dosyanin basindaki UserID,ItemID gibi gelen aciklamalardan kurtulmak icin
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
        rowCount++;
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
};