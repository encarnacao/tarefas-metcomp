//Autor: Caio Encarnação de queiroz
#include <math.h>
#include <stdio.h>
#include <string.h>
#define g 9.8 //O valor da gravidade conforme especificado no enunciado.
double k, b, m, v0y, v0x; 
/*Variaveis definidas globalmente, pois elas serão utilizadas em mais de uma função.*/

/*Funções para os calculos das EDOS.*/
double euler1(double h, double x0, double dx0); 
double euler2(double h,double dx0,double (*df)(double));
/*Funções das segundas derivadas das posições.*/
double ddy(double v);
double ddx(double v);

int main(void){
  /*Definindo as variáveis necessarias dentro da main.*/
  double y0 = 0, x0 = 0, t = 0;
  double y, vy, x, vx, dt;
  char fname[30]; //Nome do arquivo a ser criado.
  FILE *euler = NULL; //Arquivo para a escrita das posições.

  /*------------------------------//ENUNCIADO//------------------------------*/
  printf("------------------------------//TAREFA 5//------------------------------\n");
  printf("Um projétil é lançado do solo com velocidade inicial v⃗0=v0xî +v0yĵ.\n");
  printf("Assumimos que durante todo o trajeto além da força da gravidade atue\n"); 
  printf("uma força de atrito cujo o módulo dessa força seja kv^2(t)(a força de\n");
  printf("atrito tem a mesma direção e sentido oposto ao da velocidade do projétil)\n");
  printf("Este programa calcula as posições do projétil a cada intervalo de tempo\n");
  printf("até ele atingir o solo novamente. Ele utiliza o método de Euler para o\n");
  printf("calculo das EDOs de segunda ordem.\n");
  printf("-------------------------------//DADOS//-------------------------------\n");
  printf("Por favor insira um valor para a massa[kg]: ");
  scanf("%lf", &m);
  printf("Por favor insira um valor para constante k: ");
  scanf("%lf", &k);
  printf("Por favor insira um valor para o intervalo de tempo[s]: ");
  scanf("%lf", &dt);
  printf("Por favor insira um valor para a velocidade inicial em x[m/s]: ");
  scanf("%lf", &v0x);
  printf("Por favor insira um valor para a velocidade inicial em y[m/s]: ");
  scanf("%lf", &v0y);
  printf("-----------------------------//POSIÇÕES//-----------------------------\n");

  sprintf(fname, "posicoes.dat"); //Nome do arquivo

  euler = fopen(fname, "wt"); //Cria arquivo
  if (euler == NULL){
    printf("Erro na criação do arquivo.\n");
    return 0;
  }

  /*Printa as posições iniciais*/
  fprintf(euler, "%lf %lf\n", x0, y0);
  printf("r⃗(%g): %lfî + %lfĵ\n", t, x0, y0);

  b = k/m;

  while (y>0 || t == 0) //Inicia o loop com duas condições. Quando y==0  o projétil atinge o solo. Entretanto, em t=0, a posição em y, y0==0. Portanto, outra condição pro loop iniciar é t ser igual a 0.
  {
    vy = euler2(dt,v0y,ddy);
    y = euler1(dt,y0,v0y);
    vx = euler2(dt,v0x,ddx);
    x = euler1(dt,x0,v0x);

    if(y<0){ 
        double r = -y0/y;
        double xl = (x0 + r*x)/(r+1);
        y = 0;
        x = xl;
      } //Assumindo que o projétil não vai ultrapassar o solo, sendo assim, quando y é negativo, redefinimos pra 0 e estimamos um novo valor pra x.

    t += dt;

    fprintf (euler, "%lf %lf\n", x, y); //Escreve as posições em um arquivo.
    printf("r⃗(%g): %lfî + %lfĵ\n", t, x, y); //Printa as posições em forma de vetor.

    /*Redefine os valores para o próximo cálculo*/
    y0 = y;
    v0y = vy;
    x0 = x;
    v0x = vx;
  }
  printf("Arquivo \"%s\" criado.\n", fname);
  fclose(euler);
  return 0;
}

double ddy(double v){ //Segunda derivada de y, a aceleração no eixo y. Além da aceleração proveniente do atrito do ar, temos o termo -g da gravidade que atua sob o projétil.
  double fat = -b*v*sqrt(v0y*v0y+v0x*v0x);
  if(fat <= g) return fat - g;
  if(fat > g) return 0;
}

double ddx(double v){ //Segunda derivada de x, a aceleração no eixo x.
  return -b*v*sqrt(v0y*v0y+v0x*v0x);
}
/*Metodo Euler para calcularmos as posições.*/
double euler1(double h, double x0, double dx0){  
  double f;
  f = x0 + h*dx0;
  return f;
}
/*Método euler para calcularmos as velocidades. Como no calculo da posição não utilizamos uma função, mas apenas o valor da velocidade encontrado nesta função, não podemos utlizar a mesma função para o cálculo das duas grandezas. Portanto, eu separei em euler1 e euler2.*/
double euler2(double h,double dx0,double (*df)(double)){ 
  double f;
  f = dx0 + df(dx0)*h;
  return f;
}