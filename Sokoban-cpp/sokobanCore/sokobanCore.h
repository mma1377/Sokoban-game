#pragma once
#include<utility>
#include<string>

namespace sokobanCore {

	class SOKOBAN {
	private:
		bool** gamemap;
		std::pair<int, int> player;
		std::pair<int, int> box;
		std::pair<int, int> spot;
	public:
		SOKOBAN();
		SOKOBAN(std::string inputDirectory);
		int test();
	};

}