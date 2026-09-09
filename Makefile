CXX      := g++
# Usando -O3 por padrão para garantir a otimização máxima nos testes de desempenho
CXXFLAGS := -Wall -Wextra -O3 
BUILD    := ./build

# =====================================================================
# A CORREÇÃO ESTÁ AQUI: Avisa o make que esses nomes são comandos, não pastas!
.PHONY: all clean trie patricia kdtree splay treap run-trie run-patricia run-kdtree run-splay run-treap
# =====================================================================

# A regra "all" agora compila todas as árvores de uma vez
all: trie patricia kdtree splay treap

# Regras individuais para cada árvore
trie:
	@mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) Trie/main.cpp Trie/Trie.cpp -o $(BUILD)/exec_trie

patricia:
	@mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) Patricia/main.cpp Patricia/Patricia.cpp -o $(BUILD)/exec_patricia

kdtree:
	@mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) KDTree/main.cpp KDTree/KDTree.cpp -o $(BUILD)/exec_kdtree

splay:
	@mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) Splay/main.cpp Splay/Splay.cpp -o $(BUILD)/exec_splay

treap:
	@mkdir -p $(BUILD)
	$(CXX) $(CXXFLAGS) Treap/main.cpp Treap/Treap.cpp -o $(BUILD)/exec_treap

# Limpa a pasta build apagando todos os executáveis gerados
clean:
	-@rm -rvf $(BUILD)/*

# Atalhos para rodar cada árvore rapidamente
run-trie:
	./build/exec_trie

run-patricia:
	./build/exec_patricia

run-kdtree:
	./build/exec_kdtree

run-splay:
	./build/exec_splay

run-treap:
	./build/exec_treap