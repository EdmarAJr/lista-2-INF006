/**
* Considere as seguintes entrada e sáida abaixo:

*          L2Q2.in

*    15 2 5 19 2 22 4 9 0 3 4 5
*    0 2 4 5 1
*    4

*                      L2Q2.out

*    0 (0 ) 2 (21) 3 (0 ) 4 (−3) 5 (2 ) 9 (0 ) 15 (18) 19 (22) 22 (0 )
*    0 (12) 1 (0 ) 2 (8 ) 4 (5 ) 5 (0 )
*    4 (0 )

* Cada linha da entrada consiste em uma lista de números inteiros a ser inserida em árvore binária inicialmente vazia. O número mı́nimo de arestas de um nó à raiz define a altura deste nó. O nó raiz, portanto, tem altura zero. A cada adição de nó, se registra a altura deste. Nós com chave menor se posicionam à esquerda de seu nó pai, aqueles com chave maior ou igual à do nó pai à sua direita. Porém, nesta questão, árvores não admitirão nós duplicados.

* Na sáida, cada nó, em ordem, registrará a diferença entre a soma dos nós à direita menos a soma dos nós à esquerda (nesta ordem).
*/

 