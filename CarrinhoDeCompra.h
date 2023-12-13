#ifndef CARRINHODECOMPRA_H
#define CARRINHODECOMPRA_H

#include <vector>
#include "ItemDeCompra.h"
#include "BancoDadosProdutos.h"
#include "Desconto.h"
class Usuario;

class CarrinhoDeCompra
{
private:
    std::vector<ItemDeCompra> itens;
    Desconto *desconto;
    BancoDadosProdutos *bancoDeDados;

public:
    CarrinhoDeCompra(Desconto *desc);
    CarrinhoDeCompra(Desconto *desc, BancoDadosProdutos *bd);
    void adicionarProduto(Produto *p, int quantidade);
    void exibirProdutosComprados() const;
    const std::vector<ItemDeCompra> &getItens() const;
    void removerProduto(int numeroProduto);
    void calcularTotal();
    void aplicarDesconto();

    ~CarrinhoDeCompra();
};

#endif // CARRINHODECOMPRA_H
