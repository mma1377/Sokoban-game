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
		std::cout << bfs_res.player.first << ' ' << bfs_res.player.second << '\t' << bfs_res.box.first << ' ' << bfs_res.box.second << '\n';
	}
	
	void SokobanSolver::BFS_OMPTest()
	{
		std::cout << "Now lest do some BFS...\n";
		STATE bfs_res = m_Instance->bfs_omp();
		std::cout << "result "<< bfs_res.player.first << ' ' << bfs_res.player.second << '\t' << bfs_res.box.first << ' ' << bfs_res.box.second << '\n';
	}

	String^ SokobanSolver::BFS()
	{
		std::cout << "Now lest do some BFS...\n";
		STATE bfs_res = m_Instance->bfs();
		std::cout << "result " << bfs_res.player.first << ' ' << bfs_res.player.second << '\t' << bfs_res.box.first << ' ' << bfs_res.box.second << '\n';
		return sokobanConversion::char_array_to_string(bfs_res.path.c_str());
	}

	String^ SokobanSolver::BFS_Parallel()
	{
		std::cout << "Now lest do some BFS...\n";
		STATE bfs_res = m_Instance->bfs_omp();
		std::cout << "result " << bfs_res.player.first << ' ' << bfs_res.player.second << '\t' << bfs_res.box.first << ' ' << bfs_res.box.second << '\n';
		return sokobanConversion::char_array_to_string(bfs_res.path.c_str());
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
