#include "klasy.h"

Player::Player(float px, float py, float kx, float ky, float ks, float kw, std::string adres)
:Postac(px, py, kx, ky, ks, kw, adres)
{
    maxx = 2;
    maxy = 2;
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
