#include "pch.h"
#include "CppUnitTest.h"
#include "Scene/Scene.h"
#include "testUtils.h"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(FormatTests)
	{
	public:
		
		TEST_METHOD(BasicSceneBuildsProperly)
		{
			Scene s{ "../../TestInputs/BasicScene.xml" };
		}

		TEST_METHOD(ErrorsOnInexistingFile)
		{
			Assert::ExpectException<runtime_error>([] {Scene s{ "../../TestInputs/CeFichierNExistePas.xml" }; });
		}

		TEST_METHOD(ErrorsOnBadXml)
		{
			Assert::ExpectException<runtime_error>([] {Scene s{ "../../TestInputs/BadXml.xml" }; });
		}

		TEST_METHOD(ErrorsOnMultipleCameras)
		{
			Assert::ExpectException<runtime_error>([] {Scene s{ "../../TestInputs/TwoCameras.xml" }; });
		}

		TEST_METHOD(ReadsCoordinatesCorrrectly)
		{
			Scene s{ "../../TestInputs/BasicScene.xml" };
			Assert::IsTrue(s.getCamera() != nullptr);
			Vector3f position = s.getCamera()->getPosition();
			Vector3f orientation = s.getCamera()->getOrientation();
			Assert::IsTrue(areFloatsEqual(position.getX(), 0));
			Assert::IsTrue(areFloatsEqual(position.getY(), -20));
			Assert::IsTrue(areFloatsEqual(position.getZ(), 10));
			Assert::IsTrue(areFloatsEqual(orientation.getX(), 0));
			Assert::IsTrue(areFloatsEqual(orientation.getY(), 1));
			Assert::IsTrue(areFloatsEqual(orientation.getZ(), 0));
		}
	};
}
