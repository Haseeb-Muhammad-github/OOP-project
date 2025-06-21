#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include<fstream>
#include<sstream>
using namespace std;

const char title[] = "OOP-Project, Spring-2023";
using namespace sf;

const int numSmallBoxes = 2; // Set the number of small boxes
const  int numMaps = 37; // Set the number of Maps
const int numfood = 60;
//me: this class will serve as base class for the  player class and oponent class
class Box
{
public:
    RectangleShape shape;
    int direction; // Direction of movement for the box

    // Default constructor
    Box()
        : direction(0) // Set a default direction (you can adjust as needed)
    {
        // Set default properties or leave them uninitialized as needed
    }

    // Parameterized constructor
    Box(float x, float y, float width, float height, int initialDirection)
        : direction(initialDirection)
    {
        shape.setSize(Vector2f(width, height));
        shape.setPosition(x, y);
        shape.setFillColor(Color::Blue); // Adjust the color as needed
    }

    virtual  void move(float speed, float offsetY)
    {
        shape.move(speed * direction, offsetY);
    }
};
//me from here starting my code for the player car
class Player : public Box {
public:
    Player(float x, float y) : Box(x, y, 30.f, 30.f, -1) {
        shape.setFillColor(Color::Green);
    }
    void move(float speed, float offsetY)  override
    {        
        //this condition for the boundaries of the window
        if (shape.getPosition().y + offsetY > 0 && shape.getPosition().y + shape.getSize().y + offsetY < 780)
            shape.move(speed * direction, offsetY);
    }
};
class Opponent : public Box 
{
public:
    Opponent(float x, float y) : Box(x, y, 30.f, 30.f, -1) 
    {
        shape.setFillColor(Color::Red);
    }
    void move(float speed, float offsetY)  override
    {
        if (shape.getPosition().y + offsetY > 0 && shape.getPosition().y + shape.getSize().y + offsetY < 780)
            shape.move(speed * direction, offsetY);
    }
};
class Map
{
public:
    RectangleShape shape;
    Map() {}
    Map(float x, float y, float width, float height)
    {
        shape.setSize(Vector2f(width, height));
        shape.setPosition(x, y);
        shape.setFillColor(Color::White);
    }
};
class Food 
{
public:
    RectangleShape shape;

    Food() {}

    Food(float x, float y, float width, float height) 
    {
        shape.setSize(Vector2f(width, height));
        shape.setPosition(x, y);
        shape.setFillColor(Color :: Red);
    }

   virtual void food_colour()=0;
    virtual ~Food(){}
};

// Derived classes for specific types of food

class Red_Food : public Food 
{
public:
    Red_Food(){}
    Red_Food(float x, float y) 
    {
        shape.setSize(Vector2f(30.f, 10.f));
        shape.setPosition(x, y);
        shape.setFillColor(Color :: Red);
    }
    void food_colour() override
    {
        shape.setFillColor(Color :: Red);
    }
    ~Red_Food() override 
    {}
};

class Green_Food : public Food 
{
public:
//making circle for the food 
    CircleShape shape;
    Green_Food(){}
    Green_Food(float x, float y) 
    {
        shape.setRadius(10.f);
        shape.setPosition(x, y);
       
    }
    void food_colour() override
    {
        shape.setFillColor(Color :: Green);
    }

    ~Green_Food() override
    {} 
};

class Orange_Food : public Food 
{
public:
    ConvexShape shape;
    Orange_Food(){}
    // parametrized constructor for just adjusting the dimensions of food 
    Orange_Food(float x, float y) 
    {
        shape.setPointCount(6);
        shape.setPoint(0, Vector2f(0.f, 5.f));
        shape.setPoint(1, Vector2f(15.f, 0.f));
        shape.setPoint(2, Vector2f(30.f, 5.f));
        shape.setPoint(3, Vector2f(30.f, 15.f));
        shape.setPoint(4, Vector2f(15.f, 20.f));
        shape.setPoint(5, Vector2f(0.f, 15.f));

        shape.setPosition(x, y);
        
    }

    void food_colour() override
    {
        shape.setFillColor(Color :: Yellow);
    }

    ~Orange_Food() override
    {}
};

