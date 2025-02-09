# Projeto: Manipulação de Árvores Binárias em C

Este projeto contém a implementação em C de três questões envolvendo manipulação de árvores binárias, conforme especificado. Além das soluções em C, há um script em Python para gerar arquivos de entrada com 1000 linhas para cada questão.

## Conteúdo do Projeto

- **RL2Q1.c**  
  Implementa a **Questão 1**:  
  - Insere uma sequência de números inteiros em uma árvore binária de busca (ABB).  
  - Registra a altura de cada nó (a raiz possui altura 0).  
  - Após a inserção, identifica o nó com a chave máxima, sua altura e seu predecessor.  
  - **Arquivo de entrada:** `L2Q1.in`  
  - **Código fonte:** [`RL2Q1.c`](lista%202/RL2Q1.c) 
  - A saída é gravada em `L2Q1.out`.

- **RL2Q2.c**  
  Implementa a **Questão 2**:  
  - Insere números inteiros em uma ABB **sem permitir nós duplicados**.  
  - Após a inserção, a árvore é percorrida em ordem e, para cada nó, calcula a diferença entre a soma dos nós da subárvore direita e a soma dos nós da subárvore esquerda.  
  - **Arquivo de entrada:** `L2Q2.in` 
  - **Código fonte:** [`RL2Q1.c`](lista%202/RL2Q2.c) 
  - A saída é gravada em `L2Q2.out` no formato `chave (dif)`.

- **RL2Q3.c**  
  Implementa a **Questão 3**:  
  - Processa operações de inserção e remoção em uma ABB.  
  - Operações:  
    - `a X`: adiciona o número X na árvore (permitindo duplicatas).  
    - `r X`: remove o número X; se o nó não existir, a operação é tratada como inserção.  
  - Após as operações, a árvore é percorrida em ordem e cada nó é impresso com sua altura (número mínimo de arestas a partir da raiz). 
  - **Arquivo de entrada:** `L2Q3.in`  
  - **Código fonte:** [`RL2Q1.c`](lista%202/RL2Q3.c)  
  - A saída é gravada em `L2Q3.out`.

## Configuração do ambiente

Para compilar e depurar os códigos, utilize o Visual Studio Code com as seguintes configurações:

- **Compilador:** gcc
- **Depurador:** gdb

### Arquivo `tasks.json`

Configuração para compilar os arquivos `.c`:

```json
{
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C/C++: gcc arquivo de build ativo",
            "command": "/usr/bin/gcc",
            "args": [
                "-fdiagnostics-color=always",
                "-g",
                "${file}",
                "-o",
                "${fileDirname}/${fileBasenameNoExtension}"
            ],
            "options": {
                "cwd": "${fileDirname}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "Tarefa gerada pelo Depurador."
        }
    ],
    "version": "2.0.0"
}
```


## Como executar  
1. Abra o **Visual Studio Code**.
2. Abra a pasta do projeto `cd lista 1`  .
3. Compile o código utilizando a tarefa de build (`Ctrl+Shift+B`).
4. Inicie a depuração (`F5`).


### Compilação

Utilize o compilador `gcc` no terminal para compilar os arquivos C. Por exemplo:

```bash
gcc L2Q1.c -o L2Q1
gcc L2Q2.c -o L2Q2
gcc L2Q3.c -o L2Q3
```

Para executar os aquivos compilados
```bash
./L2Q1
./L2Q2
./L2Q3
```

### Licença
Este projeto está licenciado sob a licença MIT. Veja o arquivo LICENSE para mais detalhes. 