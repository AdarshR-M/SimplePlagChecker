#include <fstream>
#include <string>
#include <iostream>
#include "math.h"
#include <cassert>
#include <vector>
using namespace std;
#include "reusable.h"

const char FILENAME[7] = "Output";
const int LEN = 1000;

class func : public Tools{
    vector <string> class_names;
    vector < vector <int> > function_sign;      // {int, double, float, char, string, bool, other}
    int unhandleable_events;
public:
    func() : Tools() {
        unhandleable_events = 0;
    } 

    void find_class(string s){
        if (find(s, "class ") > 0){
            string name;
            ofstream o;
            ifstream f;
            o.open(FILENAME);
            o << s;
            o.close();
            f.open(FILENAME);
            bool b = 0;
            while (true){
                f >> name;
                if (b){
                    class_names.push_back(name);
                    break;
                }
                if (name == "class"){
                    b = 1;
                }
                if (f.eof()){
                    break;
                }
            }
            f.close();
        }
    }

    void find_function(string s){
        int no = find(s, ")");
        if (no == 0){ 
            unhandleable_events += 1;
            return;
        }
        else if(no > 1){
            unhandleable_events += 1;
            return;
        }
        ofstream o;
        o.open(FILENAME);
        o << s;
        o.close();

        ifstream f;
        char ST[LEN];
        string S;
        f.open(FILENAME);
        f.getline(ST , LEN, ')');
        S = ST;
        function_process(S);
    }

    void function_process(string s){
        vector <int> V(7, 0);
        V[0] += find(s, "int ") + find(s, "int*") + find(s,"int&");
        V[1] += find(s, "double ") + find(s, "double*") +find(s, "double&");
        V[2] += find(s, "float ") + find(s, "float*") +find(s, "float&");
        V[3] += find(s, "char ") + find(s, "char*") +find(s, "char&");
        V[4] += find(s, "string ") + find(s, "string*") +find(s, "string&");
        V[5] += find(s, "bool ") + find(s, "bool*") +find(s, "bool&");
        for (int i = 0; i < class_names.size(); i++){
            string name = class_names[i];
            V[6] += find(s, name+" ") + find(s, name+"*") + find(s, name+"&");
        }
        function_sign.push_back(V);
    }

    void print_classes(){
        for (int i = 0; i < class_names.size(); i++){
            cout << class_names[i] << " ";
        }
    }

    double function_matches(func & F){
        vector < vector <int> > V1 = function_sign;
        vector < vector <int> > V2 = F.function_sign; 
        int Max = max(V1.size(), V2.size());
        int matches = 0;
        for(int i = 0; i < V1.size(); i++){
            for (int j = 0; j < V2.size(); j++){
                if (V1[i] == V2[j]){
                    V2.erase(V2.begin()+j);
                    matches += 1;
                    break;
                }
            }
        }
        if (Max == 0) return 0;
        return matches/Max;
    }

    int Score(func & F){
        int SCR = 0;
        SCR += 70*function_matches(F) + 0.1;
        int Max = max(class_names.size(), F.class_names.size());
        int Min = min(class_names.size(), F.class_names.size());
        if (Max == 0) {
            SCR += 10;
        }
        else {
            SCR += 10*Min*1.0/Max + 0.1;
        }

        Max = max(function_sign.size(), F.function_sign.size());
        Min = min(function_sign.size(), F.function_sign.size());
        if (Max == 0){ 
            SCR += 10;
        }
        else {
            SCR += 20*Min*1.0/Max + 0.1;
        }
        return SCR;
    }

    void compare(string n1){
        ifstream f1;
        f1.open(n1);
        char C[LEN];
        string S;
        while (true){
            f1.getline(C , LEN, '(');
            S = C;
            if (f1.rdstate() == f1.failbit || f1.eof()){
                break;
            }
            find_function(S);
        }
        f1.getline(C, LEN, ')');
        S = C; 
        S += ")";
        find_function(S);
        f1.close();
    }
};

int checksimilarity (string n1, string n2) {
    func F1, F2;
    ofstream(o);
    ifstream f1, f2; 
    f1.open(n1);
    char C[LEN];

    string S;
    while (true){
        f1.getline(C , LEN, '{');
        S = C;
        F1.find_class(S);
        if (f1.rdstate() == f1.failbit || f1.eof()){
            break;
        }
    }
    f1.close();

    f2.open(n2);
    while (true){
        f2.getline(C , LEN, '{');
        S = C;
        F2.find_class(S);
        if (f2.rdstate() == f2.failbit || f2.eof()){
            break;
        }
    }
    f2.close();
    F1.compare(n1);
    F2.compare(n2);
    int score = F1.Score(F2);
    o.open(FILENAME);
    remove(FILENAME);

return score;
}