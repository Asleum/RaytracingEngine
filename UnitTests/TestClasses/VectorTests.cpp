#include "../pch.h"
#include "CppUnitTest.h"
#include "Scene/Scene.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

const float EPSILON{ .0001f };

bool areFloatsEqual(float x, float y) {
	return abs(x - y) < EPSILON;
}

namespace UnitTests
{
	TEST_CLASS(VectorTests)
	{
	public:

		TEST_METHOD(BasicArithmeticWorks)
		{
			Vector3f v1{1, 2, 3};
			Vector3f v2{.5, -1, 0};
			Assert::AreEqual(Vector3f{ 1.5, 1, 3 }, v1 + v2);
			Assert::AreEqual(Vector3f{ .5, 3, 3 }, v1 - v2);
			Assert::AreEqual(Vector3f{ 2, 4, 6 }, v1 * 2);
			Assert::AreEqual(Vector3f{ .5, 1, 1.5 }, v1 / 2);
		}

	};
}
