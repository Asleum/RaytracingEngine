#include <iostream>
#include "Scene/Scene.h"

using namespace std;

int main(int argc, char* argv [])
{
	if (argc != 4)
	{
		cout << "usage: RaytracingEngineCli pathToInput resolutionX resolutionY" << endl;
		return 0;
	}

	try {
		cout << "processing file : " << argv[1] << endl;
		Scene scene{ argv[1] };
		scene.prepareRendering(atoi(argv[2]), atoi(argv[3]));
		scene.renderAll();
		cout << "sucessfully generated scene image at " << scene.finalizeRendering();;
	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
		return 1;
	}

	return 0;
}