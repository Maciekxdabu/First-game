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
    
    switch (ob->getTag())
    {
    case postac:
        ilosc_postaci++;
        break;
    case interaktywny:
        ilosc_interaktywnych++;
        break;
    case statyczny:
        ilosc_statycznych++;
        break;
    case granica:
        ilosc_granic++;
        break;
    default:
        ilosc_pozostalych++;
        break;
    }
}

sf::Sprite segment::getObraz()
{
    return obraz;
}

int segment::getPos()
{
    return ilosc_postaci;
}

int segment::getStat()
{
    return ilosc_statycznych;
}

int segment::getInt()
{
    return ilosc_interaktywnych;
}

int segment::getPoz()
{
    return ilosc_pozostalych;
}

int segment::getGran()
{
    return ilosc_granic;
}
