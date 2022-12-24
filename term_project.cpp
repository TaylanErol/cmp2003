#include "term_project.h"



void dataSet::setFileName(){
    std::cout << "Dosya adi girin: " << "\n";
    std::cin >> fileName;
}

dataSet::dataSet() {
    fileName = "";

}

void dataSet::exportToFile() {

    std::ofstream fout;
    fout.open("submission.csv");
    fout << "ID,Predicted\n";
    for (auto & i : exportData) {
        fout << i.first << "," << i.second << "\n";
    }

}

void dataSet::import_test(){
    //bu fonksiyon import file ile benzerlik gostermektedir ancak icindekileri yazdirmak yerine kaydeder
    // file pointer
    std::ifstream fin;
    // !!!daha guzel bir cozum bulunabilir!!! dosyanin basindaki UserID,ItemID gibi gelen aciklamalardan kurtulmak icin
    std::string firstCellPurge;

    //1. 2. 3. hucredeki verileri icine alacak
    std::string getID;
    std::string getUser;
    std::string getMovie;
    this->setFileName();
    // verilen dosyayi ac
    fin.open(fileName);

    // dosya aciliyormu kontrol etmek icin
    if(!fin.is_open()) std::cout << "ERROR: File couldn't be opened!" << '\n';

    //dosyanin basindaki ilk satiri cope at
    getline(fin,firstCellPurge,'\n');

    //dosya sonuna kadar devam eder
    while(fin.peek()!=EOF) {

        getline(fin, getID, ',');
        int fileID = std::stoi(getID);
        getline(fin, getUser, ',');
        int fileUser = std::stoi(getUser);
        getline(fin, getMovie, '\n');
        int fileMovie = std::stoi(getMovie);
        std::unordered_map<int,float>::const_iterator it2;
        double avgRating = dataUserMap.find(fileUser)->second->avgRating;
        auto it2begin = dataUserMap.find(fileUser)->second->ratedMoviesMap.begin();
        auto it2end = dataUserMap.find(fileUser)->second->ratedMoviesMap.end();
        int vectorSize = dataMovieMap.find(fileMovie)->second->size();
        std::vector<std::pair<double,int>> vscsAndCandidateID;
        for (int i = 0; i < vectorSize; ++i) {
            userNode *candidateNodePtr = dataUserMap.find(dataMovieMap.find(fileMovie)->second->at(i))->second;
            std::vector<std::pair<float,float>> file2CandidateRatingAVGDIFF;
            for (it2 = it2begin; it2 != it2end; ++it2) {
                    if (candidateNodePtr->ratedMoviesMap.count(it2->first) == 1){
                        /*std::cout << "Candidate ID: " << dataUserMap.find(dataMovieMap.find(fileMovie)->second->at(i))->first
                                  << " CandidateMovie: " << dataUserMap.find(dataMovieMap.find(fileMovie)->second->at(i))->second->ratedMoviesMap.find(it2->first)->first
                                  << " Candidate Rating: " << dataUserMap.find(dataMovieMap.find(fileMovie)->second->at(i))->second->ratedMoviesMap.find(it2->first)->second << "\n";
                        std::cout << "File User ID: " << dataUserMap.find(fileUser)->first
                                  << " File User Movie : " << it2->first
                                  << " File User Rating: " << it2->second << "\n";*/
                        file2CandidateRatingAVGDIFF.emplace_back(it2->second - avgRating,candidateNodePtr->ratedMoviesMap.find(it2->first)->second - candidateNodePtr->avgRating);
                }
            }
            if(file2CandidateRatingAVGDIFF.size() > 5) {
                double cossim = cosine_similarity(file2CandidateRatingAVGDIFF);
                double vscs = cossim; //* ((double) fileMovieRatings.size() / (double) dataUserMap.find(dataMovieMap.find(fileMovie)->second->at(i))->second->ratedMoviesMap.size());
                int candidateID = dataUserMap.find(dataMovieMap.find(fileMovie)->second->at(i))->first;
                /*std::cout << "File User ID: " << dataUserMap.find(fileUser)->first << ", "
                          << "Candidate ID: " << candidateID << ", Similarity: " << cossim
                          << " Vector Size: " << file2CandidateRatingAVGDIFF.size() << ", vs*cs: " << vscs << "\n";*/
                vscsAndCandidateID.emplace_back(vscs,candidateID); //Compiler emplace_back onerdi neden bilmiyorum ama daha hos duruyo :P
            }
        }

        double denominator = 0.0;
        double numerator = 0.0;
        for (auto & i : vscsAndCandidateID) {
            if (!std::isnan(i.first)) {
                numerator += i.first * (dataUserMap.find(i.second)->second->ratedMoviesMap.find(fileMovie)->second - dataUserMap.find(i.second)->second->avgRating);
                denominator += fabs(i.first);
                //std::cout << vscsAndCandidateID[i].first << " "<< vscsAndCandidateID[i].second << " r: " << dataUserMap.find(vscsAndCandidateID[i].second)->second->ratedMoviesMap.find(fileMovie)->second << std::endl;
            }
        }
        double rating = dataUserMap.find(fileUser)->second->avgRating + (numerator/denominator);
        exportData.emplace_back(fileID,rating);

        std::cout << "Recommended Rating: " << rating << " fileUserAvgRaating: " << dataUserMap.find(fileUser)->second->avgRating << " cossimEffect: " << numerator/denominator <<"\n";
        std::cout << "////////" << getID << " Mov: " << getMovie <<"---------------Finish File User ID: " << dataUserMap.find(fileUser)->first << "\n";

    }
    //dosyayi kapatir
    fin.close();
}


