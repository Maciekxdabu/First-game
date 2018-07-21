#include "segment.h"

segment::segment(std::string adres_obrazu, int xx, int yy)
{
    tekstura.loadFromFile(adres_obrazu);
    obraz.setTexture(tekstura);
    obraz.setPosition(xx*width, yy*height);
    x = xx;
    y = yy;
}

segment::~segment()
{
    ;
}

int segment::getIlosc()
{
    return zawartosc.getLenght();
}

int segment::getObiekt(int n)
{
    return zawartosc[n];
}

void segment::dodaj(ob_fiz* ob)
{
    zawartosc.push_back(ob);
}

sf::Sprite segment::getObraz()
{
    return obraz;
}
