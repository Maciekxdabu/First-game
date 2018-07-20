#include <SFML/Graphics.hpp>
#include <vector>

enum Tag
{
    mob,
    statyczny,
    interaktywny,
    NONE
};

class ob_fiz  /// klasa bazowa pod inne dzialajace na zasadzie interakcji miedzy soba
{
protected:
    float x, y;
    float szerokosc, wysokosc;
    //int warstwa;
    sf::Vector2f predkosc; /// wektor przechowujacy dane o predkosci w ktora porusza sie obiekt
    int maxx, maxy; /// maksymalne wartosci jakie moze przyjac predkosc (const ???)
    Tag tag; /// przechowuje wartosc tag odrozniajaca obiekty (jak 'm' dla moba, czy 'f' dla obiektu fizycznego)
    sf::Sprite obraz; /// obraz obiektu fizycznego

public:
    ob_fiz();
    ~ob_fiz();
    virtual void wyrownaj(ob_fiz*); // wyrownuje obiekt na podstawie drugiego obiektu (kolizja)
    Tag getTag(); /// zwraca tag
    void addVector(int=0, int=0);
    void ruch();

    friend bool czy_kol(ob_fiz*, ob_fiz*);
};

class Interaktywne :public ob_fiz /// klasa bazowa zwiazana z obiektami interaktywnymi (obsluguje obiekty z ktorymi gracz moze wejsc w interakcje)
{
protected:


public:
    Interaktywne();
    ~Interaktywne();

    friend bool czy_kol(ob_fiz*, ob_fiz*);
};

bool czy_kol(ob_fiz*, ob_fiz*);

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
