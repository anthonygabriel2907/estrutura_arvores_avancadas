#include "Splay.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>

void executarExperimento(std::string nomeArquivo, std::ofstream &saida) {
    Splay minhaArvore;
    std::ifstream arquivo(nomeArquivo);
    int chave;

    if (!arquivo.is_open()) {
        std::cout << "Erro ao abrir o arquivo de entrada: " << nomeArquivo << std::endl;
        return;
    }

    std::cout << "\nTestando arquivo: " << nomeArquivo << " ---" << std::endl;
    saida << "\nTestando arquivo: " << nomeArquivo << " ---" << std::endl;

    auto inicioInsercao = std::chrono::high_resolution_clock::now();
    int contInsercoes = 0;
    long long opsInsercao = 0;
    
    while (arquivo >> chave) {
        minhaArvore.inserir(chave, opsInsercao);
        contInsercoes++;
    }
    auto fimInsercao = std::chrono::high_resolution_clock::now();
    auto tempoInsercao = std::chrono::duration_cast<std::chrono::milliseconds>(fimInsercao - inicioInsercao).count();

    std::cout << "Insercao: " << contInsercoes << " chaves em " << tempoInsercao << " ms. (Operacoes: " << opsInsercao << ")" << std::endl;
    saida << "Insercao: " << contInsercoes << " chaves em " << tempoInsercao << " ms. (Operacoes: " << opsInsercao << ")" << std::endl;

    arquivo.clear();
    arquivo.seekg(0, std::ios::beg);

    // Busca
    auto inicioBusca = std::chrono::high_resolution_clock::now();
    int contBuscas = 0;
    long long opsBusca = 0;
    
    while (arquivo >> chave) {
        minhaArvore.buscar(chave, opsBusca);
        contBuscas++;
    }
    auto fimBusca = std::chrono::high_resolution_clock::now();
    auto tempoBusca = std::chrono::duration_cast<std::chrono::milliseconds>(fimBusca - inicioBusca).count();

    std::cout << "Busca:    " << contBuscas << " chaves em " << tempoBusca << " ms. (Operacoes: " << opsBusca << ")" << std::endl;
    saida << "Busca:    " << contBuscas << " chaves em " << tempoBusca << " ms. (Operacoes: " << opsBusca << ")" << std::endl;

    arquivo.clear();
    arquivo.seekg(0, std::ios::beg);

    long long memoriaBytes = minhaArvore.getConsumoMemoriaEmBytes();
    double memoriaKB = memoriaBytes / 1024.0;
    double memoriaMB = memoriaKB / 1024.0;

    std::cout << "Memoria:  " << memoriaBytes << " bytes (" << memoriaKB << " KB / " << memoriaMB << " MB)" << std::endl;
    saida << "Memoria:  " << memoriaBytes << " bytes (" << memoriaKB << " KB / " << memoriaMB << " MB)" << std::endl;

    // Remoção
    auto inicioRemocao = std::chrono::high_resolution_clock::now();
    int contRemocoes = 0;
    long long opsRemocao = 0;
    
    while (arquivo >> chave) {
        minhaArvore.remover(chave, opsRemocao);
        contRemocoes++;
    }
    auto fimRemocao = std::chrono::high_resolution_clock::now();
    auto tempoRemocao = std::chrono::duration_cast<std::chrono::milliseconds>(fimRemocao - inicioRemocao).count();

    std::cout << "Remocao:  " << contRemocoes << " chaves em " << tempoRemocao << " ms. (Operacoes: " << opsRemocao << ")" << std::endl;
    saida << "Remocao:  " << contRemocoes << " chaves em " << tempoRemocao << " ms. (Operacoes: " << opsRemocao << ")" << std::endl;

    
    arquivo.close();
}

int main() {
    std::ofstream arquivoSaida("output/resultados_splay.txt");
    if (!arquivoSaida.is_open()) {
        std::cout << "Erro ao criar arquivo de saida na pasta output!" << std::endl;
        return 1;
    }

    std::cout << "Iniciando testes da Arvore Splay" << std::endl;

    executarExperimento("input/dados_teste_splay/tam_10/insercao_aleatoria.txt", arquivoSaida);
    executarExperimento("input/dados_teste_splay/tam_10/insercao_crescente.txt", arquivoSaida);
    executarExperimento("input/dados_teste_splay/tam_10/insercao_decrescente.txt", arquivoSaida);
    executarExperimento("input/dados_teste_splay/tam_10/acesso_uniforme.txt", arquivoSaida);
    executarExperimento("input/dados_teste_splay/tam_10/acesso_localidade.txt", arquivoSaida);

    executarExperimento("input/dados_teste_splay/tam_100/insercao_aleatoria.txt", arquivoSaida);
    executarExperimento("input/dados_teste_splay/tam_100/insercao_crescente.txt", arquivoSaida);
    executarExperimento("input/dados_teste_splay/tam_100/insercao_decrescente.txt", arquivoSaida);
    executarExperimento("input/dados_teste_splay/tam_100/acesso_uniforme.txt", arquivoSaida);
    executarExperimento("input/dados_teste_splay/tam_100/acesso_localidade.txt", arquivoSaida);

    executarExperimento("input/dados_teste_splay/tam_1000/insercao_aleatoria.txt", arquivoSaida);
    executarExperimento("input/dados_teste_splay/tam_1000/insercao_crescente.txt", arquivoSaida);
    executarExperimento("input/dados_teste_splay/tam_1000/insercao_decrescente.txt", arquivoSaida);
    executarExperimento("input/dados_teste_splay/tam_1000/acesso_uniforme.txt", arquivoSaida);
    executarExperimento("input/dados_teste_splay/tam_1000/acesso_localidade.txt", arquivoSaida);

    executarExperimento("input/dados_teste_splay/tam_10000/insercao_aleatoria.txt", arquivoSaida);
    executarExperimento("input/dados_teste_splay/tam_10000/insercao_crescente.txt", arquivoSaida);
    executarExperimento("input/dados_teste_splay/tam_10000/insercao_decrescente.txt", arquivoSaida);
    executarExperimento("input/dados_teste_splay/tam_10000/acesso_uniforme.txt", arquivoSaida);
    executarExperimento("input/dados_teste_splay/tam_10000/acesso_localidade.txt", arquivoSaida);

    executarExperimento("input/dados_teste_splay/tam_100000/insercao_aleatoria.txt", arquivoSaida);
    executarExperimento("input/dados_teste_splay/tam_100000/insercao_crescente.txt", arquivoSaida);
    executarExperimento("input/dados_teste_splay/tam_100000/insercao_decrescente.txt", arquivoSaida);
    executarExperimento("input/dados_teste_splay/tam_100000/acesso_uniforme.txt", arquivoSaida);
    executarExperimento("input/dados_teste_splay/tam_100000/acesso_localidade.txt", arquivoSaida);

    executarExperimento("input/dados_teste_splay/tam_1000000/insercao_aleatoria.txt", arquivoSaida);
    executarExperimento("input/dados_teste_splay/tam_1000000/insercao_crescente.txt", arquivoSaida);
    executarExperimento("input/dados_teste_splay/tam_1000000/insercao_decrescente.txt", arquivoSaida);
    executarExperimento("input/dados_teste_splay/tam_1000000/acesso_uniforme.txt", arquivoSaida);
    executarExperimento("input/dados_teste_splay/tam_1000000/acesso_localidade.txt", arquivoSaida);
    
    arquivoSaida.close();
    std::cout << "\nTestes finalizados. Resultados salvos em 'output/resultados_splay.txt'" << std::endl;
    
    return 0;
}