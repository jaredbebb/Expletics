#include "stdafx.h"
#include "CppUnitTest.h"
#include "../SigmoidNeuron.h"
#include <vector>
#include <iostream>
#include <math.h>



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
	TEST_CLASS(unittestsigmoid)
	{
	public:

		TEST_METHOD(TestSigmoidPredict)
		{
			SigmoidNeuron sn;
			//Assert::AreEqual(1.0, sn.predict({ 2.0,3.0 }));
			Assert::AreEqual(1.0, sn.predict({ 0.5,0.5 }));
		}
		TEST_METHOD(TestSigmoidPredict2)
		{
			std::vector<std::vector<double>> input{ {1, 1},{0.6, 0.6},{0.4, 0},{0, 0.4},{0, 0} };
			std::vector<int> labels{ 1,1,0,0,0 };
			SigmoidNeuron s;
			s.train(input,labels, (int)2);

			std::vector<double> test{ 0.0,0.0 };
			std::vector<double> test1{ 0.3,0.44 };
			std::vector<double> test2{ 0.7,0.84 };
			std::vector<double> test3{ 1.0,1.0 };

			Assert::AreEqual(0.0, s.predict(test));
			Assert::AreEqual(0.0, s.predict(test1));
			Assert::AreEqual(1.0, s.predict(test2));
			Assert::AreEqual(1.0, s.predict(test3));
		}
	};
}