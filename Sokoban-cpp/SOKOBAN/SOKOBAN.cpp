#include "pch.h"
#include "SOKOBAN.h"
#include <iostream>

namespace SOKOBAN {

	SokobanSolver::SokobanSolver(String^ inputDirectory) : SOKOBANWrapper::ManagedObject<sokobanCore::SOKOBAN>(new sokobanCore::SOKOBAN(sokobanConversion::string_to_char_array(inputDirectory)))
	{
		singleBoxFlag = false;
	}

	SokobanSolver::SokobanSolver(String^ inputDirectory, bool isSingleBox) : SOKOBANWrapper::ManagedObject<sokobanCore::SOKOBAN>(new sokobanCore::SOKOBAN(sokobanConversion::string_to_char_array(inputDirectory)))
	{
		singleBoxFlag = isSingleBox;
		if (singleBoxFlag)
			singleBoxSolver = gcnew SokobanSolverSingleBox(inputDirectory);
	}

	String^ SokobanSolver::BFS(const unsigned int historySize)
	{
		if (singleBoxFlag)
			return singleBoxSolver->BFS(historySize);
		std::cout << "Now let's do some BFS...\n";
		unsigned int count = 0;
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		sokobanCore::STATE bfs_res;
		bfs_res = m_Instance->bfs(historySize, count);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		lastProcessTimeElapsed = (float)std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000;
		lastProcessNodesCount = count;
		std::cout << "nodes count = " << count << "\npath = " << bfs_res.path;
		return sokobanConversion::char_array_to_string(bfs_res.path.c_str());
	}

	String^ SokobanSolver::BFS_Parallel(const unsigned int historySize)
	{
		if (singleBoxFlag)
			return singleBoxSolver->BFS_Parallel(historySize);
		std::cout << "Now let's do some BFS...\n";
		unsigned int count = 0;
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		sokobanCore::STATE bfs_res = m_Instance->bfs_omp(historySize, count);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		lastProcessTimeElapsed = (float)std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000;
		lastProcessNodesCount = count;
		std::cout << "nodes count = " << count << "\npath = " << bfs_res.path;
		return sokobanConversion::char_array_to_string(bfs_res.path.c_str());
	}

	String^ SokobanSolver::BFS()
	{
		if (singleBoxFlag)
			return singleBoxSolver->BFS();
		return BFS(200000);
	}

	String^ SokobanSolver::BFS_Parallel()
	{
		if (singleBoxFlag)
			return singleBoxSolver->BFS_Parallel();
		return BFS_Parallel(200000);
	}

	String^ SokobanSolver::DFS(int max_depth, const unsigned int history_size)
	{
		if (singleBoxFlag)
			return singleBoxSolver->DFS(max_depth, history_size);
		unsigned int count = 0;
		std::cout << "Now let's do some DFS...\n";
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		sokobanCore::STATE dfs_res = m_Instance->dfs(max_depth, history_size, count);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		lastProcessTimeElapsed = (float)std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000;
		lastProcessNodesCount = count;
		std::cout << "nodes count = " << count << "\npath = " << dfs_res.path;
		return sokobanConversion::char_array_to_string(dfs_res.path.c_str());
	}

	String^ SokobanSolver::DFS_Parallel(int max_depth, const unsigned int history_size)
	{
		if (singleBoxFlag)
			return singleBoxSolver->DFS_Parallel(max_depth, history_size);
		unsigned int count = 0;
		std::cout << "Now let's do some DFS...\n";
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		sokobanCore::STATE dfs_res = m_Instance->dfs_omp(max_depth, history_size, count);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		lastProcessTimeElapsed = (float)std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000;
		lastProcessNodesCount = count;
		std::cout << "nodes count = " << count << "\npath = " << dfs_res.path;
		return sokobanConversion::char_array_to_string(dfs_res.path.c_str());
	}

	String^ SokobanSolver::DFS(int max_depth)
	{
		if (singleBoxFlag)
			return singleBoxSolver->DFS(max_depth);
		return DFS(max_depth, 200000);
	}

