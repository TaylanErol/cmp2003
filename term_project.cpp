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
        if(std::isnan(i.second)){
            std::cout << "Warning nan detected at ID: " << i.first << "!\n";
            fout << i.first << "," << 3.0 << "\n";
        }
        else {
            fout << i.first << "," << i.second << "\n";
        }
    }
}

void dataSet::import_test(){
    std::ifstream fin;
    std::string firstCellPurge;
    std::string getID;
    std::string getUser;
    std::string getMovie;

    this->setFileName();

    fin.open(fileName);
    if(!fin.is_open()) std::cout << "ERROR: File couldn't be opened!" << '\n';
    getline(fin,firstCellPurge,'\n');

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
                        //For debugging
                        /*std::cout << "Candidate ID: " << dataUserMap.find(dataMovieMap.find(fileMovie)->second->at(i))->first
                                  << " CandidateMovie: " << dataUserMap.find(dataMovieMap.find(fileMovie)->second->at(i))->second->ratedMoviesMap.find(it2->first)->first
                                  << " Candidate Rating: " << dataUserMap.find(dataMovieMap.find(fileMovie)->second->at(i))->second->ratedMoviesMap.find(it2->first)->second << "\n";
                        std::cout << "File User ID: " << dataUserMap.find(fileUser)->first
                                  << " File User Movie : " << it2->first
                                  << " File User Rating: " << it2->second << "\n";*/
                        file2CandidateRatingAVGDIFF.emplace_back(it2->second - avgRating,candidateNodePtr->ratedMoviesMap.find(it2->first)->second - candidateNodePtr->avgRating);
                }
            }

            if(file2CandidateRatingAVGDIFF.size() > 3) {
                double cossim = cosine_similarity(file2CandidateRatingAVGDIFF);
                double vscs = cossim * file2CandidateRatingAVGDIFF.size(); //* ((double) fileMovieRatings.size() / (double) dataUserMap.find(dataMovieMap.find(fileMovie)->second->at(i))->second->ratedMoviesMap.size());
                int candidateID = dataUserMap.find(dataMovieMap.find(fileMovie)->second->at(i))->first;
                /*std::cout << "File User ID: " << dataUserMap.find(fileUser)->first << ", "
                          << "Candidate ID: " << candidateID << ", Similarity: " << cossim
                          << " Vector Size: " << file2CandidateRatingAVGDIFF.size() << ", vs*cs: " << vscs << "\n";*/
                vscsAndCandidateID.emplace_back(vscs,candidateID);
            }
        }

        double denominator = 0.0;
        double numerator = 0.0;

        for (auto & i : vscsAndCandidateID) {
            if (!std::isnan(i.first)) {
                numerator += i.first * (dataUserMap.find(i.second)->second->ratedMoviesMap.find(fileMovie)->second - dataUserMap.find(i.second)->second->avgRating);
                denominator += fabs(i.first);
                //For debugging
                //std::cout << vscsAndCandidateID[i].first << " "<< vscsAndCandidateID[i].second << " r: " << dataUserMap.find(vscsAndCandidateID[i].second)->second->ratedMoviesMap.find(fileMovie)->second << std::endl;
            }
        }

        double rating = dataUserMap.find(fileUser)->second->avgRating + (numerator/denominator);
        exportData.emplace_back(fileID,rating);

        std::cout << "Recommended Rating: " << rating << " fileUserAvgRaating: " << dataUserMap.find(fileUser)->second->avgRating << " cossimEffect: " << numerator/denominator <<"\n";
        std::cout << "////////" << getID << " Mov: " << getMovie <<"---------------Finish File User ID: " << dataUserMap.find(fileUser)->first << "\n";
    }
    fin.close();
}


void dataSet::import_and_save(){
    std::ifstream fin;
    std::string firstCellPurge;
    std::string getUser;
    std::string getMovie;
    std::string getRating;
    this->setFileName();

    fin.open(fileName);

    if(!fin.is_open()) std::cout << "ERROR: File couldn't be opened!" << '\n';

    getline(fin,firstCellPurge,'\n');

    while(fin.peek()!=EOF) {

        getline(fin, getUser, ',');
        int fileUser = std::stoi(getUser);
        getline(fin, getMovie, ',');
        int fileMovie = std::stoi(getMovie);
        getline(fin, getRating, '\n');
        float fileRating = std::stof(getRating);

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

void swap(int* ap, int* bp)
{
    int temp = *ap;
    *ap = *bp;
    *bp = temp;
}

void selectionSort(int x[], int y[], int n)
{
    int min;

    for (int i = 0; i < n - 1; i++)
    {
        min = i;
        for (int j = i + 1; j < n; j++)
            if (x[j] < x[min])
                min = j;

        if (min != i) {
            swap(&x[min], &x[i]);
            swap(&y[min], &y[i]);
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
        //For debugging
        //std::cout << "dotp: " <<dotp << " bolum_a: " << bolum_a<< " bolum_b: " << bolum_b << "\n";
    }
    return dotp / (sqrt(bolum_a) * sqrt(bolum_b)) ;
}

double euclidian_distance(const std::vector<std::pair<float, float>> &rating) {
    double toplam = 0.0;
    for (auto &i: rating) {
        toplam += (i.first - i.second) * (i.first - i.second);
    }
    return sqrt(toplam);
}
