#ifndef DEBUG_H_
#define DEBUG_H_

#include <iostream>
#include <string>
#include <fstream>

#ifdef _LINUX
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <cstdlib>
#define GetCurrentProcessId getpid
#elif defined(_MSWIN)
#include <windows.h>
#elif defined(_SOLARIS)
#define __FUNCTION__ __func__
#define GetCurrentProcessId getpid
#endif

using namespace std;

#ifdef __DEBUG__
#define DEBUG cerr << "== debug [" << GetCurrentProcessId() << "][" << __FILE__ << (string) "][" << __FUNCTION__ << (string) "][" << __LINE__ << (string) "]" << endl
#define __DEBUG(errorMessage) cerr << "== debug [" << GetCurrentProcessId() << "][" << __FILE__ << (string) "][" << __FUNCTION__ << (string) "][" << __LINE__ << (string) "]: " << errorMessage << endl
#define _E_ cerr << "<< enter [" << GetCurrentProcessId() << "][" << __FUNCTION__ << (string) "]" << endl
#define _L_ cerr << ">> leave [" << GetCurrentProcessId() << "][" << __FUNCTION__ << (string) "]" << endl
#else
#define DEBUG
#define __DEBUG(errorMessage)
#define _E_
#define _L_
#endif

#endif
