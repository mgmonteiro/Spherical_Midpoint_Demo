#include "Hamiltonian.h"

double Hamiltonian::Energy(double s[3], double I[3])
{
	if ((I[0] != 0.0) && (I[1] != 0.0) && (I[2] != 0)) {

		double eng;
		for (int i = 0; i < 3; i++) {
			
			//Perturbated spinning top energy H = 1/2 * sum_j 1/Ij * (sj^2 + (2 sj^3)/3 )
			eng += (1.0 / I[i]) * ((s[i] * s[i]) + (2.0 / 3.0) * (s[i] * s[i] * s[i]));
		}

		return 0.5*eng;
	}

	else
	{
	return 0.0;
	}
	
}
