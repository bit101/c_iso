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
  mode = IMAGE;

  // width, height, frames (fps*seconds), fps
  bl_render_config configs[4] = {
      {800, 800, 0, 0},         // IMAGE
      {400, 400, 30 * 2, 30},   // GIF
      {1920, 1080, 30 * 2, 30}, // VIDEO
      {640.0, 360, 30 * 2, 30}, // SMALL_VIDEO
  };
  return configs[mode];
}

////////////////////////////////////////
// RENDER
////////////////////////////////////////

void render(cairo_t *cr, double percent) {
  cairo_clear_rgb(cr, 1, 1, 1);
  cairo_set_line_width(cr, 0.5);
  cairo_translate(cr, width * 0.5, height * 0.5);

  for (int z = 0; z < 10; z++) {
    for (int x = 0; x < 10; x++) {
      for (int y = 0; y < 10; y++) {
        if (g_random_double() > 0.25) {
          draw_box(cr, x, y, z * 30, 30);
        }
      }
    }
  }
}
