# Algoritmo de Dijkstra

​	Minha implementação do algoritmo de Dijkstra, estudado durante a disciplina "Algoritmos e Estruturas de Dados II", no curso Sistemas de Informação da Universidade de São Paulo. O código encontra o caminho de custo mínimo entre um vértice e outro, em um grafo não-dirigido ponderado; vértices representam salas, e arestas conexões entre as salas, com um peso associado a elas que representa o custo.
​	Para aumentar a dificuldade do problema, foi acrescentada a informação de que algumas salas podem estar trancadas, e nesse caso existirá uma sala com chave que concede acesso a todas outras salas. O caminho de menor custo não pode passar por uma sala trancada sem passar pela sala com chave antes, e é função do algoritmo decidir se é melhor passar pela sala com chave ou não.
		
 	Além da implementação do Dijkstra, o código também executa uma serialização de estrutura de dado. O grafo está representado por um arquivo txt, e o  programa abre esse arquivo e recupera as informações com o uso de fscanf em diferentes laços. As arestas do grafo são armazenas em um vetor ijpeso[], no qual cada tripla representa uma aresta. Por exemplo ijpeso[] = {1,3,10, 5,8,10} tem duas arestas, entre os vértices 1 e 3, 5 e 8, e ambas com peso 10. O arquivo grafo.txt também contém a informação dos testes que serão realizados no grafo, para verificar qual o custo mínimo entre diferentes salas, considerando diferentes cenários, em que as salas trancadas e a sala com chave mudam.

​	Cujas informações estão no arquivo txt com o seguinte formato:

9 15
1 2 1
1 4 2
1 6 1
1 8 4
2 3 4
2 4 2
2 8 1
2 9 5
3 4 1
3 5 1
4 5 1
5 6 2
6 7 1
7 8 2
8 9 1

	A primeira linha contém a quantidade de vértices do grafo, seguida pela quantidade de arestas. Além disso, grafo.txt também possui os testes que serão realizados:
10
1 9 3 1 0 1 1 1 1 1 1 1
1 9 7 1 0 1 1 1 1 1 0 1
1 9 3 1 0 1 1 1 1 1 0 1
1 9 3 1 0 1 0 1 1 1 0 1
9 4 7 1 1 1 1 1 1 1 1 1
9 4 7 1 0 1 1 1 1 1 1 1
9 4 7 0 0 1 1 1 1 1 1 1
9 4 7 1 1 1 1 1 1 1 0 1
8 6 3 1 0 1 1 0 0 1 1 1
8 6 3 0 1 1 1 0 0 1 1 1

​	Com o código implementado, é possível fazer o quaisquer testes em qualquer grafo não-dirigido ponderado, desde que o arquivo txt tenha a mesma formatação de grafo.txt.

# Compilação e execução

​	Para compilar, é necessário ter o gcc instalado.

- #### Instalação do gcc em sistemas operacionais windows

  ​	Caso você não possua o gcc em sua máquina e utilize windows, baixe o mingw neste link(recomendado): https://sourceforge.net/projects/mingw/. Após o término do download, execute o arquivo e conclua toda a instalação. Depois é necessário configurar as variáveis de ambiente. Se tiver dúvidas em algum desses passos, siga esse tutorial: https://dev.to/gamegods3/how-to-install-gcc-in-windows-10-the-easier-way-422j

- #### Instalação do gcc em sistemas operacionais linux

  ​	Caso você utilize alguma distribuição linux, provavelmente o seu sistema já tem o gcc instalado. Para verificar, abra o terminal e digite o comando "gcc --version". Se for exibida a versão do gcc, está tudo certo. Caso contrário, apenas digite "sudo apt install gcc", que o sistema se encarregará de instalar o gcc junto com toda a biblioteca do C, inclusive da configuração das variáveis de ambiente.

- #### Compilação

  ​	Após se assegurar que o gcc está devidamente instalado junto com toda a biblioteca padrão do C, abra o terminal na mesma pasta que contém os códigos fonte e o arquivo txt, digite o comando "gcc main.cpp -o main", para compilar o código e gerar um executável binário. Por fim, digite "main grafo.txt" para executar. A função main recebe como argumento o nome do arquivo txt, por isso é importante que o nome desse arquivo seja digitado corretamente.
