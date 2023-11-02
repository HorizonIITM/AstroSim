#include "../headers/simulator.h"

 //abstract class
Derivative:: Derivative(GravitationalSystem& s, short int& coordType, GravitationalBody& current_body): 
        sys(s), coordType(coordType), current_body(current_body){}

PositionDerivative:: PositionDerivative(GravitationalSystem& sys, short int& coordType,GravitationalBody& current_body):
    Derivative(sys, coordType, current_body){};

valtype PositionDerivative:: operator() (valtype t, valtype x) const{
    return (this->current_body).momentum[this->coordType] / (this->current_body).mass;
}



MomentumDerivative::MomentumDerivative(GravitationalSystem& sys, short int& coordType,GravitationalBody& current_body):
    Derivative(sys, coordType, current_body){};


valtype MomentumDerivative:: operator() (valtype t, valtype px) const{
    valtype der = 0;
    
    for(auto& body : (this->sys).bodies){
        if(body.ID == (this->current_body).ID) continue;
        valtype distsq = distSquare(body.position, (this->current_body).position);
        der+= (-(G * (this->current_body).mass * body.mass * ((this->current_body).position[this->coordType]-body.position[this->coordType])) *(pow (Q_rsqrt(distsq),3.0)));
    }
    return der;
}


GravitationalIntegrator:: GravitationalIntegrator(std::vector<GravitationalBody>&& bodies, valtype step, valtype progTime, std::string integrator):  GravitationalSystem(std::move(bodies), progTime), Integrator(step,integrator){}

GravitationalIntegrator:: GravitationalIntegrator(string&& infile, valtype step, valtype progTime, std::string integrator):  GravitationalSystem(std::move(infile), progTime), Integrator(step,integrator){}


void GravitationalIntegrator:: nextStepAll(){
    for(auto& body : this->bodies){
        for(short int i=0;i<body.position.size();i++){
            body.position[i] = this->nextStep(body.position[i], this->progTime, PositionDerivative(*this, i, body));
            body.momentum[i] = this->nextStep(body.momentum[i], this->progTime, MomentumDerivative(*this, i, body));
        }
    }                        
    this->progTime+=this->step;
}


void GravitationalIntegrator:: solve(const valtype totalProgTime, const string filename){
    bool writeFlag = filename=="" ? false : true;
    ofstream my_file(filename); 
    if(writeFlag) {
        //my_file<<"x1,y1,z1,,,x2,y2,z2,,,x3,y3,z3,,,"<<endl; //scam
        for(int i=1;i<=(this->bodies).size();i++){
            my_file<<"x"<<i<<",y"<<i<<",z"<<i<<",";
        }
        my_file<<"\n";
    }
    while(this->progTime<totalProgTime){
        if(writeFlag) this->writeBodyCoords(my_file, ",", "", "\n");
        nextStepAll();
    }
    if(writeFlag) this->writeBodyCoords(my_file, ",", "", "\n");
}
