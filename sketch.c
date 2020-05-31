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
      {400, 400, 30 * 60, 30},   // GIF
      {1920, 1080, 30 * 60, 30}, // VIDEO
      {640.0, 360, 30 * 2, 30},  // SMALL_VIDEO
  };
  return configs[mode];
}

////////////////////////////////////////
// RENDER
////////////////////////////////////////

void render(cairo_t *cr, double percent) {
  cairo_clear_grey(cr, 0.66);
  cairo_set_line_width(cr, 0.5);
  cairo_translate(cr, width * 0.5, height * 0.5);
  /* cairo_line(cr, -width / 2, 0, width / 2, 0); */
  double scale = 0.1;
  /* draw_box(cr, 100, 0, 0, 50, 50, 50); */

  draw_cube(cr, 0, 0, -1.5, 100);
  for (int z = 0; z < 10; z++) {
    for (int x = 0; x < 10; x++) {
      for (int y = 0; y < 10; y++) {
        if (bl_perlin_3(x * scale, y * scale, z * scale + percent * 20) > 0.0) {
          draw_cube(cr, x, y, z, 10);
        }
      }
    }
  }
  draw_cube(cr, 0, 0, 1.5, 100);
  draw_cube(cr, 0, 0, 2.5, 100);
}
