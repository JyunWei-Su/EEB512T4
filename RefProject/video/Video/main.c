#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_video.h>

int main()
{
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_VIDEO *video = NULL;
    ALLEGRO_KEYBOARD_STATE keyboard_state;
    ALLEGRO_KEYBOARD_STATE keyboard_state1;

    int play=0 ;


    al_init();
    al_install_audio();
    al_init_video_addon();
    al_install_keyboard();


    display = al_create_display(1000, 800);  // �]�w�����j�p
    al_reserve_samples(0); //�гymixer

    video = al_open_video("test_video.ogv");  // Ū���v���ɮ�
    if(video == NULL)
    {
        printf("Video open error\n");
        abort();
    }

    al_start_video(video, al_get_default_mixer()) ; // �}�l����v��


    while(al_is_video_playing(video))  //��v�����b����ɰ���H�U���F��
    {


        ALLEGRO_BITMAP* frame = al_get_video_frame(video);  // �N�v����e���v����X

        if(frame != NULL)
        {
            float scale = 1.0;  //�]�w�Y����
            float sw = al_get_bitmap_width(frame);  //source width
            float sh = al_get_bitmap_height(frame);  //source height
            float dw = scale * al_get_video_scaled_width(video);  //destination width
            float dh = scale * al_get_video_scaled_height(video);  //destination height
            al_draw_scaled_bitmap(frame, 0, 0, sw, sh, 0, 0, dw, dh, 0);
            //(ALLEGRO_BITMAP *bitmap, float sx, float sy, float sw, float sh,float dx, float dy, float dw, float dh, int flags)
        }
        al_flip_display();  //��ܦb�e���W
        //al_rest(1.0 / 60.0);

        al_get_keyboard_state(&keyboard_state);

        // Check whether ESC was held down or not.
        while (al_key_down(&keyboard_state, ALLEGRO_KEY_ESCAPE)&&play==0)
        {
            al_set_video_playing(video,0) ;
            al_get_keyboard_state(&keyboard_state1);
            if(al_key_down(&keyboard_state1, ALLEGRO_KEY_ENTER))
            {
                play=play+1 ;
                al_set_video_playing(video,1) ;
            }
        }


        al_rest(0.01);
        play=0 ;
    }

    //al_rest(10);
    al_close_video(video);
    al_destroy_display(display);

    system("pause");

    return 0;
}

