#include "segment.h"

segment::segment()
{
    ;
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

int segment::getIloscMob()
{
    return moby.getLenght();
}

int segment::getMob(int n)
{
    return moby[n];
}

int segment::getIloscPoz()
{
    return pozostale.getLenght();
}

int segment::getPoz(int n)
{
    return pozostale[n];
}

void segment::dodaj(ob_fiz* ob)
{
    zawartosc.push_back(ob);
    switch (ob->getTag())
    {
    case 'm':
        moby.push_back(ob);
        break;
    default:
        pozostale.push_back(ob);
    }
}
