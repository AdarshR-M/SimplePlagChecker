#include <fstream>
#include <string>
#include <iostream>
#include "math.h"
#include <cassert>
using namespace std;
#include "reusable.h"


// definition of the function: one variant


class code : public Tools{
    int * No_data_types;   // # of (int, double, char, string, vector)
    int * Conditionals;    // # of (if, else if, else) blocks
    int * Loops;           // # of (for, while, switch)
    int * Objects;         // # of (class, struct, void)
public:
    code() : Tools(){
        No_data_types = new int [5];
        Conditionals = new int [3];
        Loops = new int [3];
        Objects = new int [3];

        initialize(No_data_types, 5);
        initialize(Conditionals, 3);
        initialize(Loops, 3);
        initialize(Objects, 3);

        assert(ensure_initialization(No_data_types, 5) &&
               ensure_initialization(Conditionals, 3) &&
               ensure_initialization(Loops, 3) &&
               ensure_initialization(Objects, 3));
    };

    void initialize(int * A, int N, int s = 0){
        for (int i = 0; i < N; i++){
            A[0] = 0;
        }
    }

    int sum(int * A, int N){
        int sum = 0;
        for (int i = 0; i < N; i++){
            sum += A[i];
        }
        return sum;
    }

    bool ensure_initialization(int * A, int N, int s = 0){
        bool b = 1;
        for (int i = 0; i < N; i++){
            b = (b && (A[i] == s));
        }
        return b;
    }

    void check_data_type(string s){
        No_data_types[0] += find(s, "int");
        No_data_types[1] += find(s, "double")+find(s,"float");
        No_data_types[2] += find(s, "char");
        No_data_types[3] += find(s, "string");
        No_data_types[4] += find(s, "vector");
    }

    void check_conditionals(string s){
        Conditionals[0] += find(s, "if") - find(s, "else if");
        Conditionals[1] += find(s, "else if");
        Conditionals[2] += find(s, "else") - find(s, "else if");
    }

    void check_loops(string s){
        Loops[0] += find(s, "for");
        Loops[1] += find(s, "while");
        Loops[2] += find(s, "switch");
    }

    void check_objects(string s){
        Objects[0] += find(s, "class");
        Objects[1] += find(s, "struct");
        Objects[2] += find(s, "void");
    }

    void check_all(string s){
        check_data_type(s);
        check_conditionals(s);
        check_loops(s);
        check_objects(s);
    }

    int template_score(int * A, int * B, int N, double total){     // out of 20
        int Max, Min;
        double score = 0;
        double w = 0;
        for (int i = 0; i < N; i++){
            Max = max(A[i], B[i]);
            Min = min(A[i], B[i]);
            if (Max > 0){
                score += (1+log(1+Max))*(Min*1.0/Max);
                w += 1+log(1+Max);
            }
            else if (Max == 0 && Min == 0){
                score += 1;
                w += 1;
            }
            assert(w >= 0-0.000001);
        }
        assert(w > 0 && score > 0);
        double s = (score/w) + 0.0001;
        return s*total;
    }

    int Score(code & C){
        int s = 0;
        s += template_score(this->No_data_types, C.No_data_types, 5, 20);
        s += template_score(this->Conditionals, C.Conditionals, 3, 30);
        s += template_score(this->Loops, C.Loops, 3, 30);
        s += template_score(this->Objects, C.Objects, 3, 20);
        return s;
    }

    int no_samples(){
        int samples = 0;
        samples += sum(No_data_types, 5);
        samples += sum(Conditionals, 3);
        samples += sum(Loops, 3);
        samples += sum(Objects, 3);
        return samples;
    }

    ~code(){
        delete No_data_types;
        delete Conditionals;
        delete Loops;
        delete Objects;
    }
};

int checksimilarity (string n1, string n2) {
    ifstream f1, f2; 
    code C1, C2;
    string s;

    f1.open(n1);
    f2.open(n2);
    while(true){
        f1 >> s;
        if (f1.eof()) break;
        C1.check_all(s);
    }
    while(true){
        f2 >> s;
        if (f2.eof()) break;
        C2.check_all(s);
    }

    int score = C1.Score(C2);

    f1.close();
    f2.close();
    int max_samples = max(C1.no_samples(), C2.no_samples());
    int sample_diff = abs(C1.no_samples() - C2.no_samples());
    assert(max_samples > 0);
    score = score*(1-sample_diff*1.0/max_samples);
    
    return score;
}

