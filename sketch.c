#include "bitlib.h"
#include "iso.h"
#include <cairo.h>
#include <glib.h>

double width, height;
enum bl_render_mode mode;

////////////////////////////////////////
// SETUP
////////////////////////////////////////

bl_render_config setup() {
  // IMAGE, GIF, VIDEO, SMALL_VIDEO
  mode = GIF;

  // width, height, frames (fps*seconds), fps
  bl_render_config configs[4] = {
      {800, 800, 0, 0},          // IMAGE
      {400, 400, 30 * 10, 30},   // GIF
      {1920, 1080, 30 * 60, 30}, // VIDEO
      {640.0, 360, 30 * 2, 30},  // SMALL_VIDEO
  };
  return configs[mode];
}

////////////////////////////////////////
// RENDER
////////////////////////////////////////

void render(cairo_t *cr, double percent) {
  noise_rectangle(cr, 0, 0, width, height, 0);
  cairo_translate(cr, width * 0.5, height * 0.75);
  double scale = 0.1;
  g_random_set_seed(0);

  hue = 120;
  rect_func = hsv;
  for (int z = 0; z < 10; z++) {
    for (int x = 0; x < 10; x++) {
      for (int y = 0; y < 10; y++) {
        if (bl_perlin_3(x * scale, y * scale, z * scale + percent * 20) > 0.0) {
          draw_box(cr, x * 10, y * 10, z * 10, 10, 10, 10);
        }
      }
    }
  }
  rect_func = flat;
  draw_box(cr, 0, 0, 100, 110, 110, 400);
}
