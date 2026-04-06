#include <iostream>
#include <string>
#include <fstream>
#include <iomanip> // 1/17/2026 is for this one and the ones above
#include <cstdlib>
#include <sstream> // 1/22/2026 is for this one and the one above

#include "karatedojo.h"
#include "StudentInfo.h"

using namespace std;

#ifdef DEBUG

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

#else


int main() { //main function, calling the right functions
	karatedojo dojo;
	dojo.introbanner();
	dojo.menu();
	return 0;
}


#endif // DEBUG
