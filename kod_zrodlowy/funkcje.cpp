#include "klasy.h"


void wyrownaj(Postac* p, Granica* g)
{
    if (p->kolizje == true)
    {
        if (ob_fiz::czy_kol(p, g))
        {
            switch (g->getKier())
            {
            case gora:
                if (p->predkosc.y <= 0)
                {
                    p->obraz.setPosition(p->obraz.getPosition().x, g->obraz.getPosition().y);
                    p->predkosc.y = 0;
                }
                break;
            case dol:
                if (p->predkosc.y >= 0)
                {
                    p->obraz.setPosition(p->obraz.getPosition().x, g->obraz.getPosition().y - p->wysokosc);
                    p->predkosc.y = 0;
                }
                break;
            case lewo:
                if (p->predkosc.x <= 0)
                {
                    p->obraz.setPosition(g->obraz.getPosition().x, p->obraz.getPosition().y);
                    p->predkosc.x = 0;
                }
                break;
            case prawo:
                if (p->predkosc.x >= 0)
                {
                    p->obraz.setPosition(g->obraz.getPosition().x - p->szerokosc, p->obraz.getPosition().y);
                    p->predkosc.x = 0;
                }
                break;
            }

        }
    }
}

int StrToInt(std::string n)
{
    int l;
    std::istringstream iss(n);
    iss >> l;
    return l;
}

std::string IntToStr(int l)
{
    std::ostringstream ss;
    ss << l;
    return ss.str();
}

/*
bool czy_kol(Player* g, Interaktywne* i)
{
    if (g->x + g->szerokosc >= i->pole_interakcji.left && g->x <= i->pole_interakcji.left + i->pole_interakcji.width
         && g->y + g->wysokosc >= i->pole_interakcji.top && g->y <= i->pole_interakcji.top + i->pole_interakcji.height)
        return true;
    else
        return false;
}*/
