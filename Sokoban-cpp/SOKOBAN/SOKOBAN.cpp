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
	SokobanSolver::SokobanSolver(String^ inputDirectory) : SOKOBANWrapper::ManagedObject<sokobanCore::SOKOBAN>(new sokobanCore::SOKOBAN(sokobanConversion::string_to_char_array(inputDirectory)))
	{

	}

	void SokobanSolver::BFSTest()
	{
		std::cout << "Now lest do some BFS...\n";
		STATE bfs_res = m_Instance->bfs();
		std::cout << bfs_res.first.first << ' ' << bfs_res.first.second << '\t' << bfs_res.second.first << ' ' << bfs_res.second.second << '\n';
	}
	
	void SokobanSolver::BFS_OMPTest()
	{
		std::cout << "Now lest do some BFS...\n";
		STATE bfs_res = m_Instance->bfs_omp();
		std::cout << "result "<< bfs_res.first.first << ' ' << bfs_res.first.second << '\t' << bfs_res.second.first << ' ' << bfs_res.second.second << '\n';
	}

	/*sTest::sTest(std::string inputDirectory): ManagedObject(new sokobanCore::SOKOBAN(inputDirectory))
	{

	}*/
}
