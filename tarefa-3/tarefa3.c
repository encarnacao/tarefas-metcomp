#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//Autor: Caio Encarnação de Queiroz

//Variaveis Globais
const double HMin = 1e5; //A quantidade minima de hits 

/*----------------------------------------------------------------------------------------------------------*/
double f1(double x){
  return -exp(x)*x;
}
/*----------------------------------------------------------------------------------------------------------*/
int main(void) {
  double total=0, hit=0, h, b, Ar; //Tentativas, Hits, Altura, Base e Area do retângulo.
  double li=0, ls; //Limites inferior, que é sempre 0, e inferior, inserido posteriormente pelo usuário.

  /*-------------------------------------------ENUNCIADO-------------------------------------------------*/
  printf("-----------------------------------------------------------------------------------------\n");
  printf("Uma mola quando distendida realiza uma força F(x)=−k(x)*x [N], onde k(x)=exp(x) [N/m] e x=0 [m]\n");
  printf("quando a mola está relaxada. Este programa calcula o trabalho da força de F(x) sobre um\n");
  printf("bloco para um distendimento da mola que seja dado como entrada pelo teclado usando o método de\n");
  printf("integração Hit or Miss tendo pelo menos 100000 acertos.\n");
  printf("-----------------------------------------------------------------------------------------\n");

  printf("Insira o valor de x: ");  
  scanf("%lf", &ls);
  while (ls == 0){
  	printf("O distendimento não pode ser 0, o trabalho é nulo, por favor insira um novo valor: ");
  	scanf("%lf", ls);
  }
  if(ls<-1) h=f1(-1); 
  if(ls>=-1)  h=f1(ls);
  b = ls;
  Ar = b * h;
  /*Definimos área do retângulo. A altura é definida como 0.4 caso a área a ser calculada seja à esquerda do gráfico,
  já que 0.4 é maior que o ponto máximo da função. Caso seja à direita, calculamos a altura como f(ls), sendo assim 
  sempre o ponto mais alto. Como b seria ls-li, mas já que li=0, b=ls*/

  if (ls<0){ 
    while (hit<=HMin){
  	float x = li + b*rand()/RAND_MAX;
   	float y = h*rand()/RAND_MAX;
    if (y <= f1(x)) hit++;
    total++;	
    }
  }
  if (ls>0){
    while (hit<=HMin){
  	float x = li + b*rand()/RAND_MAX;
   	float y = h*rand()/RAND_MAX;
    if (y >= f1(x)) hit++;
    total++;  	
    }
  }
  /*É necessário observar dois casos distintos novamente, o caso de ls>0 e ls<0, já que o critério para um hit muda
  nos casos, como a área para ls>0 está abaixo do gráfico.*/


  double itg = (hit/total)*Ar; //Calculo da integral
  
  printf("Trabalho de F(x) de %g até %g = %lf\n", li, ls, itg );
  return 0;
}