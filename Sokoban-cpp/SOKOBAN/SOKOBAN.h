#pragma once
#include"../sokobanCore/sokobanCore.h"
#include"ManagedObject.h"
#include<iostream>

using namespace SOKOBANWrapper;

namespace SOKOBAN {
	public ref class SokobanSolver : ManagedObject<sokobanCore::SOKOBAN>
	{
	public:
		SokobanSolver();
		SokobanSolver(std::string inputDirectory);
		int test2();
		int test();
		static void test3() {
			std::cout << "test\n";
		}
	};
}
