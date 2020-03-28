#pragma once
class Integrate
{
public:
	//Perform integration on each spin component with predictor corrector approximation
	//We will use an Euler predictor followed by iteration in the implicit methods
	//A fixed toleration error is used for this particular experiment
	void timejump(double spins[3], double spins1[3], double fH[3], double I[3]);

};

