#pragma once
#include"../sokobanCore/sokobanCore.h"
#include"ManagedObject.h"
#include"sokobanConversion.h"

using namespace SOKOBANWrapper;

namespace SOKOBAN {
	public ref class SokobanSolver : ManagedObject<sokobanCore::SOKOBAN>
	{
	private:
		float lastProcessTimeElapsed;
		unsigned int lastProcessNodesCount;
	public:
		SokobanSolver(String^);
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