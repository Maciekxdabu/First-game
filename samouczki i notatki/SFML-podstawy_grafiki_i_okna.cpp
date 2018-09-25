#include <iostream>
#include <SFML/Graphics.hpp> /// naglowek dodaje do programu funkcje graficzne SFMLa

using namespace std;

// w podanych obiektach tworze kolejno:
sf::RenderWindow okno; /// obiekt okna
sf::Texture tekstura; /// teksture/grafike
sf::Sprite obrazek; /// obrazek do wyswietlania w oknie
sf::Font czcionka; /// obiekt czcionki
sf::Text tekst; /// pole tekstowe

// --------------------------------------------------------------------------------------------------------------------------------------------------------- funkcja main

int main()
{
    // ustawiam poczatkowe wartosci:

    ///dla okna
    okno.create(sf::VideoMode(200, 200, 32), "Samouczek"); /// tworzy okno o rozmiarach 200x200 z 32 bitowa glebia kolorow i napisem "Samouczek" na pasku okna
    ///mozna tez po prostu napisac:
//  sf::RenderWindow okno(sf::VideoMode(200, 200, 32), "Samouczek");
    ///czyli przy tworzeniu obiektu

    ///dla tekstury:
    if (!tekstura.loadFromFile("adres_tekstury")) /// wczytuje teksture z pliku i przy okazji sprawdzam czy istnieje, bowiem funkcja zwraca bool
        return 0;

    ///dla obrazka;
    obrazek.setTexture(tekstura); /// ustawiam teksture dla obrazka (uwaga: obrazek zapisuje adres do tekstury wiec musi na istniec w pamieci RAM zeby nam sie wyswietlal poprawnie)

    /// czcionki:
    if (!czcionka.loadFromFile("adres_czcionki")) /// wczytuje czcionke z pliku i przy okazji sprawdzam czy istnieje, bowiem funkcja zwraca bool
        return 0;

    ///dla pola tekstowego:
    tekst.setFont(czcionka); /// ustawiam czcionke
    tekst.setString("xxxxx"); /// ustawiam napis w polu na "xxxxx"
    tekst.setCharacterSize(32); /// ustawiam wielkosc czcionki (opcjonalne)
    tekst.setFillColor(sf::Color::Black); /// ustawiam kolor czcionki na czarny (opcjonalne)


    //ustaiwam pozycje obiektow:
    obrazek.setPosition(10, 30); ///obrazka na x:10 i y:30
    tekst.setPosition(30, 10); ///pola tekstowego na x:30 i y:10
    //UWAGA:
    //w programach okienkowych wspolrzedne okreslamy wzgledem LEWEGO GORNEGO rogu okna
    // x rosna w prawo x-->
    // y rosna w dol y (czyli odwrotnie niz normalnie)
    //               |
    //               |
    //              \ /

// --------------------------------------------------------------------------------------------------------------------------------------------------------- glowna petla okna

    while (okno.isOpen()) /// petla (a przez to program) dziala dopoki okno jest otwarte (to chyba oczywiste) --- jedno przejscie przez ta petle to jedna klatka programu
    {
        sf::Event zdarzenie; /// tworze zmienna przechowujaca zdarzenia
        while (okno.pollEvent(zdarzenie)) /// petla sprawdza wszystkie zdarzenia ktore wydarzyly sie w danej klatce programu
        {
            if (zdarzenie.type == sf::Event::Closed) /// jezeli nastapila proba zamkniecia okna (przez np. roznorodne 'X')
            {
                okno.close(); /// zamyka okno, a przez to petle i w koncu program --- mozna tu jeszcze dac ostateczne zapytanie "Czy na pewno chcesz wyjsc?" przed konkretnym zamknieciem
            }
        }

        okno.clear(sf::Color::White); /// czysci okno pojedynczym kolorem (w tym przypadku bialym)

        // rysuje kolejno:
        okno.draw(obrazek); /// obrazek
        okno.draw(tekst); /// pole tekstowe

        okno.display(); /// wyswietlam to co zostalo narysowane na oknie dla uzytkownika
    }

    return 0;
}
