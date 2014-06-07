
#include <iostream>
#include <random>
#include <math.h>




#ifndef _GENERADOR_H
#define _GENERADOR_H

using namespace std;

class Generador
{	//parametros

public:
	//tu llamas a estas cosas para que te de el tiempo
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


	Generador (){};
	~Generador ()
	{
		fileout.close();
		filelog.close();
	};


	bool cargarDatos (string txtin, string txtout)
	{
		is_openIn = lectura(txtin);
		fileout.open(txtout.c_str(), ios::out);
		if (fileout.is_open())
			is_openOut = true;
		return true;
	};
	bool cargarDatos (string txtin, string txtout, string txtlog)
	{
		is_openIn = lectura (txtin);
		fileout.open(txtout.c_str(), ios::out);		
		if (fileout.is_open())
			is_openOut = true;
		filelog.open(txtlog.c_str(), ios::out);
		if (filelog.is_open())
			is_openLog = true;
		return true;
	};

	bool escribirOut (string salida)
	{
		filelog << salida << endl;
		return true;
	};
	bool escribirLog (string tipo, int tiempo, int id)
	{
		filelog << tipo << ": Tiempo= " << tiempo << " ID= " << id << endl;
		return true;
	};





	double Interarrivo(double tiempo){
		double delta;
		switch(interarrivo){//se supone que lo conozco, maldita
			case 2: //uniforme
				delta=Uniforme(interarrivo1,interarrivo2,tiempo);
				break;

			case 4://exponencial
				delta=Exponencial(interarrivo1,tiempo);
				break;

		}

		return delta;
	};


	double Tservicio(double tiempo){
		cout << "tipo servicio " << servicio <<endl;
		double delta;
		switch(servicio){
			case 2://uniforme
				delta=Uniforme(servicio1,servicio2,tiempo);
				break;
			case 4://exponencial
				delta=Exponencial(servicio1,tiempo);
				break;

		}
		return delta;
	};


	double RP(double tiempo){
		double delta;
		switch(rp){
			case 1://constante
				delta=rp1;
				break;

			case 2:
				delta=Uniforme(rp1,rp2,tiempo);
				break;

			case 3:
				delta=Normal(rp1,rp2,tiempo);
				break;

			case 4:
				delta=Exponencial(rp1,tiempo);
				break;
		}
		return delta;

	};
	double RIO(double tiempo){
		double delta;
		switch(rio){
			case 1:
				delta=rio1;
				break;

			case 2:
				delta=Uniforme(rio1,rio2,tiempo);
				break;

		}
		return delta;
	};



private:
	double Exponencial(int lambda, double tiempo){
		cout <<"esto Exponencial: ";
		default_random_engine generator;
		exponential_distribution<double> distribution(lambda);
		generator.seed(tiempo);
		double tux=distribution(generator);
		return tux;
	};

	double Uniforme(int a,int b,double tiempo){//t es el tiempo de eecucion c:
		cout <<"esto Exponencial: ";
		default_random_engine generator;
		uniform_int_distribution<int> distribution(a,b);
		generator.seed(tiempo);
		double tux = distribution(generator);

		//double numerador=pow(M_E,tiempo*b)-pow(M_E,tiempo*a);
		//double denominador=tiempo*(b-a);
		//ouble tux=(numerador/denominador);
		return tux;
	
	};

	// http://www.cplusplus.com/reference/random/normal_distribution/
	double Normal(int mu,int desv1,double tiempo){
		cout <<"esto Normal: ";
		double desv =sqrt(desv1);
		std::default_random_engine generator;
  		std::normal_distribution<double> distribution(mu,desv);
		generator.seed(tiempo);
		//double primerTermino=mu*sqrt(2*M_PI);
		//double primero=pow(primerTermino,-1);//va
		//double num1= pow(tiempo-mu,2);
		//double den1=2*pow(mu,2);
		//double elevado=-1*num1/den1;//va
		//double tux=primero*pow(M_E,elevado);
		double tux = distribution(generator);
		return tux;
	};

//hasta acá hice yo, Valeria  c:

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
				if (getline.compare("FCFS") == 0)
					algoritmo = 1;
				else if (getline.compare("SJF") == 0)
					algoritmo = 2;
				else if (getline.compare("RR") == 0)
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
				if (getline.compare("uniforme") == 0)
				{
					interarrivo = 1;
					filein >> getline;
					interarrivo1 = atoi (getline.c_str());
					filein >> getline;
					interarrivo2 = atoi (getline.c_str());
				}
				else if (getline.compare("expotencial") == 0)
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
				if (getline.compare("uniforme") == 0)
				{
					servicio = 1;
					filein >> getline;
					servicio1 = atoi (getline.c_str());
					filein >> getline;
					servicio2 = atoi (getline.c_str());
				}
				else if (getline.compare("expotencial") == 0)
				{
					servicio = 2;
					filein >> getline;
					servicio1 = atoi (getline.c_str());
				}
				cout << servicio << servicio1 << servicio2 << endl;
			}
			else if (!getline.compare("RP"))
			{
				filein >> getline;
				if (getline.compare("constante") == 0)
				{
					rp = 1;
					filein >> getline;
					rp1 = atoi (getline.c_str());
				}
				else if (getline.compare("uniforme") == 0)
				{
					rp = 2;
					filein >> getline;
					rp1 = atoi (getline.c_str());
					filein >> getline;
					rp2 = atoi (getline.c_str());
				}				
				else if (getline.compare("normal") == 0)
				{
					rp = 3;
					filein >> getline;
					rp1 = atoi (getline.c_str());
					filein >> getline;
					rp2 = atoi (getline.c_str());
				}
				else if (getline.compare("expotencial") == 0)
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
				if (getline.compare("constante") == 0)
				{
					rio = 1;
					filein >> getline;
					rio1 = atoi (getline.c_str());
				}
				else if (getline.compare("uniforme") == 0)
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