#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <stdbool.h>
#include <stdio.h>
#include <allegro5/allegro_primitives.h>
#include <stdlib.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

struct player{
    int sol;                           //count of soldiers
    int count;                         //count of countries
    int id;
};

bool is_continent(int player, int number_of_country,int map[7][6], int count[7][6], int count_of_countries[4]){
    int i,j,k = 0;
    for(i=0; i<7; i++){
        for(j=0; j<6; j++){
            if(map[i][j] == number_of_country && count[7][6] == player){
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
        if(is_continent(player,i,map,count,count_of_countries) == true ){
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
    }
    if (i1 == i2){
        if (j1 - j2 == 1){
            return true;
        } else if (j2 - j1 == 1){
            return true;
        }
    }
    return false;
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

void attack( int* sol1, int* sol2 ){
    int i,count1,count2;
    if((*sol1-1)/3 >= 1){
        count1 = 3;
    }else{
        count1 = *sol1 -1;
    }
    if(*sol2 >= 2){
        count2 = 2;
    }else{
        count2 = 1;
    }
    int attack[count1], defense[count2];
    for(i=0; i<count1; ++i){
        attack[i] = rand()%6;
    }
    for(i=0; i<count2; ++i){
        defense[i] = rand()%6;
    }
    up_to_down(attack,count1);
    up_to_down(defense,count2);
    for(i = 0; i < count2; ++i){
        if(defense[i] >= attack[i]){
            *sol1--;
        }else{
            *sol2--;
        }
    }
}

bool is_there_any_way(){
    return true;
}

    int main() {
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

        for (i = 0; i < 7; i++) {
            for (j = 0; j < 6; j++) {
                sol[i][j] = 1;
            }
        }
        //writing map

        map[0][0] = 0; map[1][0] = 0; map[2][0] = 0; map[3][0] = 0; map[4][0] = 0; map[5][0] = 0; map[0][1] = 0; map[1][1] = 0; map[5][1] = 1;  // 1 means amrika
        map[0][2] = 1; map[0][3] = 1; map[1][2] = 1; map[1][3] = 1; map[2][2] = 1; map[2][3] = 1;                                  // 2 means urupa
        map[0][4] = 2; map[0][5] = 2; map[1][4] = 2; map[1][5] = 2; map[2][4] = 2; map[2][5] = 2; map[3][4] = 2; map[3][5] = 2;            // 3 means asia
        map[3][3] = 3; map[4][3] = 3; map[5][3] = 3; map[4][4] = 3; map[5][4] = 3; map[6][4] = 3;                                  // 4 means africa
        map[6][0] = 4; map[6][1] = 4; map[6][3] = 4; map[6][4] = 4; map[6][5] = 4; map[5][5] = 4; map[5][4] = 4; map[4][5] = 4; map[4][4] = 4; map[2][1] = 4; map[3][1] = 4; map[4][1] = 4; map[3][2] = 4;   // 5 means sea

        // finish writing map


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
        ALLEGRO_FONT *font24 = al_load_font("font.ttf", 24, 0);
        ALLEGRO_FONT *fontt24 = al_load_font("fontt.ttf", 24, 0);
        event_queue = al_create_event_queue();

        al_register_event_source(event_queue, al_get_display_event_source(display));
        al_register_event_source(event_queue, al_get_mouse_event_source());

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
                        done = true;
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
                } else if (player2.count < 15){
                    count[i][j] = 2;
                    player2.count++;
                }
            }
        }
        player1.sol = 15;
        player2.sol = 16;
        done = false;
        while (!done && (player1.sol > 0 && player2.sol > 0)) {

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
            al_flip_display();
            //al_clear_to_color(al_map_rgb(0, 0, 0));

            ALLEGRO_EVENT ev;
            al_wait_for_event(event_queue, &ev);

            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
                done = true;
                break;
            } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && player1.sol > 0) {
                if ((ev.mouse.button & 1) && ev.mouse.x < 540 && ev.mouse.x > 500 && ev.mouse.y > 400 &&
                    ev.mouse.y < 420) {
                    done = true;
                    break;
                } else if (ev.mouse.button & 1) {
                    pos_x = ev.mouse.x;
                    pos_y = ev.mouse.y;
                    sol[(pos_y - 135) / 30][(pos_x - 170) / 50]++;
                    player1.sol--;
                }
            }

            al_wait_for_event(event_queue, &ev);

            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE && player2.sol > 0) {
                done = true;
                break;
            } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN && player2.sol > 0) {
                if (ev.mouse.button & 1) {
                    pos_x = ev.mouse.x;
                    pos_y = ev.mouse.y;
                    sol[(pos_y - 135) / 30][(pos_x - 170) / 50]++;
                    player2.sol--;
                }
            }
        }

        al_clear_to_color(al_map_rgb(0, 0, 0));

        int k;
        while (player1.count != 29 && player2.count != 29) {
            k = 0;
            done = false;
            while (!done && k < count_of_continent(player1.id, map, count, count_of_countries) + (player1.count/3)) {
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
                al_draw_filled_rectangle(500, 400, 565, 380, al_map_rgb(100, 100, 0));
                al_draw_text(font24, al_map_rgb(0, 0, 0), 500, 380, 0, "next");
            }
            done = false;
            while (!done) {
                ALLEGRO_EVENT ev;
                al_wait_for_event(event_queue, &ev);
                if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                    if (ev.mouse.button & 1) {
                        pos_x = ev.mouse.x;
                        pos_y = ev.mouse.y;
                        if ((pos_y - 135) / 30 > 0 && (pos_y - 135) / 30 < 8 && (pos_x - 170) / 50 > 0 && (pos_x - 170) / 50 < 7) {
                            i1 = (pos_y - 135) / 30;
                            j1 = (pos_x - 170) / 50;
                            al_wait_for_event(event_queue, &ev);
                            if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                                if (ev.mouse.button & 1) {
                                    pos_x = ev.mouse.x;
                                    pos_y = ev.mouse.y;
                                    i2 = (pos_y - 135) / 30;
                                    j2 = (pos_x - 170) / 50;
                                }
                            }
                            if (is_around(i1, j1, i2, j2)) {
                                attack(&sol[i1][j1], &sol[i2][j2]);
                            } else if (pos_y < 400 && pos_y > 380 && pos_x > 500 & pos_x < 565) {
                                done = true;
                                break;
                            }
                        }
                    }
                }
            }
            done = false;
            while (!done){
                ALLEGRO_EVENT ev;
                al_wait_for_event(event_queue,&ev);
                if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                    if(ev.mouse.button & 1){
                        pos_x = ev.mouse.x;
                        pos_y = ev.mouse.y;
                        if ((pos_y - 135) / 30 > 0 && (pos_y - 135) / 30 < 8 && (pos_x - 170) / 50 > 0 && (pos_x - 170) / 50 < 7){
                            i1 = (pos_y - 135) / 30;
                            j1 =  (pos_x - 170) / 50;
                            al_wait_for_event(event_queue,&ev);
                            if(ev.mouse.button & 1){
                                pos_x = ev.mouse.x;
                                pos_y = ev.mouse.y;
                                i2 = (pos_y - 135) / 30;
                                j2 =  (pos_x - 170) / 50;
                            }
                            if(is_there_any_way()) {
                                sol[i1][j1]--;
                                sol[i2][j2]++;
                            }
                        } else if (pos_y < 400 && pos_y > 380 && pos_x > 500 & pos_x < 565) {
                            done = true;
                            break;
                        }
                    }
                }
            }
            k = 0;
            done = false;
            while (k < count_of_continent(player1.id, map, count, count_of_countries) + (player1.count/3)) {
                ALLEGRO_EVENT ev;
                al_wait_for_event(event_queue,&ev);
                if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                    if(ev.mouse.button & 1){
                        pos_x = ev.mouse.x;
                        pos_y = ev.mouse.y;
                        if((pos_y - 135) > 0 && (pos_y - 135) < 8 && (pos_x - 170) / 50 > 0 && (pos_x - 170) / 50 < 7) {
                            sol[(pos_y - 135) / 30][(pos_x - 170) / 50]++;
                            k++;
                        }else if( pos_y < 400 && pos_y > 380 && pos_x > 500 & pos_x < 565){
                            done = true;
                            break;
                        }
                    }
                }
                done = false;
                while (!done) {
                    ALLEGRO_EVENT ev;
                    al_wait_for_event(event_queue, &ev);
                    if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                        if (ev.mouse.button & 1) {
                            pos_x = ev.mouse.x;
                            pos_y = ev.mouse.y;
                            if ((pos_y - 135) / 30 > 0 && (pos_y - 135) / 30 < 8 && (pos_x - 170) / 50 > 0 &&
                                (pos_x - 170) / 50 < 7) {
                                i1 = (pos_y - 135) / 30;
                                j1 = (pos_x - 170) / 50;
                                al_wait_for_event(event_queue, &ev);
                                if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                                    if (ev.mouse.button & 1) {
                                        pos_x = ev.mouse.x;
                                        pos_y = ev.mouse.y;
                                        i2 = (pos_y - 135) / 30;
                                        j2 = (pos_x - 170) / 50;
                                    }
                                }
                                if (is_around(i1, j1, i2, j2)) {
                                    attack(sol[i1][j1], sol[i2][j2]);
                                } else if (pos_y < 400 && pos_y > 380 && pos_x > 500 & pos_x < 565) {
                                    done = true;
                                    break;
                                }
                            }
                        }
                    }
                }

                done = false;
                while (!done){
                    ALLEGRO_EVENT ev;
                    al_wait_for_event(event_queue,&ev);
                    if(ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
                        if(ev.mouse.button & 1){
                            pos_x = ev.mouse.x;
                            pos_y = ev.mouse.y;
                            if ((pos_y - 135) / 30 > 0 && (pos_y - 135) / 30 < 8 && (pos_x - 170) / 50 > 0 && (pos_x - 170) / 50 < 7){
                                i1 = (pos_y - 135) / 30;
                                j1 =  (pos_x - 170) / 50;
                                al_wait_for_event(event_queue,&ev);
                                if(ev.mouse.button & 1){
                                    pos_x = ev.mouse.x;
                                    pos_y = ev.mouse.y;
                                    i2 = (pos_y - 135) / 30;
                                    j2 =  (pos_x - 170) / 50;
                                }
                                if(is_there_any_way()) {
                                    sol[i1][j1]--;
                                    sol[i2][j2]++;
                                }
                            } else if (pos_y < 400 && pos_y > 380 && pos_x > 500 & pos_x < 565) {
                                done = true;
                                break;
                            }
                        }
                    }
                }
                    al_draw_filled_rectangle(500, 400, 565, 380, al_map_rgb(100, 100, 0));
                al_draw_text(font24, al_map_rgb(0, 0, 0), 500, 380, 0, "next");
            }
            al_flip_display();
        }

        //al_draw_textf(fontt24, al_map_rgb(250, 0, 0), 200, 200, ALLEGRO_ALIGN_CENTRE, "%i hi", player2.sol);
        al_draw_text(font24, al_map_rgb(255, 255, 0), 50, 50, 0, "helloo");
        al_flip_display();
        al_rest(5.0);
        al_destroy_display(display);

        return 0;
    }
