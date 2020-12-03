#include "myHeader.h"

int main()
{
    int state = 1; //�n�����񪺵{���O�_�~�����, �O:1 �_:0
    ALLEGRO_DISPLAY *display = NULL;
    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *instance = NULL;
    ALLEGRO_MIXER *mixer = NULL;
    ALLEGRO_VOICE *voice = NULL;
    ALLEGRO_MOUSE_STATE mouse;

    allegro_init(); //��l�ƩҦ��ݭn�Ψ쪺allegro�禡
    sample = al_load_sample("./music/test2.wav");//Ū���n������
    display = al_create_display(330, 60);//�Ыص���
    instance = al_create_sample_instance(sample);//�Ы��n������

    voice_init(instance, &mixer, &voice);//��l���n��������

    layout_init();//�襴�}������

    if(state == 1)
    {
        playing(&mouse, instance, &state);
    }

    //����Ҧ��ʺA�O����Ŷ�
    al_destroy_voice(voice);
    al_destroy_mixer(mixer);
    al_destroy_sample_instance(instance);
    al_destroy_sample(sample);
    al_destroy_display(display);
    return 0;
}
