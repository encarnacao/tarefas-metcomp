  #include <stdio.h>
#include <math.h>
#include <stdlib.h>


//variaveis globais
int debug=0;
int npassos=0;
double precisao=1e-5;
const float moduloforca=9.81; 
/*Módulo da força peso. Como o objeto tem m=1kg -> f=ma=1g. Como o módulo da força peso não varia, a defini como uma constante.
O enunciado não especificava o valor da gravidade a ser usado, portanto utilizei g = 9.81 m/s^2, o valor comumente utilizado no 
primeiro volume do Moysés */

double f1( double x );
double df1( double x );


double Bissecao(double (*f)(double), double precisao);
double NewtonRaphson(double (*f)(double), double (*df)(double), double precisao);
    

/*----------------------------------------------------------------------------*/
int main()
{
   /*------------------------------------ENUNCIADO-----------------------------------------*/
  printf("-----------------------------------------------------------------------------\n");
  printf("Um objeto de massa m=1kg está em repouso preso na extremidade de uma mola  \n");
  printf("cuja a outra extremidade está presa no teto. O módulo da força da mola sobre\n");
  printf("o objeto varia com a sua deformação, x, seguindo a equação F(x)=k(x)*x, onde \n");
  printf("k(x)=exp(x). Este programa usa os métodos de Bisseção e de Newton-Raphson para\n");
  printf("encontrar a deformação da mola.\n");
  printf("-----------------------------------------------------------------------------\n");

  printf("Por favor, insira a precisão: "); 
  scanf("%lf", &precisao); //Precisao lida pelo teclado
  debug = 1;
  printf("Deformação da mola = %lf\n\n", Bissecao(f1,precisao));
  debug = 2;
  printf("Deformação da mola = %lf\n", NewtonRaphson(f1,df1,precisao));
  return 1;
}
/*----------------------------------------------------------------------------*/
double f1 ( double x ) {
  return exp(x)*x - moduloforca; 
  /*Normalmente, o método de bissecao e newton-raphson entcontram as raízes das funções
  Como as raízes são valores tais que f(x)=0, para eu encontrar um valor de x tal que f(x)=a, basta eu deslocar a função
  subtraindo o valor "a" f(x). Portanto, supondo que o sistema está em equilibrio. Se eu subtraio o módulo da força peso
  da equação da força elástica e tento achar as raízes pelo programa, irei encontrar a deformação que gera uma força de módulo
  igual a da peso*/
} 
/*----------------------------------------------------------------------------*/
double df1 ( double x ) {
  return exp(x)+x*exp(x);
}

/*----------------------------------------------------------------------------*/
double Bissecao(double (*f)(double), double precisao) {
 
  double x_min, x_max;
  printf ("*** Bissecao **** \n\n");
  printf ("Entre com os valores inferior e superior do intervalo:\n ");
  scanf ("%lf %lf", &x_min, &x_max);

  while ( (f(x_min)*f(x_max)) > 0 ) {
    printf ("O intervalo dado nao contem nenhuma raiz.\n");
    printf ("Entre com novos valores: ");
    scanf ("%lf %lf", &x_min, &x_max);
  }

  double dx=(x_max - x_min);  /* largura do intervalo */
  double meio;              /* x no centro do intervalo */
  npassos = 0;    /* numero de passos utilizados para chegar a precisao */
  
  while( dx > precisao ){
    meio = 0.5 * (x_min+x_max);
    if(debug>1) printf ("%d - %lf\n",npassos,meio);
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
  if (debug==1) printf ("--> Bissect : numeros de passos = %d\n",npassos);
  return meio;
}
/*----------------------------------------------------------------------------*/
double NewtonRaphson(double (*f)(double), double (*df)(double), double precisao) {
  double xini; 
  printf ("*** Newton-Raphson **** \n\n");
  printf ("Entre com o valor inicial para o metodo de Newton-Raphson ");
  scanf ("%lf", &xini);
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
    if(debug>1) printf(" n=%d xi=%13.10f fxi=%f dfxi=%f x=%13.10f\n ",npassos, xini, f(xini), df(xini),x);
    xini = x;
  }
  if(debug>1) printf ("--> Newton-Raphson : numeros de passos = %d\n",npassos);
  return x;
}
/*----------------------------------------------------------------------------*/


