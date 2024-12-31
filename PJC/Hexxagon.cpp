#include "Hexxagon.hpp"

//Private functions
void Hexxagon::initVariables()
{
    field = {
        {-1, -1, -1, -1, 2, -1, -1, -1, -1},
        {-1, -1, -1, 0, -1, 0, -1, -1, -1},
        {-1, -1, 0, -1, 0, -1, 0, -1, -1},
        {-1, 0, -1, 0, -1, 0, -1, 0, -1},
        {1, -1, 0, -1, 0, -1, 0, -1, 1},
        {-1, 0, -1, 0, -1, 0, -1, 0, -1},
        {0, -1, 0, -1, -1, -1, 0, -1, 0},
        {-1, 0, -1, 0, -1, 0, -1, 0, -1},
        {0, -1, 0, -1, 0, -1, 0, -1, 0},
        {-1, 0, -1, -1, -1, -1, -1, 0, -1},
        {0, -1, 0, -1, 0, -1, 0, -1, 0},
        {-1, 0, -1, 0, -1, 0, -1, 0, -1},
        {2, -1, 0, -1, 0, -1, 0, -1, 2},
        {-1, 0, -1, 0, -1, 0, -1, 0, -1},
        {-1, -1, 0, -1, 0, -1, 0, -1, -1},
        {-1, -1, -1, 0, -1, 0, -1, -1, -1},
        {-1, -1, -1, -1, 1, -1, -1, -1, -1}
    };
    
    isSelected = false;
    mouseHeld = false;
    yourMove = true;
    endGame = false;
    red = false;
    blue = false;
}

sf::CircleShape Hexxagon::initHexagon()
{
    sf::CircleShape hexagon(55.f, 6);
    hexagon.setOutlineColor(sf::Color::Transparent);
    hexagon.setOutlineThickness(10.f);
    
    return hexagon;
}

void Hexxagon::initHexagonField()
{
    for(int i = 0; i<this->field.size(); i++){
        for (int j = 0; j<this->field[i].size(); j++){
            
            if(this->field[i][j] == 0){
                sf::CircleShape hexagon = initHexagon();
                hexagon.setFillColor(sf::Color(128, 128, 128));
                hexagon.setPosition((i%2 ? 870 : 870) + j * 130.f, 30 + i * 85.f);
                figures.push_back(hexagon);
                figuresIndexes.push_back({i, j});
                
            }
            
            if(field[i][j] == 1){
                sf::CircleShape hexagon = initHexagon();
                hexagon.setFillColor(sf::Color::Red);
                hexagon.setPosition((i%2 ? 870 : 870) + j * 130.f, 30 + i * 85.f);
                figures.push_back(hexagon);
                figuresIndexes.push_back({i, j});
            }
            
            if(field[i][j] == 2){
                sf::CircleShape hexagon = initHexagon();
                hexagon.setFillColor(sf::Color::Cyan);
                hexagon.setPosition((i%2 ? 870 : 870) + j * 130.f, 30 + i * 85.f);
                figures.push_back(hexagon);
                figuresIndexes.push_back({i, j});
                
            }
        }
    }
}

void Hexxagon::initPanel()
{
    this->panelShape.setSize(sf::Vector2f(1200, 500));
    this->panelShape.setFillColor(sf::Color::White);
    this->panelShape.setPosition(sf::Vector2f(850, 450));
    this->panelShape.setOutlineColor(sf::Color::Black);
    this->panelShape.setOutlineThickness(5.f);
}

void Hexxagon::initFonts()
{
    if(!this->font1.loadFromFile("/Users/masagorosena/Desktop/2223s_20c_s27179/PJC/arial.ttf"))
    {
        return EXIT_FAILURE;
    }
}

