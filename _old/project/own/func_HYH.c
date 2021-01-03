#include "../own/header_HYH.h"
#include "../defineHeader.h"

void allegro_init()
{
    al_init();
    al_init_image_addon();
    al_install_audio();
    al_init_acodec_addon();
    al_install_mouse();
    al_reserve_samples(2);//�w�w�n�����󪺪Ŷ�
}

void voice_init(ALLEGRO_SAMPLE_INSTANCE *instance, ALLEGRO_MIXER **mixer, ALLEGRO_VOICE **voice)
{
    //init all voice value(mixer�Avoice)
    *mixer = al_create_mixer(al_get_sample_instance_frequency(instance), al_get_sample_instance_depth(instance), al_get_sample_instance_channels(instance));
    *voice = al_create_voice(al_get_sample_instance_frequency(instance), al_get_sample_instance_depth(instance), al_get_sample_instance_channels(instance));
    al_attach_sample_instance_to_mixer(instance, *mixer);
    al_attach_mixer_to_voice(*mixer, *voice);
}

void playing(ALLEGRO_MOUSE_STATE *mouse, ALLEGRO_SAMPLE_INSTANCE *instance, int *state){
    //play_state��ܭ��֬O�_�b���񪬺A, pause_state��ܬO�_�O�Ȱ�, �O:1 �_:0
    int play_state = 1, pause_state = 0;
    float gain = 0.5; //�W�q(��ȳ]0.5)
    unsigned int position; //�n������쪺��m
    ALLEGRO_BITMAP *loudspeaker = NULL, *background= NULL, *nosound = NULL;

    //�ɤJ�Ϥ�
    loudspeaker = al_load_bitmap("./img/music_icon/loudspeaker.jpg");
    background = al_load_bitmap("./img/back900.png");
    nosound = al_load_bitmap("./img/music_icon/nosound.jpg");

    //�]�w�n����l���A
    al_set_sample_instance_gain(instance, gain);//�]�w�n�����񪺤j�p
    al_set_sample_instance_playmode(instance, ALLEGRO_PLAYMODE_LOOP);//�]�w�n�����񪺼Ҧ�(��@, �`��, ���V?)
    al_set_sample_instance_playing(instance, true);//�]�w�n�����񪺪��A(play or not)
    while(*state == 1)
    {
        al_get_mouse_state(mouse); //�����ƹ��ثe�����A
        if(mouse->buttons & 1) //�����ƹ�����
        {
            //����play��pause�Ϥ�����m
            if(mouse->x >= DISPLAY_WIDTH-150 && mouse->x <= DISPLAY_WIDTH-110 && mouse->y >= DISPLAY_HEIGHT-50 && mouse->y <=DISPLAY_HEIGHT-10)
            {
                if(play_state == 1)
                {
                    if(pause_state == 1)
                    {
                        //play���s�ܦ�pause���s�ñq�W������쪺�ɶ��I����
                        al_draw_bitmap_region(background, DISPLAY_WIDTH-150, DISPLAY_HEIGHT-50, 40, 40, DISPLAY_WIDTH-150, DISPLAY_HEIGHT-50, 0);
                        al_draw_bitmap(loudspeaker, DISPLAY_WIDTH-150, DISPLAY_HEIGHT-50, 0);
                        pause_state = 0;
                        al_set_sample_instance_position(instance, position);//�]�w�n�����񪺮ɶ��I
                        al_set_sample_instance_playing(instance, true);
                    }
                    else
                    {
                        //pause���s�ܦ�play���s���x�s�ثe����쪺�ɶ��I
                        al_draw_bitmap_region(background, DISPLAY_WIDTH-150, DISPLAY_HEIGHT-50, 40, 40, DISPLAY_WIDTH-150, DISPLAY_HEIGHT-50, 0);
                        al_draw_bitmap(nosound,DISPLAY_WIDTH-150, DISPLAY_HEIGHT-50, 0);
                        pause_state = 1;
                        play_state = 1;
                        position = al_get_sample_instance_position(instance);//�o���n���ثe����쪺�ɶ��I
                        al_set_sample_instance_playing(instance, false);
                    }
                }
                    else
                   {
                    //play���s�ܦ�pause���s�ñq�Y����
                    al_draw_bitmap_region(background, DISPLAY_WIDTH-150, DISPLAY_HEIGHT-50, 40, 40, DISPLAY_WIDTH-150, DISPLAY_HEIGHT-50, 0);
                    al_draw_bitmap(loudspeaker,DISPLAY_WIDTH-150, DISPLAY_HEIGHT-50, 0);
                    pause_state = 0;
                    play_state = 1;
                    al_set_sample_instance_playing(instance, true);
                   }
            }
            else if(mouse->x >= DISPLAY_WIDTH-100 && mouse->x <= DISPLAY_WIDTH-60 && mouse->y >= DISPLAY_HEIGHT-50 && mouse->y <=DISPLAY_HEIGHT-10)
            {
                //�N�n���W�[��l�n����0.1��
                gain = gain + 0.1;
                al_set_sample_instance_gain(instance, gain);
            }
            else if(mouse->x >= DISPLAY_WIDTH-50 && mouse->x <=DISPLAY_WIDTH-10 && mouse->y >= DISPLAY_HEIGHT-50 && mouse->y <=DISPLAY_HEIGHT-10)
            {
                //�N�n����֭�l�n����0.1��
                if(gain >= 0) //�n���j�p���|�p��0
                {
                    gain = gain - 0.1;
                }
                al_set_sample_instance_gain(instance, gain);
            }
            //�L�X�{�b�ƹ��Ҧb����m
            printf("mouse_position(%d, %d)\n", mouse->x, mouse->y);
        }
        //��ܹϤ�
        al_flip_display();
        //�{���Ȱ�0.1��
        al_rest(0.1);
    }

    //���񤣻ݭn���ʺA�O����Ŷ�
    al_destroy_bitmap(loudspeaker);
    al_destroy_bitmap(background);
    al_destroy_bitmap(nosound);
}
