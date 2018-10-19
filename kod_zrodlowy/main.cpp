#include "klasy.h"
#include <fstream>
#include <windows.h>

using namespace std;

Player bohater(100, 500, 0, 0, 100, 100, "img/gracz.png", 1);

int segment::width = 400;
int segment::height = 400;

int ob_fiz::maxID = 0;

int segmentow;
int laczen;

vector<segment*> mapa;
int szer, wys;
int **wspolrzedne;
string nazwa_mapy="";

/*
map<char, Tag> typ;
map<char, Granica*> granice;
map<char, Postac*> postacie;
map<char, Interaktywne*> interaktywne;
*/

slownik<Tag> typ;
slownik<Granica*> granice;
slownik<Postac*> postacie;
slownik<Interaktywne*> interaktywne;


vector<int> lacz1, lacz2;

sf::View widok_G(sf::Vector2f(100, 500), sf::Vector2f(1000, 1000));
sf::RenderWindow okno(sf::VideoMode(1000, 1000, 32), "Gra");

sf::Font czcionka;

bool is_pause_on = false;

// --------------------------------------------------------------------------------------------------------- funkcja main

int main()
{
    okno.setView(widok_G);

    czcionka.loadFromFile("arial.ttf");

    GUI_class GUI(50, 100);
    Menu_class Menu;

// --------------------------------------------------------------------------------------------------------- wczytywanie mapy

    fstream plik;
    plik.open("mapa_pierwsza.txt", ios::in);

    getline(plik, nazwa_mapy);

    plik >> szer >> wys;
    wspolrzedne = new int*[szer];
    for (int i=0; i<szer; i++)
        wspolrzedne[i] = new int[wys];
    for (int i=0; i<szer; i++)
    {
        for (int j=0; j<wys; j++)
            wspolrzedne[i][j] = -1;
    }

    plik >> segmentow;

    for (int i=0; i<segmentow; i++) /// wczytywanie segmentow
    {
        int x, y;
        string adres;
        plik >> x;
        plik >> y;
        plik >> adres;
        mapa.push_back(new segment(adres, x, y));
        wspolrzedne[x][y] = mapa.size()-1;
    }

    plik >> laczen;

    for (int i=0; i<laczen; i++) /// wczytywanie laczen
    {
        int p, d;
        plik >> p;
        plik >> d;
        lacz1.push_back(p);
        lacz2.push_back(d);
    }

    for (int i=0; i<segmentow; i++) /// wczytywanie obiektow
    {
        int obiektow;
        plik >> obiektow;
        for (int j=0; j<obiektow; j++)
        {
            Tag typ_obiektu;
            int b;
            plik >> b;
            typ_obiektu = (Tag)b;

            switch (typ_obiektu)
            {
            case granica:
                {
                    sf::Vector2f polozenie;
                    int dlugosc;
                    Kier kierunek;
                    plik >> polozenie.x;
                    plik >> polozenie.y;
                    plik >> dlugosc;
                    plik >> b;
                    kierunek = (Kier)b;

                    Granica *bufor;
                    if (kierunek == gora || kierunek == dol)
                        bufor = new Granica(polozenie.x, polozenie.y, 0, 0, dlugosc, 0, "", kierunek);
                    else
                        bufor = new Granica(polozenie.x, polozenie.y, 0, 0, 0, dlugosc, "", kierunek);

                    mapa[i]->dodaj(bufor);
                    granice.dodaj(bufor->getID(), bufor);
                    typ.dodaj(bufor->getID(), granica);

                    break;
                }
            /*case postac:
                Postac *bufor = new Postac();

                break;*/
            case interaktywny:
                {
                    sf::Vector2f polozenie, cel;
                    std::string adres;
                    plik >> polozenie.x >> polozenie.y;
                    plik >> cel.x >> cel.y;
                    plik >> adres;
                    //cout << adres << endl;

                    Drzwi *bufor;

                    bufor = new Drzwi(polozenie.x, polozenie.y, 0, 0, 100, 200, adres, cel.x, cel.y);

                    mapa[i]->dodaj(bufor);
                    interaktywne.dodaj(bufor->getID(), bufor);
                    typ.dodaj(bufor->getID(), interaktywny);

                    break;
                }
            }
        }
    }

    plik.close();

    mapa[1]->dodaj(&bohater);
    postacie.dodaj(bohater.getID(), &bohater);
    typ.dodaj(bohater.getID(), bohater.getTag());

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

// --------------------------------------------------------------------------------------------------------- manu pauzy

            if (zdarzenie.type == sf::Event::KeyPressed && zdarzenie.key.code == sf::Keyboard::Escape)
            {
                is_pause_on = true;
                //okno.setView(okno.getDefaultView());
                //okno.draw(Menu.getObraz());
                //okno.setView(widok_G);
                //okno.display();
                while (is_pause_on == true)
                {
                    while (okno.pollEvent(zdarzenie))
                    {
                        ;

                        if (zdarzenie.type == sf::Event::KeyPressed)
                        {
                            if (zdarzenie.key.code == sf::Keyboard::Escape)
                            {
                                is_pause_on = false;
                                break;
                            }

                            if (zdarzenie.key.code == sf::Keyboard::Down)
                                Menu.w_dol();
                            if (zdarzenie.key.code == sf::Keyboard::Up)
                                Menu.w_gore();

                            if (zdarzenie.key.code == sf::Keyboard::Return) /// Enter
                            {
                                switch (Menu.getTyp())
                                {
                                case glowne:
                                    switch (Menu.getWybrane())
                                    {
                                    case 0:
                                        is_pause_on = false;
                                        break;
                                    case 3:
                                        return 0;
                                        break;
                                    }
                                    break;
                                }
                            }
                        }
                    }

                    okno.clear(sf::Color::White);

                    for (int i=0; i<mapa.size(); i++)
                        okno.draw(mapa[i]->getObraz());

                    for (int i=0; i<mapa.size(); i++)
                    {
                        for (int j=0; j<mapa[i]->getInt(); j++)
                            okno.draw( interaktywne[mapa[i]->getObiekt(j, interaktywny)]->getObraz() );
                    }

                    //okno.draw(drzwi1.getObraz());
                    //okno.draw(drzwi2.getObraz());

                    okno.draw(bohater.getObraz());

                    okno.setView(okno.getDefaultView());
                    okno.draw(GUI.getObraz());
                    okno.draw(Menu.getObraz());
                    okno.setView(widok_G);

                    okno.display();
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

// --------------------------------------------------------------------------------------------------------- ruch obiektow

        bohater.ruch();

// --------------------------------------------------------------------------------------------------------- sprawdzanie zmiany segmentu

        for (int i=0; i<segmentow; i++)
        {
            for (int j=0; j<mapa[i]->getPos(); j++)
            {
                int bid = mapa[i]->getObiekt(j, postac);
                sf::Vector2i nowy = postacie[ bid ]->checkSeg();
                if ( nowy.x != -1 )
                {
                    mapa[i]->usun( bid );
                    mapa[ wspolrzedne[nowy.x][nowy.y] ]->dodaj( postacie[ bid ] );
                    postacie[ bid ]->setSeg(nowy);
                }
            }
        }

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

        okno.clear(sf::Color::White);

        for (int i=0; i<mapa.size(); i++)
            okno.draw(mapa[i]->getObraz());

        //okno.draw(drzwi1.getObraz());
        //okno.draw(drzwi2.getObraz());

        for (int i=0; i<mapa.size(); i++)
        {
            for (int j=0; j<mapa[i]->getInt(); j++)
                okno.draw( interaktywne[mapa[i]->getObiekt(j, interaktywny)]->getObraz() );
        }

        okno.draw(bohater.getObraz());

        okno.setView(okno.getDefaultView());
        okno.draw(GUI.getObraz());
        okno.setView(widok_G);

        //for (int i=0; i<interaktywne.ilosc(); i++)
            //okno.draw(interaktywne[])

        okno.display();
    }

// ---------------------------------------------------------------------------------------------------------- koniec programu (po zamknieciu okna)

    return 0;
}
