#ifndef _ISO_H_
#define _ISO_H_

#include <gtk/gtk.h>
#include "bitlib.h"
#include "iso.h"

////////////////////
// render rect
////////////////////
typedef struct _rect {
  double x;
  double y;
  double w;
  double h;
} rect;

typedef void (*surface_renderer)(cairo_t* cr, rect r, double val, void* render_data);

void flat(cairo_t* cr, rect r, double val, void* render_data);
void hsv(cairo_t* cr, rect r, double val, void* render_data);
void noise(cairo_t* cr, rect r, double val, void* render_data);

////////////////////
// surfaces
////////////////////

typedef struct _box_model {
  double x;
  double y;
  double z;
  double width;
  double depth;
  double height;
} box_model;

void init_box(box_model* box, double x, double y, double z, double w, double d, double h);
void position_box(box_model* box, double x, double y, double z);
void size_box(box_model* box, double w, double d, double h);
void cube_box(box_model* box, double size);

void draw_box(cairo_t* cr, box_model box, surface_renderer renderer, void* render_data);

#endif
