
#include "Jupiter.h"
#include "ImageLoader.h"

void Filled_circle(float radius, float xc, float yc, float r, float g, float b) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < 200; i++) {
        glColor3ub(r, g, b);
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = radius;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x + xc, y + yc);
    }
    glEnd();
}

void Empty_circle(float radius, float xc, float yc, float r, float g, float b) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 200; i++) {
        glColor3ub(r, g, b);
        float pi = 3.1416;
        float A = (i * 2 * pi) / 200;
        float r = radius;
        float x = r * cos(A);
        float y = r * sin(A);
        glVertex2f(x + xc, y + yc);
    }
    glEnd();
}

void rock1(float x_location, float y_location, float scale) {
    glBegin(GL_POLYGON);
    glColor3ub(147, 139, 134);

    glVertex2f(x_location + scale * 27.0030268424264, y_location + scale * 54.1635636074607);
    glVertex2f(x_location + scale * 30.8870277422356, y_location + scale * 57.0406013110315);
    glVertex2f(x_location + scale * 35.058732412401, y_location + scale * 57.7598607369242);
    glVertex2f(x_location + scale * 38.798881427032, y_location + scale * 55.314378688889);
    glVertex2f(x_location + scale * 39.3742889677445, y_location + scale * 51.4303777890685);
    glVertex2f(x_location + scale * 35.3464361827572, y_location + scale * 49.5603032817475);
    glVertex2f(x_location + scale * 26.7153230720702, y_location + scale * 50.2795627076402);

    glEnd();
}

void ufo() {
    glBegin(GL_POLYGON);
    glColor3ub(147, 139, 134);

    glVertex2f(150, 135);
    glVertex2f(152.6088723479732, 136.1769205933373);
    glVertex2f(154.7629565264869, 136.9412730437799);
    glVertex2f(157.2644736370189, 137.4971657350109);
    glVertex2f(159.55753098834,   137.8445986670303);
    glVertex2f(161.6421285804501, 138.0530584262419);
    glVertex2f(163.6282664133683, 138.1225440126457);
    glVertex2f(165.5259444870947, 138.0520554262419);
    glVertex2f(167.3351628016292, 137.8415926670303);
    glVertex2f(169.0559213579719, 137.4911557350109);
    glVertex2f(170.6882201561228, 136.9907446301837);
    glVertex2f(172.2320591960819, 136.3403593525487);
    glVertex2f(175, 135);
    glVertex2f(162,125);
    glVertex2f(150,135);
    glEnd();
}

