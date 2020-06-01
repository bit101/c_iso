#include "iso.h"
#include <gtk/gtk.h>
#include <pthread.h>
#include "bitlib.h"

const double sin_60 = sin(G_PI / 3);
const double cos_60 = cos(G_PI / 3);
const double tan_30 = tan(G_PI / 6);

////////////////////
// render rect
////////////////////
void flat(cairo_t* cr, rect r, double val, void* render_data) {
  cairo_set_source_grey(cr, val);
  cairo_fill_rectangle(cr, r.x, r.y, r.w, r.h);
}

void hsv(cairo_t* cr, rect r, double val, void* render_data) {
  double hue = *(double*)render_data;
  cairo_set_source_hsv(cr, hue, 1, val);
  cairo_fill_rectangle(cr, r.x, r.y, r.w, r.h);
}

void noise(cairo_t* cr, rect r, double val, void* render_data) {
  for (double yy = r.y; yy < r.y + r.h; yy++) {
    for (double xx = r.x; xx < r.x + r.w; xx++) {
      cairo_set_source_color(cr, bl_color_random_grey_range(val - 0.2, val + 0.2));
      cairo_fill_rectangle(cr, xx, yy, 1, 1);
    }
  }
}

////////////////////
// surfaces
////////////////////
void draw_left(cairo_t* cr, box_model box, surface_renderer renderer, void* render_data) {
  cairo_matrix_t matrix;
  cairo_matrix_init(&matrix, 1, tan_30, 0, 1, 0, 0);

  rect r = {0, box.depth - box.height, box.width * sin_60, box.height};

  cairo_save(cr);
  cairo_transform(cr, &matrix);
  cairo_translate(cr, -box.width * sin_60, 0);
  renderer(cr, r, 0.2, render_data);
  cairo_restore(cr);
}

void draw_right(cairo_t* cr, box_model box, surface_renderer renderer, void* render_data) {
  cairo_matrix_t matrix;
  cairo_matrix_init(&matrix, 1, -tan_30, 0, 1, 0, 0);

  rect r = {0, box.depth - box.height, box.depth * sin_60, box.height};

  cairo_save(cr);
  cairo_transform(cr, &matrix);
  renderer(cr, r, 0.5, render_data);
  cairo_restore(cr);
}

void draw_top(cairo_t* cr, box_model box, surface_renderer renderer, void* render_data) {
  cairo_matrix_t matrix;
  cairo_matrix_init(&matrix, 1, -tan_30, 0, 1, 0, 0);

  rect r = {(box.depth - box.width) * sin_60, 0, box.width * sin_60, box.depth};

  cairo_save(cr);
  cairo_translate(cr, 0, -box.height);
  cairo_rotate(cr, G_PI / 3);
  cairo_transform(cr, &matrix);
  renderer(cr, r, 0.8, render_data);
  cairo_restore(cr);
}

void init_box(box_model* box, double x, double y, double z, double w, double d, double h) {
  box->x = x;
  box->y = y;
  box->z = z;
  box->width = w;
  box->depth = d;
  box->height = h;
}

void position_box(box_model* box, double x, double y, double z) {
  box->x = x;
  box->y = y;
  box->z = z;
}

void size_box(box_model* box, double w, double d, double h) {
  box->width = w;
  box->depth = d;
  box->height = h;
}

void cube_box(box_model* box, double size) {
  box->width = size;
  box->depth = size;
  box->height = size;
}

void draw_box(cairo_t* cr, box_model box, surface_renderer renderer, void* render_data) {
  cairo_save(cr);
  cairo_set_antialias(cr, CAIRO_ANTIALIAS_NONE);
  cairo_translate(cr, (box.x - box.y) * sin_60 + (box.width - box.depth) * sin_60,
                  (box.x + box.y) * cos_60 + (box.width - box.depth) * cos_60 - box.z);
  draw_top(cr, box, renderer, render_data);
  draw_left(cr, box, renderer, render_data);
  draw_right(cr, box, renderer, render_data);
  cairo_restore(cr);
}
