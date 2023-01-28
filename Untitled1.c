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
};

int main(){
    struct player player1, player2, player3, player4;
    int width = 640;
    int height = 480;
    int pos_x, pos_y;
    int sol[7][6], i, j;
    bool done = false;

    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;
    ALLEGRO_FONT* font24 = al_load_font("font.ttf", 24, 0);

    if(!al_init()) {
        return -1;
    }

    display = al_create_display(width,height);
    event_queue = al_create_event_queue();

    if(!display) {
        return -1;
    }

    al_init_primitives_addon();
    al_install_mouse();
    al_init_font_addon();
    al_init_ttf_addon();

    event_queue = al_create_event_queue();

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_mouse_event_source());

    for (i = 0; i < 7; i++) {
        for (j = 0; j < 6; j++) {
            if (rand() % 2 == 0 && player1.count < 16) {
                sol[i][j] = 1;
                player1.count++;
            } else if (rand() % 2 == 1 && player2.count < 15) {
                sol[i][j] = 2;
                player2.count++;
            } else if (player1.count < 16) {
                sol[i][j] = 1;
                player1.count++;
            } else if (player2.count < 15) {
                sol[i][j] = 2;
                player2.count++;
            }
        }
    }
    player1.sol=15;
    player2.sol=16;

    al_draw_text(font24, al_map_rgb(255,255,0),50,50,0,"helloo");
    al_flip_display();
    al_rest(5.0);
    al_destroy_display(display);

    return 0;
}
