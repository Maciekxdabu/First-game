#include "ob_fiz.h"

ob_fiz::ob_fiz()
{
    ;
}

ob_fiz::~ob_fiz()
{
    ;
}

void ob_fiz::wyrownaj(ob_fiz* ob)
{
    if (czy_kol(this, ob) == true) /// czy szybkosc wplynie mocno na to ????????
    {
        if (x + szerokosc <= ob->x + ob->szerokosc/2)
        {
            x = ob->x - szerokosc;
        }
        else if (x > ob->x + ob->szerokosc/2)
        {
            x = ob->x + ob->szerokosc;
        }

        if (y + wysokosc <= ob->y + ob->wysokosc)
        {
            y = ob->y - wysokosc;
        }
        else if (y > ob->y + ob->wysokosc/2)
        {
            y = ob->y + ob->wysokosc;
        }
    }
}




bool czy_kol(ob_fiz *ob1, ob_fiz *ob2)
{
    if (ob1->x + ob1->szerokosc >= ob2->x && ob1->x <= ob2->x + ob2->szerokosc && ob1->y + ob1->wysokosc >= ob2->y && ob1->y <= ob2->y + ob2->wysokosc)
        return true;
    else
        return false;
}
