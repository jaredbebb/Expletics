#include "stdafx.h"
#include "CppUnitTest.h"
#include "../Dtw.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestExpletics
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		std::vector<double>  lista = { 1.0,3.0,4.0,9.0,8.0,2.0,1.0,5.0,7.0,3.0 };
		std::vector<double>	 listb = { 1.0,6.0,2.0,3.0,0.0,9.0,4.0,3.0,6.0,3.0 };

		TEST_METHOD(TestMethod1)
		{
			Dtw d;
			Assert::AreEqual(15.0, d.calculate_dtw_distance(lista, listb));
			// TODO: Your test code here
		}

	};
}