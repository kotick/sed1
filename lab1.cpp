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
	int iotime;
	
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
	//total de tiempo que el procesador pasa oceoso
	int oceo=0;

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
	//funcion 3 que inserta un proceso dentro de la cola I/O en el lugar que le corresponde
	//funcion 4 segun la politica de Scheuling entrega el siguiente proceso de la queue
	proceso proce;
	proce.id = contador;
	contador++;
	proce.tiempo = tiempo;
	
	procesador.estado = false;
	procesador.lista.push_back(proce);
	
	evento inter;
	//funcion que da el tiempo aleatorio del inter arribo
	inter.tiempo = intert;
	inter.id = 1;
	//ejecuto funcion2(inter)
	eventos.push_back(inter);

	evento rp;
	//funcion que da el tiempo aleatorio del RP
	rp.tiempo = rpt;
	rp.id = 2;
	//ejecuto funcion2(rp)
	eventos.push_back(rp);


	//Bucle que expresa el funcionamiento del procesador
	while (procesot<a){
		evento k = eventos.front();
		switch(k.id){
			case 1:
				//ejecuto funcion1(k.tiempo)
				tiempototal = tiempototal+k.tiempo;
				eventos.erase(eventos.begin());

				proceso proce;
				proce.id = contador;
				contador++;
				proce.tiempo = tiempo;
				
				evento inter;
				//funcion que da el tiempo aleatorio del inter arribo
				inter.tiempo = intert;
				inter.id = 1;			
				//ejecuto funcion2(inter)
				eventos.push_back(inter);

				if (procesador.estado){
					procesador.estado = false;
					procesador.lista.push_back(proce);
					evento rp;
					rp.tiempo = rpt;
					rp.id = 2;
					//ejecuto funcion2(rp)
					eventos.push_back(rp);
				}
				else{
					queue.push_back(proce);
				}
				break;
			case 2:
				//ejecuto funcion1(k.tiempo)
				tiempototal = tiempototal+k.tiempo;

				evento rio;
				//funcion que entrega el tiempo de IO
				rio.tiempo = riot;
				rio.id=3;

				procesador.lista.front().iotime = rio.tiempo;
				procesador.lista.front().tiempo = procesador.lista.front().tiempo - k.tiempo;
				//ejecuto funcion3(procesador.lista.front())

				//vacio procesador y lo pongo disponible
				procesador.lista.erase(procesador.lista.begin());
				procesador.estado = true;


				
				eventos.erase(eventos.begin());
				//ejecuto funcion2(rio)
				eventos.push_back(rio);			

				if (queue.empty()){
					oceo = oceo +eventos.front().tiempo;
				}
				else{
					//funcion4
					proce = queue.front();
					procesador.estado = false;
					procesador.lista.push_back(proce);
					evento rp;
					rp.tiempo = rpt;
					rp.id = 2;
					//ejecuto funcion2(rp)
					eventos.push_back(rp);
					queue.erase(queue.begin());
				}
				break;

			case 3:
				//ejecuto funcion1(k.tiempo)
				tiempototal = tiempototal+k.tiempo;
				queue.push_back(io.front());
				io.erase(io.begin());
				if(procesador.estado){
					//funcion4
					proce = queue.front();
					procesador.estado = false;
					procesador.lista.push_back(proce);
					evento rp;
					rp.tiempo = rpt;
					rp.id = 2;
					//ejecuto funcion2(rp)
					eventos.push_back(rp);
					queue.erase(queue.begin());
				}

				break;

		  default:
    			cout << "value of x unknown";
		}

	}
	return 0;
}

