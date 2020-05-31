#ifndef _ISO_H_
#define _ISO_H_

#include <gtk/gtk.h>

extern double hue;
void (*rect_func)(cairo_t *cr, double x, double y, double w, double h,
                  double val);

void draw_box(cairo_t *cr, double x, double y, double z, double width,
              double depth, double height);
void draw_cube(cairo_t *cr, double x, double y, double z, double size);
void noise_rectangle(cairo_t *cr, double x, double y, double w, double h,
                     double val);

void flat(cairo_t *cr, double x, double y, double w, double h, double val);
void hsv(cairo_t *cr, double x, double y, double w, double h, double val);
#endif
