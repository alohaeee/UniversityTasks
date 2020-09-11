#pragma once

#include <iostream>

#include <dlfcn.h>


#include "matrix.h"
#include "myarray.h"


void* loadDLL(const char* libraryName);
void closeDLL(void *library);


template<class T>
T loadFunction(void* library, const char* functionName)
{
    T function = nullptr;
    if(library != nullptr)
    {
       function = reinterpret_cast<T>(dlsym(library,functionName));
       if(function != nullptr)
       {
           return function;
       }
       else
       {
            std::cerr << "Cannot open function, name: " << functionName << std::endl
                    << dlerror() << std::endl;
            return nullptr;
       }
    }
    else
    {
        std::cerr << "Library is not exist!\t" << library << std::endl;
        return nullptr;
    }
}

