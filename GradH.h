#pragma once
struct Precession
{
	//Spin of spinning top coordinates in phase space at time t
	double s[3];
	double s1[3];
	//Inertia
	double I[3];
	//Precession function s X grad H
	double fH[3];
};

