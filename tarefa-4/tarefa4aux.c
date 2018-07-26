#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#define x2(x) (x*x)
#define MAX 10000
//Autor: Caio Encarnação de Queiroz

//Variáveis globais
const float g = 9.8;
double k=0, v0x=25, v0y=5, m=0.9; 

double vx(double t);
double vy(double t);
double trapezio(double (*f1)(double), double dt);
/*-------------------------------------------------------------------------------------------------------------*/
int main(void){
  double xt[2], yt[2], t=0, dt=0.01;
  int i = 1;

  printf("\n------------------------// Ajuda Lusiano //--------------------------\n");
  printf("O programa vai criar o grafico necessario pra tarefa 4 na pasta em que ele está\n");
  printf("Recomendavel que seja executado num sistema Unix porque não sei se funciona no Windows.\n");
  for(i=1;i<=3;i++){
    char arq[30];
    sprintf(arq, "psc%d.dat", i);

    FILE *grafico;
    grafico = fopen(arq, "wt");
    if(grafico == NULL){
      printf("DEU RUIM!\n");
      return 0;
    }
    
    t=0;

    do{
      xt[1] = trapezio(vx,t);
      yt[1] = trapezio(vy,t);
      if(yt[1]<0){
        double r = -yt[0]/yt[1];
        xt[1] = (xt[0]+r*xt[1])/(r+1);
        yt[1]=0;
      }
      
      fprintf(grafico, "%g %g\n", xt[1], yt[1]);
      t+=dt;

      xt[0] = xt[1];
      yt[0] = yt[1];
    }while(yt[1]>0 || t == dt);

    k+=0.5;
    fclose(grafico);
  }

  FILE * script=fopen("graph.gpl", "wt");
  fprintf(script, "set xtics 2 nomirror\nset ytics nomirror\nset mxtics 2\nset mytics 2\nset grid mxtics mytics xtics ytics ls 0\nset border 3\nset title 'Posições do projétil'\nset xl 'Posição em x[m]'\nset yl 'Posição em y[m]'\nset term gif size 1920,1080\nset out 'tarefa4.gif'\nplot 'psc1.dat' w lp pt 7 ps 1.5 lw 3 lc rgb 'red' t 'k = 0.0', 'psc2.dat' w lp pt 7 ps 1.5 lw 3 lc rgb 'green' t 'k = 0.5', 'psc3.dat' w lp pt 7 ps 1.5 lw 3 lc rgb 'blue' t 'k = 1.0'\nquit\n");
  fclose(script);

  system("gnuplot -p -e \"load 'graph.gpl'\"");
  system("rm psc1.dat psc2.dat psc3.dat graph.gpl");
  return 0;
}
/*-------------------------------------------------------------------------------------------------------------*/
double vx(double t){
  return v0x*exp(-k*x2(t)/m);
}
/*-------------------------------------------------------------------------------------------------------------*/
double vy(double t){
  return (v0y-g*t)*exp(-k*x2(t)/m);
}
/*-------------------------------------------------------------------------------------------------------------*/
double trapezio(double (*f1)(double), double dt){ 
  double precisao = 1e-5; //A precisão foi especificada no AVA como 10^-5
  int j=1, k=0; //O debug serve para iniciar o loop para as iterações e também pra definir na primeira iteração que T-1 é igual a T0. j é o indice do somatório e k é o numero que eleva 2 e que usamos como indice para o calculo da integral. 2^k define a quantidade de trapézios a ser utilizada
  double a, b, T[MAX], dxk, soma=0, f; //Defino as variaveis dos limites da integral, T é o resultado.
   
  a = 0; //A integral sempre começa de 0
  b = dt; //E vai até o dt inserido no argumento da função.
  
  //Definido T0, a aproximação inicial da integral, e o loop conforme foi visto na aula 7.
  T[0] = 0.5*(b-a)*(f1(a)+f1(b)); 
  do {
    k++;
    dxk = (b-a)/pow(2.,k);

    j = 1;
    soma=0;

    while(j<=(pow(2,k)-1)){
      f = f1(a + j*dxk);
      soma=soma+f;
      j+=2.;
    }

    T[k] = T[k-1]*0.5 + dxk*soma;
  }
  while(fabs(T[k]-T[k-1])>=precisao);

  return T[k]; //A função retorna T, que é o valor da integral de 0 até dt.
}
/*-----------------------------------------------------------------------------------------------------------*/