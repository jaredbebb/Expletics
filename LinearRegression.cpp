#include "LinearRegression.h"


LinearRegression::LinearRegression()
{
}

double LinearRegression::get_score() {
	return score;
}

void LinearRegression::set_score(double val) { score = val; }
double LinearRegression::get_a() { return a; }
void LinearRegression::set_a(double val) { a = val; }
double LinearRegression::get_b() { return b; }
void LinearRegression::set_b(double val) { b = val; }

double calculate_slope(double r, double std_devx, double std_devy) {
	return r * (std_devy / std_devx);
}

double std_deviation(double a, double length) {
	return sqrt(a / (length - 1));
}

double mean(std::vector<double> values) {
	double sum = 0.0, count = 0.0;
	for (int i = 0; i < values.size(); i++) {
		sum += values[i];
		count += 1.0;
	}
	return sum / count;
}

void LinearRegression::fit( std::vector<double> X, std::vector<double> Y) {
	double x = 0.0, x2 = 0.0, y = 0.0, y2 = 0.0, xy = 0.0;
	double meanx = 0.0, meany = 0.0;
	meanx = mean(X);
	meany = mean(Y);
	double len = X.size();
	for (int i = 0; i < len; i++) {
		x = X[i];
		y = Y[i];
		x2 += pow((x - meanx), 2);
		y2 += pow((y - meany), 2);
		xy += (x - meanx)*(y - meany);
	}
	double r = 0.0, b = 0.0, a = 0.0;
	r = xy / sqrt(x2*y2);
	set_score(pow(r, 2));
	b = calculate_slope(r, std_deviation(x2, len), std_deviation(y2, len));
	a = meany - b * meanx;
	set_b(b);
	set_a(a);
}

LinearRegression::~LinearRegression()
{
}