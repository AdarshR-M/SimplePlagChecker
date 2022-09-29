#include <iostream>
#include <string>
using namespace std;
#include "similarity.h"


int main(int argc, char* argv[]){
    int score;
    score = checksimilarity(argv[1], argv[2]);
    cout << score << endl;
return 0;
}