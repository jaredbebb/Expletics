#pragma once

#include <vector>
class Perceptron
{
private:
	std::vector<double>weights;
	std::vector<int>labels;
	double learningRate;
	std::vector<std::vector<double>> inputs;
	int maxIter;

public:

	Perceptron();
	void train(std::vector<std::vector<double>>_inputs, std::vector<int> _labels, int array_dims, double _learningRate = 0.001, int _maxIter = 0);
	int predict(std::vector<double>input);
	std::vector<std::vector<double>> getInputs();
	~Perceptron();
};
