#include "klasy.h"

GUI_class::GUI_class(int hp, int maxhp)
{
    HP = hp;
    maxHP = maxhp;

    ostateczna_textura.create(1000, 1000);

    koncowy.setPosition(0,0);

    napisy.setFont(czcionka);
    napisy.setCharacterSize(30);
    napisy.setFillColor(sf::Color::Red);
    napisy.setString(IntToStr(HP) + "/" + IntToStr(maxHP));
    napisy.setPosition(20, 20);

    reload();
}

GUI_class::~GUI_class()
{
    ;
}

void GUI_class::reload()
{
    ostateczna_textura.clear(sf::Color::Transparent);

    ostateczna_textura.draw(napisy);

    ostateczna_textura.display();

    koncowy.setTexture(ostateczna_textura.getTexture());
}

sf::Sprite GUI_class::getObraz()
{
    reload();
    koncowy.setPosition(0,0);
    return koncowy;
}

void GUI_class::updHP(int hp, int maxhp)
{
    HP = hp;
    if (maxhp != -1)
        maxHP = maxhp;
    reload();
}