class White_Food : public Food 
{
public:
  //a class  of sfml for making of convex shape 
    ConvexShape shape;
    White_Food(){}
    White_Food(float x, float y) 
    {
        shape.setPointCount(3);
        shape.setPoint(0, Vector2f(0.f, 0.f));
        shape.setPoint(1, Vector2f(30.f, 0.f));
        shape.setPoint(2, Vector2f(15.f, 20.f));

        shape.setPosition(x, y);
        // shape.setFillColor(Color :: White);
    }
     void food_colour() override
    {
        shape.setFillColor(Color :: White);
    }

    ~White_Food() override
    {}
};
//for file handling 
struct Score 
{    
    int score;
};
Score readHighestScore() 
{
    std::ifstream inputFile("score.txt");
    Score highestScore;
    highestScore.score=INT32_MIN;
     
    if (inputFile.is_open()) 
    {
    } else {
        std::cerr << "Unable to open the file for reading.\n";
    }
    int scores;
        while (inputFile  >> scores) 
        {
            if(scores>highestScore.score){
                highestScore.score=scores;
            }
        }
        inputFile.close();

    return highestScore;
}
                                      //using just for the input in file  
void score_file( const Score &  score) 
{
    std::ofstream outputFile("score.txt", std::ios::app);

    if (outputFile.is_open()) 
    {
        outputFile << score.score << "\n";
        outputFile.close();
    } else 
    {
        std::cerr << "Unable to open the file for writing.\n";
    }
}
class score_window
{
    public:
    void render(){
         sf::RenderWindow window(sf::VideoMode(400, 200), "Game Scores");

    // Read the highest score
    Score highestScore = readHighestScore();
    
    //   std:: ifstream output("score.txt");
    std:: stringstream out;

     out<<"scores : "<<highestScore.score;
    // Create a text object to display the score
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font.\n";
        
    }

    sf::Text scoreText(out.str(), font , 20);
    scoreText.setPosition(50, 50);
    scoreText.setFillColor(sf::Color::White);

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Clear the window
        window.clear();

        // Draw the score text
        window.draw(scoreText);

        // Display the contents of the window
        window.display();
       } 
    }
};
//for the score increment
class GamePoint
{
public:
    int score;

    GamePoint() : score(0) {}

    void score_red()
    {
        score += 10;
        
        Score in_score;
        in_score.score=score;
        score_file(in_score);
    }
    void score_white()
    {
        score += 10;
        Score in_score;
        in_score.score=score;
        score_file(in_score);
    }
    void score_green()
    {
        score += 20;
        Score in_score;
        in_score.score=score;
        score_file(in_score);
    }
    void score_orange()
    {
        score += 10;
        Score in_score;
        in_score.score=score;
        score_file(in_score);
    }
    int getScore() 
    {
        return score;
    }
};


class Game
{
public:
    Sprite background; // Game background sprite
    Texture bg_texture;
    Box smallBoxes[numSmallBoxes]; // Declare the array here
    int direction = 1; // Variable to store the direction of movement
    
    Box player;//player in green
    Box enemy;
    Map Maps[numMaps]; // Declare the array for Maps
   

    //Declaring array of pointers for the different typres of food
    Red_Food * red_food[29]; 
    White_Food *  white_food[7];
    Orange_Food * orange_food[7];
    Green_Food *  green_food[9];
     

    GamePoint gamePoint;
    Font font;
    Text scoreText;

    Game()
    {
        bg_texture.loadFromFile("img/background.jpg");
        background.setTexture(bg_texture);
        background.setScale(2, 1.5);
        initializeSmallBoxes();
        initializeFood();
        if (!font.loadFromFile("arial.ttf")) 
        {
            cout << "Error loading font!" << endl;
        }

         scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(Color::Yellow);
        scoreText.setPosition(340.f, 370.f);
        void updateScoreText();
        // void updateScoreText();

    }

