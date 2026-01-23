#include <graphics.h>
#include <conio.h>
#include <iostream.h>
#include <stdlib.h>
#include <math.h>

/* ================= TRANSFORMATIONS ================= */

void translate_point(int &x, int &y, int tx, int ty) {
    x += tx;
    y += ty;
}

// Scale relative to center cx, cy
void scale_point(int &x, int &y, float sx, float sy, int cx, int cy) {
    x = (int)(cx + (x - cx) * sx);
    y = (int)(cy + (y - cy) * sy);
}

// Rotate around center cx, cy
void rotate_point(int &x, int &y, float angle, int cx, int cy) {
    float rad = angle * 3.14159 / 180.0;
    int xr = (int)(cx + (x - cx) * cos(rad) - (y - cy) * sin(rad));
    int yr = (int)(cy + (x - cx) * sin(rad) + (y - cy) * cos(rad));
    x = xr;
    y = yr;
}

/* ================= LINE DRAWING ================= */

void dda_line(int x1, int y1, int x2, int y2, int color) {
    int dx = x2 - x1, dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    if (steps == 0) {
        putpixel(x1, y1, color);
        return;
    }
    float xi = dx / (float)steps;
    float yi = dy / (float)steps;
    float x = x1, y = y1;
    for (int i = 0; i <= steps; i++) {
        putpixel((int)(x + 0.5), (int)(y + 0.5), color);
        x += xi; y += yi;
    }
}

void bresenham_line(int x1, int y1, int x2, int y2, int color) {
    int dx = abs(x2 - x1), dy = abs(y2 - y1);
    int sx = (x2 > x1) ? 1 : ((x2 < x1) ? -1 : 0);
    int sy = (y2 > y1) ? 1 : ((y2 < y1) ? -1 : 0);
    int err = dx - dy;
    while (1) {
        putpixel(x1, y1, color);
        if (x1 == x2 && y1 == y2) break;
        int e2 = 2 * err;
        if (e2 > -dy) { err -= dy; x1 += sx; }
        if (e2 < dx) { err += dx; y1 += sy; }
    }
}

/* ================= CIRCLE ================= */

void midpoint_circle(int xc, int yc, int r, int color) {
    int x = 0, y = r, p = 1 - r;
    while (x <= y) {
        putpixel(xc + x, yc + y, color); putpixel(xc - x, yc + y, color);
        putpixel(xc + x, yc - y, color); putpixel(xc - x, yc - y, color);
        putpixel(xc + y, yc + x, color); putpixel(xc - y, yc + x, color);
        putpixel(xc + y, yc - x, color); putpixel(xc - y, yc - x, color);
        x++;
        if (p < 0) p += 2 * x + 1; else { y--; p += 2 * (x - y) + 1; }
    }
}

void bresenham_circle(int xc, int yc, int r, int color) {
    int x = 0, y = r, d = 3 - 2 * r;
    while (x <= y) {
        putpixel(xc + x, yc + y, color); putpixel(xc - x, yc + y, color);
        putpixel(xc + x, yc - y, color); putpixel(xc - x, yc - y, color);
        putpixel(xc + y, yc + x, color); putpixel(xc - y, yc + x, color);
        putpixel(xc + y, yc - x, color); putpixel(xc - y, yc - x, color);
        if (d < 0) d += 4 * x + 6; else { d += 4 * (x - y) + 10; y--; }
        x++;
    }
}

/* ================= ELLIPSE ================= */

void midpoint_ellipse(int xc, int yc, int rx, int ry, int color) {
    long x = 0, y = ry;
    long rx2 = rx * rx;
    long ry2 = ry * ry;
    long dx = 0;
    long dy = 2 * rx2 * y;

    long d1 = ry2 - rx2 * ry + (rx2 / 4);

    /* REGION 1 */
    while (dx < dy) {
        putpixel(xc + x, yc + y, color);
        putpixel(xc - x, yc + y, color);
        putpixel(xc + x, yc - y, color);
        putpixel(xc - x, yc - y, color);

        if (d1 < 0) {
            x++;
            dx += 2 * ry2;
            d1 += dx + ry2;
        } else {
            x++;
            y--;
            dx += 2 * ry2;
            dy -= 2 * rx2;
            d1 += dx - dy + ry2;
        }
    }

    /* REGION 2 (INTEGER SAFE) */
    long d2 = (ry2 * x * x) +
              (ry2 * x) +
              (rx2 * (y - 1) * (y - 1)) -
              (rx2 * ry2);

    while (y >= 0) {
        putpixel(xc + x, yc + y, color);
        putpixel(xc - x, yc + y, color);
        putpixel(xc + x, yc - y, color);
        putpixel(xc - x, yc - y, color);

        if (d2 > 0) {
            y--;
            dy -= 2 * rx2;
            d2 += rx2 - dy;
        } else {
            y--;
            x++;
            dx += 2 * ry2;
            dy -= 2 * rx2;
            d2 += dx - dy + rx2;
        }
    }
}

