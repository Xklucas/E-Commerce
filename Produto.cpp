#include "Produto.h"
#include "ItemDeCompra.h"

void Produto::adicionarAoCarrinho(int quantidade, std::vector<ItemDeCompra> &carrinho)
{
    if (quantidade > 0 && quantidade <= this->quantidade)
    {
        this->quantidade -= quantidade;
        std::cout << quantidade << " " << nome << "(s) adicionado(s) ao carrinho." << std::endl;
    }
    else
    {
        std::cout << "Quantidade indisponível no banco de dados para " << nome << "." << std::endl;
    }
}

void Produto::exibirDetalhes() const
{
    std::cout << "Detalhes do Produto - Nome: " << nome << ", Preço: " << preco << std::endl;
}
