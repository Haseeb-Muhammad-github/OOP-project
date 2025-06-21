#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h" 
using namespace sf;
class Menu {
public:
    Menu() {}
     Game game;
     score_window score;
    void display_menu()
    {
        
        RenderWindow window(sf::VideoMode(400, 300), "Menu");//window for menu
        Sprite picture;
        Texture   pic;
        pic.loadFromFile("img/background.jpg");
        picture.setTexture(pic);
        picture.setScale(2, 1);
        Font font;
        if (!font.loadFromFile("arial.ttf")) {
            cout << "Error loading font\n";
            return;
        }

        // Create text objects for menu options
        Text startGame( "1) Start a new game", font );
        Text Scores( "2) See high-scores" , font);
        Text help( "3) Exit", font);
        // Text exitText( "4) Exit", font);

         //setting the position of all text in the menu window
        startGame.setPosition(20, 20);
        Scores.setPosition(20, 60);
        help.setPosition(20, 100);
        // exitText.setPosition(20, 140);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) 
            {
                if (event.type == Event::Closed) {
                    window.close();
                }
                   else if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::Num1) {
                        game.start_game();   //starts the game
                    }
                    else if (event.key.code == Keyboard::Num2) {
                        score.render();   // calling the function from score class for the score window

                    }
                    
                    else if (event.key.code == Keyboard::Num3) {
                       //closes the game  window 
                        window.close();
                    }
                }
            }

            window.draw(picture);
            window.draw(startGame);
            window.draw(Scores);
            window.draw(help);
            // window.draw(exitText);
            window.display();
            window.clear(Color::Black);
        }
    }
};
