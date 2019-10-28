#include "pch.h"
#include "SOKOBAN.h"
#include <iostream>

namespace SOKOBAN {
	/*SokobanSolver::SokobanSolver()
	{
	}
	SokobanSolver::SokobanSolver(std::string inputDirectory)
	{
	}*/
	SokobanSolver::SokobanSolver() :SOKOBANWrapper::ManagedObject<sokobanCore::SOKOBAN>(new sokobanCore::SOKOBAN)
	{
		
	}
	SokobanSolver::SokobanSolver(std::string inputDirectory) : SOKOBANWrapper::ManagedObject<sokobanCore::SOKOBAN>(new sokobanCore::SOKOBAN(inputDirectory))
	{

	}
	int SokobanSolver::test2()
	{
		std::cout << "test\n";
		return 11;
	}
	int SokobanSolver::test()
	{
		return m_Instance->test();
	}
	/*sTest::sTest(std::string inputDirectory): ManagedObject(new sokobanCore::SOKOBAN(inputDirectory))
	{

	}*/
}
