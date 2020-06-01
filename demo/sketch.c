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
      {800, 400, 0, 0},           // IMAGE
      {400, 400, 30 * 30, 30},    // GIF
      {1920, 1080, 30 * 60, 30},  // VIDEO
      {640.0, 360, 30 * 2, 30},   // SMALL_VIDEO
  };
  return configs[mode];
}

////////////////////////////////////////
// RENDER
////////////////////////////////////////

void camo(cairo_t* cr, rect r, double val, void* render_data) {
  cairo_save(cr);
  cairo_rectangle(cr, r.x, r.y, r.w, r.h);
  cairo_clip(cr);

  cairo_set_source_grey(cr, val);
  cairo_fill_rectangle(cr, r.x, r.y, r.w, r.h);
  cairo_set_source_rgba(cr, 0, 0, 0, 0.05);
  double radius = r.w * 0.05;
  for (int i = 0; i < 1000; i++) {
    cairo_fill_circle(cr, g_random_double_range(r.x, r.x + r.w), g_random_double_range(r.y, r.y + r.h), radius);
  }

  cairo_restore(cr);
}

void img(cairo_t* cr, rect r, double val, void* render_data) {
  cairo_surface_t* surface = cairo_image_surface_create_from_png("boy.png");
  cairo_set_source_surface(cr, surface, r.x, r.y);
  cairo_pattern_t* pattern = cairo_get_source(cr);
  cairo_matrix_t matrix;
  double scale_x = r.w / cairo_image_surface_get_width(surface);
  double scale_y = r.h / cairo_image_surface_get_height(surface);
  cairo_matrix_init_identity(&matrix);
  cairo_matrix_scale(&matrix, 1 / scale_x, 1 / scale_y);
  cairo_pattern_set_matrix(pattern, &matrix);
  cairo_fill_rectangle(cr, r.x, r.y, r.w, r.h);

  cairo_set_source_rgba(cr, 0, 0, 0, 1 - val);
  cairo_fill_rectangle(cr, r.x, r.y, r.w, r.h);
}

void render(cairo_t* cr, double percent) {
  double scale = 0.1;
  double box_size = 300;
  double world_size = 35;
  double hue;
  bool green;
  double offset;
  box_model box;

  cairo_clear_grey(cr, 0.15);
  cairo_translate(cr, width * 0.5, height * 0.5);

  init_box(&box, -135, 135, 0, 125, 175, 125);
  draw_box(cr, box, img, &hue);

  init_box(&box, 0, 0, 0, 125, 125, 175);
  draw_box(cr, box, img, &hue);

  init_box(&box, 135, -135, 0, 175, 125, 125);
  draw_box(cr, box, img, &hue);
}
