#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>

#define NUM_THREADS 4 //Hilos

//Estructura para almacenar datos para el calculo de cada hilo.
typedef struct{
	double a, b;		//Limite inferior y superior.
	int n;			//Numero de subintervalos para hilos.
	double resultado;	//Resultado del calculo.
} thread_data;

//Semicircunferencia superor del circulo
double funcion(double x){
	return sqrt(1 - x * x);
}

//Funcion para cada hilo para calcular su parte del area.
void* calcularArea(void* arg){ 
	thread_data* data = (thread_data*)arg; 
	double h = (data->b - data->a) / data->n;
	double area = (funcion(data->a) + funcion(data->b)) / 2.0;

	//Suma las areas de los subintervalos intermedios.
	for(int i = 1; i < data->n; i++){
		double x = data->a + i * h;
		area += funcion(x);
	}

	data->resultado = area * h; //Calcular el area total para este hilo y lo guarda.
	pthread_exit(NULL);
}

int main(){
	pthread_t threads[NUM_THREADS]; //Array para almacenar identificadores.
	thread_data data[NUM_THREADS];	//Array oara almacenar datos.
	struct timeval inicio, fin;	//Medir tiempo de ejecucion.

	double a = 0; //Limite inferior.
	double b = 1; //Limite superior.
	int n = 1000000; //Numero total de subintervalos.

	gettimeofday(&inicio, NULL);

	//Creacion y ejecucion
	for(int i = 0; i < NUM_THREADS; i++){
		data[i].a = a + i * (b - a) / NUM_THREADS;
		data[i].b = a + (i + 1) * (b - a) / NUM_THREADS;
		data[i].n = n / NUM_THREADS;
		pthread_create(&threads[i], NULL, calcularArea, (void*)&data[i]);
	}

	//Variable para acumular el area total calculada por todos los hilos.
	double area_total = 0;
	
	//Se espera a que terminen y guarda resultados.
	for(int i = 0; i < NUM_THREADS; i++){
		pthread_join(threads[i], NULL);
		area_total += data[i].resultado;
	}

	//Calcula PI y Marca tiempo de ejecucion.
	double pi = 4 * area_total;
	gettimeofday(&fin, NULL);

	double tiempo_transcurrido = (fin.tv_sec - inicio.tv_sec) + (fin.tv_usec - inicio.tv_usec) / 1000000.0;

	printf("El valor estimado de PI es: %f\n", pi);
	printf("Tiempo transcurrido: %f segundos\n", tiempo_transcurrido);

	return 0;
}
