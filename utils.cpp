#include "../headers/simulator.h"


long double Q_rsqrt(long double number){
    return 1/sqrt(number);
}

double Q_rsqrt(double number){
    return 1/sqrt(number);
}

valtype distSquare(vector<valtype> const &p1, vector<valtype> const &p2){
    valtype sum = 0;
    for(short int coord = 0;coord<p1.size() ;coord++){
        sum += pow(p1[coord]-p2[coord],2.0);
    }
    return sum;
}