	String^ SokobanSolver::DFS(const unsigned int history_size)
	{
		if (singleBoxFlag)
			return singleBoxSolver->DFS(history_size);
		return DFS(UINT_MAX, history_size);
	}

	String^ SokobanSolver::DFS_Parallel(const unsigned int history_size)
	{
		if (singleBoxFlag)
			return singleBoxSolver->DFS_Parallel(history_size);
		return DFS_Parallel(UINT_MAX, history_size);
	}

	String^ SokobanSolver::DFS_Parallel(int max_depth)
	{
		if (singleBoxFlag)
			return singleBoxSolver->DFS_Parallel(max_depth);
		return DFS_Parallel(max_depth, 200000);
	}

	String^ SokobanSolver::DFS()
	{
		if (singleBoxFlag)
			return singleBoxSolver->DFS();
		return DFS(UINT_MAX);
	}

	String^ SokobanSolver::DFS_Parallel()
	{
		if (singleBoxFlag)
			return singleBoxSolver->DFS_Parallel();
		return DFS_Parallel(UINT_MAX);
	}

	String^ SokobanSolver::IDS(const unsigned int historySize)
	{
		if (singleBoxFlag)
			return singleBoxSolver->IDS(historySize);
		std::cout << "Now lest do some IDS...\n";
		unsigned int count = 0;
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		sokobanCore::STATE bfs_res = m_Instance->ids(historySize, count);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		lastProcessTimeElapsed = (float)std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000;
		lastProcessNodesCount = count;
		std::cout << "nodes count = " << count << "\npath = " << bfs_res.path;
		return sokobanConversion::char_array_to_string(bfs_res.path.c_str());
	}

	String^ SokobanSolver::IDS_Parallel(const unsigned int historySize)
	{
		if (singleBoxFlag)
			return singleBoxSolver->IDS_Parallel(historySize);
		std::cout << "Now lest do some IDS...\n";
		unsigned int count = 0;
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		sokobanCore::STATE bfs_res = m_Instance->ids_omp(historySize, count);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		lastProcessTimeElapsed = (float)std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000;
		lastProcessNodesCount = count;
		std::cout << "nodes count = " << count << "\npath = " << bfs_res.path;
		return sokobanConversion::char_array_to_string(bfs_res.path.c_str());
	}

	String^ SokobanSolver::IDS()
	{
		if (singleBoxFlag)
			return singleBoxSolver->IDS();
		return IDS(200000);
	}

	String^ SokobanSolver::IDS_Parallel()
	{
		if (singleBoxFlag)
			return singleBoxSolver->IDS_Parallel();
		return IDS_Parallel(200000);
	}

	float SokobanSolver::LastProcessTimeElapsed()
	{
		if (singleBoxFlag)
			return singleBoxSolver->LastProcessTimeElapsed();
		return lastProcessTimeElapsed;
	}

	unsigned int SokobanSolver::LastProcessNodesCount()
	{
		if (singleBoxFlag)
			return singleBoxSolver->LastProcessNodesCount();
		return lastProcessNodesCount;
	}

	SokobanSolverSingleBox::SokobanSolverSingleBox(String^ inputDirectory) : SOKOBANWrapper::ManagedObject<sokobanCoreSingleBox::SOKOBAN>(new sokobanCoreSingleBox::SOKOBAN(sokobanConversion::string_to_char_array(inputDirectory)))
	{
	}

	String^ SokobanSolverSingleBox::BFS(const unsigned int historySize)
	{

		std::cout << "Now let's do some BFS...\n";
		unsigned int count = 0;
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		sokobanCoreSingleBox::STATE bfs_res = m_Instance->bfs(historySize, count);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		lastProcessTimeElapsed = (float)std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000;
		lastProcessNodesCount = count;
		std::cout << "nodes count = " << count << "\npath = " << bfs_res.path;
		return sokobanConversion::char_array_to_string(bfs_res.path.c_str());
	}

