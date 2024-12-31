
#ifndef Game_hpp
#define Game_hpp

//#include <stdio.h>
#include <SFMl/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "Menu.hpp"

/**
 * @brief Klasa działająca jako silnik gry. Uruchamia i wyświetla grę w naszym oknie
 */

class Game{
private:
    //Variables
    Menu menu;
    
    //Mouse position
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    
    //Window
    sf::RenderWindow* window;
    sf::Event event;
    
    //Private functions
    
    /**
     * @brief Inicjalizuje zmienne w klasie Game.
     *
     * Funkcja inicjalizuje zmienne w klasie Game. Ustawia wskaźnik na okno na wartość nullptr.
     * Ta funkcja musi zostać wywołana przed użyciem innych funkcji w klasie Game.
     */
    void initVariables();
    
    /**
     * @brief Inicjalizuje okno gry.
     *
     * Funkcja tworzy nowe okno sf::RenderWindow o rozmiarze ekranu pulpitu i tytule "Hexagon" w trybie domyślnym.
     * Ta funkcja musi zostać wywołana przed rozpoczęciem pętli gry.
     */
    void initWindow();
    
public:
  //Constructor and destructor
    Game();
    virtual ~Game();
    
    //Accessors
    
    /**
     * @brief Sprawdza, czy gra jest w trakcie działania.
     *
     * @return Wartość logiczna, czy okno gry jest otwarte (true) lub zamknięte (false).
     * Ta funkcja może być wykorzystywana w pętli głównej gry do sprawdzania warunku zakończenia gry.
     */
    const bool running() const;
    
    //Functions
    
    /**
     * @brief Obsługuje zdarzenia związane z oknem.
     *
     * Funkcja obsługuje zdarzenia związane z oknem, takie jak zamknięcie okna lub naciśnięcie klawisza Escape.
     * Jeśli zostanie wykryte zamknięcie okna lub naciśnięcie klawisza Escape, funkcja zamyka okno gry.
     */
    void pollEvents();
    
    /**
     * @brief Aktualizuje stan gry.
     *
     * Funkcja aktualizuje stan gry poprzez obsługę zdarzeń związanych z oknem.
     */
    void update();
    
    /**
     * @brief Renderuje zawartość gry na ekranie.
     *
     * Funkcja renderuje zawartość gry na ekranie, w tym menu główne.
     */
    void render();
};


#endif /* Game_hpp */
