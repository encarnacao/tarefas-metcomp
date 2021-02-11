# TAREFA 6: DENSIDADE DE PROBABILIDADE E MÉTODO EULER
Alright. Eu demorei muito tempo pra continuar isso. Eu sequer lembro bem qual era a Tarefa 6. Ela empregava dois métodos estudados: método da rejeição e método euler. Por sorte, eu sempre pus os enunciados em todos os programas, então tenho uma boa noção do que foi feito.

A princípio, pouca coisa mudou da tarefa 5. Continuamos tendo o mesmo tipo de lançamento, são as mesmas equações de movimento, e é até o mesmo método de resolução de EDO. Porém temos dados fixos, e incluimos números _pseudoaleatórios_. Temos um projétil de 12 kg lançado do solo com velocidades iniciais em x e y iguais a 25 m/s. Durante todo o trajeto há atrito e gravidade. Porém, o _twist_ é que em algum instante **aleatório** entre 1,4 e 2,6 segundos o projétil explode. A densidade de probabilidade deste evento é **gaussiana**, com desvio padrão de 0.2 e tempo médio de 2 segundos. A explosão reparte o objeto em dois fragmentos, onde o mais leve pode possuir uma massa de 1 a 2 kg, onde a densidade de probabilidade desta vez é constante.

O que o programa faz é, a partir desta simulação que roda 10 mil vezes, calcula a probabilidade deste fragmento mais leve atingir o solo no intervalo de de 2 e 2,1 km. O passo do tempo utilizado para o método Euler é de 0.001 segundo, este que é utilizado para calcular a posição do fragmento a cada passo. O método da rejeição é utilizado para decidir o tempo da explosão. Esta é a integração dos dois métodos visto em aula.

Existem duas versões do programa apenas pelo simples motivo de que eu quis tentar uma implementação do método euler em uma função apenas. Algo muito mais fácil com as _molezas_ que o Python me proporcionol depois(Oi, numpy rs. Vem sempre por aqui?). Hoje eu volto, com um pouco mais de experiência, e surpreendentemente eu entendo o que o programa faz. Fui cauteloso nos comentários durante Metcomp. Também percebo certos erros que não cometeria caso estivesse querendo escrever um programa hoje em dia, como empregar variáveis globais. Em suma, volto ao GitHub depois de 3 anos com certa determinação pra registrar meu não tão grandioso progresso no mundo da programação. Este é o primeiro passo. 

Por fim, segue um plot das primeiras 10 simulações, apenas a titulo de curiosidade. O programa mesmo não gera arquivo ou imagem, mas eu fiz quando mais novo porque queria ver a parada bonitinha, e é bonitinha mesmo. Cada linha de cor diferente representa um lançamento diferente.É possível ver claramente onde ocorre a explosão pela mudança brusca do movimento, mas está longe demais para ver as diferenças no templo de explosão. E também, é um plot de posição x posição, não de posição x tempo. Este que seria útil para ver a diferença do tempo de explosão. Apesar disso, como todas as condições iniciais são as mesmas, é possível ver que há algo aleatório ocorrendo quando há a explosão.

![Gráfico com o plot dos lançamentos][lancamentos]

Bom, eu fiquei com 10 na tarefa, suponho que tudo esteja certo. 


[lancamentos]:https://i.imgur.com/rZjxnEZ.png
