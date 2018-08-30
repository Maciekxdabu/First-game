#include "klasy.h"
#include <fstream>

using namespace std;

Player bohater(100, 500, 0, 0, 100, 100, "img/gracz.png", 1);

int segment::width = 400;
int segment::height = 400;

int ob_fiz::maxID = 0;

int segmentow;
int laczen;

vector<segment*> mapa;
string nazwa_mapy="";

slownik<Tag> typ;
slownik<Granica*> granice;
slownik<Postac*> postacie;
slownik<Interaktywne*> interaktywne;


vector<int> lacz1, lacz2;

sf::View widok_G(sf::Vector2f(100, 500), sf::Vector2f(1000, 1000));
sf::RenderWindow okno(sf::VideoMode(1000, 1000, 32), "Gra");

// --------------------------------------------------------------------------------------------------------- funkcja main

int main()
{
    okno.setView(widok_G);

// --------------------------------------------------------------------------------------------------------- wczytywanie mapy

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
    postacie.dodaj(bohater.getID(), &bohater);
    typ.dodaj(bohater.getID(), bohater.getTag());

    Granica podloga(3, 797, 0, 0, 797, 0, "", dol);

    mapa[1]->dodaj(&podloga);
    granice.dodaj(podloga.getID(), &podloga);
    typ.dodaj(podloga.getID(), podloga.getTag());

    Granica sciana1(3, 397, 0, 0, 0, 397, "", lewo);

    mapa[1]->dodaj(&sciana1);
    granice.dodaj(sciana1.getID(), &sciana1);
    typ.dodaj(sciana1.getID(), sciana1.getTag());

    Granica sciana2(797, 397, 0, 0, 0, 397, "", prawo);

    mapa[2]->dodaj(&sciana2);
    granice.dodaj(sciana2.getID(), &sciana2);
    typ.dodaj(sciana2.getID(), sciana2.getTag());

    Drzwi drzwi1(50, 600, 0, 0, 100, 200, "img/drzwi.png", 550, 650);

    mapa[1]->dodaj(&drzwi1);
    interaktywne.dodaj(drzwi1.getID(), &drzwi1);
    typ.dodaj(drzwi1.getID(), drzwi1.getTag());

    Drzwi drzwi2(500, 600, 0, 0, 100, 200, "img/drzwi.png", 100, 650);

    mapa[2]->dodaj(&drzwi2);
    interaktywne.dodaj(drzwi2.getID(), &drzwi2);
    typ.dodaj(drzwi2.getID(), drzwi2.getTag());

// ----------------------------------------------------------------------------------------------------------------------------------------------------------------- poczatek petli okna

    while (okno.isOpen())
    {
        sf::Event zdarzenie;
        while (okno.pollEvent(zdarzenie))
        {
            if (zdarzenie.type == sf::Event::Closed)
            {
                okno.close();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) /// zdarzenie wykonujace mozliwa interakcje interakcje
            {
                int inter = bohater.getInt();
                if (inter != -1)
                {
                    interaktywne[inter]->interakcja();
                }
            }

// --------------------------------------------------------------------------------------------------------- sterowanie postacia

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                bohater.addVector(0.1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                bohater.addVector(-0.1);
            }
        }

// --------------------------------------------------------------------------------------------------------- grawitacja obiektow

        bohater.addVector(0, 0.0025);

// --------------------------------------------------------------------------------------------------------- sprawdzanie kolizji

//wyrownaj(postacie[ mapa[lacz1[i]]->getObiekt(j, postac) ], granice[ mapa[lacz1[i]]->getObiekt(k, granica) ]);

        for (int i=0; i<laczen; i++)
        {
            for (int j=0; j<mapa[lacz1[i]]->getPos(); j++)
            {
                for (int k=0; k<mapa[lacz1[i]]->getGran(); k++)
                {
                    wyrownaj(postacie[ mapa[lacz1[i]]->getObiekt(j, postac) ], granice[ mapa[lacz1[i]]->getObiekt(k, granica) ]);
                }
                for (int k=0; k<mapa[lacz2[i]]->getGran(); k++)
                {
                    wyrownaj(postacie[ mapa[lacz1[i]]->getObiekt(j, postac) ], granice[ mapa[lacz2[i]]->getObiekt(k, granica) ]);
                }
            }

            for (int j=0; j<mapa[lacz2[i]]->getPos(); j++)
            {
                for (int k=0; k<mapa[lacz1[i]]->getGran(); k++)
                {
                    wyrownaj(postacie[ mapa[lacz2[i]]->getObiekt(j, postac) ], granice[ mapa[lacz1[i]]->getObiekt(k, granica) ]);
                }
                for (int k=0; k<mapa[lacz2[i]]->getGran(); k++)
                {
                    wyrownaj(postacie[ mapa[lacz2[i]]->getObiekt(j, postac) ], granice[ mapa[lacz2[i]]->getObiekt(k, granica) ]);
                }
            }
        }

// --------------------------------------------------------------------------------------------------------- ruch obiektow

        bohater.ruch();

// --------------------------------------------------------------------------------------------------------- sprawdzanie interakcji

        bohater.reset();

        int s = bohater.getSegment();

        for (int i=0; i<mapa[s]->getInt(); i++)
        {
            bohater.czy_interakcja(interaktywne[ mapa[s]->getObiekt(i, interaktywny) ]);
        }

        for (int i=0; i<laczen; i++)
        {
            if (lacz1[i] == s)
            {
                for (int j=0; j<mapa[lacz2[i]]->getInt(); j++)
                {
                    bohater.czy_interakcja(interaktywne[ mapa[lacz2[i]]->getObiekt(j, interaktywny) ]);
                }
            }
            else if (lacz2[i] == s)
            {
                for (int j=0; j<mapa[lacz1[i]]->getInt(); j++)
                {
                    bohater.czy_interakcja(interaktywne[ mapa[lacz1[i]]->getObiekt(j, interaktywny) ]);
                }
            }
        }

// --------------------------------------------------------------------------------------------------------- odswierzenie okna

        okno.clear(sf::Color::Black);

        for (int i=0; i<mapa.size(); i++)
            okno.draw(mapa[i]->getObraz());

        okno.draw(drzwi1.getObraz());
        okno.draw(drzwi2.getObraz());

        okno.draw(bohater.getObraz());

        //for (int i=0; i<interaktywne.ilosc(); i++)
            //okno.draw(interaktywne[])

        okno.display();
    }

// ---------------------------------------------------------------------------------------------------------- koniec programu (po zamknieciu okna)

    return 0;
}
