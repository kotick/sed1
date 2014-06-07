#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <stdio.h>     
#include <math.h> 


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
	int rr;
	
};

class cpu
{
public:
	bool estado;
	vector<proceso> lista;
	
};
vector<evento> funcion1(int valor,vector<evento> lista){
	int n = 0;
	while(n < lista.size()){
		lista.at(n).tiempo = lista.at(n).tiempo - valor;
		if (lista.at(n).tiempo < 0) lista.at(n).tiempo=0;
		n++;
	}
	return lista;
};

void funcion2(vector<evento> &lista, evento n){
	int posicion;
	if(lista.size()!=0){
		for (int i = 0; i < lista.size(); ++i){
			if(lista.at(i).tiempo<n.tiempo){
				posicion=i;
			}
		}
		lista.insert(lista.begin()+posicion+1,n);
	}
	else{
		lista.push_back(n);
	}
}

void funcion3(vector<proceso> &lista, proceso n){
	int posicion;
	if(lista.size()!=0){
		for (int i = 0; i < lista.size(); ++i)
		{
			if(lista.at(i).tiempo<n.tiempo){
				posicion=i;
			}
		}
		lista.insert(lista.begin()+posicion+1,n);
	}
	else{
		lista.push_back(n);
	}

}



int main(int argc, char **argv){

	///////Reemplazar estas variables con las obtenidas del archivo de entrada
	int a = 10; //total de procesos
	int tiempo = 5; //tiempo total para acabar el proceso
	int rpt = 3; //tiempo dentro del procesador
	int riot = 2; //tiempo dentro de I/O
	int intert = 5; //tiempo inter arribo
	////// Hasta acá
	//Boolean para saber si la politica de scheduling es Round-Robin
	bool rr;


	//Total de unidades de tiempo
	int tiempototal=0;
	//Total de procesos terminados
	int procesot=0;
	//Total de tiempo que el procesador pasa oceoso
	int oceo=0;


	//Variables globales que representan la simulacion
	vector<evento> eventos;// cola de eventos
	vector<proceso> queue; //cola de procesos que esperan para entrar al procesador
	vector<proceso> io; //cola de procesos que esperan salir de I/O
	
	cpu procesador; // procesador
	procesador.estado = true; //parte el procesador como libre
	int contador = 1; // contador para darle un identificador a los procesos
	//Evento inter arribo

	//funcion2 que inserta el evento en la posicion que corresponde segun su tiempo
	//funcion 3 que inserta un proceso dentro de la cola I/O en el lugar que le corresponde,tiempo
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
	funcion2(eventos,inter);

	evento rp;
	//funcion que da el tiempo aleatorio del RP
	rp.tiempo = rpt;
	rp.id = 2;
	funcion2(eventos,rp);


	//Bucle que expresa el funcionamiento del procesador
	while (procesot<a){
		evento k = eventos.front();
		switch(k.id){
			//caso 1 el evento es un inter arribo
			case 1:
				eventos = funcion1(k.tiempo,eventos);
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
				funcion2(eventos,inter);
				if (procesador.estado){
					
					procesador.estado = false;
					procesador.lista.push_back(proce);
					evento rp;
					//funcion que fija el tiempo de rp
					rp.tiempo = rpt;
					rp.id = 2;
					//contabilizamos la posibilidad que el proceso termine antes del tiempo que se le asigno
					if(rr && proce.rr<rp.tiempo ){
						evento vuelta;
						vuelta.tiempo = proce.tiempo;
						vuelta.id=5;
						funcion2(eventos,vuelta);
					}
					else{
						if(proce.tiempo<rp.tiempo){
							evento salida;
							salida.tiempo = proce.tiempo;
							salida.id=4;
							funcion2(eventos,salida);
						}
						else{
							funcion2(eventos,rp);
						}
					}
				}
				else{
					queue.push_back(proce);
				}
				break;
			//caso 2 el evento es una salida de un proceso del procesador por que se le acabo el tiempo
			case 2:

				eventos = funcion1(k.tiempo,eventos);
				tiempototal = tiempototal+k.tiempo;

				evento rio;
				//funcion que entrega el tiempo de IO
				rio.tiempo = riot;
				rio.id=3;

				procesador.lista.front().iotime = rio.tiempo;
				procesador.lista.front().tiempo = procesador.lista.front().tiempo - k.tiempo;
				funcion3(io,procesador.lista.front());

				//vacio procesador y lo pongo disponible
				procesador.lista.erase(procesador.lista.begin());
				procesador.estado = true;
				
				eventos.erase(eventos.begin());
				funcion2(eventos,rio);		

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

					if(rr && proce.rr<rp.tiempo ){
						evento vuelta;
						vuelta.tiempo = proce.tiempo;
						vuelta.id=5;
						funcion2(eventos,vuelta);
					}
					else{
						if(proce.tiempo<rp.tiempo){
							evento salida;
							salida.tiempo = proce.tiempo;
							salida.id=4;
							funcion2(eventos,salida);
						}
						else{
							funcion2(eventos,rp);
						}
					}
					queue.erase(queue.begin());
				}
				break;
			//caso 3 el evento es una salida de un proceso de la cola de I/O
			case 3:
				eventos = funcion1(k.tiempo,eventos);
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
					funcion2(eventos,rp);
					queue.erase(queue.begin());
				}
				break;

			//caso 4 el evento es una salida de un proceso del procesador debido a que termino	de ser procesado		
			case 4:
				eventos = funcion1(k.tiempo,eventos);
				tiempototal = tiempototal+k.tiempo;
				eventos.erase(eventos.begin());
				//contabilizamos que termino un proceso
				procesot++;

				procesador.lista.erase(procesador.lista.begin());
				procesador.estado = true;
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

					if(rr && proce.rr<rp.tiempo ){
						evento vuelta;
						vuelta.tiempo = proce.tiempo;
						vuelta.id=5;
						funcion2(eventos,vuelta);
					}
					else{
						if(proce.tiempo<rp.tiempo){
							evento salida;
							salida.tiempo = proce.tiempo;
							salida.id=4;
							funcion2(eventos,salida);
						}
						else{
							funcion2(eventos,rp);
						}
					}
					queue.erase(queue.begin());
				}
			//caso 5 el evento es la salida de un proceso del procesador debido a que termino su momentum (RR)
			case 5:
				eventos = funcion1(k.tiempo,eventos);
				tiempototal = tiempototal+k.tiempo;
				eventos.erase(eventos.begin());

				procesador.lista.front().tiempo  = procesador.lista.front().tiempo -procesador.lista.front().rr;
				queue.push_back(procesador.lista.front());

				procesador.lista.erase(procesador.lista.begin());
				procesador.estado = true;


				//funcion4
				proce = queue.front();
				procesador.estado = false;
				procesador.lista.push_back(proce);
				evento rp;
				rp.tiempo = rpt;
				rp.id = 2;

				if(rr && proce.rr<rp.tiempo ){
					evento vuelta;
					vuelta.tiempo = proce.tiempo;
					vuelta.id=5;
					funcion2(eventos,vuelta);
				}
				else{
					if(proce.tiempo<rp.tiempo){
						evento salida;
						salida.tiempo = proce.tiempo;
						salida.id=4;
						funcion2(eventos,salida);
					}
					else{
						funcion2(eventos,rp);
					}
				}
				queue.erase(queue.begin());

		  	default:
    			cout << "Error";
		}

	}
	return 0;
}

