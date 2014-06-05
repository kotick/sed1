#include <iostream>

using namespace std;

int main(int argc, char const *argv[]){
	string c;
	string entrada, salida, archivolog;
	while ((c = getopt (argc, argv, "ai:o:")) != -1){
		switch (c){
			case 'i':
				entrada = optarg;
				break;
			case 'o':
				salid = optarg;
				break;
			case 'l':
				archivolog = optarg;
				break;
			default:
				cout <<error<<endl;
		}
	}
	return 0;
}