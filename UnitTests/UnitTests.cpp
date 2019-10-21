#include "pch.h"
#include "CppUnitTest.h"
#include "Scene/Camera.h"
#include "Scene/Scene.h"
#include "Scene/Scene.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(ReadingTests)
	{
	public:
		
		TEST_METHOD(BasicSceneBuildsProperly)
		{
			Scene s{ "../TestInputs/BasicScene.xml" };
		}

		TEST_METHOD(ErrorsOnInexistingFile)
		{
			Assert::ExpectException<runtime_error>([] {Scene s{ "../TestInputs/CeFichierNExistePas.xml" }; });
		}

		TEST_METHOD(ErrorsOnBadXml)
		{
			Assert::ExpectException<runtime_error>([] {Scene s{ "../TestInputs/BadXml.xml" }; });
		}

		TEST_METHOD(ErrorsOnMultipleCameras)
		{
			Assert::ExpectException<runtime_error>([] {Scene s{ "../TestInputs/TwoCameras.xml" }; });
		}
	};
}
