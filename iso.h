#ifndef _ISO_H_
#define _ISO_H_

#include <gtk/gtk.h>
typedef struct _isobox {
  double x;
  double y;
  double z;
  double width;
  double height;
  double depth;
} isobox;

isobox *new_isobox(double x, double y, double z, double width, double height,
                   double depth);
void draw_box(cairo_t *cr, double x, double y, double z, double h);

#endif
