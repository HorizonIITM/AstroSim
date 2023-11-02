#pragma once
/*
 * DIFFERENTIALEQUATIONS.H
 */
#ifndef DIFFERENTIALEQUATIONS_H_
#define DIFFERENTIALEQUATIONS_H_

#include "../headers/body.h"

 //abstract class
class Derivative{
    protected:
        GravitationalSystem& sys;
        short int& coordType; //x or y or z
        GravitationalBody& current_body;
    public:
        Derivative(GravitationalSystem&, short int&, GravitationalBody&);
        valtype operator() (valtype, valtype) const;
};


class PositionDerivative : public Derivative{
    public:
        PositionDerivative(GravitationalSystem&, short int&,GravitationalBody&);
        valtype operator() (valtype, valtype) const;
};


class MomentumDerivative : public Derivative{
    public:
        MomentumDerivative(GravitationalSystem&, short int&,GravitationalBody&);

        valtype operator() (valtype, valtype) const;
};



class GravitationalIntegrator : private Integrator, public GravitationalSystem{
    public:
        string integrator;
        GravitationalIntegrator(vector<GravitationalBody>&&, valtype, valtype = 0, string = "euler");
        GravitationalIntegrator(string&& infile, valtype, valtype = 0, string = "euler");
    
    private:
        void nextStepAll();
    public: 
        void solve(const valtype totalProgTime, const string filename = "");
};
#endif
