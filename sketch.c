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

extern double size;

void render(cairo_t *cr, double percent) {
  size = 20;
  cairo_clear_rgb(cr, 1, 0, 0);
  cairo_set_line_width(cr, 0.5);
  cairo_translate(cr, width * 0.5, height * 0.5);
  cairo_line(cr, -width / 2, 0, width / 2, 0);
  double scale = 0.09;
  /* draw_box(cr, 100, 0, 0, 50, 50, 50); */

  for (int z = 0; z < 20; z++) {
    for (int x = 0; x < 20; x++) {
      for (int y = 0; y < 20; y++) {
        /* if (bl_perlin_3(x * scale, y * scale, */
        /* z * scale + bl_lerp_sin(percent, 0, 1)) > 0.0) { */
        if (g_random_boolean()) {
          draw_cube(cr, x, y, z);
        }
        /* } */
      }
    }
  }
}
