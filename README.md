# IPC_Trabalho1
Exercícios práticos 1 de Introdução a Programação de Computadores. Foram feitos 3 exercícios práticos, sendo eles:
**1. Última Esperança Contra a Skynet
2. O Código Esquecido do Dr. Emmett Brown
3. O Código Secreto de Avalon**
### :wrench: Pré-requisitos
* [GCC](https://gcc.gnu.org/ "GCC (GNU Compiler Collection)") - Compilador para C

### :rocket: Execução
Os exercícios são executados de forma independente, sendo necessário apenas o arquivo ```matrix.txt``` para o **ex1**.

## ex1_LastHopeAgainstSkynet :robot:
### :clipboard: Exercício Proposto:
Você deve implementar uma função chamada ```fuga_humana``` que analisa um mapa representando as áreas
destruídas e infestadas de robôs. Este campo é representado por uma matriz bidimensional, onde os espaços
podem ser seguros (' '), ocupados por robôs da Skynet ('R'), humanos fugitivos ('H'), ou a desejada zona de
evacuação ('Z'). O objetivo é encontrar um caminho seguro, movendo-se para cima, para baixo, para a esquerda
ou para a direita, evitando os robôs assassinos. Os passos do caminho seguro devem ser marcados com '*', e a
função deve retornar o valor 1 (um) se um caminho seguro até a zona de evacuação for encontrado, ou 0 (zero)
se não for possível encontrar um caminho. Caso encontre o caminho seguro, a função deve imprimir a string
“Caminho encontrado” na tela e exibir o mapa com o caminho marcado.

### :books: Bibliotecas Utilizadas
* ```stdio.h``` - Biblioteca padrão de entrada e saída
* ```stdlib.h``` - Biblioteca padrão para alocação de memória 
* ```windows.h``` - Biblioteca Windows para configurar terminal

### :mag: Configurar ```matrix.txt```
O arquivo ```matrix.txt``` deve ser configurado corretamente para que a função ```readMatrix``` consiga obter a matriz "Mapa" do arquivo de texto. Ele deve possuir os caracteres reservados "H", "R", "Z", separados por caracteres qualquer, preferencialmente " " ou "v".
Eles também deve ter a mesma quantidade de caracteres em cada linha, por se tratar de uma matriz com linhas de mesmo tamanho.

### :gear: Funcionamento
#### main
``` mermaid
flowchart TD
    A(["Início"]) --> B{"counter()"}
    B --> C["Obtem quantidade de linhas e colunas"] & D["Falha ao ler arquivo ou linhas e colunas inválidas"]
    D --> E(["Fim"])
    C --> F["readMatrix()"]
    F --> H["Aloca memória para matriz e obtem valores do arquivo"] & I["Falha em alocar memória ou ler arquivo"]
    H --> J["printMatrix()"]
    J --> K["fuga_humana"]
    K --> L["Encontra caminho e imprime matriz"] & M["Não encontra caminho"]
    L --> E
    M --> E
    I --> E
    F@{ shape: diam}
    K@{ shape: diam}
```
### :zap: Principais funções
* ```counter()``` - abre o arquivo e conta linhas e colunas
* ```readMatrix()``` - aloca memoria para matriz e obtem valores do arquivo
* ```findHumanZone()``` - retorna coordenadas do Humano e da Zona Segura
* ```isValid()``` - retorna se determinada coordenada é valida para visita bfs
* ```bfs()``` - função de **Busca em Largura** para matriz, retorna distância do destino
* ```fuga_humana()``` - implementa ```findHumanZone``` e ```bfs```, retorna distancia

## ex2_EmmettBrownCode :scientist:
### :clipboard: Exercício Proposto:
Você precisa implementar uma função chamada ```busca_fibonacci```, que
gera os n primeiros números da Sequência de Fibonacci e usa a busca binária para verificar se um dado número
x está presente na sequência. Esta é uma etapa crítica para encontrar o código de ativação necessário para iniciar
a máquina do Dr. Brown.

### :books: Bibliotecas Utilizadas
* ```stdio.h``` - Biblioteca padrão de entrada e saída
* ```stdlib.h``` - Biblioteca padrão para alocação de memória 

### :zap: Funções
* ```busca_fibonacci()``` - calcula n termos de fibonacci e busca x entre os termos, retorna indice de x ou -1 caso nao encontrar
* ```binary_search()``` - busca binaria do termo x no vetor

## ex3_SecretCodeOfAvalon :classical_building:
### :clipboard: Exercício Proposto:
Você deve ajudar Elise implementando uma função
chamada ```verificar_palindromo``` que recebe uma string como entrada e verifica se ela é um palíndromo. A
função deve retornar ```True``` se a string for um palíndromo e False caso contrário, considerando a necessidade de
ignorar espaços em branco e a diferenciação entre letras maiúsculas e minúsculas.

### :books: Bibliotecas Utilizadas
* ```stdio.h``` - Biblioteca padrão de entrada e saída
* ```stdlib.h``` - Biblioteca padrão para alocação de memória 
* ```string.h``` - Biblioteca padrão com funções em string
* ```ctype.h``` - Biblioteca para tratamento de caractéres

### :zap: Funções
* ```verificar_palindromo()``` - função verificar palíndromo, retorna 1(True) se verdadeiro, 0(False) caso falso
* ```lower_string()``` - função que torna todos os caractéres minúsculos
* ```clean_punctuation()``` - remove espaço e pontuação das strings
* ```reverse_string()``` - inverte a string