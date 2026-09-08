#include "KDTree.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

void executarExperimento(std::string nomeArquivo, std::ofstream &saida) {
    KDTree minhaArvore;
    std::ifstream arquivo(nomeArquivo);
    std::vector<std::vector<double>> pontosCarregados;
    double x, y;

    if (!arquivo.is_open()) {
        std::cout << "Erro ao abrir o arquivo de entrada: " << nomeArquivo << std::endl;
        return;
    }

    // carrega todos os pontos para a memória para reutilizar nas buscas e remoções
    while (arquivo >> x >> y) {
        pontosCarregados.push_back({x, y});
    }
    arquivo.close();

    std::cout << "\nTestando arquivo: " << nomeArquivo << " ---" << std::endl;
    saida << "\nTestando arquivo: " << nomeArquivo << " ---" << std::endl;

    // inserção
    auto inicioInsercao = std::chrono::high_resolution_clock::now();
    long long opsInsercao = 0;
    
    for (const auto& ponto : pontosCarregados) {
        minhaArvore.inserir(ponto, opsInsercao);
    }
    
    auto fimInsercao = std::chrono::high_resolution_clock::now();
    auto tempoInsercao = std::chrono::duration_cast<std::chrono::milliseconds>(fimInsercao - inicioInsercao).count();

    std::cout << "Insercao: " << pontosCarregados.size() << " pontos em " << tempoInsercao << " ms. (Operacoes: " << opsInsercao << ")" << std::endl;
    saida << "Insercao: " << pontosCarregados.size() << " pontos em " << tempoInsercao << " ms. (Operacoes: " << opsInsercao << ")" << std::endl;

    // busca exata
    auto inicioBusca = std::chrono::high_resolution_clock::now();
    long long opsBusca = 0;
    
    for (const auto& ponto : pontosCarregados) {
        minhaArvore.buscar(ponto, opsBusca);
    }
    
    auto fimBusca = std::chrono::high_resolution_clock::now();
    auto tempoBusca = std::chrono::duration_cast<std::chrono::milliseconds>(fimBusca - inicioBusca).count();

    std::cout << "Busca Exata: " << pontosCarregados.size() << " pontos em " << tempoBusca << " ms. (Operacoes: " << opsBusca << ")" << std::endl;
    saida << "Busca Exata: " << pontosCarregados.size() << " pontos em " << tempoBusca << " ms. (Operacoes: " << opsBusca << ")" << std::endl;

    // busca vizinho mais proximo
    auto inicioKNN = std::chrono::high_resolution_clock::now();
    long long opsKNN = 0;
    
    // testa buscar o vizinho mais próximo usando um ponto de consulta fixo ou dinâmico
    std::vector<double> pontoConsulta = {50.0, 50.0};
    for (int i = 0; i < (int)pontosCarregados.size(); i++) {
        minhaArvore.buscarVizinhoMaisProximo(pontoConsulta, opsKNN);
    }
    
    auto fimKNN = std::chrono::high_resolution_clock::now();
    auto tempoKNN = std::chrono::duration_cast<std::chrono::milliseconds>(fimKNN - inicioKNN).count();

    std::cout << "Busca Vizinho Mais Proximo: " << tempoKNN << " ms. (Operacoes: " << opsKNN << ")" << std::endl;
    saida << "Busca Vizinho Mais Proximo: " << tempoKNN << " ms. (Operacoes: " << opsKNN << ")" << std::endl;

long long memoriaBytes = minhaArvore.getConsumoMemoriaEmBytes();
    double memoriaKB = memoriaBytes / 1024.0;
    double memoriaMB = memoriaKB / 1024.0;

    std::cout << "Memoria:  " << memoriaBytes << " bytes (" << memoriaKB << " KB / " << memoriaMB << " MB)" << std::endl;
    saida << "Memoria:  " << memoriaBytes << " bytes (" << memoriaKB << " KB / " << memoriaMB << " MB)" << std::endl;

    // ================= REMOÇÃO =================
    auto inicioRemocao = std::chrono::high_resolution_clock::now();
    long long opsRemocao = 0;
    
    for (const auto& ponto : pontosCarregados) {
        minhaArvore.remover(ponto, opsRemocao);
    }
    
    auto fimRemocao = std::chrono::high_resolution_clock::now();
    auto tempoRemocao = std::chrono::duration_cast<std::chrono::milliseconds>(fimRemocao - inicioRemocao).count();

    std::cout << "Remocao:  " << pontosCarregados.size() << " pontos em " << tempoRemocao << " ms. (Operacoes: " << opsRemocao << ")" << std::endl;
    saida << "Remocao:  " << pontosCarregados.size() << " pontos em " << tempoRemocao << " ms. (Operacoes: " << opsRemocao << ")" << std::endl;
}
int main() {
    std::ofstream arquivoSaida("output/resultados_kdtree.txt");
    if (!arquivoSaida.is_open()) {
        std::cout << "Erro ao criar arquivo de saida na pasta output!" << std::endl;
        return 1;
    }

    std::cout << "Iniciando testes da KD-Tree" << std::endl;

    executarExperimento("input/dados_teste_kdtree/tam_10/ordenado.txt", arquivoSaida);
    executarExperimento("input/dados_teste_kdtree/tam_10/aleatorio.txt", arquivoSaida);
    executarExperimento("input/dados_teste_kdtree/tam_10/agrupado.txt", arquivoSaida);

    executarExperimento("input/dados_teste_kdtree/tam_100/ordenado.txt", arquivoSaida);
    executarExperimento("input/dados_teste_kdtree/tam_100/aleatorio.txt", arquivoSaida);
    executarExperimento("input/dados_teste_kdtree/tam_100/agrupado.txt", arquivoSaida);

    executarExperimento("input/dados_teste_kdtree/tam_1000/ordenado.txt", arquivoSaida);
    executarExperimento("input/dados_teste_kdtree/tam_1000/aleatorio.txt", arquivoSaida);
    executarExperimento("input/dados_teste_kdtree/tam_1000/agrupado.txt", arquivoSaida);

    executarExperimento("input/dados_teste_kdtree/tam_10000/ordenado.txt", arquivoSaida);
    executarExperimento("input/dados_teste_kdtree/tam_10000/aleatorio.txt", arquivoSaida);
    executarExperimento("input/dados_teste_kdtree/tam_10000/agrupado.txt", arquivoSaida);

    executarExperimento("input/dados_teste_kdtree/tam_100000/ordenado.txt", arquivoSaida);
    executarExperimento("input/dados_teste_kdtree/tam_100000/aleatorio.txt", arquivoSaida);
    executarExperimento("input/dados_teste_kdtree/tam_100000/agrupado.txt", arquivoSaida);

    executarExperimento("input/dados_teste_kdtree/tam_1000000/ordenado.txt", arquivoSaida);
    executarExperimento("input/dados_teste_kdtree/tam_1000000/aleatorio.txt", arquivoSaida);
    executarExperimento("input/dados_teste_kdtree/tam_1000000/agrupado.txt", arquivoSaida);

    
    arquivoSaida.close();
    std::cout << "\nTestes finalizados. Resultados salvos em 'output/resultados_kdtree.txt'" << std::endl;
    
    return 0;
}