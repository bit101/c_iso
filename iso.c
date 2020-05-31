#include "iso.h"
#include "bitlib.h"
#include <gtk/gtk.h>

const double sin_60 = sin(G_PI / 3);
const double cos_60 = cos(G_PI / 3);
const double tan_30 = tan(G_PI / 6);

void draw_left(cairo_t *cr, double w, double d, double h) {
  cairo_matrix_t matrix;
  cairo_matrix_init(&matrix, 1, tan_30, 0, 1, 0, 0);

  cairo_save(cr);
  cairo_set_source_grey(cr, 0.2);
  cairo_transform(cr, &matrix);
  cairo_fill_rectangle(cr, 0, d - h, -w * sin_60, h);
  cairo_restore(cr);
}

void draw_right(cairo_t *cr, double w, double d, double h) {
  cairo_matrix_t matrix;
  cairo_matrix_init(&matrix, 1, -tan_30, 0, 1, 0, 0);

  cairo_save(cr);
  cairo_set_source_grey(cr, 0.5);
  cairo_transform(cr, &matrix);
  cairo_fill_rectangle(cr, 0, d - h, d * sin_60, h);
  cairo_restore(cr);
}

void draw_floor(cairo_t *cr, double w, double d, double h) {
  cairo_matrix_t matrix;
  cairo_matrix_init(&matrix, 1, -tan_30, 0, 1, 0, 0);

  cairo_save(cr);
  cairo_set_source_grey(cr, 1);
  cairo_rotate(cr, G_PI / 3);
  cairo_transform(cr, &matrix);
  cairo_fill_rectangle(cr, (d - w) * sin_60, 0, w * sin_60, d);
  cairo_restore(cr);
}

void draw_top(cairo_t *cr, double w, double d, double h) {
  cairo_matrix_t matrix;
  cairo_matrix_init(&matrix, 1, -tan_30, 0, 1, 0, 0);

  cairo_save(cr);
  cairo_set_source_grey(cr, 0.8);
  cairo_translate(cr, 0, -h);
  cairo_rotate(cr, G_PI / 3);
  cairo_transform(cr, &matrix);
  cairo_fill_rectangle(cr, (d - w) * sin_60, 0, w * sin_60, d);
  cairo_restore(cr);
}

void draw_box(cairo_t *cr, double x, double y, double z, double width,
              double depth, double height) {
  cairo_save(cr);
  cairo_set_antialias(cr, CAIRO_ANTIALIAS_NONE);
  cairo_translate(cr, (x - y) * sin_60 + (width - depth) * sin_60,
                  (x + y) * cos_60 + (width - depth) * cos_60 - z);
  /* draw_floor(cr, width, depth, height); */
  draw_top(cr, width, depth, height);
  draw_left(cr, width, depth, height);
  draw_right(cr, width, depth, height);
  cairo_restore(cr);
}

void draw_cube(cairo_t *cr, double x, double y, double z, double size) {
  draw_box(cr, x * size, y * size, z * size, size, size, size);
  /* cairo_save(cr); */
  /* cairo_set_antialias(cr, CAIRO_ANTIALIAS_NONE); */
  /* cairo_translate(cr, (x - y) * size * sin_60, */
  /*                 (x + y) * size * cos_60 - z * size); */
  /* draw_top(cr, size, size, size); */
  /* draw_left(cr, size, size, size); */
  /* draw_right(cr, size, size, size); */
  /* cairo_restore(cr); */
}
