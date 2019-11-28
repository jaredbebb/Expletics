#pragma once
#include <vector>

class FeedForward
{
public:
	FeedForward();
	~FeedForward();

	void fit();
	int predict(std::vector<double>point);

private:
	double sigmoid();
};

