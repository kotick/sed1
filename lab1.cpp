#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


using namespace std;

int main(int argc, char **argv){
	char c;
	string entrada, salida, archivolog;
	while ((c = getopt (argc, argv, "i:o:l:")) != -1){
		switch (c){
			case 'i':
				entrada = optarg;
				break;
			case 'o':
				salida = optarg;
				break;
			case 'l':
				archivolog = optarg;
				break;
			default:
				cout << "error" <<endl;
				break;
		}
	}
	return 0;
}