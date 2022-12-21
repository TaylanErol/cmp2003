#include "term_project.h"

void dataSet::import_file(){
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
    while(fin.peek()!=EOF){

        getline(fin,getcell1,',');
        getline(fin,getcell2,',');
        getline(fin,getcell3,'\n');


        //ONEMLI!!! calisiyor ama pointeri heape mi stackemi koyuyo emin degilim, node heapte ondan eminim ama :PP
        node* row = new node;
        mainDataPointerVector.push_back(row);
        row->userID = std::stoi(getcell1);
        row->itemID = std::stoi(getcell2);
        row->rating = std::stof(getcell3);
    }

    //dosyayi kapatir
    fin.close();
}

//konsola yazdirmak bi 6-7 dk suruyor
void dataSet::printSaved(){
    node* print;
    for (int i = 0; i < mainDataPointerVector.size(); ++i) {
        print = mainDataPointerVector.at(i);
        std::cout << print->userID  << ","<< print -> itemID << ","<< print->rating << " \n";
    }
}