#pragma once
/*
 * BODY.H
 */
#ifndef BODY_H_
#define BODY_H_

// #include <iostream>
// using std::cout;
// using std::endl;
// using std::cin;

#include <fstream>
using std::ofstream;
using std::ifstream;

#include <string>
using std::string;

#include <vector>
using std::vector;

struct GravitationalBody{
    int ID;
    valtype mass;
    vector<valtype> position;
    vector<valtype> momentum;

    GravitationalBody(int, valtype, vector<valtype>, vector<valtype>);
    void writeCoords(ofstream&, string, string)const;

    vector<valtype> find_angular_momentum();
};

struct GravitationalSystem{
    vector<GravitationalBody> bodies;
    valtype progTime;

    GravitationalSystem(vector<GravitationalBody> , valtype );
    GravitationalSystem(string , valtype );

    void writeBodyCoords(std::ofstream& outstream, std::string coordSep, std::string bodySep, std::string end )const;

    vector<valtype> check_angular_momentum();
};

#endif