#include "../headers/simulator.h"


long double Q_rsqrt(long double number){
    // union {
    // float    f;
    // uint32_t i;
    // } conv = { .f = number };
    // conv.i  = 0x5f3759df - (conv.i >> 1);
    // conv.f *= 1.5F - (number * 0.5F * conv.f * conv.f);
    // return conv.f;
    return 1/sqrt(number);
}

double Q_rsqrt(double number){
    // union {
    // float    f;
    // uint32_t i;
    // } conv = { .f = number };
    // conv.i  = 0x5f3759df - (conv.i >> 1);
    // conv.f *= 1.5F - (number * 0.5F * conv.f * conv.f);
    // return conv.f;
    return 1/sqrt(number);
}

// float Q_rsqrt(float number){
//     // union {
//     // float    f;
//     // uint32_t i;
//     // } conv = { .f = number };
//     // conv.i  = 0x5f3759df - (conv.i >> 1);
//     // conv.f *= 1.5F - (number * 0.5F * conv.f * conv.f);
//     // return conv.f;
//     return 1/sqrt(number);
// }

valtype distSquare(vector<valtype> p1, vector<valtype> p2){
    valtype sum = 0;
    for(short int coord = 0;coord<p1.size() ;coord++){
        sum += pow(p1[coord]-p2[coord],2.0);
    }
    return sum;
}

vector<valtype> cross_product(vector<valtype>v1, vector<valtype>v2) {
    vector<valtype> returned_result(3);
    returned_result[0] = v1[1] * v2[2] - v1[2] * v2[1];
    returned_result[1] = v1[2] * v2[0] - v1[0] * v2[2];
    returned_result[2] = v1[0] * v2[1] - v1[1] * v2[0];
    return returned_result;
}