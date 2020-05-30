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
  size = 10;
  cairo_clear_rgb(cr, 1, 0, 0);
  cairo_set_line_width(cr, 0.5);
  cairo_translate(cr, width * 0.5, height * 0.5);
  cairo_line(cr, -width / 2, 0, width / 2, 0);
  double scale = 0.09;
  /* draw_cube(cr, -1, 0, 1); */
  /* draw_cube(cr, 0, -1, 1); */
  /* draw_cube(cr, 1, -1, 0); */
  /* draw_cube(cr, 1, -1, 1); */
  /* draw_cube(cr, 0, 0, 0); */
  /* draw_cube(cr, 1, 0, 0); */
  /* draw_cube(cr, 1, 0, 2); */
  /* draw_cube(cr, 1, 0, 3); */
  /* draw_cube(cr, 1, 1, 4); */
  /* draw_cube(cr, 1, 1, 2); */
  /* draw_cube(cr, 1, 0, 1); */

  /* draw_cube(cr, 1, 0, 0); */
  /* draw_box(cr, 100, 100, 0, 100, 100, 100); */
  /* draw_box(cr, 200, 0, 0, 100, 100, 100); */
  /* draw_box(cr, 200, 0, 100, 100, 100, 100); */
  /* cairo_translate(cr, 200, 0); */
  /* draw_box(cr, 0, 0, 0, 10, 300, 100); */

  draw_box(cr, 0, 0, 0, 50, 200, 50);
  draw_box(cr, 50, 0, 0, 50, 100, 50);
  draw_box(cr, 100, 0, 0, 50, 50, 50);
  draw_box(cr, 12.5, 12.5, 50, 25, 25, 50);
  /* for (int z = 0; z < 20; z++) { */
  /*   for (int x = 0; x < 20; x++) { */
  /*     for (int y = 0; y < 20; y++) { */
  /*       /1* if (bl_perlin_3(x * scale, y * scale, *1/ */
  /*       /1* z * scale + bl_lerp_sin(percent, 0, 1)) > 0.0) { *1/ */
  /*       /1* if (g_random_boolean()) { *1/ */
  /*       draw_cube(cr, x, y, z + 22); */
  /*       /1* } *1/ */
  /*       /1* } *1/ */
  /*     } */
  /*   } */
  /* cairo_translate(cr, 400, 0); */
  /* } */
}
