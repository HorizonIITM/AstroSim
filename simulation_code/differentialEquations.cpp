#include "../headers/simulator.h"

 //abstract class

vector<vector<valtype>> Derivative:: MomentumDerivative(vector <GravitationalBody> sys){
    vector<vector<valtype>> MomentumDerivatives ;
    for (int i =0;i<sys.size();i++){
        valtype pxd = 0;
        valtype pyd = 0;
        valtype pzd = 0;
        for (int j=0;j<sys.size();j++){
            if (i==j) continue;
            double xr = sys[j].position[0] - sys[i].position[0];
            double yr = sys[j].position[1] - sys[i].position[1];
            double zr = sys[j].position[2] - sys[i].position[2];
            pxd += (G*sys[i].mass*sys[j].mass*xr)/pow(xr*xr+yr*yr+zr*zr,1.5);
            pyd += (G*sys[i].mass*sys[j].mass*yr)/pow(xr*xr+yr*yr+zr*zr,1.5);
            pzd += (G*sys[i].mass*sys[j].mass*zr)/pow(xr*xr+yr*yr+zr*zr,1.5);
        }
        MomentumDerivatives.push_back({pxd,pyd,pzd});
    }
    return MomentumDerivatives;
}

vector<vector<valtype>> Derivative:: PositionDerivative(vector <GravitationalBody> sys){
    vector<vector<valtype>> PositionDerivatives ;
    for (int i =0;i<sys.size();i++){
        valtype xd = sys[i].momentum[0]/sys[i].mass;
        valtype yd = sys[i].momentum[1]/sys[i].mass;
        valtype zd = sys[i].momentum[2]/sys[i].mass;
        PositionDerivatives.push_back({xd,yd,zd});
        }
    return PositionDerivatives;
}


GravitationalIntegrator:: GravitationalIntegrator(std::vector<GravitationalBody> bodies, valtype step, valtype progTime):  GravitationalSystem(bodies, progTime), step(step){}

GravitationalIntegrator:: GravitationalIntegrator(string infile, valtype step, valtype progTime):  GravitationalSystem(infile, progTime), step(step){}


vector<GravitationalBody> GravitationalIntegrator:: Step1(){
    vector<GravitationalBody> Step1bodies = this->bodies;
    vector<vector<valtype>> MomentumDerivativesStep1 = MomentumDerivative(Step1bodies);
    vector<vector<valtype>> PositionDerivativesStep1 = PositionDerivative(Step1bodies);
    for(auto& body : Step1bodies){
        for(short int i=0;i<body.position.size();i++){
            body.position[i] += step*PositionDerivativesStep1[body.ID][i]/2;
            body.momentum[i] += step*MomentumDerivativesStep1[body.ID][i]/2;
        }
    }
    return Step1bodies;
}

vector<GravitationalBody> GravitationalIntegrator::Step2(vector<GravitationalBody> Step1bodies){
    vector<GravitationalBody> Step2bodies = this->bodies;
    vector<vector<valtype>> MomentumDerivativesStep2 = MomentumDerivative(Step1bodies);
    vector<vector<valtype>> PositionDerivativesStep2 = PositionDerivative(Step1bodies);
    for(auto& body : Step2bodies){
        for(short int i=0;i<body.position.size();i++){
            body.position[i] += step*PositionDerivativesStep2[body.ID][i]/2;
            body.momentum[i] += step*MomentumDerivativesStep2[body.ID][i]/2;
        }
    }
    return Step2bodies;
}

vector<GravitationalBody> GravitationalIntegrator:: Step3(vector<GravitationalBody>  Step2bodies){
    vector<GravitationalBody> Step3bodies = this->bodies;
    vector<vector<valtype>> MomentumDerivativesStep3 = MomentumDerivative(Step2bodies);
    vector<vector<valtype>> PositionDerivativesStep3 = PositionDerivative(Step2bodies);
    for(auto& body : Step3bodies){
        for(short int i=0;i<body.position.size();i++){
            body.position[i] += step*PositionDerivativesStep3[body.ID][i];
            body.momentum[i] += step*MomentumDerivativesStep3[body.ID][i];
        }
    }
    return Step3bodies;
}

vector<GravitationalBody> GravitationalIntegrator:: Step4(vector<GravitationalBody> Step3bodies){
    vector<GravitationalBody> Step4bodies = this->bodies;
    vector<vector<valtype>> MomentumDerivativesStep4 = MomentumDerivative(Step3bodies);
    vector<vector<valtype>> PositionDerivativesStep4 = PositionDerivative(Step3bodies);
    for(auto& body : Step4bodies){
        for(short int i=0;i<body.position.size();i++){
            body.position[i] += step*PositionDerivativesStep4[body.ID][i];
            body.momentum[i] += step*MomentumDerivativesStep4[body.ID][i];
        }
    }
    return Step4bodies;
}

void GravitationalIntegrator:: nextStepAll(){
    vector<GravitationalBody> Step1bodies = Step1();
    vector<GravitationalBody> Step2bodies = Step2(Step1bodies);
    vector<GravitationalBody> Step3bodies = Step3(Step2bodies);
    vector<GravitationalBody> Step4bodies = Step2(Step3bodies);
    for(auto& body : this->bodies){
        for(short int i=0;i<body.position.size();i++){
            body.position[i] += (2*Step1bodies[body.ID].position[i]+4*Step2bodies[body.ID].position[i]+2*Step3bodies[body.ID].position[i]+Step4bodies[body.ID].position[i]-9*body.position[i])/6;
            body.momentum[i] += (2*Step1bodies[body.ID].momentum[i]+4*Step2bodies[body.ID].momentum[i]+2*Step3bodies[body.ID].momentum[i]+Step4bodies[body.ID].momentum[i]-9*body.momentum[i])/6;
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