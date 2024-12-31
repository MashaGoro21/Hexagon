#ifndef Hexxagon_hpp
#define Hexxagon_hpp

//#include <stdio.h>
#include <SFMl/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>

/**
 * @brief W klasie Hexxagon cała gra jest aktualizowana i rysowana
 */
class Hexxagon
{
private:
    //Variables
    
    //Panel
    sf::RectangleShape panelShape;
    
    //Vectors
    std::vector<std::vector<int>> field;
    std::vector<sf::CircleShape> figures;
    std::vector<std::vector<int>> figuresIndexes;
    
    bool gameType;
    bool isSelected;
    bool mouseHeld;
    bool yourMove;
    bool endGame;
    bool red;
    bool blue;
    
    //Font
    sf::Font font1;
    
    //Sześciokąty
    sf::CircleShape pointsHexagonYou;
    sf::CircleShape pointsHexagonRival;
    
    sf::CircleShape redWinHexagon;
    sf::CircleShape blueWinHexagon;
    
    //Private functions
    
    /**
     * @brief Inicjalizuje zmienne gry Hexxagon.
     *
     * Funkcja inicjalizuje zmienne gry Hexxagon, takie jak plansza i flagi stanu gry.
     *
     * - field to jest pole gry (-1 - pusta klatka, po której nie można chodzić; 0 - pusta klatka, po której można chodzić; 1 - red; 2 - blue)
     * - isSelected ustawiane jest na false, ponieważ żadna figura nie została jeszcze wybrana.
     * - mouseHeld ustawiane jest na false, ponieważ przycisk myszy nie jest wciśnięty.
     * - yourMove ustawiane jest na true, ponieważ gra rozpoczyna się od twojej tury (red).
     * - endGame ustawiane jest na false, bo gra jeszcze się nie skończyła.
     * - red ustawiane jest na false, bo nikt jeszcze nie wygrywa (true kiedy red wygrywa)
     * - blue ustawiane jest na false, bo nikt jeszcze nie wygrywa (true kiedy wygrywa blue)
     */
    void initVariables();
    
    /**
     * @brief Inicjalizuje sześciokąt dla gry.
     *
     * Funkcja tworzy i inicjalizuje sześciokąt dla gry.
     *
     * @return Obiekt sf::CircleShape reprezentujący sześciokąt dla gry.
     */
    sf::CircleShape initHexagon();
    
    /**
     * @brief Inicjalizuje pola gry w kształcie sześciokątów.
     *
     * Funkcja tworzy i inicjalizuje pola gry w kształcie sześciokątów na podstawie danych zawartych w tablicy field.
     */
    void initHexagonField();
    
    /**
     * @brief Inicjalizuje panel gry.
     *
     * Funkcja inicjalizuje panel gry. Ustawia rozmiar, kolor, położenie i styl obramowania panelu.
     */
    void initPanel();
    
    /**
     * @brief Inicjalizuje czcionkę w klasie Hexxagon.
     *
     * Funkcja wczytuje plik czcionki i inicjalizuje go w klasie Hexxagon.
     *
     * @return `EXIT_FAILURE` w przypadku niepowodzenia wczytania czcionki, w przeciwnym razie nie ma wartości zwracanej.
     */
    void initFonts();
    
    /**
     * @brief Inicjalizuje sześciokąty, które pojawią się w przypadku czyjegoś zwycięstwa oraz w pobliżu punktów.
     *
     * Funkcja inicjalizuje sześciokąty dla gracza i rywala.
     * Ustawia rozmiar, kolor i położenie każdego z elementów.
     */
    void initPointsWinHexagons();
    
public:
    //Constructor and destructor
    Hexxagon();
    Hexxagon(bool gameType);
    virtual ~Hexxagon();
    
    //Functions
    
    /**
     * @brief Inicjuje tekst wygranej.
     *
     * Funkcja inicjalizuje tekst wyświetlany po zakończeniu gry.
     * Wybiera odpowiedni napis w zależności od tego, czy wygrał RED czy BLUE.
     * Ustawia rozmiar, czcionkę, kolor i położenie tekstu.
     *
     *@return Tekst wygranej.
     */
    sf::Text initWinText();
    
    /**
     * @brief Sprawdza, czy istnieją dostępne ruchy dla określonego koloru.
     *
     * @param color Kolor do sprawdzenia (sf::Color).
     *
     * @return Wartość logiczna true, jeśli istnieją dostępne ruchy dla danego koloru, w przeciwnym razie false.
     */
    bool areThereMoves(sf::Color color);
    
