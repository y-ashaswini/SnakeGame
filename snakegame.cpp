#include <iostream>     // for input output stream
#include <cstdlib>      // for random numbers, math
#include <windows.h>    // for setting coordinates, placing console pointers, etc.
#include <conio.h>      // for recording input output like keystrokes, etc.
#include <vector>       // for including vectors
 
using namespace std;

#define HEIGHT 20
#define WIDTH 60
#define H_char '|'
#define W_char '='

class Snake {
    private:
        int len;
        int vel;
        char direction;
        COORD pos;
        vector<COORD> body;

    public:
        Snake(COORD pos, int vel) {
            this->pos = pos;
            this->vel = vel;
            this->len = 1;
            this->direction = 'n';
        }
        int speed = 50;
        void change_dir(char dir) {
            this->direction = dir;
        }

        void setPos(int x, int y) {
            pos.X = x;
            pos.Y = y;
        }

        char get_dir() {
            return direction;
        }

        void inc_len() {
            this->len++;
            if(len < 5) speed = 50;
            else if(len < 10) speed = 40;
            else if(len < 10) speed = 30;
            else if(len < 20) speed = 30;
            else if(len < 30) speed = 20;
            else speed = 0;
        }


        void move_snake() {
            switch(direction) {
                case('u') : pos.Y -= vel; break;
                case('d') : pos.Y += vel; break;
                case('l') : pos.X -= vel; break;
                case('r') : pos.X += vel; break;
            }
            body.push_back(pos);
            if(body.size() > len) body.erase(body.begin());
        }

        COORD get_pos() {
            return pos;
        }

        vector<COORD> get_body() {
            return body;
        }
};

class Food {
    private:
        COORD pos;
    public:
        void generate_pos() {
            pos.X = (rand() % (WIDTH-2)) + 1;
            pos.Y = (rand() % (HEIGHT-2)) + 1;
        }

        COORD get_pos() {
            return pos;
        }
};

Snake snake({WIDTH/2, HEIGHT/2}, 1);
Food food;



void board() {
    COORD snake_pos = snake.get_pos();
    COORD food_pos = food.get_pos();
    vector<COORD> snake_body = snake.get_body();
    
    for(int i=0; i<HEIGHT; i++) {
        cout << H_char;
        for(int j=1; j<WIDTH-1; j++) {
            if(i==0 || i == HEIGHT - 1) cout << W_char;
            else if(i == food_pos.Y && j == food_pos.X) cout << "*";
            else {
                bool isBodyPart = false;
                for(int k=0; k<snake_body.size(); k++) {
                    if(i == snake_body[k].Y && j == snake_body[k].X) {
                        cout << 'O';
                        isBodyPart = true;
                        break;
                    }
                }
                if(!isBodyPart) cout << ' ';
            }
        }
        cout << H_char << "\n";
    }
    int difficulty = snake.speed < 50 ? (snake.speed < 40 ? (snake.speed < 30 ? (snake.speed < 20 ? (snake.speed < 10 ? 6 : 5) : 4) : 3 ) : 2 ): 1;
    cout << "> Coordinates of Snake : (" << snake_pos.X << "," << snake_pos.Y  << ")        " << endl;
    cout << "> Your Score : " << snake_body.size()<< endl;
    cout << "> Difficulty Level : " << difficulty << endl;
    cout << "> Keys: W-A-S-D\n> Press SPACE to EXIT" << endl;
    
}


int main() {
    system("cls");
    int in = 1;
    food.generate_pos();
    while(in) {
        board();
        if(kbhit()) {
            // w = up, a = left, s = down, d = right
            switch(getch()) {
                case 'w': snake.change_dir('u'); break;
                case 'a': snake.change_dir('l'); break;
                case 's': snake.change_dir('d'); break;
                case 'd': snake.change_dir('r'); break;
                case ' ': in = 0; break;
            }
        }

        char dir = snake.get_dir();

        COORD snake_pos_main = snake.get_pos();
        COORD food_pos_main = food.get_pos();
        
        if(snake_pos_main.Y == 0 || snake_pos_main.Y == HEIGHT-1 || snake_pos_main.X == 0 || snake_pos_main.X == WIDTH-1) {
            in=0;
        }
        if(!in) break;

        // if (snake_pos_main.Y == 0) {
        //     snake.setPos(snake_pos_main.X, HEIGHT-1);
        // }
        
        // if(snake_pos_main.Y == HEIGHT-1) {
        //     snake.setPos(snake_pos_main.X, 1);
        // }
        
        // if(snake_pos_main.X == 0){
        //     snake.setPos(WIDTH-1, snake_pos_main.Y);
        // }
        
        // if(snake_pos_main.X == WIDTH-1) {
        //     snake.setPos(1, snake_pos_main.Y);
        // }

        snake.move_snake();
        Sleep(snake.speed);

        if((snake_pos_main.X == food_pos_main.X) && (snake_pos_main.Y == food_pos_main.Y)) {
            snake.inc_len();
            food.generate_pos();
        }
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0,0});

    }

    if(!in) {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, HEIGHT+10});
        cout << "-------------------------\n|\tGAME OVER!\t|\n-------------------------" << endl;
    }

    return 0;
}