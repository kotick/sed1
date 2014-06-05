#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <vector>
#include <sys/time.h>
#include <time.h>
#include <string.h>


using namespace std;


/* -para indicar fin de la ejecución */
int quit=0;
/* -mutex para serializar el acceso a las otras variables globales */
pthread_mutex_t mymutex=PTHREAD_MUTEX_INITIALIZER;


class Configuracion
{
  public:
    float q1, 
        q2,
        tiempoPromedioIngresoNuevoProceso,
        desviacionEstandarIngresoNuevoProceso,
        
        tiempoPromedioProcesos_t1,
        desviacionEstandarTiempoProcesos_t1,
        tiempoMedioIO_t1,
        desviacionEstandarTiempoIO_t1,
        
        tiempoPromedioProcesos_t2,
        desviacionEstandarTiempoProcesos_t2,
        tiempoMedioIO_t2,
        desviacionEstandarTiempoIO_t2,
        
        out_Promedio_t1,
        out_Promedio_t2,
        out_Promedio_t,
        out_Desviacion_t1,
        out_Desviacion_t2,
        out_Desviacion_t,
        out_CPU,
        out_IO1,
        out_IO2;
        
    int porcentajeProcesosTipo1,
      tamColaDeProcesos,
      tamColaIO, 
      cantidadProcesos,
      out_Total;
    bool algoritmoDePlanificacion;    
    Configuracion()
    {
        FILE *txt = fopen ("in.txt", "r") ;
    if (txt == NULL) cout << "error" << endl;
    char *in, *nada;
    this->q1 = leerSigFloat (txt, in)*1000000.0;
    this->q2 = leerSigFloat (txt, in)*1000000.0;
    this->tamColaDeProcesos = leerSigInt (txt, in);
    this->tamColaIO = leerSigInt (txt, in);
    this->algoritmoDePlanificacion = leerSigBool (txt, in);
    this->cantidadProcesos = leerSigInt (txt, in);
    this->tiempoPromedioIngresoNuevoProceso = leerSigFloat (txt, in)*1000000.0;
    this->desviacionEstandarIngresoNuevoProceso = leerSigFloat (txt, in)*1000000.0;
    this->porcentajeProcesosTipo1 = leerSigInt (txt, in);
    nada = (char *)malloc(sizeof(char)*50);
    fscanf (txt, "%s", nada);
    free(nada);
    this->tiempoPromedioProcesos_t1 = leerSigFloat (txt, in)*1000000.0;
    this->desviacionEstandarTiempoProcesos_t1 = leerSigFloat (txt, in)*1000000.0;
    this->tiempoMedioIO_t1 = leerSigFloat (txt, in)*1000000.0;
    this->desviacionEstandarTiempoIO_t1 = leerSigFloat (txt, in)*1000000.0;
    nada = (char *)malloc(sizeof(char)*50);
    fscanf (txt, "%s", nada);
    free(nada);
    this->tiempoPromedioProcesos_t2 = leerSigFloat (txt, in)*1000000.0;
    this->desviacionEstandarTiempoProcesos_t2 = leerSigFloat (txt, in)*1000000.0;
    this->tiempoMedioIO_t2 = leerSigFloat (txt, in)*1000000.0;
    this->desviacionEstandarTiempoIO_t2 = leerSigFloat (txt, in)*1000000.0;

    fclose (txt);
    };   
    
    float aFloat (char * in)
  {
    char *comma = strstr(in, ",");
    if(comma!=NULL)
      comma[0]=46;
    float out = atof(in);
    free (in);
    return out;
  };

  float leerSigFloat (FILE *txt, char *in)
  {
    in = (char *)malloc(sizeof(char)*6);
    char *nada = (char *)malloc(sizeof(char)*50);
    fscanf (txt, "%s", nada);
    free(nada);
    fscanf (txt, "%s", in);
    return aFloat(in);
  };
  
