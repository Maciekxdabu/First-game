#include "ob_fiz.h"

using namespace std;

int segment::width = 100;
int segment::height = 100;

segment mapa[10][10];

int main()
{   
    sf::RenderWindow okno(sf::VideoMode(500, 500, 32), "Gra");

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

        okno.display();
    }

    return 0;
}
