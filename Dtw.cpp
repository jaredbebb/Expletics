#include "Dtw.h"
#include <algorithm>
#include <iostream>



Dtw::Dtw()
{
}

double Dtw::calculate_dtw_distance(std::vector<double> lista, std::vector<double>  listb){
	double sizea = lista.size();
	double sizeb = listb.size();
	std::vector<std::vector<double>> distance_matrix;
	distance_matrix.resize(sizea, std::vector<double>(sizeb, 0.0));
	double top = 0.0;
	double left = 0.0;
	double diagonal = 0.0;
	double cost = 0.0;
	double current = 0.0;
	double compareTo = 0.0;
	for (int i = 0; i < sizea; i++) {
		for (int j = 0; j < sizeb; j++) {
			current = lista[i];
			compareTo = listb[j];
			cost = std::abs(current - compareTo);
			if (i == 0 && j == 0) {
				distance_matrix[i][j] = cost;
			}
			else if (i == 0) {
				left = std::abs(distance_matrix[i][j - 1]);
				distance_matrix[i][j] = left + cost;
			}
			else if (j == 0) {
				top = std::abs(distance_matrix[i - 1][j]);
				distance_matrix[i][j] = top + cost;
			}
			else {
				//TODO only have to use std::abs for each cell
				top = std::abs(distance_matrix[i - 1][j]);
				left = std::abs(distance_matrix[i][j - 1]);
				diagonal = std::abs(distance_matrix[i - 1][j - 1]);
				distance_matrix[i][j] = std::min(top, std::min(left, diagonal)) + cost;
			}
		}
	}
	return distance_matrix[sizea - 1][sizea - 1];
}

void Dtw::set_time_buckets(std::vector<std::vector<double>> _pos, std::vector<std::vector<double>> _neg) {
	pos = _pos;
	neg = _neg;
}

double Dtw::time_bucket_dtw(std::vector<std::vector<double>>  tb,std::vector<double> sample) {
	double trendscore = 0.0;
	for (size_t i = 0; i < tb.size(); i++) {
		trendscore += calculate_dtw_distance(tb[i], sample);
	}
	return trendscore;
}

double Dtw::figure_of_merit(std::vector<double> sample) {
	//std::vector<double> the_sample = {1.0,9.0};
	double figure_of_merit = 0.0;
	double up = 0.0;
	double down = 0.0;
	up = time_bucket_dtw(pos, sample);
	down = time_bucket_dtw(neg,sample);
	figure_of_merit = (1.0 / up) / (1.0 / down);
	return figure_of_merit;
}


Dtw::~Dtw()
{
}
