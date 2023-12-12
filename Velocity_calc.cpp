#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

const float G = 1;

int main()
{
    int n;
    float M, R, e, V;
    std::cout<<"Enter"<<std::endl<<" 1.Circular:" <<std::endl<< "2.Elliptical:"<<std::endl<<" 3.Parabolic:"<<std::endl<<" 4.Hyperbolic:";
    std::cin>>n;
    std::cout<<"Enter the mass of the star:";
    std::cin>>M;
    std::cout<<"Enter the mass of the distance between the two:";
    std::cin>>R;
    while(n>0 && n<4)
    {
        switch(n)
        {
            case 1:
                V = sqrt(G*M/R);
                break;
            case 2:
                std::cout<<"Enter the eccentriccity:";
                std::cin>>e;
                V = sqrt(G*M*(1+e)/R);
                break;
            case 3:
                V = sqrt(2*G*M/R);
                break;
            default:
                std::cout<<"Invalid input loop exited.";
        }
        std::cout<<"Velocity:"<<V;
        std::cout<<"Enter"<<std::endl<<" 1.Circular:" <<std::endl<< "2.Elliptical:"<<std::endl<<" 3.Parabolic:"<<std::endl<<" 4.Hyperbolic:";
        std::cin>>n;
    }
    return 0;
}