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
