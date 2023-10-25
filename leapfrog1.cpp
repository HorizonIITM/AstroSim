#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
const float G = 1;
const float step = 0.01;

class Celestial_Body
{
    public:
        float M, x, y, z, vx, vy, vz, ax, ay, az, t;
        std::vector<float> X, Y, Z;
};

float Q_rsqrt(float number)
{
    union {
    float    f;
    uint32_t i;
    } conv = { .f = number };
    conv.i  = 0x5f3759df - (conv.i >> 1);
    conv.f *= 1.5F - (number * 0.5F * conv.f * conv.f);
    return conv.f;
}

class integrator
{
    public:
        void leapfrog_step1(Celestial_Body B, float dt)
        {
            B.vx += B.ax * dt * 0.5;
            B.vy += B.ay * dt * 0.5;
            B.vz += B.az * dt * 0.5;
            B.x += B.vx * dt;
            B.y += B.vy * dt;
            B.z += B.vz * dt;
        }
        void leapfrog_step2(Celestial_Body B, float dt)
        {
            B.vx += B.ax * dt * 0.5;
            B.vy += B.ay * dt * 0.5;
            B.vz += B.az * dt * 0.5;
        }
};

class force_calc
{
    private:
        int n;
        float X, Y, Z;
    public:
        force_calc(int N): n(N){}
        float fx(Celestial_Body b1, Celestial_Body b2)
        {
            float X = b2.x - b1.x;
            float Y = b2.y - b1.y;
            float Z = b2.z - b1.z;
            return ((G * b2.M) * X) / (pow(Q_rsqrt(X * X + Y * Y + Z * Z), 3));
        }
        float fy(Celestial_Body b1, Celestial_Body b2)
        {
            float X = b2.x - b1.x;
            float Y = b2.y - b1.y;
            float Z = b2.z - b1.z;
            return ((G * b2.M) * Y) / (pow(Q_rsqrt(X * X + Y * Y + Z * Z), 3));
        }
        float fz(Celestial_Body b1, Celestial_Body b2)
        {
            float X = b2.x - b1.x;
            float Y = b2.y - b1.y;
            float Z = b2.z - b1.z;
            return ((G * b2.M) * Z) / (pow(Q_rsqrt(X * X + Y * Y + Z * Z), 3));
        }
        float* FX(std::vector<Celestial_Body>& B)
        {
            float* AX = new float[n];
            for(int i = 0; i < n-1; i++)
            {
                for(int j = 0; j < n-1; j++)
                {
                    if(i!=j)
                        AX[i] += fx(B[i], B[j]);
                }
            }
            return AX;
        }
        float* FY(std::vector<Celestial_Body>& B)
        {
            float* AY = new float[n];
            for(int i = 0; i < n-1; i++)
            {
                for(int j = 0; j < n-1; j++)
                {
                    if(i!=j)
                        AY[i]+=fy(B[i], B[j]);
                }
            }
            return AY;
        }
        float* FZ(std::vector<Celestial_Body>& B)
        {
            float* AZ = new float[n];
            for(int i = 0; i < n-1; i++)
            {
                for(int j = 0; j < n-1; j++)
                {
                    if(i!=j)
                        AZ[i] += fz(B[i], B[j]);
                }
            }
            return AZ;
        }
};

class solver:public Celestial_Body
{
    public:
        void solve(std::vector<Celestial_Body>& B, float T)
        {
            int n = B.size();
            float t = T / step;
            force_calc FC(n);
            integrator I;
            float* ax=FC.FX(B);
            float* ay=FC.FY(B);
            float* az=FC.FZ(B);
            for(int i=0; i<t; i++)
            {
                for(int j=0; j<n; j++)
                {
                    B[j].ax=ax[j];
                    B[j].ay=ay[j];
                    B[j].az=az[j];
                    I.leapfrog_step1(B[j], step);
                    B[j].X[i]=B[j].x;
                    B[j].Y[i]=B[j].y;
                    B[j].Z[i]=B[j].z;
                }
                ax=FC.FX(B);
                ay=FC.FY(B);
                az=FC.FZ(B);
                for(int j=0; j<n; j++)
                    I.leapfrog_step2(B[j], step);
            }
        }  
};

void input(std::vector<Celestial_Body>& B)
{
    int n = B.size();
    for(int i=0; i<n; i++)
    {
        std::cout<<i+1<<"th Object:"<<std::endl;
        std::cout<<"Mass:";
        std::cin>>B[i].M;
        std::cout<<"Coordinates:";
        std::cin>>B[i].x;
        std::cin>>B[i].y;
        std::cin>>B[i].z;
        std::cout<<"Velocity:";
        std::cin>>B[i].vx;
        std::cin>>B[i].vy;
        std::cin>>B[i].vz;
    }
}

void output(std::vector<Celestial_Body>& B, float T, std::string filename = "")
{
    int n = B.size();
    bool write_flag = filename=="" ? false : true;
    std::ofstream my_file(filename);                       
    for(int i=0; i<n; i++)
    {
        my_file<<"Body"<<i<<std::endl;
        for(int j=0; j<T/step;j++)
        {
            if(write_flag)
                my_file<<B[i].X[j]<<","<<B[i].Y[j]<<","<<B[i].Z[j]<<std::endl;
        } 
    }
    my_file.close();
}

int main()
{
    int n;
    float T;
    solver S;
    std::cout<<"Enter the number of bodies:";
    std::cin>>n;
    std::cout<<"Enter the total time:";
    std::cin>>T;
    std::vector<Celestial_Body> B(n);
    input(B);
    S.solve(B, T);
    //output(B, T, "V1.txt");
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<T; j+=step)
        {
            std::cout<<B[i].X[j]<<"\t"<<B[i].X[j]<<"\t"<<B[i].X[j]<<std::endl;
        }
    }
}