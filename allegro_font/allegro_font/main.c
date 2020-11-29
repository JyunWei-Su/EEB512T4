#include "myheader.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#define EURO      "\xe2\x82\xac"
int main()
{
    int finish = 0;
 int ranges[] = {
    0x0020, 0x007F,  /* ASCII */
    0x00A1, 0x00FF,  /* Latin 1 */
    0x0100, 0x017F,  /* Extended-A */
    0x20AC, 0x20AC}; /* Euro */
    srand(time(0));

    ALLEGRO_EVENT_QUEUE *event_queue = NULL; //拿來存事件 #1 (目前用於視窗X叉叉)
    ALLEGRO_EVENT event; //拿來存事件 #2 (目前用於視窗X叉叉)

    ALLEGRO_DISPLAY *display = NULL;



    ALLEGRO_KEYBOARD_STATE keyboard_state;




    // Initialize Allegro
    al_init();
    al_install_keyboard();
    al_init_image_addon();
    al_init_font_addon();
    al_init_ttf_addon();

    // Create allegro display
    display = al_create_display(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    event_queue = al_create_event_queue(); // Create allegro enevt detector #1
    al_register_event_source(event_queue, al_get_display_event_source(display)); // Create allegro enevt detector #2


    ALLEGRO_BITMAP *bitmap1= al_load_bitmap("B.tga");

//Create allegro font
    ALLEGRO_FONT *font_24= al_load_font("DFT_TL9.TTC", 24, 0);
    ALLEGRO_FONT *font_48= al_load_font("DFT_TL9.TTC", 48, 0);
    ALLEGRO_FONT *font_36= al_load_font("DFT_TL9.TTC", 36, 0);
     ALLEGRO_FONT *a4f;

    al_clear_to_color(al_map_rgb(220,200,243));
    //寫字在螢幕上
    al_draw_text(font_24,al_map_rgb(255,0,255),100,100,0,"the font is 24");
    al_draw_text(font_36,al_map_rgb(255,255,0),100,200,0,"the font is 36");
    al_draw_text(font_48,al_map_rgb(100,0,100),100,300,0,"the font is 48");

    int screen_w = al_get_display_width(display);
    int screen_h = al_get_display_height(display);
//寫字在螢幕上並印出變數
    al_draw_textf(font_24,al_map_rgb(0,200,100),screen_w/2,500,ALLEGRO_ALIGN_CENTRE,
                  "TEXT with variable output:Screen width and height = %d / %d",screen_w,screen_h );

al_draw_justified_text(font_24,al_map_rgb(0,200,200), 0, 500,0, 630, 0, "al draw justified text 24 ");
// 文字不會超過x1~x2的距離(0~500)，y=0，diff=630(文字間距)
//       diff參數是單詞之間允許的最大水平空間量。如果對齊文本超過diff像素，或者字符串包含少於兩個單詞，則將字符串左對齊。
al_draw_justified_textf(font_48,al_map_rgb(0,200,200), 0, 500,700, 630, 0, "al draw justified text %d ",16888);
//al_draw_justified_text的變數版本

al_draw_bitmap(bitmap1, 500, 100, 0);
a4f = al_grab_font_from_bitmap(bitmap1, 1, ranges);
//al_draw_text(a4f, al_map_rgb(23, 29, 255), 10, 90, 0, "t");
al_shutdown_font_addon();
//al_draw_bitmap(bitmap1, 500, 100, 0);
    // Flip display to show the drawing result
    al_flip_display();

    while (finish!= 1)
    {
        al_get_keyboard_state(&keyboard_state); // Save the state of the keyboard specified at the time
        if(al_wait_for_event_timed(event_queue, &event, 0.1))
            printf("-----#####-----\n"); //偵測活動(可偵測視窗X叉叉)
        if (al_key_down(&keyboard_state, ALLEGRO_KEY_ESCAPE))
            finish = 1; // Check whether ESC was held down or not.
        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            finish = 1; //檢查-視窗X叉叉
        if (event.type == ALLEGRO_EVENT_DISPLAY_SWITCH_IN)
            al_flip_display(); //修正視窗縮小後重新開啟東西會不見
        al_rest(0.01); // Delay
    }
al_destroy_bitmap(bitmap1);

    al_destroy_display(display);

    return 0;
}


