#include <pebble.h>
#include <time.h>


#define DEBUG false
#define TILE_SIZE 10
const unsigned char LINE[] = {0, 0, 1, 1, 1, 1, 1, 0, 0, 0};
#define FONT font_thin
  
#define KEY_COLOR1 0
#define COLOR1_KEY 1
#define KEY_COLOR2 2
#define COLOR2_KEY 3

// distance on left and right of text
#define PADDING_X 2
#define PADDING_Y 1

// distance between characters
#define SPACING_X 1
#define SPACING_Y 2

size_t LINE_N = sizeof LINE / sizeof *LINE;

GColor g_Color1;

GColor g_Color2;

unsigned char font_thick[][5][3] =  {{
  {1, 1, 1},
  {1, 0, 1},
  {1, 0, 1},
  {1, 0, 1},
  {1, 1, 1}
}, {
  {1, 1, 0},
  {0, 1, 0},
  {0, 1, 0},
  {0, 1, 0},
  {1, 1, 1}
}, {
  {1, 1, 1},
  {0, 0, 1},
  {1, 1, 1},
  {1, 0, 0},
  {1, 1, 1}
}, {
  {1, 1, 1},
  {0, 0, 1},
  {1, 1, 1},
  {0, 0, 1},
  {1, 1, 1}
}, {
  {1, 0, 1},
  {1, 0, 1},
  {1, 1, 1},
  {0, 0, 1},
  {0, 0, 1}
}, {
  {1, 1, 1},
  {1, 0, 0},
  {1, 1, 1},
  {0, 0, 1},
  {1, 1, 1}
}, {
  {1, 1, 1},
  {1, 0, 0},
  {1, 1, 1},
  {1, 0, 1},
  {1, 1, 1}
}, {
  {1, 1, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1},
  {0, 0, 1}
}, {
  {1, 1, 1},
  {1, 0, 1},
  {1, 1, 1},
  {1, 0, 1},
  {1, 1, 1}
}, {
  {1, 1, 1},
  {1, 0, 1},
  {1, 1, 1},
  {0, 0, 1},
  {1, 1, 1}
}};

unsigned char font_thin[][7][5] =  {{
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 1}
}, {
  {0, 1, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 0, 1, 0, 0},
  {0, 1, 1, 1, 0}
}, {
  {1, 1, 1, 1, 1},
  {0, 0, 0, 0, 1},
  {0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0},
  {1, 1, 1, 1, 1}
}, {
  {1, 1, 1, 1, 1},
  {0, 0, 0, 0, 1},
  {0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1},
  {0, 0, 0, 0, 1},
  {0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1}
}, {
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 1},
  {0, 0, 0, 0, 1},
  {0, 0, 0, 0, 1},
  {0, 0, 0, 0, 1}
}, {
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0},
  {1, 1, 1, 1, 1},
  {0, 0, 0, 0, 1},
  {0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1}
}, {
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 0},
  {1, 0, 0, 0, 0},
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 1}
}, {
  {1, 1, 1, 1, 1},
  {0, 0, 0, 0, 1},
  {0, 0, 0, 0, 1},
  {0, 0, 0, 0, 1},
  {0, 0, 0, 0, 1},
  {0, 0, 0, 0, 1},
  {0, 0, 0, 0, 1}
}, {
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 1}
}, {
  {1, 1, 1, 1, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 1, 1, 1, 1},
  {0, 0, 0, 0, 1},
  {0, 0, 0, 0, 1},
  {1, 1, 1, 1, 1}
}};

#define FONT_HEIGHT (sizeof *FONT / sizeof **FONT)
#define FONT_WIDTH (sizeof **FONT)

#define SCREEN_WIDTH 144
#define SCREEN_HEIGHT 168

#define TILES_X ( \
  PADDING_X + FONT_WIDTH + SPACING_X + FONT_WIDTH + PADDING_X)
#define TILES_Y ( \
  PADDING_Y + FONT_HEIGHT + SPACING_Y + FONT_HEIGHT + PADDING_Y)

#define ORIGIN_X ((SCREEN_WIDTH - TILES_X*TILE_SIZE)/2)
#define ORIGIN_Y ((SCREEN_HEIGHT - TILES_Y*TILE_SIZE)/2)

