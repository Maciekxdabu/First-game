#include "ob_fiz.h"
#include <fstream>

using namespace std;

int segment::width = 400;
int segment::height = 400;

vector<segment*> mapa;
string nazwa_mapy="";

int main()
{   
    sf::RenderWindow okno(sf::VideoMode(500, 500, 32), "Gra");
    
// ---------------------------------------------------------------------------------------------------- wczytywanie mapy

    fstream plik;
    plik.open("mapa_pierwsza.txt", ios::in);

    getline(plik, nazwa_mapy);

    int segmentow;
    plik >> segmentow;

    for (int i=0; i<segmentow; i++)
    {
        int x, y;
        string adres;
        plik >> x;
        plik >> y;
        plik >> adres;
        mapa.push_back(new segment(adres, x, y));
    }

    plik.close();

// --------------------------------------------------------------------------------------------------- poczatek petli okna

    while (okno.isOpen())
    {
        sf::Event zdarzenie;
        while (okno.pollEvent(zdarzenie))
        {
            if (zdarzenie.type == sf::Event::Closed)
            {
                okno.close();
            }
            
            if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key == sf::Keyboard::E) /// zdarzenie wykrywajace interakcje
            {
                ;
            }
        }

        okno.clear(sf::Color::White);
        
        for (int i=0; i<mapa.size(); i++)
            okno.draw(mapa[i]->getObraz());

        okno.display();
    }

    return 0;
}
