#include "../headers/simulator.h"

GravitationalBody:: GravitationalBody(int ID, valtype mass, vector<valtype> position, vector<valtype> momentum): ID(ID), mass(mass), position(position), momentum(momentum){}

void GravitationalBody:: writeCoords(ofstream& outstream, string sep, string end)const {
    for(auto& coord: position){
        outstream<<coord<<sep;
    }
    outstream<<end;
}

vector<valtype> GravitationalBody::find_angular_momentum() { //Unnecessary, can directly use cross_product, but added anyway in spirit of other design decisions taken.
    return cross_product(position, momentum);
}

GravitationalSystem::  GravitationalSystem(vector<GravitationalBody> bodies, valtype progTime): bodies(bodies), progTime(progTime){}

GravitationalSystem::  GravitationalSystem(string infile, valtype progTime): progTime(progTime){
    //expecting inputfile with format ID M X Y  Z VX VY VZ \N
    bodies = vector<GravitationalBody>();
    ifstream instream(infile);
    int ID;
    valtype m, x, y, z, vx, vy, vz;
    while(true){
        
        //std::cout<<"hello"<<std::endl;

        instream>>ID>>m>>x>>y>>z>>vx>>vy>>vz;
        if (instream.eof()) {
            break;
        }
        std::cout<<" "<<ID<<" "<<m<<" "<<x<<" "<<y<<" "<<z<<" "<<vx<<" "<<vy<<" "<<vz<<std::endl;
        bodies.push_back(GravitationalBody(ID,m,{x,y,z},{vx*m,vy*m,vz*m}));
    }
}



void GravitationalSystem:: writeBodyCoords(ofstream& outstream, string coordSep, string bodySep, string end )const {
    for(auto& body:bodies){
        body.writeCoords(outstream, coordSep, bodySep);
    }
    outstream<<end;
}


vector<valtype> GravitationalSystem:: check_angular_momentum() {
    vector<valtype>total_angular_momentum = { 0,0,0 };
    vector<valtype>temp;
    for (auto& body : bodies) { //Take total angular momentum. Loops through all bodies, so lots of overhead if n_bodies large. Maybe directly add to other force calculation/integration loops?
        temp = body.find_angular_momentum();
        total_angular_momentum[0] = total_angular_momentum[0] + temp[0];
        total_angular_momentum[1] = total_angular_momentum[1] + temp[1];
        total_angular_momentum[2] = total_angular_momentum[2] + temp[2];
    }
    return total_angular_momentum;
}