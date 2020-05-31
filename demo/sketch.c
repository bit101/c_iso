#include <cairo.h>
#include <glib.h>
#include "bitlib.h"
#include "iso.h"

double width, height;
enum bl_render_mode mode;

////////////////////////////////////////
// SETUP
////////////////////////////////////////

bl_render_config setup() {
  // IMAGE, GIF, VIDEO, SMALL_VIDEO
  mode = IMAGE;

  // width, height, frames (fps*seconds), fps
  bl_render_config configs[4] = {
      {800, 800, 0, 0},           // IMAGE
      {400, 400, 30 * 30, 30},    // GIF
      {1920, 1080, 30 * 60, 30},  // VIDEO
      {640.0, 360, 30 * 2, 30},   // SMALL_VIDEO
  };
  return configs[mode];
}

////////////////////////////////////////
// RENDER
////////////////////////////////////////

void render(cairo_t* cr, double percent) {
  double scale = 0.1;
  double box_size = 10;
  double world_size = 35;
  double hue;
  bool green;
  double offset;
  box_model box;

  cairo_clear_grey(cr, 0.15);
  cairo_translate(cr, width * 0.5, height * 0.5);

  cube_box(&box, box_size);

  for (int z = 0; z < world_size; z++) {
    for (int x = 0; x < world_size; x++) {
      for (int y = 0; y < world_size; y++) {
        offset = bl_lerp_sin(percent, 0, 19);
        green = bl_perlin_3(x * scale, y * scale, z * scale + offset) > 0.0;
        hue = green ? 120 : 240;

        position_box(&box, x * box_size, y * box_size, z * box_size);
        draw_box(cr, box, hsv, &hue);
      }
    }
  }
}