    /**
     * @brief Liczy liczbę możliwych ruchów dla figury o podanym indeksie.
     *
     * @param index Indeks figury do sprawdzenia (int).
     *
     * @return Liczba możliwych ruchów dla figury.
     */
    int countPossibleMoves(int index);
    
    /**
     * @brief Liczy punkty dla figur na planszy.
     *
     * @return Wektor obiektów sf::Text zawierający punkty dla czerwonych i niebieskich figur.
     */
    std::vector<sf::Text> countPoints();
    
    /**
     * @brief Znajduje indeks zaznaczonej figury.
     *
     * @return Indeks zaznaczonej figury.
     */
    int findSelected();
    
    /**
     * @brief Czyści pole planszy.
     *
     * Czyści pole planszy poprzez ustawienie przezroczystego koloru obrysu dla wszystkich figur.
     */
    void clearField();
    
    /**
     * @brief Znajduje indeks figury na podstawie współrzędnych (i, j) w wektorze figuresIndexes.
     *
     * @param i Współrzędna i.
     * @param j Współrzędna j.
     *
     *  @return Indeks figury w wektorze figuresIndexes.
     */
    int indexFigure(int i, int j);
    
    /**
     * @brief Sprawdza, czy indeks pola jest prawidłowy w kontekście wektora figures.
     *
     * @param index Indeks pola.
     *
     * @return Wartość true, jeśli indeks jest prawidłowy, w przeciwnym razie false.
     */
    bool isValidField(int index);
    
    /**
     * @brief Sprawdza, czy jedna figura została zaznaczona.
     *
     * @return Wartość true, jeśli jedna figura jest zaznaczona, w przeciwnym razie false.
     */
    bool oneFigureSelected();
    
    /**
     * @brief Sprawdza kolizję sześciokątu z pozycją myszy.
     *
     * Funkcja sprawdza, czy pozycja myszy koliduje z obszarem sześciokątu.
     *
     * @param hexagon Referencja do obiektu sf::CircleShape, który ma być sprawdzany.
     * @param window Referencja do obiektu sf::RenderWindow, okna, w którym znajduje się sześciokąt.
     *
     * @return Wartość logiczna określająca, czy wystąpiła kolizja (true) lub nie (false).
     */
    bool checkCollision(sf::CircleShape hexagon, sf::RenderWindow& window);
    
    /**
     * @brief Wybiera figury na planszy na podstawie indeksu.
     *
     * Sprawdza, czy nie jest już wybrana żadna figura i czy żadna figura nie jest obecnie zaznaczona.
     * Jeśli tak, to ustawia obramowanie na białe dla figury o indeksie i, oznacza, że figura jest teraz zaznaczona  i wywołuje funkcję possibleMoves(i).
     * W drugiej części sprawdzane jest, czy figura o indeksie i ma już obramowanie białe.
     * Jeśli tak, to ustawia obramowanie na przezroczyste, oznaczając, że figura nie jest już zaznaczona, oraz wywołuje funkcję clearField().
     *
     * @param i Indeks figury do wybrania.
     */
    void selectFigure(int i);
    
    /**
     * @brief Zaznacza możliwe ruchy dla wybranej figury na planszy na podstawie indeksu.
     *
     * @param index Indeks wybranej figury.
     */
    void possibleMoves(int index);
    
    /**
     * @brief Aktualizuje kolory sąsiednich figur na planszy na podstawie wybranej figury.
     *
     * @param index Indeks wybranej figury.
     */
    void updateFigures(int index);
    
    /**
     * @brief Wyszukuje wszystkie możliwe ruchy dla komputera.
     *
     * @return Wektor zawierający informacje o najlepszym ruchu dla komputera.
     *         Indeks 0 - indeks figury komputera
     *         Indeks 1 - indeks najlepszego ruchu
     *         Indeks 2 - 0 (zielony) lub 1 (żółty)
     */
    std::vector<int> computerAllPossibleMoves();
    
    /**
     * @brief Liczy możliwe punkty dla danego ruchu komputera.
     *
     * @param index Indeks figury, dla której liczone są punkty.
     *
     * @return Liczba możliwych punktów.
     */
    int computerCountPossiblePoints(int index);
    
