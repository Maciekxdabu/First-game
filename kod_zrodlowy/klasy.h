#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <sstream>
#include <math.h>

class ob_fiz;
class Interaktywne;
class segment;
class Granica;
class Postac;
class Player;

enum Tag /// zmienne typu Tag odpowiadaj¹ przede wszystkim za odró¿nianie poszczególnych klas
{
    statyczny,
    interaktywny,
    postac,
    granica,
    drzwi,
    NONE
};
enum Kier /// zmienna typu Kier odpowiedzialna jest za zapamietywanie kierunkow
{
    gora,
    dol,
    lewo,
    prawo
};


template <class T>
class slownik /// klasa przechowuja rozne klasy dajac dostep poprzez ID
{
    std::vector<int> IDs;
    std::vector<T> IDobiektu;

public:
    slownik();
    ~slownik();
    T operator[](int);
    void dodaj(int, T);
    void usun(int);
    int ilosc();
};

enum typ_przedmiotu
{
    crafting_component,
    other
};

struct szablon_przedmiotu
{
    std::string nazwa;
    sf::Texture tekstura;
    typ_przedmiotu tag;
};

extern slownik<Tag> typ; /// zapis mowi ze zmienna jest zadeklarowana ale w innej czesci kodu ( w tym przypadku w main)
extern sf::View widok_G;
extern sf::RenderWindow okno;
extern Player bohater;
extern sf::Font czcionka;
extern int **wspolrzedne;
extern sf::Time deltaTime;


// -------------------------------------------------------------------------------------------------------------------------------------------------- klasa ob_fiz

class ob_fiz  /// klasa bazowa pod inne dzialajace na zasadzie interakcji miedzy soba
{
protected:
    float x, y;
    float szerokosc, wysokosc; /// wspolrzedne i wielkosci odpowiedzialne za wykrywanie kolizji
    sf::Vector2i seg; /// wspolredne segmentu w ktorym znajduje sie obiekt
    //int warstwa;
    sf::Vector2f predkosc; /// wektor przechowujacy dane o predkosci w ktora porusza sie obiekt
    int maxx, maxy; /// maksymalne wartosci jakie moze przyjac predkosc (const ???)
    Tag tag; /// przechowuje wartosc tag odrozniajaca obiekty (jak 'm' dla moba, czy 'f' dla obiektu fizycznego)
    sf::Sprite obraz; /// obraz obiektu fizycznego
    sf::Texture tekstura; /// i jego tekstura

    int ID;

    static int maxID;

public:
    ob_fiz(float, float, float, float, float, float, std::string);
    ~ob_fiz();
    Tag getTag(); /// zwraca tag
    sf::Vector2f getSpeed();
    sf::Vector2f getPos();
    sf::Sprite getObraz();
    void addVector(float=0, float=0);
    void ruch();
    int getID();
    sf::Vector2f getKolPos();
    sf::Vector2f getWym();
    sf::Vector2i getSeg();
    sf::Vector2i checkSeg();
    void setSeg(sf::Vector2i);

    static bool czy_kol(ob_fiz*, ob_fiz*);
    static int getMaxID();

    friend void wyrownaj(Postac*, Granica*);
};

// -------------------------------------------------------------------------------------------------------------------------------------------------- klasa Interaktywne

class Interaktywne :public ob_fiz /// klasa bazowa zwiazana z obiektami interaktywnymi (obsluguje obiekty z ktorymi gracz moze wejsc w interakcje)
{
protected:
    //sf::IntRect pole_interakcji;


public:
    Interaktywne(float, float, float, float, float, float, std::string);
    ~Interaktywne();
    virtual void interakcja()=0;

    //friend bool Player::czy_interakcja(Interaktywne*);
    //friend bool czy_kol(Player*, Interaktywne*);
};

class Drzwi :public Interaktywne
{
protected:
    sf::Vector2f cel; /// wspolrzedne na ktore drzwi przenosza gracza

public:
    Drzwi(float, float, float, float, float, float, std::string, float, float);
    ~Drzwi();
    virtual void interakcja();
};

// ------------------------------------------------------------------------------------------------------------------------------------------------------ klasa segment

