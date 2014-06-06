#include <iostream>
#include <vector>
#include <string>


using namespace std;

class evento
{
public:
	int tiempo;
	int id;
	
};

class proceso
{
public:
	int tiempo;
	int id;
	
};

class cpu
{
public:
	bool estado;
	vector<proceso> lista;
	
};
int main(int argc, char **argv){
	int a = 10; //total de procesos
	int tiempo = 5; //tiempo total para acabar el proceso
	int rpt = 3; //tiempo dentro del procesador
	int riot = 2; //tiempo dentro de I/O
	int intert = 5; //tiempo inter arribo

	//Numero de procesos arribados
	int arribados = 0;
	//total de unidades de tiempo
	int tiempototal=0;
	//total de procesos terminados
	int procesot=0;

	//Variables globales que representan la simulacion
	vector<evento> eventos;
	vector<proceso> queue;
	vector<proceso> io;
	cpu procesador;
	procesador.estado = true;
	int contador = 1;
	//Evento inter arribo

	//funcion1 que resta el tiempo a los elementos de lista de eventos
	//funcion2 que inserta el evento en la posicion que corresponde segun su tiempo
	proceso proce;
	proce.id = contador;
	contador++;
	proce.tiempo = tiempo;
	
	if (procesador.estado){
		procesador.estado = false;
		procesador.lista.push_back(proce);
		evento rp;
		rp.tiempo = rpt;
		tiempototal = tiempototal+rpt;
		rp.id = 2;
		//ejecuto funcion1(rp)
		eventos.push_back(rp);
	}
	else{
		queue.push_back(proce);
	}
	//Bucle que expresa el funcionamiento del procesador
	while (procesot<a){
		evento k = eventos.front();
		switch(k.id){
			case 1:
				proceso proce;
				proce.id = contador;
				contador++;
				proce.tiempo = tiempo;
				if (procesador.estado){
					procesador.estado = false;
					procesador.lista.push_back(proce);
					evento rp;
					rp.tiempo = rpt;
					rp.id = 2;
					eventos.push_back(rp);
				}
				else{
					queue.push_back(proce);
				}
			case 2:
				//rp
				cout <<"relleno"<<endl;
			case 3:
				//rio
				cout <<"relleno"<<endl;
		}

	}
	return 0;
}

