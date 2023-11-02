#include "../headers/simulator.h"

GravitationalBody:: GravitationalBody(int ID, valtype mass, vector<valtype> position, vector<valtype> momentum): ID(ID), mass(mass), position(position), momentum(momentum){}

void GravitationalBody:: writeCoords(ofstream& outstream, const string& sep, const string& end)const {
    for(auto& coord: position){
        outstream<<coord<<sep;
    }
    outstream<<end;
}

GravitationalSystem::  GravitationalSystem(vector<GravitationalBody>&& bodies, valtype progTime): bodies(bodies), progTime(progTime){}

GravitationalSystem::  GravitationalSystem(string&& infile, valtype progTime): progTime(progTime){
    //expecting inputfile with format ID M X Y  Z VX VY VZ \N
    bodies = vector<GravitationalBody>();
    ifstream instream(infile);
    while(!instream.eof()){
        int ID;
        valtype m,x,y,z,vx,vy,vz;
        //std::cout<<"hello"<<std::endl;
        instream>>ID>>m>>x>>y>>z>>vx>>vy>>vz;
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

