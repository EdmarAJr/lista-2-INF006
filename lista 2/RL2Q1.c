/**
* Considere as seguintes entrada e sáida abaixo:

*             L2Q1.in

         5 8 −1 4 6 9 11 15
         5 6 7 6 5 4

*                L2Q1.out

     0 1 1 2 2 2 3 4 max 15 a l t 4 pred 11
     0 1 2 3 2 1 max 7 a l t 2 pred 6

* Cada linha da entrada consiste em uma lista de números inteiros a ser inserida em árvore binária inicialmente vazia. O número mı́nimo de arestas de um nó à raiz define a altura deste nó. O nó raiz, portanto, tem altura zero. A cada adição de nó, se registra a altura deste. Nós com chave menor se posicionam à esquerda de seu nó pai, aqueles com chave maior ou igual à do nó pai à sua direita.

* Na sáida, você deve registrar a altura de cada nó inserido na sequência informada, o nó com chave máxima, sua altura e seu predecessor (não havendo predecessor, imprima NaN).
*/