    ~Game() {
        for(int i=0; i<7; i++)
        {
        {    delete orange_food[i];
            delete  white_food[i];
        }
        
        for(int x=0; x<29; x++)
             delete red_food[x];
        }
        for(int s=0; s<9; s++){
            delete green_food[s];
        }
            

    }
    void initializeSmallBoxes()
    {
        // Add code here to initialize small boxes as needed
        smallBoxes[0] = Opponent(200.f, 300.f); // Initial direction is 1 (right)
        smallBoxes[1] = Player(400.f, 500.f);
        player.shape.setSize(Vector2f(30, 30));
        player.shape.setFillColor(Color :: Cyan);  
        
        
        //Maps    represnet the map of the game  i.e maze of the game

        Maps[0] = Map(0.f, 0.f, 20.f, 760.f);    //left full Map
        Maps[1] = Map(0.f, 760.f, 780.f, 40.f); //down full Map
        Maps[2] = Map(760.f, 0.f, 20.f, 760.f); //right full Map
        Maps[3] = Map(0.f, 0.f, 760.f, 20.f);   //up full Map
        Maps[4] = Map(90.f, 70.f, 20.f, 280.f); //left 2nd half up vertical Map
        Maps[5] = Map(90.f, 440.f, 20.f, 260.f);//left 2nd half down vertical Map
        Maps[6] = Map(670.f, 70.f, 20.f, 280.f);//right 2nd half up vertical Map
        Maps[7] = Map(670.f, 440.f, 20.f, 260.f);//right 2nd half down vertical Map
        Maps[8] = Map(90.f, 70.f, 220.f, 20.f);  //left 2nd half horizontal up Map
        Maps[9] = Map(470.f, 70.f, 220.f, 20.f); //right 2nd half horizontal up Map
        Maps[10] = Map(90.f, 680.f, 220.f, 20.f);//left  2nd half down horizontal Map
        Maps[11] = Map(470.f, 680.f, 220.f, 20.f);//right 2nd half down horizontal Map
        Maps[12] = Map(160.f, 140.f, 20.f, 210.f);//left 3rd half up vertical Map
        Maps[13] = Map(160.f, 140.f, 150.f, 20.f);//left 3rd half up horizontal Map
        Maps[14] = Map(470.f, 140.f, 150.f, 20.f);//right 3rd half up horizontal Map
        Maps[15] = Map(600.f, 140.f, 20.f, 210.f);//right 3rd half up vertical Map
        Maps[16] = Map(160.f, 440.f, 20.f, 170.f);//left 3rd half down vertical Map 
        Maps[17] = Map(160.f, 610.f, 150.f, 20.f); //left 3rd half down horizontal Map
        Maps[18] = Map(470.f, 610.f, 150.f, 20.f);//right 3rd half down horizontal Map
        Maps[19] = Map(600.f, 440.f, 20.f, 170.f);//right 3rd half down vertical Map
        Maps[20] = Map(240.f, 210.f, 20.f, 140.f);//left 4th half up vertical Map
        Maps[21] = Map(530.f, 210.f, 20.f, 140.f);//right 4th half up vertical Map
        Maps[22] = Map(240.f, 440.f, 20.f, 120.f);//left 4th half down vertical Map
        Maps[23] = Map(530.f, 440.f, 20.f, 120.f);//right 4th half down vertical Map
        Maps[24] = Map(240.f, 210.f, 70.f, 20.f); //left 4th half up horizontal Map
        Maps[25] = Map(470.f, 210.f, 70.f, 20.f); //right 4th half up horizontal Map
        Maps[26] = Map(240.f, 540.f, 70.f, 20.f); //left 4th half down horizontal Map
        Maps[27] = Map(470.f, 540.f, 80.f, 20.f); //right 4th half down horizontal Map
        Maps[28] = Map(320.f, 330.f, 150.f, 20.f);//uo middle box Map
        Maps[30] = Map(320.f, 440.f, 160.f, 20.f);// down middle box Map
        Maps[31] = Map(320.f, 330.f, 20.f, 120.f);//left middle box Map
        Maps[32] = Map(460.f, 330.f, 20.f, 120.f);//right middle box Map


        
    }
    

