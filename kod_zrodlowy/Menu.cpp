#include "klasy.h"

Menu_class::Menu_class()
{
    wybrane = 0;
    maksymalne = 4;
    aktualne = glowne;

    obraz.setPosition(0,0);
    plotno.create(1000, 1000);

    gl[0] = "Kontynuuj";
    gl[1] = "Wczytaj";
    gl[2] = "Zapisz";
    gl[3] = "Wyjdz";

    tekst.setFont(czcionka);
    tekst.setCharacterSize(30);
    tekst.setPosition(100, 500);

    reload();
}

Menu_class::~Menu_class()
{
    ;
}

sf::Sprite Menu_class::getObraz()
{
    return obraz;
}

void Menu_class::reload()
{
    plotno.clear(sf::Color(0, 0, 0, 100));

    switch (aktualne)
    {
    case glowne:
        for (int n=0; n<4; n++)
        {
            tekst.setString(gl[n]);
            if (wybrane == n)
                tekst.setFillColor(sf::Color::Green);
            else
                tekst.setFillColor(sf::Color::White);
            plotno.draw(tekst);
            tekst.move(0, 30);
        }
        tekst.move(0, -120);
        break;
    }

    plotno.display();

    obraz.setTexture(plotno.getTexture());
}

void Menu_class::w_gore()
{
    wybrane--;
    if (wybrane == -1)
        wybrane = maksymalne - 1;

    reload();
}

void Menu_class::w_dol()
{
    wybrane++;
    if (wybrane == maksymalne)
        wybrane = 0;

    reload();
}

int Menu_class::getWybrane()
{
    return wybrane;
}

void Menu_class::zmien(okienko m)
{
    aktualne = m;

    switch (m)
    {
    case glowne:
        maksymalne = 4;
        break;
    }
    wybrane = 0;
}

okienko Menu_class::getTyp()
{
    return aktualne;
}
