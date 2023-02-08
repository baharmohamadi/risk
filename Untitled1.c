#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <stdbool.h>
#include <stdio.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <time.h>
#include <allegro5/allegro_image.h>
#include <windows.h>
struct player{
    int sol;                           //count of soldiers
    int count;                         //count of countries
    int id;
};

bool is_continent(int player, int number_of_continent,int map[7][6], int count[7][6], int count_of_countries[4]){
    int i,j,k = 0;
    for(i=0; i<7; i++){
        for(j=0; j<6; j++){
            if(map[i][j] == number_of_continent && count[i][j] == player){
                k++;
            }
        }
    }
    if(k == count_of_countries[number_of_continent - 1]){
        return true;
    }
    return false;
}

int count_of_continent(int player,int map[7][6], int count[7][6], int count_of_countries[4]){
    int i, k = 0;
    for(i=1; i<5; i++){
        if(is_continent(player,i,map,count,count_of_countries)){
            k++;
        }
    }
    return k;
}

bool is_around(int i1, int j1, int i2, int j2){
    if (j1 == j2) {
        if (i1 - i2 == 1) {
            return true;
        } else if (i2 - i1 == 1) {
            return true;
        }
    }else if (i1 == i2){
        if (j1 - j2 == 1){
            return true;
        } else if (j2 - j1 == 1){
            return true;
        }
    }else {
        return false;
    }
}

void up_to_down( int a[], int size ){
    int i,j,c;
    for( i = 0; i < size; ++i ){
        for( j = i + 1; j < size; ++j ){
           if( a[j] > a[i] ){
             c= a[i];
             a[i] = a[j];
             a[j] = c;
           }
        }
    }
}

int find_i (int pos_x, int pos_y, int posx[7][6], int posy[7][6]){
    int i, j;
    for(i = 0; i < 7; i++){
        for(j = 0; j < 6; j++){
            if((pos_y - posy[i][j])*(pos_y - posy[i][j]) + (pos_x - posx[i][j])*(pos_x - posx[i][j]) <= 100){
                return i;
            }
        }
    }
}


int find_j (int pos_x, int pos_y, int posx[7][6], int posy[7][6]){
    int i, j;
    for(i = 0; i < 7; i++){
        for(j = 0; j < 6; j++){
            if((pos_y - posy[i][j])*(pos_y - posy[i][j]) + (pos_x - posx[i][j])*(pos_x - posx[i][j]) <= 100){
                return j;
            }
        }
    }
}