/* ================= RECTANGLE ================= */

void draw_rect(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, int color) {
    setcolor(color);
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x4, y4);
    line(x4, y4, x1, y1);
    setcolor(WHITE);
}

/* ================= TRIANGLE ================= */

void draw_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int color) {
    setcolor(color);
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x1, y1);
    setcolor(WHITE);
}

/* ================= MAIN ================= */

void main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    char cont = 'y';
    do {
        cleardevice();

        int choice;
        cout << "\n==== COMPUTER GRAPHICS MENU ====\n";
        cout << "1.Line  2.Circle  3.Ellipse  4.Rectangle  5.Triangle  6.Exit  Choice: ";
        cin >> choice;

        if (choice == 6) break;

        cleardevice();

        /* ---------- LINE ---------- */
        if (choice == 1) {
            int algo, x1, y1, x2, y2;
            cout << "1.DDA  2.Bresenham: "; cin >> algo;
            cout << "Enter x1 y1 x2 y2: "; cin >> x1 >> y1 >> x2 >> y2;

            if (algo == 1) dda_line(x1, y1, x2, y2, WHITE); else bresenham_line(x1, y1, x2, y2, WHITE);

            char trans_cont = 'd';
            do {
                int t; cout << "1.Translate 2.Scale 3.Rotate: "; cin >> t;
                int cx = (x1 + x2) / 2, cy = (y1 + y2) / 2;

                int tx1 = x1, ty1 = y1, tx2 = x2, ty2 = y2;

                if (t == 1) { int tx, ty; cout << "tx ty: "; cin >> tx >> ty; translate_point(tx1, ty1, tx, ty); translate_point(tx2, ty2, tx, ty); }
                if (t == 2) { float sx, sy; cout << "sx sy: "; cin >> sx >> sy; scale_point(tx1, ty1, sx, sy, cx, cy); scale_point(tx2, ty2, sx, sy, cx, cy); }
                if (t == 3) { float a; cout << "angle: "; cin >> a; rotate_point(tx1, ty1, a, cx, cy); rotate_point(tx2, ty2, a, cx, cy); }

                if (algo == 1) dda_line(tx1, ty1, tx2, ty2, RED); else bresenham_line(tx1, ty1, tx2, ty2, RED);

                cout << "Do you want to continue from starting (s) or with same coordinates with different option (d)? ";
                cin >> trans_cont;
            } while (trans_cont == 'd' || trans_cont == 'D');
        }

        /* ---------- CIRCLE ---------- */
        else if (choice == 2) {
            int algo, xc, yc, r;
            cout << "1.Midpoint 2.Bresenham: "; cin >> algo;
            cout << "Enter xc yc r: "; cin >> xc >> yc >> r;

            if (algo == 1) midpoint_circle(xc, yc, r, WHITE); else bresenham_circle(xc, yc, r, WHITE);

            char trans_cont = 'd';
            do {
                int t; cout << "1.Translate 2.Scale: "; cin >> t;
                int txc = xc, tyc = yc, tr = r;

                if (t == 1) { int tx, ty; cout << "tx ty: "; cin >> tx >> ty; translate_point(txc, tyc, tx, ty); }
                if (t == 2) { float s; cout << "scale s: "; cin >> s; tr = (int)(tr * s); }

                if (algo == 1) midpoint_circle(txc, tyc, tr, RED); else bresenham_circle(txc, tyc, tr, RED);

                cout << "Do you want to continue from starting (s) or with same coordinates with different option (d)? ";
                cin >> trans_cont;
            } while (trans_cont == 'd' || trans_cont == 'D');
        }

        /* ---------- ELLIPSE ---------- */
        else if (choice == 3) {
            int xc, yc, rx, ry;
            cout << "Enter xc yc rx ry: "; cin >> xc >> yc >> rx >> ry;

            midpoint_ellipse(xc, yc, rx, ry, WHITE);

            char trans_cont = 'd';
            do {
                int t; cout << "1.Translate 2.Scale: "; cin >> t;
                int txc = xc, tyc = yc, trx = rx, tryy = ry;

                if (t == 1) { int tx, ty; cout << "tx ty: "; cin >> tx >> ty; translate_point(txc, tyc, tx, ty); }
                if (t == 2) { float s; cout << "scale s: "; cin >> s; trx = (int)(trx * s); tryy = (int)(tryy * s); }

                midpoint_ellipse(txc, tyc, trx, tryy, RED);

                cout << "Do you want to continue from starting (s) or with same coordinates with different option (d)? ";
                cin >> trans_cont;
            } while (trans_cont == 'd' || trans_cont == 'D');
        }

        /* ---------- RECTANGLE ---------- */
        else if (choice == 4) {
            int x1, y1, x3, y3, x2, y2, x4, y4;
            cout << "Enter top-left x y: "; cin >> x1 >> y1;
            cout << "Enter bottom-right x y: "; cin >> x3 >> y3;
            x2 = x3; y2 = y1; x4 = x1; y4 = y3;

            draw_rect(x1, y1, x2, y2, x3, y3, x4, y4, WHITE);

            char trans_cont = 'd';
            do {
                int t; cout << "1.Translate 2.Scale 3.Rotate: "; cin >> t;
                int cx = (x1 + x3) / 2, cy = (y1 + y3) / 2;

                int tx1 = x1, ty1 = y1, tx2 = x2, ty2 = y2, tx3 = x3, ty3 = y3, tx4 = x4, ty4 = y4;

                if (t == 1) { int tx, ty; cout << "tx ty: "; cin >> tx >> ty; translate_point(tx1, ty1, tx, ty); translate_point(tx2, ty2, tx, ty); translate_point(tx3, ty3, tx, ty); translate_point(tx4, ty4, tx, ty); }
                if (t == 2) { float sx, sy; cout << "sx sy: "; cin >> sx >> sy; scale_point(tx1, ty1, sx, sy, cx, cy); scale_point(tx2, ty2, sx, sy, cx, cy); scale_point(tx3, ty3, sx, sy, cx, cy); scale_point(tx4, ty4, sx, sy, cx, cy); }
                if (t == 3) { float a; cout << "angle: "; cin >> a; rotate_point(tx1, ty1, a, cx, cy); rotate_point(tx2, ty2, a, cx, cy); rotate_point(tx3, ty3, a, cx, cy); rotate_point(tx4, ty4, a, cx, cy); }

                draw_rect(tx1, ty1, tx2, ty2, tx3, ty3, tx4, ty4, RED);

                cout << "Do you want to continue from starting (s) or with same coordinates with different option (d)? ";
                cin >> trans_cont;
            } while (trans_cont == 'd' || trans_cont == 'D');
        }

        /* ---------- TRIANGLE ---------- */
        else if (choice == 5) {
            int x1, y1, x2, y2, x3, y3;
            cout << "Enter x1 y1 x2 y2 x3 y3: "; cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

            draw_triangle(x1, y1, x2, y2, x3, y3, WHITE);

            char trans_cont = 'd';
            do {
                int t; cout << "1.Translate 2.Scale 3.Rotate: "; cin >> t;
                int cx = (x1 + x2 + x3) / 3, cy = (y1 + y2 + y3) / 3;

                int tx1 = x1, ty1 = y1, tx2 = x2, ty2 = y2, tx3 = x3, ty3 = y3;

                if (t == 1) { int tx, ty; cout << "tx ty: "; cin >> tx >> ty; translate_point(tx1, ty1, tx, ty); translate_point(tx2, ty2, tx, ty); translate_point(tx3, ty3, tx, ty); }
                if (t == 2) { float sx, sy; cout << "sx sy: "; cin >> sx >> sy; scale_point(tx1, ty1, sx, sy, cx, cy); scale_point(tx2, ty2, sx, sy, cx, cy); scale_point(tx3, ty3, sx, sy, cx, cy); }
                if (t == 3) { float a; cout << "angle: "; cin >> a; rotate_point(tx1, ty1, a, cx, cy); rotate_point(tx2, ty2, a, cx, cy); rotate_point(tx3, ty3, a, cx, cy); }

                draw_triangle(tx1, ty1, tx2, ty2, tx3, ty3, RED);

                cout << "Do you want to continue from starting (s) or with same coordinates with different option (d)? ";
                cin >> trans_cont;
            } while (trans_cont == 'd' || trans_cont == 'D');
        }

        cout << "Do you want to continue? (y/n): ";
        cin >> cont;
    } while (cont == 'y' || cont == 'Y');

    getch();
    closegraph();
}
