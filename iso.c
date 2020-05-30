#include "iso.h"
#include "bitlib.h"
#include <gtk/gtk.h>

double size = 100;
const double sin_60 = sin(G_PI / 3);
const double cos_60 = cos(G_PI / 3);
const double tan_30 = tan(G_PI / 6);

isobox *new_isobox(double x, double y, double z, double width, double depth,
                   double height) {
  isobox *box = malloc(sizeof(isobox));
  box->x = x;
  box->y = y;
  box->z = z;
  box->width = width;
  box->height = height;
  box->depth = depth;
}

void draw_left(cairo_t *cr, double w, double d, double h) {
  cairo_matrix_t left_matrix;
  cairo_matrix_init(&left_matrix, 1, tan_30, 0, 1, 0, 0);

  cairo_save(cr);
  cairo_set_source_grey(cr, 0.5);
  cairo_transform(cr, &left_matrix);
  cairo_fill_rectangle(cr, -w * sin_60, -h, w * sin_60, h);
  cairo_restore(cr);
}

void draw_right(cairo_t *cr, double w, double d, double h) {
  cairo_matrix_t right_matrix;
  cairo_matrix_init(&right_matrix, 1, -tan_30, 0, 1, 0, 0);

  cairo_save(cr);
  cairo_set_source_grey(cr, 0.75);
  cairo_transform(cr, &right_matrix);
  cairo_fill_rectangle(cr, 0, -h, d * sin_60, h);
  cairo_restore(cr);
}

void draw_top(cairo_t *cr, double w, double d, double h) {
  cairo_matrix_t right_matrix;
  cairo_matrix_init(&right_matrix, 1, -tan_30, 0, 1, 0, 0);
  cairo_save(cr);
  cairo_set_source_grey(cr, 0.9);
  cairo_translate(cr, 0, -h);
  cairo_rotate(cr, G_PI / 3);
  cairo_transform(cr, &right_matrix);
  cairo_fill_rectangle(cr, -w * sin_60, -d, w * sin_60, d);
  cairo_restore(cr);
}

void draw_box(cairo_t *cr, double x, double y, double z, double width,
              double depth, double height) {
  x /= width;
  y /= depth;
  z /= height;
  cairo_save(cr);
  cairo_set_antialias(cr, CAIRO_ANTIALIAS_NONE);
  cairo_translate(cr, (x - y) * width * sin_60,
                  (x + y) * fmin(depth, width) * cos_60 - z * height +
                      fmin(depth, width));
  // + width);//fmin(width, depth));
  draw_top(cr, width, depth, height);
  draw_left(cr, width, depth, height);
  draw_right(cr, width, depth, height);
  cairo_restore(cr);
}

void draw_cube(cairo_t *cr, double x, double y, double z) {
  cairo_save(cr);
  cairo_set_antialias(cr, CAIRO_ANTIALIAS_NONE);
  cairo_translate(cr, (x - y) * size * sin_60,
                  (x + y) * size * cos_60 - z * size + size);
  draw_top(cr, size, size, size);
  draw_left(cr, size, size, size);
  draw_right(cr, size, size, size);
  cairo_restore(cr);
}
