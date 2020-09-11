#include "DebugLogger.h"

namespace winapi
{
#ifdef _DEBUG
	std::ofstream Debug::_LOGGER("log.txt");
#endif
}
