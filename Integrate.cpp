#include "Integrate.h"
#include "spinner.h"
#include "math.h"
#include "stdio.h"


void Integrate::timejump(double spins[3], double spins1[3], double fH[3], double I[3])
{
	//faux and jump are auxiliary variables for iteration
	double fauxspin[3], jumpspin[3];
	double stop = 0.001;
	double dt = 0.5;
	double spinnorm;
	spinner X;

	//Manifold local coordinate (s_n + s_(n+1))/norm(s_n + s_(n+1))
	double sphspin[3];
	//Midpoint rule local coordinate (s_n + s_(n+1))/2
	double midspin[3];

	X.spin(spins, I, fH);

	//Perform Euler step as a first iteration, fixed timestep and fixed tolerance for this sample
	for (int i = 0; i < 3; i++) {
		fauxspin[i] = spins[i] + dt * fH[i];
	}

	spinnorm = sqrt(pow((fauxspin[0] - spins[0]), 2) + pow((fauxspin[1] - spins[1]), 2) + pow((fauxspin[2] - spins[2]), 2));

	//Classical midpoint integration
	int count_iter = 0;
	while (spinnorm > stop ) {
		
		for (int k = 0; k < 3; k++) {
			midspin[k] = 0.5 * (spins[k] + fauxspin[k]);
			jumpspin[k] = fauxspin[k];
		}

		X.spin(midspin, I, fH);
		
		for (int j = 0; j < 3; j++) {
			fauxspin[j] = spins[j] + dt * fH[j];
		}

		spinnorm = sqrt(pow((fauxspin[0] - jumpspin[0]), 2) + pow((fauxspin[1] - jumpspin[1]), 2) + pow((fauxspin[2] - jumpspin[2]), 2));
	
		count_iter++;
	}

	//Final value for the step
	printf("\n We have done: %d steps for this iteration of midpoint \n ", count_iter);
	for (int j = 0; j < 3; j++) {
		spins[j] = fauxspin[j];
	}

	//Begin new spherical midpoint step
	X.spin(spins1, I, fH);

	//Perform Euler step as a first iteration, fixed timestep and fixed tolerance for this sample
	for (int i = 0; i < 3; i++) {
		fauxspin[i] = spins1[i] + dt * fH[i];
	}

	spinnorm = sqrt(pow((fauxspin[0] - spins1[0]), 2) + pow((fauxspin[1] - spins1[1]), 2) + pow((fauxspin[2] - spins1[2]), 2));


	//Spherical midpoint integration
	count_iter = 0;
	while (spinnorm > stop) {
		double sphnorm;
		for (int k = 0; k < 3; k++) {
			sphspin[k] = (spins1[k] + fauxspin[k]);
			jumpspin[k] = fauxspin[k];
		}

		sphnorm = sqrt(sphspin[0] * sphspin[0] + sphspin[1] * sphspin[1] + sphspin[2] * sphspin[2]);
	
		for (int k = 0; k < 3; k++) {
			sphspin[k] = sphspin[k] / sphnorm;
		}
		
		X.spin(sphspin, I, fH);
	
		for (int k = 0; k < 3; k++) {
			fauxspin[k] = spins1[k] + dt * fH[k];
		}

		spinnorm = sqrt(pow((fauxspin[0] - jumpspin[0]), 2) + pow((fauxspin[1] - jumpspin[1]), 2) + pow((fauxspin[2] - jumpspin[2]), 2));

		count_iter++;
		//if (count_iter == 10) break; //To quickly test which method failed if convergence fails
	}
	printf("\n We have done: %d steps for this iteration of sphr. midpoint \n ", count_iter);
	for (int j = 0; j < 3; j++) {
		spins1[j] = fauxspin[j];
	}

	return;
}

