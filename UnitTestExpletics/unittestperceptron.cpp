#include "stdafx.h"
#include "CppUnitTest.h"
#include "../perceptron.h"
#include <vector>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{		
	TEST_CLASS(unittestperceptron)
	{
	public:
		
		TEST_METHOD(TestPerceptron)
		{
			std::vector<std::vector<double>> input{ {1, 1},{0.6, 0.6},{0.4, 0},{0, 0.4},{0, 0} };
			std::vector<int> labels{ 1,1,0,0,0 };
			double learning_rate = 0.01;
			int maxIter = 10;

			Perceptron p;
			p.train(input, labels, (int)2, learning_rate, maxIter);

			std::vector<double> sample{ 0.0,0.0 };
			std::vector<double> sample1{ 0.3,0.44 };
			std::vector<double> sample2{ 0.7,0.84 };
			std::vector<double> sample3{ 1.0,1.0 };

			Assert::AreEqual(0, p.predict(sample));
			Assert::AreEqual(0, p.predict(sample1));
			Assert::AreEqual(1, p.predict(sample2));
			Assert::AreEqual(1, p.predict(sample3));
		}

	};
}