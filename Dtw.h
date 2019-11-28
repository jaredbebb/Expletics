#pragma once
#include <vector>

class Dtw
{
private:
	std::vector<std::vector<double>> pos;
	std::vector<std::vector<double>> neg;
public:
	Dtw();
	void set_time_buckets(std::vector<std::vector<double>> _pos, std::vector<std::vector<double>> _neg);
	double calculate_dtw_distance(std::vector<double> lista, std::vector<double>  listb);
	double time_bucket_dtw(std::vector<std::vector<double>> tb, std::vector<double> sample);
	double figure_of_merit(std::vector<double> sample);
	~Dtw();
};

