#include "ob_fiz.h"

using namespace std;

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
        }

        okno.clear(sf::Color::White);

        okno.display();
    }

    return 0;
}
