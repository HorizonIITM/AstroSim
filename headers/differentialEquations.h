#pragma once
/*
 * DIFFERENTIALEQUATIONS.H
 */
#ifndef DIFFERENTIALEQUATIONS_H_
#define DIFFERENTIALEQUATIONS_H_

#include "../headers/body.h"

 //abstract class
class Derivative{
    public:
        vector<vector<valtype>> PositionDerivative(vector <GravitationalBody>);
        vector<vector<valtype>> MomentumDerivative(vector <GravitationalBody>);
};

class GravitationalIntegrator : public GravitationalSystem, public Derivative{
    public:
        valtype step;
        GravitationalIntegrator(vector<GravitationalBody>, valtype, valtype = 0);
        GravitationalIntegrator(string infile, valtype, valtype = 0);
    
    private:
        vector<GravitationalBody>  Step1();
        vector<GravitationalBody>  Step2(vector<GravitationalBody> );
        vector<GravitationalBody>  Step3(vector<GravitationalBody> );
        vector<GravitationalBody>  Step4(vector<GravitationalBody> );
        void nextStepAll();
    public: 
        void solve(const valtype totalProgTime, const string filename = "");
};
#endif
