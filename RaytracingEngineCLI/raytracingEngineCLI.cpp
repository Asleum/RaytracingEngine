#include <iostream>
#include "Scene/Scene.h"

using namespace std;

int main(int argc, char* argv [])
{
	if (argc != 2)
	{
		cout << "usage: RaytracingEngineCli pathToInput" << endl;
		return 0;
	}

	try {
		cout << "processing file : " << argv[1] << endl;
		Scene scene{ argv[1] };
		scene.makeImage(300, 200);
		cout << "done" << endl;
	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
		return 1;
	}

	return 0;
}