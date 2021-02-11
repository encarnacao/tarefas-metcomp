#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define x2(x) x*x
//Autor: Caio Encarnação de Queiroz

/*Constantes e variaveis definidas globalmente, que serão utilizadas em mais de uma função.*/
double m, v0y=25, v0x=25;
const double g = 9.8, sigma = 0.2, tm = 2, k=0.0005; 


/*Funções para os calculos das EDOS.*/
double euler1(double h, double x0, double dx0); 
double euler2(double h,double x0,double (*df)(double));
/*Funções das segundas derivadas das posições.*/
double ay(double v);
double ax(double v);
/*Função da densidade de probabilidade e do método de rejeição*/
double prob(double x);
double reject(double a, double b, double (*f)(double));

int main(void){
  /*Definindo as variáveis necessarias dentro da main.*/
  int i=0, hit=0; //Tentativas e acertos.
  double dt=0.001; //Intervalo de tempo para calcular os pontos das posições
  double y0, x0, t, vx, vy, y, x, te, m2, probabilidade; //Posições iniciais, tempo, velocidades, posições, tempo da explosão, massa do fragmento leve e probabilidade.

  /*----------------------------------------------//ENUNCIADO//----------------------------------------------*/
  printf("----------------------------------------//TAREFA 6//----------------------------------------\n");
  printf("Um projétil de massa 12kg é lançado do solo com velocidade inicial v⃗0=v0xî +v0yĵ. Assumimos\n");
  printf("que durante todo o trajeto além da força da gravidade atue uma força de atrito cujo o módulo\n"); 
  printf("dessa força seja kv^2(t).\n");
  printf("O projétil explode após um intervalo de tempo podendo ser entre 1.4 e 2.6s com densidade de\n");
  printf("probabilidade igual a exp(−0.5∗(t−tm)^2/σ^2), onde tm=2 s e σ=0.2 s. A explosão reparte o\n");
  printf("projétil em dois fragmentos. O fragmento mais pesado fica em repouso após a explosão. O\n");
  printf("fragmento mais leve pode possuir uma massa entre 1 e 2 kg com densidade de probabilidade\n");
  printf("constante nesse intervalo.\n");
  printf("Este programa calcula a probabilidade do fragmento mais leve atingir um alvo no solo\n");
  printf("entre 2000 e 2100m.\n");
  printf("------------------------------------------//DADOS//------------------------------------------\n");
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
      vy = euler2(dt,v0y,ay);
      y = euler1(dt,y0,v0y);
      vx = euler2(dt, v0x, ax);
      x = euler1(dt, x0, v0x);
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
    m = m2;
   
   /*Calcula as posições com os parâmetros novos até o projétil atingir o solo*/
    while(y!=0){
      vy = euler2(dt,v0y,ay);
      y = euler1(dt,y0,v0y);
      if(y<0) y=0; //Assumindo que o projétil não vai ultrapassar o solo, sendo assim, quando y é negativo, redefinimos pra 0.
      vx = euler2(dt,v0x,ax);
      x = euler1(dt,x0,v0x);
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
  return exp(-x2((t-tm))/(2.0*x2(sigma)));
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
double ay(double v){ 
  return -(k/m)*v*sqrt(x2(v0y)+x2(v0x)) - g;
}

/*Segunda derivada de x, a aceleração no eixo x.*/
double ax(double v){ 
  return -(k/m)*v*sqrt(x2(v0y)+x2(v0x));
}

/*Metodo Euler para calcularmos as posições.*/
double euler1(double h, double x0, double dx0){  
  double f;
  f = x0 + h*dx0;
  return f;
}

/*Método euler para calcularmos as velocidades. Como no calculo da posição não utilizamos uma função, mas apenas o valor da velocidade encontrado nesta função, não podemos utlizar a mesma função para o cálculo das duas grandezas. Portanto, eu separei em euler1 e euler2.*/
double euler2(double h,double x0,double (*df)(double)){ 
  double f;
  f = x0 + df(x0)*h;
  return f;
}