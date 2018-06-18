#include <SFML/Graphics.hpp>
#include <vector>

class ob_fiz  /// klasa bazowa pod inne dzialajace na zasadzie interakcji miedzy soba
{
protected:
    float x, y;
    float szerokosc, wysokosc;
    //int warstwa;

public:
    ob_fiz();
    ~ob_fiz();
    void wyrownaj(ob_fiz*); // wyrownuje obiekt na podstawie drugiego obiektu (kolizja)

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

class Pokoj /// klasa odpowiedzialna za optymalizacje (mniejsze obliczenia)
{
protected:
    std::vector<Interaktywne> interakcje;
    // wstawic pozniej klase postaci (ogolna)

public:
    Pokoj();
    Pokoj(int);
    ~Pokoj();
    void inicjalizacja(Interaktywne);
};
