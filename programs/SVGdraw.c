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

void SVGdraw_init(SVGdraw *self, int width, int height, const char* filename) {
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
    self->impl = d;

    d->svg = fopen(filename, "w");
    checkArg(d->svg != NULL, "Nepodarilo sa otvorit subor na zapis");
    initSVG(d->svg, width, height);
}

void SVGdraw_wait(SVGdraw *self, double time) {
    checkArg(time > 0, "Cas cakania musi byt kladne cislo");
    self->impl->time += time;
}

void SVGdraw_clear(SVGdraw *self) {
    struct SVGdraw_impl *d = self->impl;
    for (int i = 0; i < d->itemTimesCount; i++) {
        if (d->itemTimes[i].second < 0) {
            d->itemTimes[i].second = d->time;
        }
    }
}

void SVGdraw_hideItem(SVGdraw *self, int id) {
    struct SVGdraw_impl *d = self->impl;
    checkArg(id >= 0 && id < d->itemTimesCount, "Zadane id pre hideItem neexistuje");
    checkArg(d->itemTimes[id].second < 0, "Objekt s danym id vo funkcii hideItem bol uz predtym skryty.");
    d->itemTimes[id].second = d->time;
}

void SVGdraw_finish_without_destroy(SVGdraw *self) {
    struct SVGdraw_impl *d = self->impl;
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

void SVGdraw_destroy(SVGdraw *self) {
    if (self == NULL) {
        return;
    }
    struct SVGdraw_impl *d = self->impl;
    if (d == NULL) {
        return;
    }
    if (d->isActive) {
        SVGdraw_finish_without_destroy(self);
    }
    free(d->itemTimes);
    free(d->polygon);
    free(d);
    self->impl = NULL;
}

void SVGdraw_finish(SVGdraw *self) {
    SVGdraw_finish_without_destroy(self);
    SVGdraw_destroy(self);
}

int SVGdraw_drawRectangle(SVGdraw *self, double x, double y, double width, double height) {
    struct SVGdraw_impl *d = self->impl;
    checkArg(d != NULL && d->isActive, "Po zavolani funkcie finish uz nie je mozne vykreslovat");
    fprintf(d->svg, "<rect id=\"item%d\" x=\"%g\" y=\"%g\" width=\"%g\" height=\"%g\" ",
            nextItemId(d), x, y, width, height);
    printStyle(d);
    fprintf(d->svg, " />\n");
    return addItem(d);
}

int SVGdraw_drawEllipse(SVGdraw *self, double x, double y, double rx, double ry) {
    struct SVGdraw_impl *d = self->impl;
    checkArg(d != NULL && d->isActive, "Po zavolani funkcie finish uz nie je mozne vykreslovat");
    fprintf(d->svg, "<ellipse id=\"item%d\" cx=\"%g\" cy=\"%g\" rx=\"%g\" ry=\"%g\" ",
            nextItemId(d), x, y, rx, ry);
    printStyle(d);
    fprintf(d->svg, " />\n");
    return addItem(d);
}

int SVGdraw_drawLine(SVGdraw *self, double x1, double y1, double x2, double y2) {
    struct SVGdraw_impl *d = self->impl;
    checkArg(d != NULL && d->isActive, "Po zavolani funkcie finish uz nie je mozne vykreslovat");
    fprintf(d->svg, "<line id=\"item%d\" x1=\"%g\" y1=\"%g\" x2=\"%g\" y2=\"%g\" ",
            nextItemId(d), x1, y1, x2, y2);
    printStyle(d);
    fprintf(d->svg, " />\n");
    return addItem(d);
}

int SVGdraw_drawText(SVGdraw *self, double x, double y, const char* text,
                     const char* justification) {
    struct SVGdraw_impl *d = self->impl;
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

void SVGdraw_startPolygon(SVGdraw *self, double x, double y) {
    self->impl->polygonCount = 0;
    SVGdraw_addPolygonPoint(self, x, y);
}

void SVGdraw_addPolygonPoint(SVGdraw *self, double x, double y) {
    struct SVGdraw_impl *d = self->impl;
    pushPair(&d->polygon, &d->polygonCount, &d->polygonCap, x, y);
}

int SVGdraw_drawPolygon(SVGdraw *self) {
    struct SVGdraw_impl *d = self->impl;
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

void SVGdraw_setLineColorRGB(SVGdraw *self, int r, int g, int b) {
    formatRGBColor(self->impl->lineColor, SVGDRAW_COLOR_MAX, r, g, b);
}

void SVGdraw_setLineColor(SVGdraw *self, const char* color) {
    setColorString(self->impl->lineColor, color);
}

void SVGdraw_setFillColorRGB(SVGdraw *self, int r, int g, int b) {
    formatRGBColor(self->impl->fillColor, SVGDRAW_COLOR_MAX, r, g, b);
}

void SVGdraw_setFillColor(SVGdraw *self, const char* color) {
    const char *c = color;
    while ((*c) != 0) {
        checkArg(islower((unsigned char) *c), "Meno farby musi pozostavat iba z malych pismen");
        c++;
    }
    setColorString(self->impl->fillColor, color);
}

void SVGdraw_setNoFill(SVGdraw *self) {
    strcpy(self->impl->fillColor, "none");
}

void SVGdraw_setFontSize(SVGdraw *self, double size) {
    checkArg(size > 0, "Velkost fontu musi byt kladna");
    self->impl->fontSize = size;
}

void SVGdraw_setLineWidth(SVGdraw *self, double width) {
    checkArg(width > 0, "Sirka ciary musi byt kladna");
    self->impl->lineWidth = width;
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

void Turtle_init(Turtle *self, int width, int height, const char* filename,
                 int x, int y, double angle) {
    struct Turtle_impl *d = malloc(sizeof(struct Turtle_impl));
    checkArg(d != NULL, "Nedostatok pamate");
    d->x = x;
    d->y = y;
    d->angle = angle;
    d->pathLength = 0;
    d->speed = 100;
    d->isActive = 1;
    self->impl = d;

    d->svg = fopen(filename, "w");
    checkArg(d->svg != NULL, "Nepodarilo sa otvorit subor na zapis");
    initSVG(d->svg, width, height);
    fprintf(d->svg, "<path fill=\"none\" stroke=\"black\" id=\"turtlepath\"  d=\"");
    fprintf(d->svg, "M %g %g", d->x, d->y);
}

void Turtle_finish_without_destroy(Turtle *self) {
    struct Turtle_impl *d = self->impl;
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

void Turtle_destroy(Turtle *self) {
    if (self == NULL) {
        return;
    }
    struct Turtle_impl *d = self->impl;
    if (d == NULL) {
        return;
    }
    if (d->isActive) {
        Turtle_finish_without_destroy(self);
    }
    free(d);
    self->impl = NULL;
}

void Turtle_finish(Turtle *self) {
    Turtle_finish_without_destroy(self);
    Turtle_destroy(self);
}

void Turtle_setSpeed(Turtle *self, double speed) {
    checkArg(speed > 0, "Rychlost korytnacky musi byt kladna");
    self->impl->speed = speed;
}

void Turtle_forward(Turtle *self, double length) {
    struct Turtle_impl *d = self->impl;
    double x = d->x + length * cos(d->angle * DEGREES_RATIO);
    double y = d->y - length * sin(d->angle * DEGREES_RATIO);

    Turtle_goTo(self, x, y);
}

void Turtle_turnLeft(Turtle *self, double angle) {
    self->impl->angle += angle;
}

void Turtle_turnRight(Turtle *self, double angle) {
    self->impl->angle -= angle;
}

void Turtle_goTo(Turtle *self, double x, double y) {
    struct Turtle_impl *d = self->impl;
    checkArg(d != NULL && d->isActive, "Po zavolani funkcie finish uz nie je mozne posuvat korytnacku");
    double dx = x - d->x;
    double dy = y - d->y;
    d->pathLength += sqrt(dx * dx + dy * dy);
    d->x = x;
    d->y = y;
    fprintf(d->svg, " L %g %g", d->x, d->y);
}
