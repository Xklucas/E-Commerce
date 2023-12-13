#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

#include "Produto.h"
#include "ItemDeCompra.h"
#include "Desconto.h"
#include "DescontoFixo.h"
#include "CarrinhoDeCompra.h"
#include "BancoDadosProdutos.h"
#include "Usuario.h"
#include "UsuarioComum.h"
#include "Admin.h"

// Le a planilha de dados
std::vector<Produto *> lerCSV(const std::string &arquivoCSV)
{
    std::vector<Produto *> produtos;

    std::ifstream arquivo(arquivoCSV);
    if (!arquivo.is_open())
    {
        std::cerr << "Erro ao abrir arquivo." << std::endl;
        return produtos;
    }

    std::string linha;
    getline(arquivo, linha); // Ignora a primeira linha, que contém os cabeçalhos

    while (getline(arquivo, linha))
    {
        std::stringstream ss(linha); // Divide as linhas do arquivo em tokens
        std::string token;

        Produto *produto = new Produto;
        getline(ss, token, ',');
        produto->nome = token;

        getline(ss, token, ',');      // Le cada token da linha ate encontrar virgula
        produto->preco = stod(token); // O valor lido e atribuido ao membro do objeto produto

        getline(ss, token, ',');
        produto->quantidade = stoi(token);

        getline(ss, token, ',');
        produto->categoria = token;

        produtos.push_back(produto);
    }

    arquivo.close();
    return produtos;
}

int main()
{
    // Autenticação do usuário
    std::string usuario, senha;

    std::cout << "Digite seu nome de usuário: ";
    std::cin >> usuario;

    std::cout << "Digite sua senha: ";
    std::cin >> senha;

    // Verifica se o usuário é admin ou usuario comum
    Usuario *usuarioAtual = nullptr;
    if (usuario == "admin" && senha == "admin123")
    {
        std::cout << "Logado como Admin." << std::endl;
        usuarioAtual = new Admin();
    }
    else if (usuario.length() >= 6 && usuario.substr(usuario.length() - 6) == "ufv.br")
    {
        std::cout << "Bem Vindo" << std::endl;
        usuarioAtual = new UsuarioComum();
    }
    else
    {
        std::cout << "Erro: Dominio Invalido." << std::endl;
        return 1; // Fecha o programa se o dominio for invalido
    }

    // Nome do arquivo e local
    std::string caminhoArquivoCSV = "produtos.csv";

    // Armazena em um vetor dinamico de ponteiros objetos de produto
    std::vector<Produto *> produtosOriginais = lerCSV(caminhoArquivoCSV);

    // Inicializando o banco de dados com os produtos do CSV
    BancoDadosProdutos bancoDeDadosProdutos;
    for (const auto &produto : produtosOriginais)
    {
        bancoDeDadosProdutos.adicionarProduto(new Produto(*produto));
    }

    // Exibindo os produtos disponiveis no banco de dados
    std::cout << "Produtos disponiveis :" << std::endl;
    for (const auto &produto : bancoDeDadosProdutos.produtos)
    {
        produto->exibirDetalhes();
    }

    // Exibe as quantidades dos produtos no banco de dados
    for (const auto &produto : bancoDeDadosProdutos.produtos)
    {
        std::cout << produto->nome << ": " << produto->quantidade << std::endl;
    }

    DescontoFixo descontoFixo(0.1);     // 10% de desconto
    Desconto *desconto = &descontoFixo; // Um ponteiro para Desconto
    CarrinhoDeCompra carrinho(desconto, &bancoDeDadosProdutos);

    if (usuarioAtual->isAdmin())
    {
        // Se for admin, apresente as opções de adicionar produtos e sair
        usuarioAtual->adicionarProduto(produtosOriginais, carrinho, bancoDeDadosProdutos);
    }
    else
    {
        // Se for usuário comum, apresente as opções de adicionar e remover produtos
        while (true)
        {
            int escolha;
            std::cout << "\nEscolha uma opção:" << std::endl;
            std::cout << "1. Adicionar produto ao carrinho" << std::endl;
            std::cout << "2. Remover produto do carrinho" << std::endl;
            std::cout << "0. Sair" << std::endl;

            std::cin >> escolha;

            switch (escolha)
            {
            case 0:
                std::cout << "Saindo do processo." << std::endl;
                break;
            case 1:
                usuarioAtual->adicionarProduto(produtosOriginais, carrinho, bancoDeDadosProdutos);
                break;
            case 2:
                usuarioAtual->removerProduto(carrinho);
                break;
            default:
                std::cout << "Opção inválida." << std::endl;
                break;
            }

            if (escolha == 0)
            {
                break;
            }
        }
    }

    // Exibindo informações atualizadas do carrinho e aplicando desconto
    carrinho.calcularTotal();
    carrinho.aplicarDesconto();
    // Exibindo os produtos comprados
    carrinho.exibirProdutosComprados();
    std::cout << std::endl;
    // Atualiza o banco de dados com as quantidades de produtos compradas
    for (const auto &item : carrinho.getItens())
    {
        Produto *produtoComprado = item.getProduto();

        // Encontrar o produto correspondente no banco de dados
        auto it = find_if(bancoDeDadosProdutos.produtos.begin(), bancoDeDadosProdutos.produtos.end(),
                          [produtoComprado](Produto *produtoBD)
                          { return produtoBD->nome == produtoComprado->nome; });

        if (it != bancoDeDadosProdutos.produtos.end())
        {
            // Atualizar a quantidade no banco de dados
            bancoDeDadosProdutos.atualizarQuantidade(*it, -item.getQuantidade());
        }
    }

    for (const auto &item : carrinho.getItens())
    {
        bancoDeDadosProdutos.atualizarQuantidade(item.getProduto(), -item.getQuantidade());
    }
    // Exibe as quantidades dos produtos no banco de dados para o admin
    if (usuario == "admin" && senha == "admin123")
    {
        for (const auto &produto : bancoDeDadosProdutos.produtos)
        {
            std::cout << produto->nome << ": " << produto->quantidade << std::endl;
        }
    }

    // Escrevendo os dados atualizados no arquivo CSV
    bancoDeDadosProdutos.escreverCSV(caminhoArquivoCSV);

    delete usuarioAtual; // Liberar a memória alocada

    return 0;
}