    /**
     * @brief Wykonuje ruch na planszy
     *
     * Sprawdza się kolor obramowania figury, na którą chcemy wykonać ruch i na podstawie tego podejmuje odpowiednie działania.
     * Również aktualizowane są figury planszy i czyszczone pola. Po wykonaniu ruchu, isSelected jest ustawiana na false, a flaga yourMove jest odwracana.
     *
     * @param i Indeks pola, na które ma zostać wykonany ruch.
     */
    void move(int i);
    
    /**
     * @brief Wykonuje ruch gracza.
     *
     * Sprawdzane, czy teraz jest ruch gracza. Jeśli tak, to sprawdza się, czy lewy przycisk myszy jest wciśnięty.
     * Jeśli tak, iteruje się po figurach na planszy i sprawdza się kolizję z myszą.
     * Jeśli figura ma kolor red, to jest zaznaczana. Jeśli figura ma kolor grey, to jest wykonywany ruch na to pole.
     *
     * @param window Referencja do okna aplikacji.
     *
     */
    void myMove(sf::RenderWindow& window);
    
    /**
     * @brief Wykonuje ruch gracza.
     *
     * Sprawdza się, czy lewy przycisk myszy jest wciśnięty.
     * Jeśli tak, iteruje się po figurach na planszy i sprawdza się kolizję z myszą.
     * Jeśli figura ma kolor cyan, to jest zaznaczana. Jeśli figura ma kolor grey, to jest wykonywany ruch na to pole.
     *
     * @param window Referencja do okna aplikacji.
     */
    void playerMove(sf::RenderWindow& window);
    
    /**
     * @brief Wykonuje ruch komputera
     *
     * Sprawdza, czy teraz jest ruch komputera.
     * Jeśli tak, wywoływana jest funkcja, która zwraca wektor zawierający informacje o najlepszym ruchu komputera.
     * Na koniec yourMove jest odwracana.
     */
    void computerMove();
    
    /**
     * @brief Sprawdza warunek zakończenia gry dla trybu jednoosobowego.
     *
     * Jeśli nie ma już figurek w kolorze czerwonym lub cyan, ustawia flagę endGame na true.
     */
    void endGameOnePlayer();
    
    /**
     * @brief Sprawdza warunek zakończenia gry dla braku możliwych ruchów dla figury czerwonej.
     *
     * Jeśli nie ma już możliwych ruchów dla figur czerwonych, ustawia flagę endGame na true.
     */
    void endGameNotPossibleMovesRed();
    
    /**
     * @brief Sprawdza warunek zakończenia gry dla braku możliwych ruchów dla figury niebieskiej.
     *
     * Jeśli nie ma już możliwych ruchów dla figur niebieskich, ustawia flagę endGame na true.
     */
    void endGameNotPossibleMovesBlue();
    
    /**
     * @brief Logika gry dla trybu player vs. player.
     *
     * Obsługuje kolejne etapy gry, takie jak ruch gracza, sprawdzenie warunków zakończenia gry, aktualizacja wyników i wyświetlanie punktów na ekranie.
     *
     * @param window Referencja do obiektu sf::RenderWindow, na którym rysowana jest gra.
     */
    void gamePlayer(sf::RenderWindow& window);
    
    /**
     * @brief Logika gry dla trypu player vs. computer.
     *
     * Obsługuje kolejne etapy gry, takie jak ruch gracza, sprawdzenie warunków zakończenia gry, aktualizacja wyników i wyświetlanie punktów na ekranie.
     *
     * @param window Referencja do obiektu sf::RenderWindow, na którym rysowana jest gra.
     */
    void gameComputer(sf::RenderWindow& window);
    
    /**
     * @brief Aktualizuje stan gry na podstawie wybranego trybu i obsługuje logikę gry.
     *
     * @param window Referencja do obiektu sf::RenderWindow, na którym rysowana jest gra.
     */
    void update(sf::RenderWindow& window);
    
    /**
     * @brief Renderuje elementy gry na podanym obiekcie sf::RenderWindow.
     *
     * - Rysowanie pointsHexagonYou.
     * - Rysowanie pointsHexagonRival.
     * - Rysowanie wszystkich figurek na planszy.
     * - Wywołanie funkcji update w celu aktualizacji stanu gry.
     *
     * @param window Referencja do obiektu sf::RenderWindow, na którym rysowane są elementy gry.
     */
    void render(sf::RenderWindow& window);
};



#endif /* Hexxagon_hpp */
