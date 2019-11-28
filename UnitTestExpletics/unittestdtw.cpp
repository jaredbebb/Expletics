#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Dtw.h"
#include <vector>
#include <iostream>
#include <math.h>



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
	TEST_CLASS(unittestdtw)
	{
	public:
		std::vector<double>  lista = { 1.0,3.0,4.0,9.0,8.0,2.0,1.0,5.0,7.0,3.0 };
		std::vector<double>	 lista1 = { 1.0,3.0,4.0,9.0,8.0,2.0,1.0,5.0,7.0,3.0 };
		std::vector<double>	 listb = { 1.0,6.0,2.0,3.0,0.0,9.0,4.0,3.0,6.0,3.0 };
		std::vector<double>	 trenddown = { 16.0,8.0,4.0,2.0,0.0,0.0,0.0 };
		std::vector<double>	 trendup = { 16.0, 8.0, 4.0, 2.0, 0.0, 0.0, 0.0 };
		std::vector<double>	 trendflat = { 16.0, 16.0, 16.0, 16.0, 16.0, 16.0, 16.0 };
		std::vector<std::string>	 str_arr = { "hi","hi", "heelo","heelo","heelo", "bye","bye" };
		std::vector<double>	 short_trend = { 16.0,8.0,5.0,3.0 };
		

		TEST_METHOD(TestDtw)
		{
			Dtw d;
			Assert::AreEqual(15.0, d.calculate_dtw_distance(lista, listb));
			Assert::AreEqual(0.0, d.calculate_dtw_distance(lista, lista1));
		}

		TEST_METHOD(TestFlat)
		{
			Dtw d;
			double up = d.calculate_dtw_distance(trendflat, trendup);
			double down = d.calculate_dtw_distance(trendflat, trenddown);
			Assert::AreEqual(1.0, (1.0 / up) / (1.0 / down));
		}

		TEST_METHOD(TestTimeBucket) {
			Dtw d;
			std::vector<std::vector<double>> pos{ {1.0,2.0,4.0,8.0,16.0,32.0,64.0,128.0,256.0,512.0},{1.0,2.0,4.0,8.0,16.0,32.0,64.0,128.0,256.0,513.0}};
			std::vector<std::vector<double>> neg{ {512.0,256.0,128.0,64.0,32.0,16.0,8.0,4.0,2.0,1.0},{513.0,256.0,128.0,64.0,32.0,16.0,8.0,4.0,2.0,1.0} };
			d.set_time_buckets(pos,neg);
			std::vector<double>  pulse = { 1.0,2.0,4.0,8.0,16.0,16.0,8.0,4.0,2.0,1.0 };
			std::vector<double>  ramp_up = { 1.0,2.0,4.0,8.0,16.0,32.0,64.0,128.0,256.0,511.0 };
			std::vector<double>  ramp_down = { 511.0,256.0,128.0,64.0,32.0,16.0,8.0,4.0,2.0,1.0 };
			Assert::AreEqual(1.0, double(roundf(d.figure_of_merit(pulse) * 100) / 100));
			Assert::AreEqual(float(1281), roundf(d.figure_of_merit(ramp_up) * 100) / 100);
			Assert::AreEqual(float(0.0008), roundf(d.figure_of_merit(ramp_down) * 10000) / 10000);
		}
	};
}