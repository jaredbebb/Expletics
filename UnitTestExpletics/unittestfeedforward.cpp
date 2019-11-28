#include "stdafx.h"
#include "CppUnitTest.h"
#include "../FeedForward.h"
#include <vector>
#include <iostream>
#include <math.h>



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
	TEST_CLASS(unittestfeedforward)
	{
	public:



		TEST_METHOD(TestFeedForwardPredict)
		{
			FeedForward ff;
			std::vector<double> points (1,6);
			Assert::AreEqual(1, ff.predict(points));
		}
	};
}