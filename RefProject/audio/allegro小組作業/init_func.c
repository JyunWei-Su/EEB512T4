#include "myHeader.h"

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
    //�Ы��n����Xbuffer
    *mixer = al_create_mixer(al_get_sample_instance_frequency(instance), al_get_sample_instance_depth(instance), al_get_sample_instance_channels(instance));
    //�Ы��n����X�s���f
    *voice = al_create_voice(al_get_sample_instance_frequency(instance), al_get_sample_instance_depth(instance), al_get_sample_instance_channels(instance));
    al_attach_sample_instance_to_mixer(instance, *mixer);//�N�n������link buffer
    al_attach_mixer_to_voice(*mixer, *voice);//�Nbuffer link ��X�s���f
}

void layout_init()
{
    ALLEGRO_BITMAP *enlarge = NULL, *narrow = NULL, *stop = NULL, *frame = NULL, *pause = NULL, *cross = NULL;

    //�ɤJ�Ϥ�
    enlarge = al_load_bitmap("./pic/enlarge.png");
    narrow = al_load_bitmap("./pic/narrow.png");
    stop = al_load_bitmap("./pic/stop.png");
    frame = al_load_bitmap("./pic/frame.png");
    pause = al_load_bitmap("./pic/pause.png");
    cross = al_load_bitmap("./pic/cross.png");

    //�N�Ϥ��ɤJbuffer
    al_draw_bitmap(frame, 0, 0, 0);
    al_draw_bitmap(pause, 20, 5, 0);
    al_draw_bitmap(stop, 80, 5, 0);
    al_draw_bitmap(enlarge, 140, 5, 0);
    al_draw_bitmap(narrow, 200, 5, 0);
    al_draw_bitmap(cross, 260, 5, 0);

    //��ܹϤ�
    al_flip_display();

    //���񤣻ݭn���ʺA�O����Ŷ�
    al_destroy_bitmap(enlarge);
    al_destroy_bitmap(narrow);
    al_destroy_bitmap(stop);
    al_destroy_bitmap(frame);
    al_destroy_bitmap(pause);
    al_destroy_bitmap(cross);
}

void playing(ALLEGRO_MOUSE_STATE *mouse, ALLEGRO_SAMPLE_INSTANCE *instance, int *state)
{
    //play_state��ܭ��֬O�_�b���񪬺A, pause_state��ܬO�_�O�Ȱ�, �O:1 �_:0
    int play_state = 1, pause_state = 0;
    float gain = 0.5;
    unsigned int position; //�ثe�n������쪺�ɶ��I
    ALLEGRO_BITMAP *play = NULL, *frame = NULL, *pause = NULL;

    //�ɤJ�Ϥ�
    play = al_load_bitmap("./pic/play.png");
    frame = al_load_bitmap("./pic/frame.png");
    pause = al_load_bitmap("./pic/pause.png");

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
            if(mouse->x >= 20 && mouse->x <= 70 && mouse->y >= 5 && mouse->y <=55)
            {
                if(play_state == 1)
                {
                    if(pause_state == 1)
                    {
                        //play���s�ܦ�pause���s�ñq�W������쪺�ɶ��I����
                        al_draw_bitmap_region(frame, 20, 5, 50, 50, 20, 5, 0);
                        al_draw_bitmap(pause, 20, 5, 0);
                        pause_state = 0;
                        al_set_sample_instance_position(instance, position);//�]�w�n�����񪺮ɶ��I
                        al_set_sample_instance_playing(instance, true);
                    }
                    else
                    {
                        //pause���s�ܦ�play���s���x�s�ثe����쪺�ɶ��I
                        al_draw_bitmap_region(frame, 20, 5, 50, 50, 20, 5, 0);
                        al_draw_bitmap(play, 20, 5, 0);
                        pause_state = 1;
                        play_state = 1;
                        position = al_get_sample_instance_position(instance);//�o���n���ثe����쪺�ɶ��I
                        al_set_sample_instance_playing(instance, false);
                    }
                }
                else
                {
                    //play���s�ܦ�pause���s�ñq�Y����
                    al_draw_bitmap_region(frame, 20, 5, 50, 50, 20, 5, 0);
                    al_draw_bitmap(pause, 20, 5, 0);
                    pause_state = 0;
                    play_state = 1;
                    al_set_sample_instance_playing(instance, true);
                }
            }
            else if(mouse->x >= 80 && mouse->x <= 130 && mouse->y >= 5 && mouse->y <=55)
            {
                if(play_state == 1)
                {
                     //pause���s�ܦ�play���s�ð����n������
                    al_draw_bitmap_region(frame, 20, 5, 50, 50, 20, 5, 0);
                    al_draw_bitmap(play, 20, 5, 0);
                    pause_state = 0;
                    play_state = 0;
                    al_set_sample_instance_playing(instance, false);
                }
            }
            else if(mouse->x >= 140 && mouse->x <= 190 && mouse->y >= 5 && mouse->y <=55)
            {
                //�N�n���W�[��l�n����0.05��
                gain = gain + 0.05;
                al_set_sample_instance_gain(instance, gain);
            }
            else if(mouse->x >= 200 && mouse->x <= 250 && mouse->y >= 5 && mouse->y <=55)
            {
                //�N�n����֭�l�n����0.05��
                if(gain >= 0) //�n���j�p���|�p��0
                {
                    gain = gain - 0.05;
                }
                al_set_sample_instance_gain(instance, gain);
            }
            else if(mouse->x >= 260 && mouse->x <= 310 && mouse->y >= 5 && mouse->y <=55)
            {
                //�{����������
                *state = 0;
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
    al_destroy_bitmap(play);
    al_destroy_bitmap(frame);
    al_destroy_bitmap(pause);
}
