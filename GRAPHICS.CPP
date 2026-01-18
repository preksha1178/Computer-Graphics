#include <graphics.h>
#include <conio.h>
#include <iostream.h>
#include <stdlib.h>
#include <math.h>

/* ---------- LINE DRAWING ---------- */
void dda_line(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xinc = dx / (float)steps;
    float yinc = dy / (float)steps;
    float x = x1, y = y1;
    for(int i=0;i<=steps;i++) {
        putpixel((int)(x+0.5),(int)(y+0.5),WHITE);
        x+=xinc; y+=yinc;
    }
}

void bresenham_line(int x1,int y1,int x2,int y2) {
    int dx = abs(x2-x1), dy = abs(y2-y1);
    int sx = (x2>x1)?1:-1, sy = (y2>y1)?1:-1;
    int err = dx - dy;
    while(1) {
        putpixel(x1,y1,WHITE);
        if(x1==x2 && y1==y2) break;
        int e2 = 2*err;
        if(e2>-dy){ err-=dy; x1+=sx; }
        if(e2<dx){ err+=dx; y1+=sy; }
    }
}

/* ---------- CIRCLE DRAWING ---------- */
void midpoint_circle(int xc,int yc,int r) {
    int x=0, y=r, p=1-r;
    while(x<=y) {
        putpixel(xc+x,yc+y,WHITE); putpixel(xc-x,yc+y,WHITE);
        putpixel(xc+x,yc-y,WHITE); putpixel(xc-x,yc-y,WHITE);
        putpixel(xc+y,yc+x,WHITE); putpixel(xc-y,yc+x,WHITE);
        putpixel(xc+y,yc-x,WHITE); putpixel(xc-y,yc-x,WHITE);
        x++;
        if(p<0) p+=2*x+1; else{ y--; p+=2*(x-y)+1; }
    }
}

void bresenham_circle(int xc,int yc,int r) {
    int x=0, y=r, d=3-2*r;
    while(x<=y) {
        putpixel(xc+x,yc+y,WHITE); putpixel(xc-x,yc+y,WHITE);
        putpixel(xc+x,yc-y,WHITE); putpixel(xc-x,yc-y,WHITE);
        putpixel(xc+y,yc+x,WHITE); putpixel(xc-y,yc+x,WHITE);
        putpixel(xc+y,yc-x,WHITE); putpixel(xc-y,yc-x,WHITE);
        if(d<0) d+=4*x+6; else{ d+=4*(x-y)+10; y--; }
        x++;
    }
}

/* ---------- ELLIPSE ---------- */
void draw_ellipse(int xc,int yc,int rx,int ry) {
    float dx, dy, d1, d2;
    int x=0, y=ry;
    d1 = ry*ry - rx*rx*ry + 0.25*rx*rx;
    dx = 2*ry*ry*x; dy=2*rx*rx*y;
    while(dx<dy) {
        putpixel(xc+x,yc+y,WHITE); putpixel(xc-x,yc+y,WHITE);
        putpixel(xc+x,yc-y,WHITE); putpixel(xc-x,yc-y,WHITE);
        if(d1<0){ x++; dx+=2*ry*ry; d1+=dx+ry*ry; }
        else{ x++; y--; dx+=2*ry*ry; dy-=2*rx*rx; d1+=dx-dy+ry*ry; }
    }
    d2 = ry*ry*(x+0.5)*(x+0.5)+rx*rx*(y-1)*(y-1)-rx*rx*ry*ry;
    while(y>=0){
        putpixel(xc+x,yc+y,WHITE); putpixel(xc-x,yc+y,WHITE);
        putpixel(xc+x,yc-y,WHITE); putpixel(xc-x,yc-y,WHITE);
        if(d2>0){ y--; dy-=2*rx*rx; d2+=rx*rx-dy; }
        else{ y--; x++; dx+=2*ry*ry; dy-=2*rx*rx; d2+=dx-dy+rx*rx; }
    }
}

/* ---------- RECTANGLE ---------- */
void draw_rectangle(int x1,int y1,int x2,int y2){ rectangle(x1,y1,x2,y2); }

/* ---------- TRIANGLE ---------- */
void draw_triangle(int x1,int y1,int x2,int y2,int x3,int y3){
    line(x1,y1,x2,y2); line(x2,y2,x3,y3); line(x3,y3,x1,y1);
}

/* ---------- MAIN ---------- */
void main() {
    int gd=DETECT, gm;
    initgraph(&gd,&gm,"C:\\TURBOC3\\BGI");

    int choice;
    do {
        // Console menu
	clrscr();
        cout<<"\n==== COMPUTER GRAPHICS MENU ====\n";
        cout<<"1. Line Drawing\n2. Circle Drawing\n3. Ellipse Drawing\n4. Rectangle Drawing\n5. Triangle Drawing\n6. Exit\n";
        cout<<"Enter your choice: "; cin>>choice;

        cleardevice();

        switch(choice){
            case 1:{
                int line_choice,x1,y1,x2,y2;
                cout<<"1. DDA Line\n2. Bresenham Line\nEnter choice: "; cin>>line_choice;
                cout<<"Enter x1 y1: "; cin>>x1>>y1;
                cout<<"Enter x2 y2: "; cin>>x2>>y2;
                cleardevice();
                if(line_choice==1) dda_line(x1,y1,x2,y2);
                else bresenham_line(x1,y1,x2,y2);
                break;
            }
            case 2:{
                int circ_choice,xc,yc,r;
                cout<<"1. Midpoint Circle\n2. Bresenham Circle\nEnter choice: "; cin>>circ_choice;
                cout<<"Enter center x y: "; cin>>xc>>yc;
                cout<<"Enter radius: "; cin>>r;
                cleardevice();
                if(circ_choice==1) midpoint_circle(xc,yc,r);
                else bresenham_circle(xc,yc,r);
                break;
            }
            case 3:{
                int xc,yc,rx,ry;
                cout<<"Enter center x y: "; cin>>xc>>yc;
                cout<<"Enter x-radius y-radius: "; cin>>rx>>ry;
                cleardevice();
                draw_ellipse(xc,yc,rx,ry);
                break;
            }
            case 4:{
                int x1,y1,x2,y2;
                cout<<"Enter top-left x y and bottom-right x y: "; cin>>x1>>y1>>x2>>y2;
                cleardevice();
                draw_rectangle(x1,y1,x2,y2);
                break;
            }
            case 5:{
                int x1,y1,x2,y2,x3,y3;
                cout<<"Enter three vertices x1 y1 x2 y2 x3 y3: "; cin>>x1>>y1>>x2>>y2>>x3>>y3;
                cleardevice();
                draw_triangle(x1,y1,x2,y2,x3,y3);
                break;
            }
            case 6: closegraph(); exit(0);
            default: cout<<"Invalid choice!\n"; break;
        }

        outtextxy(10, getmaxy() - 20, "Press any key to continue...");getch();

        cleardevice();

    }while(1);

    closegraph();
}