  int leerSigInt (FILE *txt, char *in)
  {
    in = (char *)malloc(sizeof(char)*6);
    char *nada = (char *)malloc(sizeof(char)*50);
    fscanf (txt, "%s", nada);
    free(nada);
    fscanf (txt, "%s", in);
    return atoi(in);
  };
  
  bool leerSigBool (FILE *txt, char *in)
  {
    in = (char *)malloc(sizeof(char)*6);
    char *nada = (char *)malloc(sizeof(char)*50);
    fscanf (txt, "%s", nada);
    free(nada);
    fscanf (txt, "%s", in);
    if (!strncasecmp("FCFS", in, 4)) return false;
    if (!strncasecmp("SPN", in, 3)) return true;
  };
  
  void txtSalida()
  {
    FILE *f2 = fopen("salida.txt","w");
   
 
    fputs("Tiempo promedio de término de un proceso tipo 1 desde que entra: ",f2);
    fprintf(f2,"%.2f microseg.\n",this->out_Promedio_t1); 
    fputs("Tiempo promedio de término de un proceso tipo 2 desde que entra: ",f2);
    fprintf(f2,"%.2f microseg.\n",this->out_Promedio_t2);
    fputs("Tiempo promedio de término de un proceso desde que entra: ",f2);
    fprintf(f2,"%.2f microseg.\n",this->out_Promedio_t);
    fputs("Desviación estándar de término de un proceso tipo 1 desde que entra: ",f2);
    fprintf(f2,"%.2f microseg.\n",this->out_Desviacion_t1);
    fputs("Desviación estándar de término de un proceso tipo 2 desde que entra: ",f2);
    fprintf(f2,"%.2f microseg.\n",this->out_Desviacion_t2);
    fputs("Desviación estándar de término de un proceso desde que entra: ",f2);
    fprintf(f2,"%.2f microseg.\n",this->out_Desviacion_t);
    fputs("Tiempo total: ",f2);
    fprintf(f2,"%i seg.\n",this->out_Total);
    fputs("Tiempo de utilización del procesador: ",f2);
    fprintf(f2,"%.2f microseg.\n",this->out_CPU);
    fputs("Tiempo de utilización dl manejador de I/O 1: ",f2);
    fprintf(f2,"%.2f microseg.\n",this->out_IO1);
    fputs("Tiempo de utilización dl manejador de I/O 2: ",f2);
    fprintf(f2,"%.2f microseg.\n",this->out_IO2);
 
    fclose(f2);
  };
};

Configuracion data;

class Proceso
{
  public:
    float tiempoProcesos, 
          tiempoIO,
          tiempoVida;
    int nProceso,
      colaDestino,
      tipoProceso;
  
    Proceso(float tiempoProcesos, float tiempoIO, int nProceso, int tipoProceso)
    {
      this->tiempoProcesos = tiempoProcesos; 
      this->tiempoIO = tiempoIO;
      this->nProceso = nProceso;
      this->colaDestino = 1; //1: CPU - 2: IO
      this->tipoProceso = tipoProceso;
      this->tiempoVida = 0.0;
    };
  
};

vector<Proceso> colaProcesos;
vector<Proceso> colaIO;
vector<Proceso> colaEspera;