void Hexxagon::initPointsWinHexagons()
{
    //Points Hexagon You
    this->pointsHexagonYou = sf::CircleShape(70.f, 6);
    this->pointsHexagonYou.setFillColor(sf::Color::Red);
    this->pointsHexagonYou.setPosition(sf::Vector2f(2500, 1100));
    
    //Points Hexagon Rival
    this->pointsHexagonRival = sf::CircleShape(70.f, 6);
    this->pointsHexagonRival.setFillColor(sf::Color::Cyan);
    this->pointsHexagonRival.setPosition(sf::Vector2f(2500, 1300));
    
    //Red Win Hexagon
    this->redWinHexagon = sf::CircleShape(100.f, 6);
    this->redWinHexagon.setFillColor(sf::Color::Red);
    this->redWinHexagon.setPosition(sf::Vector2f(1350, 500));
    this->redWinHexagon.setOutlineColor(sf::Color::Black);
    this->redWinHexagon.setOutlineThickness(5.f);
    
    //Blue Win Hexagon
    this->blueWinHexagon = sf::CircleShape(100.f, 6);
    this->blueWinHexagon.setFillColor(sf::Color::Cyan);
    this->blueWinHexagon.setPosition(sf::Vector2f(1350, 500));
    this->blueWinHexagon.setOutlineColor(sf::Color::Black);
    this->blueWinHexagon.setOutlineThickness(5.f);
}

//Constructor and destructor
Hexxagon::Hexxagon(bool gameType) : gameType(gameType)
{
    this->initVariables();
    this->initFonts();
    this->initHexagonField();
    this->initPanel();
    this->initPointsWinHexagons();
}

Hexxagon::Hexxagon()
{
    
}

Hexxagon::~Hexxagon()
{
    
}

//Functions
sf::Text Hexxagon::initWinText()
{
    sf::Text winText;
    if(red){
        winText = sf::Text("RED WIN!", font1, 150);
    } else{
        winText = sf::Text("BLUE WIN!", font1, 150);
    }
    
    winText.setFillColor(sf::Color::Black);
    winText.setPosition(sf::Vector2f(1140, 710));
    
    return winText;
}

bool Hexxagon::areThereMoves(sf::Color color)
{
    int count = 0;
    for (int i = 0; i<figures.size(); i++){
        if(figures[i].getFillColor() == color){
            if(this->countPossibleMoves(i) > 0){
                count++;
            }
        }
    }
    
    if(count == 0){
        return false;
    } else{
        return true;
    }
}

int Hexxagon::countPossibleMoves(int index){
    int i = figuresIndexes[index][0];
    int j = figuresIndexes[index][1];
    
    int count = 0;
    
    int figure = indexFigure(i+2, j);
    if(isValidField(figure) && figures[figure].getFillColor() == sf::Color(128, 128, 128)){
        count++;
    }
    
    figure = indexFigure(i-2, j);
    if(isValidField(figure) && figures[figure].getFillColor() == sf::Color(128, 128, 128)){
        count++;
    }
    int y = 1;
    for(int x = i-4; x<=i+4; x++){
        if(x == i-4 || x == i+4){
            figure = indexFigure(x, j);
            if(isValidField(figure) && figures[figure].getFillColor() == sf::Color(128, 128, 128)){
                count++;
            }
        } else{
            figure = indexFigure(x, j-y);
            if(isValidField(figure) && figures[figure].getFillColor() == sf::Color(128, 128, 128)){
                count++;
            }
            
            figure = indexFigure(x, j+y);
            if(isValidField(figure) && figures[figure].getFillColor() == sf::Color(128, 128, 128)){
                count++;
            }
            
            if(y == 1){
                y = 2;
            } else{
                y = 1;
            }
        }
    }
    
    return count;
}

std::vector<sf::Text> Hexxagon::countPoints()
{
    int red = 0;
    int blue = 0;
    
    for(int i = 0; i<figures.size(); i++){
        if (figures[i].getFillColor() == sf::Color::Red){
            red++;
        }
        
        if(figures[i].getFillColor() == sf::Color::Cyan){
            blue++;
        }
    }
    
    if(red > blue){
        this->red = true;
        this->blue = false;
    } else{
        this->red = false;
        this->blue = true;
    }
    
    std::vector<sf::Text> texts = {sf::Text(std::to_string(red), font1, 60), sf::Text(std::to_string(blue), font1, 60)};
    
    texts[0].setFillColor(sf::Color::Black);
    texts[1].setFillColor(sf::Color::Black);
    
    texts[0].setPosition(sf::Vector2f(2400, 1130));
    texts[1].setPosition(sf::Vector2f(2400, 1330));
    
    return texts;
}

int Hexxagon::findSelected()
{
    for (int i = 0; i<figures.size(); i++){
        if(figures[i].getOutlineColor() == sf::Color::White){
            return i;
        }
    }
}

void Hexxagon::clearField()
{
    for (int i = 0; i<figures.size(); i++){
        figures[i].setOutlineColor(sf::Color::Transparent);
    }
}

