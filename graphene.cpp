#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <complex>
#include <cmath>


#include <Eigen/Core>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

using namespace std::literals::complex_literals;


// atoms positions

double RA[2] = {0.666667000,1.333333000};
double R1[2] = {0.333333000,1.666667000};
double R2[2] = {1.333333000,1.666667000};
double R3[2] = {0.333333000,0.666667000};

#define GAMMA_0 ((double)-2.78)
#define S_0     ((double) 0.06)
#define E_2p    ((double) 0.00)


void create_hamiltonian(Eigen::MatrixXcd &H, const double kx, const double ky)
{
    H(0,0) = E_2p;
    H(1,0) = GAMMA_0*(  std::exp( 2*M_PI*1i*(kx*(RA[0] - R1[0]) + ky*(RA[1] - R1[1])) ) +
                        std::exp( 2*M_PI*1i*(kx*(RA[0] - R2[0]) + ky*(RA[1] - R2[1])) ) +
                        std::exp( 2*M_PI*1i*(kx*(RA[0] - R3[0]) + ky*(RA[1] - R3[1])) )   );
    H(0,1) = std::conj(H(1,0));
    H(1,1) = E_2p;
}

void create_overlaps(Eigen::MatrixXcd &S, const double kx, const double ky)
{
    S(0,0) = 1.0;
    S(1,0) = S_0*(  std::exp( 2*M_PI*1i*(kx*(RA[0] - R1[0]) + ky*(RA[1] - R1[1])) ) +
                    std::exp( 2*M_PI*1i*(kx*(RA[0] - R2[0]) + ky*(RA[1] - R2[1])) ) +
                    std::exp( 2*M_PI*1i*(kx*(RA[0] - R3[0]) + ky*(RA[1] - R3[1])) )   );
    S(0,1) = std::conj(S(1,0));
    S(1,1) = 1.0;
}




int main(int argc, char* argv[])
{
    
//     Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd> eigensolver;
    Eigen::MatrixXcd H(2,2);
    Eigen::MatrixXcd S(2,2);
    
    double kx,ky, dkx, dky;
    
    std::ofstream file;
    file.open("graphene.dat");
    
    
    // path M-Gamma
    std::cout << "M-Gamma" <<std::endl;
    dkx = 0.00;
    dky = - 0.01/2.0;
    for (unsigned ix = 0; ix <= 100; ix++)
    {
        kx = 0.0     + dkx*ix;
        ky = 1.0/2.0 + dky*ix;
        
        create_hamiltonian(H,kx,ky);
        create_overlaps(S,kx,ky);
        
        Eigen::GeneralizedSelfAdjointEigenSolver<Eigen::MatrixXcd> eigensolver(H,S,Eigen::Ax_lBx | Eigen::EigenvaluesOnly);
        
        std::cout << std::setprecision(2) << std::fixed;
        std::cout << "(" << kx << "," << ky << ")" << "\t";
        std::cout << eigensolver.eigenvalues().transpose() << std::endl;
        file      << std::setprecision(15) << std::fixed;
        file      <<  kx << "\t" << ky << "\t";
        file      << eigensolver.eigenvalues().transpose() << std::endl;
        
    }
    
    // path Gamma-K
    std::cout << "Gamma-K" <<std::endl;
    dkx = 0.01/3.0;
    dky = 0.01/3.0;
    for (unsigned ix = 0; ix <= 100; ix++)
    {
        kx = 0.0 + dkx*ix;
        ky = 0.0 + dky*ix;
        
        create_hamiltonian(H,kx,ky);
        create_overlaps(S,kx,ky);
        
        Eigen::GeneralizedSelfAdjointEigenSolver<Eigen::MatrixXcd> eigensolver(H,S,Eigen::Ax_lBx | Eigen::EigenvaluesOnly);
        
        std::cout << std::setprecision(2) << std::fixed;
        std::cout << "(" << kx << "," << ky << ")" << "\t";
        std::cout << eigensolver.eigenvalues().transpose() << std::endl;
        file      << std::setprecision(15) << std::fixed;
        file      <<  kx << "\t" << ky << "\t";
        file      << eigensolver.eigenvalues().transpose() << std::endl;
        
    }
    
    // path K-M
    std::cout << "K-M" <<std::endl;
    dkx = - 0.01/3.0;
    dky =   0.01/6.0;
    for (unsigned ix = 0; ix <= 100; ix++)
    {
        kx = 1.0/3.0 + dkx*ix;
        ky = 1.0/3.0 + dky*ix;
        
        create_hamiltonian(H,kx,ky);
        create_overlaps(S,kx,ky);
        
        Eigen::GeneralizedSelfAdjointEigenSolver<Eigen::MatrixXcd> eigensolver(H,S,Eigen::Ax_lBx | Eigen::EigenvaluesOnly);
        
        std::cout << std::setprecision(2) << std::fixed;
        std::cout << "(" << kx << "," << ky << ")" << "\t";
        std::cout << eigensolver.eigenvalues().transpose() << std::endl;
        file      << std::setprecision(15) << std::fixed;
        file      <<  kx << "\t" << ky << "\t";
        file      << eigensolver.eigenvalues().transpose() << std::endl;
        
    }
    
    
    
    file.close();
    
    return EXIT_SUCCESS;
}