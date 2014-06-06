#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <vector>
#include <sys/time.h>
#include <time.h>

using namespace std;

class Parametros
{
public:
	int numproc,
		algoritmo,
		algoritmo1,
		interarrivo,
		interarrivo1,
		interarrivo2,
		servicio,
		servicio1,
		servicio2,
		rp,
		rp1,
		rp2,
		rio,
		rio1,
		rio2;

	Parametros (){}	;


	bool lectura (string intxt)
	{
		fstream filein(intxt.c_str(), ios::in);
		if (!filein.is_open())
		{
			cout << intxt << " no existe o no se puede cargar" << endl;
			return false;
		}
		while (!filein.eof())
		{
			string getline;
			filein >> getline;
			if (!getline.compare("numproc"))
			{
				filein >> getline;
				numproc = atoi (getline.c_str());
				cout << numproc << endl;
			}
			else if (!getline.compare("algoritmo"))
			{
				filein >> getline;
				if (getline.find("FCFS") == 0)
					algoritmo = 1;
				else if (getline.find("SJF") == 0)
					algoritmo = 2;
				else if (getline.find("RR") == 0)
				{
					algoritmo = 3;
					filein >> getline;
					algoritmo1 = atoi (getline.c_str());
				}
				cout << algoritmo << algoritmo1  << endl;
			}
			else if (!getline.compare("interarrivo"))
			{
				filein >> getline;
				if (getline.find("uniforme") == 0)
				{
					interarrivo = 1;
					filein >> getline;
					interarrivo1 = atoi (getline.c_str());
					filein >> getline;
					interarrivo2 = atoi (getline.c_str());
				}
				else if (getline.find("expotencial") == 0)
				{
					interarrivo = 2;
					filein >> getline;
					interarrivo1 = atoi (getline.c_str());
				}
				cout << interarrivo << interarrivo1 << interarrivo2 << endl;
			}
			else if (!getline.compare("servicio"))
			{
				filein >> getline;
				if (getline.find("uniforme") == 0)
				{
					servicio = 1;
					filein >> getline;
					servicio1 = atoi (getline.c_str());
					filein >> getline;
					servicio2 = atoi (getline.c_str());
				}
				else if (getline.find("expotencial") == 0)
				{
					servicio = 2;
					filein >> getline;
					servicio1 = atoi (getline.c_str());
				}
				cout << servicio << servicio1 << servicio2 << endl;
			}
			else if (!getline.compare("RF"))
			{
				filein >> getline;
				if (getline.find("constante") == 0)
				{
					rp = 1;
					filein >> getline;
					rp1 = atoi (getline.c_str());
				}
				else if (getline.find("uniforme") == 0)
				{
					rp = 2;
					filein >> getline;
					rp1 = atoi (getline.c_str());
					filein >> getline;
					rp2 = atoi (getline.c_str());
				}				
				else if (getline.find("normal") == 0)
				{
					rp = 3;
					filein >> getline;
					rp1 = atoi (getline.c_str());
					filein >> getline;
					rp2 = atoi (getline.c_str());
				}
				else if (getline.find("expotencial") == 0)
				{
					rp = 4;
					filein >> getline;
					rp1 = atoi (getline.c_str());
				}
				cout << rp << rp1 << rp2 << endl;
			}
			else if (!getline.compare("RIO"))
			{
				filein >> getline;
				if (getline.find("constante") == 0)
				{
					rio = 1;
					filein >> getline;
					rio1 = atoi (getline.c_str());
				}
				else if (getline.find("uniforme") == 0)
				{
					rio = 2;
					filein >> getline;
					rio1 = atoi (getline.c_str());
					filein >> getline;
					rio2 = atoi (getline.c_str());
				}
				cout << rio << rio1 << rio2 << endl;
			}
		}
		filein.close();
		return true;
	};
};

int main(int argc, char **argv)
{
	bool makelog = false;
	char c;	
	string txtin, txtout = string("out.txt") , txtlog = string("log.txt");
	while ((c = getopt (argc, argv, "i:o:l:")) != -1)
	{
		switch (c)
		{
			case 'i':
				txtin = string(optarg);
				/*fstream filein("in.txt", ios::in);
				if (!filein.is_open())
				{
					cout << txtin << "no existe o no se peude cargar" << endl;
					return 1;
				}
				filein.close();*/
				break;
			case 'o':
				txtout = string(optarg);
				break;
			case 'l':
				txtlog = string(optarg);
				makelog = true;
				break;
			default:
				abort();
			}
	}

	Parametros leAsdf;
	if (leAsdf.lectura(txtin))
		cout << "it works!" << endl;
	else 
		cout << "it fails :(" << endl;


	return 0;
}