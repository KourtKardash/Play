#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <bits/stdc++.h>
using namespace sf;
using namespace std;
struct node {
    double func;
    int pochatok_x;
    int pochatok_y;
    int kinec_x;
    int kinec_y;
    node *next;
    node *to_enemy;
};
CircleShape fishki[18]; //figures
RectangleShape cells[8][8];
int board[8][8] =
    {0,1,2,-1,-1,-1,-1,-1,
     3,4,5,-1,-1,-1,-1,-1,
     6,7,8,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,9,10,11,
     -1,-1,-1,-1,-1,12,13,14,
     -1,-1,-1,-1,-1,15,16,17};

bool check_stupor() {
    if(board[0][0] == 0 && (board[0][1] == -1 || board[0][1] > 8) && (board[0][2] == -1 || board[0][2] > 8)
       && (board[1][0] == -1 || board[1][0] > 8) && (board[2][0] == -1 || board[2][0] > 8) && (board[1][1] == -1 || board[1][1] > 8)
       && (board[1][2] == -1 || board[1][2] > 8) && (board[2][1] == -1 || board[2][1] > 8) && (board[2][2] == -1 || board[2][2] > 8)) return true;
    else if(board[0][1] == 0 && (board[0][0] == -1 || board[0][0] > 8) && (board[0][2] == -1 || board[0][2] > 8)
       && (board[1][0] == -1 || board[1][0] > 8) && (board[2][0] == -1 || board[2][0] > 8) && (board[1][1] == -1 || board[1][1] > 8)
       && (board[1][2] == -1 || board[1][2] > 8) && (board[2][1] == -1 || board[2][1] > 8) && (board[2][2] == -1 || board[2][2] > 8)) return true;
    else return false;
}
void ins_head(node *&L, double s, int xp, int yp, int xk, int yk) {
    node *q = new node;
    q->func = s;
    q->pochatok_x = xp;
    q->pochatok_y = yp;
    q->kinec_x = xk;
    q->kinec_y = yk;
    q->to_enemy = NULL;
    q->next = NULL;
    L = q;
    return;
}
void ins_after(node *&L, double s, int xp, int yp, int xk, int yk) {
    node *q = new node;
    q->func = s;
    q->pochatok_x = xp;
    q->pochatok_y = yp;
    q->kinec_x = xk;
    q->kinec_y = yk;
    q->next = NULL;
    q->to_enemy = NULL;
    L->next = q;
    return;
}
void congr() {
    RenderWindow w(VideoMode(280 , 180) , "You won");
    Image i;
    i.loadFromFile("21329-150x150-removebg-preview.png");
    Texture t; t.loadFromImage(i);
    Sprite s(t); s.setPosition(85, 15);
    while(w.isOpen()) {
        Event e;
        while(w.pollEvent(e)) {
            switch(e.type) {
            case Event::Closed:
                w.close();
            //case Event::KeyPressed:
            //    if(e.key.code == Keyboard::Enter) return;
            }
        }
        w.clear(Color(72,118,255));
        w.draw(s);
        w.display();
    }
}
void sorry() {
    RenderWindow w(VideoMode(280 , 180) , "You lose");
    Image i; i.loadFromFile("21333-150x150-removebg-preview.png");
    Texture t; t.loadFromImage(i);
    Sprite s(t); s.setPosition(5,15);
    while(w.isOpen()) {
        Event e;
        while(w.pollEvent(e)) {
            switch(e.type) {
            case Event::Closed:
                w.close();
            //case Event::KeyPressed:
            //    if(e.key.code == Keyboard::Enter) return;
            }
        }
        w.clear(Color(72,118,255));
        w.draw(s);
        w.display();
    }
}
void massive() {
    board[0][0] = 0; board[0][1] = 1; board[0][2] = 2;
    board[1][0] = 3; board[1][1] = 4; board[1][2] = 5;
    board[2][0] = 6; board[2][1] = 7; board[2][2] = 8;
    for(int i = 3; i < 8; ++i) board[0][i] = -1;
    for(int i = 3; i < 8; ++i) board[1][i] = -1;
    for(int i = 3; i < 8; ++i) board[2][i] = -1;
    for(int i = 0; i < 8; ++i) board[3][i] = -1;
    for(int i = 0; i < 8; ++i) board[4][i] = -1;
    for(int i = 0; i < 5; ++i) board[5][i] = -1;
    for(int i = 0; i < 5; ++i) board[6][i] = -1;
    for(int i = 0; i < 5; ++i) board[7][i] = -1;
    board[5][5] = 9; board[5][6] = 10; board[5][7] = 11;
    board[6][5] = 12; board[6][6] = 13; board[6][7] = 14;
    board[7][5] = 15; board[7][6] = 16; board[7][7] = 17;
    return;
}
int check(){
    bool flag = true;
    for(int i = 0; i < 3; ++i) {
        for(int j = 0; j < 3; ++j) {
            if(board[i][j] < 9) {flag = false; break;}
        }
    }
    if(flag) return 1;
    for(int i = 5; i < 8; ++i) {
        for(int j = 5; j < 8; ++j) {
            if(board[i][j] >= 9 || board[i][j] < 0) return 0;
        }
    }
    return 2;
}
int check_win() {
    int empty_cells = 0, blue_cells = 0;
    for(int i = 5; i < 8; ++i) {
        for(int j = 5; j < 8; ++j) {
            if(board[i][j] == -1) ++empty_cells;
            if(board[i][j] <= 8 && board[i][j] >= 0) ++blue_cells;
        }
    }
    return empty_cells*10+blue_cells;
}
void where_good(int a , int b) {
    if(a-1 > -1) {
        if(board[b][a-1] == -1) {
            board[b][a-1] = -20;
            cells[a-1][b].setFillColor(Color(0, 238, 118, 128));
        }
    }
    if(a+1 < 8) {
        if(board[b][a+1] == -1) {
            board[b][a+1] = -20;
            cells[a+1][b].setFillColor(Color(0, 238, 118, 128));
        }
    }
    if(b-1 > -1) {
        if(board[b-1][a] == -1) {
            board[b-1][a] = -20;
            cells[a][b-1].setFillColor(Color(0, 238, 118, 128));
        }
    }
    if(b+1 < 8) {
        if(board[b+1][a] == -1) {
            board[b+1][a] = -20;
            cells[a][b+1].setFillColor(Color(0, 238, 118, 128));
        }
    }
    return;
}
void where_good_more(int a, int b) {
    if(a-2 > -1) {
        if(board[b][a-1] >= 0 && board[b][a-1] <= 17 && board[b][a-2] == -1) {
            board[b][a-2] = -20;
            cells[a-2][b].setFillColor(Color(0,238,118,128));
            where_good_more(a-2, b);
        }
    }
    if(a+2 < 8) {
        if(board[b][a+1] >= 0 && board[b][a+1] <= 17 && board[b][a+2] == -1) {
            board[b][a+2] = -20;
            cells[a+2][b].setFillColor(Color(0,238,118,128));
            where_good_more(a+2, b);
        }
    }
    if(b-2 > -1) {
        if(board[b-1][a] >= 0 && board[b-1][a] <= 17 && board[b-2][a] == -1) {
            board[b-2][a] = -20;
            cells[a][b-2].setFillColor(Color(0,238,118,128));
            where_good_more(a, b-2);
        }
    }
    if(b+2 < 8) {
        if(board[b+1][a] >= 0 && board[b+1][a] <= 17 && board[b+2][a] == -1) {
            board[b+2][a] = -20;
            cells[a][b+2].setFillColor(Color(0,238,118,128));
            where_good_more(a, b+2);
        }
    }
    return;
}
void play_corner(RenderWindow & w){
    Clock clock;
    Image image; image.loadFromFile("21321-300x300-removebg-preview.png");
    Texture texture; texture.loadFromImage(image);
    Sprite sprite(texture); sprite.setPosition(-20, 400);
    Image im; im.loadFromFile("b41535121ad2c3fe88e7662d4fc85285-removebg-preview.png");
    Texture tex; tex.loadFromImage(im);
    Sprite spr(tex); spr.setPosition(780, 200);
    int a, b, count = 0;
    int a_beg = -100500, b_beg = -100500;
    int c1 = 220 , c2 = 120;
    for(int i = 0; i < 8; ++i) {
        int j;
        if(i%2 == 0) j = 0;
        else j = 1;
        for(j; j < 8; j+=2) {
            cells[i][j].setFillColor(Color(232,232,232));
            cells[i][j].setSize(Vector2f(70,70));
            cells[i][j].setPosition(70*i+c1, 70*j+c2);
        }
    }
    for(int i = 0; i < 8; ++i) {
        int j;
        if(i%2 == 0) j = 1;
        else j = 0;
        for(j; j < 8; j+=2) {
            cells[i][j].setFillColor(Color(169,169,169));
            cells[i][j].setSize(Vector2f(70,70));
            cells[i][j].setPosition(70*i+c1, 70*j+c2);
        }
    }
    for(int i = 0; i < 9; ++i) {
        fishki[i].setRadius(30);
        fishki[i].setFillColor(Color(67,110,238));
        fishki[i].setPosition(70*(i%3)+c1+5, 70*(i/3)+c2+5);
    }
    for(int i = 9; i < 18; ++i) {
        fishki[i].setRadius(30);
        fishki[i].setFillColor(Color::Black);
        fishki[i].setPosition(70*(i%3)+c1+355, 70*(i/3-3)+c2+355);
    }
    while(w.isOpen()) {
        Event event;
        Vector2i pos = Mouse::getPosition(w);
        int x = pos.x , y = pos.y;
        if(x >= c1 && x <= 780 && y >= c2 && y <= 680) {
            a = (x-c1)/70;
            b = (y-c2)/70;
        }
        while(w.pollEvent(event)) {
            switch(event.type) {
        case Event::Closed:
            w.close();
        case Event::MouseButtonPressed:
            if(cells[a][b].getGlobalBounds().contains(pos.x, pos.y)) {
                if((board[b][a] >= 0 && board[b][a] <= 17)|| board[b][a] == -20) {
                    if(count%2 == 0) {
                        fishki[board[b][a]].setOutlineThickness(3);
                        fishki[board[b][a]].setOutlineColor(Color(0, 255, 127));
                        a_beg = a; b_beg = b;
                        where_good(a_beg, b_beg);
                        where_good_more(a_beg, b_beg);
                        ++count;
                    }
                    else {
                        if(a == a_beg && b == b_beg) {
                            fishki[board[b][a]].setOutlineColor(Color::Transparent);
                            for(int i = 0; i < 8; ++i) {
                                for(int j = 0; j < 8; ++j) {
                                    if(board[i][j] == -20) board[i][j] = -1;
                                    if(i%2 == j%2) cells[i][j].setFillColor(Color(232,232,232));
                                    else cells[i][j].setFillColor(Color(169,169,169));
                                }
                            }
                            --count;
                        }
                        else {
                            if(board[b][a] == -20){
                                fishki[board[b_beg][a_beg]].setOutlineColor(Color::Transparent);
                                for(int i = 0; i < 8; ++i) {
                                    for(int j = 0; j < 8; ++j) {
                                        if(board[i][j] == -20) board[i][j] = -1;
                                        if(i%2 == j%2) cells[i][j].setFillColor(Color(232,232,232));
                                        else cells[i][j].setFillColor(Color(169,169,169));
                                    }
                                }
                                board[b][a] = board[b_beg][a_beg];
                                fishki[board[b_beg][a_beg]].setPosition(a*70+c1+5, b*70+c2+5);
                                board[b_beg][a_beg] = -1;
                                ++count;
                                int z = check();
                                if(z == 1) {
                                    congr();
                                    massive();
                                    return;
                                }
                                else if (z == 2) {
                                    sorry();
                                    massive();
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        default:
            break;
            }
         }
        w.clear(Color(135, 206, 250));
        for(int i = 0; i < 8; ++i) {
            for(int j = 0; j < 8; ++j) {
                w.draw(cells[i][j]);
            }
        }
        for(int i = 0; i < 18; ++i) w.draw(fishki[i]);
        w.draw(sprite); w.draw(spr);
        w.display();
    }
}
void hard_corner(RenderWindow & w) {
    srand(time(NULL));
    int z = 0;
    Font font;
    font.loadFromFile("Lobster-Regular.ttf");
    Text text;
    text.setString("Enter..."); text.setFont(font);
    text.setCharacterSize(30); text.setPosition(55,200);
    text.setFillColor(Color(0,0,130));

    Image image1;
    image1.loadFromFile("21329-150x150-removebg-preview.png");
    Texture texture1;
    texture1.loadFromImage(image1);
    Sprite sprite1(texture1);
    sprite1.setPosition(20,10);

    Image image2;
    image2.loadFromFile("21333-150x150-removebg-preview.png");
    Texture texture2;
    texture2.loadFromImage(image2);
    Sprite sprite2(texture2);
    sprite2.setPosition(20,10);
    ///ÂÈÂIÄ ÂÑÜÎÃÎ///
    Image image; image.loadFromFile("21321-300x300-removebg-preview.png");
    Texture texture; texture.loadFromImage(image);
    Sprite sprite(texture); sprite.setPosition(-20, 400);
    Image im; im.loadFromFile("b41535121ad2c3fe88e7662d4fc85285-removebg-preview.png");
    Texture tex; tex.loadFromImage(im);
    Sprite spr(tex); spr.setPosition(780, 200);
    int a, b, count = 0, steps = rand()%2, steps_to_lose = 0, windows, blues;
    int a_beg = -100500, b_beg = -100500, k = 0;
    int c1 = 220 , c2 = 120;
    node *dp;
    for(int i = 0; i < 8; ++i) {
        int j;
        if(i%2 == 0) j = 0;
        else j = 1;
        for(j; j < 8; j+=2) {
            cells[i][j].setFillColor(Color(232,232,232)); cells[i][j].setSize(Vector2f(70,70));
            cells[i][j].setPosition(70*i+c1, 70*j+c2);
        }
    }
    for(int i = 0; i < 8; ++i) {
        int j;
        if(i%2 == 0) j = 1;
        else j = 0;
        for(j; j < 8; j+=2) {
            cells[i][j].setFillColor(Color(169,169,169)); cells[i][j].setSize(Vector2f(70,70));
            cells[i][j].setPosition(70*i+c1, 70*j+c2);
        }
    }
    for(int i = 0; i < 9; ++i) {
        fishki[i].setRadius(30); fishki[i].setFillColor(Color(67,110,238));
        fishki[i].setPosition(70*(i%3)+c1+5, 70*(i/3)+c2+5);
    }
    for(int i = 9; i < 18; ++i) {
        fishki[i].setRadius(30); fishki[i].setFillColor(Color::Black);
        fishki[i].setPosition(70*(i%3)+c1+355, 70*(i/3-3)+c2+355);
    }
    ///ÂÈÂIÄ ÂÑÜÎÃÎ///
    while(w.isOpen()) {
        Event event;
        Vector2i pos = Mouse::getPosition(w);
        int x = pos.x , y = pos.y;
        if(x >= c1 && x <= 780 && y >= c2 && y <= 680) {
            a = (x-c1)/70;
            b = (y-c2)/70;
        }
        if(steps%2 == 0 && z != 1) {
            node *List = NULL, *L;
            steps_to_lose = check_win();     ///âîò ýòèì â êîíöå çàíèìàòüñÿ
            windows = steps_to_lose/10;
            blues = steps_to_lose%10;
            for(int i = 0; i < 9; ++i) {
                int ic = (fishki[i].getPosition().y-c2-5)/70;
                int jc = (fishki[i].getPosition().x-c1-5)/70;
                double s = 0;
                for(int j = 0; j < 9; ++j) {
                    int ic1 = (fishki[j].getPosition().y-c2-5)/70;
                    int jc1 = (fishki[j].getPosition().x-c1-5)/70;
                    if(ic == ic1 && jc == jc1) continue;
                    s += sqrt((7-ic1)*(7-ic1)+(7-jc1)*(7-jc1));
                }
                where_good(jc, ic);
                where_good_more(jc, ic);
                for(int m = 0; m < 8; ++m) {
                    for(int n = 0; n < 8; ++n) {
                        if(board[m][n] == -20) {
                            double f = sqrt((7-m)*(7-m)+(7-n)*(7-n));
                            s += f;
                            if(List == NULL) {
                                ins_head(List, s, ic, jc, n, m);
                                L = List;
                            }
                            else {
                                ins_after(List, s, ic, jc, n, m);
                                List = List->next;
                            }
                            s -= f;
                            board[m][n] = -1;
                        }
                        if(m%2 == n%2) cells[m][n].setFillColor(Color(232,232,232));
                        else cells[m][n].setFillColor(Color(169,169,169));
                    }
                }
            }
            List = L;
            ///ñìîòðèì õîäû ñîïåðíèêà òî åñòü íàøè///
            while(List != NULL) {
                board[List->kinec_y][List->kinec_x] = board[List->pochatok_x][List->pochatok_y];
                board[List->pochatok_x][List->pochatok_y] = -1;
                node *enemy_List = NULL, *enemy_L;
                for(int i = 9; i < 18; ++i) {
                    int ic = (fishki[i].getPosition().y-c2-5)/70;
                    int jc = (fishki[i].getPosition().x-c1-5)/70;
                    double s = 0;
                    for(int j = 0; j < 9; ++j) {
                        int ic1 = (fishki[j].getPosition().y-c2-5)/70;
                        int jc1 = (fishki[j].getPosition().x-c1-5)/70;
                        if(ic == ic1 && jc == jc1) continue;
                        s += sqrt((0-ic1)*(0-ic1)+(0-jc1)*(0-jc1));
                    }
                    where_good(jc, ic);
                    where_good_more(jc, ic);
                    for(int m = 0; m < 8; ++m) {
                        for(int n = 0; n < 8; ++n) {
                            if(board[m][n] == -20) {
                                double f = sqrt((0-m)*(0-m)+(0-n)*(0-n));
                                s += f;
                                if(enemy_List == NULL) {
                                    ins_head(enemy_List, s, ic, jc, n, m);
                                    enemy_L = enemy_List;
                                }
                                else {
                                    ins_after(enemy_List, s, ic, jc, n, m);
                                    enemy_List = enemy_List->next;
                                }
                                s -= f;
                                board[m][n] = -1;
                            }
                            if(m%2 == n%2) cells[m][n].setFillColor(Color(232,232,232));
                            else cells[m][n].setFillColor(Color(169,169,169));
                        }
                    }
                }
                ///ÏÎÑÒÐÎÅÍ ÑÏÈÑÎÊ ÂÎÇÌÎÆÍÛÕ ÕÎÄÎÂ ÑÎÏÅÐÍÈÊÀ ÍÀ ÊÎÍÊÐÅÒÍÛÉ ÕÎÄ ÁÎÒÀ

                List->to_enemy = enemy_L;
                int minimum = 100500;
                for(node *p = enemy_L; p != NULL; p = p->next) {
                    if(p->func < minimum) minimum = p->func;
                }
                ///ÍÀØËÈ ÍÀÈÁÎËÅÅ ÂÛÃÎÄÍÛÉ ÕÎÄ ÄËß ÑÎÏÅÐÍÈÊÀ
                List->func -= minimum;
                board[List->pochatok_x][List->pochatok_y] = board[List->kinec_y][List->kinec_x];
                board[List->kinec_y][List->kinec_x] = -1;

                List = List->next;
            }
            List = L;
            if(windows == 1 && blues == 8) {
                for(node *p = L; p != NULL; p = p->next) {
                    if(p->kinec_x == 4 && p->kinec_y == 7) p->func = 10000000;
                    if(p->kinec_x == 7 && p->kinec_y == 4) p->func = 10000000;
                }
            }
            else if(windows == 2 && blues == 7) {
                if(board[4][6] <= 8 && board[4][6] >= 0 && board[4][7] <=8  && board[4][7] >= 0) {
                    for(node *p = L; p != NULL; p = p->next) {
                        if(p->pochatok_x == 4 && p->pochatok_y == 6 || p->pochatok_x == 4 && p->pochatok_y == 7) continue;
                        p->func = 10000000;
                    }
                }
                else if(board[6][4] <= 8 && board[6][4] >= 0 && board[7][4] <=8  && board[7][4] >= 0) {
                    for(node *p = L; p != NULL; p = p->next) {
                        if(p->pochatok_x == 6 && p->pochatok_y == 4 || p->pochatok_x == 7 && p->pochatok_y == 4) continue;
                        p->func = 10000000;
                    }
                }
                else if(board[4][7] <= 8 && board[4][7] >= 0 && board[7][4] <= 8 && board[7][4] >= 0) {
                    for(node *p = L; p != NULL; p = p->next) {
                        if(p->pochatok_x == 4 && p->pochatok_y == 7 || p->pochatok_x == 7 && p->pochatok_y == 4) continue;
                        p->func = 10000000;
                    }
                }
            }
            else if(windows == 3 && blues == 6) {
                if(board[4][6] <= 8 && board[4][6] >= 0 && board[4][7] <=8  && board[4][7] >= 0 && board[3][6] <= 8 && board[3][6] >= 0) {
                    for(node *p = L; p != NULL; p = p->next) {
                        if(p->kinec_x == 7 && p->kinec_y == 4) p->func = 10000000;
                    }
                }
                if(board[6][4] <= 8 && board[6][4] >= 0 && board[7][4] <=8  && board[7][4] >= 0 && board[6][3] <= 8 && board[6][3] >= 0) {
                    for(node *p = L; p != NULL; p = p->next) {
                        if(p->kinec_x == 4 && p->kinec_y == 7) p->func = 10000000;
                    }
                }
            }
            else if(windows == 1 && blues == 8) {
                if(board[0][0] <= 8 && board[0][0] >= 0) {
                    for(node* p = L; p != NULL; p = p->next) {
                        if(p->pochatok_x == 0 && (p->pochatok_y == 0 || p->pochatok_y == 1)) p->func = 0;
                        else p->func = 10000000;
                    }
                }
            }
            if(check_stupor()) {
                for(node* p = L; p != NULL; p = p->next) {
                    if(p->pochatok_x == 0 && (p->pochatok_y == 0 || p->pochatok_y == 1)) p->func = 0;
                    else p->func = 10000000;
                }
            }
            for(node *p = L; p != NULL; p = p->next) {
                if(p->pochatok_x == 0 && p->pochatok_y == 1 && p->kinec_x == 0 && p->kinec_y == 0) p->func = 10000000;
            }
            node *min;
            double minim = 100500;
            for(node *p = L; p != NULL; p = p->next) {
                if(p->func < minim) {
                    min = p;
                    minim = p->func;
                }
            }
            fishki[board[min->pochatok_x][min->pochatok_y]].setPosition(min->kinec_x*70+c1+5, min->kinec_y*70+c2+5);
            board[min->kinec_y][min->kinec_x] = board[min->pochatok_x][min->pochatok_y];
            board[min->pochatok_x][min->pochatok_y] = -1;
            ++steps;
        }
        while(w.pollEvent(event)) {
            switch(event.type) {
        case Event::Closed:
            w.close();
        case Event::MouseButtonPressed:
            if(steps%2 != 0) {
                if(cells[a][b].getGlobalBounds().contains(pos.x, pos.y)) {
                    if((board[b][a] >= 9 && board[b][a] <= 17)|| board[b][a] == -20) {
                        if(count%2 == 0) {
                            fishki[board[b][a]].setOutlineThickness(3);
                            fishki[board[b][a]].setOutlineColor(Color(0, 255, 127));
                            a_beg = a; b_beg = b;
                            where_good(a_beg, b_beg); where_good_more(a_beg, b_beg);
                            ++count;
                        }
                        else {
                            if(a == a_beg && b == b_beg) {
                                fishki[board[b][a]].setOutlineColor(Color::Transparent);
                                for(int i = 0; i < 8; ++i) {
                                    for(int j = 0; j < 8; ++j) {
                                        if(board[i][j] == -20) board[i][j] = -1;
                                        if(i%2 == j%2) cells[i][j].setFillColor(Color(232,232,232));
                                        else cells[i][j].setFillColor(Color(169,169,169));
                                    }
                                }
                                --count;
                            }
                            else {
                                if(board[b][a] == -20){
                                    fishki[board[b_beg][a_beg]].setOutlineColor(Color::Transparent);
                                    for(int i = 0; i < 8; ++i) {
                                        for(int j = 0; j < 8; ++j) {
                                            if(board[i][j] == -20) board[i][j] = -1;
                                            if(i%2 == j%2) cells[i][j].setFillColor(Color(232,232,232));
                                            else cells[i][j].setFillColor(Color(169,169,169));
                                        }
                                    }
                                    board[b][a] = board[b_beg][a_beg];
                                    fishki[board[b_beg][a_beg]].setPosition(a*70+c1+5, b*70+c2+5);
                                    board[b_beg][a_beg] = -1;
                                    ++count;
                                    ++steps;
                                }
                            }
                        }
                    }
                }
            }
        case Event::KeyPressed:
            if(z != 0) {
                if(event.key.code == Keyboard::Enter) {
                    massive();
                    return;
                }
            }
        default:
            break;
            }
         }
        w.clear(Color(135, 206, 250));
        for(int i = 0; i < 8; ++i) {
            for(int j = 0; j < 8; ++j) {
                w.draw(cells[i][j]);
            }
        }
        z = check();
        if(z == 1 || z == 2) {
            w.draw(text);
            if(z == 1) w.draw(sprite1);
            else w.draw(sprite2);
        }
        for(int i = 0; i < 18; ++i) w.draw(fishki[i]);
        w.draw(sprite); w.draw(spr);
        w.display();
    }
}
void middle_corner(RenderWindow & w) {
    srand(time(NULL));
    int z = 0;
    Font font;
    font.loadFromFile("Lobster-Regular.ttf");
    Text text;
    text.setString("Enter..."); text.setFont(font);
    text.setCharacterSize(30); text.setPosition(55,200);
    text.setFillColor(Color(0,0,130));

    Image image1;
    image1.loadFromFile("21329-150x150-removebg-preview.png");
    Texture texture1;
    texture1.loadFromImage(image1);
    Sprite sprite1(texture1);
    sprite1.setPosition(20,10);

    Image image2;
    image2.loadFromFile("21333-150x150-removebg-preview.png");
    Texture texture2;
    texture2.loadFromImage(image2);
    Sprite sprite2(texture2);
    sprite2.setPosition(20,10);

    ///ÂÈÂIÄ ÂÑÜÎÃÎ///
    Image image; image.loadFromFile("21321-300x300-removebg-preview.png");
    Texture texture; texture.loadFromImage(image);
    Sprite sprite(texture); sprite.setPosition(-20, 400);
    Image im; im.loadFromFile("b41535121ad2c3fe88e7662d4fc85285-removebg-preview.png");
    Texture tex; tex.loadFromImage(im);
    Sprite spr(tex); spr.setPosition(780, 200);
    int a, b, count = 0, steps = rand()%2, steps_to_lose = 0, windows, blues;
    int a_beg = -100500, b_beg = -100500, k = 0;
    int c1 = 220 , c2 = 120;
    node *dp;
    for(int i = 0; i < 8; ++i) {
        int j;
        if(i%2 == 0) j = 0;
        else j = 1;
        for(j; j < 8; j+=2) {
            cells[i][j].setFillColor(Color(232,232,232)); cells[i][j].setSize(Vector2f(70,70));
            cells[i][j].setPosition(70*i+c1, 70*j+c2);
        }
    }
    for(int i = 0; i < 8; ++i) {
        int j;
        if(i%2 == 0) j = 1;
        else j = 0;
        for(j; j < 8; j+=2) {
            cells[i][j].setFillColor(Color(169,169,169)); cells[i][j].setSize(Vector2f(70,70));
            cells[i][j].setPosition(70*i+c1, 70*j+c2);
        }
    }
    for(int i = 0; i < 9; ++i) {
        fishki[i].setRadius(30); fishki[i].setFillColor(Color(67,110,238));
        fishki[i].setPosition(70*(i%3)+c1+5, 70*(i/3)+c2+5);
    }
    for(int i = 9; i < 18; ++i) {
        fishki[i].setRadius(30); fishki[i].setFillColor(Color::Black);
        fishki[i].setPosition(70*(i%3)+c1+355, 70*(i/3-3)+c2+355);
    }
    ///ÂÈÂIÄ ÂÑÜÎÃÎ///

    while(w.isOpen()) {
        Event event;
        Vector2i pos = Mouse::getPosition(w);
        int x = pos.x , y = pos.y;
        if(x >= c1 && x <= 780 && y >= c2 && y <= 680) {
            a = (x-c1)/70;
            b = (y-c2)/70;
        }
        if(steps%2 == 0 && z != 1) {
            node *List = NULL, *L;
            steps_to_lose = check_win();
            windows = steps_to_lose/10;
            blues = steps_to_lose%10;
            for(int i = 0; i < 9; ++i) {
                int ic = (fishki[i].getPosition().y-c2-5)/70;
                int jc = (fishki[i].getPosition().x-c1-5)/70;
                double s = 0;
                for(int j = 0; j < 9; ++j) {
                    int ic1 = (fishki[j].getPosition().y-c2-5)/70;
                    int jc1 = (fishki[j].getPosition().x-c1-5)/70;
                    if(ic == ic1 && jc == jc1) continue;
                    s += sqrt((8-ic1)*(8-ic1)+(8-jc1)*(8-jc1));
                }
                where_good(jc, ic);
                where_good_more(jc, ic);
                for(int m = 0; m < 8; ++m) {
                    for(int n = 0; n < 8; ++n) {
                        if(board[m][n] == -20) {
                            double f = sqrt((8-m)*(8-m)+(8-n)*(8-n));
                            s += f;
                            if(List == NULL) {
                                ins_head(List, s, ic, jc, n, m);
                                L = List;
                            }
                            else {
                                ins_after(List, s, ic, jc, n, m);
                                List = List->next;
                            }
                            s -= f;
                            board[m][n] = -1;
                        }
                        if(m%2 == n%2) cells[m][n].setFillColor(Color(232,232,232));
                        else cells[m][n].setFillColor(Color(169,169,169));
                    }
                }
            }
            if(windows == 1 && blues == 8) {
                for(node *p = L; p != NULL; p = p->next) {
                    if(p->kinec_x == 4 && p->kinec_y == 7) p->func = 10000000;
                    if(p->kinec_x == 7 && p->kinec_y == 4) p->func = 10000000;
                }
            }
            else if(windows == 2 && blues == 7) {
                if(board[4][6] <= 8 && board[4][6] >= 0 && board[4][7] <=8  && board[4][7] >= 0) {
                    for(node *p = L; p != NULL; p = p->next) {
                        if(p->pochatok_x == 4 && p->pochatok_y == 6 || p->pochatok_x == 4 && p->pochatok_y == 7) continue;
                        p->func = 10000000;
                    }
                }
                else if(board[6][4] <= 8 && board[6][4] >= 0 && board[7][4] <=8  && board[7][4] >= 0) {
                    for(node *p = L; p != NULL; p = p->next) {
                        if(p->pochatok_x == 6 && p->pochatok_y == 4 || p->pochatok_x == 7 && p->pochatok_y == 4) continue;
                        p->func = 10000000;
                    }
                }
                else if(board[4][7] <= 8 && board[4][7] >= 0 && board[7][4] <= 8 && board[7][4] >= 0) {
                    for(node *p = L; p != NULL; p = p->next) {
                        if(p->pochatok_x == 4 && p->pochatok_y == 7 || p->pochatok_x == 7 && p->pochatok_y == 4) continue;
                        p->func = 10000000;
                    }
                }
            }
            else if(windows == 3 && blues == 6) {
                if(board[4][6] <= 8 && board[4][6] >= 0 && board[4][7] <=8  && board[4][7] >= 0 && board[3][6] <= 8 && board[3][6] >= 0) {
                    for(node *p = L; p != NULL; p = p->next) {
                        if(p->kinec_x == 7 && p->kinec_y == 4) p->func = 10000000;
                    }
                }
                if(board[6][4] <= 8 && board[6][4] >= 0 && board[7][4] <=8  && board[7][4] >= 0 && board[6][3] <= 8 && board[6][3] >= 0) {
                    for(node *p = L; p != NULL; p = p->next) {
                        if(p->kinec_x == 4 && p->kinec_y == 7) p->func = 10000000;
                    }
                }
            }
            else if(windows == 1 && blues == 8) {
                if(board[0][0] <= 8 && board[0][0] >= 0) {
                    for(node* p = L; p != NULL; p = p->next) {
                        if(p->pochatok_x == 0 && (p->pochatok_y == 0 || p->pochatok_y == 1)) p->func = 0;
                        else p->func = 10000000;
                    }
                }
            }
            if(check_stupor()) {
                for(node* p = L; p != NULL; p = p->next) {
                    if(p->pochatok_x == 0 && (p->pochatok_y == 0 || p->pochatok_y == 1)) p->func = 0;
                    else p->func = 10000000;
                }
            }
            for(node *p = L; p != NULL; p = p->next) {
                if(p->pochatok_x == 0 && p->pochatok_y == 1 && p->kinec_x == 0 && p->kinec_y == 0) p->func = 10000000;
            }
            node *min;
            double minim = 100500;
            for(node *p = L; p != NULL; p = p->next) {
                if(p->func < minim) {
                    min = p;
                    minim = p->func;
                }
            }
            fishki[board[min->pochatok_x][min->pochatok_y]].setPosition(min->kinec_x*70+c1+5, min->kinec_y*70+c2+5);
            board[min->kinec_y][min->kinec_x] = board[min->pochatok_x][min->pochatok_y];
            board[min->pochatok_x][min->pochatok_y] = -1;
            ++steps;
        }
        while(w.pollEvent(event)) {
            switch(event.type) {
        case Event::Closed:
            w.close();
        case Event::MouseButtonPressed:
            if(steps%2 != 0) {
                if(cells[a][b].getGlobalBounds().contains(pos.x, pos.y)) {
                    if((board[b][a] >= 9 && board[b][a] <= 17)|| board[b][a] == -20) {
                        if(count%2 == 0) {
                            fishki[board[b][a]].setOutlineThickness(3);
                            fishki[board[b][a]].setOutlineColor(Color(0, 255, 127));
                            a_beg = a; b_beg = b;
                            where_good(a_beg, b_beg); where_good_more(a_beg, b_beg);
                            ++count;
                        }
                        else {
                            if(a == a_beg && b == b_beg) {
                                fishki[board[b][a]].setOutlineColor(Color::Transparent);
                                for(int i = 0; i < 8; ++i) {
                                    for(int j = 0; j < 8; ++j) {
                                        if(board[i][j] == -20) board[i][j] = -1;
                                        if(i%2 == j%2) cells[i][j].setFillColor(Color(232,232,232));
                                        else cells[i][j].setFillColor(Color(169,169,169));
                                    }
                                }
                                --count;
                            }
                            else {
                                if(board[b][a] == -20){
                                    fishki[board[b_beg][a_beg]].setOutlineColor(Color::Transparent);
                                    for(int i = 0; i < 8; ++i) {
                                        for(int j = 0; j < 8; ++j) {
                                            if(board[i][j] == -20) board[i][j] = -1;
                                            if(i%2 == j%2) cells[i][j].setFillColor(Color(232,232,232));
                                            else cells[i][j].setFillColor(Color(169,169,169));
                                        }
                                    }
                                    board[b][a] = board[b_beg][a_beg];
                                    fishki[board[b_beg][a_beg]].setPosition(a*70+c1+5, b*70+c2+5);
                                    board[b_beg][a_beg] = -1;
                                    ++count;
                                    ++steps;
                                }
                            }
                        }
                    }
                }
            }
        case Event::KeyPressed:
            if(z != 0) {
                if(event.key.code == Keyboard::Enter) {
                    massive();
                    return;
                }
            }
        default:
            break;
            }
         }
        w.clear(Color(135, 206, 250));
        for(int i = 0; i < 8; ++i) {
            for(int j = 0; j < 8; ++j) {
                w.draw(cells[i][j]);
            }
        }
        z = check();
        if(z == 1 || z == 2) {
            w.draw(text);
            if(z == 1) w.draw(sprite1);
            else w.draw(sprite2);
        }
        for(int i = 0; i < 18; ++i) w.draw(fishki[i]);
        w.draw(sprite); w.draw(spr);
        if(z != 0) w.draw(text);
        w.display();
    }
}
void easy_corner(RenderWindow & w) {
    int z = 0;
    Font font;
    font.loadFromFile("Lobster-Regular.ttf");
    Text text;
    text.setString("Enter..."); text.setFont(font);
    text.setCharacterSize(30); text.setPosition(55,200);
    text.setFillColor(Color(0,0,130));
    Image image1;
    image1.loadFromFile("21329-150x150-removebg-preview.png");
    Texture texture1;
    texture1.loadFromImage(image1);
    Sprite sprite1(texture1);
    sprite1.setPosition(20,10);

    srand(time(NULL));
    Image image; image.loadFromFile("21321-300x300-removebg-preview.png");
    Texture texture; texture.loadFromImage(image);
    Sprite sprite(texture); sprite.setPosition(-20, 400);
    Image im; im.loadFromFile("b41535121ad2c3fe88e7662d4fc85285-removebg-preview.png");
    Texture tex; tex.loadFromImage(im);
    Sprite spr(tex); spr.setPosition(780, 200);
    int a = 0, b = 0, count = 0, steps = rand()%2;
    int a_beg = 0, b_beg = 0, begin_x = -1, begin_y = -1, end_x = -1, end_y = -1;
    int c1 = 220 , c2 = 120;
    for(int i = 0; i < 8; ++i) {
        int j;
        if(i%2 == 0) j = 0;
        else j = 1;
        for(j; j < 8; j+=2) {
            cells[i][j].setFillColor(Color(232,232,232)); cells[i][j].setSize(Vector2f(70,70));
            cells[i][j].setPosition(70*i+c1, 70*j+c2);
        }
    }
    for(int i = 0; i < 8; ++i) {
        int j;
        if(i%2 == 0) j = 1;
        else j = 0;
        for(j; j < 8; j+=2) {
            cells[i][j].setFillColor(Color(169,169,169)); cells[i][j].setSize(Vector2f(70,70));
            cells[i][j].setPosition(70*i+c1, 70*j+c2);
        }
    }
    for(int i = 0; i < 9; ++i) {
        fishki[i].setRadius(30); fishki[i].setFillColor(Color(67,110,238));
        fishki[i].setPosition(70*(i%3)+c1+5, 70*(i/3)+c2+5);
    }
    for(int i = 9; i < 18; ++i) {
        fishki[i].setRadius(30); fishki[i].setFillColor(Color::Black);
        fishki[i].setPosition(70*(i%3)+c1+355, 70*(i/3-3)+c2+355);
    }
    while(w.isOpen()) {
        Event event;
        Vector2i pos = Mouse::getPosition(w);
        int x = pos.x , y = pos.y;
        if(x >= c1 && x <= 780 && y >= c2 && y <= 680) {
            a = (x-c1)/70;
            b = (y-c2)/70;
        }
        if(steps%2 == 0 && z != 1) {
            try_again:
            int number_of_fishka = rand()%9+1;
            for(int i = 0; i < 64; ++i) {
                if(board[i/8][i%8] >= 0 && board[i/8][i%8] <= 8) --number_of_fishka;
                if(number_of_fishka == 0) {
                    b_beg = i/8; a_beg = i%8; break;
                }
            }
            where_good(a_beg, b_beg); where_good_more(a_beg, b_beg);
            int hody = 0;
            for(int i = 0; i < 64; ++i) {
                if(board[i/8][i%8] == -20) ++hody;
            }
            if(hody == 0) goto try_again;
            int mozhlivi_misca = rand()%hody+1;
            for(int i = 0; i < 64; ++i) {
                if(board[i/8][i%8] == -20) --mozhlivi_misca;
                if(mozhlivi_misca == 0) {
                    board[i/8][i%8] = board[b_beg][a_beg];
                    end_y = i/8; end_x = i%8; begin_y = b_beg; begin_x = a_beg;
                    fishki[board[b_beg][a_beg]].setPosition((i%8)*70+c1+5, (i/8)*70+c2+5);
                    board[b_beg][a_beg] = -1;

                    for(int k = 0; k < 8; ++k) {
                        for(int m = 0; m < 8; ++m) {
                            if(board[k][m] == -20) board[k][m] = -1;
                            if(k%2 == m%2) cells[k][m].setFillColor(Color(232,232,232));
                            else cells[k][m].setFillColor(Color(169,169,169));
                        }
                    }
                    break;
                }
            }
            ++steps;
        }
        while(w.pollEvent(event)) {
            switch(event.type) {
        case Event::Closed:
            w.close();
        case Event::MouseButtonPressed:
            if(steps%2 != 0) {
                if(cells[a][b].getGlobalBounds().contains(pos.x, pos.y)) {
                    if((board[b][a] >= 9 && board[b][a] <= 17)|| board[b][a] == -20) {
                        if(count%2 == 0) {
                            fishki[board[b][a]].setOutlineThickness(3);
                            fishki[board[b][a]].setOutlineColor(Color(0, 255, 127));
                            a_beg = a; b_beg = b;
                            where_good(a_beg, b_beg); where_good_more(a_beg, b_beg);
                            ++count;
                        }
                        else {
                            if(a == a_beg && b == b_beg) {
                                fishki[board[b][a]].setOutlineColor(Color::Transparent);
                                for(int i = 0; i < 8; ++i) {
                                    for(int j = 0; j < 8; ++j) {
                                        if(board[i][j] == -20) board[i][j] = -1;
                                        if(i%2 == j%2) cells[i][j].setFillColor(Color(232,232,232));
                                        else cells[i][j].setFillColor(Color(169,169,169));
                                    }
                                }
                                --count;
                            }
                            else {
                                if(board[b][a] == -20){
                                    fishki[board[b_beg][a_beg]].setOutlineColor(Color::Transparent);
                                    for(int i = 0; i < 8; ++i) {
                                        for(int j = 0; j < 8; ++j) {
                                            if(board[i][j] == -20) board[i][j] = -1;
                                            if(i%2 == j%2) cells[i][j].setFillColor(Color(232,232,232));
                                            else cells[i][j].setFillColor(Color(169,169,169));
                                        }
                                    }
                                    board[b][a] = board[b_beg][a_beg];
                                    end_y = b; end_x = a; begin_y = b_beg; begin_x = a_beg;
                                    fishki[board[b_beg][a_beg]].setPosition(a*70+c1+5, b*70+c2+5);
                                    board[b_beg][a_beg] = -1;
                                    ++count;
                                    ++steps;
                                }
                            }
                        }
                    }
                }
            }
        case Event::KeyPressed:
            if(z == 1 || z == 2) {
                if(event.key.code == Keyboard::Enter) {
                    massive();

                    return;
                }
            }
        default:
            break;
            }
         }
        w.clear(Color(135, 206, 250));
        for(int i = 0; i < 8; ++i) {
            for(int j = 0; j < 8; ++j) w.draw(cells[i][j]);
        }
        for(int i = 0; i < 18; ++i) w.draw(fishki[i]);
        z = check();
        if(z == 1 || z == 2) {
            w.draw(text);
            w.draw(sprite1);
        }

        w.draw(sprite); w.draw(spr);
        w.display();
    }
}
void menu(RenderWindow & w) {
    Font font;
    font.loadFromFile("Lobster-Regular.ttf");
    bool isMenu = true;
	int menuNum = 0;
	Image fon; fon.loadFromFile("fon.jpg");
	Texture textureOfFon; textureOfFon.loadFromImage(fon);
	Sprite ffon(textureOfFon); ffon.setPosition(0,0);

    Text text; text.setString("Óãîëêè"); text.setFont(font);
    text.setCharacterSize(90);
    text.setStyle(Text::Bold); text.setFillColor(Color(58,95,205));
    text.setPosition(20,20); text.setStyle(Text::Underlined);

    Text text1, text2, text3, text4, text5;
    text1.setString("Âûáåðèòå óðîâåíü ñëîæíîñòè:");
    text1.setFont(font); text1.setCharacterSize(50);
    text1.setStyle(Text::Bold); text1.setFillColor(Color(67,110,238));
    text1.setPosition(180,200);

    text2.setString("Ë¸ãêèé (Áûêîâ)");
    text2.setFont(font); text2.setCharacterSize(40);
    text2.setFillColor(Color(67,110,238));
    text2.setPosition(180,300);

    text3.setString("Ñðåäíèé (Ãîëóáêîâ)");
    text3.setFont(font); text3.setCharacterSize(40);
    text3.setFillColor(Color(67,110,238));
    text3.setPosition(180,400);

    text4.setString("Òÿæ¸ëûé (Ðîùèíà)");
    text4.setFont(font);
    text4.setCharacterSize(40);
    text4.setFillColor(Color(67,110,238));
    text4.setPosition(180,500);

    text5.setString("Ðåæèì íà äâîèõ");
    text5.setFont(font);
    text5.setCharacterSize(40);
    text5.setFillColor(Color(67,110,238));
    text5.setPosition(180,630);

    Image aid; aid.loadFromFile("21317-300x300.png");
    Texture of_aid; of_aid.loadFromImage(aid);
    Sprite of_of_aid(of_aid); of_of_aid.setPosition(600,300);
	while(isMenu) {
        sf::Event event;
        while(w.pollEvent(event)) {
            switch(event.type) {
            case sf::Event::Closed:
                w.close();
                break;
            default:
                break;
            }
        }
        text2.setFillColor(Color(67,110,238));
        text3.setFillColor(Color(67,110,238));
        text4.setFillColor(Color(67,110,238));
        text5.setFillColor(Color(67,110,238));
        menuNum = 0;
        w.clear();

        if(IntRect(180 , 300 , 280 , 40).contains(Mouse::getPosition(w))) {text2.setFillColor(Color(0,0,205)); menuNum = 1;}
        if(IntRect(180 , 400 , 330 , 40).contains(Mouse::getPosition(w))) {text3.setFillColor(Color(0,0,205)); menuNum = 2;}
        if(IntRect(180 , 500 , 340 , 40).contains(Mouse::getPosition(w))) {text4.setFillColor(Color(0,0,205)); menuNum = 3;}
        if(IntRect(180 , 630 , 295 , 40).contains(Mouse::getPosition(w))) {text5.setFillColor(Color(0,0,205)); menuNum = 4;}
        if (Mouse::isButtonPressed(Mouse::Left)) {
			if (menuNum == 1) {easy_corner(w);}
			if (menuNum == 2) {middle_corner(w);}
			if (menuNum == 3) {hard_corner(w);}
			if (menuNum == 4) {play_corner(w);}
		}
		w.draw(ffon);
        w.draw(text); w.draw(text1); w.draw(text2); w.draw(text3); w.draw(text4); w.draw(text5);
        w.draw(of_of_aid);
        w.display();
    }
    return;
}

int main() {
    setlocale(LC_ALL , "rus");
    RenderWindow w(sf::VideoMode(1000 , 800) , "Play");
	menu(w);
    return 0;
}
