#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <random>
#include "generador.h"


using namespace std;

class evento
{
public:
	double tiempo;
	int id;
	
};

class proceso
{
public:
	double tiempo;
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

void funcion2(vector<evento> &lista, evento event){
	int posicion;
	if(lista.size()!=0){

		for (int i = 0; i < lista.size(); ++i)
		{
			if(lista.at(i).tiempo<event.tiempo){
				posicion=i;
			}
		}
		lista.insert(lista.begin()+posicion+1,event);
	}
	else{
		lista.push_back(event);


	}
}

void funcion3(vector<proceso> &lista, proceso proc){
	int posicion;
	if(lista.size()!=0){
		for (int i = 0; i < lista.size(); ++i)
		{
			if(lista.at(i).tiempo<proc.tiempo){
				posicion=i;
			}
		}
		lista.insert(lista.begin()+posicion+1,proc);
	}
	else{
		lista.push_back(proc);
	}

}

proceso funcion4(vector<proceso> &lista, int idAlgoritmo){
	proceso aux;
	int posicion;
	proceso com=lista.at(0);

	switch(idAlgoritmo)
	{
		case 1://fifo			
			aux=lista.at(0);
			lista.erase(lista.begin());
			break;

		case 2:
			posicion=0;
			for (int i = 0; i < lista.size(); ++i)
			{
				if(com.tiempo>lista.at(i).tiempo){
					com=lista.at(i);
					posicion=i;
				}
				
			}
			aux=lista.at(posicion);
			lista.erase(lista.begin()+posicion);
			break;

		case 3:
			aux=lista.at(0);
			lista.erase(lista.begin());
			break;
	}
	return aux;
}


int main(int argc, char **argv){
	bool makelog = false;
	char c;	
	string txtin, txtout = string("out.txt") , txtlog = string("log.txt");
	fstream filetest;
	while ((c = getopt (argc, argv, "i:o:l:")) != -1)
	{
		switch (c)
		{
			case 'i':				
				filetest.open(optarg, ios::in);
				if (!filetest.is_open())
				{
					cout << txtin << "no existe o no se puede cargar" << endl;
					return 1;
				}
				filetest.close();
				txtin = string(optarg);
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

	Generador param;
	param.cargarDatos(txtin, txtout);
	if (param.is_openIn)
		cout << "it works!" << endl;
	else 
		cout << "it fails :(" << endl;

	int a = param.numproc; //total de procesos


	//total de unidades de tiempo
	int tiempototal=0;
	//total de procesos terminados
	int procesot=0;
	//total de tiempo que el procesador pasa oceoso
	int oceo=0;

	int procesossalidos = 0;
	int procesoscreados = 0;
	//boolean para saber si la politica de scheduling es Round-Robin
	bool rr;
	if(param.algoritmo==3){
		rr=true;
	}
	else{
		rr=false;
	}


	//Variables globales que representan la simulacion
	vector<evento> eventos;
	vector<proceso> queue; //cola de procesos que esperan para entrar al procesador
	vector<proceso> io; //cola de procesos que esperan salir de I/O
	cpu procesador; // procesador
	procesador.estado = true; //parte el procesador como libre
	int contador = 1; // contador para darle un identificador a los procesos
	//Evento inter arribo

	//funcion2 que inserta el evento en la posicion que corresponde segun su tiempo
	//funcion 3 que inserta un proceso dentro de la cola I/O en el lugar que le corresponde
	//funcion 4 segun la politica de Scheuling entrega el siguiente proceso de la queue

	proceso proceinicial;
	procesoscreados++;
	proceinicial.id = contador;
	contador++;
	proceinicial.tiempo = param.Tservicio(tiempototal);

	if (rr){
		proceinicial.rr = param.algoritmo1;
	}
	procesador.estado = false;
	procesador.lista.push_back(proceinicial);
	
	evento inter;
	inter.tiempo = param.Interarrivo(tiempototal);
	inter.id = 1;
	funcion2(eventos,inter);

	evento rp;
	rp.tiempo = param.RP(tiempototal);
	rp.id = 2;

	funcion2(eventos,rp);

	//Bucle que expresa el funcionamiento del procesador
	while (procesot<a){
		if(eventos.empty()){
			break;
		}
		evento k = eventos.front();
		switch(k.id){
			//caso 1 el evento es un inter arribo
			case 1:{
				if (procesoscreados==a){
					eventos.erase(eventos.begin());
				}
				else{
					cout<< "Evento 1"<<endl;
					eventos.erase(eventos.begin());
					eventos = funcion1(k.tiempo,eventos);
					tiempototal = tiempototal+k.tiempo;

					proceso proce1;
					procesoscreados++;
					proce1.id = contador;
					contador++;
					proce1.tiempo = param.Tservicio(tiempototal);
					if (rr){
						proce1.rr = param.algoritmo1;
					}
					evento inter;
					inter.tiempo = param.Interarrivo(tiempototal);
					inter.id = 1;
					cout << "retardo"<<endl;
					funcion2(eventos,inter);
					param.escribirLog("inter", inter.tiempo, inter.id);
					if (procesador.estado){
						procesador.estado = false;
						procesador.lista.push_back(proce1);
						evento rp;
						rp.tiempo = param.RP(tiempototal);
						rp.id = 2;
						//contabilizamos la posibilidad que el proceso termine antes del tiempo que se le asigno
						if(rr){
							if(proce1.rr<rp.tiempo){
								if(proce1.tiempo<proce1.rr){
									evento salida;
									salida.tiempo = proce1.tiempo;
									salida.id=4;
									funcion2(eventos,salida);
									param.escribirLog("salida", salida.tiempo, salida.id);
								}
								else{
									evento vuelta;
									vuelta.tiempo = proce1.tiempo;
									vuelta.id=5;
									funcion2(eventos,vuelta);
									param.escribirLog("vuelta", vuelta.tiempo, vuelta.id);
								}
							}
							else{
								if(proce1.tiempo<rp.tiempo){
									evento salida;
									salida.tiempo = proce1.tiempo;
									salida.id=4;
									funcion2(eventos,salida);
									param.escribirLog("salida", salida.tiempo, salida.id);

								}
								else{
									funcion2(eventos,rp);
								}
							}
						}
						else{
							if(proce1.tiempo<rp.tiempo){
								evento salida;
								salida.tiempo = proce1.tiempo;
								salida.id=4;
								funcion2(eventos,salida);
								param.escribirLog("salida", salida.tiempo, salida.id);

							}
							else{
								funcion2(eventos,rp);
								param.escribirLog("rp", rp.tiempo, rp.id);
							}
						}
					}
					else{
						queue.push_back(proce1);
					}
				}
				break;
			}
			//caso 2 el evento es una salida de un proceso del procesador por que se le acabo el tiempo
			case 2:{
				cout<< "Evento 2"<<endl;
				eventos.erase(eventos.begin());
				eventos = funcion1(k.tiempo,eventos);
				tiempototal = tiempototal+k.tiempo;

				evento rio;
				//funcion que entrega el tiempo de IO
				rio.tiempo = param.RIO(tiempototal);
				rio.id=3;

				procesador.lista.front().iotime = rio.tiempo;
				procesador.lista.front().tiempo = procesador.lista.front().tiempo - k.tiempo;
				funcion3(io,procesador.lista.front());
				//vacio procesador y lo pongo disponible
				procesador.lista.erase(procesador.lista.begin());
				procesador.estado = true;
				cout << "retardo"<<endl;
				funcion2(eventos,rio);
				param.escribirLog("rio", rio.tiempo, rio.id);

				if (queue.empty()){
					oceo = oceo +eventos.front().tiempo;
				}

				else{
					proceso proce2 = funcion4(queue,param.algoritmo);
					procesador.estado = false;
					procesador.lista.push_back(proce2);

					evento rp;
					rp.tiempo = param.RP(tiempototal);
					rp.id = 2;
					if(rr){
						if(proce2.rr<rp.tiempo){
							if(proce2.tiempo<proce2.rr){
								evento salida;
								salida.tiempo = proce2.tiempo;
								salida.id=4;
								funcion2(eventos,salida);
								param.escribirLog("salida", salida.tiempo, salida.id);
							}
							else{
								evento vuelta;
								vuelta.tiempo = proce2.tiempo;
								vuelta.id=5;
								funcion2(eventos,vuelta);
								param.escribirLog("vuelta", vuelta.tiempo, vuelta.id);
							}
						}
						else{
							if(proce2.tiempo<rp.tiempo){
								evento salida;
								salida.tiempo = proce2.tiempo;
								salida.id=4;
								funcion2(eventos,salida);
								param.escribirLog("salida", salida.tiempo, salida.id);

							}
							else{
								funcion2(eventos,rp);
							}
						}
					}
					else{
						if(proce2.tiempo<rp.tiempo){
							evento salida;
							salida.tiempo = proce2.tiempo;
							salida.id=4;
							funcion2(eventos,salida);
							param.escribirLog("salida", salida.tiempo, salida.id);

						}
						else{
							funcion2(eventos,rp);
							param.escribirLog("rp", rp.tiempo, rp.id);
						}
					}
				}
				break;
			}
			//caso 3 el evento es una salida de un proceso de la cola de I/O
			case 3:{

				cout<< "Evento 3"<<endl;
				eventos.erase(eventos.begin());
				eventos = funcion1(k.tiempo,eventos);
				tiempototal = tiempototal+k.tiempo;

				queue.push_back(io.front());
				io.erase(io.begin());
				if(procesador.estado){
					proceso proce3 = funcion4(queue,param.algoritmo);
					procesador.estado = false;
					procesador.lista.push_back(proce3);
					evento rp;
					rp.tiempo = param.RP(tiempototal);
					rp.id = 2;
					funcion2(eventos,rp);
					param.escribirLog("rp", rp.tiempo, rp.id);
				}
				break;
			}
			//caso 4 el evento es una salida de un proceso del procesador debido a que termino	de ser procesado		
			case 4:{

				cout<< "Evento 4"<<endl;
				eventos.erase(eventos.begin());
				eventos = funcion1(k.tiempo,eventos);
				tiempototal = tiempototal+k.tiempo;
				
				//contabilizamos que termino un proceso
				procesot++;

				procesador.lista.erase(procesador.lista.begin());
				procesador.estado = true;
				procesossalidos++;

				if (queue.empty()){
					oceo = oceo +k.tiempo;
				}
				else{
					proceso proce4 = funcion4(queue,param.algoritmo);
					procesador.estado = false;
					procesador.lista.push_back(proce4);
					evento rp;
					rp.tiempo = param.RP(tiempototal);
					rp.id = 2;
					if(rr){
						if(proce4.rr<rp.tiempo){
							if(proce4.tiempo<proce4.rr){
								evento salida;
								salida.tiempo = proce4.tiempo;
								salida.id=4;
								funcion2(eventos,salida);
								param.escribirLog("salida", salida.tiempo, salida.id);
							}
							else{
								evento vuelta;
								vuelta.tiempo = proce4.tiempo;
								vuelta.id=5;
								funcion2(eventos,vuelta);
								param.escribirLog("vuelta", vuelta.tiempo, vuelta.id);
							}
						}
						else{
							if(proce4.tiempo<rp.tiempo){
								evento salida;
								salida.tiempo = proce4.tiempo;
								salida.id=4;
								funcion2(eventos,salida);
								param.escribirLog("salida", salida.tiempo, salida.id);

							}
							else{
								funcion2(eventos,rp);
							}
						}
					}
					else{
						if(proce4.tiempo<rp.tiempo){
							evento salida;
							salida.tiempo = proce4.tiempo;
							salida.id=4;
							funcion2(eventos,salida);
							param.escribirLog("salida", salida.tiempo, salida.id);

						}
						else{
							funcion2(eventos,rp);
							param.escribirLog("rp", rp.tiempo, rp.id);
						}
					}
				}

				break;
			}
			//caso 5 el evento es la salida de un proceso del procesador debido a que termino su momentum (RR)
			case 5:{
				cout<< "Evento 5"<<endl;
				eventos.erase(eventos.begin());
				eventos = funcion1(k.tiempo,eventos);
				tiempototal = tiempototal+k.tiempo;

				procesador.lista.front().tiempo  = procesador.lista.front().tiempo -procesador.lista.front().rr;
				queue.push_back(procesador.lista.front());

				procesador.lista.erase(procesador.lista.begin());

				proceso proce5 = funcion4(queue,param.algoritmo);

				procesador.lista.push_back(proce5);
				evento rp;
				rp.tiempo = param.RP(tiempototal);
				rp.id = 2;

				if(proce5.rr<rp.tiempo){
					if(proce5.tiempo<proce5.rr){
						evento salida;
						salida.tiempo = proce5.tiempo;
						salida.id=4;
						funcion2(eventos,salida);
						param.escribirLog("salida", salida.tiempo, salida.id);
					}
					else{
						evento vuelta;
						vuelta.tiempo = proce5.tiempo;
						vuelta.id=5;
						funcion2(eventos,vuelta);
						param.escribirLog("vuelta", vuelta.tiempo, vuelta.id);
					}
				}
				else{
					if(proce5.tiempo<rp.tiempo){
						evento salida;
						salida.tiempo = proce5.tiempo;
						salida.id=4;
						funcion2(eventos,salida);
						param.escribirLog("salida", salida.tiempo, salida.id);

					}
					else{
						funcion2(eventos,rp);
					}
				}
				break;
			}
		  	default:
    			cout << "Error";
		}

	}
	cout << procesoscreados <<endl;
	cout << procesot <<endl;
	
	
	return 0;
}

