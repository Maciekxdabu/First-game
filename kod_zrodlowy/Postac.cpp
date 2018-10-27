#include "klasy.h"

Postac::Postac(float px, float py, float kx, float ky, float ks, float kw, std::string adres)
:ob_fiz(px, py, kx, ky, ks, kw, adres)
{
    tag = postac;
    kolizje = true;
}

Postac::~Postac()
{
    ;
}

void Postac::addVector(float xx, float yy)
{
    ob_fiz::addVector(xx*deltaTime.asSeconds(), yy*deltaTime.asSeconds());

    if (predkosc.x >= 0.001)
    {
        predkosc.x -= 0.001;
    }
    else if (predkosc.x <= -0.001)
    {
        predkosc.x += 0.001;
    }
    else
    {
        predkosc.x = 0;
    }
}

void Postac::etheric(bool z)
{
    kolizje = !z;
}

bool Postac::getKol()
{
    return kolizje;
}
