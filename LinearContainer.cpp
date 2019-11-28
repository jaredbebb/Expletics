#include "LinearContainer.h"

LinearContainer::LinearContainer()
{
}

LinearContainer::~LinearContainer()
{
}


double LinearContainer::get_score() { 
	return score; }

/**set the score of object **/
void LinearContainer::set_score(double val) { score = val; }
double LinearContainer::get_a() { return a; }
void LinearContainer::set_a(double val) { a = val; }
double LinearContainer::get_b() { return b; }
void LinearContainer::set_b(double val) { b = val; }
