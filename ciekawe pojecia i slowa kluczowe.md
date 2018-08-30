extern - zmienne można poprzeć tym słowem kluczowym jężeli są one zadeklarowane globalnie w innym pliku
template<class T> - od tego można zacząć tworzyć szablon klasy lub funkcji (gdzie typ zmiennej określony jest przez 'T'), zamiast pisać wielokrotnie to samo
enum X {...}; - poprzez enum tworzymy zmienną typu 'X' która przyjmuje wartości podane w nawiasach
struct X {...}; - poprzez struct tworzymu struktórę danych zawartych w nawiasach (np. wizytówka złorzona ze: string imie, int telefon itd.)
static - tym słowem kluczowym można poprzeć zmienną lub funkcję w klasie jak również samą klasę, mówi ono że istnieje tylko jeden egzemplarz danej wartości (zmienna jest stała dla wszytskich obiektów, a funkcjemają bezpośredni dostęp do prywatnych argumentów zarówno w klasie bazowej jak i tych dziedziczącej po niej), dostę do tych danych i funkcji uzyskujemy poprzez operator nazwy: nazwa_klasy::nazwa_funkcji/zmiennej
