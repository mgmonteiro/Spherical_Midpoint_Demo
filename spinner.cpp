#include "spinner.h"
#include "Integrate.h"

void spinner::spin(double spins[3], double I[3], double fH[3])
{
	//equation is ds/dt = s X grad H -------> The lines below are F = s X grad H
	double gH[3];

	for (int i = 0; i < 3; i++) {
		gH[i] = (1 / I[i]) * (2 * spins[i] + 2 * spins[i] * spins[i]);
	}
	
	//cross product
	fH[0] = spins[1] * gH[2] - spins[2] * gH[1];
	fH[1] = spins[2] * gH[0] - spins[0] * gH[2];
	fH[2] = spins[0] * gH[1] - spins[1] * gH[0];

	return;
}
