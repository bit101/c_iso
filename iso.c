#include "iso.h"
#include "bitlib.h"
#include <gtk/gtk.h>

double size = 30;

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

void draw_left(cairo_t *cr, double height) {
  cairo_matrix_t left_matrix;
  cairo_matrix_init(&left_matrix, 1, 0.5, 0, 1, 0, 0);

  cairo_save(cr);
  cairo_set_source_grey(cr, 0.5);
  cairo_transform(cr, &left_matrix);
  cairo_fill_rectangle(cr, -size, -height, size, height);
  cairo_restore(cr);
}

void draw_right(cairo_t *cr, double height) {
  cairo_matrix_t right_matrix;
  cairo_matrix_init(&right_matrix, 1, -0.5, 0, 1, 0, 0);

  cairo_save(cr);
  cairo_set_source_grey(cr, 0.75);
  cairo_transform(cr, &right_matrix);
  cairo_fill_rectangle(cr, 0, -height, size, height);
  cairo_restore(cr);
}

void draw_top(cairo_t *cr, double height) {
  cairo_save(cr);
  cairo_set_source_grey(cr, 0.9);
  cairo_translate(cr, 0, -height);
  cairo_scale(cr, 1, 0.5);
  cairo_scale(cr, sqrt(2), sqrt(2));
  cairo_rotate(cr, G_PI / 4);
  cairo_fill_rectangle(cr, -size, -size, size, size);
  cairo_restore(cr);
}

void draw_box(cairo_t *cr, double x, double y, double z, double h) {
  cairo_save(cr);
  cairo_set_antialias(cr, CAIRO_ANTIALIAS_NONE);
  /* cairo_translate(cr, box->x - box->y, box->y + box->x / 2); */

  cairo_translate(cr, (x - y) * size, (x + y) * size / 2 - z);
  draw_top(cr, h);
  draw_left(cr, h);
  draw_right(cr, h);
  cairo_restore(cr);
}
