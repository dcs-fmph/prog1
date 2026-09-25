/*
 * File:   SVGdraw.h
 * Authors: Jaro Budis, Brona Brejova, Peter Grochal
 *
 * The SVGdraw library provides a simple interface for writing SVG
 * files. It was developed for teaching first-year course Programming
 * (1) in C/C++ at Comenius University Bratislava.
 *
 * See more information at the course webpage
 * https://dcs-fmph.github.io/prog1
 */
#ifndef SVGDRAW_H
#define	SVGDRAW_H

/** Struct representing a drawing. */
typedef struct SVGdraw {
    struct SVGdraw_impl *impl;
} SVGdraw;

/** Initialize SVG image with width w and height h and write it to
 * the specified filename.
 * Upper left corner coordinate is (0,0), lower-right corner (w,h). */
void SVGdraw_init(SVGdraw *self, int width, int height, const char* filename);
/** Animation will wait time seconds. */
void SVGdraw_wait(SVGdraw *self, double time);
/** All visible items in the animation will disappear */
void SVGdraw_clear(SVGdraw *self);
/** Hide item with selected id. Ids are returned by all
 * drawing functions (drawRectangle etc.) */
void SVGdraw_hideItem(SVGdraw *self, int id);

/** Finish writing the image file and free memory used by the drawing. */
void SVGdraw_finish(SVGdraw *self);

/** Draw a rectangle with upper left corner (x,y), width w, height h.
 * Return value specifies item id for future delteion. */
int SVGdraw_drawRectangle(SVGdraw *self, double x, double y, double width, double height);
/** Draw an ellipse with center (x,y), x-axis radius rx, y-axis radius ry. */
int SVGdraw_drawEllipse(SVGdraw *self, double x, double y, double rx, double ry);
/** Draw a line from (x1,y2) to (x2,y2). */
int SVGdraw_drawLine(SVGdraw *self, double x1, double y1, double x2, double y2);
/** Write the given text at position (x, y).
 * If justification is empty, text will be centered in both x and y.
 * If justification contains letter l, left border will be at x,
 * letter r means right border will be at x. Similarly letters b and t
 * mean that top or bottom will be at coordinate y. */
int SVGdraw_drawText(SVGdraw *self, double x, double y, const char* text,
                     const char* justification);

/** Start a new polygonal path at position (x,y).
 * After starting polygon, add more points by addPolygonPoint,
 * then draw by drawPolygon. */
void SVGdraw_startPolygon(SVGdraw *self, double x, double y);
/** Add a new point to the current polygon. */
void SVGdraw_addPolygonPoint(SVGdraw *self, double x, double y);
/** Draw the polygon specified by startPolygond and
 * addPolygonPoint methods, then clear polygin coordinates. */
int SVGdraw_drawPolygon(SVGdraw *self);

/** Set line color to a given RGB value.
 * All three values should be between 0 and 255.
 * Line color is used for drawing lines and writing text. */
void SVGdraw_setLineColorRGB(SVGdraw *self, int r, int g, int b);
/** Set line color to a given named color.
 * List of color names: http://www.w3.org/TR/SVG/types.html#ColorKeywords
 */
void SVGdraw_setLineColor(SVGdraw *self, const char* color);
/** Set fill color to a given RGB value.
 * This color is used to fill in shapes. */
void SVGdraw_setFillColorRGB(SVGdraw *self, int r, int g, int b);
/** Set fill color to a given named color. */
void SVGdraw_setFillColor(SVGdraw *self, const char* color);
/** Set fill to invisible color. */
void SVGdraw_setNoFill(SVGdraw *self);
/** Set size of the font (default is 12). */
void SVGdraw_setFontSize(SVGdraw *self, double size);
/** Set width of lines (default is 1). */
void SVGdraw_setLineWidth(SVGdraw *self, double width);

/** A struct for turtle graphics. */
typedef struct Turtle {
    struct Turtle_impl *impl;
} Turtle;

/** Initialize SVG image and create a turtle.
 * Image will have width w and height h and will be writen to
 * the specified filename.
 * Turtle will start at position (x,y) heading at the given angle.
 * With angle=0 turtle heads right, angle=90 heads up etc. */
void Turtle_init(Turtle *self, int width, int height, const char* filename,
                 int x, int y, double angle);
/** Set turtle speed to given value.
 * Default is 100 distance units per second. */
void Turtle_setSpeed(Turtle *self, double speed);
/** Move furtle forward by distance d. */
void Turtle_forward(Turtle *self, double length);
/** Turn turtle left by the given angle (in degrees).  */
void Turtle_turnLeft(Turtle *self, double angle);
/** Turn turtle right by the given angle (in degrees).  */
void Turtle_turnRight(Turtle *self, double angle);
/** Move turtle to the specified location. */
void Turtle_goTo(Turtle *self, double x, double y);

/** Finish writing the file and free memory used by the turtle */
void Turtle_finish(Turtle *self);

#endif	/* SVGDRAW_H */