bool is_there_any_way(int i1,int j1,int i2,int j2,int count[7][6],int player_number){
    int a[30][30],b[1000],c[1000],d[1000],e[1000],i,j,t=-1,k,m=0;
    for(i=0; i<7; i++){
        for(j=0; j<6; j++){
            a[i][j] = count[i][j];
        }
    }
    i=j1;
    j=i1;
    while(i!=i2 || j!=j2){
        if(a[i+1][j]==player_number && i<7){
            a[i+1][j]--;
            b[t]=i;
            c[t]=j;
            i++;
            d[t]=i;
            e[t]=j;
            t++;
        }else if(a[i][j+1]==player_number && j<6){
            a[i][j+1]--;
            b[t]=i;
            c[t]=j;
            j++;
            d[t]=i;
            e[t]=j;
            t++;
        }else if(a[i-1][j]==player_number && i>-1){
            a[i-1][j]--;
            b[t]=i;
            c[t]=j;
            i--;
            d[t]=i;
            e[t]=j;
            t++;
        }else if(a[i][j-1]==player_number && j>-1){
            a[i][j-1]--;
            b[t]=i;
            c[t]=j;
            j--;
            d[t]=i;
            e[t]=j;
            t++;
        }else if(a[b[t-1]][c[t-1]]==-1){
            a[d[t-1]][e[t-1]]--;
            i=b[t-1];
            j=c[t-1];
            t--;
        }else if(a[b[t-1]][c[t-1]]==-2){
            a[d[t-1]][e[t-1]]--;
            i=b[t-1];
            j=c[t-1];
            t--;
        }else if(a[b[t-1]][c[t-1]]==-3){
            a[d[t-1]][e[t-1]]--;
            i=b[t-1];
            j=c[t-1];
            t--;
        }else{
            return false;
        }
    }
    return true;
}

    int main() {
        srand(time(0));
        struct player player1, player2, player3, player4;
        int width = 801;
        int height = 450;
        int pos_x, pos_y, k, m;
        int sol[7][6], count[7][6], map[7][6], i, j, i1, i2, j1, j2;
        int imagewidth = 0 , imageheight = 0;
        bool done = false;
        int count_of_countries[4] = {9, 6, 8, 6};
        player1.id = 1;
        player2.id = 2;
        player3.id = 3;
        player4.id = 4;
        player1.count = 0;
        player2.count = 0;
        player3.count = 0;
        player4.count = 0;
        int n = 0, number;
        time_t time1;
        for (i = 0; i < 7; i++) {
            for (j = 0; j < 6; j++) {
                sol[i][j] = 1;
            }
        }

        //writing map

        map[0][0] = 0;
        map[1][0] = 0;
        map[2][0] = 0;
        map[3][0] = 0;
        map[4][0] = 0;
        map[5][0] = 0;
        map[0][1] = 0;
        map[1][1] = 0;
        map[5][1] = 1;  // 1 means amrika
        map[0][2] = 1;
        map[0][3] = 1;
        map[1][2] = 1;
        map[1][3] = 1;
        map[2][2] = 1;
        map[2][3] = 1;  // 2 means urupa
        map[0][4] = 2;
        map[0][5] = 2;
        map[1][4] = 2;
        map[1][5] = 2;
        map[2][4] = 2;
        map[2][5] = 2;
        map[3][4] = 2;
        map[3][5] = 2;  // 3 means asia
        map[3][3] = 3;
        map[4][3] = 3;
        map[5][3] = 3;
        map[4][4] = 3;
        map[5][4] = 3;
        map[6][4] = 3;  // 4 means africa
        map[6][0] = 4;
        map[6][1] = 4;
        map[6][3] = 4;
        map[6][4] = 4;
        map[6][5] = 4;
        map[5][5] = 4;
        map[5][4] = 4;
        map[4][5] = 4;
        map[4][4] = 4;
        map[2][1] = 4;
        map[3][1] = 4;
        map[4][1] = 4;
        map[3][2] = 4; // 5 means sea

        // finish writing map
        // writing cordinates
        int posy[7][6];

        posy[0][0] = 95;
        posy[0][1] = 197;
        posy[1][0] = 140;
        posy[1][1] = 170;
        posy[2][0] = 233;
        posy[3][0] = 100;
        posy[4][0] = 63;
        posy[5][0] = 145;
        posy[5][1] = 174;
        posy[0][5] = 334;
        posy[1][5] = 384;
        posy[2][5] = 314;
        posy[3][5] = 252;
        posy[0][4] = 292;
        posy[1][4] = 280;
        posy[2][4] = 335;
        posy[3][4] = 258;
        posy[0][2] = 100;
        posy[0][3] = 137;
        posy[1][2] = 137;
        posy[1][3] = 177;
        posy[2][2] = 176;
        posy[2][3] = 200;
        posy[3][3] = 233;
        posy[4][3] = 251;
        posy[5][3] = 274;
        posy[4][2] = 292;
        posy[5][2] = 297;
        posy[6][2] = 269;

        int posx[7][6];
        posx[0][2] = 85;
        posx[0][3] = 147;
        posx[1][2] = 210;
        posx[1][3] = 150;
        posx[2][2] = 92;
        posx[2][3] = 132;
        posx[3][3] = 176;
        posx[4][3] = 125;
        posx[5][3] = 75;
        posx[4][2] = 128;
        posx[5][2] = 188;
        posx[6][2] = 174;
        posx[0][0] = 278;
        posx[0][1] = 300;
        posx[1][0] = 360;
        posx[1][1] = 460;
        posx[2][0] = 450;
        posx[3][0] = 510;
        posx[4][0] = 495;
        posx[5][0] = 278;
        posx[5][1] = 530;
        posx[0][5] = 404;
        posx[1][5] = 420;
        posx[2][5] = 496;
        posx[3][5] = 377;
        posx[0][4] = 404;
        posx[1][4] = 484;
        posx[2][4] = 538;
        posx[3][4] = 520;

        // finish writing cordinates
        ALLEGRO_MOUSE_STATE state;
        ALLEGRO_DISPLAY *display = NULL;
        ALLEGRO_EVENT_QUEUE *event_queue = NULL;
        if (!al_init()) {
            return -1;
        }

        display = al_create_display(width, height);
        event_queue = al_create_event_queue();

        if (!display) {
            return -1;
        }

        al_init_primitives_addon();
        al_install_mouse();
        al_init_font_addon();
        al_init_ttf_addon();
        al_init_image_addon();
        ALLEGRO_TIMER  *timer = al_create_timer(1.0 / 60);
        ALLEGRO_FONT *font24 = al_load_font("font.ttf", 24, 0);
        ALLEGRO_FONT *font18 = al_load_font("fontt.ttf", 18, 0);
        ALLEGRO_BITMAP* start = NULL;
        ALLEGRO_BITMAP* board = NULL;
        start = al_load_bitmap("risk.jpg");
        board = al_load_bitmap("map.png");
        event_queue = al_create_event_queue();
        al_register_event_source(event_queue, al_get_display_event_source(display));
        al_register_event_source(event_queue, al_get_mouse_event_source());
        al_register_event_source(event_queue, al_get_timer_event_source(timer));
//        al_start_timer(timer);


        while (!done) {
            al_draw_bitmap(start,0,0,0);
            al_draw_text(font24, al_map_rgb(255, 255, 255), 540, 300, 0, "New game");
            al_draw_text(font24, al_map_rgb(255, 255, 255), 540, 340, 0, "Option");
            al_draw_text(font24, al_map_rgb(255, 255, 255), 540, 380, 0, "Info");
            al_flip_display();
            al_get_mouse_state(&state);
            pos_x = state.x;
            pos_y = state.y;
            if(al_mouse_button_down(&state , 1) == 1 && pos_x > 535 && pos_x < 730 && pos_y > 300 && pos_y < 330){
                done = true;
            }
        }
        al_clear_to_color(al_map_rgb(0, 0, 0));
        done = false;
        Sleep(300);
        while (!done) {
            al_draw_bitmap(start,0,0,0);
            al_draw_text(font18, al_map_rgb(255, 255, 255), 540, 300, 0, "2 members");
            al_draw_text(font18, al_map_rgb(255, 255, 255), 540, 340, 0, "3 members");
            al_draw_text(font18, al_map_rgb(255, 255, 255), 540, 380, 0, "3 members");
            al_flip_display();
            al_get_mouse_state(&state);
            pos_x = state.x;
            pos_y = state.y;
            if(al_mouse_button_down(&state , 1) == 1 && pos_x > 535 && pos_x < 730 && pos_y > 300 && pos_y < 330){
                number = 2;
                done = true;
            }else if(al_mouse_button_down(&state , 1) == 1 && pos_x > 535 && pos_x < 730 && pos_y > 340 && pos_y < 370){
                number = 3;
                done = true;
            }else if(al_mouse_button_down(&state , 1) == 1 && pos_x > 535 && pos_x < 730 && pos_y > 380 && pos_y < 410){
                number = 4;
                done = true;
            }
        }
        al_clear_to_color(al_map_rgb(0, 0, 0));
        done = false;

        if(number == 2) {
            for (i = 0; i < 7; i++) {
                for (j = 0; j < 6; j++) {
                    if (rand() % 2 == 0 && player1.count < 16) {
                        count[i][j] = 1;
                        player1.count++;
                    } else if (rand() % 2 == 1 && player2.count < 15) {
                        count[i][j] = 2;
                        player2.count++;
                    } else if (player1.count < 16) {
                        count[i][j] = 1;
                        player1.count++;
                    } else if (player2.count < 15) {
                        count[i][j] = 2;
                        player2.count++;
                    }
                }
            }
            player1.sol = 15;
            player2.sol = 16;
            player3.sol = 0;
            player4.sol = 0;
            done = false;
            m = 0;
            k = 0;
        }else if(number == 3) {
            for (i = 0; i < 7; i++) {
                for (j = 0; j < 6; j++) {
                    if (rand() % 3 == 0 && player1.count < 10) {
                        count[i][j] = 1;
                        player1.count++;
                    } else if (rand() % 3 == 1 && player2.count < 10) {
                        count[i][j] = 2;
                        player2.count++;
                    } else if (rand() % 3 == 2 && player3.count < 9) {
                        count[i][j] = 3;
                        player3.count++;
                    } else if (player1.count < 10) {
                        count[i][j] = 1;
                        player1.count++;
                    } else if (player2.count < 10) {
                        count[i][j] = 2;
                        player2.count++;
                    } else if (player3.count < 9) {
                        count[i][j] = 3;
                        player3.count++;
                    }
                }
            }
            player1.sol = 15;
            player2.sol = 15;
            player3.sol = 16;
            player4.sol = 0;
            done = false;
            k = 0;
            m = 0;
        }else if(number == 4){
            for (i = 0; i < 7; i++) {
                for (j = 0; j < 6; j++) {
                    if (rand() % 4 == 0 && player1.count < 7) {
                        count[i][j] = 1;
                        player1.count++;
                    } else if (rand() % 4 == 1 && player2.count < 7) {
                        count[i][j] = 2;
                        player2.count++;
                    } else if (rand() % 4 == 2 && player3.count < 7) {
                        count[i][j] = 3;
                        player3.count++;
                    } else if (rand() % 4 == 3 && player3.count < 8) {
                        count[i][j] = 3;
                        player3.count++;
                    } else if (player1.count < 7) {
                        count[i][j] = 1;
                        player1.count++;
                    } else if (player2.count < 7) {
                        count[i][j] = 2;
                        player2.count++;
                    } else if (player3.count < 7) {
                        count[i][j] = 3;
                        player3.count++;
                    } else if (player4.count < 8) {
                        count[i][j] = 4;
                        player4.count++;
                    }
                }
            }
            player1.sol = 13;
            player2.sol = 13;
            player3.sol = 13;
            player4.sol = 12;
            done = false;
            k = 0;
            m = 0;
        }
        while (!done && (player1.sol > 0 || player2.sol > 0 || player3.sol > 0 || player4.sol > 0)) {
            al_clear_to_color(al_map_rgb(0,0,0));
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 100, 50, 0, "sol1 : %i", player1.sol);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 100, 70, 0, "sol2 : %i", player2.sol);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 100, 90, 0, "sol3 : %i", player3.sol);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 100, 110, 0, "sol4 : %i", player4.sol);
            al_draw_filled_rectangle(170, 135, 270, 195, al_map_rgb(0, 0, 0));
            al_draw_filled_rectangle(270, 135, 370, 225, al_map_rgb(255, 0, 0));
            al_draw_filled_rectangle(370, 135, 470, 255, al_map_rgb(0, 255, 0));
            al_draw_filled_rectangle(170, 195, 220, 285, al_map_rgb(0, 0, 0));
            al_draw_filled_rectangle(220, 195, 270, 285, al_map_rgb(0, 0, 255));
            al_draw_filled_rectangle(170, 285, 270, 315, al_map_rgb(0, 0, 0));
            al_draw_filled_rectangle(170, 315, 270, 345, al_map_rgb(0, 0, 255));
            al_draw_filled_rectangle(270, 225, 320, 255, al_map_rgb(0, 0, 255));
            al_draw_filled_rectangle(320, 225, 370, 315, al_map_rgb(255, 255, 0));
            al_draw_filled_rectangle(270, 255, 320, 345, al_map_rgb(255, 255, 0));
            al_draw_filled_rectangle(320, 315, 470, 345, al_map_rgb(0, 0, 255));
            al_draw_filled_rectangle(370, 255, 470, 345, al_map_rgb(0, 0, 255));
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 135, 0, "%i", sol[0][0]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 165, 0, "%i", sol[1][0]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 195, 0, "%i", sol[2][0]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 225, 0, "%i", sol[3][0]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 255, 0, "%i", sol[4][0]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 285, 0, "%i", sol[5][0]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 230, 135, 0, "%i", sol[0][1]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 230, 165, 0, "%i", sol[1][1]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 230, 285, 0, "%i", sol[5][1]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 135, 0, "%i", sol[0][2]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 165, 0, "%i", sol[1][2]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 195, 0, "%i", sol[2][2]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 135, 0, "%i", sol[0][3]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 165, 0, "%i", sol[1][3]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 195, 0, "%i", sol[2][3]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 225, 0, "%i", sol[3][3]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 255, 0, "%i", sol[4][3]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 285, 0, "%i", sol[5][3]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 255, 0, "%i", sol[4][2]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 285, 0, "%i", sol[5][2]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 315, 0, "%i", sol[6][2]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 135, 0, "%i", sol[0][4]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 165, 0, "%i", sol[1][4]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 195, 0, "%i", sol[2][4]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 225, 0, "%i", sol[3][4]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 135, 0, "%i", sol[0][5]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 165, 0, "%i", sol[1][5]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 195, 0, "%i", sol[2][5]);
            al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 225, 0, "%i", sol[3][5]);
            al_draw_filled_rectangle(500, 400, 565, 380, al_map_rgb(100, 100, 0));
            al_draw_text(font24, al_map_rgb(0, 0, 0), 500, 380, 0, "next");
            if(((k+1)% number == 0 && player1.sol > 0) || ((k+1)% number == 1 && player2.sol > 0) || ((k+1)% number == 2 && player3.sol > 0) || ((k+1)% number == 3 && player4.sol > 0)) {
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 300, 50, 0, "player%i", (k+1) % number + 1);
            }else{
                k++;
            }
            al_flip_display();
            ALLEGRO_EVENT ev;
            al_wait_for_event(event_queue,&ev);
            if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                if(ev.mouse.button & 1){
                    k++;
                    pos_x = ev.mouse.x;
                    pos_y = ev.mouse.y;
                    i = (pos_y - 135) / 30;
                    j = (pos_x - 170) / 50;
                    if (i >= 0 && i < 7 && j >= 0 && j < 6) {
                        if (k % number == 0 && player1.sol > 0) {
                            player1.sol--;
                            sol[i][j]++;
                        } else if (k % number == 1 && player2.sol > 0) {
                            player2.sol--;
                            sol[i][j]++;
                        }else if (k % number == 2 && player3.sol > 0) {
                            player3.sol--;
                            sol[i][j]++;
                        }else if (k % number == 3 && player4.sol > 0) {
                            player4.sol--;
                            sol[i][j]++;
                        }
                    } else if (pos_x > 500 && pos_x < 565 && pos_y > 380 && pos_y < 400) {
                        done = true;
                        break;
                    }
                }
            }
        }
        al_clear_to_color(al_map_rgb(0, 0, 0));
        done = false;
        int count1, count2, solfirst1, solfirst2, countfirst1, countfirst2;
        while (!done && player1.count != 29 && player2.count != 29 && player3.count != 29 && player4.count != 29) {
            if (m % number == 0) {
                k =  count_of_continent(player1.id, map, count, count_of_countries) + (player1.count / 3);
                while (!done && k > 0) {
                    al_clear_to_color(al_map_rgb(0,0,0));
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 50, 50, 0, "sol1 : %i", k);
                    al_draw_filled_rectangle(170, 135, 270, 195, al_map_rgb(0, 0, 0));
                    al_draw_filled_rectangle(270, 135, 370, 225, al_map_rgb(255, 0, 0));
                    al_draw_filled_rectangle(370, 135, 470, 255, al_map_rgb(0, 255, 0));
                    al_draw_filled_rectangle(170, 195, 220, 285, al_map_rgb(0, 0, 0));
                    al_draw_filled_rectangle(220, 195, 270, 285, al_map_rgb(0, 0, 255));
                    al_draw_filled_rectangle(170, 285, 270, 315, al_map_rgb(0, 0, 0));
                    al_draw_filled_rectangle(170, 315, 270, 345, al_map_rgb(0, 0, 255));
                    al_draw_filled_rectangle(270, 225, 320, 255, al_map_rgb(0, 0, 255));
                    al_draw_filled_rectangle(320, 225, 370, 315, al_map_rgb(255, 255, 0));
                    al_draw_filled_rectangle(270, 255, 320, 345, al_map_rgb(255, 255, 0));
                    al_draw_filled_rectangle(320, 315, 470, 345, al_map_rgb(0, 0, 255));
                    al_draw_filled_rectangle(370, 255, 470, 345, al_map_rgb(0, 0, 255));
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 135, 0, "%i", sol[0][0]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 165, 0, "%i", sol[1][0]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 195, 0, "%i", sol[2][0]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 225, 0, "%i", sol[3][0]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 255, 0, "%i", sol[4][0]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 285, 0, "%i", sol[5][0]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 230, 135, 0, "%i", sol[0][1]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 230, 165, 0, "%i", sol[1][1]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 230, 285, 0, "%i", sol[5][1]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 135, 0, "%i", sol[0][2]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 165, 0, "%i", sol[1][2]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 195, 0, "%i", sol[2][2]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 135, 0, "%i", sol[0][3]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 165, 0, "%i", sol[1][3]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 195, 0, "%i", sol[2][3]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 225, 0, "%i", sol[3][3]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 255, 0, "%i", sol[4][3]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 285, 0, "%i", sol[5][3]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 255, 0, "%i", sol[4][2]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 285, 0, "%i", sol[5][2]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 315, 0, "%i", sol[6][2]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 135, 0, "%i", sol[0][4]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 165, 0, "%i", sol[1][4]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 195, 0, "%i", sol[2][4]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 225, 0, "%i", sol[3][4]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 135, 0, "%i", sol[0][5]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 165, 0, "%i", sol[1][5]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 195, 0, "%i", sol[2][5]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 225, 0, "%i", sol[3][5]);
                    al_draw_filled_rectangle(500, 400, 565, 380, al_map_rgb(100, 100, 0));
                    al_draw_text(font24, al_map_rgb(0, 0, 0), 500, 380, 0, "next");
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 200, 50, 0, "player%i", m % number + 1);
                    al_flip_display();
                    al_draw_text(font24, al_map_rgb(255, 255, 255), 340, 100, 0, "add soldiers!");
                    ALLEGRO_EVENT ev;
                    al_wait_for_event(event_queue,&ev);
                    if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                        if(ev.mouse.button & 1){
                            pos_x = ev.mouse.x;
                            pos_y = ev.mouse.y;
                            i = (pos_y - 135) / 30;
                            j = (pos_x - 170) / 50;
                            if (i >= 0 && i < 7 && j >= 0 && j < 6) {
                                sol[i][j]++;
                                k--;
                            } else if (pos_x > 500 && pos_x < 565 && pos_y > 380 && pos_y < 400) {
                                done = true;
                                break;
                            }
                        }
                    }
                }
            } else if (m % number == 1) {
                k = count_of_continent(player2.id, map, count, count_of_countries) + (player2.count / 3);
                while (!done && k > 0) {
                    al_clear_to_color(al_map_rgb(0,0,0));
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 50, 50, 0, "sol2 : %i", k);
                    al_draw_filled_rectangle(170, 135, 270, 195, al_map_rgb(0, 0, 0));
                    al_draw_filled_rectangle(270, 135, 370, 225, al_map_rgb(255, 0, 0));
                    al_draw_filled_rectangle(370, 135, 470, 255, al_map_rgb(0, 255, 0));
                    al_draw_filled_rectangle(170, 195, 220, 285, al_map_rgb(0, 0, 0));
                    al_draw_filled_rectangle(220, 195, 270, 285, al_map_rgb(0, 0, 255));
                    al_draw_filled_rectangle(170, 285, 270, 315, al_map_rgb(0, 0, 0));
                    al_draw_filled_rectangle(170, 315, 270, 345, al_map_rgb(0, 0, 255));
                    al_draw_filled_rectangle(270, 225, 320, 255, al_map_rgb(0, 0, 255));
                    al_draw_filled_rectangle(320, 225, 370, 315, al_map_rgb(255, 255, 0));
                    al_draw_filled_rectangle(270, 255, 320, 345, al_map_rgb(255, 255, 0));
                    al_draw_filled_rectangle(320, 315, 470, 345, al_map_rgb(0, 0, 255));
                    al_draw_filled_rectangle(370, 255, 470, 345, al_map_rgb(0, 0, 255));
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 135, 0, "%i", sol[0][0]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 165, 0, "%i", sol[1][0]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 195, 0, "%i", sol[2][0]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 225, 0, "%i", sol[3][0]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 255, 0, "%i", sol[4][0]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 285, 0, "%i", sol[5][0]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 230, 135, 0, "%i", sol[0][1]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 230, 165, 0, "%i", sol[1][1]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 230, 285, 0, "%i", sol[5][1]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 135, 0, "%i", sol[0][2]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 165, 0, "%i", sol[1][2]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 195, 0, "%i", sol[2][2]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 135, 0, "%i", sol[0][3]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 165, 0, "%i", sol[1][3]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 195, 0, "%i", sol[2][3]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 225, 0, "%i", sol[3][3]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 255, 0, "%i", sol[4][3]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 285, 0, "%i", sol[5][3]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 255, 0, "%i", sol[4][2]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 285, 0, "%i", sol[5][2]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 315, 0, "%i", sol[6][2]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 135, 0, "%i", sol[0][4]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 165, 0, "%i", sol[1][4]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 195, 0, "%i", sol[2][4]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 225, 0, "%i", sol[3][4]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 135, 0, "%i", sol[0][5]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 165, 0, "%i", sol[1][5]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 195, 0, "%i", sol[2][5]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 225, 0, "%i", sol[3][5]);
                    al_draw_filled_rectangle(500, 400, 565, 380, al_map_rgb(100, 100, 0));
                    al_draw_text(font24, al_map_rgb(0, 0, 0), 500, 380, 0, "next");
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 200, 50, 0, "player%i", m % number + 1);
                    al_flip_display();
                    al_draw_text(font24, al_map_rgb(255, 255, 255), 340, 100, 0, "add soldiers!");
                    ALLEGRO_EVENT ev;
                    al_wait_for_event(event_queue,&ev);
                    if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                        if(ev.mouse.button & 1){
                            pos_x = ev.mouse.x;
                            pos_y = ev.mouse.y;
                            i = (pos_y - 135) / 30;
                            j = (pos_x - 170) / 50;
                            if (i >= 0 && i < 7 && j >= 0 && j < 6) {
                                sol[i][j]++;
                                k--;
                            } else if (pos_x > 500 && pos_x < 565 && pos_y > 380 && pos_y < 400) {
                                done = true;
                                break;
                            }
                        }
                    }
                }
            } else if (m % number == 2) {
                k = count_of_continent(player3.id, map, count, count_of_countries) + (player3.count / 3);
                while (!done && k > 0) {
                    al_clear_to_color(al_map_rgb(0,0,0));
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 50, 50, 0, "sol3 : %i", k);
                    al_draw_filled_rectangle(170, 135, 270, 195, al_map_rgb(0, 0, 0));
                    al_draw_filled_rectangle(270, 135, 370, 225, al_map_rgb(255, 0, 0));
                    al_draw_filled_rectangle(370, 135, 470, 255, al_map_rgb(0, 255, 0));
                    al_draw_filled_rectangle(170, 195, 220, 285, al_map_rgb(0, 0, 0));
                    al_draw_filled_rectangle(220, 195, 270, 285, al_map_rgb(0, 0, 255));
                    al_draw_filled_rectangle(170, 285, 270, 315, al_map_rgb(0, 0, 0));
                    al_draw_filled_rectangle(170, 315, 270, 345, al_map_rgb(0, 0, 255));
                    al_draw_filled_rectangle(270, 225, 320, 255, al_map_rgb(0, 0, 255));
                    al_draw_filled_rectangle(320, 225, 370, 315, al_map_rgb(255, 255, 0));
                    al_draw_filled_rectangle(270, 255, 320, 345, al_map_rgb(255, 255, 0));
                    al_draw_filled_rectangle(320, 315, 470, 345, al_map_rgb(0, 0, 255));
                    al_draw_filled_rectangle(370, 255, 470, 345, al_map_rgb(0, 0, 255));
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 135, 0, "%i", sol[0][0]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 165, 0, "%i", sol[1][0]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 195, 0, "%i", sol[2][0]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 225, 0, "%i", sol[3][0]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 255, 0, "%i", sol[4][0]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 285, 0, "%i", sol[5][0]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 230, 135, 0, "%i", sol[0][1]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 230, 165, 0, "%i", sol[1][1]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 230, 285, 0, "%i", sol[5][1]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 135, 0, "%i", sol[0][2]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 165, 0, "%i", sol[1][2]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 195, 0, "%i", sol[2][2]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 135, 0, "%i", sol[0][3]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 165, 0, "%i", sol[1][3]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 195, 0, "%i", sol[2][3]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 225, 0, "%i", sol[3][3]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 255, 0, "%i", sol[4][3]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 285, 0, "%i", sol[5][3]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 255, 0, "%i", sol[4][2]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 285, 0, "%i", sol[5][2]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 315, 0, "%i", sol[6][2]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 135, 0, "%i", sol[0][4]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 165, 0, "%i", sol[1][4]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 195, 0, "%i", sol[2][4]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 225, 0, "%i", sol[3][4]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 135, 0, "%i", sol[0][5]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 165, 0, "%i", sol[1][5]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 195, 0, "%i", sol[2][5]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 225, 0, "%i", sol[3][5]);
                    al_draw_filled_rectangle(500, 400, 565, 380, al_map_rgb(100, 100, 0));
                    al_draw_text(font24, al_map_rgb(0, 0, 0), 500, 380, 0, "next");
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 200, 50, 0, "player%i", m % number + 1);
                    al_flip_display();
                    al_draw_text(font24, al_map_rgb(255, 255, 255), 340, 100, 0, "add soldiers!");
                    ALLEGRO_EVENT ev;
                    al_wait_for_event(event_queue,&ev);
                    if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                        if(ev.mouse.button & 1){
                            pos_x = ev.mouse.x;
                            pos_y = ev.mouse.y;
                            i = (pos_y - 135) / 30;
                            j = (pos_x - 170) / 50;
                            if (i >= 0 && i < 7 && j >= 0 && j < 6) {
                                sol[i][j]++;
                                k--;
                            } else if (pos_x > 500 && pos_x < 565 && pos_y > 380 && pos_y < 400) {
                                done = true;
                                break;
                            }
                        }
                    }
                }
            } else if (m % number == 3) {
                k = count_of_continent(player4.id, map, count, count_of_countries) + (player4.count / 3);
                while (!done && k > 0) {
                    al_clear_to_color(al_map_rgb(0,0,0));
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 50, 50, 0, "sol4 : %i", k);
                    al_draw_filled_rectangle(170, 135, 270, 195, al_map_rgb(0, 0, 0));
                    al_draw_filled_rectangle(270, 135, 370, 225, al_map_rgb(255, 0, 0));
                    al_draw_filled_rectangle(370, 135, 470, 255, al_map_rgb(0, 255, 0));
                    al_draw_filled_rectangle(170, 195, 220, 285, al_map_rgb(0, 0, 0));
                    al_draw_filled_rectangle(220, 195, 270, 285, al_map_rgb(0, 0, 255));
                    al_draw_filled_rectangle(170, 285, 270, 315, al_map_rgb(0, 0, 0));
                    al_draw_filled_rectangle(170, 315, 270, 345, al_map_rgb(0, 0, 255));
                    al_draw_filled_rectangle(270, 225, 320, 255, al_map_rgb(0, 0, 255));
                    al_draw_filled_rectangle(320, 225, 370, 315, al_map_rgb(255, 255, 0));
                    al_draw_filled_rectangle(270, 255, 320, 345, al_map_rgb(255, 255, 0));
                    al_draw_filled_rectangle(320, 315, 470, 345, al_map_rgb(0, 0, 255));
                    al_draw_filled_rectangle(370, 255, 470, 345, al_map_rgb(0, 0, 255));
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 135, 0, "%i", sol[0][0]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 165, 0, "%i", sol[1][0]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 195, 0, "%i", sol[2][0]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 225, 0, "%i", sol[3][0]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 255, 0, "%i", sol[4][0]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 285, 0, "%i", sol[5][0]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 230, 135, 0, "%i", sol[0][1]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 230, 165, 0, "%i", sol[1][1]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 230, 285, 0, "%i", sol[5][1]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 135, 0, "%i", sol[0][2]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 165, 0, "%i", sol[1][2]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 195, 0, "%i", sol[2][2]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 135, 0, "%i", sol[0][3]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 165, 0, "%i", sol[1][3]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 195, 0, "%i", sol[2][3]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 225, 0, "%i", sol[3][3]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 255, 0, "%i", sol[4][3]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 285, 0, "%i", sol[5][3]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 255, 0, "%i", sol[4][2]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 285, 0, "%i", sol[5][2]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 315, 0, "%i", sol[6][2]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 135, 0, "%i", sol[0][4]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 165, 0, "%i", sol[1][4]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 195, 0, "%i", sol[2][4]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 225, 0, "%i", sol[3][4]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 135, 0, "%i", sol[0][5]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 165, 0, "%i", sol[1][5]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 195, 0, "%i", sol[2][5]);
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 225, 0, "%i", sol[3][5]);
                    al_draw_filled_rectangle(500, 400, 565, 380, al_map_rgb(100, 100, 0));
                    al_draw_text(font24, al_map_rgb(0, 0, 0), 500, 380, 0, "next");
                    al_draw_textf(font18, al_map_rgb(255, 255, 255), 200, 50, 0, "player%i", m % number + 1);
                    al_flip_display();
                    al_draw_text(font24, al_map_rgb(255, 255, 255), 340, 100, 0, "add soldiers!");
                    ALLEGRO_EVENT ev;
                    al_wait_for_event(event_queue,&ev);
                    if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                        if(ev.mouse.button & 1){
                            pos_x = ev.mouse.x;
                            pos_y = ev.mouse.y;
                            i = (pos_y - 135) / 30;
                            j = (pos_x - 170) / 50;
                            if (i >= 0 && i < 7 && j >= 0 && j < 6) {
                                sol[i][j]++;
                                k--;
                            } else if (pos_x > 500 && pos_x < 565 && pos_y > 380 && pos_y < 400) {
                                done = true;
                                break;
                            }
                        }
                    }
                }
            }
            al_clear_to_color(al_map_rgb(0, 0, 0));
            k = -1;
            while (!done) {
                al_clear_to_color(al_map_rgb(0,0,0));
                al_draw_filled_rectangle(170, 135, 270, 195, al_map_rgb(0, 0, 0));
                al_draw_filled_rectangle(270, 135, 370, 225, al_map_rgb(255, 0, 0));
                al_draw_filled_rectangle(370, 135, 470, 255, al_map_rgb(0, 255, 0));
                al_draw_filled_rectangle(170, 195, 220, 285, al_map_rgb(0, 0, 0));
                al_draw_filled_rectangle(220, 195, 270, 285, al_map_rgb(0, 0, 255));
                al_draw_filled_rectangle(170, 285, 270, 315, al_map_rgb(0, 0, 0));
                al_draw_filled_rectangle(170, 315, 270, 345, al_map_rgb(0, 0, 255));
                al_draw_filled_rectangle(270, 225, 320, 255, al_map_rgb(0, 0, 255));
                al_draw_filled_rectangle(320, 225, 370, 315, al_map_rgb(255, 255, 0));
                al_draw_filled_rectangle(270, 255, 320, 345, al_map_rgb(255, 255, 0));
                al_draw_filled_rectangle(320, 315, 470, 345, al_map_rgb(0, 0, 255));
                al_draw_filled_rectangle(370, 255, 470, 345, al_map_rgb(0, 0, 255));
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 135, 0, "%i", sol[0][0]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 165, 0, "%i", sol[1][0]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 195, 0, "%i", sol[2][0]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 225, 0, "%i", sol[3][0]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 255, 0, "%i", sol[4][0]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 285, 0, "%i", sol[5][0]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 230, 135, 0, "%i", sol[0][1]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 230, 165, 0, "%i", sol[1][1]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 230, 285, 0, "%i", sol[5][1]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 135, 0, "%i", sol[0][2]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 165, 0, "%i", sol[1][2]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 195, 0, "%i", sol[2][2]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 135, 0, "%i", sol[0][3]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 165, 0, "%i", sol[1][3]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 195, 0, "%i", sol[2][3]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 225, 0, "%i", sol[3][3]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 255, 0, "%i", sol[4][3]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 285, 0, "%i", sol[5][3]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 255, 0, "%i", sol[4][2]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 285, 0, "%i", sol[5][2]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 315, 0, "%i", sol[6][2]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 135, 0, "%i", sol[0][4]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 165, 0, "%i", sol[1][4]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 195, 0, "%i", sol[2][4]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 225, 0, "%i", sol[3][4]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 135, 0, "%i", sol[0][5]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 165, 0, "%i", sol[1][5]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 195, 0, "%i", sol[2][5]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 225, 0, "%i", sol[3][5]);
                al_draw_filled_rectangle(500, 400, 565, 380, al_map_rgb(100, 100, 0));
                al_draw_text(font24, al_map_rgb(0, 0, 0), 500, 380, 0, "next");
                al_draw_text(font24, al_map_rgb(100, 100, 0), 240, 100, 0, "attacking!");
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 50, 50, 0, "player%i", m % number + 1);
                al_flip_display();
                ALLEGRO_EVENT ev;
                al_wait_for_event(event_queue, &ev);
                if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                    if (ev.mouse.button & 1) {
                        pos_y = ev.mouse.y;
                        pos_x = ev.mouse.x;
                        i = (pos_y - 135) / 30;
                        j = (pos_x - 170) / 50;
                        if (pos_x < 565 && pos_x > 500 && pos_y > 380 && pos_y < 400) {
                            done = true;
                            break;
                        } else if (i >= 0 && i < 8 && j >= 0 && j < 7) {
                            k++;
                            if (k % 2 == 0) {
                                i1 = i;
                                j1 = j;
                            } else if (k % 2 == 1) {
                                i2 = i;
                                j2 = j;
                                if (is_around(i1, j1, i2, j2)) {
                                    if ((sol[i1][j1] - 1) / 3 >= 1) {
                                        count1 = 3;
                                    } else {
                                        count1 = sol[i1][j1] - 1;
                                        if (count1 == 0) {
                                            al_draw_text(font24, al_map_rgb(255, 255, 255), 30, 30, 0,"you cant attack!");
                                            break;
                                        }
                                    }
                                    if (sol[i2][j2] >= 2) {
                                        count2 = 2;
                                    } else {
                                        count2 = 1;
                                    }
                                    int attack[count1], defense[count2];
                                    int min = min(count1,count2);
                                    for (i = 0; i < count1; i++) {
                                        attack[i] = rand() % 6;
                                    }
                                    for (i = 0; i < count2; i++) {
                                        defense[i] = rand() % 6;
                                    }
                                    up_to_down(attack, count1);
                                    up_to_down(defense, count2);
                                    solfirst1 = sol[i1][j1];
                                    solfirst2 = sol[i2][j2];
                                    countfirst1 = count1;
                                    countfirst2 = count2;
                                    for (i = 0; i < min; i++) {
                                        if (defense[i] >= attack[i]) {
                                            sol[i1][j1]--;
                                            count1--;
                                        } else {
                                            sol[i2][j2]--;
                                            count2--;
                                        }
                                        if (solfirst1 - sol[i1][j1] == countfirst1) {
                                            count[i1][j1] = count[i2][j2];
                                            sol[i1][j1] = count2;
                                            sol[i2][j2] -= count2;
                                            break;
                                        } else if (solfirst2 - sol[i2][j2] == countfirst2) {
                                            count[i2][j2] = count[i1][j1];
                                            sol[i2][j2] = count1;
                                            sol[i1][j1] -= count1;
                                            break;
                                        }
                                    }
                                }else{
                                    al_draw_text(font18, al_map_rgb(255,255,255),100,400,0,"these are not around each other!");
                                }
                            }
                        }
                    }
                }
            }
            done = false;
            k = -1;
            while (!done) {
                al_clear_to_color(al_map_rgb(0,0,0));
                al_draw_text(font24, al_map_rgb(100, 100, 0), 240, 100, 0, "converting soldiers!");
                al_draw_filled_rectangle(170, 135, 270, 195, al_map_rgb(0, 0, 0));
                al_draw_filled_rectangle(270, 135, 370, 225, al_map_rgb(255, 0, 0));
                al_draw_filled_rectangle(370, 135, 470, 255, al_map_rgb(0, 255, 0));
                al_draw_filled_rectangle(170, 195, 220, 285, al_map_rgb(0, 0, 0));
                al_draw_filled_rectangle(220, 195, 270, 285, al_map_rgb(0, 0, 255));
                al_draw_filled_rectangle(170, 285, 270, 315, al_map_rgb(0, 0, 0));
                al_draw_filled_rectangle(170, 315, 270, 345, al_map_rgb(0, 0, 255));
                al_draw_filled_rectangle(270, 225, 320, 255, al_map_rgb(0, 0, 255));
                al_draw_filled_rectangle(320, 225, 370, 315, al_map_rgb(255, 255, 0));
                al_draw_filled_rectangle(270, 255, 320, 345, al_map_rgb(255, 255, 0));
                al_draw_filled_rectangle(320, 315, 470, 345, al_map_rgb(0, 0, 255));
                al_draw_filled_rectangle(370, 255, 470, 345, al_map_rgb(0, 0, 255));
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 135, 0, "%i", sol[0][0]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 165, 0, "%i", sol[1][0]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 195, 0, "%i", sol[2][0]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 225, 0, "%i", sol[3][0]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 255, 0, "%i", sol[4][0]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 180, 285, 0, "%i", sol[5][0]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 230, 135, 0, "%i", sol[0][1]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 230, 165, 0, "%i", sol[1][1]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 230, 285, 0, "%i", sol[5][1]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 135, 0, "%i", sol[0][2]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 165, 0, "%i", sol[1][2]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 195, 0, "%i", sol[2][2]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 135, 0, "%i", sol[0][3]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 165, 0, "%i", sol[1][3]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 195, 0, "%i", sol[2][3]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 225, 0, "%i", sol[3][3]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 255, 0, "%i", sol[4][3]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 330, 285, 0, "%i", sol[5][3]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 255, 0, "%i", sol[4][2]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 285, 0, "%i", sol[5][2]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 280, 315, 0, "%i", sol[6][2]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 135, 0, "%i", sol[0][4]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 165, 0, "%i", sol[1][4]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 195, 0, "%i", sol[2][4]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 380, 225, 0, "%i", sol[3][4]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 135, 0, "%i", sol[0][5]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 165, 0, "%i", sol[1][5]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 195, 0, "%i", sol[2][5]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 430, 225, 0, "%i", sol[3][5]);
                al_draw_textf(font18, al_map_rgb(255, 255, 255), 50, 50, 0, "player%i", m % number + 1);
                al_draw_text(font24, al_map_rgb(0, 0, 0), 500, 380, 0, "next");
                for(i=0; i<7; i++){
                    for(j=0; j<6; j++){
                        if(map[i][j] != 4){
                            if(count[i][j]==1){
                                al_draw_circle(180+j*50,145+i*30,5, al_map_rgb(255,255,255),2);
                            }else{
                                al_draw_filled_circle(180+j*50,145+i*30,5, al_map_rgb(255,255,255));
                            }
                        }
                    }
                }
                al_flip_display();
                done = false;
                ALLEGRO_EVENT ev;
                al_wait_for_event(event_queue, &ev);
                if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                    if (ev.mouse.button & 1) {
                        pos_y = ev.mouse.y;
                        pos_x = ev.mouse.x;
                        i = (pos_y - 135) / 30;
                        j = (pos_x - 170) / 50;
                        if (pos_x < 560 && pos_x > 500 && pos_y > 380 && pos_y < 400) {
                            done = true;
                            break;
                        } else if (i >= 0 && i < 8 && j >= 0 && j < 7) {
                            k++;
                            if (k % 2 == 0) {
                                i1 = i;
                                j1 = j;
                            } else if (k % 2 == 1) {
                                i2 = i;
                                j2 = j;
                                sol[i1][j1]--;
                                sol[i2][j2]++;
                            }
                        }
                    }
                }
            }
        }
        if(player1.count == 29){
            al_draw_text(font24, al_map_rgb(255, 255, 0), 50, 50, 0, "player1 won!");
        }else if(player2.count == 29){
            al_draw_text(font24, al_map_rgb(255, 255, 0), 50, 50, 0, "player2 won!");
        }else if(player2.count == 29){
            al_draw_text(font24, al_map_rgb(255, 255, 0), 50, 50, 0, "player3 won");
        }else if(player2.count == 29){
            al_draw_text(font24, al_map_rgb(255, 255, 0), 50, 50, 0, "player4 won");
        }
        al_flip_display();
        al_rest(5.0);
        al_destroy_display(display);
        al_destroy_bitmap(start);
        al_destroy_bitmap(board);
        return 0;
    }
