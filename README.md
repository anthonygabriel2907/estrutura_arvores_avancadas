# Estruturas em Árvores Avançadas

**Trabalho Individual — Algoritmos e Estruturas de Dados II**
CEFET-MG, Campus V — Divinópolis, Brasil

**Autor:** Anthony Gabriel Sotto Mayor Silva
Graduando em Engenharia de Computação

---

## Sobre o trabalho

Este repositório contém a implementação, a instrumentação de desempenho e os dados experimentais de cinco estruturas de dados em árvore especializadas, desenvolvidas como aprofundamento além das estruturas clássicas de Árvore Binária de Busca (BST) e Árvore AVL. O trabalho tem como objetivo comparar diferentes estratégias de organização, busca, balanceamento e indexação de dados, relacionando fundamentação teórica, decisões de projeto e comportamento experimental observado sob diferentes volumes e distribuições de entrada.

As estruturas implementadas são:

| Estrutura | Pasta | Operações implementadas |
|---|---|---|
| Trie (Árvore de Prefixos) | [`Trie/`](./Trie) | Inserção, busca, remoção lógica |
| Patricia (Radix Tree compacta) | [`Patricia/`](./Patricia) | Inserção com divisão de prefixos (*split*), busca, remoção com re-compactação (*merge*) |
| Splay Tree (árvore autoajustável) | [`Splay/`](./Splay) | Inserção, busca, remoção, rotações de auto-ajuste (*splay*) |
| Treap (Tree + Heap) | [`Treap/`](./Treap) | Inserção, busca, remoção por rebaixamento via rotações |
| KD-Tree (K=2) | [`KDTree/`](./KDTree) | Inserção, busca exata, remoção (algoritmo de Bentley), busca do vizinho mais próximo |

O relatório técnico completo — com fundamentação teórica, decisões de projeto, análise de complexidade assintótica, demonstração visual e discussão crítica dos resultados — está disponível separadamente. Em caso de dúvida sobre qualquer detalhe de implementação não coberto por este README, consulte o [repositório no GitHub](https://github.com/anthonygabriel2907/estrutura_arvores_avancadas) para a versão mais atual do código.

## Estrutura do repositório

```
.
├── Trie/
│   ├── Trie.hpp / Trie.cpp     # Implementação da estrutura
│   └── main.cpp                # Driver de experimentos
├── Patricia/
│   ├── Patricia.hpp / Patricia.cpp
│   └── main.cpp
├── Splay/
│   ├── Splay.hpp / Splay.cpp
│   └── main.cpp
├── Treap/
│   ├── Treap.hpp / Treap.cpp
│   └── main.cpp
├── KDTree/
│   ├── KDTree.hpp / KDTree.cpp
│   └── main.cpp
├── input/                       # Massas de dados de teste, organizadas por estrutura e tamanho
│   ├── dados_teste_string/      # Entradas para Trie e Patricia (aleatório, dicionário, prefixo comum)
│   ├── dados_teste_splay/       # Entradas para Splay (aleatória, crescente, decrescente, acesso uniforme/localidade)
│   ├── dados_teste_treap/       # Entradas para Treap (aleatória, crescente, decrescente)
│   └── dados_teste_kdtree/      # Entradas para KD-Tree (aleatório, agrupado, ordenado)
├── output/                       # Resultados brutos de cada execução (gerados automaticamente)
│   ├── resultados_trie.txt
│   ├── resultados_patricia.txt
│   ├── resultados_splay.txt
│   ├── resultados_treap.txt
│   └── resultados_kdtree.txt
└── Makefile                      # Automação de build e execução
```

Cada pasta de dados em `input/` está subdividida por tamanho de entrada (`tam_10`, `tam_100`, ..., `tam_1000000`), refletindo a metodologia experimental descrita no relatório (escalando de 10¹ a 10⁶ elementos).

## Requisitos

- Compilador **g++** com suporte a C++17 ou superior
- **GNU Make**
- Ambiente Linux (os experimentos do relatório foram executados via WSL)

## Como compilar

O projeto usa um `Makefile` na raiz do repositório, com um alvo individual para cada estrutura:

```bash
make            # compila as cinco estruturas de uma vez
make trie       # compila apenas a Trie
make patricia   # compila apenas a Patricia
make splay      # compila apenas a Splay
make treap      # compila apenas a Treap
make kdtree     # compila apenas a KD-Tree
```

Os executáveis são gerados em `./build/` (ex.: `build/exec_trie`), compilados com as flags `-Wall -Wextra -O3` para garantir otimização máxima nos testes de desempenho.

## Como executar os experimentos

**Importante:** os programas leem os arquivos de `input/` e escrevem em `output/` usando caminhos relativos — por isso, devem ser executados **a partir da raiz do repositório**, não de dentro de `build/`.

```bash
make run-trie       # equivalente a: ./build/exec_trie
make run-patricia
make run-splay
make run-treap
make run-kdtree
```

Cada execução roda automaticamente a bateria completa de testes (inserção, busca e remoção, mais busca de vizinho mais próximo no caso da KD-Tree) sobre todos os tamanhos de entrada disponíveis, medindo tempo de execução, número de operações realizadas e consumo de memória, salvando os resultados no arquivo correspondente em `output/`.

Para limpar os binários gerados:

```bash
make clean
```

## Metodologia experimental

Os testes avaliam o desempenho das operações fundamentais sob diferentes volumes de entrada (10¹ a 10⁶ elementos) e diferentes distribuições de dados — aleatória, ordenada/crescente/decrescente, com sobreposição de prefixos (Trie/Patricia), com localidade de acesso (Splay) e espacialmente agrupada/ordenada (KD-Tree) — de modo a expor tanto o comportamento médio quanto os casos favoráveis e desfavoráveis de cada estrutura. Os experimentos reportados no trabalho foram compilados e cronometrados em ambiente Linux (via WSL), com o compilador GCC (`g++`) e otimização `-O3`.

Os resultados brutos de cada execução ficam salvos em `output/`; a análise crítica completa desses dados, relacionando-os à complexidade assintótica teórica, está no relatório técnico.

## Autor

**Anthony Gabriel Sotto Mayor Silva**
Graduando em Engenharia de Computação — CEFET-MG, Campus V
anthonygabrielsotto29@gmail.com
