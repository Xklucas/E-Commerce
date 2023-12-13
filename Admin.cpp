#include "Admin.h"
#include <iostream>
#include <stdexcept>
#include <limits>
#include <algorithm>
void Admin::adicionarProduto(std::vector<Produto *> &produtos, CarrinhoDeCompra &carrinho, BancoDadosProdutos &bancoDeDados) const
{
    while (true)
    {
        int escolha;
        std::cout << "\nEscolha uma opcão:" << std::endl;
        std::cout << "1. Adicionar produto ao carrinho" << std::endl;
        std::cout << "2. Adicionar produto ao banco de dados" << std::endl;
        std::cout << "0. Sair" << std::endl;

        std::cin >> escolha;

        switch (escolha)
        {
        case 0:
            std::cout << std::endl;
            return;
        case 1:
            adicionarAoCarrinho(produtos, carrinho);
            break;
        case 2:
            adicionarAoBancoDeDados(produtos, bancoDeDados);
            break;
        default:
            std::cout << "Opcao invalida." << std::endl;
            break;
        }
    }
}

bool Admin::isAdmin() const
{
    return true;
}

void Admin::adicionarAoCarrinho(std::vector<Produto *> &produtos, CarrinhoDeCompra &carrinho) const
{
    int escolha;
    std::cout << "\nEscolha um produto para adicionar ao carrinho (0 para sair):" << std::endl;

    for (int i = 0; i < static_cast<int>(produtos.size()); ++i)
    {
        std::cout << i + 1 << ". " << produtos[i]->nome << std::endl;
    }

    while (true)
    {
        std::string entrada;
        std::cin >> entrada;

        if (entrada == "0")
        {
            std::cout << "Saindo do processo de adicao de produtos." << std::endl;
            return;
        }

        try
        {
            escolha = std::stoi(entrada);

            if (escolha < 1 || escolha > static_cast<int>(produtos.size()))
            {
                throw std::out_of_range("Opcao fora do intervalo.");
            }

            break; // Sai do loop se a entrada for válida
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Erro: Entrada invalida. Por favor, digite um numero inteiro." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        catch (const std::out_of_range &e)
        {
            std::cerr << "Erro: " << e.what() << std::endl;
        }
    }

    Produto *produtoEscolhido = produtos[escolha - 1];
    int quantidade;

    std::cout << "Quantidade desejada: ";
    std::cin >> quantidade;

    while (std::cin.fail())
    {
        std::cerr << "Erro: Entrada invalida. Por favor, digite um numero inteiro." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Quantidade desejada: ";
        std::cin >> quantidade;
    }

    carrinho.adicionarProduto(produtoEscolhido, quantidade);
}

void Admin::adicionarAoBancoDeDados(std::vector<Produto *> &produtos, BancoDadosProdutos &bancoDeDados) const
{
    std::string nomeProduto;
    std::cout << "Nome do produto: ";
    std::cin >> nomeProduto;

    // Verificar se o produto já existe no banco de dados
    auto it = std::find_if(bancoDeDados.produtos.begin(), bancoDeDados.produtos.end(),
                           [nomeProduto](Produto *produtoBD)
                           { return produtoBD->nome == nomeProduto; });

    if (it != bancoDeDados.produtos.end())
    {
        // O produto já existe, então adicionamos apenas a quantidade
        int quantidade;
        std::cout << "Quantidade a ser adicionada ao estoque: ";
        std::cin >> quantidade;

        if (std::cin.fail())
        {
            std::cerr << "Erro: Entrada inválida. Por favor, digite um número inteiro." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return;
        }

        (*it)->quantidade += quantidade;
        std::cout << "Quantidade adicionada ao estoque com sucesso." << std::endl;
    }
    else
    {
        // O produto não existe, então adicionamos um novo
        Produto *novoProduto = new Produto;

        try
        {
            novoProduto->nome = nomeProduto;

            std::cout << "Preço do novo produto: ";
            std::cin >> novoProduto->preco;

            if (std::cin.fail())
            {
                throw std::invalid_argument("Entrada inválida. Por favor, digite um número inteiro.");
            }

            std::cout << "Quantidade do novo produto: ";
            std::cin >> novoProduto->quantidade;

            if (std::cin.fail())
            {
                throw std::invalid_argument("Entrada inválida. Por favor, digite um número inteiro.");
            }

            std::cout << "Categoria do novo produto: ";
            std::cin >> novoProduto->categoria;

            bancoDeDados.adicionarProduto(novoProduto);
            produtos.push_back(novoProduto);

            std::cout << "Novo produto adicionado ao carrinho e ao banco de dados." << std::endl;
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Erro: " << e.what() << std::endl;
            delete novoProduto;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

void Admin::removerProduto(CarrinhoDeCompra &carrinho)
{
    
    carrinho.exibirProdutosComprados(); // Exibe produtos antes da remoção

    // Solicita ao usuário o número do produto a ser removido
    int numeroProduto;
    std::cout << "Digite o número do produto a ser removido (0 para sair): ";
    std::cin >> numeroProduto;

    if (numeroProduto == 0)
    {
        std::cout << "Operação de remoção de produto cancelada." << std::endl;
        return;
    }
}
