#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//variaveis globais
int npassos=0;
double precisao=1e-5;
double precmax=1e-9; //Define o valor máximo para a precisão
const float moduloforca=9.81; //Como o objeto tem m=1kg -> f=ma=1g

double f1( double x );
double df1( double x );

double Bissecao(double (*f)(double), double precisao);
double NewtonRaphson(double (*f)(double), double (*df)(double), double precisao);
    

/*----------------------------------------------------------------------------*/
int main()
{
  FILE *graph=NULL; 
  graph=fopen("graph.dat" , "wt"); //Cria arquivo do gráfico
  fprintf(graph, "\"Bisseção\"\n");
  while(precisao>=precmax){ //Gera um loop para escrever numero de iterações e log10 da precisão no arquivo do gráfico
  	Bissecao(f1, precisao);
  	fprintf(graph, "%.0lf %d\n", log10(precisao), npassos); 
  	precisao = precisao/10; //Diminui o valor da precisão a fim de alcançar a precisão máxima.
  }
  fprintf(graph, "\n\n\"Newton-Raphson\"\n");
  precisao=1e-5;
  while(precisao>=precmax){
  	NewtonRaphson(f1, df1, precisao);
  	fprintf(graph, "%.0lf %d\n", log10(precisao), npassos);
  	precisao = precisao/10; //Diminui o valor da precisão a fim de alcançar a precisão máxima.
  }
  fclose (graph);
  system("gnuplot -p -e \"load 'tarefa2g.gpl'\"");
  return 1;
}
/*----------------------------------------------------------------------------*/
double f1 ( double x ) {
  return exp(x)*x - moduloforca;
} 
/*----------------------------------------------------------------------------*/
double df1 ( double x ) {
  return exp(x)+x*exp(x);
}


/*----------------------------------------------------------------------------*/
double Bissecao(double (*f)(double), double precisao) {
 
  double x_min=1, x_max=2;
  printf ("*** Bissecao **** \n\n");
  printf ("Entre com os valores inferior e superior do intervalo:\n ");

  while ( (f(x_min)*f(x_max)) > 0 ) {
    printf ("O intervalo dado nao contem nenhuma raiz.\n");
    printf ("Entre com novos valores: ");
    scanf ("%lf %lf", &x_min, &x_max);
  }

  double dx=(x_max - x_min);  /* largura do intervalo */
  double meio;              /* x no centro do intervalo */
  npassos = 0;    /* numero de passos utilizados para chegar a precisao */
  printf("\n");
  while( dx > precisao ){
    meio = 0.5 * (x_min+x_max);
    printf ("%d - %lf\n",npassos,meio);
    if ( ( f(x_min)*f(meio) ) < 0 ) {
      x_max = meio;
    } else if ( (f(meio)*f(x_max)) < 0 ) {
      x_min = meio;
    } else {
      printf ("Erro: f_min or f_max = 0");
	  return 1;
    }
    dx = (x_max - x_min);
    npassos++; 
  }
  printf ("\n--> Deformacao da mola = %lf\n", meio);
  printf ("--> Bissect : numeros de passos = %d\n",npassos);
  return meio;
}
/*----------------------------------------------------------------------------*/
double NewtonRaphson(double (*f)(double), double (*df)(double), double precisao) {
  double xini=1.5; 
  printf ("*** Newton-Raphson **** \n\n");
  printf("\n");
  while (df(xini) == 0) {
      printf ("O valor inicial tem derivada nula.\n");
      printf ("Entre com um novos valor inicial: ");
      scanf ("%lf", &xini);
  }
  double dx = 1000.;         
  double x;              /* x no centro do intervalo */

  npassos = 0;    /* numero de passos utilizados para chegar a precisao */
  
  while( fabs(dx) > precisao ){
    if ( fabs(df(xini))>0 ) {
      x = xini - f(xini)/df(xini);
    }else{
      printf ("Erro : derivada = 0 !!!");
    }
    dx = (x - xini);
    npassos++; 
    printf("n=%d xi=%13.10f fxi=%f dfxi=%f x=%13.10f\n",npassos, xini, f(xini), df(xini),x);
    xini = x;
  }
  printf ("\n--> Deformacao da mola = %lf\n",xini);
  printf ("--> Newton-Raphson : numeros de passos = %d\n",npassos);
  return x;
}
/*----------------------------------------------------------------------------*/


