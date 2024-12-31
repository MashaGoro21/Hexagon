
#ifndef Menu_hpp
#define Menu_hpp

//#include <stdio.h>
#include <SFMl/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Hexxagon.hpp"

/**
 *@brief W klasie Menu wyświetla się menu, w którym możesz stworzyć grę, wczytać starą, wyjść.
 */
class Menu
{
private:
    //Variables
    bool isVisibleMenu;
    bool isVisibleType;
    bool playMode;
    bool saveGame;
    bool gameType;
    bool isGameSaved;
    
    
    //Panel
    sf::RectangleShape panelShape;
    
    Hexxagon hexagon;
    
    //Text
    sf::Text menuText;
    sf::Text newGameText;
    sf::Text loadGameText;
    sf::Text scoreBoardText;
    sf::Text quitText;
    
    sf::Text playerText;
    sf::Text computerText;
    
    sf::Text quitTextField;
    
    sf::Text saveGameText;
    sf::Text yesText;
    sf::Text noText;

    
    //Fonts
    sf::Font font;
    
    //Private functions
    
    /**
     * @brief Inicjalizuje zmienne w klasie Menu.
     *
     * Funkcja ustawia początkowe wartości zmiennych dla menu.
     *
     * - isVisibleMenu ustawiane jest na true, aby menu było widoczne.
     * - isVisibleType ustawiane jest na false, aby typy gry nie był widoczne.
     * - playMode ustawiane jest na false, aby nie rozpoczynać gry.
     * - saveGame ustawiane jest na false, aby okno z zapisywaniem gry się nie wyświetlało.
     * - gameType ustawiane jest na true (true - player vs. player, false - player vs. computer).
     * - isGameSaved ustawiane jest na false, ponieważ żadna gra nie jest jeszcze zapisana.
     */
    void initVariables();
    
    /**
     * @brief Inicjalizuje czcionkę w klasie Menu.
     *
     * Funkcja wczytuje plik czcionki i inicjalizuje go w klasie Menu.
     *
     * @return `EXIT_FAILURE` w przypadku niepowodzenia wczytania czcionki, w przeciwnym razie nie ma wartości zwracanej.
     */
    void initFonts();
    
    /**
     * @brief Inicjalizuje tekst w klasie Menu.
     *
     * Funkcja inicjalizuje obiekty tekstu dla różnych elementów menu.
     *
     * - Inicjalizuje tekst dla tytułu menu.
     * - Inicjalizuje tekst dla opcji "New Game".
     * - Inicjalizuje tekst dla opcji "Load Game".
     * - Inicjalizuje tekst dla opcji "Quit".
     * - Inicjalizuje tekst dla opcji "PLAYER vs. PLAYER".
     * - Inicjalizuje tekst dla opcji "PLAYER vs. COMPUTER".
     * - Inicjalizuje tekst dla pola "Quit" w grze.
     * - Inicjalizuje tekst dla pytania "Do you want to save game?".
     * - Inicjalizuje tekst dla opcji "YES".
     * - Inicjalizuje tekst dla opcji "NO".
     */
    void initText();
    
    /**
     * @brief Inicjalizuje panel w klasie Menu.
     *
     * Funkcja inicjalizuje kształt panelu w klasie Menu.
     *
     * - Ustawia rozmiar panelu.
     * - Ustawia kolor wypełnienia panelu.
     * - Ustawia pozycję panelu.
     * - Ustawia kolor obramowania panelu.
     * - Ustawia grubość obramowania panelu.
     */
    void initPanel();
    
public:
    
//Constructor and destructor
    Menu();
    virtual ~Menu();
    
    //Functions
    
    /**
     * @brief Sprawdza kolizję tekstu z pozycją myszy.
     *
     * Funkcja sprawdza, czy pozycja myszy koliduje z obszarem tekstu.
     *
     * @param text Referencja do obiektu sf::Text, który ma być sprawdzany.
     * @param window Referencja do obiektu sf::RenderWindow, okna, w którym znajduje się tekst.
     *
     * @return Wartość logiczna określająca, czy wystąpiła kolizja (true) lub nie (false).
     */
    bool checkCollision(sf::Text text, sf::RenderWindow& window);
    
    /**
     * @brief Aktualizuje wygląd tekstu na podstawie kolizji z myszą.
     *
     * Funkcja aktualizuje wygląd tekstu na podstawie kolizji z myszą. Sprawdza kolizje dla różnych elementów menu
     * i zmienia ich kolor w zależności od interakcji z myszą. Dodatkowo, obsługuje akcje wykonywane po kliknięciu
     * na odpowiednie elementy.
     *
     * @param window Referencja do obiektu sf::RenderWindow, okna, na którym jest rysowane menu.
     */

    void update(sf::RenderWindow& window);
    
    /**
     * @brief Renderuje menu na oknie.
     *
     * Funkcja renderuje menu na oknie, aktualizując najpierw jego stan przez wywołanie funkcji `update()`.
     * Następnie rysuje odpowiednie elementy menu w zależności od aktualnego stanu.
     *
     * @param window Referencja do obiektu sf::RenderWindow, okna, na którym jest rysowane menu.
     */
    void render(sf::RenderWindow& window);
};

#endif /* Menu_hpp */