//kaydetmek dusundugumden hizli calisiyor mutluyum :))
void dataSet::import_and_save(){
    //bu fonksiyon import file ile benzerlik gostermektedir ancak icindekileri yazdirmak yerine kaydeder
    // file pointer
    std::ifstream fin;
    // !!!daha guzel bir cozum bulunabilir!!! dosyanin basindaki UserID,ItemID gibi gelen aciklamalardan kurtulmak icin
    std::string firstCellPurge;

    //1. 2. 3. hucredeki verileri icine alacak
    std::string getUser;
    std::string getMovie;
    std::string getRating;
    this->setFileName();
    // verilen dosyayi ac
    fin.open(fileName);

    // dosya aciliyormu kontrol etmek icin
    if(!fin.is_open()) std::cout << "ERROR: File couldn't be opened!" << '\n';

    //dosyanin basindaki ilk satiri cope at
    getline(fin,firstCellPurge,'\n');

    //dosya sonuna kadar devam eder
    while(fin.peek()!=EOF) {

        getline(fin, getUser, ',');
        int fileUser = std::stoi(getUser);
        getline(fin, getMovie, ',');
        int fileMovie = std::stoi(getMovie);
        getline(fin, getRating, '\n');
        float fileRating = std::stof(getRating);

        //Black Magic
        if(dataUserMap.count(fileUser) != 1 && dataMovieMap.count(fileMovie) != 1){

            userNode *node;
            node = new userNode;
            std::vector<int> *movieVector;
            movieVector = new std::vector<int>;
            movieVector->push_back(fileUser);
            node->ratedMoviesMap.insert(std::make_pair(fileMovie,fileRating));
            dataUserMap.insert(std::make_pair(fileUser,node));
            dataMovieMap.insert(std::make_pair(fileMovie,movieVector));

        } else if(dataUserMap.count(fileUser) != 1 && dataMovieMap.count(fileMovie) == 1){

            userNode *node;
            node = new userNode;
            node->ratedMoviesMap.insert(std::make_pair(fileMovie,fileRating));
            dataUserMap.insert(std::make_pair(fileUser,node));
            dataMovieMap.find(fileMovie)->second->push_back(fileUser);


        } else if(dataUserMap.count(fileUser) == 1 && dataMovieMap.count(fileMovie) != 1){

            std::vector<int> *movieVector;
            movieVector = new std::vector<int>;
            movieVector->push_back(fileUser);
            dataMovieMap.insert(std::make_pair(fileMovie,movieVector));
            dataUserMap.find(fileUser)->second->ratedMoviesMap.insert(std::make_pair(fileMovie,fileRating));


        } else if (dataUserMap.count(fileUser) == 1 && dataMovieMap.count(fileMovie) == 1){

            dataMovieMap.find(fileMovie)->second->push_back(fileUser);
            dataUserMap.find(fileUser)->second->ratedMoviesMap.insert(std::make_pair(fileMovie,fileRating));


        }
    }
    //dosyayi kapatir
    calcAvgRating();
    fin.close();
}

void dataSet::calcAvgRating(){
    std::unordered_map<int,userNode*>::const_iterator it;
    for (it = dataUserMap.begin(); it != dataUserMap.end(); ++it){
        std::unordered_map<int,float>::const_iterator it2;
        double totalRating = 0.0;
        for (it2 = it->second->ratedMoviesMap.begin(); it2 != it->second->ratedMoviesMap.end(); ++it2) {
            totalRating += it2->second;
        }
        it->second->avgRating = totalRating/it->second->ratedMoviesMap.size();
    }
}

