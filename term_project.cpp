#include "term_project.h"



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

void dataSet::exportToFile() {

    std::ofstream fout;
    fout.open("submission.csv");
    fout << "ID,Predicted\n";
    for (int i = 0; i < exportData.size() ; ++i) {
        fout << exportData[i].first << "," << exportData[i].second;
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
        std::map <int,float>::const_iterator it2;
        std::map <int,float>::const_iterator it2begin = dataUserMap.find(fileUser)->second->ratedMoviesMap.begin();
        std::map <int,float>::const_iterator it2end = dataUserMap.find(fileUser)->second->ratedMoviesMap.end();
        std::map<int, float> fileUserMapPtr  = dataUserMap.find(fileUser)->second->ratedMoviesMap;
        int vectorSize = dataMovieMap.find(fileMovie)->second->size();
        std::vector<std::pair<double,int>> vscsAndCandidateID;
        for (int i = 0; i < vectorSize; ++i) {
            std::vector<float> fileMovieRatings;
            std::vector<float> candidateMovieRatings;
            std::map <int,float>::const_iterator it;
            for (it2 = it2begin; it2 != it2end; ++it2) {
                    if (dataUserMap.find(dataMovieMap.find(fileMovie)->second->at(i))->second->ratedMoviesMap.count(it2->first) == 1){
                        /*std::cout << "Candidate ID: " << dataUserMap.find(dataMovieMap.find(fileMovie)->second->at(i))->first
                                  << " CandidateMovie: " << dataUserMap.find(dataMovieMap.find(fileMovie)->second->at(i))->second->ratedMoviesMap.find(it2->first)->first
                                  << " Candidate Rating: " << dataUserMap.find(dataMovieMap.find(fileMovie)->second->at(i))->second->ratedMoviesMap.find(it2->first)->second << "\n";
                        std::cout << "File User ID: " << dataUserMap.find(fileUser)->first
                                  << " File User Movie : " << it2->first
                                  << " File User Rating: " << it2->second << "\n";*/
                        fileMovieRatings.push_back(it2->second);
                        candidateMovieRatings.push_back(dataUserMap.find(dataMovieMap.find(fileMovie)->second->at(i))->second->ratedMoviesMap.find(it2->first)->second);
                }
            }
            if(fileMovieRatings.size() != 0) {
                double cossim = cosine_similarity(fileMovieRatings, candidateMovieRatings, fileMovieRatings.size());
                double vscs = cossim * ((double) fileMovieRatings.size() / (double) dataUserMap.find(dataMovieMap.find(fileMovie)->second->at(i))->second->ratedMoviesMap.size());
                int candidateID = dataUserMap.find(dataMovieMap.find(fileMovie)->second->at(i))->first;
                /*std::cout << "File User ID: " << dataUserMap.find(fileUser)->first << ", "
                          << "Candidate ID: " << candidateID << ", Similarity: " << cossim
                          << " Vector Size: " << fileMovieRatings.size() << ", vs*cs: " << vscs << "\n";*/
                vscsAndCandidateID.emplace_back(vscs,candidateID); //Compiler emplace_back onerdi neden bilmiyorum ama daha hos duruyo :P
            }
        }
        std::sort(vscsAndCandidateID.begin(), vscsAndCandidateID.end());
        int count = 0;
        float candidateRatingAddition = 0.0;
        for (int i = vscsAndCandidateID.size() - 1; i > 0 && count < 3; i--) {
            if (std::isnan(vscsAndCandidateID[i].first) == false) {
                // "first" and "second" are used to access
                // 1st and 2nd element of pair respectively
                float candidateRating = dataUserMap.find(vscsAndCandidateID[i].second)->second->ratedMoviesMap.find(fileMovie)->second;
                /*std::cout << vscsAndCandidateID[i].first << " "<< vscsAndCandidateID[i].second << std::endl;*/
                candidateRatingAddition += candidateRating;
                count++;
            }
        }
        double rating = (double)candidateRatingAddition/count;
        exportData.emplace_back(fileID,rating);

        /*std::cout << "Recommended Rating: " << rating << "\n";
        std::cout << "////////" << getID <<"---------------Finish File User ID: " << dataUserMap.find(fileUser)->first << "\n";*/

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
        getline(fin, getMovie, ',');
        getline(fin, getRating, '\n');


        //Black Magic
        if(dataUserMap.count(std::stoi(getUser)) != 1 && dataMovieMap.count(std::stoi(getMovie)) != 1){

            userNode *node;
            node = new userNode;
            std::vector<int> *movieVector;
            movieVector = new std::vector<int>;
            movieVector->push_back(std::stoi(getUser));
            node->ratedMoviesMap.insert(std::pair<int,float>(std::stoi(getMovie),std::stof(getRating)));
            dataUserMap.insert(std::pair<int,userNode*>(std::stoi(getUser),node));
            dataMovieMap.insert(std::pair<int,std::vector<int>*>(std::stoi(getMovie),movieVector));

        } else if(dataUserMap.count(std::stoi(getUser)) != 1 && dataMovieMap.count(std::stoi(getMovie)) == 1){

            userNode *node;
            node = new userNode;
            node->ratedMoviesMap.insert(std::pair<int,float>(std::stoi(getMovie),std::stof(getRating)));
            dataUserMap.insert(std::pair<int,userNode*>(std::stoi(getUser),node));
            dataMovieMap.find(std::stoi(getMovie))->second->push_back(std::stoi(getUser));

        } else if(dataUserMap.count(std::stoi(getUser)) == 1 && dataMovieMap.count(std::stoi(getMovie)) != 1){

            std::vector<int> *movieVector;
            movieVector = new std::vector<int>;
            movieVector->push_back(std::stoi(getUser));
            dataMovieMap.insert(std::pair<int,std::vector<int>*>(std::stoi(getMovie),movieVector));
            dataUserMap.find(std::stoi(getUser))->second->ratedMoviesMap.insert(std::pair<int,float>(std::stoi(getMovie),std::stof(getRating)));

        } else if (dataUserMap.count(std::stoi(getUser)) == 1 && dataMovieMap.count(std::stoi(getMovie)) == 1){

            dataMovieMap.find(std::stoi(getMovie))->second->push_back(std::stoi(getUser));
            dataUserMap.find(std::stoi(getUser))->second->ratedMoviesMap.insert(std::pair<int,float>(std::stoi(getMovie),std::stof(getRating)));

        }


    }
    //dosyayi kapatir
    fin.close();
}

//konsola yazdirmak bi 6-7 dk suruyor
void dataSet::printSaved(){
    std::cout << "~~~~~~~~~~~~~~~~" << '\n';
    std::map <int,userNode*>::const_iterator it;
    for (it = dataUserMap.begin(); it != dataUserMap.end(); ++it)
    {
        std::cout << "USERID: "<< it->first <<'\n';
        std::map <int,float>::const_iterator it2;
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
    std::map <int,userNode*>::const_iterator it;
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
    std::map <int,std::vector<int>*>::const_iterator it;
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
    return dotp / (sqrt(bolum_a) * sqrt(bolum_b)) ;
}
