#include "ob_fiz.h"

class segment
{
public:
    static int width;
    static int height;

protected:
    std::vector<ob_fiz*> zawartosc; /// zbior elementow w segmencie mapy
    std::vector<ob_fiz*> moby;
    std::vector<ob_fiz*> pozostale;
    bool czy_zawiera; /// czy segment jest czescia mapy

public:
    segment();
    ~segment();
    int getIlosc(); /// zwraca ilosc elementow w segmencie mapy
    ob_fiz* getObiekt(int); /// zwraca obiekt o podanym indeksie
    int getIloscMob(); /// zwraca ilosc mobow w segmencie mapy
    ob_fiz* getMob(int); /// zwraca moba o podanym indeksie
    int getIloscPoz(); /// zwraca ilosc pozostalych w segmencie mapy
    ob_fiz* getPoz(int); /// zwraca pozostaly o podanym indeksie

    void dodaj(ob_fiz*); /// dodaje nowy element z segmentu
    void usun(); /// usuwa element z segmentu ---TO DO---
};

int segment::width = 100;
int segment::height = 100;
