#pragma once
#include"../sokobanCore/sokobanCore.h"
#include"ManagedObject.h"
#include"sokobanConversion.h"

using namespace SOKOBANWrapper;

namespace SOKOBAN {
	public ref class SokobanSolver : ManagedObject<sokobanCore::SOKOBAN>
	{
	public:
		SokobanSolver(String^ inputDirectory);
	};
}