#include "Perceptron.h"
#include <numeric>
#include <iostream>


//Single layer perceptron model
Perceptron::Perceptron()
{
}

void Perceptron::train(std::vector<std::vector<double>> _inputs, std::vector<int> _labels, int array_dims, double _learningRate, int _maxIter) {
	//weights will have shape 1x3
	//add extra value for bias
	weights.assign(array_dims + 1, 0.0);
	maxIter = _maxIter;
	learningRate = _learningRate;
	inputs = _inputs;
	labels = _labels;
	for (int i = 0; i < maxIter; i++) {
		int prediction = 0;
		for (size_t j = 0; j < inputs.size(); j++) {
			prediction = predict(inputs[j]);
			weights[0] += learningRate * (labels[j] - prediction);
			weights[1] += learningRate * (labels[j] - prediction)*(inputs[1, j])[0];
			weights[2] += learningRate * (labels[j] - prediction)*(inputs[1, j])[1];
		}
	}
}

int Perceptron::predict(std::vector<double>input) {
	double sum = 0.0;
	std::vector<double> sub(weights.begin() + 1, weights.end());
	sum = std::inner_product(input.begin(), input.end(), sub.begin(), 0.0) + weights[0];
	if (sum > 0.0) { return 1; }
	else { return 0; }
}

std::vector<std::vector<double>> Perceptron::getInputs() {
	return inputs;
}

Perceptron::~Perceptron()
{
}