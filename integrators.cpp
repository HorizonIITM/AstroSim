#include "../headers/simulator.h"


Integrator::Integrator(valtype step, string integrator):step(step), integrator(integrator){}


template <class func>
valtype Integrator:: nextStep(valtype x, valtype t, valtype v, func acc, func accderivative){
    return nextstepHermite(x, t, v, acc, accderivative)
}

template <class func>
valtype Integrator:: nextStep(valtype x, valtype t, func derivative){
    if(integrator == "euler"){
        return nextStepEuler(x,t,derivative);
    }else if(integrator == "rk4 old"){
        return nextStepRK4(x,t,derivative);
    }cout<<"NO SUCH INTEGRATOR. USING EULER"<<endl;
    return nextStepEuler(x,t,derivative);
}


template <class func>
valtype Integrator::  nextStepEuler(valtype x, valtype t, func f){
    x+= f(t,x)*step;
    return x;
}


template <class func>
valtype Integrator:: nextStepRK4(valtype x, valtype t, func f){
    valtype k1 = step * f(t,x);  //other variables are constant!!
    valtype k2 = step * f(t + step/2.0 , x + step*k1/2.0);
    valtype k3 = step * f(t + step/2.0 , x + step*k2/2.0);
    valtype k4 = step * f(t + step , x + step*k3);
    x += (step/6.0)* (k1+ 2*k2 + 2*k3 + k4);
    t +=step;
    return x;
}

template <class func>
valtype Integrator:: nextStepHermite(valtype x, valtype t, valtype v, func a, func j){
     float s2 = step * step;
     float s3 = step * step * step;
     v += a(x, t) * step + 0.5 * j(x, t) * s2;
     x += v * step + 0.5 * a(x, t) * s2 + j(x, t) * s3 / 6;
     t +=step;
     return x;
 }