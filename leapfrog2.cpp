#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const float G = 1;
const float step = 1;

class Celestial_Body {
public:
    float M, x, y, z, vx, vy, vz, ax, ay, az, t;
    std::vector<float> X, Y, Z;

    Celestial_Body() : t(0) {}
};

float Q_rsqrt(float number) {
    union {
        float f;
        uint32_t i;
    } conv = {.f = number};
    conv.i = 0x5f3759df - (conv.i >> 1);
    conv.f *= 1.5F - (number * 0.5F * conv.f * conv.f);
    return conv.f;
}

class integrator {
public:
    void leapfrog_step1(Celestial_Body& B, float dt) {
        B.vx += B.ax * dt * 0.5;
        B.vy += B.ay * dt * 0.5;
        B.vz += B.az * dt * 0.5;
        B.x += B.vx * dt;
        B.y += B.vy * dt;
        B.z += B.vz * dt;
    }

    void leapfrog_step2(Celestial_Body& B, float dt) {
        B.vx += B.ax * dt * 0.5;
        B.vy += B.ay * dt * 0.5;
        B.vz += B.az * dt * 0.5;
    }
};

class force_calc {
private:
    int n;

public:
    force_calc(int N) : n(N) {}

    void calculate_forces(std::vector<Celestial_Body>& B) {
        for (int i = 0; i < n; i++) {
            B[i].ax = 0;
            B[i].ay = 0;
            B[i].az = 0;
            for (int j = 0; j < n; j++) {
                if (i != j) {
                    float X = B[j].x - B[i].x;
                    float Y = B[j].y - B[i].y;
                    float Z = B[j].z - B[i].z;
                    float dist_cubed = pow(X * X + Y * Y + Z * Z, 1.5);
                    float force = (G * B[j].M) / dist_cubed;
                    B[i].ax += force * X;
                    B[i].ay += force * Y;
                    B[i].az += force * Z;
                }
            }
        }
    }
};

class solver {
public:
    void solve(std::vector<Celestial_Body>& B, float T) {
        int n = B.size();
        int num_steps = static_cast<int>(T / step);
        force_calc FC(n);
        integrator I;

        for (int step = 0; step < num_steps; step++) {
            FC.calculate_forces(B);
            for (int j = 0; j < n; j++) {
                I.leapfrog_step1(B[j], ::step);
                B[j].X.push_back(B[j].x);
                B[j].Y.push_back(B[j].y);
                B[j].Z.push_back(B[j].z);
            }
            FC.calculate_forces(B);
            for (int j = 0; j < n; j++) {
                I.leapfrog_step2(B[j], ::step);
            }
        }
    }
};

void input(std::vector<Celestial_Body>& B) {
    int n = B.size();
    for (int i = 0; i < n; i++) {
        std::cout << i + 1 << "th Object:" << std::endl;
        std::cout << "Mass:";
        std::cin >> B[i].M;
        std::cout << "Coordinates:";
        std::cin >> B[i].x;
        std::cin >> B[i].y;
        std::cin >> B[i].z;
        std::cout << "Velocity:";
        std::cin >> B[i].vx;
        std::cin >> B[i].vy;
        std::cin >> B[i].vz;
    }
}

void output(std::vector<Celestial_Body>& B, float T, std::string filename = "") {
    int n = B.size();
    bool write_flag = !filename.empty();
    std::ofstream my_file(filename);
    my_file << std::endl;
    for(float j = 0; j < T; j += step){
        int index = static_cast<int>(j / ::step);
        for(int i = 0; i < n; i++){
            if (write_flag)
            {
                if (i==n-1)
                    my_file << B[i].X[index] << "," << B[i].Y[index] << "," << B[i].Z[index];
                else
                    my_file << B[i].X[index] << "," << B[i].Y[index] << "," << B[i].Z[index]<<",";
            }       
        }
        my_file << std::endl;
    }
    my_file.close();
}

int main() {
    int n;
    float T;
    solver S;
    std::cout << "Enter the number of bodies:";
    std::cin >> n;
    std::cout << "Enter the total time:";
    std::cin >> T;
    std::vector<Celestial_Body> B(n);
    input(B);
    S.solve(B, T);
    output(B, T, "output.txt");
    return 0;
}
