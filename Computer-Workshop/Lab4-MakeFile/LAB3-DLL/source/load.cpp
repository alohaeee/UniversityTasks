#include "load.h"


#ifdef WIN32

void* loadDLL(const char* libraryName)
{
    void* library = LoadLibrary(libraryName);
    if(library == nullptr)
    {
        std::cerr << "Can't open library, name: " << libraryName << std::endl;
        return nullptr;
    }
    return library;
}

void closeDLL(void *library)
{
    FreeLibrary((HINSTANCE)library);
}
#else
void* loadDLL(const char* libraryName)
{
    void* library = dlopen(libraryName, RTLD_LAZY);
    if(library == nullptr)
    {
        std::cerr << "Can't open library, name: " << libraryName << std::endl
            << dlerror() << std::endl;
        return nullptr;
    }
    return library;
}

void closeDLL(void *library)
{
    dlclose(library);
}
#endif