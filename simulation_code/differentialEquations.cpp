#include "../headers/simulator.h"

 //abstract class

vector<vector<valtype>> Derivative:: MomentumDerivative(vector <GravitationalBody> sys){
    vector<vector<valtype>> MomentumDerivatives ;
    for (int i =0;i<sys.size();i++){
        valtype pxd,pyd,pzd;
        for (int j=0;j<sys.size();j++){
            if (i!=j){
                double xr = sys[j].position[0] - sys[i].position[0];
                double yr = sys[j].position[1] - sys[i].position[1];
                double zr = sys[j].position[2] - sys[i].position[2];
                pxd += (G*sys[i].mass*sys[j].mass*xr)/pow(xr*xr+yr*yr+zr*zr,1.5);
                pyd += (G*sys[i].mass*sys[j].mass*yr)/pow(xr*xr+yr*yr+zr*zr,1.5);
                pzd += (G*sys[i].mass*sys[j].mass*zr)/pow(xr*xr+yr*yr+zr*zr,1.5);
            }
            MomentumDerivatives.push_back({pxd,pyd,pzd});
        }
    }
    return MomentumDerivatives;
}

vector<vector<valtype>> Derivative:: PositionDerivative(vector <GravitationalBody> sys){
    vector<vector<valtype>> PositionDerivatives ;
    for (int i =0;i<sys.size();i++){
        valtype xd,yd,zd;
        xd = sys[i].momentum[0]/sys[i].mass;
        yd = sys[i].momentum[1]/sys[i].mass;
        zd = sys[i].momentum[2]/sys[i].mass;
        PositionDerivatives.push_back({xd,yd,zd});
        }
    return PositionDerivatives;
}


GravitationalIntegrator:: GravitationalIntegrator(std::vector<GravitationalBody> bodies, valtype step, valtype progTime):  GravitationalSystem(bodies, progTime){}

GravitationalIntegrator:: GravitationalIntegrator(string infile, valtype step, valtype progTime):  GravitationalSystem(infile, progTime){}


GravitationalSystem GravitationalIntegrator:: Step1(){
    vector<GravitationalBody> Step1bodies = bodies;
    vector<vector<valtype>> MomentumDerivativesStep1 = PositionDerivative(Step1bodies);
    vector<vector<valtype>> PositionDerivativesStep1 = PositionDerivative(Step1bodies);
    GravitationalSystem Step1Sys(Step1bodies,progTime);
    for(auto& body : Step1bodies){
        for(short int i=0;i<body.position.size();i++){
            body.position[i] += step*PositionDerivativesStep1[body.ID][i]/2;
            body.momentum[i] += step*MomentumDerivativesStep1[body.ID][i]/2;
        }
    }
    return Step1Sys;
}

GravitationalSystem GravitationalIntegrator:: Step2(GravitationalSystem Step1Sys){
    vector<GravitationalBody> Step2bodies = bodies;
    GravitationalSystem Step2Sys(Step2bodies,progTime);
    vector<vector<valtype>> MomentumDerivativesStep2 = MomentumDerivative(Step1Sys.bodies);
    vector<vector<valtype>> PositionDerivativesStep2 = PositionDerivative(Step1Sys.bodies);
    for(auto& body : Step2bodies){
        for(short int i=0;i<body.position.size();i++){
            body.position[i] += step*PositionDerivativesStep2[body.ID][i]/2;
            body.momentum[i] += step*MomentumDerivativesStep2[body.ID][i]/2;
        }
    }
    return Step2Sys;
}

GravitationalSystem GravitationalIntegrator:: Step3(GravitationalSystem Step2Sys){
    vector<GravitationalBody> Step3bodies = bodies;
    GravitationalSystem Step3Sys(Step3bodies,progTime);
    vector<vector<valtype>> MomentumDerivativesStep3 = MomentumDerivative(Step2Sys.bodies);
    vector<vector<valtype>> PositionDerivativesStep3 = PositionDerivative(Step2Sys.bodies);
    for(auto& body : Step3bodies){
        for(short int i=0;i<body.position.size();i++){
            body.position[i] += step*PositionDerivativesStep3[body.ID][i];
            body.momentum[i] += step*MomentumDerivativesStep3[body.ID][i];
        }
    }
    return Step3Sys;
}

GravitationalSystem GravitationalIntegrator:: Step4(GravitationalSystem Step3Sys){
    vector<GravitationalBody> Step4bodies = bodies;
    GravitationalSystem Step4Sys(Step4bodies,progTime);
    vector<vector<valtype>> MomentumDerivativesStep4 = MomentumDerivative(Step3Sys.bodies);
    vector<vector<valtype>> PositionDerivativesStep4 = PositionDerivative(Step3Sys.bodies);
    for(auto& body : Step4bodies){
        for(short int i=0;i<body.position.size();i++){
            body.position[i] += step*PositionDerivativesStep4[body.ID][i];
            body.momentum[i] += step*MomentumDerivativesStep4[body.ID][i];
        }
    }
    return Step4Sys;
}

void GravitationalIntegrator:: nextStepAll(){
    GravitationalSystem Step1Sys = Step1();
    GravitationalSystem Step2Sys = Step2(Step1Sys);
    GravitationalSystem Step3Sys = Step3(Step2Sys);
    GravitationalSystem Step4Sys = Step2(Step3Sys);
    for(auto& body : this->bodies){
        for(short int i=0;i<body.position.size();i++){
            body.position[i] += (2*Step1Sys.bodies[body.ID].position[i]+4*Step2Sys.bodies[body.ID].position[i]+2*Step3Sys.bodies[body.ID].position[i]+Step4Sys.bodies[body.ID].position[i]-9*body.position[i])/6;
            body.momentum[i] += (2*Step1Sys.bodies[body.ID].momentum[i]+4*Step2Sys.bodies[body.ID].momentum[i]+2*Step3Sys.bodies[body.ID].momentum[i]+Step4Sys.bodies[body.ID].momentum[i]-9*body.momentum[i])/6;
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