int Hexxagon::indexFigure(int i, int j)
{
    for (int x = 0; x<figuresIndexes.size(); x++){
        if(figuresIndexes[x][0] == i && figuresIndexes[x][1] == j){
            return x;
        }
    }
}

bool Hexxagon::isValidField(int index)
{
    return (index>=0 && index<figures.size());
}

bool Hexxagon::oneFigureSelected()
{
    for(int i = 0; i<figures.size(); i++){
        if(figures[i].getOutlineColor() == sf::Color::White){
            return true;
        }
    }
    return false;
}

bool Hexxagon::checkCollision(sf::CircleShape hexagon, sf::RenderWindow& window)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    return hexagon.getGlobalBounds().contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));
}

void Hexxagon::selectFigure(int i){
    if(!oneFigureSelected() && !isSelected){
        figures[i].setOutlineColor(sf::Color::White);
        isSelected = true;
        this->possibleMoves(i);
    } else{
        if(figures[i].getOutlineColor() == sf::Color::White){
            figures[i].setOutlineColor(sf::Color::Transparent);
            isSelected = false;
            clearField();
        }
    }
}

void Hexxagon::possibleMoves(int index)
{
    int i = figuresIndexes[index][0];
    int j = figuresIndexes[index][1];
    
    int figure = indexFigure(i+2, j);
    if(isValidField(figure) && figures[figure].getFillColor() == sf::Color(128, 128, 128)){
        figures[figure].setOutlineColor(sf::Color::Green);

    }
    
    figure = indexFigure(i-2, j);
    if(isValidField(figure) && figures[figure].getFillColor() == sf::Color(128, 128, 128)){
        figures[figure].setOutlineColor(sf::Color::Green);
    }
    int y = 1;
    for(int x = i-4; x<=i+4; x++){
        if(x == i-4 || x == i+4){
            figure = indexFigure(x, j);
            if(isValidField(figure) && figures[figure].getFillColor() == sf::Color(128, 128, 128)){
                figures[figure].setOutlineColor(sf::Color::Yellow);
            }
        } else{
            sf::Color color;
            if(x == i-1 || x == i+1){
                color = sf::Color::Green;
            } else{
                color = sf::Color::Yellow;
            }
            
            figure = indexFigure(x, j-y);
            if(isValidField(figure) && figures[figure].getFillColor() == sf::Color(128, 128, 128)){
                figures[figure].setOutlineColor(color);
            }
            
            figure = indexFigure(x, j+y);
            if(isValidField(figure) && figures[figure].getFillColor() == sf::Color(128, 128, 128)){
                figures[figure].setOutlineColor(color);
            }
            
            if(y == 1){
                y = 2;
            } else{
                y = 1;
            }
        }
    }
}

void Hexxagon::updateFigures(int index)
{
    int i = figuresIndexes[index][0];
    int j = figuresIndexes[index][1];
    
    int figure = indexFigure(i-2, j);
    if(isValidField(figure) && figures[figure].getFillColor() != sf::Color(128, 128, 128)){
        figures[figure].setFillColor(figures[index].getFillColor());
    }
    
    figure = indexFigure(i+2, j);
    if(isValidField(figure) && figures[figure].getFillColor() != sf::Color(128, 128, 128)){
        figures[figure].setFillColor(figures[index].getFillColor());
    }
    
    for(int x = i-1; x<=i+1; x+=2){
        figure = indexFigure(x, j-1);
        if(isValidField(figure) && figures[figure].getFillColor() != sf::Color(128, 128, 128)){
            figures[figure].setFillColor(figures[index].getFillColor());
        }
        
        figure = indexFigure(x, j+1);
        if(isValidField(figure) && figures[figure].getFillColor() != sf::Color(128, 128, 128)){
            figures[figure].setFillColor(figures[index].getFillColor());
        }
    }
}

