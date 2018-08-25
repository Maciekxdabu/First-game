#include "klasy.h"

Granica::Granica(float px, float py, float kx, float ky, float ks, float kw, std::string adres, Kier k)
:ob_fiz(px, py, kx, ky, ks, kw, adres)
{
    tag = granica;
    kierunek = k;
}

Granica::~Granica()
{
    ;
}

Kier Granica::getKier()
{
    return kierunek;
}