class segment
{
public:
    static int width;
    static int height;

protected:
    std::vector<int> zawartosc; /// zbior elementow w segmencie mapy (ich ID)
    bool czy_zawiera; /// czy segment jest czescia mapy
    sf::Sprite obraz;
    sf::Texture tekstura;
    int x, y; /// wspolrzedne segmentu w mapie
    int ilosc_postaci;
    int ilosc_statycznych;
    int ilosc_interaktywnych;
    int ilosc_pozostalych;
    int ilosc_granic;

public:
    segment(std::string, int, int);
    ~segment();
    int getIlosc(); /// zwraca ilosc elementow w segmencie mapy
    int getObiekt(int, Tag=NONE); /// zwraca ID obiektu o numerze int (podanego tagu) (zwraca -1 w przypadku bledu/nie-znalezienia)
    sf::Sprite getObraz(); /// zwraca obiekt Sprite do wyswietlenia w oknie
    int getPos();
    int getStat();
    int getInt();
    int getPoz();
    int getGran();

    void dodaj(ob_fiz*); /// dodaje nowy element z segmentu
    void usun(int); /// usuwa element o podanym ID z segmentu
};

// ------------------------------------------------------------------------------------------------------------------------------------------------------ klasa Granica

class Granica :public ob_fiz
{
protected:
    Kier kierunek;

public:
    Granica(float, float, float, float, float, float, std::string, Kier);
    ~Granica();
    Kier getKier();
};

// ------------------------------------------------------------------------------------------------------------------------------------------------------ klasa Postac

class Postac :public ob_fiz
{
protected:
    int HP, MAXHP;
    std::string imie;
    bool kolizje; /// true = normalne kolizje | false = brak kolizji granicy dla np. drabiny

public:
    Postac(float, float, float, float, float, float, std::string);
    ~Postac();
    void addVector(float=0, float=0);
    void etheric(bool); /// zmienia wartosc zmiennej kolizje
    bool getKol();


    friend void wyrownaj(Postac*, Granica*);

};

// ------------------------------------------------------------------------------------------------------------------------------------------------------ klasa Player

class Player :public Postac
{
protected:
    int EXP, MAXEXP;
    int LV;
    //sf::Rect pole_interakcji; /// pole zwiazane z wykrywaniem interakcji
    int mozliwe; /// ID do obiektu z mozliwa interakcja
    bool interakcja;
    //int numer_segmentu;

    void teleportacja(float, float); /// teleportuje gracza w wybrane miejsce (tylko klasy i funkcje zaprzyjaznione)

public:
    Player(float, float, float, float, float, float, std::string, int);
    ~Player();
    bool checkLV(); /// zwraca czy postac moze wylewelowac
    void LVup();
    void ruch();
    void czy_interakcja(Interaktywne*);
    //void zmien_segment(int);
    int getSegment();
    int getInt();

    void reset(); /// WAZNE - resetuje niekture parametry postaci co klatke

    friend void wyrownaj(Postac*, Granica*);
    friend bool czy_kol(Player*, Interaktywne*);
    friend Drzwi;
};

// ------------------------------------------------------------------------------------------------------------------------------------------------------ klasa GUI

class GUI_class /// klasa odpowiedzialna za renderowanie panelu GUI
{
protected:
    sf::RenderTexture ostateczna_textura;
    sf::Sprite koncowy;
    sf::Texture tekstury;
    sf::Text napisy;
    int HP, maxHP;
    std::string nazwa;

    void reload();

public:
    GUI_class(int, int);
    ~GUI_class();
    sf::Sprite getObraz();
    void updHP(int, int=-1);

};

// ------------------------------------------------------------------------------------------------------------------------------------------------------ klasa menu

enum okienko /// jaka czesc menu ma byc teraz wyswietlona
{
    glowne, opcje, koniec, nowa, wczytaj, zapisz
};

class Menu_class /// klasa odpowiadajaca za poruszanie sie po roznych menu
{
protected:
    sf::RenderTexture plotno;
    sf::Sprite obraz;
    okienko aktualne;
    sf::Text tekst;
    int wybrane, maksymalne;
    std::string gl[4];

    void reload();

public:
    Menu_class();
    ~Menu_class();
    sf::Sprite getObraz();
    void w_gore();
    void w_dol();
    int getWybrane();
    void zmien(okienko); /// zmiana plaszczyzny (maksymalnej ilosci wyborow)
    okienko getTyp();
};


//deklaracje ponizszych w funkcje.cpp
void wyrownaj(Postac*, Granica*);
//bool czy_kol(Player*, Interaktywne*);
int StrToInt(std::string);
std::string IntToStr(int);
