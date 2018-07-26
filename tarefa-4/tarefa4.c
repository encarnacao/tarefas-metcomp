#include <stdio.h>
#include <math.h>
#define x2(x) (x*x) //Definindo um macro pra elevar ao quadrado.
#define MAX 10000
//Autor: Caio Encarnação de Queiroz
//DRE: 117096500

//Variáveis globais
const float g = 9.8;
double k, v0x, v0y, m; 

double vx(double t); //Separa-se a velocidade em duas funções. Uma para como ela se comporta no eixo x e outra como ela se comporta no eixo y.
double vy(double t);
double trapezio(double (*f1)(double), double dt); /*Esta é a função que faz o calculo numérico da integral pelo método do trapézio. Como argumento coloquei para aceitar a função, que é necessário e o limite superior da integral para facilitar na hora de escrever o loop na main.*/
/*-------------------------------------------------------------------------------------------------------------*/
int main(void){
  double xt[2], yt[2],t=0 ,dt; /*Posição em x, em y, tempo e intervalo de tempo*/

  printf("\n--------------------------------------// ENUNCIADO //---------------------------------\n");
  printf("Um projétil é lançado do solo com velocidade inicial v⃗0 = v0xî + v0yĵ. Assumindo que\n");
  printf("durante todo o trajeto, além da força da gravidade atue uma força de atrito de tal \n");
  printf("forma que v⃗(t) = (v0xî + (v0y−gt)ĵ)exp(−kt^2/m). Este programa calcula as posições do \n");
  printf("projétil a cada intervalo de tempo Δt até ele atingir o solo novamente.\n"); 
  printf("--------------------------------------// DADOS //-------------------------------------\n");
  /*Espaço dedicado à leitura dos dados*/
  printf("Insira um valor para k: ");
  scanf("%lf", &k);
  printf("Insira um valor para v0x[m/s]: ");
  scanf("%lf", &v0x);
  printf("Insira um valor para v0y[m/s]: ");
  scanf("%lf", &v0y);
  printf("Insira um valor para a massa[kg]: ");
  scanf("%lf", &m);
  printf("Insira o intervalo de tempo Δt[s]: ");
  scanf("%lf", &dt);
  printf("-----------------------------------// POSIÇÕES //-------------------------------------\n"); 
  /*Inicia um loop para medir a posição diversas vezes como já foi explicado anteriormente. Utilizei a estrutura do...while poque era necessario medir yt e t antes de checar a condição.*/
  do{
    xt[1] = trapezio(vx,t);
    yt[1] = trapezio(vy,t);
    if(yt[1]<0){
      double r = -yt[0]/yt[1];
      xt[1] = (xt[0]+r*xt[1])/(r+1);
      yt[1]=0;
    }/*Como é altamentente improvável que o móvel atravesse o chão, eu coloquei um parâmetro pra definir que caso yt seja negativo, ele zere. Com os ultimos pontos, conseguimos estimar uma posição em x. Essa estimativa eu encontrei no livro Computational Physics do Giordano*/
    printf("r⃗(%g): %lfî + %lfĵ\n", t, xt[1], yt[1]); /*O enunciado não especifica como a posição deve ser impressa, portanto eu coloquei pra imprimir como se fosse um vetor, em termos de suas componentes.*/
    t+=dt;
    xt[0]=xt[1];
    yt[0]=yt[1];
  }while(yt[1] != 0 || t==dt); 
  /*Como na posição 0 yt é 0, adicionei um debug para o loop continuar perfeitamente. Havia utilizado antes o parâmetro xt==0, mas isso não permitiria o loop encerrar caso alguém decidisse simular um lançamento vertical, definindo v0x = 0, então decidi colocar esse debug que garante pelo menos 2 iterações do loop.*/

  printf("\n"); //Questão de organização
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