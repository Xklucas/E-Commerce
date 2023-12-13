#include "DescontoFixo.h"

DescontoFixo::DescontoFixo(double pct) : percentual(pct) {}

double DescontoFixo::calcularDesconto(double total) const
{
    return total - (total * percentual);
}
