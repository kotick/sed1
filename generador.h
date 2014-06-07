#include "parametros.h"
#ifndef _GENERADOR_H
#define _GENERADOR_H

class Generador : Parametros
{	//parametros

public:
	//tu llamas a estas cosas para que te de el tiempo

	double Interarrivo(tiempo){
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
	}


	double Tservicio(tiempo){
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
	}


	double RP(tiempo){
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

	}
	double RIO(tiempo){
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
	}



private:
	double Exponencial(lambda,tiempo){
		u=Uniforme(0,1,tiempo);
		double tiempo=(-1/lambda)*u;
		return tiempo;
	}

	double Uniforme(a,b,tiempo){//t es el tiempo de eecucion c:
		double numerador=pow(M_E,t*b)-pow(M_E,t*a);
		double denominador=t*(b-a);
		double tiempo=(numerador/denominador);
		return tiempo;
	
	}

	// http://www.cplusplus.com/reference/random/normal_distribution/
	double Normal(mu,desv,tiempo){
		double primerTermino=mu*sqrt(2*M_PI);
		double primero=pow(primerTermino,-1);//va
		double num1= pow(t-mu,2);
		double den1=2*pow(mu,2);
		double elevado=-1*num1/den1;//va
		double tiempo=primero*pow(M_E,elevado);
		return tiempo;
	}
};
//hasta acá hice yo, Valeria  c:

#endif