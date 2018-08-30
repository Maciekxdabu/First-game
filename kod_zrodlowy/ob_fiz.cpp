#include "klasy.h"

// --------------------------------------------------------------------------------------------------------- klasa ob_fiz

ob_fiz::ob_fiz(float px, float py, float kx, float ky, float ks, float kw, std::string adres)
{
    obraz.setPosition(px, py);

    x = px + kx;
    y = py + ky;
    szerokosc = ks;
    wysokosc = kw;
    
    maxx = 0;
    maxy = 0;

    if (adres != "")
    {
        tekstura.loadFromFile(adres);
        obraz.setTexture(tekstura);
    }

    //tag = NONE;
    
    ID = maxID;
    maxID++;
}

ob_fiz::~ob_fiz()
{
    ;
}

Tag ob_fiz::getTag()
{
    return tag;
}

void ob_fiz::addVector(float xx, float yy)
{
    predkosc.x += xx;
    if (predkosc.x > maxx)
        predkosc.x = maxx;
    else if (predkosc.x < maxx*-1)
        predkosc.x = maxx*-1;

    predkosc.y += yy;
    if (predkosc.y > maxy)
        predkosc.y = maxy;
    else if (predkosc.y < maxy*-1)
        predkosc.y = maxy*-1;
}

void ob_fiz::ruch()
{
    obraz.move(predkosc);
    x += predkosc.x;
    y += predkosc.y;
}

sf::Vector2f ob_fiz::getSpeed()
{
    return predkosc;
}

sf::Vector2f ob_fiz::getPos()
{
    return obraz.getPosition();
}

sf::Sprite ob_fiz::getObraz()
{
    return obraz;
}

int ob_fiz::getID()
{
    return ID;
}

sf::Vector2f ob_fiz::getKolPos()
{
    return sf::Vector2f(x, y);
}

sf::Vector2f ob_fiz::getWym()
{
    return sf::Vector2f(szerokosc, wysokosc);
}







/*
bool czy_kol(ob_fiz *ob1, ob_fiz *ob2)
{
    if (ob1->x + ob1->szerokosc >= ob2->x && ob1->x <= ob2->x + ob2->szerokosc && ob1->y + ob1->wysokosc >= ob2->y && ob1->y <= ob2->y + ob2->wysokosc)
        return true;
    else
        return false;
}*/


bool ob_fiz::czy_kol(ob_fiz *ob1, ob_fiz *ob2)
{
    sf::Vector2f wym1 = ob1->getWym();
    sf::Vector2f wym2 = ob2->getWym();
    sf::Vector2f kol1 = ob1->getKolPos();
    sf::Vector2f kol2 = ob2->getKolPos();

    if (kol1.x + wym1.x >= kol2.x && kol1.x <= kol2.x + wym2.x && kol1.y + wym1.y >= kol2.y && kol1.y <= kol2.y + wym2.y)
        return true;
    else
        return false;
}