	String ^ SokobanSolverSingleBox::BFS_Parallel(const unsigned int historySize)
	{
		std::cout << "Now let's do some BFS...\n";
		unsigned int count = 0;
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		sokobanCoreSingleBox::STATE bfs_res = m_Instance->bfs_omp(historySize, count);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		lastProcessTimeElapsed = (float)std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000;
		lastProcessNodesCount = count;
		std::cout << "nodes count = " << count << "\npath = " << bfs_res.path;
		return sokobanConversion::char_array_to_string(bfs_res.path.c_str());
	}

	String ^ SokobanSolverSingleBox::BFS()
	{
		return BFS(200000);
	}

	String^ SokobanSolverSingleBox::BFS_Parallel()
	{
		return BFS_Parallel(200000);
	}

	String^ SokobanSolverSingleBox::DFS(int max_depth, const unsigned int history_size)
	{
		unsigned int count = 0;
		std::cout << "Now let's do some DFS...\n";
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		sokobanCoreSingleBox::STATE dfs_res = m_Instance->dfs(max_depth, history_size, count);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		lastProcessTimeElapsed = (float)std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000;
		lastProcessNodesCount = count;
		std::cout << "nodes count = " << count << "\npath = " << dfs_res.path;
		return sokobanConversion::char_array_to_string(dfs_res.path.c_str());
	}

	String ^ SokobanSolverSingleBox::DFS_Parallel(int max_depth, const unsigned int history_size)
	{
		unsigned int count = 0;
		std::cout << "Now let's do some DFS...\n";
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		sokobanCoreSingleBox::STATE dfs_res = m_Instance->dfs_omp(max_depth, history_size, count);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		lastProcessTimeElapsed = (float)std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000;
		lastProcessNodesCount = count;
		std::cout << "nodes count = " << count << "\npath = " << dfs_res.path;
		return sokobanConversion::char_array_to_string(dfs_res.path.c_str());
	}

	String ^ SokobanSolverSingleBox::DFS(int max_depth)
	{
		return DFS(max_depth, 200000);
	}

	String^ SokobanSolverSingleBox::DFS(const unsigned int history_size)
	{
		return DFS(UINT_MAX, history_size);
	}

	String^ SokobanSolverSingleBox::DFS_Parallel(const unsigned int history_size)
	{
		return DFS_Parallel(UINT_MAX, history_size);
	}

	String^ SokobanSolverSingleBox::DFS_Parallel(int max_depth)
	{
		return DFS_Parallel(max_depth, 200000);
	}

	String^ SokobanSolverSingleBox::DFS()
	{
		return DFS(UINT_MAX);
	}

	String^ SokobanSolverSingleBox::DFS_Parallel()
	{
		return DFS_Parallel(UINT_MAX);
	}

	String^ SokobanSolverSingleBox::IDS(const unsigned int historySize)
	{

		std::cout << "Now lest do some IDS...\n";
		unsigned int count = 0;
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		sokobanCoreSingleBox::STATE bfs_res = m_Instance->ids(historySize, count);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		lastProcessTimeElapsed = (float)std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000;
		lastProcessNodesCount = count;
		std::cout << "nodes count = " << count << "\npath = " << bfs_res.path;
		return sokobanConversion::char_array_to_string(bfs_res.path.c_str());
	}

	String ^ SokobanSolverSingleBox::IDS_Parallel(const unsigned int historySize)
	{
		std::cout << "Now lest do some IDS...\n";
		unsigned int count = 0;
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		sokobanCoreSingleBox::STATE bfs_res = m_Instance->ids_omp(historySize, count);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		lastProcessTimeElapsed = (float)std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() / 1000;
		lastProcessNodesCount = count;
		std::cout << "nodes count = " << count << "\npath = " << bfs_res.path;
		return sokobanConversion::char_array_to_string(bfs_res.path.c_str());
	}

	String ^ SokobanSolverSingleBox::IDS()
	{
		return IDS(200000);
	}

	String^ SokobanSolverSingleBox::IDS_Parallel()
	{
		return IDS_Parallel(200000);
	}

	float SokobanSolverSingleBox::LastProcessTimeElapsed()
	{
		return lastProcessTimeElapsed;
	}

	unsigned int SokobanSolverSingleBox::LastProcessNodesCount()
	{
		return lastProcessNodesCount;
	}
}
