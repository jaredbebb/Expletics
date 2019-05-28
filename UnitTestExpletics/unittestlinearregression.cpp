#include "stdafx.h"
#include "CppUnitTest.h"
#include "../LinearRegression.h"
#include <vector>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
	TEST_CLASS(unittestlinearregression)
	{
	public:

		TEST_METHOD(TestLinearRegression)
		{
			std::vector<double>  x = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			std::vector<double>	 y = { 5, 10, 25, 30, 40, 50, 65, 70, 80, 90 };

			LinearRegression lc;
			lc.fit(x, y);
			Assert::AreEqual(3.0,lc.get_a());
			Assert::AreEqual(round(9.6666), round(lc.get_b()));
			Assert::AreEqual(round(.9944), round(lc.get_score()));
		}

	};
}