void Building1(float x_location, float y_location, float scale) {
    //main body
    glBegin(GL_POLYGON);
    glColor3ub(169, 70, 21);
    glVertex2f(x_location + scale * 30.2064655125222, y_location + scale * 130.6193965375666);
    glVertex2f(x_location + scale * 40.0800840401481, y_location + scale * 130.7181067441525);
    glVertex2f(x_location + scale * 40, y_location + scale * 100);
    glVertex2f(x_location + scale * 30, y_location + scale * 100);
    glEnd();

    //body glass left
    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(x_location + scale * 31, y_location + scale * 125);
    glVertex2f(x_location + scale * 34, y_location + scale * 125);
    glVertex2f(x_location + scale * 34, y_location + scale * 104);
    glVertex2f(x_location + scale * 31, y_location + scale * 104);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 255);
    glVertex2f(x_location + scale * 31, y_location + scale * 116);
    glVertex2f(x_location + scale * 34, y_location + scale * 116);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 255);
    glVertex2f(x_location + scale * 31, y_location + scale * 110);
    glVertex2f(x_location + scale * 34, y_location + scale * 110);
    glEnd();

    //body glass right
    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(x_location + scale * 36, y_location + scale * 125);
    glVertex2f(x_location + scale * 39, y_location + scale * 125);
    glVertex2f(x_location + scale * 39, y_location + scale * 104);
    glVertex2f(x_location + scale * 36, y_location + scale * 104);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 255);
    glVertex2f(x_location + scale * 36, y_location + scale * 116);
    glVertex2f(x_location + scale * 39, y_location + scale * 116);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 255);
    glVertex2f(x_location + scale * 36, y_location + scale * 110);
    glVertex2f(x_location + scale * 39, y_location + scale * 110);
    glEnd();

    //bottom part
    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(x_location + scale * 30, y_location + scale * 100);
    glVertex2f(x_location + scale * 40, y_location + scale * 100);
    glVertex2f(x_location + scale * 50, y_location + scale * 95);
    glVertex2f(x_location + scale * 20, y_location + scale * 95);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 255);
    glVertex2f(x_location + scale * 35, y_location + scale * 129.8415129770023);
    glVertex2f(x_location + scale * 35, y_location + scale * 100);
    glEnd();

    //upper circle
    Filled_circle(scale * 15.15848702, x_location + scale * 35, y_location + scale * 145, 243, 153, 5);
    Empty_circle(scale * 15.15848702, x_location + scale * 35, y_location + scale * 145, 0, 0, 0);

    glBegin(GL_LINES);
    glColor3ub(255, 255, 255);
    glVertex2f(x_location + scale * 20.6933, y_location + scale * 150);
    glVertex2f(x_location + scale * 49.3067, y_location + scale * 150);
    glEnd();

    glBegin(GL_LINES);
    glColor3ub(255, 255, 255);
    glVertex2f(x_location + scale * 20.6933, y_location + scale * 139.9895);
    glVertex2f(x_location + scale * 49.3088, y_location + scale * 139.9895);
    glEnd();

    //middle glass
    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(x_location + scale * 24, y_location + scale * 148);
    glVertex2f(x_location + scale * 46, y_location + scale * 148);
    glVertex2f(x_location + scale * 46, y_location + scale * 142);
    glVertex2f(x_location + scale * 24, y_location + scale * 142);
    glEnd();

    //upper glass
    glBegin(GL_TRIANGLES);
    glColor3ub(0, 0, 0);
    glVertex2f(x_location + scale * 29, y_location + scale * 156);
    glVertex2f(x_location + scale * 32, y_location + scale * 152);
    glVertex2f(x_location + scale * 26, y_location + scale * 152);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3ub(0, 0, 0);
    glVertex2f(x_location + scale * 41, y_location + scale * 156);
    glVertex2f(x_location + scale * 44, y_location + scale * 152);
    glVertex2f(x_location + scale * 38, y_location + scale * 152);
    glEnd();

    //lower glass
    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(x_location + scale * 26, y_location + scale * 138);
    glVertex2f(x_location + scale * 30, y_location + scale * 138);
    glVertex2f(x_location + scale * 30, y_location + scale * 134);
    glVertex2f(x_location + scale * 26, y_location + scale * 134);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(x_location + scale * 33, y_location + scale * 138);
    glVertex2f(x_location + scale * 37, y_location + scale * 138);
    glVertex2f(x_location + scale * 37, y_location + scale * 134);
    glVertex2f(x_location + scale * 33, y_location + scale * 134);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);
    glVertex2f(x_location + scale * 40, y_location + scale * 138);
    glVertex2f(x_location + scale * 44, y_location + scale * 138);
    glVertex2f(x_location + scale * 44, y_location + scale * 134);
    glVertex2f(x_location + scale * 40, y_location + scale * 134);
    glEnd();
}


void road() {
    glBegin(GL_POLYGON);
    glColor3ub(98, 56, 18 );
    glVertex2f(0, 40);
    glVertex2f(300, 40);
    glVertex2f(300, 10);
    glVertex2f(0, 10);
    glEnd();
}


void display() {
    glPointSize(5.0);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (background)

    /*glBegin(GL_POLYGON);
    glColor3ub(29, 135, 255);//light blue
    glVertex2f(150,200);
    glColor3ub(20,29,130);//dark blue
    glVertex2f(300,200);
    glColor3ub(130,20,113);//purple
    glVertex2f(300,80);
    glColor3ub(147,213,237);//sky blue
    glVertex2f(300,0);
    glColor3ub(147,213,237);//sky blue
    glVertex2f(0,0);
    glColor3ub(130,20,113);//purple
    glVertex2f(0,65);
    glColor3ub(20,29,130);//dark blue
    glVertex2f(0,200);
    glColor3ub(29, 135, 255);//light blue
    glVertex2f(150,200);
*/

    glEnd();

    //Surface ID:- 0001
    Filled_circle(677.471962326, 148.8280851977981, -600.8887453335378, 155, 56, 6);


    //Building1 ID:- 0002
    Building1(30, 22, 0.8);
    //Building1 ID:- 0003
    Building1(0, 0, 1);


    //rock10 ID:- 0004
    rock1(-5, 10, 0.9);
    //rock1 ID:- 0005
    rock1(0, 0, 1);
    //rock12 ID:- 0006
    rock1(-10, 10, 0.8);
    //rock13 ID:- 0007
    rock1(12, 5, 1);
    //rock14 ID:- 0008
    rock1(15, 3, 0.9);

    ufo();

    //road
    road();


    glutSwapBuffers(); // Swap the front and back frame buffers (double buffering)
}
