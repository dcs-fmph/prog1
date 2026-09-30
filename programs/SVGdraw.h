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
typedef struct Drawing {
    struct SVGdraw_impl *impl;
} Drawing;

/** Return an initialized drawing with width w and height h and 
 * start writing SVG image to the specified filename.
 * Upper left corner coordinate is (0,0), lower-right corner (w,h). */
Drawing drawingInit(int width, int height, const char* filename);

/** Animation will wait time seconds. */
void drawingWait(Drawing drawing, double time);

/** All visible items in the animation will disappear */
void drawingClear(Drawing drawing);

/** Hide item with selected id. Ids are returned by all
 * drawing functions (drawRectangle etc.) */
void drawingHideItem(Drawing drawing, int id);

/** Finish writing the SVG image file and free memory used by the drawing. */
void drawingFinish(Drawing drawing);

/** Draw a rectangle with upper left corner (x,y), width w, height h.
 * Return value specifies item id for future hiding of the rectangle. */
int drawRectangle(Drawing drawing, double x, double y, double width, double height);

/** Draw an ellipse with center (x,y), x-axis radius rx, y-axis radius ry. 
 * If rx=ry, the ellipse is a circle. 
 * Return value specifies item id for future hiding of the ellipse. */
int drawEllipse(Drawing drawing, double x, double y, double rx, double ry);

/** Draw a line from (x1,y2) to (x2,y2). 
 * Return value specifies item id for future hiding of the line. */
int drawLine(Drawing drawing, double x1, double y1, double x2, double y2);

/** Write the given text at position (x, y).
 * If justification is empty, text will be centered in both x and y.
 * If justification contains letter l, left border will be at x,
 * letter r means right border will be at x. Similarly letters b and t
 * mean that top or bottom will be at coordinate y. */
int drawText(Drawing drawing, double x, double y, const char* text,
                     const char* justification);

/** Start a new polygonal path at position (x,y).
 * After starting polygon, add more points by drawPolygonAddPoint,
 * then draw it by drawPolygonFinish. */
void drawPolygonStart(Drawing drawing, double x, double y);

/** Add a new point to the current polygon. */
void drawPolygonAddPoint(Drawing drawing, double x, double y);

/** Draw the polygon specified by drawPolygonStart and
 * drawPolygonAddPoint methods, then clear polygon coordinates. 
 * Return value specifies item id for future hiding of the polygon. */
int drawPolygonFinish(Drawing drawing);

/** Set line color to a given RGB value.
 * All three values should be between 0 and 255.
 * Line color is used for drawing lines and writing text. */
void setLineColorRGB(Drawing drawing, int r, int g, int b);

/** Set line color to a given named color.
 * List of color names: http://www.w3.org/TR/SVG/types.html#ColorKeywords
 */
void setLineColor(Drawing drawing, const char* color);

/** Set fill color to a given RGB value.
 * This color is used to fill in shapes. */
void setFillColorRGB(Drawing drawing, int r, int g, int b);

/** Set fill color to a given named color. */
void setFillColor(Drawing drawing, const char* color);

/** Set fill to invisible color. */
void setNoFill(Drawing drawing);

/** Set size of the font (default is 12). */
void setFontSize(Drawing drawing, double size);

/** Set width of lines (default is 1). */
void setLineWidth(Drawing drawing, double width);

/** A struct for turtle graphics. */
typedef struct Turtle {
    struct Turtle_impl *impl;
} Turtle;

/** Return an initialized turtle with given parameters.
 * The SVG image will have width w and height h and will be writen to
 * the specified filename.
 * Turtle will start at position (x,y) heading at the given angle.
 * With angle=0 turtle heads right, angle=90 heads up etc. */
Turtle turtleInit(int width, int height, const char* filename,
                 int x, int y, double angle);

/** Set turtle speed to given value.
 * Default is 100 distance units per second. */
void turtleSetSpeed(Turtle turtle, double speed);

/** Move furtle forward by distance d. 
 * For negative d, turtle moves backward. */
void turtleForward(Turtle turtle, double length);

/** Turn turtle left by the given angle (in degrees).  */
void turtleTurnLeft(Turtle turtle, double angle);

/** Turn turtle right by the given angle (in degrees).  */
void turtleTurnRight(Turtle turtle, double angle);

/** Move turtle to the specified location. */
void turtleGoTo(Turtle turtle, double x, double y);

/** Finish writing the SVG image file and free memory used by the turtle */
void turtleFinish(Turtle turtle);

#endif	/* SVGDRAW_H */