unsigned char frames[2][TILES_X][TILES_Y];
size_t current_frame = 0;
size_t prev_frame = 1;

unsigned short get_display_hour(unsigned short hour) {
  if (clock_is_24h_style()) {
    return hour;
  }
  unsigned short display_hour = hour % 12;
  return display_hour ? display_hour : 12;
}

#define OFFSET 0
unsigned char get_pixel(size_t i, size_t j, bool fg) {
  int fgf = fg ? 1 : -1;
  size_t x = ((i + j*fgf + TILE_SIZE + OFFSET)%TILE_SIZE) * LINE_N/TILE_SIZE;
  return LINE[x % LINE_N];
};

// TODO: Do the work to generate the bitmap only once, then use
// graphics_draw_bitmap_in_rect? It's probably faster.
#define REVERSE_STROKE false
void draw_tile(GContext* ctx, size_t x, size_t y, bool fg) {
  
    if (persist_exists(COLOR1_KEY)) 
{
  char colorname[20];
  persist_read_string(COLOR1_KEY, colorname, sizeof(colorname));
  if(strcmp(colorname, "1") == 0){g_Color1 = GColorPictonBlue;}
      else if(strcmp(colorname, "2") == 0){g_Color1 = GColorDukeBlue;}
      else if(strcmp(colorname, "3") == 0){g_Color1 = GColorOxfordBlue;}
      else if(strcmp(colorname, "4") == 0){g_Color1 = GColorWhite;}
      else if(strcmp(colorname, "5") == 0){g_Color1 = GColorLightGray;}
      else if(strcmp(colorname, "6") == 0){g_Color1 = GColorBlack;}
      else if(strcmp(colorname, "7") == 0){g_Color1 = GColorYellow;}
      else if(strcmp(colorname, "8") == 0){g_Color1 = GColorChromeYellow;}
      else if(strcmp(colorname, "9") == 0){g_Color1 = GColorRed;}
      else if(strcmp(colorname, "10") == 0){g_Color1 = GColorDarkCandyAppleRed;}
      else if(strcmp(colorname, "11") == 0){g_Color1 = GColorBrightGreen;}
      else if(strcmp(colorname, "12") == 0){g_Color1 = GColorGreen;}
      else if(strcmp(colorname, "13") == 0){g_Color1 = GColorIslamicGreen;}
      else if(strcmp(colorname, "14") == 0){g_Color1 = GColorVividViolet;}
      else if(strcmp(colorname, "15") == 0){g_Color1 = GColorPurple;}
      else if(strcmp(colorname, "16") == 0){g_Color1 = GColorImperialPurple;}

      else {g_Color1 = GColorPictonBlue;}
  }else {g_Color1 = GColorPictonBlue;}
  
    if (persist_exists(COLOR2_KEY)) 
{
  char colorname[20];
  persist_read_string(COLOR2_KEY, colorname, sizeof(colorname));
  if(strcmp(colorname, "1") == 0){g_Color2 = GColorPictonBlue;}
      else if(strcmp(colorname, "2") == 0){g_Color2 = GColorDukeBlue;}
      else if(strcmp(colorname, "3") == 0){g_Color2 = GColorOxfordBlue;}
      else if(strcmp(colorname, "4") == 0){g_Color2 = GColorWhite;}
      else if(strcmp(colorname, "5") == 0){g_Color2 = GColorLightGray;}
      else if(strcmp(colorname, "6") == 0){g_Color2 = GColorBlack;}
      else if(strcmp(colorname, "7") == 0){g_Color2 = GColorYellow;}
      else if(strcmp(colorname, "8") == 0){g_Color2 = GColorChromeYellow;}
      else if(strcmp(colorname, "9") == 0){g_Color2 = GColorRed;}
      else if(strcmp(colorname, "10") == 0){g_Color2 = GColorDarkCandyAppleRed;}
      else if(strcmp(colorname, "11") == 0){g_Color2 = GColorBrightGreen;}
      else if(strcmp(colorname, "12") == 0){g_Color2 = GColorGreen;}
      else if(strcmp(colorname, "13") == 0){g_Color2 = GColorIslamicGreen;}
      else if(strcmp(colorname, "14") == 0){g_Color2 = GColorVividViolet;}
      else if(strcmp(colorname, "15") == 0){g_Color2 = GColorPurple;}
      else if(strcmp(colorname, "16") == 0){g_Color2 = GColorImperialPurple;}

      else {g_Color2 = GColorBlack;}
  }else {g_Color2 = GColorBlack;}
  
  for (size_t j = 0; j < TILE_SIZE; j++) {
    for (size_t i = 0; i < TILE_SIZE; i++) {
      if (get_pixel(i, j, fg)) {
        graphics_context_set_stroke_color(ctx, g_Color1);//Color1 kirk
      } else {
        graphics_context_set_stroke_color(ctx, g_Color2);//Color2
      }

      graphics_draw_pixel(ctx, GPoint(
        ORIGIN_X + x*TILE_SIZE + i,
        ORIGIN_Y + y*TILE_SIZE + j));
    }
  }
};