void *cpufunc(void *arg)
{
  int *id = (int *)arg;  
  vector<float> tiemposTipo1;
  vector<float> tiemposTipo2;
  vector<float> tiempoTipoCpu;
    while(true)
    {
      //usleep(rand()%10000);
    pthread_mutex_lock(&mymutex);
    if ( quit && colaProcesos.size() == 0 && colaIO.size() == 0 && colaEspera.size() == 0 )
    {
        float total1 = 0.0, total2 = 0.0, total_tiempo = 0.0, totalcpu = 0.0;
        float varianza_1=0,varianza_2=0,varianza_t=0,tamano1_size=tiemposTipo1.size(),tamano2_size=tiemposTipo2.size();
        for (int i=0; i<tiemposTipo1.size(); i++)
        total1 += tiemposTipo1[i];
        for (int i=0; i<tiemposTipo2.size(); i++)
        total2 += tiemposTipo2[i];
        for (int i=0; i<tiempoTipoCpu.size(); i++)
        totalcpu += tiempoTipoCpu[i]; 
     
          data.out_Promedio_t1 = (total1/((float)tiemposTipo1.size()));
        data.out_Promedio_t2 = (total2/((float)tiemposTipo2.size()));
        data.out_Promedio_t = ((total1+total2)/((float)(tiemposTipo1.size()+tiemposTipo2.size())));
        data.out_CPU = totalcpu;
         
        float promedio_1,promedio_2,promedio_t,diferencia_1=0,diferencia_2=0,diferencia_t=0,sumatoria_1=0,sumatoria_2=0,sumatoria_t=0;
        promedio_1=(total1/((float)tiemposTipo1.size()));
        promedio_2=(total2/((float)tiemposTipo2.size()));
        promedio_t=((total1+total2)/((float)(tiemposTipo1.size()+tiemposTipo2.size())));
     
        for (int i = 0; i < tiemposTipo1.size(); ++i)
        {
        diferencia_1=tiemposTipo1[i]-promedio_1;
        sumatoria_1=sumatoria_1+(diferencia_1*diferencia_1);
        }
        sumatoria_1=sumatoria_1/tamano1_size;
         
     
        for (int i = 0; i < tiemposTipo2.size(); ++i)
        {
        diferencia_2=tiemposTipo2[i]-promedio_2;
        sumatoria_2=sumatoria_2+(diferencia_2*diferencia_2);
        }
        sumatoria_2=sumatoria_2/tamano2_size;
         
        int numero_total=tiemposTipo2.size()+tiemposTipo1.size();
        for (int i = 0; i < numero_total; ++i)
        {
        diferencia_t=(tiemposTipo2[i]+tiemposTipo1[i])-promedio_t;
        sumatoria_t=sumatoria_t+(diferencia_t*diferencia_t);
        }
        sumatoria_t=sumatoria_t/(tamano1_size+tamano2_size);
        float desv_1,desv_2,desv_t;
        data.out_Desviacion_t1 = sqrt(sumatoria_1);
        data.out_Desviacion_t2 = sqrt(sumatoria_2);
        data.out_Desviacion_t = sqrt(sumatoria_t);    
            
      pthread_mutex_unlock(&mymutex);
      pthread_exit(NULL);
    }
    else
    {
      if(colaProcesos.size())
      { 
        Proceso temp = colaProcesos.back();
        colaProcesos.erase(colaProcesos.end()); 
        //pthread_mutex_unlock(&mymutex);
        
        float randval = (float) (rand()%100);
        float delta = data.q1 * randval * 0.01;
        if (0.0 > temp.tiempoProcesos - delta)
          delta = temp.tiempoProcesos;
        usleep((int) delta);  
        temp.tiempoVida += delta;
        temp.tiempoProcesos -= delta;
        
        tiempoTipoCpu.push_back(delta);
        
        //pthread_mutex_lock(&mymutex);
        if(temp.tiempoIO > 0.0)
          temp.colaDestino = 2;
        if(temp.tiempoProcesos > 0.0 || temp.tiempoIO > 0.0)
        {
          cout << temp.nProceso << "[" << temp.tipoProceso << "]: Proceso vida " << temp.tiempoVida << "(" << temp.tiempoProcesos << "/" << temp.tiempoIO << ")" << endl;
          colaEspera.insert(colaEspera.begin(), temp);
        }  
        else
        {
          if(temp.tipoProceso==1)
            tiemposTipo1.push_back(temp.tiempoVida);
          if(temp.tipoProceso==2)
            tiemposTipo2.push_back(temp.tiempoVida);
        }        
      }       
    }
    pthread_mutex_unlock(&mymutex);
  }
}

