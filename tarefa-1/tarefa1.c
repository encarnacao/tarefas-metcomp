#include <stdio.h>
#include <math.h>
#include <stdlib.h>
//Autor: Caio Encarnação de Queiroz

int debug=0;

double fat(double a){ //Eu defini uma função para usar o fatorial, após tentativas frustradas de jogar um loop dentro de outro loop. Isto também ajuda na organização do código.
  double ftrl=1;
  while(a>1){ //Produtório
    ftrl=ftrl*a ;
    a--;
  }
return(ftrl);
}

void main(){ //Aqui começa a função principal que de fato contém a série de taylor.
  int n=0; //Numero de termos do somatório, a soma inicia de n=0 até infinito.
  float x, rad; //O valor de x cujo seno o usuário gostaria de saber, em graus, e uma variável pra transformá-lo em radianos. Caso definimos essas variáveis como doubles, há um problema no calculo do critério de pausa do loop
  double tl, soma=0, ref, acc; //tl é a série de taylor, soma será a variável que somará os termos do somatório, e ref é o valor de referência que usaremos pra saber a acurácia do cálculo.

  /*-----------------------------------------------------ENUNCIADO------------------------------------------------------*/
  printf("Este programa calcula o valor de sin(x) através da serie de Taylor\nO programa atinge uma acurácia de 1%%\n\n");
  printf("Insira o valor de x para o calculo de sin(x): ");
  scanf ("%f", &x); //Scaneia um valor inserido pelo teclado.
  printf("\nSomatorio:\n");
  /*-------------------------------------------------------------------------------------------------------------------*/

  rad = x*M_PI/180; //Transforma o valor de x, que está em graus, em radianos
  ref=sin(rad); //Define a variável ref como sin(x), função presente na biblioteca math.h

  while (debug ==0 || acc>0.01 || fabs(soma)>1 ) { //Loop do somatório, como o critério para iniciar não pode ser alcançado antes da primeira iteração, defini um debug pra iniciar o loop.
    acc = fabs(1-soma/ref);  //Um dos critérios é definido, inicializando a variável acc
    tl = (pow(rad,2*n+1)*pow((-1),n))/(fat(2*n+1)); 
    soma = soma+tl; 
    printf ("n%d: %lf \n", n, soma);//Essa linha especifica que os resultados devem ser impressos a cada termo.
    n++;
    debug = 1;
    }

  printf ("\nSin(%.0f): %lf \nNumero de termos: %d\nValor de Referencia:%lf\nCriterio:%lf\n", x, soma, n, ref, acc); 
  /*Impressão do resultado final. A título de curiosidade, imprimi o numero de termos, o valor de referência e o critério, que é a acurácia.*/
}