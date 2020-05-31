#ifndef _ISO_H_
#define _ISO_H_

#include <gtk/gtk.h>

void draw_box(cairo_t *cr, double x, double y, double z, double width,
              double depth, double height);
void draw_cube(cairo_t *cr, double x, double y, double z, double size);

#endif