size_t DIGIT_X[] = {PADDING_X, PADDING_X + FONT_WIDTH+SPACING_X};
size_t DIGIT_Y[] = {PADDING_Y, PADDING_Y + FONT_HEIGHT+SPACING_Y};

void draw_digit(unsigned short d, size_t x, size_t y) {
  for (size_t j = 0; j < FONT_HEIGHT; j++) {
    for (size_t i = 0; i < FONT_WIDTH; i++) {
      frames[current_frame][DIGIT_X[x]+i][DIGIT_Y[y]+j] = FONT[d][j][i];
    }
  }
}

void draw_rect(size_t x1, size_t y1, size_t x2, size_t y2, unsigned char v) {
  for (size_t y = y1; y < y2; y++) {
    for (size_t x = 0; x < x2; x++) {
      frames[current_frame][x][y] = v;
    }
  }
}

void swap(size_t* a, size_t* b) {
  size_t temp = *a;
  *a = *b;
  *b = temp;
}

void display_layer_update_cb(Layer *me, GContext* ctx) {
  time_t now = time(NULL);
  struct tm *t = localtime(&now);

  unsigned short display_hour = get_display_hour(t->tm_hour);
  unsigned short display_min = t->tm_min;
  unsigned short display_sec = t->tm_sec;

  unsigned short row1, row2;
  if (DEBUG) {
    row1 = display_min;
    row2 = display_sec;
  } else {
    row1 = display_hour;
    row2 = display_min;
  }

  draw_rect(0, 0, TILES_X, TILES_Y, 0);
  draw_digit(row1/10, 0, 0);
  draw_digit(row1%10, 1, 0);
  draw_digit(row2/10, 0, 1);
  draw_digit(row2%10, 1, 1);

  // now redraw tiles that have changed
  for (size_t j = 0; j < TILES_Y; j++) {
    for (size_t i = 0; i < TILES_X; i++) {
      unsigned char v = frames[current_frame][i][j];
      // TODO: make this only redraw when tiles have changed. At the moment,
      // I am marking the entire display_layer as dirty which seems to mean
      // I have to repaint the whole thing. Probably what I want is is separate
      // layer for each tile?

      // if (v != frames[prev_frame][i][j]) {
        draw_tile(ctx, i, j, v == 1);
        frames[prev_frame][i][j] = v;
      // }
    }
  }

  swap(&current_frame, &prev_frame);
}

Window* window;
Layer* display_layer;

static void handle_minute_tick(struct tm *tick_time, TimeUnits units_changed) {
  // APP_LOG(APP_LOG_LEVEL_DEBUG, "Time flies!");
  layer_mark_dirty(display_layer);
}

