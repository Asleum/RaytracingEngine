#include "pch.h"
#include "CppUnitTest.h"
#include "Geometry/Vector3.h"
#include "testUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(VectorTests)
	{
	public:

		TEST_METHOD(BasicArithmeticWorks)
		{
			Vector3f v1{1, 2, 3};
			Vector3f v2{.5, -1, 0};
			Assert::IsTrue(Vector3f{ 1.5, 1, 3 } == v1 + v2);
			Assert::IsTrue(Vector3f{ .5, 3, 3 } == v1 - v2);
			Assert::IsTrue(Vector3f{ 2, 4, 6 } == v1 * 2);
			Assert::IsTrue(Vector3f{ .5, 1, 1.5 } == v1 / 2);
		}

		TEST_METHOD(LengthIsCorrect)
		{
			Vector3f v1{ 3, 0, 4 };
			Vector3f v2{ 0, -10, 0 };
			Assert::IsTrue(areFloatsEqual(v1.length(), 5));
			Assert::IsTrue(areFloatsEqual(v2.length(), 10));
		}

		TEST_METHOD(NormalizationWorks)
		{
			Vector3f v1{ 1, 2, 3 };
			Vector3f v2{ 0, -10, 0 };
			Assert::IsTrue(areFloatsEqual(v1.normalized().length(), 1));
			Assert::IsTrue(v2.normalized() == Vector3f{ 0, -1, 0 });
		}

		TEST_METHOD(ScalarAndCrossWork)
		{
			Vector3f v1{ 1, 2, 3 };
			Vector3f v2{ .5, -1, 0 };
			Vector3f cross = v1.cross(v2);
			Assert::IsTrue(v1.dot(v2) == v2.dot(v1));
			Assert::IsTrue(areFloatsEqual(v1.dot(v2), -1.5));
			Assert::IsTrue(cross == Vector3f{ 3, 1.5, -2 });
			Assert::IsTrue(areFloatsEqual(v1.dot(cross), 0) && areFloatsEqual(v2.dot(cross), 0));
		}

	};
}
