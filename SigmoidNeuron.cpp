#include "SigmoidNeuron.h"
#include <math.h>

SigmoidNeuron::SigmoidNeuron()
{
}

//from hinton neural networks for machine learning on coursera, Week 1 "some simple models of neurons"
double logisticFunction(const std::vector<double>inputs, const std::vector<double>weights, const double bias) {
	double z = 0.0;
	z += bias;
	for (size_t i = 0; i < inputs.size(); i++) {
		z += inputs[i] * weights[i];
	}
	return z;
}

//derivatives of the logit,z with respect to the inputs and the weights are very simple. z = b+ Sum(xiwi)
double input_layer(const std::vector<double> inputs, const std::vector<double> weights, const double bias) {
	double z = 0.0;
	for (size_t i = 0; i < inputs.size(); i++)
		z += inputs[i] * weights[i];
	return bias + z;
}

double hidden_layer() { return 0.0; }

double delta_rule_for_learning_linear(const double x, double y, const double t, const double e) {
	return e * x * (t - y); //t= target output value, y= actual output value, e = learning rate, x = input value
}

/*
derivative of the output with respect to each weight
*/
double delta_rule_for_learning_sigmoid(const double x, double y, const double t) {
	return -1 * x*y*(1 - y)*(t - y); //x = input value, y = actual output value, t = target output value
}

//y=1/1+e^-z
double SigmoidNeuron::sigmoid(const double z) {
	return 1 / (1 + exp(-z));
}

double SigmoidNeuron::predict(const std::vector<double>input) {
	W1 = { {0.2,0.3},{-0.4,0.5},{0,1} };//W1 and W2 will be calculated in train(), can delete assignment here
	W2 = { 2,-1,5 };
	std::vector<double>hidden_layer{ 0.0,0.0,0.0 };//hidden layer is composed of logistic neuron X * W1
	for (size_t n = 0; n < W1.size(); n++) {
		double z = 0.0;
		for (size_t m = 0; m < input.size(); m++) {
			z += input[m] * W1[n][m];
		}
		hidden_layer[n] += sigmoid(z);
	}
	double prediction = 0.0;
	for (size_t n = 0; n < W1.size(); n++) {
		prediction += hidden_layer[n] * W2[n];
	}
	return prediction;
}

void SigmoidNeuron::train(const std::vector<std::vector<double>> inputs, const std::vector<int> labels, const int array_dims) {
	double prediction = 0.0;
	//W1.assign(array_dims + 1, 0.0);
	W1 = { {0.0,0.0},{0.0,0.0},{0.0,0.0} };
	for (size_t i = 0; i < inputs.size(); i++) {
		prediction = predict(inputs[i]);
		W1[0][0] += delta_rule_for_learning_sigmoid(inputs[1, i][0], prediction, labels[i]);
		W1[1][0] += delta_rule_for_learning_sigmoid(inputs[1, i][0], prediction, labels[i]);
		W1[2][0] += delta_rule_for_learning_sigmoid(inputs[1, i][1], prediction, labels[i]);
	}
}

SigmoidNeuron::~SigmoidNeuron()
{
}