static void in_recv_handler(DictionaryIterator *iterator, void *context)
{
  //Get Tuple
  Tuple *t = dict_read_first(iterator);
  
  // For all items
  while(t != NULL) {
    // Which key was received?
    switch(t->key) {
    case KEY_COLOR1:
       //It's the KEY_COLOR key
      if(strcmp(t->value->cstring, "1") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorPictonBlue;
        persist_write_string(COLOR1_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "2") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorDukeBlue;
        
        persist_write_string(COLOR1_KEY, t->value->cstring);

      }     
      else if(strcmp(t->value->cstring, "3") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorOxfordBlue;
        
        persist_write_string(COLOR1_KEY, t->value->cstring);

      }    
     else if(strcmp(t->value->cstring, "4") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorWhite;
        
        persist_write_string(COLOR1_KEY, t->value->cstring);

      }     
      else if(strcmp(t->value->cstring, "5") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorLightGray;
        
        persist_write_string(COLOR1_KEY, t->value->cstring);

      }   
      else if(strcmp(t->value->cstring, "6") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorBlack;
        
        persist_write_string(COLOR1_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "7") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorYellow;
        
        persist_write_string(COLOR1_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "8") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorChromeYellow;
        
        persist_write_string(COLOR1_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "9") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorRed;

        persist_write_string(COLOR1_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "10") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorDarkCandyAppleRed;

        persist_write_string(COLOR1_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "11") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorBrightGreen;

        persist_write_string(COLOR1_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "12") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorGreen;

        persist_write_string(COLOR1_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "13") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorIslamicGreen;

        persist_write_string(COLOR1_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "14") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorVividViolet;

        persist_write_string(COLOR1_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "15") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorPurple;

        persist_write_string(COLOR1_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "16") == 0)
      {
        //Set and save the color 
        g_Color1 = GColorImperialPurple;

        persist_write_string(COLOR1_KEY, t->value->cstring);
      }
      else {g_Color1 = GColorPictonBlue;persist_write_string(COLOR1_KEY, t->value->cstring);}
      break;
      case KEY_COLOR2:
       //It's the KEY_COLOR key
      if(strcmp(t->value->cstring, "1") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorPictonBlue;
        persist_write_string(COLOR2_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "2") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorDukeBlue;
        
        persist_write_string(COLOR2_KEY, t->value->cstring);

      }     
      else if(strcmp(t->value->cstring, "3") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorOxfordBlue;
        
        persist_write_string(COLOR2_KEY, t->value->cstring);

      }    
     else if(strcmp(t->value->cstring, "4") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorWhite;
        
        persist_write_string(COLOR2_KEY, t->value->cstring);

      }     
      else if(strcmp(t->value->cstring, "5") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorLightGray;
        
        persist_write_string(COLOR2_KEY, t->value->cstring);

      }   
      else if(strcmp(t->value->cstring, "6") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorBlack;
        
        persist_write_string(COLOR2_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "7") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorYellow;
        
        persist_write_string(COLOR2_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "8") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorChromeYellow;
        
        persist_write_string(COLOR2_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "9") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorRed;

        persist_write_string(COLOR2_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "10") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorDarkCandyAppleRed;

        persist_write_string(COLOR2_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "11") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorBrightGreen;

        persist_write_string(COLOR2_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "12") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorGreen;

        persist_write_string(COLOR2_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "13") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorIslamicGreen;

        persist_write_string(COLOR2_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "14") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorVividViolet;

        persist_write_string(COLOR2_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "15") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorPurple;

        persist_write_string(COLOR2_KEY, t->value->cstring);

      }
      else if(strcmp(t->value->cstring, "16") == 0)
      {
        //Set and save the color 
        g_Color2 = GColorImperialPurple;

        persist_write_string(COLOR2_KEY, t->value->cstring);
      }
      else {g_Color2 = GColorPictonBlue;persist_write_string(COLOR2_KEY, t->value->cstring);}
      break;
          default:
      break;
    }
        // Look for next item
    t = dict_read_next(iterator);
  }
  layer_mark_dirty(display_layer);
}

