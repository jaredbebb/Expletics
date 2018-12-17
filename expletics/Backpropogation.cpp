#include "Backpropogation.h"
#include <math.h>

Backpropogation::Backpropogation()
{
}

//Witten,Data Mining p. 235
//f(x) - 1/(1+e^-x)
double sigmoid(double e, double x) {
	double fx = 1 / (pow(e, -x));
	return fx;
}

//squared-error loss function
//Witten p.235
//E = 1/2(y-f(x))^2
double squared_error_loss(double y, double fx, double e, double x) {
	double E = 1/2*pow(y-sigmoid(e,x),2);
}

Backpropogation::~Backpropogation()
{
}
