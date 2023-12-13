#ifndef BANCODADOSPRODUTOS_H
#define BANCODADOSPRODUTOS_H

#include <vector>
#include "Produto.h"

class BancoDadosProdutos
{
public:
    std::vector<Produto *> produtos;

    void adicionarProduto(Produto *p);
    void atualizarQuantidade(Produto *p, int quantidade);
    void escreverCSV(const std::string &arquivoCSV);
    void removerProduto(Produto *p);
    ~BancoDadosProdutos();
};

#endif // BANCODADOSPRODUTOS_H
