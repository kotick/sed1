

#ifndef _PARAMETROS_H
#define _PARAMETROS_H


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
	bool is_openIn,
		 is_openOut,
		 is_openLog;
	fstream filein,
			fileout, 
			filelog;


	Parametros (){};
	~Parametros ()
	{
		fileout.close();
		filelog.close();
	};


	bool cargarDatos (string txtin, string txtout)
	{
		is_openIn = lectura(txtin);
		fileout.open(txtout.c_str(), ios::out);
		return true;
	};
	bool cargarDatos (string txtin, string txtout, string txtlog)
	{
		lectura (txtin);
		fileout.open(txtout.c_str(), ios::out);		
		filelog.open(txtlog.c_str(), ios::out);
		return true;
	};

	bool escribirOut (string salida)
	{
		filelog << salida << endl;
	};
	bool escribirLog (string tipo, int tiempo, int id)
	{
		filelog << tipo << ": Tiempo= " << tiempo << " ID= " << id << endl;
	};

	

	bool lectura (string txtin)
	{
		filein.open(txtin.c_str(), ios::in);
		if (!filein.is_open())
		{
			cout << txtin << " no existe o no se puede cargar" << endl;
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


#endif 