//konsola yazdirmak bi 6-7 dk suruyor
void dataSet::printSaved(){
    std::cout << "~~~~~~~~~~~~~~~~" << '\n';
    std::unordered_map<int,userNode*>::const_iterator it;
    for (it = dataUserMap.begin(); it != dataUserMap.end(); ++it)
    {
        std::cout << "USERID: "<< it->first <<'\n';
        std::cout << "AVGRATING: " << it->second->avgRating << '\n';
        std::unordered_map<int,float>::const_iterator it2;
        for (it2 = it->second->ratedMoviesMap.begin(); it2 != it->second->ratedMoviesMap.end(); ++it2) {
            std::cout << "/////////////" << '\n';
            std::cout << "ITEMID: "<< it2->first << '\n';
            std::cout << "RATING: "<< it2->second << '\n';
            std::cout << "/////////////" << '\n';
        }
        std::cout << "~~~~~~~~~~~~~~~~" << '\n';
    }
}
void dataSet::printTop10Users() {
    std::unordered_map <int,userNode*>::const_iterator it;
    int topUserID[10] = {0,0,0,0,0,0,0,0,0,0};
    int topUserCount[10] = {0,0,0,0,0,0,0,0,0,0};

    for (it = dataUserMap.begin(); it != dataUserMap.end(); ++it)
    {
            if(it->second->ratedMoviesMap.size() > topUserCount[0]) {
                topUserID[0] = it->first;
                topUserCount[0] = it->second->ratedMoviesMap.size();
                selectionSort(topUserCount,topUserID, 10);
            }
    }
    for (int i = 0; i < 10; ++i) {
        std::cout << "[" << topUserID[i] << "," << topUserCount[i] << "]";
    }
    std::cout << "\n";
}

void dataSet::printTop10Movies(){
    std::unordered_map <int,std::vector<int>*>::const_iterator it;
    int topMovieID[10] = {0,0,0,0,0,0,0,0,0,0};
    int topMovieCount[10] = {0,0,0,0,0,0,0,0,0,0};

    for (it = dataMovieMap.begin(); it != dataMovieMap.end(); ++it)
    {
        if(it->second->size() > topMovieCount[0]) {
            topMovieID[0] = it->first;
            topMovieCount[0] = it->second->size();
            selectionSort(topMovieCount,topMovieID, 10);
        }
    }
    for (int i = 0; i < 10; ++i) {
        std::cout << "[" << topMovieID[i] << "," << topMovieCount[i] << "]";
    }
    std::cout << "\n";
}

int dataSet::getUniqueUserCount() {
    return dataUserMap.size();
}

int dataSet::getUniqueMovieCount() {
    return dataMovieMap.size();
}
//WIP
/*void dataSet::calcSimilarityIndex() {
    std::map <int,userNode*>::const_iterator it;
    for (it = dataUserMap.begin(); it != dataUserMap.end(); ++it)
    {
        it->second->similarityIndex = cosine_similarity(it->second->ratedMovies,it->second->ratings,it->second->ratedMovies.size());
        //std::cout << "USERID: "<< it->first << " SimilarityWeight: "<< it->second->similarityIndex << "\n";
    }
}*/

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

double dataSet::printAvgRating(int userID) {

    return dataUserMap.find(userID)->second->avgRating;

}

double cosine_similarity(const std::vector<std::pair<float, float>> &rating)
{
    double dotp = 0.0;
    double bolum_a = 0.0;
    double bolum_b = 0.0 ;
    for(auto & i : rating) {
        dotp += i.first * i.second ;
        bolum_a += i.first * i.first ;
        bolum_b += i.second * i.second ;
        //std::cout << "dotp: " <<dotp << " bolum_a: " << bolum_a<< " bolum_b: " << bolum_b << "\n";
    }
    return dotp / (sqrt(bolum_a) * sqrt(bolum_b)) ;
}
/*
double cosine_similarity(std::vector<float> ratingA, std::vector<float> ratingB, int vectorSize)
{
    double dotp = 0.0;
    double bolum_a = 0.0;
    double bolum_b = 0.0 ;
    for(int i = 0; i < vectorSize; ++i) {
        dotp += ratingA[i] * ratingB[i] ;
        bolum_a += ratingA[i] * ratingA[i] ;
        bolum_b += ratingB[i] * ratingB[i] ;
    }
    return dotp / (sqrt(bolum_a) * sqrt(bolum_b)) ;*/