bool ioNum = false;

void *iofunc(void *arg)
{
  int id;
  pthread_mutex_lock(&mymutex);
  if (ioNum)
    id = 2; 
  else 
  {
    id = 1;
    ioNum = true;
  }
  pthread_mutex_unlock(&mymutex);
  
  vector<float> tiempoIO;
  
    while(true)
    {
      //usleep(rand()%10000);
    pthread_mutex_lock(&mymutex);
    if ( quit && colaProcesos.size() == 0 && colaIO.size() == 0 && colaEspera.size() == 0 )
    {  
      float totalio = 0.0;
      for (int i=0; i<tiempoIO.size(); i++)
        totalio += tiempoIO[i];
      
      if (id == 1) data.out_IO1 = totalio;
      else if (id == 2) data.out_IO2 = totalio;
      
      pthread_mutex_unlock(&mymutex);
      pthread_exit(NULL);
    }
    else
    {
      if(colaIO.size())
      { 
        Proceso temp = colaIO.back();
        colaIO.erase(colaIO.end());
        //pthread_mutex_unlock(&mymutex);
                
        float randval = (float) (rand()%100);
        float delta = data.q2 * randval * 0.01;
        if (0.0 > temp.tiempoIO - delta)
          delta = temp.tiempoIO;
        usleep((int) delta);  
        temp.tiempoVida += delta;
        temp.tiempoIO -= delta;
              
        tiempoIO.push_back(delta);
        
        temp.colaDestino = 1;
        
        //pthread_mutex_lock(&mymutex);
        colaEspera.insert(colaEspera.begin(), temp);
      }       
    }
    pthread_mutex_unlock(&mymutex);
  }
}


void *asignador(void *arg)
{
  int *id = (int *)arg;  
  /*vector<Proceso> colaProcesos;
  vector<Proceso> colaIO;
  vector<Proceso> colaEspera;*/
  //usleep(rand()%1000000);
  while(true)
  {
    pthread_mutex_lock(&mymutex);   
    if (colaEspera.size() != 0)
    {
      Proceso temp = colaEspera.back();
      colaEspera.erase(colaEspera.end()); 
      
      if (temp.colaDestino == 1)
      {
        if (data.algoritmoDePlanificacion)
        {
          int i=0;
          vector<Proceso>::iterator pos = colaProcesos.end();
          for (i=0; i<colaProcesos.size(); i++)
          {
            if (colaProcesos[i].tiempoProcesos < temp.tiempoProcesos)
            {
              pos = colaProcesos.begin()+i;
              break;
            }
          }
          colaProcesos.insert(pos, temp);
        } 
        else
          colaProcesos.insert(colaProcesos.begin(), temp);
      }
      
      else if (temp.colaDestino == 2)
        colaIO.insert(colaIO.begin(), temp);
    }
      /*FAlSE = FCFS
        TRUE = SPN*/
    
    else if ( quit && colaProcesos.size() == 0 && colaIO.size() == 0)
    {
      pthread_mutex_unlock(&mymutex);
      pthread_exit(NULL);
    }
    pthread_mutex_unlock(&mymutex);         
  }
}


