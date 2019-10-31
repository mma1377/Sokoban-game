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

	String^ SokobanSolver::BFS(const unsigned int historySize)
	{
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

	String^ SokobanSolver::BFS()
	{
		return BFS(25000);
	}

	String^ SokobanSolver::BFS_Parallel()
	{
		return BFS_Parallel(25000);
	}

	String^ SokobanSolver::DFS(int max_depth, const unsigned int history_size)
	{
		unsigned int count = 0;
		STATE dfs_res = m_Instance->dfs(max_depth, history_size, count);
		std::cout << "nodes count = " << count << "\npath = " << dfs_res.path;
		return sokobanConversion::char_array_to_string(dfs_res.path.c_str());
	}

	String^ SokobanSolver::DFS_Parallel(int max_depth, const unsigned int history_size)
	{
		unsigned int count = 0;
		STATE dfs_res = m_Instance->dfs_omp(max_depth, history_size, count);
		std::cout << "nodes count = " << count << "\npath = " << dfs_res.path;
		return sokobanConversion::char_array_to_string(dfs_res.path.c_str());
	}

	String^ SokobanSolver::DFS(int max_depth)
	{
		return DFS(max_depth, 25000);
	}

	String^ SokobanSolver::DFS_Parallel(int max_depth)
	{
		return DFS_Parallel(max_depth, 25000);
	}

	String^ SokobanSolver::DFS()
	{
		return DFS(UINT_MAX);
	}

	String^ SokobanSolver::DFS_Parallel()
	{
		return DFS_Parallel(UINT_MAX);
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
