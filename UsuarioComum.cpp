#include "UsuarioComum.h"
#include "Produto.h"
#include "CarrinhoDeCompra.h"
#include "BancoDadosProdutos.h"
#include "ItemDeCompra.h"

#include <iostream>
#include <limits>
#include <stdexcept>

void UsuarioComum::adicionarProduto(std::vector<Produto *> &produtos, CarrinhoDeCompra &carrinho, BancoDadosProdutos &bancoDeDados) const
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
            std::cout << std::endl;
            break;
        }

        try
        {
            escolha = std::stoi(entrada);

            if (escolha < 1 || escolha > static_cast<int>(produtos.size()))
            {
                throw std::out_of_range("Opção fora do intervalo.");
            }

            break; // Sai do loop se a entrada for valida
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << "Erro: Entrada inválida. Por favor, digite um número inteiro." << std::endl;
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
        std::cerr << "Erro: Entrada inválida. Por favor, digite um número inteiro." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Quantidade desejada: ";
        std::cin >> quantidade;
    }

    carrinho.adicionarProduto(produtoEscolhido, quantidade);
}
void UsuarioComum::removerProduto(CarrinhoDeCompra &carrinho)
{
    carrinho.exibirProdutosComprados();

    // Solicita ao usuário o número do produto a ser removido
    int numeroProduto;
    std::cout << "Digite o número do produto a ser removido (0 para sair): ";
    std::cin >> numeroProduto;

    if (numeroProduto == 0)
    {
        std::cout << "Operação de remoção de produto cancelada." << std::endl;
        return;
    }

    carrinho.removerProduto(numeroProduto);
}

bool UsuarioComum::isAdmin() const
{
    return false;
}
