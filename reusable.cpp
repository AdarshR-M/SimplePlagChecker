#include "reusable.h"

int Tools::find(string str, string sub) {  
    int pos = -1;
    int n = 0;
    assert(sub.length() > 0);
    for (int i = 0, j = 0; i < str.length(); i++){
        if (str[i] != sub[j]){
            pos = -1;
            j = 0;
        }
        else if (str[i] == sub[j] && j == 0){
            pos = i;
            j++;
        }
        else if (str[i] == sub[j]){
            j++;
        }
        if (j == sub.length()){
            n += 1;
            j = 0;
        }
    }
    return n;
}

