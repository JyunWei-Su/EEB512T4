
# 參考資料

## 偵測視窗的叉叉"X" 並關掉程式(event)參考：
 * https://stackoverflow.com/questions/36342997/allegro5-window-wont-close
 * https://www.aprendendoallegro.tk/eventos.php
 * https://www.allegro.cc/manual/5/al_wait_for_event_timed

## 字體來源
 * https://www.kfstudio.net/font/kfhimajiface/
 * https://nonty.net/font/freefont/fancy-heart/

## 圖片
 * https://www.flaticon.com/free-icon/home_1057118?related_item_id=1057118&term=home
 * https://www.flaticon.com/free-icon/dollar_550638?term=coin&page=1&position=2&related_item_id=550638

## printf詳細應用
 * https://www.itdaan.com/tw/e932594201ca64b7c99341b294af43e9

# 遊戲架構
 > main()  CheckEvent()
 >> ALLEGRO_EVENT_DISPLAY_CLOSE
 >>> CheckWantToFinish()

 >> ALLEGRO_EVENT_MENU_CLICK
 >> ALLEGRO_EVENT_MOUSE_AXES
 >>> RecordMouse()
 >>> CheckMouseMove()

 >> ALLEGRO_EVENT_MOUSE_BUTTON_DOWN
 >>> CheckMouseClick()

 >> ALLEGRO_EVENT_MOUSE_BUTTON_UP:
 >>> CheckMouseClick()

 >> ALLEGRO_EVENT_KEY_DOWN:
 >>> CheckKeyboardDown()

 >> ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
 >>> al_flip_display();

 >> ALLEGRO_EVENT_TIMER
 >>> PlaySoundEffect(mainData, allegroObj);
 >>> ParameterOperate(mainData, allegroObj);
 >>> DrawDisplayAndFlip(mainData, allegroObj);

