#include "ob_fiz.h"
#include <fstream>

using namespace std;

Player bohater(100, 500, 0, 0, 100, 100, "img/gracz.png");

int segment::width = 400;
int segment::height = 400;

int segmentow;
int laczen;

vector<segment*> mapa;
string nazwa_mapy="";

vector<int> lacz1, lacz2;

int main()
{   
    sf::RenderWindow okno(sf::VideoMode(500, 500, 32), "Gra");
    
// ---------------------------------------------------------------------------------------------------- wczytywanie mapy

    fstream plik;
    plik.open("mapa_pierwsza.txt", ios::in);

    getline(plik, nazwa_mapy);

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
    
    plik >> laczen;

    for (int i=0; i<laczen; i++)
    {
        int p, d;
        plik >> p;
        plik >> d;
        lacz1.push_back(p);
        lacz2.push_back(d);
    }

    plik.close();
    
    mapa[1]->dodaj(&bohater);

    Granica podloga(3, 797, 0, 0, 397, 0, "", dol);

    mapa[1]->dodaj(&podloga);

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
        
// --------------------------------------------------------------------------------------------------------- grawitacja obiektow

    bohater.addVector(0, 0.0025);

// --------------------------------------------------------------------------------------------------------- sprawdzanie kolizji

    for (int i=0; i<laczen; i++)
    {
        int postaci = mapa[lacz1[i]]->getPos();
        for (int j=0; j<postaci; j++)
        {
            int gran = mapa[lacz1[i]]->getGran();
            for (int k=0; k<gran; k++)
            {
                ;
            }
            gran = mapa[lacz2[i]]->getGran();
            for (int k=0; k<gran; k++)
            {
                ;
            }
        }

        postaci = mapa[lacz2[i]]->getPos();
        for (int j=0; j<postaci; j++)
        {
            int gran = mapa[lacz1[i]]->getGran();
            for (int k=0; k<gran; k++)
            {
                ;
            }
            gran = mapa[lacz2[i]]->getGran();
            for (int k=0; k<gran; k++)
            {
                ;
            }
        }
    }

// --------------------------------------------------------------------------------------------------------- ruch obiektow

    bohater.ruch();

// --------------------------------------------------------------------------------------------------------- odswierzenie okna

        okno.clear(sf::Color::Black);
        
        for (int i=0; i<mapa.size(); i++)
            okno.draw(mapa[i]->getObraz());
        
        okno.draw(bohater.getObraz());

        okno.display();
    }

    // ---------------------------------------------------------------------------------------------------------- koniec programu (po zamknieciu okna)
    
    return 0;
}