    void drawGameObjects(RenderWindow& window)
    {

        //  for the white maze
        for (int i = 0; i < numMaps; ++i)
        {
            window.draw(Maps[i].shape);
        }
          
          //for the red food
          for(int f=0; f<29; f++)
          {
            red_food[f]->food_colour();
            window.draw(red_food[f]->shape);

          }
          //loop for the green food
        for (int s = 0; s <9 ; s++)
        {   green_food[s]->food_colour();
            window.draw(green_food[s]->shape);
       
        //for the white coloured food  and orange coloured food   
        for(int h=0; h<7; h++)
        {
            white_food[h]->food_colour();
            orange_food[h]->food_colour();
            window.draw(orange_food[h]->shape);
            window.draw(white_food[h]->shape);
        }
           
        }

    }
    void updateScoreText()
    {//used to convert score into string
        scoreText.setString("Score:" + to_string(gamePoint.getScore()));
    }
    void start_game()
    {

           bool left= true;
        bool right= false;
        bool down= false;
        bool up= false;

        bool stop = false;
            float speed = 2.5f;


        srand(time(0));
        RenderWindow window(VideoMode(780, 780), title);
        Clock clock;
        float timer = 0;

        while (window.isOpen())
        {
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;

            Event e;
            while (window.pollEvent(e))
            {
                if (e.type == Event :: Closed)
                    window.close();
                //me : 
                if (e.type == Event :: KeyPressed)//events for the checking of the key pressing checking on the game window
                {   
                      if(e.key.code == Keyboard :: Left)
                      {
                        if(stop){
                            stop = false;
                        }
                        left = true;
                        right = false;
                        up = false;
                        down = false;
                        

                    }
                     
                    else if(e.key.code == Keyboard :: Right)
                    {
                        if(stop){
                            stop = false;
                            player.shape.move(0, speed);
                        }
                        left = false;
                        right = true;
                        up = false;
                        down = false;

                    }
                    else if(e.key.code == Keyboard :: Up)
                    {
                        if(stop)
                            stop = false;
                        
                        left = false;
                        right = false;
                        up = true;
                        down = false;
                        player.shape.move(0, -speed);

                    }
                    else if(e.key.code == Keyboard :: Down)
                    {
                        if(stop)
                            stop = false;
                        
                        left = false;
                        right = false;
                        up = false;
                        down = true;
                    }
                }
             
             
          
             //loop for collision detection of white rectangles
             int foods=7;
             for(int g=0; g<foods; g++)
             {      
                    FloatRect playerBounds = player.shape.getGlobalBounds();
                    FloatRect white_foodBound = white_food[g]->shape.getGlobalBounds();
                    FloatRect orange_foodBound =orange_food[g]->shape.getGlobalBounds();
                    if (playerBounds.intersects(white_foodBound))
                    {
                        // Collision detected, handle it here
                        white_food[g]->shape.setPosition(-1200.f, +1200.f);
                        gamePoint.score_red();
                        updateScoreText(); // Update the score text
                        // cout << "Score:" << gamePoint.getScore() << endl;


                    
                       }
                    
                    if (playerBounds.intersects(orange_foodBound))
                    {
                        // Collision detected, handle it here
                        orange_food[g]->shape.setPosition(-1200.f, +1200.f);
                        // white_food[i].shape.setPosition(-1200.f, +1200.f);
                        gamePoint.score_orange();
                        updateScoreText(); // Update the score text
                        // cout << "Score:" << gamePoint.getScore() << endl;

                    }
             }
             
             for(int x=0; x<29; x++)
             {
                    FloatRect playerBounds = player.shape.getGlobalBounds();
                    FloatRect red_foodBound = red_food[x]->shape.getGlobalBounds();
                    if (playerBounds.intersects(red_foodBound))
                    {
                        // Collision detected, handle it here
                        red_food[x]->shape.setPosition(-1200.f, +1200.f);
                       
                        gamePoint.score_white();
                        updateScoreText(); // Update the score text
                        // cout << "Score:" << gamePoint.getScore() << endl;

                    }

             }
                for (int s = 0; s < 9; s++)
                {   FloatRect playerBounds = player.shape.getGlobalBounds();
                    
                    FloatRect green_foodBound = green_food[s]->shape.getGlobalBounds();
                    if (playerBounds.intersects(green_foodBound))
                    {
                        // Collision detected, handle it here
                        green_food[s]->shape.setPosition(-1200.f, +1200.f);
                        gamePoint.score_green();
                        updateScoreText(); // Update the score text

                    }
                }
            }
            window.clear(Color::Black);
            window.draw(background);

        

            // for (int i = 0; i < numSmallBoxes; ++i)
            
                float speed = 2.0f;
                smallBoxes[0].move(speed, 0.0f);
                if (smallBoxes[0].shape.getPosition().x + smallBoxes[0].shape.getSize().x > window.getSize().x
                ||
                    smallBoxes[0].shape.getPosition().x < 0)
                {
                    //  cout<<"position cvalue:"<<smallBoxes[i].shape.getPosition().x<<"\n";
                    smallBoxes[0].direction = -smallBoxes[0].direction;
                }
                
                // window.draw(smallBoxes[i].shape);
                
                //checks for the four boundaries of the window for the player 
             if(left && !stop){
                if(!(player.shape.getPosition().x == 0) ){
                    player.shape.move(-speed, 0);
                }
            }
            else if(right && !stop){
                if(!(player.shape.getPosition().x >= 770)){
                    player.shape.move(speed, 0);
                }
            }
            else if(up && !stop){
                if(!(player.shape.getPosition().y <= 0 )){
                    player.shape.move(0, -speed);

                }
            }
            else if(down && !stop){
                if(!(player.shape.getPosition().y >= 770)){
                    player.shape.move(0, speed);
                }
            }
             //checks if the player is on the edge then it stops        
            if(player.shape.getPosition().y == 770 || player.shape.getPosition().y == 0 || 
            player.shape.getPosition().x == 770 || player.shape.getPosition().y == 0)
            {
                stop = true;
            }

           
            for (int i = 0; i < numMaps; ++i)
            {
                window.draw(Maps[i].shape);
                drawGameObjects(window);
            }
            window.draw(scoreText);
            window.draw(smallBoxes[0].shape);
            window.draw(player.shape);  
            window.display();
        }
    }
    void initializeFood()
    {
        //Red food
        red_food[0] = new  Red_Food(40.f, 40.f);
        red_food[1] =new Red_Food(240.f, 40.f);
        red_food[2] =new Red_Food(40.f, 720.f);
        red_food[3] =new Red_Food(130.f, 720.f);
        red_food[4] =new Red_Food(240.f, 720.f);
        red_food[5] =new Red_Food(520.f, 720.f);
        red_food[6] =new Red_Food(610.f, 720.f);
        red_food[7] =new Red_Food(700.f, 550.f);
        red_food[8] =new Red_Food(700.f, 310.f);
        red_food[9] =new Red_Food(700.f, 130.f);
        red_food[10] =new Red_Food(700.f, 40.f);
        red_food[11] =new Red_Food(120.f, 220.f);
        red_food[12] =new Red_Food(120.f, 310.f);
        red_food[13] =new Red_Food(120.f, 460.f);
        red_food[14] =new Red_Food(120.f, 550.f);
        red_food[15] =new Red_Food(250.f, 640.f);
        red_food[16] =new Red_Food(630.f, 640.f);
        red_food[17] =new Red_Food(630.f, 550.f);
        red_food[18] =new Red_Food(630.f, 460.f);
        red_food[19] =new Red_Food(630.f, 220.f);
        red_food[20] =new Red_Food(630.f, 110.f);
        red_food[21] =new Red_Food(240.f, 180.f);
        red_food[22] =new Red_Food(200.f, 220.f);
        red_food[23] =new Red_Food(200.f, 310.f);
        red_food[24] =new Red_Food(200.f, 550.f);
        red_food[25] =new Red_Food(240.f, 580.f);
        red_food[26] =new Red_Food(500.f, 580.f);
        red_food[27] =new Red_Food(560.f, 310.f);
        red_food[28] =new Red_Food(560.f, 220.f);

        //White  food
        white_food[0] = new  White_Food(130.f, 40.f);
        white_food[1] = new  White_Food(40.f, 220.f);
        white_food[2] = new  White_Food(40.f, 630.f);
        white_food[3] = new  White_Food(700.f, 720.f);
        white_food[4] = new  White_Food(480.f, 40.f);
        white_food[5] = new  White_Food(120.f, 640.f);
        white_food[6] = new  White_Food(560.f, 530.f);

        //Orange food will
        orange_food[0] =new Orange_Food(40.f, 130.f);
        orange_food[1] =new Orange_Food(40.f, 310.f);
        orange_food[2] =new Orange_Food(40.f, 460.f);
        orange_food[3] =new Orange_Food(700.f, 630.f);
        orange_food[3] =new Orange_Food(700.f, 630.f);
        orange_food[4] =new Orange_Food(700.f, 220.f);
        orange_food[5] =new Orange_Food(240.f, 110.f);
        orange_food[6] =new Orange_Food(490.f, 180.f);

        //Green  food
        green_food[0] =new Green_Food(40.f, 550.f);
        green_food[1] =new Green_Food(700.f, 460.f);
        green_food[2] =new Green_Food(590.f, 40.f);
        green_food[3] =new Green_Food(120.f, 110.f);
        green_food[4] =new Green_Food(490.f, 640.);
        green_food[5] =new Green_Food(630.f, 310.f);
        green_food[6] =new Green_Food(490.f, 110.f);
        green_food[7] =new Green_Food(200.f, 460.f);
        green_food[8] =new Green_Food(560.f, 460.f);
     
    }
};

