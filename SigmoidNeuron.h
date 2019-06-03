#pragma once
#include <vector>

class SigmoidNeuron
{
private:
	std::vector<std::vector<double>> W1;
	std::vector<double>W2;
	double sigmoid(double z);
public:
	SigmoidNeuron();
	~SigmoidNeuron();

	void train(std::vector<std::vector<double>> inputs, std::vector<int> labels, int array_dims);
	double predict(std::vector<double>input);
};

