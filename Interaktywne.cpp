#include "klasy.h"

Interaktywne::Interaktywne(float px, float py, float kx, float ky, float ks, float kw, std::string adres)
:ob_fiz(px, py, kx, ky, ks, kw, adres)
{
    tag = interaktywny;
}

Interaktywne::~Interaktywne()
{
    ;
}

// ----------------------------------------------------------------------- Drzwi

Drzwi::Drzwi(float px, float py, float kx, float ky, float ks, float kw, std::string adres, float xx, float yy)
:Interaktywne(px, py, kx, ky, ks, kw, adres)
{
    cel = sf::Vector2f(xx, yy);
}

Drzwi::~Drzwi()
{
    ;
}

void Drzwi::interakcja()
{
    bohater.teleportacja(cel.x, cel.y);
}