std::vector<int> Hexxagon::computerAllPossibleMoves()
{
    // 0 - figure's index, 1 - best move index, 2 - 0(green), (1) - yellow
    std::vector<int> result = {0, 0, 0};
    int maxPoints = 0;
    int points = 0;
    
    for(int index = 0; index<figures.size(); index++){
        if(figures[index].getFillColor() == sf::Color::Cyan){
            
            int i = figuresIndexes[index][0];
            int j = figuresIndexes[index][1];
            
            int figure = indexFigure(i+2, j);
            if(isValidField(figure) && figures[figure].getFillColor() == sf::Color(128, 128, 128)){
                points = computerCountPossiblePoints(figure) + 1;
                if(points > maxPoints){
                    maxPoints = points;
                    result[0] = index;
                    result[1] = figure;
                    result[2] = 0;
                }
            }
            
            figure = indexFigure(i-2, j);
            if(isValidField(figure) && figures[figure].getFillColor() == sf::Color(128, 128, 128)){
                points = computerCountPossiblePoints(figure) + 1;
                if(points > maxPoints){
                    maxPoints = points;
                    result[0] = index;
                    result[1] = figure;
                    result[2] = 0;
                }
            }
            int y = 1;
            for(int x = i-4; x<=i+4; x++){
                if(x == i-4 || x == i+4){
                    figure = indexFigure(x, j);
                    if(isValidField(figure) && figures[figure].getFillColor() == sf::Color(128, 128, 128)){
                        points = computerCountPossiblePoints(figure);
                        if(points > maxPoints){
                            maxPoints = points;
                            result[0] = index;
                            result[1] = figure;
                            result[2] = 1;
                        }
                    }
                } else{
                    int count = 0;
                    if(x == i-1 || x == i+1){
                        count = 1;
                    } else{
                        count = 0;
                    }
                    
                    figure = indexFigure(x, j-y);
                    if(isValidField(figure) && figures[figure].getFillColor() == sf::Color(128, 128, 128)){
                        points = computerCountPossiblePoints(figure) + count;
                        if(points > maxPoints){
                            maxPoints = points;
                            result[0] = index;
                            result[1] = figure;
                            result[2] = 0;
                        }
                    }
                    
                    figure = indexFigure(x, j+y);
                    if(isValidField(figure) && figures[figure].getFillColor() == sf::Color(128, 128, 128)){
                        points = computerCountPossiblePoints(figure) + count;
                        if(points > maxPoints){
                            maxPoints = points;
                            result[0] = index;
                            result[1] = figure;
                            result[2] = 0;
                        }
                    }
                    
                    if(y == 1){
                        y = 2;
                    } else{
                        y = 1;
                    }
                }
            }
        }
    }
    return result;
}

int Hexxagon::computerCountPossiblePoints(int index)
{
    int i = figuresIndexes[index][0];
    int j = figuresIndexes[index][1];
    
    int points = 0;
    
    int figure = indexFigure(i-2, j);
    if(isValidField(figure) && figures[figure].getFillColor() != sf::Color(128, 128, 128)){
        points++;
    }
    
    figure = indexFigure(i+2, j);
    if(isValidField(figure) && figures[figure].getFillColor() != sf::Color(128, 128, 128)){
        points++;
    }
    
    for(int x = i-1; x<=i+1; x+=2){
        figure = indexFigure(x, j-1);
        if(isValidField(figure) && figures[figure].getFillColor() != sf::Color(128, 128, 128)){
            points++;
        }
        
        figure = indexFigure(x, j+1);
        if(isValidField(figure) && figures[figure].getFillColor() != sf::Color(128, 128, 128)){
            points++;
        }
    }
    return points;
}

void Hexxagon::move(int i)
{
    if(isSelected){
        int index = findSelected();
        if(figures[i].getOutlineColor() == sf::Color::Green){
            figures[i].setFillColor(figures[index].getFillColor());
            this->updateFigures(i);
            this->clearField();
            isSelected = false;
            yourMove = !yourMove;
        }
        
        if(figures[i].getOutlineColor() == sf::Color::Yellow){
            figures[i].setFillColor(figures[index].getFillColor());
            figures[index].setFillColor(sf::Color(128, 128, 128));
            this->updateFigures(i);
            this->clearField();
            isSelected = false;
            yourMove = !yourMove;
        }
    }
}

void Hexxagon::myMove(sf::RenderWindow& window)
{
    if(yourMove){
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(!mouseHeld){
                mouseHeld = true;
                for(int i = 0; i<figures.size(); i++){
                    if(checkCollision(figures[i], window)){
                        if(figures[i].getFillColor() == sf::Color::Red){
                            this->selectFigure(i);
                        }
                        if(figures[i].getFillColor() == sf::Color(128, 128, 128)){
                            this->move(i);
                        }
                    }
                }
            }
        } else{
            mouseHeld = false;
        }
    }
}

