#include <SFML/Graphics.hpp>

using namespace std;

//nowe klasy:
sf::View widok; /// klasa odpowiedzialna za to jaka czêœæ mapy rysujemy na ekranie
//"krotkie" wyjasnienie:
/// wszystkie obiekty w SFMLu ktore mozna narysowac maja swoja okreslona pozycje na ekranie (we floatach dla dokladniejszych obliczen)
/// mapy moga byc bardzo duze nawet 50 000 pikseli (zo raczej przekracza wiekszosc monitorow)
/// widoki pozwalaja rysowac okreslona czesc mapy ( pozycje i skale)
/// skale mozna wykorzystac na przyklad do zrobienia mini-mapy lub przyblizenia
/// ogolnie dziala to tak ze odejmuje wspolrzedne obiektu od wspolrzednych widoku zeby narysowac obraz w oknie
//wazne roznice:
/// w widoku ustawiamy pozycje poprzez srodek, anie poprzez lewy gorny rog obiektu jak w wiekszosci

int main()
{
    sf::RenderWindow okno(sf::VideoMode(400, 400, 32), "Zdarzenia i widoki");

    widok.setCenter(200, 200); /// funkcja ustawia srodek widoku (w tym przypadku srodek okna wiec nie zobaczymy zmian)
    okno.setView(widok); /// funkcja ustawia widok dla danego okna (nie pobiera wskaznika wiec trzeba jej uzyc zawsze kiedy nastapi zmiana widoku aby zobaczyc efekty)

    while (okno.isOpen())
    {
        sf::Event zdarzenie;
        while (okno.pollEvent(zdarzenie))
        {
            if (zdarzenie.type == sf::Event::Closed)
            {
                okno.close();
            }

            if (zdarzenie.type == sf::Event::KeyPressed) /// zdarzenie zwiazane z wcisnieciem klawisza
            {
                if (zdarzenie.key.code == sf::Keyboard::Return) /// gdy wcisnieto klawisz enter
                    ;
                if (zdarzenie.key.code == sf::Keyboard::A && zdarzenie.key.shift == true) /// gdy wcisnieto klawisz 'A' trzymajac SHIFT
                    ;
            }

            if (zdarzenie.type == sf::Event::KeyReleased) /// zdarzenie zwiazane z puszczeniem klawisza
            {
                if (zdarzenie.key.code == sf::Keyboard::Return) /// gdy puszczono klawisz enter
                    ;
                if (zdarzenie.key.code == sf::Keyboard::A && zdarzenie.key.alt == true) /// gdy puszczono klawisz 'A' trzymajac ALT
                    ;
            }

            if (zdarzenie.type == sf::Event::MouseButtonPressed) /// zdarzenie zwiazane z wcisnieciem klawisza
            {
                if (zdarzenie.mouseButton.button == sf::Mouse::Left) /// gdy wcisnieto lewy klawisz myszki
                    ;
                if (zdarzenie.mouseButton.button == sf::Mouse::Middle) /// gdy wcisnieto kolko myszki
                    ;
            }

            if (zdarzenie.type == sf::Event::MouseButtonReleased) /// zdarzenie zwiazane z puszczeniem klawisza
            {
                if (zdarzenie.mouseButton.button == sf::Mouse::Left) /// gdy puszczono lewy klawisz myszki
                    ;
                if (zdarzenie.mouseButton.button == sf::Mouse::Middle) /// gdy puszczono kolko myszki
                    ;
            }

            // dalej przykladow dawac nie musze bo i tak Code::Blocks wam da opisy wydarzen w okienku autouzupelniania nazw
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) /// ta funkcja zwraca bezposrednio stan klawisza (wcisniety lub nie wcisniety) rowniez poza Eventami
            ;
        // ciekawostka: funkcja ta moze zwrocic prawde nawet wtedy kiedy okno nie ma fokusu, poniewaz czyta ona stan klawisza bezposrednio z klawiatury

        okno.clear(sf::Color::White);

        okno.display();
    }

    return 0;
}
