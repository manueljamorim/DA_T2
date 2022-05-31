Instâncias de grafos dirigidos acíclicos com pesos

A primeira linha tem o número de vértices (N) e o número de ramos (R)

Seguem-se R linhas, cada uma com 4 inteiros

       i j Capacidade_ij Duração_ij

i é o nó inicial do ramo  e j o nó final.

 --- O grafo define um DAG

 --- Os nós estão numerados de 1 a N

 --- O nó 1 é o único com grau de entrada zero.

 --- O nó N é o único com grau de saída zero.
  
 --- Não há ramos com a mesma origem e o mesmo fim
     (ou seja se tem  i j ...  só terá uma vez)