class Hebra
{
  public:
    pthread_t asignadorHebra;
    pthread_t cpufuncHebra;
    pthread_t iofuncHebra1;
    pthread_t iofuncHebra2;
    
  
    Hebra()
    {
    int id0=0, id1=1, id2=2, id3=3;
    if (pthread_create(&asignadorHebra, NULL, asignador, (void *)&id0))
    {
      perror("Thread create:");
      exit(1);
    }
    if (pthread_create(&cpufuncHebra, NULL, cpufunc, (void *)&id1))
    {
      perror("Thread create:");
      exit(1);
    }
    if (pthread_create(&iofuncHebra1, NULL, iofunc, (void *)&id2))
    {
      perror("Thread create:");
      exit(1);
    }
    if (pthread_create(&iofuncHebra2, NULL, iofunc, (void *)&id3))
    {
      perror("Thread create:");
      exit(1);
    }
    };
  
  
void productor ()
{
  for (int i=0; i< data.cantidadProcesos; i++)
  { 
      pthread_mutex_lock(&mymutex);
      if ((data.tamColaDeProcesos/2) <  colaProcesos.size())
        {
          i--;
          pthread_mutex_unlock(&mymutex);
          continue;
        }
      /* seccion critica */
      colaEspera.insert(colaEspera.begin(), elaborar(i));
      pthread_mutex_unlock(&mymutex);
    }
    pthread_mutex_lock(&mymutex);
    quit=1;
    pthread_mutex_unlock(&mymutex);
    pthread_join(asignadorHebra, NULL);
    pthread_join(cpufuncHebra, NULL);
    pthread_join(iofuncHebra1, NULL);
    pthread_join(iofuncHebra2, NULL);
};  
  
  Proceso elaborar (int nProceso)
  {
    float tiempoProcesos, tiempoIO, randval = (float) (rand()%100);
    float variacion = randval * 0.01 * pow(-1.0, rand()%2);
    int tipoProceso;
    if ((rand()%100) < data.porcentajeProcesosTipo1)//Tipo 1
    {
      tiempoProcesos = data.tiempoPromedioProcesos_t1 + (data.desviacionEstandarTiempoProcesos_t1 * variacion);
      tiempoIO = data.tiempoMedioIO_t1 + (data.desviacionEstandarTiempoIO_t1 * variacion);
      tipoProceso = 1;
    }
    else//Tipo 2
    {
      tiempoProcesos = data.tiempoPromedioProcesos_t2 + (data.desviacionEstandarTiempoProcesos_t2 * variacion);
      tiempoIO = data.tiempoMedioIO_t2 + (data.desviacionEstandarTiempoIO_t2 * variacion);
      tipoProceso = 2;
    }
    Proceso nuevo (tiempoProcesos, tiempoIO, nProceso, tipoProceso);
    return nuevo;
  };
  
};




int main(int argc, char const *argv[])
{ 
	int main (int argc, char **argv)
{
  int aflag = 0;
  //Puntero de nombres de ficheros
  char *txto = "b bbstatistics.raw" , *txt1 = NULL, *txt2 = NULL, c;
  int i;
  while ((c = getopt (argc, argv, "ai:o:")) != -1)
      switch (c)
      {
	//En caso de necesitar muestra avanzada
        case 'a':
          aflag = 1;
          break;
	//Entrada txt. Si no empieza con corchete se despreciala entrada
        case 'i':
          if (optarg[0] != '[') 
          {
            fprintf(fopen(txto, "w"), "Error parametros de entrada en -i\n");
            return 1;
          }
          txt1 = strtok ((optarg + sizeof(char)), "_");
          txt2 = strtok (NULL, "_]");
          break;
	//Evitar que por error se ingrese una bandera. 
        case 'o':
          if (optarg[0] == '-') 
          {
            fprintf(fopen(txto, "w"), "Error parametros de entrada en -o\n");
            return 1;
          }
          txto=optarg;
          break;
        case '?':          
	//Errores varios
          if (optopt == 'i' || optopt == 'o') fprintf (fopen(txto, "w"), "Opcion -%c requiere un argumento.\n", optopt);
          else if (isprint (optopt)) fprintf (fopen(txto, "w"), "Opcion desconocida `-%c'.\n", optopt);
          else fprintf (fopen(txto, "w"), "Caracter desconocido `\\x%x'.\n", optopt);
          return 1;
        default:
            abort ();
      }    
	
  srand(time(NULL));
  time_t tInicio, tFinal;
  time(&tInicio);
    Hebra procesador;
    procesador.productor(); 
    time(&tFinal);
    data.out_Total = difftime(tFinal, tInicio); 
    data.txtSalida();
  return 0;
}



