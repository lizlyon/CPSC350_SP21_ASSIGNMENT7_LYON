#include <iostream>
#include <string>
#include "sort.h"

using namespace std;

int main(int argc, char** argv){

		string mode = argv[1];
		int number = atoi(argv[2]);
		string filename = argv[3];

		Sort sort;
		sort.run(mode, number, filename);

		return 0;
}
