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
			Assert::AreEqual(1.0, sn.predict({ 2.0,3.0 }));
		}
	};
}