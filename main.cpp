#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <sstream>

#ifdef SFML_SYSTEM_IOS
#include <SFML/Main.hpp>
#endif

using namespace std;
using namespace sf;

int windowWidth = 1000;
int windowHeight = 700;
int batscore = 0;
int lives = -1;


int main () {
    
    RenderWindow window(VideoMode(windowWidth, windowHeight), "Pong");


    
    
    // creating objects
        //    Bat bat(windowWidth/2, windowHeight-20);
        //    Ball ball(windowWidth/2+50, windowHeight/2);
        //    AIBat aibat(windowWidth/2, 10);
    
    while (window.isOpen()) {
    
    Event event;
    while (window.pollEvent(event)) {
        if(event.type==Event::Closed)
            window.close();
    }
    
       
        
        //USER INPUT
        
        if(((event.type == event.KeyPressed) && event.key.code == Keyboard::M)) {
            multiPlayer();
        }
        
    if(((event.type == event.KeyPressed) && event.key.code == Keyboard::S)) {
    
        singlePlayer();
        }
        
        //LOGIC//////////
        ball.reboundSides();
        ball.passTop();
        ball.passBottom();
        
        if (ball.getBallFloatRect().intersects(bat.getBatFloatRect())) {
     ball.reboundBatorAI();
                        
        }
        
        if (ball.getBallFloatRect().intersects(aibat.getAIBatFloatRect())) {
        
ball.reboundBatorAI();
                           
           }

        if (ball.getBallFloatRect().left > (aibat.getAIBatFloatRect().left) + 50) {
              if (aibatcounter % 60 == 0) aibat.moveAIBatRight();
        }
        
        if (ball.getBallFloatRect().left < (aibat.getAIBatFloatRect().left) + 50) {
              if (aibatcounter % 60 == 0) aibat.moveAIBatLeft();
        }
    


        if (ball.getBallPosition.x > windowWidth)
            aibat.AIBatSpeedReverse();
      
        
        //TEXT and FONT
        std::stringstream ss;
                
        ss << "Score: " << batscore <<"       Lives: " << lives;
         
        Text text;
        Font font;
        font.loadFromFile("Nexa Light.otf");

        text.setFont(font);
        text.setCharacterSize(45);
        text.setFillColor(sf::Color::White);
        
        text.setString(ss.str());

        
        // PAUSE MESSAGE
        
        std::stringstream ss2;
        ss2 << "You ran out of lives. \n\nYour score is " << batscore <<".\n\nPress any key to play again.";
         Text pauseMessage;
        
        
        pauseMessage.setCharacterSize(50);
         pauseMessage.setPosition(windowWidth/2-400, windowHeight/2-100);
        pauseMessage.setFont(font);
    pauseMessage.setString(ss2.str());
        // START MESSAGE
            std::stringstream ss3;
            ss3 << "Welcome to Pong.\n\nPress M for multiplayer and S for single player";
             Text startMessage;
            
            startMessage.setCharacterSize(60);
            startMessage.setPosition(windowWidth/2-400, windowHeight/2-100);
            startMessage.setFont(font);
            startMessage.setString(ss3.str());
        // UPDATE
        // if(aibatcounter == 1000000) {
        //     aibatcounter = 0;
        // }
        //aibatcounter++;
        ball.update();
        bat.update();
        aibat.update();
        // DRAW
        window.clear(Color(26, 128, 182, 255));
       
        if (lives == 0) {
            
    window.draw(pauseMessage);
            ball.stop();
            
        if(event.type == event.KeyPressed) {
            lives = 3;
            batscore = 0;
            ball.go();
                 }
        }
        else if (lives == -1) {
            window.draw(startMessage);
            ball.stop();
            if(event.type == event.KeyPressed) {
                     lives = 3;
                     batscore = 0;
                     ball.go();
                          }
                 }

        
        else {
        window.draw(bat.getBatObject());
        window.draw(ball.getBallObject());
            
            window.draw(text);
            window.draw((aibat.getAIBatObject()));
        }
        window.display();
    }
    
    return 0;
}