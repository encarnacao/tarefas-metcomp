#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define x2(x) x*x
//Autor: Caio Encarnação de Queiroz
/*Versão alternativa da tarefa 6 pra utilizar apenas uma função para o calculo de Euler*/
/*Constantes globais*/
const double g = 9.8, sigma = 0.2, tm = 2, k=0.0005; 

/*Função para os calculos das EDOS.*/
double euler(double h,double x0, double y0, double massa,double (*df)(double,double,double));
/*Funções das segundas e primeiras derivadas das posições.*/
double ay(double vy, double vx, double massa);
double ax(double vx, double vy, double massa);
double Vx(double a, double b, double c);
double Vy(double a, double b, double c);
/*Função da densidade de probabilidade e do método de rejeição*/
double prob(double x);
double reject(double a, double b, double (*f)(double));

int main(void){
  /*Definindo as variáveis necessarias dentro da main.*/
  int i=0, hit=0; //Tentativas e acertos.
  double dt=0.001, m=12, v0y=25, v0x=25;; //Intervalo de tempo para calcular os pontos das posições
  double y0, x0, t, vx, vy, y, x, te, m2, probabilidade; //Posições iniciais, tempo, velocidades, posições, tempo da explosão, massa do fragmento leve e probabilidade.

  printf("-----------------------------//DADOS//-----------------------------\n");
  printf("Velocidade inicial em x: %g m/s\n", v0x);
  printf("Velocidade inicial em y: %g m/s\n", v0y);
  printf("Constante k: %g\n", k);
  printf("Passo do tempo: %gs\n", dt);
  
  while(i<10000){
    /*Redefine os valores pro iniciais para o próximo loop*/
    t=0;
    m = 12;
    v0x = 25;
    v0y = 25;
    x0=0;
    y0=0;

    /*Gera números pseudo-aleatórios pro tempo da explosão e pra massa do fragmento mais leve*/
    te = reject(1.4,2.6,prob); 
    m2 = 1+(double)rand()/RAND_MAX;
    /*Calcula as posições com os parâmtros iniciais até o tempo atingir o tempo da explosão*/
    while (t<te){    
      vy = euler(dt,v0y,v0x,m,ay);
      y = euler(dt,y0,v0y,m,Vy);
      vx = euler(dt,v0x,v0y,m,ax);
      x = euler(dt,x0,v0x,m,Vx);
      t += dt;
      /*Redefine os valores para o próximo cálculo*/
      y0 = y;
      v0y = vy;
      x0 = x;
      v0x = vx;
    }

    /*Utiliza conservação do momento linear para calcular as velocidades do fragmento após a explosão e redefine o valor da massa.*/
    v0x = (m*vx)/m2;
    v0y = (m*vy)/m2;

   /*Calcula as posições com os parâmetros novos até o projétil atingir o solo*/
    while(y!=0){
      vy = euler(dt,v0y,v0x,m2,ay);
      y = euler(dt,y0,v0y,m2,Vy);
      vx = euler(dt,v0x,v0y,m2,ax);
      x = euler(dt,x0,v0x,m2,Vx);
      if(y<0){ 
        double r = -y0/y;
        double xl = (x0 + r*x)/(r+1);
        y = 0;
        x = xl;
      } //Assumindo que o projétil não vai ultrapassar o solo, sendo assim, quando y é negativo, redefinimos pra 0 e estimamos um novo valor pra x.
      t += dt;
      /*Redefine os valores para o próximo cálculo*/
      y0 = y;
      v0y = vy;
      x0 = x;
      v0x = vx; 
    }
    if(x>=2000 && x<=2100) hit++; //Adiciona um contador caso a posição em x do fragmento esteja dentro do intervalo [2000,2100]
    i++; //Nº de tentativas + 1
  }
  /*Probabilidade de atingir o solo no intervalo é calculada*/
  probabilidade = (1.0*hit)/i; 
  printf("Quantidade de tentativas: %d\n", i);
  printf("Quantidade de acertos: %d\n", hit);
  printf("Probabilidade de atingir alvo entre 2000 e 2100m: %g%%\n", probabilidade*100);
  return 0;
}
/*Densidade de Probabilidade*/
double prob(double t){
  return exp(-0.5*x2((t-tm))/(x2(sigma)));
}
/* Função do método de Rejeição */
double reject(double a, double b, double (*f)(double)){
  double z, y, v;
  do{
    z = (double)rand()/RAND_MAX; /*Z é gerado entre 0 e 1 pois é o pico da função da densidade de probabilidade*/
    y = a + (b-a)*(double)rand()/RAND_MAX;
  } while(z>f(y));
  v = roundf(y*1000)/1000; /* Esta linha garante que possamos atingir o valor obtido com o valor de t. Multiplicamos o numero achado no loop por 1000 e arredondamos pra um inteiro, em seguida dividimos por 1000 e sabemos que o numero só pode ter 3 algarismos significativos, e como o tempo cresce em intervalos de 0.001, sabemos que em algum momento necessariamente t == v, então devemos retornar esse valor. */
  return v;
}
/*Segunda derivada de y, a aceleração no eixo y. Além da aceleração proveniente do atrito do ar, temos o termo -g da gravidade que atua sob o projétil.*/
double ay(double vy, double vx, double massa){ 
  double fat = -(k/massa)*vy*sqrt(x2(vy)+x2(vx));
  if(fat <= g) return fat - g;
  if(fat > g) return 0;
}
/*Segunda derivada de x, a aceleração no eixo x.*/
double ax(double vx, double vy, double massa){ 
  return -(k/massa)*vx*sqrt(x2(vy)+x2(vx));
}
double Vx(double a, double b, double c){
  return b;
}
double Vy(double a, double b, double c){
  return b;
}
double euler(double h,double x0, double y0, double massa,double (*df)(double,double,double)){ 
  double f;
  f = x0 + df(x0, y0, massa)*h;
  return f;
}
