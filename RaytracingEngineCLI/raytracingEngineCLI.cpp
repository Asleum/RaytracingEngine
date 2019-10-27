#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include "Scene/Scene.h"

using namespace std;


int main(int argc, char* argv [])
{
	if (argc != 4)
	{
		cout << "usage: RaytracingEngineCli pathToInput resolutionX=300 resolutionY=200 concurrentThreads=4" << endl;
		return 0;
	}

	try {
		cout << "processing file : " << argv[1] << endl;
		Scene scene{ argv[1] };
		int resolutionX{ argc > 2 ? atoi(argv[2]) : 300 };
		int resolutionY{ argc > 3 ? atoi(argv[3]) : 200 };
		int concurrentThreads{ argc > 4 ? atoi(argv[4]) : 4 };
		scene.prepareRendering(resolutionX, resolutionY);
		auto startTime = chrono::high_resolution_clock::now();

		atomic<int> counter{ 0 };
		auto concurrentRenderer = [&scene, &counter, resolutionX, resolutionY]
		{
			while (true)
			{
				int i = counter++;
				if (i >= resolutionX * resolutionY)
					break;
				scene.renderPixel(i);
			}
		};
		vector<thread> threads;
		threads.reserve(concurrentThreads);
		for (int i = 0; i != concurrentThreads; ++i)
			threads.emplace_back(concurrentRenderer);
		for (thread& thread : threads)
			thread.join();

		auto endTime = chrono::high_resolution_clock::now();
		long long time = chrono::duration_cast<chrono::milliseconds>(endTime - startTime).count();
		cout << "sucessfully generated scene image at " << scene.finalizeRendering() << " in " << time << "ms" << endl;
	}
	catch (runtime_error e)
	{
		cout << e.what() << endl;
		return 1;
	}

	return 0;
}
