#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "date.h"
#include "member.h"
#include "resource.h"
#include "library.h"
#include "space.h"
#define MAX_BOOK_LEN 100
using namespace std;

int main(int argc, char** argv) {
	library lib;
	lib.process(argc, argv);
	return 0;
}