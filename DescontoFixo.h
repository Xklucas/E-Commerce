#ifndef DESCONTOFIXO_H
#define DESCONTOFIXO_H

#include "Desconto.h"

class DescontoFixo : public Desconto
{
private:
    double percentual;

public:
    DescontoFixo(double pct);
    double calcularDesconto(double total) const override;
};

#endif // DESCONTOFIXO_H
