#include <SFML/Graphics.hpp>
#include <vector>

enum Tag /// zmienne typu Tag odpowiadają przede wszystkim za odróżnianie poszczególnych klas
{
    statyczny,
    interaktywny,
    postac,
    granica,
    NONE
};
enum Kier /// zmienna typu Kier odpowiedzialna jest za zapamietywanie kierunkow
{
    gora,
    dol,
    lewo,
    prawo
};

// -------------------------------------------------------------------------------------------------------------------------------------------------- klasa ob_fiz

class ob_fiz  /// klasa bazowa pod inne dzialajace na zasadzie interakcji miedzy soba
{
protected:
    float x, y;
    float szerokosc, wysokosc; /// wspolrzedne i wielkosci odpowiedzialne za wykrywanie kolizji
    //int warstwa;
    sf::Vector2f predkosc; /// wektor przechowujacy dane o predkosci w ktora porusza sie obiekt
    int maxx, maxy; /// maksymalne wartosci jakie moze przyjac predkosc (const ???)
    Tag tag; /// przechowuje wartosc tag odrozniajaca obiekty (jak 'm' dla moba, czy 'f' dla obiektu fizycznego)
    sf::Sprite obraz; /// obraz obiektu fizycznego
    sf::Texture tekstura; /// i jego tekstura
    Kier kierunek;

public:
    ob_fiz(float, float, float, float, float, float, std::string);
    ~ob_fiz();
    virtual void wyrownaj(ob_fiz*); // wyrownuje obiekt na podstawie drugiego obiektu (kolizja)
    Tag getTag(); /// zwraca tag
    sf::Vector2f getSpeed();
    sf::Vector2f getPos();
    sf::Sprite getObraz();
    void addVector(float=0, float=0);
    void ruch();
    Kier getKier();

    friend bool czy_kol(ob_fiz*, ob_fiz*);
};

// -------------------------------------------------------------------------------------------------------------------------------------------------- klasa Interaktywne

class Interaktywne :public ob_fiz /// klasa bazowa zwiazana z obiektami interaktywnymi (obsluguje obiekty z ktorymi gracz moze wejsc w interakcje)
{
protected:


public:
    Interaktywne(float, float, float, float, float, float, std::string);
    ~Interaktywne();

    friend bool czy_kol(ob_fiz*, ob_fiz*);
};

bool czy_kol(ob_fiz*, ob_fiz*);

// ------------------------------------------------------------------------------------------------------------------------------------------------------ klasa segment

class segment
{
public:
    static int width;
    static int height;

protected:
    std::vector<ob_fiz*> zawartosc; /// zbior elementow w segmencie mapy
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
    ob_fiz* getObiekt(int); /// zwraca obiekt o podanym indeksie
    sf::Sprite getObraz(); /// zwraca obiekt Sprite do wyswietlenia w oknie
    int getPos();
    int getStat();
    int getInt();
    int getPoz();
    int getGran();

    void dodaj(ob_fiz*); /// dodaje nowy element z segmentu
    void usun(); /// usuwa element z segmentu ---TO DO---
};

// ------------------------------------------------------------------------------------------------------------------------------------------------------ klasa Granica

class Granica :public ob_fiz
{
protected:
    //Kier kierunek;

public:
    Granica(float, float, float, float, float, float, std::string, Kier);
    ~Granica();
    //Kier getKier();
};

// ------------------------------------------------------------------------------------------------------------------------------------------------------ klasa Postac

class Postac :public ob_fiz
{
protected:
    int HP, MAXHP;
    std::string imie;

public:
    Postac(float, float, float, float, float, float, std::string);
    ~Postac();
    virtual void wyrownaj(ob_fiz*);
};

// ------------------------------------------------------------------------------------------------------------------------------------------------------ klasa Player

class Player :public Postac
{
protected:
    int EXP, MAXEXP;
    int LV;

public:
    Player(float, float, float, float, float, float, std::string);
    ~Player();
    bool checkLV(); /// zwraca czy postac moze wylewelowac
    void LVup();
};
