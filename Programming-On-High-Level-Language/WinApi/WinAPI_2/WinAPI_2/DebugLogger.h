#pragma once

#ifdef _DEBUG

#include <fstream>

namespace winapi
{
	namespace Debug
	{
		extern std::ofstream _LOGGER;
#endif // DEBUG
		template<class T>
		void Log(T&& object)
		{
#ifdef _DEBUG
			_LOGGER << std::forward<T>(object) << std::endl;
#endif // DEBUG
		}
	}
	



}
