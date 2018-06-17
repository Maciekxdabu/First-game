#include <SFML/Graphics.hpp>

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

bool czy_kol(ob_fiz*, ob_fiz*);
