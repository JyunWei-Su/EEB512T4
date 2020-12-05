#include <stdio.h>
#include <stdlib.h>

#include <allegro5/allegro.h>

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_video.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

void video_display(ALLEGRO_VIDEO *video, ALLEGRO_DISPLAY *screen)
{

    double p;
    ALLEGRO_COLOR bc = al_map_rgba_f(0.5, 0.5, 0.5, 0.5);
   ALLEGRO_BITMAP *frame = al_get_video_frame(video);

   if (!frame)
      return;

   /* Show some video information. */
   al_draw_filled_rounded_rectangle(4, 4,
      al_get_display_width(screen) - 4, 4 + 14 * 4, 8, 8, bc);
   p = al_get_video_position(video, ALLEGRO_VIDEO_POSITION_ACTUAL);
   al_flip_display();
   al_clear_to_color(al_map_rgb(0, 0, 0));
}

    /*
    for (;;) {
      double incr;

      if (redraw && al_event_queue_is_empty(queue)) {
         video_display(video, display);
         redraw = false;
      }

      al_wait_for_event(queue, &event);
      switch (event.type) {
         case ALLEGRO_EVENT_KEY_DOWN:
            switch (event.keyboard.keycode) {
               case ALLEGRO_KEY_SPACE:
                  al_set_video_playing(video, !al_is_video_playing(video));
                  break;
               case ALLEGRO_KEY_ESCAPE:
                  al_close_video(video);
                  al_destroy_display(display);
                  break;
               case ALLEGRO_KEY_LEFT:
                  incr = -10.0;
                  goto do_seek;
               case ALLEGRO_KEY_RIGHT:
                  incr = 10.0;
                  goto do_seek;
               case ALLEGRO_KEY_UP:
                  incr = 60.0;
                  goto do_seek;
               case ALLEGRO_KEY_DOWN:
                  incr = -60.0;
                  goto do_seek;

               do_seek:
                  al_seek_video(video, al_get_video_position(video, ALLEGRO_VIDEO_POSITION_ACTUAL) + incr);
                  break;

               default:
                  break;
            }
            break;

         case ALLEGRO_EVENT_TIMER:
            /*
            display_time += 1.0 / 60;
            if (display_time >= video_time) {
               video_time = display_time + video_refresh_timer(is);
            }

         case ALLEGRO_EVENT_DISPLAY_CLOSE:
            al_close_video(video);
            al_destroy_display(display);
            break;


         case ALLEGRO_EVENT_VIDEO_FINISHED:
            printf("video finished\n");
            break;
         default:
            break;
      }
   }*/
