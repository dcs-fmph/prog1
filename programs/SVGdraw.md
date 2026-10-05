---
title: Program SVGdraw.c
---

[Súbor na stiahnutie](./SVGdraw.c)

```c
#include "SVGdraw.h"
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>

#define PI 3.14159265358979323846
static const double DEGREES_RATIO = PI / 180.0;

/* Longest real SVG colour name is under ~20 chars; 64 is a safe ceiling. */
#define SVGDRAW_COLOR_MAX 64

/* A pair of doubles, replacing C++ pair<double,double>. */
typedef struct {
    double first;
    double second;
} PairDD;

/* Hidden implementation of SVGdraw (opaque to callers). */
struct SVGdraw_impl {
    FILE *svg;
    PairDD *itemTimes;
    int itemTimesCount;
    int itemTimesCap;
    PairDD *polygon;
    int polygonCount;
    int polygonCap;
    double time;
    int isActive;
    char lineColor[SVGDRAW_COLOR_MAX];
    char fillColor[SVGDRAW_COLOR_MAX];
    double fontSize;
    double lineWidth;
};

/* Hidden implementation of Turtle (opaque to callers). */
struct Turtle_impl {
    double x, y, angle;
    double pathLength;
    double speed;
    int isActive;
    FILE *svg;
};

void checkArg(int correct, const char *message) {
    if (!correct) {
        fprintf(stderr, "Chyba v pouziti kniznice SVGdraw:\n");
        fprintf(stderr, " %s\n", message);
        exit(1);
    }
}

/* Append (a,b) to a growable array, doubling capacity when full. */
static void pushPair(PairDD **arr, int *count, int *cap, double a, double b) {
    if (*count == *cap) {
        int newCap = (*cap == 0) ? 8 : (*cap * 2);
        PairDD *tmp = realloc(*arr, (size_t) newCap * sizeof(PairDD));
        checkArg(tmp != NULL, "Nedostatok pamate");
        *arr = tmp;
        *cap = newCap;
    }
    (*arr)[*count].first = a;
    (*arr)[*count].second = b;
    (*count)++;
}

/* Copy a colour name into a fixed buffer, refusing anything too long
 * (this keeps the copy safe instead of overflowing). */
static void setColorString(char *dst, const char *src) {
    checkArg(strlen(src) < SVGDRAW_COLOR_MAX, "Meno farby je prilis dlhe");
    strcpy(dst, src);
}

static void initSVG(FILE *svg, double width, double height) {
    checkArg(width > 0 && height > 0, "Rozmery obrazku musia byt kladne");
    fprintf(svg, "<?xml version=\"1.0\" encoding=\"iso-8859-1\"?>\n");
    fprintf(svg, "<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.0//EN\" \"http://www.w3.org/TR/SVG/DTD/svg10.dtd\">\n");
    fprintf(svg, "<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" ");
    fprintf(svg, " width=\"%gpx\" height=\"%gpx\">\n", width, height);
    fprintf(svg, "<rect x=\"0\" y=\"0\" width=\"%g\" height=\"%g\""
                 " style=\"fill:white;stroke:lightgray;stroke-width:1;\" />\n\n",
            width, height);
}

/* Writes "rgb(r,g,b)" into out (snprintf can never overflow the buffer). */
static void formatRGBColor(char *out, size_t outSize, int r, int g, int b) {
    checkArg(0 <= r && r <= 255 && 0 <= g && g <= 255 && 0 <= b && b <= 255,
             "RGB farby musia byt medzi 0 a 255 vratane.");
    snprintf(out, outSize, "rgb(%d,%d,%d)", r, g, b);
}

/* Forward declarations of the internal helpers used before their definition. */
static int addItem(struct SVGdraw_impl *d);
static int nextItemId(struct SVGdraw_impl *d);
static void printStyle(struct SVGdraw_impl *d);

Drawing drawingInit(int width, int height, const char* filename) {
    struct SVGdraw_impl *d = malloc(sizeof(struct SVGdraw_impl));
    checkArg(d != NULL, "Nedostatok pamate");
    d->itemTimes = NULL;
    d->itemTimesCount = 0;
    d->itemTimesCap = 0;
    d->polygon = NULL;
    d->polygonCount = 0;
    d->polygonCap = 0;
    d->time = 0;
    d->isActive = 1;
    strcpy(d->lineColor, "black");
    strcpy(d->fillColor, "none");
    d->fontSize = 12;
    d->lineWidth = 1;
    
    d->svg = fopen(filename, "w");
    checkArg(d->svg != NULL, "Nepodarilo sa otvorit subor na zapis");
    initSVG(d->svg, width, height);
    Drawing self;
    self.impl = d;
    return self;
}

void drawingWait(Drawing drawing, double time) {
    checkArg(time > 0, "Cas cakania musi byt kladne cislo");
    drawing.impl->time += time;
}

void drawingClear(Drawing drawing) {
    struct SVGdraw_impl *d = drawing.impl;
    for (int i = 0; i < d->itemTimesCount; i++) {
        if (d->itemTimes[i].second < 0) {
            d->itemTimes[i].second = d->time;
        }
    }
}

void drawingHideItem(Drawing drawing, int id) {
    struct SVGdraw_impl *d = drawing.impl;
    checkArg(id >= 0 && id < d->itemTimesCount, "Zadane id pre hideItem neexistuje");
    checkArg(d->itemTimes[id].second < 0, "Objekt s danym id vo funkcii hideItem bol uz predtym skryty.");
    d->itemTimes[id].second = d->time;
}

void drawingFinishWithoutDestroy(Drawing drawing) {
    struct SVGdraw_impl *d = drawing.impl;
    checkArg(d != NULL && d->isActive, "Funkciu finish je mozne volat iba raz");

    for (int i = 0; i < d->itemTimesCount; i++) {
        double start = d->itemTimes[i].first;
        double end = d->itemTimes[i].second;
        if (start > 0) {
            fprintf(d->svg, "<set xlink:href=\"#item%d\""
                            " attributeName=\"visibility\" to=\"hidden\" "
                            "begin=\"0s\" dur=\"%gs\" />\n", i, start);
        }
        if (end >= 0) {
            fprintf(d->svg, "<set xlink:href=\"#item%d\""
                            " attributeName=\"visibility\" to=\"hidden\" "
                            "begin=\"%gs\" dur=\"indefinite\" />\n", i, end);
        }
    }

    fprintf(d->svg, "</svg>\n");
    fclose(d->svg);
    d->svg = NULL;
    d->isActive = 0;
}

void drawingDestroy(Drawing drawing) {
    struct SVGdraw_impl *d = drawing.impl;
    if (d == NULL) {
        return;
    }
    if (d->isActive) {
        drawingFinishWithoutDestroy(drawing);
    }
    free(d->itemTimes);
    free(d->polygon);
    free(d);
    drawing.impl = NULL;
}

void drawingFinish(Drawing drawing) {
    drawingFinishWithoutDestroy(drawing);
    drawingDestroy(drawing);
}

int drawRectangle(Drawing drawing, double x, double y, double width, double height) {
    struct SVGdraw_impl *d = drawing.impl;
    checkArg(d != NULL && d->isActive, "Po zavolani funkcie finish uz nie je mozne vykreslovat");
    fprintf(d->svg, "<rect id=\"item%d\" x=\"%g\" y=\"%g\" width=\"%g\" height=\"%g\" ",
            nextItemId(d), x, y, width, height);
    printStyle(d);
    fprintf(d->svg, " />\n");
    return addItem(d);
}

int drawEllipse(Drawing drawing, double x, double y, double rx, double ry) {
    struct SVGdraw_impl *d = drawing.impl;
    checkArg(d != NULL && d->isActive, "Po zavolani funkcie finish uz nie je mozne vykreslovat");
    fprintf(d->svg, "<ellipse id=\"item%d\" cx=\"%g\" cy=\"%g\" rx=\"%g\" ry=\"%g\" ",
            nextItemId(d), x, y, rx, ry);
    printStyle(d);
    fprintf(d->svg, " />\n");
    return addItem(d);
}

int drawLine(Drawing drawing, double x1, double y1, double x2, double y2) {
    struct SVGdraw_impl *d = drawing.impl;
    checkArg(d != NULL && d->isActive, "Po zavolani funkcie finish uz nie je mozne vykreslovat");
    fprintf(d->svg, "<line id=\"item%d\" x1=\"%g\" y1=\"%g\" x2=\"%g\" y2=\"%g\" ",
            nextItemId(d), x1, y1, x2, y2);
    printStyle(d);
    fprintf(d->svg, " />\n");
    return addItem(d);
}

int drawText(Drawing drawing, double x, double y, const char* text,
                     const char* justification) {
    struct SVGdraw_impl *d = drawing.impl;
    checkArg(d != NULL && d->isActive, "Po zavolani funkcie finish uz nie je mozne vykreslovat");
    fprintf(d->svg, "<text id=\"item%d\" x=\"%g\" y=\"%g\" "
                    "style=\"fill:%s;stroke-width:0pt;stroke:none;font-size:%gpt;",
            nextItemId(d), x, y, d->lineColor, d->fontSize);
    if (strchr(justification, 'l')) {
        fprintf(d->svg, "text-anchor:start;");
    } else if (strchr(justification, 'r')) {
        fprintf(d->svg, "text-anchor:end;");
    } else {
        fprintf(d->svg, "text-anchor:middle;");
    }
    if (strchr(justification, 't')) {
        fprintf(d->svg, "dominant-baseline:text-before-edge;");
    } else if (strchr(justification, 'b')) {
        fprintf(d->svg, "dominant-baseline:text-after-edge;");
    } else {
        fprintf(d->svg, "dominant-baseline:middle;");
    }

    fprintf(d->svg, "\">%s</text>\n", text);
    return addItem(d);
}

void drawPolygonStart(Drawing drawing, double x, double y) {
    drawing.impl->polygonCount = 0;
    drawPolygonAddPoint(drawing, x, y);
}

void drawPolygonAddPoint(Drawing drawing, double x, double y) {
    struct SVGdraw_impl *d = drawing.impl;
    pushPair(&d->polygon, &d->polygonCount, &d->polygonCap, x, y);
}

int drawPolygonFinish(Drawing drawing) {
    struct SVGdraw_impl *d = drawing.impl;
    checkArg(d != NULL && d->isActive, "Po zavolani funkcie finish uz nie je mozne vykreslovat");
    checkArg(d->polygonCount > 2, "Polygon musi mat aspon 3 vrcholy");
    fprintf(d->svg, "<polygon id=\"item%d\" points=\"", nextItemId(d));
    for (int i = 0; i < d->polygonCount; i++) {
        fprintf(d->svg, " %g,%g", d->polygon[i].first, d->polygon[i].second);
    }
    fprintf(d->svg, "\" ");
    printStyle(d);
    fprintf(d->svg, " />\n");
    d->polygonCount = 0;
    return addItem(d);
}

void setLineColorRGB(Drawing drawing, int r, int g, int b) {
    formatRGBColor(drawing.impl->lineColor, SVGDRAW_COLOR_MAX, r, g, b);
}

void setLineColor(Drawing drawing, const char* color) {
    setColorString(drawing.impl->lineColor, color);
}

void setFillColorRGB(Drawing drawing, int r, int g, int b) {
    formatRGBColor(drawing.impl->fillColor, SVGDRAW_COLOR_MAX, r, g, b);
}

void setFillColor(Drawing drawing, const char* color) {
    const char *c = color;
    while ((*c) != 0) {
        checkArg(islower((unsigned char) *c), "Meno farby musi pozostavat iba z malych pismen");
        c++;
    }
    setColorString(drawing.impl->fillColor, color);
}

void setNoFill(Drawing drawing) {
    strcpy(drawing.impl->fillColor, "none");
}

void setFontSize(Drawing drawing, double size) {
    checkArg(size > 0, "Velkost fontu musi byt kladna");
    drawing.impl->fontSize = size;
}

void setLineWidth(Drawing drawing, double width) {
    checkArg(width > 0, "Sirka ciary musi byt kladna");
    drawing.impl->lineWidth = width;
}

static int addItem(struct SVGdraw_impl *d) {
    int n = d->itemTimesCount;
    pushPair(&d->itemTimes, &d->itemTimesCount, &d->itemTimesCap, d->time, -1);
    return n;
}

static int nextItemId(struct SVGdraw_impl *d) {
    return d->itemTimesCount;
}

static void printStyle(struct SVGdraw_impl *d) {
    fprintf(d->svg, "style=\"stroke:%s;stroke-width:%g;fill:%s\"",
            d->lineColor, d->lineWidth, d->fillColor);
}

Turtle turtleInit(int width, int height, const char* filename,
                 int x, int y, double angle) {
    struct Turtle_impl *d = malloc(sizeof(struct Turtle_impl));
    checkArg(d != NULL, "Nedostatok pamate");
    d->x = x;
    d->y = y;
    d->angle = angle;
    d->pathLength = 0;
    d->speed = 100;
    d->isActive = 1;
    
    d->svg = fopen(filename, "w");
    checkArg(d->svg != NULL, "Nepodarilo sa otvorit subor na zapis");
    initSVG(d->svg, width, height);
    fprintf(d->svg, "<path fill=\"none\" stroke=\"black\" id=\"turtlepath\"  d=\"");
    fprintf(d->svg, "M %g %g", d->x, d->y);
    
    Turtle self;
    self.impl = d;
    return self;
}

void turtleFinishWithoutDestroy(Turtle turtle) {
    struct Turtle_impl *d = turtle.impl;
    checkArg(d != NULL && d->isActive, "Funkciu finish je mozne volat iba raz");
    double time = d->pathLength / d->speed;
    fprintf(d->svg, "\"/>\n\n");
    fprintf(d->svg, "<path id=\"turtle\" fill=\"red\" d=\"M 10 0 L -10 -8 L -10 8 \">\n");
    fprintf(d->svg, "  <animateMotion dur=\"%gs\" repeatCount=\"1\" rotate=\"auto\">\n", time);
    fprintf(d->svg, "  <mpath xlink:href=\"#turtlepath\"/>\n");
    fprintf(d->svg, "  </animateMotion>\n");
    fprintf(d->svg, "</path>\n");
    fprintf(d->svg, "<set xlink:href=\"#turtle\" "
                    "attributeName=\"visibility\" to=\"hidden\" "
                    "begin=\"%gs\" dur=\"indefinite\" />\n\n", time);

    fprintf(d->svg, "</svg>\n");
    fclose(d->svg);
    d->svg = NULL;
    d->isActive = 0;
}

void turtleDestroy(Turtle turtle) {
    struct Turtle_impl *d = turtle.impl;
    if (d == NULL) {
        return;
    }
    if (d->isActive) {
        turtleFinishWithoutDestroy(turtle);
    }
    free(d);
    turtle.impl = NULL;
}

void turtleFinish(Turtle turtle) {
    turtleFinishWithoutDestroy(turtle);
    turtleDestroy(turtle);
}

void turtleSetSpeed(Turtle turtle, double speed) {
    checkArg(speed > 0, "Rychlost korytnacky musi byt kladna");
    turtle.impl->speed = speed;
}

void turtleForward(Turtle turtle, double length) {
    struct Turtle_impl *d = turtle.impl;
    double x = d->x + length * cos(d->angle * DEGREES_RATIO);
    double y = d->y - length * sin(d->angle * DEGREES_RATIO);

    turtleGoTo(turtle, x, y);
}

void turtleTurnLeft(Turtle turtle, double angle) {
    turtle.impl->angle += angle;
}

void turtleTurnRight(Turtle turtle, double angle) {
    turtle.impl->angle -= angle;
}

void turtleGoTo(Turtle turtle, double x, double y) {
    struct Turtle_impl *d = turtle.impl;
    checkArg(d != NULL && d->isActive, "Po zavolani funkcie finish uz nie je mozne posuvat korytnacku");
    double dx = x - d->x;
    double dy = y - d->y;
    d->pathLength += sqrt(dx * dx + dy * dy);
    d->x = x;
    d->y = y;
    fprintf(d->svg, " L %g %g", d->x, d->y);
}
```