void init(void) {
  window = window_create();
  window_stack_push(window, true /* Animated */);

  // TODO(dmnd) try another colour
  window_set_background_color(window, GColorRed);//Color3

  // TODO(dmnd) try to remember what this does...
  // init both frames to 2
  draw_rect(0, 0, TILES_X, TILES_Y, 2);
  draw_rect(0, 0, TILES_X, TILES_Y, 2);

  // Init the layer for the display
  Layer *root_layer = window_get_root_layer(window);
  GRect frame = layer_get_frame(root_layer);
  display_layer = layer_create(frame);
  layer_set_update_proc(display_layer, &display_layer_update_cb);
  layer_add_child(root_layer, display_layer);

  app_message_register_inbox_received((AppMessageInboxReceived) in_recv_handler);
  app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
  
  if (persist_exists(COLOR1_KEY)) 
{
  char colorname[20];
  persist_read_string(COLOR1_KEY, colorname, sizeof(colorname));
  if(strcmp(colorname, "1") == 0){g_Color1 = GColorPictonBlue;}
      else if(strcmp(colorname, "2") == 0){g_Color1 = GColorDukeBlue;}
      else if(strcmp(colorname, "3") == 0){g_Color1 = GColorOxfordBlue;}
      else if(strcmp(colorname, "4") == 0){g_Color1 = GColorWhite;}
      else if(strcmp(colorname, "5") == 0){g_Color1 = GColorLightGray;}
      else if(strcmp(colorname, "6") == 0){g_Color1 = GColorBlack;}
      else if(strcmp(colorname, "7") == 0){g_Color1 = GColorYellow;}
      else if(strcmp(colorname, "8") == 0){g_Color1 = GColorChromeYellow;}
      else if(strcmp(colorname, "9") == 0){g_Color1 = GColorRed;}
      else if(strcmp(colorname, "10") == 0){g_Color1 = GColorDarkCandyAppleRed;}
      else if(strcmp(colorname, "11") == 0){g_Color1 = GColorBrightGreen;}
      else if(strcmp(colorname, "12") == 0){g_Color1 = GColorGreen;}
      else if(strcmp(colorname, "13") == 0){g_Color1 = GColorIslamicGreen;}
      else if(strcmp(colorname, "14") == 0){g_Color1 = GColorVividViolet;}
      else if(strcmp(colorname, "15") == 0){g_Color1 = GColorPurple;}
      else if(strcmp(colorname, "16") == 0){g_Color1 = GColorImperialPurple;}

      else {g_Color1 = GColorPictonBlue;}
  }else {g_Color1 = GColorPictonBlue;}
  
    if (persist_exists(COLOR2_KEY)) 
{
  char colorname[20];
  persist_read_string(COLOR2_KEY, colorname, sizeof(colorname));
  if(strcmp(colorname, "1") == 0){g_Color2 = GColorPictonBlue;}
      else if(strcmp(colorname, "2") == 0){g_Color2 = GColorDukeBlue;}
      else if(strcmp(colorname, "3") == 0){g_Color2 = GColorOxfordBlue;}
      else if(strcmp(colorname, "4") == 0){g_Color2 = GColorWhite;}
      else if(strcmp(colorname, "5") == 0){g_Color2 = GColorLightGray;}
      else if(strcmp(colorname, "6") == 0){g_Color2 = GColorBlack;}
      else if(strcmp(colorname, "7") == 0){g_Color2 = GColorYellow;}
      else if(strcmp(colorname, "8") == 0){g_Color2 = GColorChromeYellow;}
      else if(strcmp(colorname, "9") == 0){g_Color2 = GColorRed;}
      else if(strcmp(colorname, "10") == 0){g_Color2 = GColorDarkCandyAppleRed;}
      else if(strcmp(colorname, "11") == 0){g_Color2 = GColorBrightGreen;}
      else if(strcmp(colorname, "12") == 0){g_Color2 = GColorGreen;}
      else if(strcmp(colorname, "13") == 0){g_Color2 = GColorIslamicGreen;}
      else if(strcmp(colorname, "14") == 0){g_Color2 = GColorVividViolet;}
      else if(strcmp(colorname, "15") == 0){g_Color2 = GColorPurple;}
      else if(strcmp(colorname, "16") == 0){g_Color2 = GColorImperialPurple;}

      else {g_Color2 = GColorBlack;}
  }else {g_Color2 = GColorBlack;}
  
  unsigned char units;
  if (DEBUG) {
    units = SECOND_UNIT;
  } else {
    units = MINUTE_UNIT;
  }
  tick_timer_service_subscribe(units, &handle_minute_tick);
}

void deinit(void) {
  tick_timer_service_unsubscribe();
  layer_destroy(display_layer);
  window_destroy(window);
}

int main(void) {
  init();
  app_event_loop();
  deinit();
}