void Hexxagon::playerMove(sf::RenderWindow& window)
{
    if(!yourMove){
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(!mouseHeld){
                mouseHeld = true;
                for(int i = 0; i<figures.size(); i++){
                    if(checkCollision(figures[i], window)){
                        if(figures[i].getFillColor() == sf::Color::Cyan){
                            this->selectFigure(i);
                        }
                        if(figures[i].getFillColor() == sf::Color(128, 128, 128)){
                            this->move(i);
                        }

                    }
                }
            }
        } else{
            mouseHeld = false;
        }
    }
}

void Hexxagon::computerMove()
{
    if(!yourMove){
        std::vector<int> result = computerAllPossibleMoves();
        if(result[2] == 0){
            figures[result[1]].setFillColor(sf::Color::Cyan);
            this->updateFigures(result[1]);
            yourMove = !yourMove;
        } else{
            figures[result[1]].setFillColor(sf::Color::Cyan);
            figures[result[0]].setFillColor(sf::Color(128, 128, 128));
            this->updateFigures(result[1]);
            yourMove = !yourMove;
        }
    }
}

void Hexxagon::endGameOnePlayer()
{
    int red = 0;
    int cyan = 0;
    for (int i = 0; i<figures.size(); i++){
        if(figures[i].getFillColor() == sf::Color::Red){
            red++;
        }
        
        if(figures[i].getFillColor() == sf::Color::Cyan){
            cyan++;
        }
    }
    
    if(red == 0 || cyan == 0){
        this->endGame = true;
    }
}

void Hexxagon::endGameNotPossibleMovesRed()
{
    if(!areThereMoves(sf::Color::Red)){
        endGame = true;
    }
}

void Hexxagon::endGameNotPossibleMovesBlue(){
    if(!areThereMoves(sf::Color::Cyan)){
        endGame = true;
    }
}

void Hexxagon::gamePlayer(sf::RenderWindow& window)
{
    if(!endGame){
        std::vector<sf::Text> texts;
        
        this->endGameNotPossibleMovesRed();
        this->myMove(window);
        
        texts = this->countPoints();
        window.draw(texts[0]);
        window.draw(texts[1]);
        
        this->endGameOnePlayer();
        this->endGameNotPossibleMovesBlue();
        this->playerMove(window);
        
        texts = this->countPoints();
        window.draw(texts[0]);
        window.draw(texts[1]);
        
        this->endGameOnePlayer();
    } else{
        window.draw(this->panelShape);
        if(blue){
            window.draw(initWinText());
            window.draw(this->blueWinHexagon);
        }

        if(red){
            window.draw(initWinText());
            window.draw(this->redWinHexagon);
        }
        
        std::vector<sf::Text> texts;
        texts = this->countPoints();
        window.draw(texts[0]);
        window.draw(texts[1]);
    }
}

void Hexxagon::gameComputer(sf::RenderWindow& window)
{
    if(!endGame){
        std::vector<sf::Text> texts;
        
        this->endGameNotPossibleMovesRed();
        this->myMove(window);
        
        texts = this->countPoints();
        window.draw(texts[0]);
        window.draw(texts[1]);
        
        this->endGameOnePlayer();
        this->endGameNotPossibleMovesBlue();
        this->computerMove();
        
        texts = this->countPoints();
        window.draw(texts[0]);
        window.draw(texts[1]);
        
        this->endGameOnePlayer();
    } else{
        window.draw(this->panelShape);
        if(blue){
            window.draw(initWinText());
            window.draw(this->blueWinHexagon);
        }

        if(red){
            window.draw(initWinText());
            window.draw(this->redWinHexagon);
        }
        
        std::vector<sf::Text> texts;
        texts = this->countPoints();
        window.draw(texts[0]);
        window.draw(texts[1]);

    }
}

void Hexxagon::update(sf::RenderWindow& window)
{
    if(this->gameType){
        this->gamePlayer(window);
    } else{
        this->gameComputer(window);
    }
}

void Hexxagon::render(sf::RenderWindow& window)
{
    window.draw(this->pointsHexagonYou);
    window.draw(this->pointsHexagonRival);
    
    for(int i = 0; i<figures.size(); i++){
        window.draw(this->figures[i]);
    }

    this->update(window);
}
