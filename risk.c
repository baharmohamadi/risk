#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <stdbool.h>
#include <stdio.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <time.h>

struct player{
    int sol;                           //count of soldiers
    int count;                         //count of countries
    int id;
};

bool is_continent(int player, int number_of_country,int map[7][6], int count[7][6], int count_of_countries[4]){
    int i,j,k = 0;
    for(i=0; i<7; i++){
        for(j=0; j<6; j++){
            if(map[i][j] == number_of_country && count[i][j] == player){
                k++;
            }
        }
    }
    if(k == count_of_countries[number_of_country]){
        return true;
    }
    return false;
}

int count_of_continent(int player,int map[7][6], int count[7][6], int count_of_countries[4]){
    int i, k = 0;
    for(i=0; i<4; i++){
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
        int width = 640;
        int height = 480;
        int pos_x, pos_y;
        int sol[7][6], count[7][6], map[7][6], i, j, i1, i2, j1, j2;
        bool done = false;
        int count_of_countries[4] = {9, 6, 8, 6};
        player1.id = 1;
        player2.id = 2;
        player3.id = 3;
        player4.id = 4;
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
        ALLEGRO_TIMER  *timer = al_create_timer(1.0 / 60);
        ALLEGRO_FONT *font24 = al_load_font("font.ttf", 24, 0);
        ALLEGRO_FONT *fontt24 = al_load_font("fontt.ttf", 24, 0);
        ALLEGRO_FONT *font18 = al_load_font("font.ttf", 18, 0);
        event_queue = al_create_event_queue();
        al_register_event_source(event_queue, al_get_display_event_source(display));
        al_register_event_source(event_queue, al_get_mouse_event_source());
        al_register_event_source(event_queue, al_get_timer_event_source(timer));
        al_start_timer(timer);

        while (!done) {
            ALLEGRO_EVENT ev;
            al_draw_text(font24, al_map_rgb(255, 255, 255), 190, 100, 0, "welcome to risk");
            al_draw_filled_rectangle(100, 155, 260, 185, al_map_rgb(50, 50, 50));
            al_draw_rectangle(100, 155, 260, 185, al_map_rgb(0, 100, 100), 3);
            al_draw_text(font24, al_map_rgb(255, 0, 0), 100, 160, 0, "New game");
            al_draw_filled_rectangle(100, 200, 290, 230, al_map_rgb(50, 50, 50));
            al_draw_rectangle(100, 200, 290, 230, al_map_rgb(0, 100, 100), 3);
            al_draw_text(font24, al_map_rgb(255, 0, 0), 100, 200, 0, "How to play");
            //al_clear_to_color(al_map_rgb(0,0,0));
            al_wait_for_event(event_queue, &ev);
            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                done = true;
                break;
            } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                if (ev.mouse.button & 1) {
                    pos_x = ev.mouse.x;
                    pos_y = ev.mouse.y;
                    if (pos_x > 100 && pos_x < 260 && pos_y > 155 && pos_y < 185) {
                        while(!done){
                            al_draw_filled_rectangle(265,144,285,160, al_map_rgb(50,50,50));
                            al_draw_filled_rectangle(265,162,285,178, al_map_rgb(50,50,50));
                            al_draw_filled_rectangle(265,180,285,196, al_map_rgb(50,50,50));
                            al_draw_text(font18, al_map_rgb(255,0,0),275,168,0,"2 members");
                            al_draw_text(font18, al_map_rgb(255,0,0),275,170,0,"3 members");
                            al_draw_text(font18, al_map_rgb(255,0,0),275,188,0,"4 members");
                            al_flip_display();
                            al_wait_for_event(event_queue,&ev);
                            if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                                IF(ev.mouse.button & 1){
                                    pos_x = ev.mouse.x;
                                    pos_y = ev.mouse.y;
                                    if(pos_x > 265 && pos_x <285 && pos_y > 144 && pos_y < 160){
                                        member = 2;
                                        done = true;
                                        break;
                                    } else if(pos_x > 265 && pos_x <285 && pos_y > 162 && pos_y < 178){
                                        member = 3;
                                        done = true;
                                        break;
                                    } else if(pos_x > 265 && pos_x <285 && pos_y > 180 && pos_y < 196){
                                        member = 4;
                                        done = true;
                                        break;
                                    }
                                }
                            }
                        }
                        break;
                    }
                }
            }
            al_flip_display();
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));

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
        done = false;
        int k = 0;
        while (!done && (player1.sol > 0 || player2.sol > 0)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 50, 50, 0, "%i", player1.sol);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 50, 70, 0, "%i", player2.sol);
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
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 180, 135, 0, "%i", sol[0][0]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 180, 165, 0, "%i", sol[1][0]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 180, 195, 0, "%i", sol[2][0]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 180, 225, 0, "%i", sol[3][0]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 180, 255, 0, "%i", sol[4][0]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 180, 285, 0, "%i", sol[5][0]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 230, 135, 0, "%i", sol[0][1]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 230, 165, 0, "%i", sol[1][1]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 230, 285, 0, "%i", sol[5][1]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 280, 135, 0, "%i", sol[0][2]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 280, 165, 0, "%i", sol[1][2]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 280, 195, 0, "%i", sol[2][2]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 330, 135, 0, "%i", sol[0][3]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 330, 165, 0, "%i", sol[1][3]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 330, 195, 0, "%i", sol[2][3]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 330, 225, 0, "%i", sol[3][3]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 330, 255, 0, "%i", sol[4][3]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 330, 285, 0, "%i", sol[5][3]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 280, 255, 0, "%i", sol[4][2]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 280, 285, 0, "%i", sol[5][2]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 280, 315, 0, "%i", sol[6][2]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 380, 135, 0, "%i", sol[0][4]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 380, 165, 0, "%i", sol[1][4]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 380, 195, 0, "%i", sol[2][4]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 380, 225, 0, "%i", sol[3][4]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 430, 135, 0, "%i", sol[0][5]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 430, 165, 0, "%i", sol[1][5]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 430, 195, 0, "%i", sol[2][5]);
            al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 430, 225, 0, "%i", sol[3][5]);
            al_draw_filled_rectangle(500, 400, 565, 380, al_map_rgb(100, 100, 0));
            al_draw_text(font24, al_map_rgb(0, 0, 0), 500, 380, 0, "next");
            al_flip_display();
            ALLEGRO_EVENT ev;
                al_wait_for_event(event_queue, &ev);
                if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                    if (ev.mouse.button & 1) {
                        pos_y = ev.mouse.y;
                        pos_x = ev.mouse.x;
                        if (pos_x < 540 && pos_x > 500 && pos_y > 400 && pos_y < 420) {
                            done = true;
                            break;
                        } else if ((pos_y - 135) / 30 >= 0 && (pos_y - 135) / 30 < 8 && (pos_x - 170) / 50 >= 0 &&
                                   (pos_x - 170) / 50 < 7) {
                            sol[(pos_y - 135) / 30][(pos_x - 170) / 50]++;
                            k++;
                            if (k % 2 == 0 && player1.sol > 0) {
                                player1.sol--;
                            } else if (k % 2 == 1 && player2.sol > 0) {
                                player2.sol--;
                            }else {
                                continue;
                            }
                        }
                    }
                }
            }
        al_clear_to_color(al_map_rgb(0,0,0));
        done = false;

        int count1,count2,solfirst1,solfirst2,countfirst1,countfirst2;

        while (!done && player1.count != 29 && player2.count != 29) {
            //   k = 0;
            /*while (!done && k < count_of_continent(player1.id, map, count, count_of_countries) + (player1.count/3)) {
                al_draw_text(font24, al_map_rgb(100,100,0),240,100,0,"add soldiers!");
                paint_map(sol);
                ALLEGRO_EVENT ev;
                al_wait_for_event(event_queue,&ev);
                if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                    if(ev.mouse.button & 1){
                        pos_x = ev.mouse.x;
                        pos_y = ev.mouse.y;
                        if((pos_y - 135)/30 > 0 && (pos_y - 135)/30 < 8 && (pos_x - 170) / 50 > 0 && (pos_x - 170) / 50 < 7) {
                            sol[(pos_y - 135) / 30][(pos_x - 170) / 50]++;
                            k++;
                        }else if( pos_y < 400 && pos_y > 380 && pos_x > 500 & pos_x < 565){
                            done = true;
                            break;
                        }
                    }
                }
            }
            al_clear_to_color(al_map_rgb(0,0,0));
*/
            k = -1;

            while (!done) {
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
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 180, 135, 0, "%i", sol[0][0]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 180, 165, 0, "%i", sol[1][0]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 180, 195, 0, "%i", sol[2][0]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 180, 225, 0, "%i", sol[3][0]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 180, 255, 0, "%i", sol[4][0]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 180, 285, 0, "%i", sol[5][0]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 230, 135, 0, "%i", sol[0][1]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 230, 165, 0, "%i", sol[1][1]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 230, 285, 0, "%i", sol[5][1]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 280, 135, 0, "%i", sol[0][2]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 280, 165, 0, "%i", sol[1][2]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 280, 195, 0, "%i", sol[2][2]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 330, 135, 0, "%i", sol[0][3]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 330, 165, 0, "%i", sol[1][3]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 330, 195, 0, "%i", sol[2][3]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 330, 225, 0, "%i", sol[3][3]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 330, 255, 0, "%i", sol[4][3]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 330, 285, 0, "%i", sol[5][3]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 280, 255, 0, "%i", sol[4][2]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 280, 285, 0, "%i", sol[5][2]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 280, 315, 0, "%i", sol[6][2]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 380, 135, 0, "%i", sol[0][4]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 380, 165, 0, "%i", sol[1][4]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 380, 195, 0, "%i", sol[2][4]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 380, 225, 0, "%i", sol[3][4]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 430, 135, 0, "%i", sol[0][5]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 430, 165, 0, "%i", sol[1][5]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 430, 195, 0, "%i", sol[2][5]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 430, 225, 0, "%i", sol[3][5]);
                al_draw_filled_rectangle(500, 400, 565, 380, al_map_rgb(100, 100, 0));
                al_draw_text(font24, al_map_rgb(0, 0, 0), 500, 380, 0, "next");
                al_draw_text(font24, al_map_rgb(100, 100, 0), 240, 100, 0, "attacking!");
                al_flip_display();
                ALLEGRO_EVENT ev;
                al_wait_for_event(event_queue, &ev);
                if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                    if (ev.mouse.button & 1) {
                        pos_y = ev.mouse.y;
                        pos_x = ev.mouse.x;
                        if (pos_x < 540 && pos_x > 500 && pos_y > 400 && pos_y < 420) {
                            done = true;
                            break;
                        } else if ((pos_y - 135) / 30 >= 0 && (pos_y - 135) / 30 < 8 && (pos_x - 170) / 50 >= 0 && (pos_x - 170) / 50 < 7) {
                            k++;
                            if (k % 2 == 0) {
                                i1 = (pos_y - 135) / 30;
                                j1 = (pos_x - 170) / 50;
                            } else if (k % 2 == 1) {
                                i2 = (pos_y - 135) / 30;
                                j2 = (pos_x - 170) / 50;
                                if(is_around(i1, j1, i2, j2)) {
                                    //attack(&sol[i1][j1], &sol[i2][j2], &count[i1][j1], &count[i2][j2]);
                                    if((sol[i1][j1]-1)/3 >= 1){
                                        count1 = 3;
                                    }else{
                                        count1 = sol[i1][j1] - 1;
                                        if(count1 == 0){
                                            al_draw_text(font24, al_map_rgb(255,255,255),30,30,0,"you cant attack!");
                                            break;
                                        }
                                    }

                                    if(sol[i2][j2] >= 2){
                                        count2 = 2;
                                    }else{
                                        count2 = 1;
                                    }

                                    int attack[count1], defense[count2];

                                    for (i = 0; i < count1; i++){
                                        attack[i] = rand() % 6;
                                    }

                                    for (i = 0; i < count2; i++){
                                        defense[i] = rand() % 6;
                                    }

                                    up_to_down(attack,count1);
                                    up_to_down(defense,count2);

                                    solfirst1 = sol[i1][j1];
                                    solfirst2 = sol[i2][j2];
                                    countfirst1 = count1;
                                    countfirst2 = count2;
                                    for(i=0; i<count2; i++){
                                        if(defense[i] >= attack[i]){
                                            sol[i1][j1]--;
                                            count1--;
                                        }else{
                                            sol[i2][j2]--;
                                            count2--;
                                        }
                                        if(solfirst1 - sol[i1][j1] == countfirst1){
                                            count[i1][j1] = count[i2][j2];
                                            sol[i1][j1] = count2;
                                            break;
                                        }else if(solfirst2 - sol[i2][j2] == countfirst2){
                                            count[i2][j2] = count[i1][j1];
                                            sol[i2][j2] = count1;
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            done = false;
            k = -1;
            while (!done) {
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
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 180, 135, 0, "%i", sol[0][0]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 180, 165, 0, "%i", sol[1][0]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 180, 195, 0, "%i", sol[2][0]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 180, 225, 0, "%i", sol[3][0]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 180, 255, 0, "%i", sol[4][0]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 180, 285, 0, "%i", sol[5][0]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 230, 135, 0, "%i", sol[0][1]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 230, 165, 0, "%i", sol[1][1]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 230, 285, 0, "%i", sol[5][1]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 280, 135, 0, "%i", sol[0][2]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 280, 165, 0, "%i", sol[1][2]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 280, 195, 0, "%i", sol[2][2]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 330, 135, 0, "%i", sol[0][3]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 330, 165, 0, "%i", sol[1][3]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 330, 195, 0, "%i", sol[2][3]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 330, 225, 0, "%i", sol[3][3]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 330, 255, 0, "%i", sol[4][3]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 330, 285, 0, "%i", sol[5][3]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 280, 255, 0, "%i", sol[4][2]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 280, 285, 0, "%i", sol[5][2]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 280, 315, 0, "%i", sol[6][2]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 380, 135, 0, "%i", sol[0][4]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 380, 165, 0, "%i", sol[1][4]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 380, 195, 0, "%i", sol[2][4]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 380, 225, 0, "%i", sol[3][4]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 430, 135, 0, "%i", sol[0][5]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 430, 165, 0, "%i", sol[1][5]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 430, 195, 0, "%i", sol[2][5]);
                al_draw_textf(fontt24, al_map_rgb(255, 255, 255), 430, 225, 0, "%i", sol[3][5]);
                al_draw_filled_rectangle(500, 400, 565, 380, al_map_rgb(100, 100, 0));
                al_draw_text(font24, al_map_rgb(0, 0, 0), 500, 380, 0, "next");
                al_flip_display();
                done = false;
                al_draw_filled_rectangle(500, 350, 560, 370, al_map_rgb(255, 255, 0));
                al_draw_text(font24, al_map_rgb(0, 0, 0), 520, 360, 0, "OK");
                ALLEGRO_EVENT ev;
                al_wait_for_event(event_queue, &ev);
                if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                    if (ev.mouse.button & 1) {
                        pos_y = ev.mouse.y;
                        pos_x = ev.mouse.x;
                        if (pos_x < 540 && pos_x > 500 && pos_y > 400 && pos_y < 420) {
                            done = true;
                            break;
                        } else if ((pos_y - 135) / 30 >= 0 && (pos_y - 135) / 30 < 8 && (pos_x - 170) / 50 >= 0 && (pos_x - 170) / 50 < 7) {
                            k++;
                            if (k % 2 == 0) {
                                i1 = (pos_y - 135) / 30;
                                j1 = (pos_x - 170) / 50;
                            } else if (k % 2 == 1) {
                                i2 = (pos_y - 135) / 30;
                                j2 = (pos_x - 170) / 50;
                                if (is_there_any_way(i1, j1, i2, j2, count, k % 2 + 1)){
                                    sol[i1][j1]--;
                                    sol[i2][j2]++;
                                }else {
                                    al_draw_text(font24, al_map_rgb(255,255,255),30,30,0,"there isnt any way!");
                                }
                            }
                        }
                    }
                }
            }
        }
        al_draw_text(font24, al_map_rgb(255, 255, 0), 50, 50, 0, "helloo");
        al_flip_display();
        al_rest(5.0);
        al_destroy_display(display);

        return 0;
    }
