#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define LP 1000000;


double p_od, p_do;

double funk1(double x){
	return sin(x);
}

double funk2(double x){
	return cos(x);
}

double funk3(double x){
	return x*x-2*x+4;
}

double funk4(double x){
	return x*x*x-5;
}

double prostokat(double (*funk)(double)){
	double dx, n, suma=0;	
	dx = (p_do - p_od) / LP;
	for (n = p_od; n<p_do; n+=dx)
		suma += funk(n)*dx;
		return suma;
	
}

double trapez(double(*funk)(double)){
	double dx, n, suma;
	dx = (p_do - p_od) / LP;
	suma = 0.5*dx*(funk(p_od) + funk(p_do));
	for (n = p_od+dx; n<p_do; n += dx)
		suma += funk(n)*dx;
	return suma;
	}



double generuj(double a, double b) {
	return a + (double)rand() / (double)(RAND_MAX + 1) * (b - a);
}

double monte_carlo(double(*funk)(double)){
	double dx, krok, N = 100000000, Nt = 0, x, y;
	dx = p_do - p_od;
	krok = dx / LP;

	double MAX = 0, MIN = 0;

	for (double x = p_od; x <= p_do; x += krok){
		if (funk(x) >= MAX)
			MAX = funk(x);
		if (funk(x) <= MIN)
			MIN = funk(x);
	}

		srand((unsigned)time(NULL));
	for (int i = 1; i <= N; i++){
		
		x = generuj(p_od, p_do);
		y = generuj(MIN, MAX);
		if ((funk(x) > 0) && (funk(x) > y) && (y>0)) Nt++;
		if ((funk(x) < 0) && (funk(x) < y) && (y<0)) Nt--;

	}
 	 return (Nt/N)*dx*(MAX-MIN);
	 
}




void main(){
	do{
		printf("Podaj przedzial 1: ");
		scanf("%lf", &p_od);
		printf("Podaj przedzial 2: ");
		scanf("%lf", &p_do);
		if (p_do > p_od) break;
		printf("Przedzial 2 musi byc wiekszy od przedzialu 1!!! Sprobuj ponownie\n");
	} while (1);
	printf("\t\tsin(x)\t\tcos(x)\t\tx^2-2*x+4\tx^3-4\n\n");
	printf("Prostokaty\t%lf\t%lf\t%lf\t%lf\n", prostokat(*funk1), prostokat(*funk2), prostokat(*funk3), prostokat(*funk4));
	printf("Trapezy\t\t%lf\t%lf\t%lf\t%lf\n", trapez(*funk1), trapez(*funk2), trapez(*funk3), trapez(*funk4));
	printf("Monte Carlo\t%lf\t%lf\t%lf\t%lf\n", monte_carlo(*funk1), monte_carlo(*funk2), monte_carlo(*funk3), monte_carlo(*funk4));
	system("pause");	
	
} 