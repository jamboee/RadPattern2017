/**
 * @short   Compute displacements
 * @file    compute_displ.cpp
 * @author  Oluwaseun
 *
 * This file contains functions compute_displ.cpp and init_time.cpp
 * to calculate the dispalcement given necessary parameters and 
 * initialize the time vector.
 *
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <cstdlib>
#include <cmath>

#include "read_in.h"
#include "struct.h"

using namespace std;

// defining the value of PI.
#define PI 3.14159265

int compute_displ (
    double R, double theta, double phi, double *h, double *h_der,
    displacement *displ, int len, Parameters *params)
{

    double moment = params->moment; double alpha = params->alpha; double beta = params->beta;
    double rho = params->rho; string force_type = params->force_type;

//cout << RR[1]<< endl;

    // Perform operation either for Point Force, Single Couple, double_couple or force_dipole
    if (force_type == "point_force")
        for (int i=0; i<len; i++)
        {
		//cout << i << "  " << displ->P[3] << "   " << displ->SH[3] << "   "<< displ->SV[3]<< endl;
            displ->P[i]  = ((cos(theta) * PI / 180.0) * h[i]) / 
                           (4 * PI * rho * pow(alpha, 2) * R);

            displ->SH[i] = (-sin(theta * PI / 180.0) * h[i]) /
                           (4 * PI * rho * pow(beta, 2) * R);

            displ->SV[i] = displ->SH[i];
        };

    
  if (force_type == "single_couple")
        for (int i=0; i<len; i++)
        {
            displ->P[i]  = (-sin(2.0*phi * PI / 180.0)*pow(sin(theta * PI / 180.0), 2) *
                          moment * h_der[i]) / (8.0 * PI * rho * pow(alpha, 3) * R);
       
            displ->SH[i] = (sin(theta * PI / 180.0)*pow(sin(phi * PI / 180.0), 2) * 
                          moment * h_der[i]) / (8.0 * PI * rho * pow(beta, 3) * R);

            displ->SV[i] = (-sin(2.0*theta * PI / 180.0)*(sin(2.0*phi * PI / 180.0)) *
                          moment * h_der[i]) / (16.0 * PI * rho * pow(beta, 3) * R);
        }

    if (force_type == "double_couple")
        for (int i=0; i<len; i++)
        {
            displ->P[i]  = (-sin(2.0*phi * PI / 180.0)*pow(sin(theta * PI / 180.0), 2) * 
                          moment * h_der[i]) / (4.0 * PI * rho * pow(alpha, 3) * R);
        
            displ->SH[i] = (-sin(theta * PI / 180.0)*(cos(2.0*phi * PI / 180.0)) *
                          moment * h_der[i]) / (4.0 * PI * rho * pow(beta, 3) * R);
        
            displ->SV[i] = (-sin(2.0*theta * PI / 180.0)*(sin(2.0*phi * PI / 180.0)) *
                          moment * h_der[i]) / (8.0 * PI * rho * pow(beta, 3) * R);
        }

    if (force_type == "force_dipole")
        for (int i=0; i<len; i++)
        {
            displ->P[i]  = (pow(sin(theta * PI / 180.0),2)*pow(cos(phi * PI / 180.0), 2) *
                          moment * h[i]) / (4.0 * PI * rho * pow(alpha, 3) * R);

            displ->SH[i] = (-sin(theta * PI / 180.0)*(sin(2.0*phi * PI / 180.0)) *
                          moment * h[i]) / (8.0 * PI * rho * pow(beta, 3) * R);
    
            displ->SV[i] = (cos(theta * PI / 180.0)*(cos(phi * PI / 180.0)) *
                          moment * h[i]) / (4.0 * PI * rho * pow(beta, 3) * R);
        }

return 0;
};


int init_time (double *t, Parameters *params)
{
    int i = 0; 
    for (double tt=0; tt <= (params->total_time - params->time_step); tt+= params->time_step)
    {
        i++;
        t[i]  = tt;
    }

return 0;
};
