#include <stdio.h>
#include <math.h>
#include <sys/time.h>

//calcular valor de Y en el circulo de radio 1
double fuction(double x){
	return sqrt(1 - x * x);
}

//Corrige el calculo del Area
double calcularArea(double a, double b, int n){
	double h = (b - a) / n;
	double area = (fuction(a) + fuction(b)) / 2.0;
	
	for(int i = 1; i < n; i++){
		double x = a + i * h;
		area += fuction(x);
	}
	return area * h;
}


int main(){
	struct timeval inicio, fin;
	double a = 0; //Limite inferior
	double b = 1; //Limite superior
	int n = 1000000; //Num subintervalos

	gettimeofday(&inicio, NULL); //Tiempo inicial
	
	double area = calcularArea(a, b, n);
	double pi = 4 * area; //PI
	gettimeofday(&fin, NULL); //Tiempo final

	//Tiempo a segundos
	double tiempo_transcurrido = (fin.tv_sec - inicio.tv_sec) + (fin.tv_usec - inicio.tv_usec) / 1000000.0;
	
	printf("El valor estimado de PI es: %f\n", pi);
	printf("Tiempo transcurrido: %f segundos\n", tiempo_transcurrido);

	return 0;
}
