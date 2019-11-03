#pragma once
#include"../sokobanCore/sokobanCore.h"
#include"../sokobanCore/sokobanCoreSingleBox.h"
#include"ManagedObject.h"
#include"sokobanConversion.h"

using namespace SOKOBANWrapper;

namespace SOKOBAN {

	private ref class SokobanSolverSingleBox : ManagedObject<sokobanCoreSingleBox::SOKOBAN>
	{
	private:
		float lastProcessTimeElapsed;
		unsigned int lastProcessNodesCount;
	public:
		SokobanSolverSingleBox(String^);
		String^ BFS(const unsigned int);
		String^ BFS_Parallel(const unsigned int);
		String^ BFS_Parallel();
		String^ BFS();
		String^ DFS(int, const unsigned int);
		String^ DFS(int);
		String^ DFS(const unsigned int);
		String^ DFS();
		String^ DFS_Parallel(int, const unsigned int);
		String^ DFS_Parallel(int);
		String^ DFS_Parallel(const unsigned int);
		String^ DFS_Parallel();
		String^ IDS(const unsigned int);
		String^ IDS();
		String^ IDS_Parallel(const unsigned int);
		String^ IDS_Parallel();
		float LastProcessTimeElapsed();
		unsigned int LastProcessNodesCount();
	};

	public ref class SokobanSolver : ManagedObject<sokobanCore::SOKOBAN>
	{
	private:
		float lastProcessTimeElapsed;
		unsigned int lastProcessNodesCount;
		bool singleBoxFlag;
		SokobanSolverSingleBox^ singleBoxSolver;
	public:
		SokobanSolver(String^);
		SokobanSolver(String^, bool);
		String^ BFS(const unsigned int);
		String^ BFS_Parallel(const unsigned int);
		String^ BFS_Parallel();
		String^ BFS();
		String^ DFS(int, const unsigned int);
		String^ DFS(int);
		String^ DFS(const unsigned int);
		String^ DFS();
		String^ DFS_Parallel(int, const unsigned int);
		String^ DFS_Parallel(int);
		String^ DFS_Parallel(const unsigned int);
		String^ DFS_Parallel();
		String^ IDS(const unsigned int);
		String^ IDS();
		String^ IDS_Parallel(const unsigned int);
		String^ IDS_Parallel();
		float LastProcessTimeElapsed();
		unsigned int LastProcessNodesCount();
	};
}