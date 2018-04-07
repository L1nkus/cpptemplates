#include <bits/stdc++.h>

#define inc1(it1) if(!*++it1) goto br;
#define inc2(it2) if(!*++it2) goto br;

int main(int argc, char **argv){
    FILE *f1 = fopen(argv[1], "r");
    FILE *f2 = fopen(argv[2], "r");
    static char buf1[1000000], buf2[1000000];
    fread(buf1, 1, 1000000,f1);
    fread(buf2, 1, 1000000,f2);
    fclose(f1);
    fclose(f2);
    char *it1 = buf1, *it2 = buf2;
    if(!*it1 || !*it2)
        return 0&puts("SOME IS EMPTY");
    for(;;){
        while(*it1 < 33) inc1(it1);
        while(*it2 < 33) inc2(it2);
        if(*it1 >= 97 && *it1 <= 122)
            *it1 &= ~32;
        if(*it2 >= 97 && *it2 <= 122)
            *it2 &= ~32;
        if(*it1 != *it2){
            char c1 = *it1;
            char c2 = *it2;
            return 0&puts("DIFFFF");
        }
        ++it1;
        ++it2;
        if(!*it1 || !*it2) break;
    }
    br:
    if(!*it1 && !*it2)
        return 0;
    if(!*it1){
        while(*it2){
            if(*it2++ >= 33)
                return 0&puts("DIFFF");
        }
    }
    else{
        while(*it1){
            if(*it1++ >= 33)
                return 0&puts("DIFFF");
        }
    }
}

