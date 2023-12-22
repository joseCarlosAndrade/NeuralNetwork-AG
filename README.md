# Rede Neural treinada com Algoritmos Genéticos

## Descrição

Este projeto visa oferecer uma solução abrangente para a aplicação de algoritmos evolutivos na otimização dos parâmetros de redes neurais, abordando uma variedade de problemas. Para isso, foi desenvolvida uma biblioteca genérica destinada para a manipulação e configuração de Algoritmos Evolutivos. Também adaptamos a biblioteca MiniDNN para manipular, de forma genérica, Redes Neurais. Além disso, essas bibliotecas foram empregadas no contexto do aprendizado de máquina em jogos clássicos.

## Configuração e instalação

Para instalar, primeiro clone o repositório e, posteriormente, siga os seguintes comandos:

### Requisitos

### Obtenção das bibliotecas necessárias:

As bibliotecas MiniDNN (https://github.com/yixuan/MiniDNN) e Eigen (https://eigen.tuxfamily.org/index.php?title=Main_Page) são fundamentais para o funcionamento deste projeto. Desta forma, verifique se foram copiadas de forma adequada ao clonar o repositório. Em caso negativo, remova as pastas vazias e siga os seguintes comandos:

```shell
    cd lib
    git clone https://github.com/yixuan/MiniDNN.git # Clone a biblioteca MiniDNN
    git clone git clone https://gitlab.com/libeigen/eigen.git # Clone a biblioteca Eigen
```

Vale destacar que este projeto necessita de versões recentes do compilador de C e C++, por isso, recomenda-se atualiza-los para a versão mais recente.


### Configurações iniciais - CMakeLists

```shell
    mkdir build   # Crie a pasta build
    cd build      
    cmake ..      # Configure o ambiente de compilação
    make          # Compile o repositório
```

### Configurações iniciais - MakeFiles

Para instalar, primeiro clone o repositório e, posteriormente, siga os seguintes comandos:

```shell
    make install # compile my libraries 

    make all # compile the main code

    make run # run the main code
```


## Adaptação da biblioteca MiniDNN

Adaptou-se a biblioteca MiniDNN (https://github.com/yixuan/MiniDNN), já conhecida por possibilitar a criação facilitada de redes neurais profundas com uma variedade de características customizáveis, de modo que fosse possível tanto inicializar uma rede neural a partir da passagem do número de camadas e neurônios como realizar operações fundamentais de soma, subtração, divisão e multiplicação de duas redes neurais facilmente. Além disso, possibilitou-se a inicialização de uma rede neural com parâmetros de pesos e biases lidos de um arquivo de texto e também o salvamento destes parâmetros em arquivos de texto. 


## Biblioteca para Algoritmos Genéticos

Escrita em C, com intuíto de obter melhor desempenho computacional, esta biblioteca busca ser uma solução abrangente para a manipulação de algoritmos genéticos. A biblioteca está colocada dentro do repositório AG e facilita a criação de algoritmos evolutivos ao implementar genericamente uma grande variedade de métodos de seleção, predação e genocídio conhecidos da literatura dessa área. Além disso, a biblioteca permite, por meio de funções específicas descritas no header da biblioteca, a visualização do histórico de fitness e a obtenção do melhor indivíduo.

Para utiliza-la em problemas variados o usuário deve descrever seu problema por meio da criação de funções pré-definidas que serão passadas para a biblioteca. Tais funções podem ser encotradas no arquivo de exemplo criado, funçãoEscrota.c, ou no diretório Player, Player.cpp, e devem fornecer informações essenciais como a forma de avaliar o fitness, executar o crossover e a mutação, obter um elemento do objeto evolutivo e descrever sua inicialização e criação. Por fim, utiliza-se uma estrutura chamada Type Evolvable para criar uma estrutura de dados genérica ao passar o T_EVOL como argumento na sua criação, permitindo que a estrutura consiga lidar com os dados recebidos. Vale destacar que o Type Evolvable é um TAD que guarda funções específicas para a utilização em algoritmos evolutivos.

Métodos de seleção implementados: elitismo, torneio de dois e roleta. 

Métodos de genocídio implementados: genocídio mantendo o melhor elemento na população, genocídio de todos os elementos e genocídio desabilitado.

Métodos de predação implementados: predação por síntese, predação randômica e predação desabilitada.


## Interface gráfica



## Jogos implementados

### Jogo da velha simples e complexo



### Ligue 4




## Diretórios fundamentais

### AG

Diretório que contém a biblioteca para manipulação de algoritmos genéticos.

### Player

Diretório que contém a adaptação da biblioteca para manipulação de Redes Neurais e a implementação genérica das funções essenciais para a criação de um algoritmo evolutivo para jogos competitivos, como o jogo da velha e o ligue 4. 

### app

Diretório com scripts para a execução do treinamento e possíveis testes com redes treinadas. 

### Game

Diretório com a implementação de jogos criados para treinamento de redes neurais. 

### python_plot_history

Diretório com script para plotagem dos gráficos com informações fundamentais do treinamento da rede, representando a evolução do fitness médio e do melhor indivíduo em função do número de gerações.


## Integrantes do projeto

Eduardo Souza Caproni

Gabriel Takeshi Miyake Batistella

Guilherme Barros Villela

José Carlos Andrade do Nascimento

Matheus Della Rocca Martins

Nicolas Oliveira Rossoni
