#include "ob_fiz.h"

// --------------------------------------------------------------------------------------------------------- klasa ob_fiz

ob_fiz::ob_fiz(float px, float py, float kx, float ky, float ks, float kw, std::string adres)
{
    obraz.setPosition(px, py);

    x += kx;
    y += ky;
    szerokosc = ks;
    wysokosc = kw;

    if (adres != "")
    {
        tekstura.loadFromFile(adres);
        obraz.setTexture(tekstura);
    }

    tag = NONE;
}

ob_fiz::~ob_fiz()
{
    ;
}

void ob_fiz::wyrownaj(ob_fiz* ob)
{
    if (czy_kol(this, ob) == true) /// czy szybkosc wplynie mocno na to ????????
    {
        if (x + szerokosc <= ob->x + ob->szerokosc/2)
        {
            x = ob->x - szerokosc;
        }
        else if (x > ob->x + ob->szerokosc/2)
        {
            x = ob->x + ob->szerokosc;
        }

        if (y + wysokosc <= ob->y + ob->wysokosc)
        {
            y = ob->y - wysokosc;
        }
        else if (y > ob->y + ob->wysokosc/2)
        {
            y = ob->y + ob->wysokosc;
        }
    }
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




Kier ob_fiz::getKier()
{
    return kierunek;
}






bool czy_kol(ob_fiz *ob1, ob_fiz *ob2)
{
    if (ob1->x + ob1->szerokosc >= ob2->x && ob1->x <= ob2->x + ob2->szerokosc && ob1->y + ob1->wysokosc >= ob2->y && ob1->y <= ob2->y + ob2->wysokosc)
        return true;
    else
        return false;
}
