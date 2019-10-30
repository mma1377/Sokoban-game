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

	String^ SokobanSolver::BFS()
	{
		const unsigned int historySize = 50000;
		std::cout << "Now lest do some BFS...\n";
		unsigned int count = 0;
		STATE bfs_res = m_Instance->bfs(historySize, count);
		std::cout << "nodes count = " << count << "\npath = " << bfs_res.path;
		return sokobanConversion::char_array_to_string(bfs_res.path.c_str());
	}

	String^ SokobanSolver::BFS_Parallel(const unsigned int historySize)
	{
		std::cout << "Now lest do some BFS...\n";
		unsigned int count = 0;
		STATE bfs_res = m_Instance->bfs_omp(historySize, count);
		std::cout << "nodes count = " << count << "\npath = " << bfs_res.path;
		return sokobanConversion::char_array_to_string(bfs_res.path.c_str());
	}

	String^ SokobanSolver::BFS(const unsigned int historySize)
	{
		return BFS(50000);
	}

	String^ SokobanSolver::BFS_Parallel()
	{
		return BFS_Parallel(50000);
	}

	String^ SokobanSolver::DFS()
	{
		throw gcnew System::NotImplementedException();
		// TODO: insert return statement here
	}

	String^ SokobanSolver::IDS()
	{
		throw gcnew System::NotImplementedException();
		// TODO: insert return statement here
	}

	/*sTest::sTest(std::string inputDirectory): ManagedObject(new sokobanCore::SOKOBAN(inputDirectory))
	{

	}*/
}
