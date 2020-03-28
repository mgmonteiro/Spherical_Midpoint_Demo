#pragma once
class spinner
{
public:
	//equation is ds/dt = s X grad H -------> The line below is F = s X grad H
	void spin(double spins[3], double I[3], double fH[3]);

};

