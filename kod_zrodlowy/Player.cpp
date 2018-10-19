#include "klasy.h"

Player::Player(float px, float py, float kx, float ky, float ks, float kw, std::string adres, int s)
:Postac(px, py, kx, ky, ks, kw, adres)
{
    maxx = 2;
    maxy = 2;
    
    interakcja = false;
}

Player::~Player()
{
    ;
}

bool Player::checkLV()
{
    if (EXP >= MAXEXP)
        return true;
    else
        return false;
}

void Player::LVup()
{
    EXP = EXP - MAXEXP;
    //MAXEXP =
    LV++;
}

void Player::ruch()
{
    ob_fiz::ruch();

    widok_G.setCenter(obraz.getPosition().x + 50, obraz.getPosition().y + 50);
    okno.setView(widok_G);
}

void Player::czy_interakcja(Interaktywne* ob)
{
    if ( ob_fiz::czy_kol(this, ob) )
    {
        mozliwe = ob->getID();
        interakcja = true;
    }
}

void Player::teleportacja(float xx, float yy)
{
    float zmx = xx - (obraz.getPosition().x + szerokosc/2);
    float zmy = yy - (obraz.getPosition().y + wysokosc/2);

    obraz.move(zmx, zmy);
    x += zmx;
    y += zmy;
}

void Player::reset()
{
    interakcja = false;
    mozliwe = -1;
}

int Player::getSegment()
{
    return wspolrzedne[seg.x][seg.y];
}

int Player::getInt()
{
    if (interakcja == true)
        return mozliwe;
    else
        return -1;
}
