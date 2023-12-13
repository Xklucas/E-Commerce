#ifndef USUARIO_H
#define USUARIO_H

#include <vector>
#include "Produto.h"
#include "CarrinhoDeCompra.h"
#include "BancoDadosProdutos.h"

class Usuario
{
public:
    virtual void adicionarProduto(std::vector<Produto *> &produtos, CarrinhoDeCompra &carrinho, BancoDadosProdutos &bancoDeDados) const = 0;
    virtual bool isAdmin() const = 0;
    virtual void removerProduto(CarrinhoDeCompra &carrinho) = 0;
    virtual ~Usuario();
};

#endif
