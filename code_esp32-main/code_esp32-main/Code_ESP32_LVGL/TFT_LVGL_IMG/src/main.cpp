#include <lvgl.h>
#include <TFT_eSPI.h>
#include <Arduino.h>

/*
  #define TFT_MISO 19
  #define TFT_MOSI 23
  #define TFT_SCLK 18
  #define TFT_CS   5  // Chip select control pin
  #define TFT_DC    17  // Data Command control pin
  #define TFT_RST   16  // Reset pin (could connect to RST pin)
  #define TOUCH_CS 4
*/

#define LVGL_TICK_PERIOD 60

// Ticker tick; /* timer for interrupt handler */
TFT_eSPI tft = TFT_eSPI(); /* TFT instance */
static lv_disp_buf_t disp_buf;
static lv_color_t buf[LV_HOR_RES_MAX * 10];

int screenWidth = 240;
int screenHeight = 320;

lv_obj_t *Today;
lv_obj_t *Tomorrow;
lv_obj_t *Future;

lv_obj_t *humid_1;
lv_obj_t *humid_2;
lv_obj_t *humid_3;

lv_obj_t *uv_1;
lv_obj_t *uv_2;
lv_obj_t *uv_3;

lv_obj_t *img_sun;
lv_obj_t *img_sun1;
LV_IMG_DECLARE(sun_lvgl);
LV_IMG_DECLARE(PSX);

#if USE_LV_LOG != 0
/* Serial debugging */
void my_print(lv_log_level_t level, const char *file, uint32_t line, const char *dsc)
{

  Serial.printf("%s@%d->%s\r\n", file, line, dsc);
  delay(100);
}
#endif


void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
bool my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);
void lv_main();
void Add_Img();

void setup()
{
  Serial.begin(9600); /* prepare for possible serial debug */

  lv_init();

#if USE_LV_LOG != 0
  lv_log_register_print_cb(my_print); /* register print function for debugging */
#endif

  tft.begin(); /* TFT init */
  tft.setRotation(2);

  uint16_t calData[5] = {336, 3440, 305, 3549, 1};
  tft.setTouch(calData);

  lv_disp_buf_init(&disp_buf, buf, NULL, LV_HOR_RES_MAX * 10);

  /*Initialize the display*/
  lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.buffer = &disp_buf;
  lv_disp_drv_register(&disp_drv);

  /*Initialize the input device driver*/
  lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);          /*Descriptor of a input device driver*/
  indev_drv.type = LV_INDEV_TYPE_POINTER; /*Touch pad is a pointer-like device*/
  indev_drv.read_cb = my_touchpad_read;   /*Set your driver function*/
  lv_indev_drv_register(&indev_drv);      /*Finally register the driver*/

  lv_main();
}

void loop()
{
  lv_task_handler();
}
void lv_main()
{
  lv_theme_t *th = lv_theme_material_init(LV_THEME_DEFAULT_COLOR_PRIMARY, LV_THEME_DEFAULT_COLOR_SECONDARY, LV_THEME_MATERIAL_FLAG_LIGHT, LV_THEME_DEFAULT_FONT_SMALL, LV_THEME_DEFAULT_FONT_NORMAL, LV_THEME_DEFAULT_FONT_SUBTITLE, LV_THEME_DEFAULT_FONT_TITLE);
  lv_theme_set_act(th);

  lv_obj_t *scr = lv_cont_create(NULL, NULL);
  lv_disp_load_scr(scr);

  Add_Img();
}

void Add_Img()
{
  img_sun1 = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(img_sun1, &sun_lvgl);

  // // Tái tạo màu sắc
  // // lv_obj_set_style_local_image_recolor(img_sun, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(255, 255, 255));
  // // lv_obj_set_style_local_image_recolor_opa(img_sun, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 255);

  lv_obj_set_size(img_sun1, 160, 160);
  lv_obj_align(img_sun1, NULL, LV_ALIGN_CENTER, 0, 0);

  // img_sun = lv_img_create(lv_scr_act(), NULL);
  // lv_img_set_src(img_sun, &PSX);

  // Tái tạo màu sắc
  // lv_obj_set_style_local_image_recolor(img_sun, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, lv_color_make(255, 255, 255));
  // lv_obj_set_style_local_image_recolor_opa(img_sun, LV_IMG_PART_MAIN, LV_STATE_DEFAULT, 255);

  // lv_obj_set_size(img_sun, 240, 320);
  // lv_obj_align(img_sun, NULL, LV_ALIGN_CENTER, 0, 0);
}


/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint16_t c;

  tft.startWrite();                                                                            /* Start new TFT transaction */
  tft.setAddrWindow(area->x1, area->y1, (area->x2 - area->x1 + 1), (area->y2 - area->y1 + 1)); /* set the working window */
  for (int y = area->y1; y <= area->y2; y++)
  {
    for (int x = area->x1; x <= area->x2; x++)
    {
      c = color_p->full;
      tft.writeColor(c, 1);
      color_p++;
    }
  }
  tft.endWrite();            /* terminate TFT transaction */
  lv_disp_flush_ready(disp); /* tell lvgl that flushing is done */
}

bool my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
  uint16_t touchX, touchY;

  bool touched = tft.getTouch(&touchX, &touchY, 600);

  if (!touched)
  {
    return false;
  }

  if (touchX > screenWidth || touchY > screenHeight)
  {
    Serial.println("Y or y outside of expected parameters..");
    Serial.print("y:");
    Serial.print(touchX);
    Serial.print(" x:");
    Serial.print(touchY);
  }
  else
  {

    data->state = touched ? LV_INDEV_STATE_PR : LV_INDEV_STATE_REL;

    /*Save the state and save the pressed coordinate*/
    // if(data->state == LV_INDEV_STATE_PR) touchpad_get_xy(&last_x, &last_y);

    /*Set the coordinates (if released use the last pressed coordinates)*/
    data->point.x = touchX;
    data->point.y = touchY;

    Serial.print("Data x");
    Serial.println(touchX);

    Serial.print("Data y");
    Serial.println(touchY);
  }

  return false; /*Return `false` because we are not buffering and no more data to read*/
}