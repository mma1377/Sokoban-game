#pragma once

using namespace System::Runtime::InteropServices;
using namespace System;

namespace SOKOBANWrapper {
	class sokobanConversion {
	public:
		static const char* string_to_char_array(String^ string)
		{
			const char* str = (const char*)(Marshal::StringToHGlobalAnsi(string)).ToPointer();
			return str;
		}
	};
}