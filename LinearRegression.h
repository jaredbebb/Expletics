#pragma once

#ifndef LINEARREGRESSION_H
#define LINEARREGRESSION_H

#include <vector>
#include <memory>
class LinearRegression
{
private:
	double score;
	double a;
	double b;
public:
	LinearRegression();
	~LinearRegression();
	double get_score();
	void set_score(double val);
	double get_a();
	void set_a(double val);
	double get_b();
	void set_b(double val);
	void fit(std::vector<double> X, std::vector<double> Y);

};
#endif