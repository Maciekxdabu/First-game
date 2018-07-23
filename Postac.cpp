#include "klasy.h"

Postac::Postac(float px, float py, float kx, float ky, float ks, float kw, std::string adres)
:ob_fiz(px, py, kx, ky, ks, kw, adres)
{
    ;
}

Postac::~Postac()
{
    ;
}

void Postac::wyrownaj(Granica ob)
{
    if (czy_kol(this, &ob))
    {
        switch (ob.getKier())
        {
        case gora:
            if (ob.getSpeed().y <= 0)
            {
                obraz.setPosition(obraz.getPosition().x, ob.getPos().y);
                predkosc.y = 0;
            }
            break;
        case dol:
            if (ob.getSpeed().y >= 0)
            {
                obraz.setPosition(obraz.getPosition().x, ob.getPos().y - wysokosc);
                predkosc.y = 0;
            }
            break;
        case lewo:
            if (ob.getSpeed().x <= 0)
            {
                obraz.setPosition(ob.getPos().x, obraz.getPosition().y);
                predkosc.x = 0;
            }
            break;
        case prawo:
            if (ob.getSpeed().x >= 0)
            {
                obraz.setPosition(ob.getPos().x - szerokosc, obraz.getPosition().y);
                predkosc.x = 0;
            }
            break;
        }

    }
}
