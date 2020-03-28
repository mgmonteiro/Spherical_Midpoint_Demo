/*    /\_____/\     ===     Perturbated spinning top
     /  o   o  \    ===     Author: Maxwell Gama
    ( ==  ^  == )   ===     Contact: maxweljr@gmail.com
     )         (    ===     
    (           )   ===     Description: code made to showcase a Predictor-Corrector
   ( (  )   (  ) )  ===     "Spherical Midpoint" method. Uses the implicit integrator at
  (__(__)___(__)__) ===     DOI:10.1103/PhysRevE.89.061301
                    ===     If you are here for the integrator, you are looking for 'Integrate.cpp'

*/


#include <cstdio>
#include "GradH.h"
#include "Integrate.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <stdlib.h>
#include "Hamiltonian.h"


using namespace std;
using namespace std::chrono;

int main()
{
    //Object containing problem description
    Precession Simul;
    Hamiltonian Conserve;
    Integrate Equations;

    //Initial spin conditions
    Simul.s[0] = 0.0;
    Simul.s[1] = 0.7248;
    Simul.s[2] = -0.6889;
    Simul.s1[0] = 0.0;
    Simul.s1[1] = 0.7248;
    Simul.s1[2] = -0.6889;
    //Inertia tensor I
    Simul.I[0] = 1.0;
    Simul.I[1] = 2.0;
    Simul.I[2] = 4.0;
    //Hamiltonian
    double energy_midpoint = 0.0;
    double energy_sphere = 0.0;
    //Total simulated and simulation times (adimensional)
    int steps, u = 0;
    double dt = 0.5; 
    double elapsed_time = 2000.0;

    //File for output of trajectory
    ofstream trjmidpoint, trjsphere, energycheck;
    trjmidpoint.open("trj_midpoint.dat", ios::trunc);
    trjsphere.open("trj_sphere.dat", ios::trunc);
    energycheck.open("energy_drift.dat", ios::trunc);

    cout << "\n >>>>>>>>>>>>>>>>>>>>>>>>> Starting Simulation\n";
    //First Energies    
    double eng0mid = Conserve.Energy(Simul.s, Simul.I);
    double eng0sph = Conserve.Energy(Simul.s1, Simul.I);
    
    if (energycheck.is_open()) {
        energycheck << "#This file contains energy values in the format\n#E_midpoint E_sphere |E_n-E_0|mid |E_n-E_0|sph\n";
        energycheck << eng0mid << "\t" << eng0sph << "\t" << "0.0" << "\t" << "0.0\n";
    }
    //Starting runtime clock
    auto start = high_resolution_clock::now();
    
    //Loop over total time
    steps = (int)(elapsed_time / dt);
    cout << "steps =" << steps;
    while (u <= steps) {
        //write results of time n to file
        if (trjmidpoint.is_open()&&trjsphere.is_open()&&energycheck.is_open()) {
            trjmidpoint << Simul.s[0] << "\t" << Simul.s[1] << "\t" << Simul.s[2] << endl;
            trjsphere << Simul.s1[0] << "\t" << Simul.s1[1] << "\t" << Simul.s1[2] << endl;
        }
        else {
            cout << "Files failed to open. Program exitting now.\n";
            exit(1);
        }

        //Energy must be conserved
        energy_midpoint = Conserve.Energy(Simul.s, Simul.I);
        energy_sphere = Conserve.Energy(Simul.s1, Simul.I);
        cout << "We are at step" <<  u << "\n";
        energycheck << energy_midpoint << "\t" << energy_sphere << "\t" << abs(energy_midpoint - eng0mid) << "\t" << abs(energy_sphere - eng0sph) << "\n";

        //Integrate using each of the methods
        Equations.timejump(Simul.s, Simul.s1, Simul.fH, Simul.I);
        u++;
    }

    //Because of writing order we need to write last step results
    if (trjmidpoint.is_open() && trjsphere.is_open()) {
        trjmidpoint << Simul.s[0] << "\t" << Simul.s[1] << "\t" << Simul.s[2] << endl;
        trjsphere << Simul.s1[0] << "\t" << Simul.s1[1] << "\t" << Simul.s1[2] << endl;
    }
    else {
        cout << "Files failed to open. Program exitting now.\n";
        exit(1);
    }


    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<seconds>(stop - start);

    cout << "Time taken to run simulations:"<< duration.count() << "s\n";
    cout << ">>>>>>>>>>>>>Program finished, files trj_midpoint and trj_sphere are ready.\n";
        
    trjmidpoint.close();
    trjsphere.close();
    energycheck.close();

    return 0;
}