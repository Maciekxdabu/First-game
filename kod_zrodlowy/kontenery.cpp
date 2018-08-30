#include "klasy.h"

template <class T>
slownik<T>::slownik()
{
    IDs.clear();
    IDobiektu.clear();
}

template <class T>
slownik<T>::~slownik()
{
    ;
}

template <class T>
T slownik<T>::operator[](int d)
{
    int k=0;

    do
    {
        if (IDs[k] == d)
        {
            return IDobiektu[k];
        }

        k++;
    }
    while (k < IDs.size());

    //return nullptr; /// wartosc ktora oznacza ze wskaznik jest rowny 0
}

template <>
Tag slownik<Tag>::operator[](int d)
{
    int k=0;

    do
    {
        if (IDs[k] == d)
        {
            return IDobiektu[k];
        }

        k++;
    }
    while (k < IDs.size());

    return NONE;
}

template <class T>
void slownik<T>::dodaj(int d, T ob)
{
    IDs.push_back(d);
    IDobiektu.push_back(ob);
}

template <class T>
void slownik<T>::usun(int d)
{
    int n, k=0;

    do
    {
        if (IDs[k] == d)
        {
            n = IDs[k];
            IDs.erase(IDs.begin() + k);
            IDobiektu.erase(IDobiektu.begin() + n);
        }

        k++;
    }
    while (k < IDs.size());
}

template <class T>
int slownik<T>::ilosc()
{
    return IDs.size();
}


template class slownik<Tag>;
template class slownik<Granica*>;
template class slownik<Postac*>;
template class slownik<Interaktywne*>;
