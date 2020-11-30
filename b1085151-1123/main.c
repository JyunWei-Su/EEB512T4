#include "myheader.h"

/*
 * al_init_font_addon		初始化字型附件功能
 * al_shutdown_font_addon	關閉字型附件功能
 * al_load_font				讀入字型
 * al_destroy_font			free字型
 *
 * al_draw_text				寫字上去(一般)
 * al_draw_textf			寫字上去(可使用%d等變數)
 *
 * al_draw_justified_text	寫字上去(限位,一般)
 * al_draw_justified_textf	寫字上去(限位,可使用%d等變數)
 *
 * al_get_font_line_height	取得文字高度
 * al_get_font_ascent		取得文字實際高度
 * al_get_font_descent		取得文字行距
 * al_get_text_width		取得文字寬度
 */

/* for 中文
 * Step 1：聲明一個指向ALLEGRO_USTR類型的指針
 *         ALLEGRO_USTR *ustr;
 * Step 2：創建一個UTF-16的字符串
 *         ustr=al_ustr_new_from_utf16( (uint16_t*)L"你好!");
 * Step 3：渲染字符串
 *         al_draw_ustr(font,al_map_rgb(255,255,255),100,100,0,ustr);
 * Step 4：結束時銷燬字符串所佔用的資源
 *         al_ustr_free(ustr);
 */

int main(void)
{
    int screen_w , screen_h;
    int font_height, font_ascent, font_descent, font_width;
    ALLEGRO_USTR *ustrA = NULL; //for 中文

    ALLEGRO_DISPLAY *display = NULL; /* pointer to display */
    ALLEGRO_KEYBOARD_STATE KBstate;

    MyAlgc_init();

    display = al_create_display(SCREEN_W, SCREEN_H);
    screen_w = al_get_display_width(display);
    screen_h = al_get_display_height(display);

    /*讀入字型-不同大小要分開讀 */
    ALLEGRO_FONT *font_24= al_load_font("DFT_TL9.TTC", 24, 0);
    ALLEGRO_FONT *font_48= al_load_font("DFT_TL9.TTC", 48, 0);
    ALLEGRO_FONT *font_36= al_load_font("DFT_TL9.TTC", 36, 0);
    /*struct 用法 */
    struct stut_font{
        ALLEGRO_FONT *s24 = NULL;
        ALLEGRO_FONT *s36 = NULL;
        ALLEGRO_FONT *s48 = NULL;
    };
    struct stut_font fontA;
    fontA.s24 = al_load_font("DFT_TL9.TTC", 24, 0);
    fontA.s36 = al_load_font("DFT_TL9.TTC", 36, 0);
    fontA.s48 = al_load_font("DFT_TL9.TTC", 48, 0);

    al_clear_to_color(al_map_rgb(220,200,243));
    //寫字在螢幕上
    //void al_draw_text(*font, color, x, y, flags, *text)
    al_draw_text(font_24,al_map_rgb(255,0,255),100,100,0,"the font is 24");
    al_draw_text(font_36,al_map_rgb(255,255,0),100,200,0,"the font is 36");
    al_draw_text(font_48,al_map_rgb(100,0,100),100,300,0,"the font is 48");
    //寫字在螢幕上(_textf可使用printf語法變數)
    //void al_draw_textf(*font, color, x, y, flags, *format, ...)
    al_draw_textf(font_36, al_map_rgb(200,200,100), 640 , 350, ALLEGRO_ALIGN_RIGHT, "Hello你好");
    al_draw_textf(font_24, al_map_rgb(0,200,100), screen_w/2, screen_h/2, ALLEGRO_ALIGN_CENTER,
                  "Screen width and height = %d / %d", screen_w, screen_h );

    /* 三種對其方式 */
    //ALLEGRO_ALIGN_LEFT  =0
    //ALLEGRO_ALIGN_CENTRE
    //ALLEGRO_ALIGN_RIGHT

    //左右對其寫字方式
    //文字不會超過x1~x2的距離(0~500)，y=0，diff=630(文字間距)
    //diff參數是單字之間允許的最大水平空間量。如果對齊文本超過diff像素，或者字符串包含少於兩個單詞，則將字符串左對齊
    //void al_draw_justified_text(*font, color, x1, x2, y, diff, flags, *text)
    //void al_draw_justified_textf(*font, color, x1, x2, y, diff, flags, *format, ...)
    al_draw_justified_text(font_24, al_map_rgb(0,200,200), 0, 500, 0, 630, ALLEGRO_ALIGN_LEFT, "al draw justified text 24 ");
    al_draw_justified_textf(font_48,al_map_rgb(0,200,200), 0, 500,400, 630, ALLEGRO_ALIGN_LEFT, "al draw justified text %d ",168);


    //顯示中文的方法
    ustrA = al_ustr_new_from_utf16 ( (uint16_t*)L"你好!");
    al_draw_ustr(fontA.s48, al_map_rgb(255,255,255), 300, 100, ALLEGRO_ALIGN_LEFT, ustrA);
    /*
    X------------------------
        /\           |      |
       /  \          |      |
      /____\         ascent |
     /      \        |      |
    /        \       |      height
    ---------------- |      |
                     |      |
                     descent|
                     |      |
    -------------------------
    */

    /*取各種高度*/
    font_height = al_get_font_line_height(font_24);
    font_ascent = al_get_font_ascent(font_24);
    font_descent = al_get_font_descent(font_24);
    printf("The Font:\n\theight:%d\n\tascent:%d\n\tdescent%d\n", font_height, font_ascent, font_descent);

    /*取得文字寬度*/
    font_width =  al_get_text_width(font_24, "the font is 24");
    printf("The text [the font is 24] 's width: %d\n", font_width);



    al_flip_display();// Flip display to show the drawing result
    MyAlgc_waitToClose(KBstate);

    al_shutdown_font_addon();
    al_destroy_display(display);
    al_destroy_font(font_24);
    al_destroy_font(font_36);
    al_destroy_font(font_48);
    al_destroy_font(fontA.s24);
    al_destroy_font(fontA.s36);
    al_destroy_font(fontA.s48);
    al_ustr_free(ustrA);
    return 0;
}


