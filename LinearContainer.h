#pragma once
#include <memory>
#ifndef LINEARCONTAINER_H
#define LINEARCONTAINER_H
class LinearContainer
{
private:
	double score;
	double a;
	double b;
public:
	LinearContainer();
	~LinearContainer();
	double get_score();
	void set_score(double val);
	double get_a();
	void set_a(double val);
	double get_b();
	void set_b(double val);

};
#endif