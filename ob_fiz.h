#include <SFML/Graphics.hpp>
#include <vector>

/*
    klasa bazowa pod inne działające na zasadzie interakcji między sobą
    klasy dziedziczące będą mogły dzięki polimorfi sprawdzić kolizję dzięki funkcji czy_kol() poniżej
    zarówno do kolizji fizycznych (np. żeby nie wypaść za mapę)
        lub interaktywnych (jak wykrywanie obrażeń, interakcji, 
        w skrócie czy gracz jest w odpowiednim miejscu do jakiegoś warunku zdarzenia w grze)
*/
class ob_fiz
{
protected:
    float x, y;
    float szerokosc, wysokosc;
    //int warstwa;

public:
    ob_fiz();
    ~ob_fiz();
    void wyrownaj(ob_fiz*); // wyrownuje obiekt na podstawie drugiego obiektu (kolizja fizyczna)

    friend bool czy_kol(ob_fiz*, ob_fiz*);
};

/*
    klasa bazowa zwiazana z obiektami interaktywnymi (obsluguje obiekty z ktorymi gracz moze wejsc w interakcje)
    dziedziczy wykrywanie kolizji po ob_fiz
*/
class Interaktywne :public ob_fiz
{
protected:


public:
    Interaktywne();
    ~Interaktywne();
    /*
        funkcja do dziedziczenia (potomki będą miały własną interpretację, czyli własną interakcję)
        np. jedne drzwi przenoszą do drugiej w swojej parze, a drabina wprowadza w stan wchodzenia po niej
        najczęściej funkcja wywoływana po naciśnięciu klawisza np. "E"
    */
    virtual void interakcja();

    friend bool czy_kol(ob_fiz*, ob_fiz*);
};

bool czy_kol(ob_fiz*, ob_fiz*); /// funkcja sprawdzająca kolizję dla potomków ob_fiz

/*
    klasa odpowiedzialna za optymalizacje (mniejsze obliczenia)
    obiekty tej klasy przetrzymują przedmioty i stworzenia aktualnie znajdujące się w danym "pokoju"
*/
class Pokoj
{
protected:
    std::vector<Interaktywne> interakcje;
    // wstawic pozniej klase postaci (ogolna, do polimorfi)

public:
    Pokoj();
    Pokoj(int);
    ~Pokoj();
    void inicjalizacja(Interaktywne); /// funkcja dodająca obiekty do pokoju dla obliczeń (później z innymi argumentami)
};
