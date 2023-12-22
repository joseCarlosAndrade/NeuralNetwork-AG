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




## Biblioteca para Algoritmos Genéticos





## Interface gráfica



## Jogos implementados

### Jogo da velha simples e complexo



### Ligue 4



## Integrantes do projeto

Eduardo Souza Caproni

José Carlos Andrade do Nascimento

Matheus Della Rocca Martins








It uses my [matrices operation library](https://github.com/joseCarlosAndrade/MatrixOperationLib-C) built for matrices manipulation in C, and also a [mini game](https://github.com/joseCarlosAndrade/dev-jc/tree/main/c/study/game) that I've written in the same language.
