#include <GL/glut.h>
#include <math.h>
#include <iostream>
using namespace std;

#define FPS 120
#define TO_RADIANS 3.14/180.0

//  Anggota Kelompok 3
//  A. ADJI MAULANA ASROR (672020085)
//  B. YEHESKIEL HENCY ARDIANTO (672020086)
//  C. MAHARANI PUTRI SANTOSO (672020088)
//  D. MARTHEN BILLY JESAJAS (672020094)
//  E. ADELLIYA DEWI SAPUTRI (672020107)

const int width = 1280;
const int height = 720;
int i;
float sudut;
double x_geser, y_geser, z_geser;

float pitch = 0.0, yaw = 0.0;
float camX = 0.0, camZ = 0.0, terbang = 25.0;

void display();
void reshape(int w, int h);
void timer(int);
void passive_motion(int, int);
void camera();
void keyboard(unsigned char key, int x, int y);
void keyboard_up(unsigned char key, int x, int y);

struct Motion {
    bool Forward, Backward, Left, Right, Naik, Turun;
};
Motion motion = { false,false,false,false,false,false };

void init() {
    glClearColor(0.529, 0.807, 0.921, 0.0);
    glutSetCursor(GLUT_CURSOR_NONE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthFunc(GL_LEQUAL);
    glutWarpPointer(width / 2, height / 2);
}

void ground() {
    glBegin(GL_QUADS);
    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex3f(-1000.0, 0, -1000.0);

    glColor3f(0.6f, 0.6f, 0.6f);
    glVertex3f(1000.0, 0, -1000.0);

    glColor3f(0.6f, 0.6f, 0.6f);
    glVertex3f(1000.0, 0, 1000.0);

    glColor3f(0.3f, 0.3f, 0.3f);
    glVertex3f(-1000.0, 0, 1000.0);
    glEnd();
}

void draw() {
    // Mulai tuliskan isi pikiranmu disini

    //dinding pondasi depan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0, 50, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-700.0, -50.0, 700.0);
    glVertex3f(-700.0, 50.0, 700.0);
    glVertex3f(700.0, 50.0, 700.0);
    glVertex3f(700.0, -50.0, 700.0);
    glEnd();
    glPopMatrix();

    //dinding pondasi kanan
    glPushMatrix();
    glColor3f(1.0, 0.0, 1.0);
    glTranslatef(0, 50, 0);
    glBegin(GL_POLYGON);
    glVertex3f(700.0, -50.0, -700.0);
    glVertex3f(700.0, 50.0, -700.0);
    glVertex3f(700.0, 50.0, 700.0);
    glVertex3f(700.0, -50.0, 700.0);
    glEnd();
    glPopMatrix();

    //dinding pondasi kiri
    glPushMatrix();
    glColor3f(1.0, 0.0, 1.0);
    glTranslatef(0, 50, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-700.0, -50.0, -700.0);
    glVertex3f(-700.0, 50.0, -700.0);
    glVertex3f(-700.0, 50.0, 700.0);
    glVertex3f(-700.0, -50.0, 700.0);
    glEnd();
    glPopMatrix();

    //dinding pondasi belakang
    glPushMatrix();
    glColor3f(1.0, 0.0, 1.0);
    glTranslatef(0, 50, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-700.0, -50.0, -700.0);
    glVertex3f(-700.0, 50.0, -700.0);
    glVertex3f(700.0, 50.0, -700.0);
    glVertex3f(700.0, -50.0, -700.0);
    glEnd();
    glPopMatrix();

    //alas lantai 1 
    glPushMatrix();
    glColor3f(0.79, 0.73, 0.78);
    glTranslatef(0, 150, 0);
    glBegin(GL_POLYGON);
    glVertex3f(700.0, -50.0, 700.0);
    glVertex3f(700.0, -50.0, -700.0);
    glVertex3f(-700.0, -50.0, -700.0);
    glVertex3f(-700.0, -50.0, 700.0);
    glEnd();
    glPopMatrix();

    //dinding depan lantai 1 
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0, 100, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-500.0, -50.0, 500.0);
    glVertex3f(-500.0, 300.0, 500.0);
    glVertex3f(500.0, 300.0, 500.0);
    glVertex3f(500.0, -50.0, 500.0);
    glEnd();
    glPopMatrix();

    //dinding  kanan lantai 1
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0, 100, 0);
    glBegin(GL_POLYGON);
    glVertex3f(500.0, -50.0, -500.0);
    glVertex3f(500.0, 300.0, -500.0);
    glVertex3f(500.0, 300.0, 500.0);
    glVertex3f(500.0, -50.0, 500.0);
    glEnd();
    glPopMatrix();

    //dinding kiri lantai 1
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0, 100, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-500.0, -50.0, -500.0);
    glVertex3f(-500.0, 300.0, -500.0);
    glVertex3f(-500.0, 300.0, 500.0);
    glVertex3f(-500.0, -50.0, 500.0);
    glEnd();
    glPopMatrix();

    //dinding belakang lantai 1
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0, 100, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-500.0, -50.0, -500.0);
    glVertex3f(-500.0, 300.0, -500.0);
    glVertex3f(500.0, 300.0, -500.0);
    glVertex3f(500.0, -50.0, -500.0);
    glEnd();
    glPopMatrix();

    //atap lantai 1 
    glPushMatrix();
    glColor3f(0.79, 0.73, 0.78);
    glTranslatef(0, 150, 0);
    glBegin(GL_POLYGON);
    glVertex3f(700.0, 250.0, 700.0);
    glVertex3f(700.0, 250.0, -700.0);
    glVertex3f(-700.0, 250.0, -700.0);
    glVertex3f(-700.0, 250.0, 700.0);
    glEnd();
    glPopMatrix();

    //alas lantai (2)
    glPushMatrix();
    glColor3f(0.79, 0.73, 0.78);
    glTranslatef(0, 150, 0);
    glBegin(GL_POLYGON);
    glVertex3f(700.0, 301.0, 700.0);
    glVertex3f(700.0, 301.0, -700.0);
    glVertex3f(-700.0, 301.0, -700.0);
    glVertex3f(-700.0, 301.0, 700.0);
    glEnd();
    glPopMatrix();


    //didnding atap depan lantai 1 
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(0, 450, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-700.0, -50.0, 700.0);
    glVertex3f(-700.0, 5.0, 700.0);
    glVertex3f(700.0, 5.0, 700.0);
    glVertex3f(700.0, -50.0, 700.0);
    glEnd();
    glPopMatrix();

    //dinding kanan atap lantai 1
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(0, 450, 0);
    glBegin(GL_POLYGON);
    glVertex3f(700.0, -50.0, -700.0);
    glVertex3f(700.0, 5.0, -700.0);
    glVertex3f(700.0, 5.0, 700.0);
    glVertex3f(700.0, -50.0, 700.0);
    glEnd();
    glPopMatrix();

    //dinding atap kiri lantai 1
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(0, 450, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-700.0, -50.0, -700.0);
    glVertex3f(-700.0, 5.0, -700.0);
    glVertex3f(-700.0, 5.0, 700.0);
    glVertex3f(-700.0, -50.0, 700.0);
    glEnd();
    glPopMatrix();

    //dinding atap belakang lantai 1
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(0, 450, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-700.0, -50.0, -700.0);
    glVertex3f(-700.0, 5.0, -700.0);
    glVertex3f(700.0, 5.0, -700.0);
    glVertex3f(700.0, -50.0, -700.0);
    glEnd();
    glPopMatrix();


    //dinding depan lantai 2
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0, 450, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-350.0, -50.0, 350.0);
    glVertex3f(-350.0, 400.0, 350.0);
    glVertex3f(350.0, 400.0, 350.0);
    glVertex3f(350.0, -50.0, 350.0);
    glEnd();
    glPopMatrix();

    //dinding  kanan lantai 2
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0, 450, 0);
    glBegin(GL_POLYGON);
    glVertex3f(350.0, -50.0, -350.0);
    glVertex3f(350.0, 400.0, -350.0);
    glVertex3f(350.0, 400.0, 350.0);
    glVertex3f(350.0, -50.0, 350.0);
    glEnd();
    glPopMatrix();

    //dinding kiri lantai 2
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0, 450, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-350.0, -50.0, -350.0);
    glVertex3f(-350.0, 400.0, -350.0);
    glVertex3f(-350.0, 400.0, 350.0);
    glVertex3f(-350.0, -50.0, 350.0);
    glEnd();
    glPopMatrix();

    //dinding belakang lantai 2
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0, 450, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-350.0, -50.0, -350.0);
    glVertex3f(-350.0, 400.0, -350.0);
    glVertex3f(350.0, 400.0, -350.0);
    glVertex3f(350.0, -50.0, -350.0);
    glEnd();
    glPopMatrix();

    //atap lantai (2)
    glPushMatrix();
    glColor3f(0.79, 0.73, 0.78);
    glTranslatef(0, 620, 0);
    glBegin(GL_POLYGON);
    glVertex3f(450.0, 231.0, 450.0);
    glVertex3f(450.0, 231.0, -450.0);
    glVertex3f(-450.0, 231.0, -450.0);
    glVertex3f(-450.0, 231.0, 450.0);
    glEnd();
    glPopMatrix();

    //atap lantai (2)
    glPushMatrix();
    glColor3f(0.79, 0.73, 0.78);
    glTranslatef(0, 620, 0);
    glBegin(GL_POLYGON);
    glVertex3f(450.0, 260.0, 450.0);
    glVertex3f(450.0, 260.0, -450.0);
    glVertex3f(-450.0, 260.0, -450.0);
    glVertex3f(-450.0, 260.0, 450.0);
    glEnd();
    glPopMatrix();

    //didnding atap depan lantai 2 
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(0, 880, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-450.0, -50.0, 450.0);
    glVertex3f(-450.0, 5.0, 450.0);
    glVertex3f(450.0, 5.0, 450.0);
    glVertex3f(450.0, -50.0, 450.0);
    glEnd();
    glPopMatrix();

    //dinding kanan atap lantai 2
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(0, 880, 0);
    glBegin(GL_POLYGON);
    glVertex3f(450.0, -50.0, -450.0);
    glVertex3f(450.0, 5.0, -450.0);
    glVertex3f(450.0, 5.0, 450.0);
    glVertex3f(450.0, -50.0, 450.0);
    glEnd();
    glPopMatrix();

    //dinding atap kiri lantai 2
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(0, 880, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-450.0, -50.0, -450.0);
    glVertex3f(-450.0, 5.0, -450.0);
    glVertex3f(-450.0, 5.0, 450.0);
    glVertex3f(-450.0, -50.0, 450.0);
    glEnd();
    glPopMatrix();

    //dinding atap belakang lantai 2
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(0, 880, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-450.0, -50.0, -450.0);
    glVertex3f(-450.0, 5.0, -450.0);
    glVertex3f(450.0, 5.0, -450.0);
    glVertex3f(450.0, -50.0, -450.0);
    glEnd();
    glPopMatrix();


    //pelafon lantai 1
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(0, 500, 0);
    glBegin(GL_POLYGON);
    glVertex3f(550.0, 260.0, 550.0);
    glVertex3f(550.0, 260.0, -550.0);
    glVertex3f(-550.0, 260.0, -550.0);
    glVertex3f(-550.0, 260.0, 550.0);
    glEnd();
    glPopMatrix();

    //atap miring depan l2
    glPushMatrix();
    glColor3f(0.79, 0.73, 0.78);
    glTranslatef(0, 810, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-550.0, -50.0, 550.0);
    glVertex3f(-300.0, 50.0, 275.0);
    glVertex3f(300.0, 50.0, 275.0);
    glVertex3f(550.0, -50.0, 550.0);
    glEnd();
    glPopMatrix();

    //atap miring kanan l2
    glPushMatrix();
    glColor3f(0.79, 0.73, 0.78);
    glTranslatef(0, 810, 0);
    glBegin(GL_POLYGON);
    glVertex3f(550.0, -50.0, -550.0);
    glVertex3f(300.0, 50.0, -275.0);
    glVertex3f(300.0, 50.0, 275.0);
    glVertex3f(550.0, -50.0, 550.0);
    glEnd();
    glPopMatrix();

    //atap miring kiri l2
    glPushMatrix();
    glColor3f(0.79, 0.73, 0.78);
    glTranslatef(0, 810, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-550.0, -50.0, -550.0);
    glVertex3f(-300.0, 50.0, -275.0);
    glVertex3f(-300.0, 50.0, 275.0);
    glVertex3f(-550.0, -50.0, 550.0);
    glEnd();
    glPopMatrix();

    //atap miring depan l2
    glPushMatrix();
    glColor3f(0.79, 0.73, 0.78);
    glTranslatef(0, 810, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-550.0, -50.0, -550.0);
    glVertex3f(-300.0, 50.0, -275.0);
    glVertex3f(300.0, 50.0, -275.0);
    glVertex3f(550.0, -50.0, -550.0);
    glEnd();
    glPopMatrix();

    //tiang l1 depan t1
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-650, 100, 650);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 kanan
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-650, 100, 650);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 kiri
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-650, 100, 650);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 belakang
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-650, 100, 650);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();


    //tiang l1 depan t2
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-500, 100, 500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 0.0, 10.0);
    glVertex3f(-10.0, 660.0, 10.0);
    glVertex3f(10.0, 660.0, 10.0);
    glVertex3f(10.0, 0.0, 10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 kanan
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-500, 100, 500);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, 0.0, -10.0);
    glVertex3f(10.0, 660.0, -10.0);
    glVertex3f(10.0, 660.0, 10.0);
    glVertex3f(10.0, 0.0, 10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 kiri
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-500, 100, 500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 0.0, -10.0);
    glVertex3f(-10.0, 660.0, -10.0);
    glVertex3f(-10.0, 660.0, 10.0);
    glVertex3f(-10.0, 0.0, 10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 belakang
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-500, 100, 500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 0.0, -10.0);
    glVertex3f(-10.0, 660.0, -10.0);
    glVertex3f(10.0, 660.0, -10.0);
    glVertex3f(10.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 depan t3//
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(500, 100, 500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 0.0, 10.0);
    glVertex3f(-10.0, 660.0, 10.0);
    glVertex3f(10.0, 660.0, 10.0);
    glVertex3f(10.0, 0.0, 10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 kanan
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(500, 100, 500);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, 0.0, -10.0);
    glVertex3f(10.0, 660.0, -10.0);
    glVertex3f(10.0, 660.0, 10.0);
    glVertex3f(10.0, 0.0, 10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 kiri
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(500, 100, 500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 0.0, -10.0);
    glVertex3f(-10.0, 660.0, -10.0);
    glVertex3f(-10.0, 660.0, 10.0);
    glVertex3f(-10.0, 0.0, 10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 belakang
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(500, 100, 500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 0.0, -10.0);
    glVertex3f(-10.0, 660.0, -10.0);
    glVertex3f(10.0, 660.0, -10.0);
    glVertex3f(10.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 depan t4//
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(650, 100, 650);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 kanan
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(650, 100, 650);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, 0.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, 0.0, 10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 kiri
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(650, 100, 650);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 0.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, 0.0, 10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 belakang
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(650, 100, 650);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 0.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 depan t5//
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(650, 100, -650);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 kanan
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(650, 100, -650);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, 0.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, 0.0, 10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 kiri
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(650, 100, -650);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 0.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, 0.0, 10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 belakang
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(650, 100, -650);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 0.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 depan t6//
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-650, 100, -650);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 kanan
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-650, 100, -650);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 kiri
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-650, 100, -650);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 belakang
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-650, 100, -650);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 depan t7//
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(500, 100, -500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 660.0, 10.0);
    glVertex3f(10.0, 660.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 kanan
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(500, 100, -500);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 660.0, -10.0);
    glVertex3f(10.0, 660.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 kiri
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(500, 100, -500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 660.0, -10.0);
    glVertex3f(-10.0, 660.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 belakang
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(500, 100, -500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 660.0, -10.0);
    glVertex3f(10.0, 660.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();


    //tiang l1 depan t8//
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-500, 100, -500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 0.0, 10.0);
    glVertex3f(-10.0, 660.0, 10.0);
    glVertex3f(10.0, 660.0, 10.0);
    glVertex3f(10.0, 0.0, 10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 kanan
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-500, 100, -500);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, 0.0, -10.0);
    glVertex3f(10.0, 660.0, -10.0);
    glVertex3f(10.0, 660.0, 10.0);
    glVertex3f(10.0, 0.0, 10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 kiri
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-500, 100, -500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 0.0, -10.0);
    glVertex3f(-10.0, 660.0, -10.0);
    glVertex3f(-10.0, 660.0, 10.0);
    glVertex3f(-10.0, 0.0, 10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 belakang
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(-500, 100, -500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 0.0, -10.0);
    glVertex3f(-10.0, 660.0, -10.0);
    glVertex3f(10.0, 660.0, -10.0);
    glVertex3f(10.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();


    //tembok tangga kiri
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(200, 50, 790);
    glBegin(GL_POLYGON);
    glVertex3f(50.0, -50.0, -90.0);
    glVertex3f(50.0, 50.0, -90.0);
    glVertex3f(50.0, 50.0, 90.0);
    glVertex3f(50.0, -50.0, 90.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(200, 50, 790);
    glBegin(GL_POLYGON);
    glVertex3f(-50.0, -50.0, -90.0);
    glVertex3f(-50.0, 50.0, -90.0);
    glVertex3f(-50.0, 50.0, 90.0);
    glVertex3f(-50.0, -50.0, 90.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(200, 50, 790);
    glBegin(GL_POLYGON);
    glVertex3f(50.0, -50.0, 90.0);
    glVertex3f(50.0, 50.0, 90.0);
    glVertex3f(-50.0, 50.0, 90.0);
    glVertex3f(-50.0, -50.0, 90.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(200, 50, 790);
    glBegin(GL_POLYGON);
    glVertex3f(50.0, 50.0, 90.0);
    glVertex3f(50.0, -50.0, 90.0);
    glVertex3f(-50.0, -50.0, 90.0);
    glVertex3f(-50.0, 50.0, 90.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(200, 50, 790);
    glBegin(GL_POLYGON);
    glVertex3f(-50.0, 50.0, -90.0);
    glVertex3f(50.0, 50.0, -90.0);
    glVertex3f(50.0, 50.0, 90.0);
    glVertex3f(-50.0, 50.0, 90.0);
    glEnd();
    glPopMatrix();

    //tembok tangga kiri
    glPushMatrix();//samping kiri tkiri
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(-200, 50, 790);
    glBegin(GL_POLYGON);
    glVertex3f(50.0, -50.0, -90.0);
    glVertex3f(50.0, 50.0, -90.0);
    glVertex3f(50.0, 50.0, 90.0);
    glVertex3f(50.0, -50.0, 90.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//samping kanan tkiri
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(-200, 50, 790);
    glBegin(GL_POLYGON);
    glVertex3f(-50.0, -50.0, -90.0);
    glVertex3f(-50.0, 50.0, -90.0);
    glVertex3f(-50.0, 50.0, 90.0);
    glVertex3f(-50.0, -50.0, 90.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//depan kiri
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(-200, 50, 790);
    glBegin(GL_POLYGON);
    glVertex3f(50.0, -50.0, 90.0);
    glVertex3f(50.0, 50.0, 90.0);
    glVertex3f(-50.0, 50.0, 90.0);
    glVertex3f(-50.0, -50.0, 90.0);
    glEnd();

    glPopMatrix();
    glPushMatrix();//atas kiri
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-200, 50, 790);
    glBegin(GL_POLYGON);
    glVertex3f(-50.0, 50.0, -90.0);
    glVertex3f(50.0, 50.0, -90.0);
    glVertex3f(50.0, 50.0, 90.0);
    glVertex3f(-50.0, 50.0, 90.0);
    glEnd();
    glPopMatrix();

    //anak tangga
    glPushMatrix();//turun 1
    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(0, 0, 790);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, 20.0, 90.0);
    glVertex3f(-150.0, 0.0, 90.0);
    glVertex3f(150.0, 0.0, 90.0);
    glVertex3f(150.0, 20.0, 90.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//mendatar 1
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 0, 880);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, 20.0, 0.0);
    glVertex3f(150.0, 20.0, 0.0);
    glVertex3f(150.0, 20.0, -50.0);
    glVertex3f(-150.0, 20.0, -50.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//turun 2
    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(0, 20, 740);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, 20.0, 90.0);
    glVertex3f(-150.0, 0.0, 90.0);
    glVertex3f(150.0, 0.0, 90.0);
    glVertex3f(150.0, 20.0, 90.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//mendatar 2
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 0, 830);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, 40.0, 0.0);
    glVertex3f(150.0, 40.0, 0.0);
    glVertex3f(150.0, 40.0, -50.0);
    glVertex3f(-150.0, 40.0, -50.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//turun 2
    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(0, 40, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, 20.0, 90.0);
    glVertex3f(-150.0, 0.0, 90.0);
    glVertex3f(150.0, 0.0, 90.0);
    glVertex3f(150.0, 20.0, 90.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//mendatar 3
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 40, 780);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, 20.0, 0.0);
    glVertex3f(150.0, 20.0, 0.0);
    glVertex3f(150.0, 20.0, -50.0);
    glVertex3f(-150.0, 20.0, -50.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//turun 3
    glColor3f(0.0, 0.0, 1.0);
    glTranslatef(0, 60, 650);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, 20.0, 90.0);
    glVertex3f(-150.0, 0.0, 90.0);
    glVertex3f(150.0, 0.0, 90.0);
    glVertex3f(150.0, 20.0, 90.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//mendatar 4
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 0, 740);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, 80.0, 0.0);
    glVertex3f(150.0, 80.0, 0.0);
    glVertex3f(150.0, 80.0, -40.0);
    glVertex3f(-150.0, 80.0, -40.0);
    glEnd();
    glPopMatrix();


    //Ornamen dinding l1
    //tiang l1 t1
    glPushMatrix();//depan
    glColor3f(1, 0.5, 0);
    glTranslatef(-200, 100, 500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.5, 0);
    glTranslatef(-200, 100, 500);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(-200, 100, 500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(-200, 100, 500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 t2
    glPushMatrix();//depan
    glColor3f(1, 0.5, 0);
    glTranslatef(200, 100, 500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.5, 0);
    glTranslatef(200, 100, 500);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(200, 100, 500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(200, 100, 500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang mendatar t3   
    glPushMatrix();//depan
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(0, 350, 498);
    glBegin(GL_POLYGON);
    glVertex3f(-500.0, -10.0, 10.0);
    glVertex3f(-500.0, 10.0, 10.0);
    glVertex3f(500.0, 10.0, 10.0);
    glVertex3f(500.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(0, 350, 498);
    glBegin(GL_POLYGON);
    glVertex3f(-500.0, -10.0, -10.0);
    glVertex3f(-500.0, 10.0, -10.0);
    glVertex3f(500.0, 10.0, -10.0);
    glVertex3f(500.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 350, 498);
    glBegin(GL_POLYGON);
    glVertex3f(-500.0, 10.0, 10.0);
    glVertex3f(500.0, 10.0, 10.0);
    glVertex3f(500.0, 10.0, -10.0);
    glVertex3f(-500.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 350, 498);
    glBegin(GL_POLYGON);
    glVertex3f(-500.0, 0.0, 10.0);
    glVertex3f(500.0, 0.0, 10.0);
    glVertex3f(500.0, 0.0, -10.0);
    glVertex3f(-500.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang mendatar t4 
    glPushMatrix();//depan
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(350, 150, 498);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, -10.0, 10.0);
    glVertex3f(-150.0, 10.0, 10.0);
    glVertex3f(150.0, 10.0, 10.0);
    glVertex3f(150.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(350, 150, 498);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, -10.0, -10.0);
    glVertex3f(-150.0, 10.0, -10.0);
    glVertex3f(150.0, 10.0, -10.0);
    glVertex3f(150.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(350, 150, 498);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, 10.0, 10.0);
    glVertex3f(150.0, 10.0, 10.0);
    glVertex3f(150.0, 10.0, -10.0);
    glVertex3f(-150.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(350, 150, 498);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, 0.0, 10.0);
    glVertex3f(150.0, 0.0, 10.0);
    glVertex3f(150.0, 0.0, -10.0);
    glVertex3f(-150.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang mendatar t5
    glPushMatrix();//depan
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-350, 150, 498);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, -10.0, 10.0);
    glVertex3f(-150.0, 10.0, 10.0);
    glVertex3f(150.0, 10.0, 10.0);
    glVertex3f(150.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-350, 150, 498);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, -10.0, -10.0);
    glVertex3f(-150.0, 10.0, -10.0);
    glVertex3f(150.0, 10.0, -10.0);
    glVertex3f(150.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(-350, 150, 498);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, 10.0, 10.0);
    glVertex3f(150.0, 10.0, 10.0);
    glVertex3f(150.0, 10.0, -10.0);
    glVertex3f(-150.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(-350, 150, 498);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, 0.0, 10.0);
    glVertex3f(150.0, 0.0, 10.0);
    glVertex3f(150.0, 0.0, -10.0);
    glVertex3f(-150.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();


    //tiang l1 t6
    glPushMatrix();//depan
    glColor3f(1, 0.5, 0);
    glTranslatef(-200, 100, -500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.5, 0);
    glTranslatef(-200, 100, -500);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(-200, 100, -500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(-200, 100, -500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 t7
    glPushMatrix();//depan
    glColor3f(1, 0.5, 0);
    glTranslatef(200, 100, -500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.5, 0);
    glTranslatef(200, 100, -500);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(200, 100, -500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(200, 100, -500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang mendatar t8   
    glPushMatrix();//depan
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(0, 350, -498);
    glBegin(GL_POLYGON);
    glVertex3f(-500.0, -10.0, 10.0);
    glVertex3f(-500.0, 10.0, 10.0);
    glVertex3f(500.0, 10.0, 10.0);
    glVertex3f(500.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(0, 350, -498);
    glBegin(GL_POLYGON);
    glVertex3f(-500.0, -10.0, -10.0);
    glVertex3f(-500.0, 10.0, -10.0);
    glVertex3f(500.0, 10.0, -10.0);
    glVertex3f(500.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 350, -498);
    glBegin(GL_POLYGON);
    glVertex3f(-500.0, 10.0, 10.0);
    glVertex3f(500.0, 10.0, 10.0);
    glVertex3f(500.0, 10.0, -10.0);
    glVertex3f(-500.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 350, -498);
    glBegin(GL_POLYGON);
    glVertex3f(-500.0, 0.0, 10.0);
    glVertex3f(500.0, 0.0, 10.0);
    glVertex3f(500.0, 0.0, -10.0);
    glVertex3f(-500.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang mendatar t9 
    glPushMatrix();//depan
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(350, 150, -498);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, -10.0, 10.0);
    glVertex3f(-150.0, 10.0, 10.0);
    glVertex3f(150.0, 10.0, 10.0);
    glVertex3f(150.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(350, 150, -498);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, -10.0, -10.0);
    glVertex3f(-150.0, 10.0, -10.0);
    glVertex3f(150.0, 10.0, -10.0);
    glVertex3f(150.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(350, 150, -498);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, 10.0, 10.0);
    glVertex3f(150.0, 10.0, 10.0);
    glVertex3f(150.0, 10.0, -10.0);
    glVertex3f(-150.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(350, 150, -498);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, 0.0, 10.0);
    glVertex3f(150.0, 0.0, 10.0);
    glVertex3f(150.0, 0.0, -10.0);
    glVertex3f(-150.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang mendatar t10
    glPushMatrix();//depan
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-350, 150, -498);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, -10.0, 10.0);
    glVertex3f(-150.0, 10.0, 10.0);
    glVertex3f(150.0, 10.0, 10.0);
    glVertex3f(150.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-350, 150, -498);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, -10.0, -10.0);
    glVertex3f(-150.0, 10.0, -10.0);
    glVertex3f(150.0, 10.0, -10.0);
    glVertex3f(150.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(-350, 150, -498);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, 10.0, 10.0);
    glVertex3f(150.0, 10.0, 10.0);
    glVertex3f(150.0, 10.0, -10.0);
    glVertex3f(-150.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(-350, 150, -498);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, 0.0, 10.0);
    glVertex3f(150.0, 0.0, 10.0);
    glVertex3f(150.0, 0.0, -10.0);
    glVertex3f(-150.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //ornamen lantai 1 kanan t1
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(498, 150, 0);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -10.0, -500.0);
    glVertex3f(10.0, 10.0, -500.0);
    glVertex3f(10.0, 10.0, 500.0);
    glVertex3f(10.0, -10.0, 500.0);
    glEnd();
    glPopMatrix();

    //tiang l1 kiri turu 1
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(498, 150, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -10.0, -500.0);
    glVertex3f(-10.0, 10.0, -500.0);
    glVertex3f(-10.0, 10.0, 500.0);
    glVertex3f(-10.0, -10.0, 500.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(498, 150, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 10.0, 500.0);
    glVertex3f(10.0, 10.0, 500.0);
    glVertex3f(10.0, 10.0, -500.0);
    glVertex3f(-10.0, 10.0, -500.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(498, 150, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 0.0, 500.0);
    glVertex3f(10.0, 0.0, 500.0);
    glVertex3f(10.0, 0.0, -500.0);
    glVertex3f(-10.0, 0.0, -500.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(498, 350, 0);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -10.0, -500.0);
    glVertex3f(10.0, 10.0, -500.0);
    glVertex3f(10.0, 10.0, 500.0);
    glVertex3f(10.0, -10.0, 500.0);
    glEnd();
    glPopMatrix();

    //tiang l1 kiri turu2
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(498, 350, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -10.0, -500.0);
    glVertex3f(-10.0, 10.0, -500.0);
    glVertex3f(-10.0, 10.0, 500.0);
    glVertex3f(-10.0, -10.0, 500.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(498, 350, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 10.0, 500.0);
    glVertex3f(10.0, 10.0, 500.0);
    glVertex3f(10.0, 10.0, -500.0);
    glVertex3f(-10.0, 10.0, -500.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(498, 350, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 0.0, 500.0);
    glVertex3f(10.0, 0.0, 500.0);
    glVertex3f(10.0, 0.0, -500.0);
    glVertex3f(-10.0, 0.0, -500.0);
    glEnd();
    glPopMatrix();

    //tiang l1 kiri ngadek t1
    glPushMatrix();//depan
    glColor3f(1, 0.5, 0);
    glTranslatef(500, 100, -200);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.5, 0);
    glTranslatef(500, 100, -200);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(500, 100, -200);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(500, 100, -200);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 kiri ngadek t2
    glPushMatrix();//depan
    glColor3f(1, 0.5, 0);
    glTranslatef(500, 100, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.5, 0);
    glTranslatef(500, 100, 0);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(500, 100, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(500, 100, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 kiri ngadek t3
    glPushMatrix();//depan
    glColor3f(1, 0.5, 0);
    glTranslatef(500, 100, 200);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.5, 0);
    glTranslatef(500, 100, 200);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(500, 100, 200);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(500, 100, 200);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 kanan turu1
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-498, 150, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -10.0, -500.0);
    glVertex3f(-10.0, 10.0, -500.0);
    glVertex3f(-10.0, 10.0, 500.0);
    glVertex3f(-10.0, -10.0, 500.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(-498, 150, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 10.0, 500.0);
    glVertex3f(10.0, 10.0, 500.0);
    glVertex3f(10.0, 10.0, -500.0);
    glVertex3f(-10.0, 10.0, -500.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(-498, 150, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 0.0, 500.0);
    glVertex3f(10.0, 0.0, 500.0);
    glVertex3f(10.0, 0.0, -500.0);
    glVertex3f(-10.0, 0.0, -500.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-498, 350, 0);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -10.0, -500.0);
    glVertex3f(10.0, 10.0, -500.0);
    glVertex3f(10.0, 10.0, 500.0);
    glVertex3f(10.0, -10.0, 500.0);
    glEnd();
    glPopMatrix();

    //tiang l1 kanan turu2
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-498, 350, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -10.0, -500.0);
    glVertex3f(-10.0, 10.0, -500.0);
    glVertex3f(-10.0, 10.0, 500.0);
    glVertex3f(-10.0, -10.0, 500.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(-498, 350, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 10.0, 500.0);
    glVertex3f(10.0, 10.0, 500.0);
    glVertex3f(10.0, 10.0, -500.0);
    glVertex3f(-10.0, 10.0, -500.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(-498, 350, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 0.0, 500.0);
    glVertex3f(10.0, 0.0, 500.0);
    glVertex3f(10.0, 0.0, -500.0);
    glVertex3f(-10.0, 0.0, -500.0);
    glEnd();
    glPopMatrix();

    //tiang l1 kanan ngadek t1
    glPushMatrix();//depan
    glColor3f(1, 0.5, 0);
    glTranslatef(-500, 100, -200);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.5, 0);
    glTranslatef(-500, 100, -200);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(-500, 100, -200);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(-500, 100, -200);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 kanan ngadek t2
    glPushMatrix();//depan
    glColor3f(1, 0.5, 0);
    glTranslatef(-500, 100, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.5, 0);
    glTranslatef(-500, 100, 0);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(-500, 100, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(-500, 100, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang l1 kanan ngadek t3
    glPushMatrix();//depan
    glColor3f(1, 0.5, 0);
    glTranslatef(-500, 100, 200);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.5, 0);
    glTranslatef(-500, 100, 200);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(-500, 100, 200);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(-500, 100, 200);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //ORNAMEN LANTAI 2
    //dinding kiri ngadek
    //ngadek 1 kanan
    glPushMatrix();//depan
    glColor3f(1, 0.5, 0);
    glTranslatef(350, 500, 100);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.5, 0);
    glTranslatef(350, 500, 100);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(350, 500, 100);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(350, 500, 100);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //ngadek 2 kiri
    glPushMatrix();//depan
    glColor3f(1, 0.5, 0);
    glTranslatef(350, 500, -100);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.5, 0);
    glTranslatef(350, 500, -100);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(350, 500, -100);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(350, 500, -100);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //ngadek 2 kiri pojok depan
    glPushMatrix();//depan
    glColor3f(1, 0.0, 0);
    glTranslatef(350, 500, 350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(350, 500, 350);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(350, 500, 350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(350, 500, 350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //ngadek 2 kiri pojok blkng
    glPushMatrix();//depan
    glColor3f(1, 0.0, 0);
    glTranslatef(350, 500, -350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();


    //ngadek 1 kanan
    //ngadek 1
    glPushMatrix();//depan
    glColor3f(1, 0.5, 0);
    glTranslatef(-350, 500, 100);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.5, 0);
    glTranslatef(-350, 500, 100);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(-350, 500, 100);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(-350, 500, 100);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //ngadek 2 kanan
    glPushMatrix();//depan
    glColor3f(1, 0.5, 0);
    glTranslatef(-350, 500, -100);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.5, 0);
    glTranslatef(-350, 500, -100);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(-350, 500, -100);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(-350, 500, -100);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(350, 500, -350);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(350, 500, -350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(350, 500, -350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //ngadek 2 kanan pojok depan
    glPushMatrix();//depan
    glColor3f(1, 0.0, 0);
    glTranslatef(-350, 500, 350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(-350, 500, 350);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-350, 500, 350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-350, 500, 350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //ngadek 2 kanan pojok blkng
    glPushMatrix();//depan
    glColor3f(1, 0.0, 0);
    glTranslatef(-350, 500, -350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(-350, 500, -350);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-350, 500, -350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-350, 500, -350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //LATAI 2 DEPAN ORNAMEN
    //ngadek 1
    glPushMatrix();//depan
    glColor3f(1, 0.5, 0);
    glTranslatef(150, 500, 350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.5, 0);
    glTranslatef(150, 500, 350);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(150, 500, 350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(150, 500, 350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //ngadek 2
    glPushMatrix();//depan
    glColor3f(1, 0.5, 0);
    glTranslatef(-150, 500, 350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.5, 0);
    glTranslatef(-150, 500, 350);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(-150, 500, 350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(-150, 500, 350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //BLANG NGADEK
    glPushMatrix();//depan
    glColor3f(1, 0.5, 0);
    glTranslatef(150, 500, -350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.5, 0);
    glTranslatef(150, 500, -350);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(150, 500, -350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(150, 500, -350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //NGADEK 2
    glPushMatrix();//depan
    glColor3f(1, 0.5, 0);
    glTranslatef(-150, 500, -350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.5, 0);
    glTranslatef(-150, 500, -350);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(-150, 500, -350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(-150, 500, -350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //TTTTTTTTTTTTTTTURUUUUUU
    glPushMatrix();//1
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-348, 530, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -10.0, -350.0);
    glVertex3f(-10.0, 10.0, -350.0);
    glVertex3f(-10.0, 10.0, 350.0);
    glVertex3f(-10.0, -10.0, 350.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(-348, 530, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 10.0, 350.0);
    glVertex3f(10.0, 10.0, 350.0);
    glVertex3f(10.0, 10.0, -350.0);
    glVertex3f(-10.0, 10.0, -350.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(-348, 530, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -10.0, 350.0);
    glVertex3f(10.0, 10.0, 350.0);
    glVertex3f(10.0, 10.0, -350.0);
    glVertex3f(-10.0, -10.0, -350.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-348, 530, 0);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -10.0, -350.0);
    glVertex3f(10.0, 10.0, -350.0);
    glVertex3f(10.0, 10.0, 350.0);
    glVertex3f(10.0, -10.0, 350.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//2
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-348, 700, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -10.0, -350.0);
    glVertex3f(-10.0, 10.0, -350.0);
    glVertex3f(-10.0, 10.0, 350.0);
    glVertex3f(-10.0, -10.0, 350.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(-348, 700, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 10.0, 350.0);
    glVertex3f(10.0, 10.0, 350.0);
    glVertex3f(10.0, 10.0, -350.0);
    glVertex3f(-10.0, 10.0, -350.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(-348, 700, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -10.0, 350.0);
    glVertex3f(10.0, 10.0, 350.0);
    glVertex3f(10.0, 10.0, -350.0);
    glVertex3f(-10.0, -10.0, -350.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-348, 700, 0);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -10.0, -350.0);
    glVertex3f(10.0, 10.0, -350.0);
    glVertex3f(10.0, 10.0, 350.0);
    glVertex3f(10.0, -10.0, 350.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//1KNN
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(348, 530, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -10.0, -350.0);
    glVertex3f(-10.0, 10.0, -350.0);
    glVertex3f(-10.0, 10.0, 350.0);
    glVertex3f(-10.0, -10.0, 350.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(348, 530, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 10.0, 350.0);
    glVertex3f(10.0, 10.0, 350.0);
    glVertex3f(10.0, 10.0, -350.0);
    glVertex3f(-10.0, 10.0, -350.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(348, 530, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -10.0, 350.0);
    glVertex3f(10.0, 10.0, 350.0);
    glVertex3f(10.0, 10.0, -350.0);
    glVertex3f(-10.0, -10.0, -350.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(348, 530, 0);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -10.0, -350.0);
    glVertex3f(10.0, 10.0, -350.0);
    glVertex3f(10.0, 10.0, 350.0);
    glVertex3f(10.0, -10.0, 350.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//2
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(348, 700, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -10.0, -350.0);
    glVertex3f(-10.0, 10.0, -350.0);
    glVertex3f(-10.0, 10.0, 350.0);
    glVertex3f(-10.0, -10.0, 350.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(348, 700, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 10.0, 350.0);
    glVertex3f(10.0, 10.0, 350.0);
    glVertex3f(10.0, 10.0, -350.0);
    glVertex3f(-10.0, 10.0, -350.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(348, 700, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -10.0, 350.0);
    glVertex3f(10.0, 10.0, 350.0);
    glVertex3f(10.0, 10.0, -350.0);
    glVertex3f(-10.0, -10.0, -350.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(348, 700, 0);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -10.0, -350.0);
    glVertex3f(10.0, 10.0, -350.0);
    glVertex3f(10.0, 10.0, 350.0);
    glVertex3f(10.0, -10.0, 350.0);
    glEnd();
    glPopMatrix();


    //tiang mendatar L2 DEPAN
    //DPN1
    glPushMatrix();//depan
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(250, 530, 348);
    glBegin(GL_POLYGON);
    glVertex3f(-100.0, -10.0, 10.0);
    glVertex3f(-100.0, 10.0, 10.0);
    glVertex3f(100.0, 10.0, 10.0);
    glVertex3f(100.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(250, 530, 348);
    glBegin(GL_POLYGON);
    glVertex3f(-100.0, -10.0, -10.0);
    glVertex3f(-100.0, 10.0, -10.0);
    glVertex3f(100.0, 10.0, -10.0);
    glVertex3f(100.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(250, 530, 348);
    glBegin(GL_POLYGON);
    glVertex3f(-100.0, 10.0, 10.0);
    glVertex3f(100.0, 10.0, 10.0);
    glVertex3f(100.0, 10.0, -10.0);
    glVertex3f(-100.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(250, 530, 348);
    glBegin(GL_POLYGON);
    glVertex3f(-100.0, 0.0, 10.0);
    glVertex3f(100.0, 0.0, 10.0);
    glVertex3f(100.0, 0.0, -10.0);
    glVertex3f(-100.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //DPN2
    glPushMatrix();//depan
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-250, 530, 348);
    glBegin(GL_POLYGON);
    glVertex3f(-100.0, -10.0, 10.0);
    glVertex3f(-100.0, 10.0, 10.0);
    glVertex3f(100.0, 10.0, 10.0);
    glVertex3f(100.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-250, 530, 348);
    glBegin(GL_POLYGON);
    glVertex3f(-100.0, -10.0, -10.0);
    glVertex3f(-100.0, 10.0, -10.0);
    glVertex3f(100.0, 10.0, -10.0);
    glVertex3f(100.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(-250, 530, 348);
    glBegin(GL_POLYGON);
    glVertex3f(-100.0, 10.0, 10.0);
    glVertex3f(100.0, 10.0, 10.0);
    glVertex3f(100.0, 10.0, -10.0);
    glVertex3f(-100.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(-250, 530, 348);
    glBegin(GL_POLYGON);
    glVertex3f(-100.0, 0.0, 10.0);
    glVertex3f(100.0, 0.0, 10.0);
    glVertex3f(100.0, 0.0, -10.0);
    glVertex3f(-100.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //DPN3
    glPushMatrix();//depan
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(0, 700, 348);
    glBegin(GL_POLYGON);
    glVertex3f(-350.0, -10.0, 10.0);
    glVertex3f(-350.0, 10.0, 10.0);
    glVertex3f(350.0, 10.0, 10.0);
    glVertex3f(350.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(0, 700, 348);
    glBegin(GL_POLYGON);
    glVertex3f(-350.0, -10.0, -10.0);
    glVertex3f(-350.0, 10.0, -10.0);
    glVertex3f(350.0, 10.0, -10.0);
    glVertex3f(350.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 700, 348);
    glBegin(GL_POLYGON);
    glVertex3f(-350.0, 10.0, 10.0);
    glVertex3f(350.0, 10.0, 10.0);
    glVertex3f(350.0, 10.0, -10.0);
    glVertex3f(-350.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 700, 348);
    glBegin(GL_POLYGON);
    glVertex3f(-350.0, 0.0, 10.0);
    glVertex3f(350.0, 0.0, 10.0);
    glVertex3f(350.0, 0.0, -10.0);
    glVertex3f(-350.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang mendatar L2 BELAKANG
    //BLKN1
    glPushMatrix();//depan
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(250, 530, -348);
    glBegin(GL_POLYGON);
    glVertex3f(-100.0, -10.0, 10.0);
    glVertex3f(-100.0, 10.0, 10.0);
    glVertex3f(100.0, 10.0, 10.0);
    glVertex3f(100.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(250, 530, -348);
    glBegin(GL_POLYGON);
    glVertex3f(-100.0, -10.0, -10.0);
    glVertex3f(-100.0, 10.0, -10.0);
    glVertex3f(100.0, 10.0, -10.0);
    glVertex3f(100.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(250, 530, -348);
    glBegin(GL_POLYGON);
    glVertex3f(-100.0, 10.0, 10.0);
    glVertex3f(100.0, 10.0, 10.0);
    glVertex3f(100.0, 10.0, -10.0);
    glVertex3f(-100.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(250, 530, -348);
    glBegin(GL_POLYGON);
    glVertex3f(-100.0, 0.0, 10.0);
    glVertex3f(100.0, 0.0, 10.0);
    glVertex3f(100.0, 0.0, -10.0);
    glVertex3f(-100.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //BLKN2
    glPushMatrix();//depan
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-250, 530, -348);
    glBegin(GL_POLYGON);
    glVertex3f(-100.0, -10.0, 10.0);
    glVertex3f(-100.0, 10.0, 10.0);
    glVertex3f(100.0, 10.0, 10.0);
    glVertex3f(100.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-250, 530, -348);
    glBegin(GL_POLYGON);
    glVertex3f(-100.0, -10.0, -10.0);
    glVertex3f(-100.0, 10.0, -10.0);
    glVertex3f(100.0, 10.0, -10.0);
    glVertex3f(100.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(-250, 530, -348);
    glBegin(GL_POLYGON);
    glVertex3f(-100.0, 10.0, 10.0);
    glVertex3f(100.0, 10.0, 10.0);
    glVertex3f(100.0, 10.0, -10.0);
    glVertex3f(-100.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(-250, 530, -348);
    glBegin(GL_POLYGON);
    glVertex3f(-100.0, 0.0, 10.0);
    glVertex3f(100.0, 0.0, 10.0);
    glVertex3f(100.0, 0.0, -10.0);
    glVertex3f(-100.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //BLKN3
    glPushMatrix();//depan
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(0, 700, -348);
    glBegin(GL_POLYGON);
    glVertex3f(-350.0, -10.0, 10.0);
    glVertex3f(-350.0, 10.0, 10.0);
    glVertex3f(350.0, 10.0, 10.0);
    glVertex3f(350.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(0, 700, -348);
    glBegin(GL_POLYGON);
    glVertex3f(-350.0, -10.0, -10.0);
    glVertex3f(-350.0, 10.0, -10.0);
    glVertex3f(350.0, 10.0, -10.0);
    glVertex3f(350.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 700, -348);
    glBegin(GL_POLYGON);
    glVertex3f(-350.0, 10.0, 10.0);
    glVertex3f(350.0, 10.0, 10.0);
    glVertex3f(350.0, 10.0, -10.0);
    glVertex3f(-350.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 700, -348);
    glBegin(GL_POLYGON);
    glVertex3f(-350.0, 0.0, 10.0);
    glVertex3f(350.0, 0.0, 10.0);
    glVertex3f(350.0, 0.0, -10.0);
    glVertex3f(-350.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //LANTAI 3
    //dinding depan lantai 3
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0, 850, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-300.0, -50.0, 300.0);
    glVertex3f(-300.0, 450.0, 300.0);
    glVertex3f(300.0, 450.0, 300.0);
    glVertex3f(300.0, -50.0, 300.0);
    glEnd();
    glPopMatrix();

    //dinding  kanan lantai 3
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0, 850, 0);
    glBegin(GL_POLYGON);
    glVertex3f(300.0, -50.0, -300.0);
    glVertex3f(300.0, 450.0, -300.0);
    glVertex3f(300.0, 450.0, 300.0);
    glVertex3f(300.0, -50.0, 300.0);
    glEnd();
    glPopMatrix();

    //dinding kiri lantai 3
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0, 850, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-300.0, -50.0, -300.0);
    glVertex3f(-300.0, 450.0, -300.0);
    glVertex3f(-300.0, 450.0, 300.0);
    glVertex3f(-300.0, -50.0, 300.0);
    glEnd();
    glPopMatrix();

    //dinding belakang lantai 3
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0, 850, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-300.0, -50.0, -300.0);
    glVertex3f(-300.0, 450.0, -300.0);
    glVertex3f(300.0, 450.0, -300.0);
    glVertex3f(300.0, -50.0, -300.0);
    glEnd();
    glPopMatrix();

    //alas lantai (4)1
    glPushMatrix();
    glColor3f(0.79, 0.73, 0.78);
    glTranslatef(0, 1300, 0);
    glBegin(GL_POLYGON);
    glVertex3f(400.0, 0.0, 400.0);
    glVertex3f(400.0, 0.0, -400.0);
    glVertex3f(-400.0, 0.0, -400.0);
    glVertex3f(-400.0, 0.0, 400.0);
    glEnd();
    glPopMatrix();

    //alas lantai (4)2
    glPushMatrix();
    glColor3f(0.79, 0.73, 0.78);
    glTranslatef(0, 1350, 0);
    glBegin(GL_POLYGON);
    glVertex3f(400.0, 0.0, 400.0);
    glVertex3f(400.0, 0.0, -400.0);
    glVertex3f(-400.0, 0.0, -400.0);
    glVertex3f(-400.0, 0.0, 400.0);
    glEnd();
    glPopMatrix();

    //didnding atap depan lantai 3 
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(0, 1350, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-400.0, -50.0, 400.0);
    glVertex3f(-400.0, 5.0, 400.0);
    glVertex3f(400.0, 5.0, 400.0);
    glVertex3f(400.0, -50.0, 400.0);
    glEnd();
    glPopMatrix();

    //dinding kanan atap lantai 3
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(0, 1350, 0);
    glBegin(GL_POLYGON);
    glVertex3f(400.0, -50.0, -400.0);
    glVertex3f(400.0, 5.0, -400.0);
    glVertex3f(400.0, 5.0, 400.0);
    glVertex3f(400.0, -50.0, 400.0);
    glEnd();
    glPopMatrix();

    //dinding atap kiri lantai 3
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(0, 1350, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-400.0, -50.0, -400.0);
    glVertex3f(-400.0, 5.0, -400.0);
    glVertex3f(-400.0, 5.0, 400.0);
    glVertex3f(-400.0, -50.0, 400.0);
    glEnd();
    glPopMatrix();

    //dinding atap belakang lantai 3
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(0, 1350, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-400.0, -50.0, -400.0);
    glVertex3f(-400.0, 5.0, -400.0);
    glVertex3f(400.0, 5.0, -400.0);
    glVertex3f(400.0, -50.0, -400.0);
    glEnd();
    glPopMatrix();


    //LANTAI 4
    //dinding depan lantai 4
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0, 1300, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-250.0, -50.0, 250.0);
    glVertex3f(-250.0, 450.0, 250.0);
    glVertex3f(250.0, 450.0, 250.0);
    glVertex3f(250.0, -50.0, 250.0);
    glEnd();
    glPopMatrix();

    //dinding  kanan lantai 4
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0, 1300, 0);
    glBegin(GL_POLYGON);
    glVertex3f(250.0, -50.0, -250.0);
    glVertex3f(250.0, 450.0, -250.0);
    glVertex3f(250.0, 450.0, 250.0);
    glVertex3f(250.0, -50.0, 250.0);
    glEnd();
    glPopMatrix();

    //dinding kiri lantai 3
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0, 1300, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-250.0, -50.0, -250.0);
    glVertex3f(-250.0, 450.0, -250.0);
    glVertex3f(-250.0, 450.0, 250.0);
    glVertex3f(-250.0, -50.0, 250.0);
    glEnd();
    glPopMatrix();

    //dinding belakang lantai 3
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslatef(0, 1300, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-250.0, -50.0, -250.0);
    glVertex3f(-250.0, 450.0, -250.0);
    glVertex3f(250.0, 450.0, -250.0);
    glVertex3f(250.0, -50.0, -250.0);
    glEnd();
    glPopMatrix();

    //alas lantai (4)1
    glPushMatrix();
    glColor3f(0.79, 0.73, 0.78);
    glTranslatef(0, 1750, 0);
    glBegin(GL_POLYGON);
    glVertex3f(350.0, 0.0, 350.0);
    glVertex3f(350.0, 0.0, -350.0);
    glVertex3f(-350.0, 0.0, -350.0);
    glVertex3f(-350.0, 0.0, 350.0);
    glEnd();
    glPopMatrix();

    //alas lantai (4)2
    glPushMatrix();
    glColor3f(0.79, 0.73, 0.78);
    glTranslatef(0, 1805, 0);
    glBegin(GL_POLYGON);
    glVertex3f(450.0, 0.0, 450.0);
    glVertex3f(450.0, 0.0, -450.0);
    glVertex3f(-450.0, 0.0, -450.0);
    glVertex3f(-450.0, 0.0, 450.0);
    glEnd();
    glPopMatrix();

    //didnding atap depan lantai 4//
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(0, 1800, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-350.0, -50.0, 350.0);
    glVertex3f(-450.0, 5.0, 450.0);
    glVertex3f(450.0, 5.0, 450.0);
    glVertex3f(350.0, -50.0, 350.0);
    glEnd();
    glPopMatrix();

    //dinding kanan atap lantai 4
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(0, 1800, 0);
    glBegin(GL_POLYGON);
    glVertex3f(350.0, -50.0, -350.0);
    glVertex3f(450.0, 5.0, -450.0);
    glVertex3f(450.0, 5.0, 450.0);
    glVertex3f(350.0, -50.0, 350.0);
    glEnd();
    glPopMatrix();

    //dinding atap kiri lantai 4
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(0, 1800, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-350.0, -50.0, -350.0);
    glVertex3f(-450.0, 5.0, -450.0);
    glVertex3f(-450.0, 5.0, 450.0);
    glVertex3f(-350.0, -50.0, 350.0);
    glEnd();
    glPopMatrix();

    //dinding atap belakang lantai 4
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(0, 1800, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-350.0, -50.0, -350.0);
    glVertex3f(-450.0, 5.0, -450.0);
    glVertex3f(450.0, 5.0, -450.0);
    glVertex3f(350.0, -50.0, -350.0);
    glEnd();
    glPopMatrix();

    //ATAPP 5 SEGITIGA BELAKANG
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 1800, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-450.0, 5.0, -450.0);
    glVertex3f(450.0, 5.0, -450.0);
    glVertex3f(0.0, 400.0, 0.0);
    glEnd();
    glPopMatrix();

    //ATAPP 5 SEGITIGA KIRI
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 1800, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-450.0, 5.0, -450.0);
    glVertex3f(-450.0, 5.0, 450.0);
    glVertex3f(0.0, 400.0, 0.0);
    glEnd();
    glPopMatrix();

    //ATAPP 5 SEGITIGA KIRI
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 1800, 0);
    glBegin(GL_POLYGON);
    glVertex3f(450.0, 5.0, -450.0);
    glVertex3f(450.0, 5.0, 450.0);
    glVertex3f(0.0, 400.0, 0.0);
    glEnd();
    glPopMatrix();

    //ATAPP 5 SEGITIGA DEPAN
    glPushMatrix();
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 1800, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-450.0, 5.0, 450.0);
    glVertex3f(450.0, 5.0, 450.0);
    glVertex3f(0.0, 400.0, 0.0);
    glEnd();
    glPopMatrix();

    //didnding atap depan lantai 4//MIRING
    glPushMatrix();
    glColor3f(0.79, 0.73, 0.78);
    glTranslatef(0, 1750, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-550.0, -50.0, 550.0);
    glVertex3f(-350.0, 5.0, 350.0);
    glVertex3f(350.0, 5.0, 350.0);
    glVertex3f(550.0, -50.0, 550.0);
    glEnd();
    glPopMatrix();

    //dinding kanan atap lantai 4//MIRING
    glPushMatrix();
    glColor3f(0.79, 0.73, 0.78);
    glTranslatef(0, 1750, 0);
    glBegin(GL_POLYGON);
    glVertex3f(550.0, -50.0, -550.0);
    glVertex3f(350.0, 5.0, -350.0);
    glVertex3f(350.0, 5.0, 350.0);
    glVertex3f(550.0, -50.0, 550.00);
    glEnd();
    glPopMatrix();

    //dinding atap kiri lantai 4// MIRING
    glPushMatrix();
    glColor3f(0.79, 0.73, 0.78);
    glTranslatef(0, 1750, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-550.0, -50.0, -550.0);
    glVertex3f(-350.0, 5.0, -350.0);
    glVertex3f(-350.0, 5.0, 350.0);
    glVertex3f(-550.0, -50.0, 550.0);
    glEnd();
    glPopMatrix();

    //dinding atap belakang lantai 4 // MIRING
    glPushMatrix();
    glColor3f(0.79, 0.73, 0.78);
    glTranslatef(0, 1750, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-550.0, -50.0, -550.0);
    glVertex3f(-350.0, 5.0, -350.0);
    glVertex3f(350.0, 5.0, -350.0);
    glVertex3f(550.0, -50.0, -550.0);
    glEnd();
    glPopMatrix();

    //alas lantai (4)3
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(0, 1700, 0);
    glBegin(GL_POLYGON);
    glVertex3f(550.0, 0.0, 550.0);
    glVertex3f(550.0, 0.0, -550.0);
    glVertex3f(-550.0, 0.0, -550.0);
    glVertex3f(-550.0, 0.0, 550.0);
    glEnd();
    glPopMatrix();

    //TOWER
    glPushMatrix();//ATSS
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(0, 2190, 0);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, 500.0, 10.0);
    glVertex3f(10.0, 500.0, -10.0);
    glVertex3f(-10.0, 500.0, -10.0);
    glVertex3f(-10.0, 500.0, 10.0);
    glEnd();
    glPopMatrix();
    glPushMatrix();//DPN
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(0, 2190, 0);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, 0.0, 10.0);
    glVertex3f(10.0, 500.0, 10.0);
    glVertex3f(-10.0, 500.0, 10.0);
    glVertex3f(-10.0, 0.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//BLKN
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(0, 2190, 0);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, 0.0, -10.0);
    glVertex3f(10.0, 500.0, -10.0);
    glVertex3f(-10.0, 500.0, -10.0);
    glVertex3f(-10.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//KR
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(0, 2190, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 500.0, -10.0);
    glVertex3f(-10.0, 0.0, -10.0);
    glVertex3f(-10.0, 0.0, 10.0);
    glVertex3f(-10.0, 500.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//KN
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(0, 2190, 0);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, 500.0, -10.0);
    glVertex3f(10.0, 0.0, -10.0);
    glVertex3f(10.0, 0.0, 10.0);
    glVertex3f(10.0, 500.0, 10.0);
    glEnd();
    glPopMatrix();

    //atap3 lantai 4 
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(0, 1200, 0);
    glBegin(GL_POLYGON);
    glVertex3f(500.0, 0.0, 500.0);
    glVertex3f(500.0, 0.0, -500.0);
    glVertex3f(-500.0, 0.0, -500.0);
    glVertex3f(-500.0, 0.0, 500.0);
    glEnd();
    glPopMatrix();

    //didnding atap depan lantai 5//MIRING
    glPushMatrix();
    glColor3f(0.79, 0.73, 0.78);
    glTranslatef(0, 1300, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-500.0, -100.0, 500.0);
    glVertex3f(-350.0, 5.0, 350.0);
    glVertex3f(350.0, 5.0, 350.0);
    glVertex3f(500.0, -100.0, 500.0);
    glEnd();
    glPopMatrix();

    //dinding kanan atap lantai 5//MIRING
    glPushMatrix();
    glColor3f(0.79, 0.73, 0.78);
    glTranslatef(0, 1300, 0);
    glBegin(GL_POLYGON);
    glVertex3f(500.0, -100.0, -500.0);
    glVertex3f(350.0, 5.0, -350.0);
    glVertex3f(350.0, 5.0, 350.0);
    glVertex3f(500.0, -100.0, 500.00);
    glEnd();
    glPopMatrix();

    //dinding atap kiri lantai 5// MIRING
    glPushMatrix();
    glColor3f(0.79, 0.73, 0.78);
    glTranslatef(0, 1300, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-500.0, -100.0, -500.0);
    glVertex3f(-350.0, 5.0, -350.0);
    glVertex3f(-350.0, 5.0, 350.0);
    glVertex3f(-500.0, -100.0, 500.0);
    glEnd();
    glPopMatrix();

    //dinding atap belakang lantai 5 // MIRING
    glPushMatrix();
    glColor3f(0.79, 0.73, 0.78);
    glTranslatef(0, 1300, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-500.0, -100.0, -500.0);
    glVertex3f(-350.0, 5.0, -350.0);
    glVertex3f(350.0, 5.0, -350.0);
    glVertex3f(500.0, -100.0, -500.0);
    glEnd();
    glPopMatrix();

    //pintu depan l1 kanan
    glPushMatrix();//belakang kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(100, 150, 500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 170.0, 10.0);
    glVertex3f(10.0, 170.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(100, 150, 500);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 170.0, -10.0);
    glVertex3f(10.0, 170.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(100, 150, 500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 170.0, -10.0);
    glVertex3f(-10.0, 170.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(100, 150, 500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 170.0, -10.0);
    glVertex3f(10.0, 170.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();


    //pintu depan l1 kiri
    glPushMatrix();//belakang kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(-100, 150, 500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 170.0, 10.0);
    glVertex3f(10.0, 170.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(-100, 150, 500);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 170.0, -10.0);
    glVertex3f(10.0, 170.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-100, 150, 500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 170.0, -10.0);
    glVertex3f(-10.0, 170.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-100, 150, 500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 170.0, -10.0);
    glVertex3f(10.0, 170.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang mendatar pintu depan l1 atas
    glPushMatrix();//depan
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 300, 500);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, -10.0, 10.0);
    glVertex3f(-150.0, 10.0, 10.0);
    glVertex3f(150.0, 10.0, 10.0);
    glVertex3f(150.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 300, 500);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, -10.0, -10.0);
    glVertex3f(-150.0, 10.0, -10.0);
    glVertex3f(150.0, 10.0, -10.0);
    glVertex3f(150.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 300, 500);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, 10.0, 10.0);
    glVertex3f(150.0, 10.0, 10.0);
    glVertex3f(150.0, 10.0, -10.0);
    glVertex3f(-150.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 300, 500);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, 0.0, 10.0);
    glVertex3f(150.0, 0.0, 10.0);
    glVertex3f(150.0, 0.0, -10.0);
    glVertex3f(-150.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang mendatar pintu depan l1 bawah
    glPushMatrix();//depan
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 265, 500);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, -10.0, 10.0);
    glVertex3f(-150.0, 10.0, 10.0);
    glVertex3f(150.0, 10.0, 10.0);
    glVertex3f(150.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 265, 500);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, -10.0, -10.0);
    glVertex3f(-150.0, 10.0, -10.0);
    glVertex3f(150.0, 10.0, -10.0);
    glVertex3f(150.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 265, 500);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, 10.0, 10.0);
    glVertex3f(150.0, 10.0, 10.0);
    glVertex3f(150.0, 10.0, -10.0);
    glVertex3f(-150.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 265, 500);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, 0.0, 10.0);
    glVertex3f(150.0, 0.0, 10.0);
    glVertex3f(150.0, 0.0, -10.0);
    glVertex3f(-150.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //pintu belakang l1 kanan 
    glPushMatrix();//belakang kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(100, 150, -500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 170.0, 10.0);
    glVertex3f(10.0, 170.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(100, 150, -500);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 170.0, -10.0);
    glVertex3f(10.0, 170.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(100, 150, -500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 170.0, -10.0);
    glVertex3f(-10.0, 170.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(100, 150, -500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 170.0, -10.0);
    glVertex3f(10.0, 170.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();


    //pintu belakang l1 kiri
    glPushMatrix();//belakang kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(-100, 150, -500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 170.0, 10.0);
    glVertex3f(10.0, 170.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(-100, 150, -500);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 170.0, -10.0);
    glVertex3f(10.0, 170.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-100, 150, -500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 170.0, -10.0);
    glVertex3f(-10.0, 170.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-100, 150, -500);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 170.0, -10.0);
    glVertex3f(10.0, 170.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang mendatar pintu depan l1 atas belakang
    glPushMatrix();//depan
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 300, -500);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, -10.0, 10.0);
    glVertex3f(-150.0, 10.0, 10.0);
    glVertex3f(150.0, 10.0, 10.0);
    glVertex3f(150.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 300, -500);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, -10.0, -10.0);
    glVertex3f(-150.0, 10.0, -10.0);
    glVertex3f(150.0, 10.0, -10.0);
    glVertex3f(150.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 300, -500);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, 10.0, 10.0);
    glVertex3f(150.0, 10.0, 10.0);
    glVertex3f(150.0, 10.0, -10.0);
    glVertex3f(-150.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 300, -500);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, 0.0, 10.0);
    glVertex3f(150.0, 0.0, 10.0);
    glVertex3f(150.0, 0.0, -10.0);
    glVertex3f(-150.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang mendatar pintu belakang l1 bawah
    glPushMatrix();//depan
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 265, -500);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, -10.0, 10.0);
    glVertex3f(-150.0, 10.0, 10.0);
    glVertex3f(150.0, 10.0, 10.0);
    glVertex3f(150.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 265, -500);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, -10.0, -10.0);
    glVertex3f(-150.0, 10.0, -10.0);
    glVertex3f(150.0, 10.0, -10.0);
    glVertex3f(150.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 265, -500);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, 10.0, 10.0);
    glVertex3f(150.0, 10.0, 10.0);
    glVertex3f(150.0, 10.0, -10.0);
    glVertex3f(-150.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 265, -500);
    glBegin(GL_POLYGON);
    glVertex3f(-150.0, 0.0, 10.0);
    glVertex3f(150.0, 0.0, 10.0);
    glVertex3f(150.0, 0.0, -10.0);
    glVertex3f(-150.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //pintu depan l2 kanan
    glPushMatrix();//belakang kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(80, 500, 350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 150.0, 10.0);
    glVertex3f(10.0, 150.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(80, 500, 350);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 150.0, -10.0);
    glVertex3f(10.0, 150.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(80, 500, 350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 150.0, -10.0);
    glVertex3f(-10.0, 150.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(80, 500, 350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 150.0, -10.0);
    glVertex3f(10.0, 150.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();


    //pintu depan l2 kiri
    glPushMatrix();//belakang kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(-80, 500, 350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 150.0, 10.0);
    glVertex3f(10.0, 150.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(-80, 500, 350);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 150.0, -10.0);
    glVertex3f(10.0, 150.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-80, 500, 350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 150.0, -10.0);
    glVertex3f(-10.0, 150.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-80, 500, 350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 150.0, -10.0);
    glVertex3f(10.0, 150.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang mendatar pintu depan l2 atas
    glPushMatrix();//depan
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 630, 350);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, -10.0, 10.0);
    glVertex3f(-120.0, 10.0, 10.0);
    glVertex3f(120.0, 10.0, 10.0);
    glVertex3f(120.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 630, 350);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, -10.0, -10.0);
    glVertex3f(-120.0, 10.0, -10.0);
    glVertex3f(120.0, 10.0, -10.0);
    glVertex3f(120.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 630, 350);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, 10.0, 10.0);
    glVertex3f(120.0, 10.0, 10.0);
    glVertex3f(120.0, 10.0, -10.0);
    glVertex3f(-120.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 630, 350);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, 0.0, 10.0);
    glVertex3f(120.0, 0.0, 10.0);
    glVertex3f(120.0, 0.0, -10.0);
    glVertex3f(-120.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang mendatar pintu depan l2 bawah
    glPushMatrix();//depan
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 595, 350);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, -10.0, 10.0);
    glVertex3f(-120.0, 10.0, 10.0);
    glVertex3f(120.0, 10.0, 10.0);
    glVertex3f(120.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 595, 350);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, -10.0, -10.0);
    glVertex3f(-120.0, 10.0, -10.0);
    glVertex3f(120.0, 10.0, -10.0);
    glVertex3f(120.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 595, 350);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, 10.0, 10.0);
    glVertex3f(120.0, 10.0, 10.0);
    glVertex3f(120.0, 10.0, -10.0);
    glVertex3f(-120.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 595, 350);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, 0.0, 10.0);
    glVertex3f(120.0, 0.0, 10.0);
    glVertex3f(120.0, 0.0, -10.0);
    glVertex3f(-120.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //pintu belakang l2 kanan
    glPushMatrix();//belakang kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(80, 500, -350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 150.0, 10.0);
    glVertex3f(10.0, 150.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(80, 500, -350);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 150.0, -10.0);
    glVertex3f(10.0, 150.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(80, 500, -350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 150.0, -10.0);
    glVertex3f(-10.0, 150.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(80, 500, -350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 150.0, -10.0);
    glVertex3f(10.0, 150.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();


    //pintu belakang l2 kiri
    glPushMatrix();//belakang kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(-80, 500, -350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 150.0, 10.0);
    glVertex3f(10.0, 150.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(-80, 500, -350);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 150.0, -10.0);
    glVertex3f(10.0, 150.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-80, 500, -350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 150.0, -10.0);
    glVertex3f(-10.0, 150.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-80, 500, -350);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 150.0, -10.0);
    glVertex3f(10.0, 150.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang mendatar pintu belakang l2 atas
    glPushMatrix();//depan
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 630, -350);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, -10.0, 10.0);
    glVertex3f(-120.0, 10.0, 10.0);
    glVertex3f(120.0, 10.0, 10.0);
    glVertex3f(120.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 630, -350);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, -10.0, -10.0);
    glVertex3f(-120.0, 10.0, -10.0);
    glVertex3f(120.0, 10.0, -10.0);
    glVertex3f(120.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 630, -350);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, 10.0, 10.0);
    glVertex3f(120.0, 10.0, 10.0);
    glVertex3f(120.0, 10.0, -10.0);
    glVertex3f(-120.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 630, -350);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, 0.0, 10.0);
    glVertex3f(120.0, 0.0, 10.0);
    glVertex3f(120.0, 0.0, -10.0);
    glVertex3f(-120.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang mendatar pintu belakang l2 bawah
    glPushMatrix();//depan
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 595, -350);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, -10.0, 10.0);
    glVertex3f(-120.0, 10.0, 10.0);
    glVertex3f(120.0, 10.0, 10.0);
    glVertex3f(120.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 595, -350);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, -10.0, -10.0);
    glVertex3f(-120.0, 10.0, -10.0);
    glVertex3f(120.0, 10.0, -10.0);
    glVertex3f(120.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 595, -350);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, 10.0, 10.0);
    glVertex3f(120.0, 10.0, 10.0);
    glVertex3f(120.0, 10.0, -10.0);
    glVertex3f(-120.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 595, -350);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, 0.0, 10.0);
    glVertex3f(120.0, 0.0, 10.0);
    glVertex3f(120.0, 0.0, -10.0);
    glVertex3f(-120.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();


    //ORNAMEN LANTAI 3
    glPushMatrix();//depan kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(-300, 900, 300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(-300, 900, 300);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-300, 900, 300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-300, 900, 300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//depan kiri
    glColor3f(1, 0.0, 0);
    glTranslatef(300, 900, 300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(300, 900, 300);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(300, 900, 300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(300, 900, 300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang kiri
    glColor3f(1, 0.0, 0);
    glTranslatef(-300, 900, -300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(-300, 900, 300);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-300, 900, -300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-300, 900, -300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//blkang kiri
    glColor3f(1, 0.0, 0);
    glTranslatef(300, 900, -300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(300, 900, -300);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(300, 900, -300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(300, 900, -300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //depan orange ngadek l3
    //depan 1
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(150, 900, 300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(150, 900, 300);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(150, 900, 300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(150, 900, 300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //depan 2
    //depan
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(-150, 900, 300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(-150, 900, 300);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(-150, 900, 300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(-150, 900, 300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //KIRI L3
    //kiri l3 1
    //depan
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(300, 900, 150);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(300, 900, 150);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(300, 900, 150);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(300, 900, 150);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //kiri l3 2
    //depan
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(300, 900, -150);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(300, 900, -150);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(300, 900, -150);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(300, 900, -150);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //KIRI L3
    //kanan l3 1
    //depan
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(-300, 900, 150);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(-300, 900, 150);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(-300, 900, 150);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(-300, 900, 150);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //kanan l3 2
    //depan
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(-300, 900, -150);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(-300, 900, -150);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(-300, 900, -150);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(-300, 900, -150);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //belakang orange
    //depan 1
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(150, 900, -300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(150, 900, -300);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(150, 900, -300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(150, 900, -300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //blkng 2
    //depan
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(-150, 900, -300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(-150, 900, -300);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(-150, 900, -300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1.0, 0.5, 0.0);
    glTranslatef(-150, 900, -300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //TURRU LANTAI 3
    //DEPAN1 PENDEK
    glPushMatrix();//depan
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(225, 1000, 298);
    glBegin(GL_POLYGON);
    glVertex3f(-75.0, -10.0, 10.0);
    glVertex3f(-75.0, 10.0, 10.0);
    glVertex3f(75.0, 10.0, 10.0);
    glVertex3f(75.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(225, 1000, 298);
    glBegin(GL_POLYGON);
    glVertex3f(-75.0, -10.0, -10.0);
    glVertex3f(-75.0, 10.0, -10.0);
    glVertex3f(75.0, 10.0, -10.0);
    glVertex3f(75.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(225, 1000, 298);
    glBegin(GL_POLYGON);
    glVertex3f(-75.0, 10.0, 10.0);
    glVertex3f(75.0, 10.0, 10.0);
    glVertex3f(75.0, 10.0, -10.0);
    glVertex3f(-75.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(225, 1000, 298);
    glBegin(GL_POLYGON);
    glVertex3f(-75.0, 10.0, 10.0);
    glVertex3f(75.0, -10.0, 10.0);
    glVertex3f(75.0, -10.0, -10.0);
    glVertex3f(-75.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    //DEPAN 2 PENDEK
    glPushMatrix();//depan
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-225, 1000, 298);
    glBegin(GL_POLYGON);
    glVertex3f(-75.0, -10.0, 10.0);
    glVertex3f(-75.0, 10.0, 10.0);
    glVertex3f(75.0, 10.0, 10.0);
    glVertex3f(75.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-225, 1000, 298);
    glBegin(GL_POLYGON);
    glVertex3f(-75.0, -10.0, -10.0);
    glVertex3f(-75.0, 10.0, -10.0);
    glVertex3f(75.0, 10.0, -10.0);
    glVertex3f(75.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(-225, 1000, 298);
    glBegin(GL_POLYGON);
    glVertex3f(-75.0, 10.0, 10.0);
    glVertex3f(75.0, 10.0, 10.0);
    glVertex3f(75.0, 10.0, -10.0);
    glVertex3f(-75.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(-225, 1000, 298);
    glBegin(GL_POLYGON);
    glVertex3f(-75.0, 10.0, 10.0);
    glVertex3f(75.0, -10.0, 10.0);
    glVertex3f(75.0, -10.0, -10.0);
    glVertex3f(-75.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    //DEPAN 3 PANJANG
    glPushMatrix();//depan
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(0, 1150, 298);
    glBegin(GL_POLYGON);
    glVertex3f(-300.0, -10.0, 10.0);
    glVertex3f(-300.0, 10.0, 10.0);
    glVertex3f(300.0, 10.0, 10.0);
    glVertex3f(300.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(0, 1150, 298);
    glBegin(GL_POLYGON);
    glVertex3f(-300.0, -10.0, -10.0);
    glVertex3f(-300.0, 10.0, -10.0);
    glVertex3f(300.0, 10.0, -10.0);
    glVertex3f(300.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 1150, 298);
    glBegin(GL_POLYGON);
    glVertex3f(-300.0, 10.0, 10.0);
    glVertex3f(300.0, 10.0, 10.0);
    glVertex3f(300.0, 10.0, -10.0);
    glVertex3f(-300.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 1150, 298);
    glBegin(GL_POLYGON);
    glVertex3f(-300.0, 10.0, 10.0);
    glVertex3f(300.0, -10.0, 10.0);
    glVertex3f(300.0, -10.0, -10.0);
    glVertex3f(-300.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    // TURU LANTAI 3
    //BLKN 1 PENDEK
    glPushMatrix();//depan
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(225, 1000, -298);
    glBegin(GL_POLYGON);
    glVertex3f(-75.0, -10.0, 10.0);
    glVertex3f(-75.0, 10.0, 10.0);
    glVertex3f(75.0, 10.0, 10.0);
    glVertex3f(75.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(225, 1000, -298);
    glBegin(GL_POLYGON);
    glVertex3f(-75.0, -10.0, -10.0);
    glVertex3f(-75.0, 10.0, -10.0);
    glVertex3f(75.0, 10.0, -10.0);
    glVertex3f(75.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(225, 1000, -298);
    glBegin(GL_POLYGON);
    glVertex3f(-75.0, 10.0, 10.0);
    glVertex3f(75.0, 10.0, 10.0);
    glVertex3f(75.0, 10.0, -10.0);
    glVertex3f(-75.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(225, 1000, -298);
    glBegin(GL_POLYGON);
    glVertex3f(-75.0, 10.0, 10.0);
    glVertex3f(75.0, -10.0, 10.0);
    glVertex3f(75.0, -10.0, -10.0);
    glVertex3f(-75.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    //BLKN 2 PENDEK
    glPushMatrix();//depan
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-225, 1000, -298);
    glBegin(GL_POLYGON);
    glVertex3f(-75.0, -10.0, 10.0);
    glVertex3f(-75.0, 10.0, 10.0);
    glVertex3f(75.0, 10.0, 10.0);
    glVertex3f(75.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-225, 1000, -298);
    glBegin(GL_POLYGON);
    glVertex3f(-75.0, -10.0, -10.0);
    glVertex3f(-75.0, 10.0, -10.0);
    glVertex3f(75.0, 10.0, -10.0);
    glVertex3f(75.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(-225, 1000, -298);
    glBegin(GL_POLYGON);
    glVertex3f(-75.0, 10.0, 10.0);
    glVertex3f(75.0, 10.0, 10.0);
    glVertex3f(75.0, 10.0, -10.0);
    glVertex3f(-75.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(-225, 1000, -298);
    glBegin(GL_POLYGON);
    glVertex3f(-75.0, 10.0, 10.0);
    glVertex3f(75.0, -10.0, 10.0);
    glVertex3f(75.0, -10.0, -10.0);
    glVertex3f(-75.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    //BLKN 3 PANJANG
    glPushMatrix();//depan
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(0, 1150, -298);
    glBegin(GL_POLYGON);
    glVertex3f(-300.0, -10.0, 10.0);
    glVertex3f(-300.0, 10.0, 10.0);
    glVertex3f(300.0, 10.0, 10.0);
    glVertex3f(300.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(0, 1150, -298);
    glBegin(GL_POLYGON);
    glVertex3f(-300.0, -10.0, -10.0);
    glVertex3f(-300.0, 10.0, -10.0);
    glVertex3f(300.0, 10.0, -10.0);
    glVertex3f(300.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 1150, -298);
    glBegin(GL_POLYGON);
    glVertex3f(-300.0, 10.0, 10.0);
    glVertex3f(300.0, 10.0, 10.0);
    glVertex3f(300.0, 10.0, -10.0);
    glVertex3f(-300.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 1150, -298);
    glBegin(GL_POLYGON);
    glVertex3f(-300.0, 10.0, 10.0);
    glVertex3f(300.0, -10.0, 10.0);
    glVertex3f(300.0, -10.0, -10.0);
    glVertex3f(-300.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();


    //TURU KANAN
    //TKANAN 1
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(298, 1150, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -10.0, -300.0);
    glVertex3f(-10.0, 10.0, -300.0);
    glVertex3f(-10.0, 10.0, 300.0);
    glVertex3f(-10.0, -10.0, 300.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(298, 1150, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 10.0, 300.0);
    glVertex3f(10.0, 10.0, 300.0);
    glVertex3f(10.0, 10.0, -300.0);
    glVertex3f(-10.0, 10.0, -300.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(298, 1150, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 0.0, 300.0);
    glVertex3f(10.0, 0.0, 300.0);
    glVertex3f(10.0, 0.0, -300.0);
    glVertex3f(-10.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(298, 1150, 0);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -10.0, -300.0);
    glVertex3f(10.0, 10.0, -300.0);
    glVertex3f(10.0, 10.0, 300.0);
    glVertex3f(10.0, -10.0, 300.0);
    glEnd();
    glPopMatrix();

    //TKANAN 2
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(298, 1000, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -10.0, -300.0);
    glVertex3f(-10.0, 10.0, -300.0);
    glVertex3f(-10.0, 10.0, 300.0);
    glVertex3f(-10.0, -10.0, 300.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(298, 1000, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 10.0, 300.0);
    glVertex3f(10.0, 10.0, 300.0);
    glVertex3f(10.0, 10.0, -300.0);
    glVertex3f(-10.0, 10.0, -300.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(298, 1000, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 0.0, 300.0);
    glVertex3f(10.0, 0.0, 300.0);
    glVertex3f(10.0, 0.0, -300.0);
    glVertex3f(-10.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(298, 1000, 0);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -10.0, -300.0);
    glVertex3f(10.0, 10.0, -300.0);
    glVertex3f(10.0, 10.0, 300.0);
    glVertex3f(10.0, -10.0, 300.0);
    glEnd();
    glPopMatrix();


    //TURU KANAN
    //TKANAN 1
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-298, 1150, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -10.0, -300.0);
    glVertex3f(-10.0, 10.0, -300.0);
    glVertex3f(-10.0, 10.0, 300.0);
    glVertex3f(-10.0, -10.0, 300.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-298, 1150, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 10.0, 300.0);
    glVertex3f(10.0, 10.0, 300.0);
    glVertex3f(10.0, 10.0, -300.0);
    glVertex3f(-10.0, 10.0, -300.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-298, 1150, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 0.0, 300.0);
    glVertex3f(10.0, 0.0, 300.0);
    glVertex3f(10.0, 0.0, -300.0);
    glVertex3f(-10.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-298, 1150, 0);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -10.0, -300.0);
    glVertex3f(10.0, 10.0, -300.0);
    glVertex3f(10.0, 10.0, 300.0);
    glVertex3f(10.0, -10.0, 300.0);
    glEnd();
    glPopMatrix();

    //TKIRI 2
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-298, 1000, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -10.0, -300.0);
    glVertex3f(-10.0, 10.0, -300.0);
    glVertex3f(-10.0, 10.0, 300.0);
    glVertex3f(-10.0, -10.0, 300.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-298, 1000, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 10.0, 300.0);
    glVertex3f(10.0, 10.0, 300.0);
    glVertex3f(10.0, 10.0, -300.0);
    glVertex3f(-10.0, 10.0, -300.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-298, 1000, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 0.0, 300.0);
    glVertex3f(10.0, 0.0, 300.0);
    glVertex3f(10.0, 0.0, -300.0);
    glVertex3f(-10.0, 0.0, -300.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-298, 1000, 0);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -10.0, -300.0);
    glVertex3f(10.0, 10.0, -300.0);
    glVertex3f(10.0, 10.0, 300.0);
    glVertex3f(10.0, -10.0, 300.0);
    glEnd();
    glPopMatrix();


    //pintu depan l3 kanan
    glPushMatrix();//belakang kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(80, 930, 300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 150.0, 10.0);
    glVertex3f(10.0, 150.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(80, 930, 300);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 150.0, -10.0);
    glVertex3f(10.0, 150.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(80, 930, 300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 150.0, -10.0);
    glVertex3f(-10.0, 150.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(80, 930, 300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 150.0, -10.0);
    glVertex3f(10.0, 150.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();


    //pintu depan l3 kiri
    glPushMatrix();//belakang kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(-80, 930, 300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 150.0, 10.0);
    glVertex3f(10.0, 150.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(-80, 930, 300);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 150.0, -10.0);
    glVertex3f(10.0, 150.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-80, 930, 300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 150.0, -10.0);
    glVertex3f(-10.0, 150.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-80, 930, 300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 150.0, -10.0);
    glVertex3f(10.0, 150.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang mendatar pintu depan l3 atas
    glPushMatrix();//depan
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 1060, 300);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, -10.0, 10.0);
    glVertex3f(-120.0, 10.0, 10.0);
    glVertex3f(120.0, 10.0, 10.0);
    glVertex3f(120.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 1060, 300);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, -10.0, -10.0);
    glVertex3f(-120.0, 10.0, -10.0);
    glVertex3f(120.0, 10.0, -10.0);
    glVertex3f(120.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 1060, 300);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, 10.0, 10.0);
    glVertex3f(120.0, 10.0, 10.0);
    glVertex3f(120.0, 10.0, -10.0);
    glVertex3f(-120.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 1060, 300);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, 0.0, 10.0);
    glVertex3f(120.0, 0.0, 10.0);
    glVertex3f(120.0, 0.0, -10.0);
    glVertex3f(-120.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang mendatar pintu depan l3 bawah
    glPushMatrix();//depan
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 1025, 300);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, -10.0, 10.0);
    glVertex3f(-120.0, 10.0, 10.0);
    glVertex3f(120.0, 10.0, 10.0);
    glVertex3f(120.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 1025, 300);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, -10.0, -10.0);
    glVertex3f(-120.0, 10.0, -10.0);
    glVertex3f(120.0, 10.0, -10.0);
    glVertex3f(120.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 1025, 300);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, 10.0, 10.0);
    glVertex3f(120.0, 10.0, 10.0);
    glVertex3f(120.0, 10.0, -10.0);
    glVertex3f(-120.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 1025, 300);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, 0.0, 10.0);
    glVertex3f(120.0, 0.0, 10.0);
    glVertex3f(120.0, 0.0, -10.0);
    glVertex3f(-120.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //pintu belakang l3 kanan
    glPushMatrix();//belakang kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(80, 930, -300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 150.0, 10.0);
    glVertex3f(10.0, 150.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(80, 930, -300);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 150.0, -10.0);
    glVertex3f(10.0, 150.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(80, 930, -300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 150.0, -10.0);
    glVertex3f(-10.0, 150.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(80, 930, -300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 150.0, -10.0);
    glVertex3f(10.0, 150.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();


    //pintu belakang l3 kiri
    glPushMatrix();//belakang kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(-80, 930, -300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 150.0, 10.0);
    glVertex3f(10.0, 150.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(-80, 930, 300);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 150.0, -10.0);
    glVertex3f(10.0, 150.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-80, 930, -300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 150.0, -10.0);
    glVertex3f(-10.0, 150.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-80, 930, -300);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 150.0, -10.0);
    glVertex3f(10.0, 150.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang mendatar pintu depan l3 atas
    glPushMatrix();//depan
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 1060, -300);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, -10.0, 10.0);
    glVertex3f(-120.0, 10.0, 10.0);
    glVertex3f(120.0, 10.0, 10.0);
    glVertex3f(120.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 1060, -300);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, -10.0, -10.0);
    glVertex3f(-120.0, 10.0, -10.0);
    glVertex3f(120.0, 10.0, -10.0);
    glVertex3f(120.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 1060, -300);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, 10.0, 10.0);
    glVertex3f(120.0, 10.0, 10.0);
    glVertex3f(120.0, 10.0, -10.0);
    glVertex3f(-120.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 1060, -300);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, 0.0, 10.0);
    glVertex3f(120.0, 0.0, 10.0);
    glVertex3f(120.0, 0.0, -10.0);
    glVertex3f(-120.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang mendatar pintu belakang l3 bawah
    glPushMatrix();//depan
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 1025, -300);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, -10.0, 10.0);
    glVertex3f(-120.0, 10.0, 10.0);
    glVertex3f(120.0, 10.0, 10.0);
    glVertex3f(120.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 1025, -300);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, -10.0, -10.0);
    glVertex3f(-120.0, 10.0, -10.0);
    glVertex3f(120.0, 10.0, -10.0);
    glVertex3f(120.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 1025, -300);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, 10.0, 10.0);
    glVertex3f(120.0, 10.0, 10.0);
    glVertex3f(120.0, 10.0, -10.0);
    glVertex3f(-120.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 1025, -300);
    glBegin(GL_POLYGON);
    glVertex3f(-120.0, 0.0, 10.0);
    glVertex3f(120.0, 0.0, 10.0);
    glVertex3f(120.0, 0.0, -10.0);
    glVertex3f(-120.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //ORNAMEN LANTAI 4
    // TURU L4
     //TKANAN 1
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-248, 1650, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -10.0, -250.0);
    glVertex3f(-10.0, 10.0, -250.0);
    glVertex3f(-10.0, 10.0, 250.0);
    glVertex3f(-10.0, -10.0, 250.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-248, 1650, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 10.0, 250.0);
    glVertex3f(10.0, 10.0, 250.0);
    glVertex3f(10.0, 10.0, -250.0);
    glVertex3f(-10.0, 10.0, -250.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-248, 1650, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 10.0, 250.0);
    glVertex3f(10.0, -10.0, 250.0);
    glVertex3f(10.0, 10.0, -250.0);
    glVertex3f(-10.0, 10.0, -250.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-248, 1650, 0);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -10.0, -200.0);
    glVertex3f(10.0, 10.0, -200.0);
    glVertex3f(10.0, 10.0, 200.0);
    glVertex3f(10.0, -10.0, 200.0);
    glEnd();
    glPopMatrix();

    //TKiri 1
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(248, 1650, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -10.0, -250.0);
    glVertex3f(-10.0, 10.0, -250.0);
    glVertex3f(-10.0, 10.0, 250.0);
    glVertex3f(-10.0, -10.0, 250.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(248, 1650, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 10.0, 250.0);
    glVertex3f(10.0, 10.0, 250.0);
    glVertex3f(10.0, 10.0, -250.0);
    glVertex3f(-10.0, 10.0, -250.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(248, 1650, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -10.0, 250.0);
    glVertex3f(10.0, -10.0, 250.0);
    glVertex3f(10.0, -10.0, -250.0);
    glVertex3f(-10.0, -10.0, -250.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(248, 1650, 0);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -10.0, -250.0);
    glVertex3f(10.0, 10.0, -250.0);
    glVertex3f(10.0, 10.0, 250.0);
    glVertex3f(10.0, -10.0, 250.0);
    glEnd();
    glPopMatrix();


    //TKiri 2
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(248, 1450, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -10.0, -250.0);
    glVertex3f(-10.0, 10.0, -250.0);
    glVertex3f(-10.0, 10.0, 250.0);
    glVertex3f(-10.0, -10.0, 250.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(248, 1450, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 10.0, 250.0);
    glVertex3f(10.0, 10.0, 250.0);
    glVertex3f(10.0, 10.0, -250.0);
    glVertex3f(-10.0, 10.0, -250.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(248, 1450, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -10.0, 250.0);
    glVertex3f(10.0, -10.0, 250.0);
    glVertex3f(10.0, -10.0, -250.0);
    glVertex3f(-10.0, -10.0, -250.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(248, 1450, 0);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -10.0, -250.0);
    glVertex3f(10.0, 10.0, -250.0);
    glVertex3f(10.0, 10.0, 250.0);
    glVertex3f(10.0, -10.0, 250.0);
    glEnd();
    glPopMatrix();

    //Tkanan 2
    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-248, 1450, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -10.0, -250.0);
    glVertex3f(-10.0, 10.0, -250.0);
    glVertex3f(-10.0, 10.0, 250.0);
    glVertex3f(-10.0, -10.0, 250.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-248, 1450, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 10.0, 250.0);
    glVertex3f(10.0, 10.0, 250.0);
    glVertex3f(10.0, 10.0, -250.0);
    glVertex3f(-10.0, 10.0, -250.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-248, 1450, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -10.0, 250.0);
    glVertex3f(10.0, -10.0, 250.0);
    glVertex3f(10.0, -10.0, -250.0);
    glVertex3f(-10.0, -10.0, -250.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslatef(-248, 1450, 0);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -10.0, -250.0);
    glVertex3f(10.0, 10.0, -250.0);
    glVertex3f(10.0, 10.0, 250.0);
    glVertex3f(10.0, -10.0, 250.0);
    glEnd();
    glPopMatrix();


    //Kiri orange 1
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(248, 1400, -123);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.5, 0);
    glTranslatef(248, 1400, -123);;
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(248, 1400, -123);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(248, 1400, -123);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //Kiri orange 2
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(248, 1400, 123);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.5, 0);
    glTranslatef(248, 1400, 123);;
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(248, 1400, 123);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(248, 1400, 123);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //Kiri orange 1
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(-248, 1400, -123);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.5, 0);
    glTranslatef(-248, 1400, -123);;
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(-248, 1400, -123);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(-248, 1400, -123);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //Kiri orange 2
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(-248, 1400, 123);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.5, 0);
    glTranslatef(-248, 1400, 123);;
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(-248, 1400, 123);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.5, 0);
    glTranslatef(-248, 1400, 123);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //depan kanan
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-250, 1400, 250);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(-250, 1400, 250);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-250, 1400, 250);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-250, 1400, 250);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();


    //DEPAN KIRI
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(250, 1400, 250);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(250, 1400, 250);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(250, 1400, 250);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(250, 1400, 250);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();


    //BELAKANG KIRI
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-250, 1400, -250);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(-250, 1400, -250);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-250, 1400, -250);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-250, 1400, -250);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();


    //BELAKANG KANAN
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(250, 1400, -250);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(250, 1400, -250);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(250, 1400, -250);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(-10.0, 300.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(250, 1400, -250);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 300.0, -10.0);
    glVertex3f(10.0, 300.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //pintu depan l4 kanan
    glPushMatrix();//belakang kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(80, 1400, 250);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 250.0, 10.0);
    glVertex3f(10.0, 250.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(80, 1400, 250);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 250.0, -10.0);
    glVertex3f(10.0, 250.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(80, 1400, 250);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 250.0, -10.0);
    glVertex3f(-10.0, 250.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(80, 1400, 250);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 250.0, -10.0);
    glVertex3f(10.0, 250.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();


    //pintu depan l4 kiri
    glPushMatrix();//belakang kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(-80, 1400, 250);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 250.0, 10.0);
    glVertex3f(10.0, 250.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(-80, 1400, 250);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 250.0, -10.0);
    glVertex3f(10.0, 250.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-80, 1400, 250);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 250.0, -10.0);
    glVertex3f(-10.0, 250.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-80, 1400, 250);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 250.0, -10.0);
    glVertex3f(10.0, 250.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang mendatar pintu depan l4 atas
    glPushMatrix();//depan
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 1635, 250);
    glBegin(GL_POLYGON);
    glVertex3f(-200.0, -10.0, 10.0);
    glVertex3f(-200.0, 10.0, 10.0);
    glVertex3f(200.0, 10.0, 10.0);
    glVertex3f(200.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 1635, 250);
    glBegin(GL_POLYGON);
    glVertex3f(-200.0, -10.0, -10.0);
    glVertex3f(-200.0, 10.0, -10.0);
    glVertex3f(200.0, 10.0, -10.0);
    glVertex3f(200.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 1635, 250);
    glBegin(GL_POLYGON);
    glVertex3f(-200.0, 10.0, 10.0);
    glVertex3f(200.0, 10.0, 10.0);
    glVertex3f(200.0, 10.0, -10.0);
    glVertex3f(-200.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 1635, 250);
    glBegin(GL_POLYGON);
    glVertex3f(-200.0, 0.0, 10.0);
    glVertex3f(200.0, 0.0, 10.0);
    glVertex3f(200.0, 0.0, -10.0);
    glVertex3f(-200.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang mendatar pintu depan l4 tengah
    glPushMatrix();//depan
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 1600, 250);
    glBegin(GL_POLYGON);
    glVertex3f(-200.0, -10.0, 10.0);
    glVertex3f(-200.0, 10.0, 10.0);
    glVertex3f(200.0, 10.0, 10.0);
    glVertex3f(200.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 1600, 250);
    glBegin(GL_POLYGON);
    glVertex3f(-200.0, -10.0, -10.0);
    glVertex3f(-200.0, 10.0, -10.0);
    glVertex3f(200.0, 10.0, -10.0);
    glVertex3f(200.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 1600, 250);
    glBegin(GL_POLYGON);
    glVertex3f(-200.0, 10.0, 10.0);
    glVertex3f(200.0, 10.0, 10.0);
    glVertex3f(200.0, 10.0, -10.0);
    glVertex3f(-200.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 1600, 250);
    glBegin(GL_POLYGON);
    glVertex3f(-200.0, 0.0, 10.0);
    glVertex3f(200.0, 0.0, 10.0);
    glVertex3f(200.0, 0.0, -10.0);
    glVertex3f(-200.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang mendatar pintu depan l4 bawah
    glPushMatrix();//depan
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 1565, 250);
    glBegin(GL_POLYGON);
    glVertex3f(-200.0, -10.0, 10.0);
    glVertex3f(-200.0, 10.0, 10.0);
    glVertex3f(200.0, 10.0, 10.0);
    glVertex3f(200.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 1565, 250);
    glBegin(GL_POLYGON);
    glVertex3f(-200.0, -10.0, -10.0);
    glVertex3f(-200.0, 10.0, -10.0);
    glVertex3f(200.0, 10.0, -10.0);
    glVertex3f(200.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 1565, 250);
    glBegin(GL_POLYGON);
    glVertex3f(-200.0, 10.0, 10.0);
    glVertex3f(200.0, 10.0, 10.0);
    glVertex3f(200.0, 10.0, -10.0);
    glVertex3f(-200.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 1565, 250);
    glBegin(GL_POLYGON);
    glVertex3f(-200.0, 0.0, 10.0);
    glVertex3f(200.0, 0.0, 10.0);
    glVertex3f(200.0, 0.0, -10.0);
    glVertex3f(-200.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //pintu belakang l4 kanan
    glPushMatrix();//belakang kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(80, 1400, -250);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 250.0, 10.0);
    glVertex3f(10.0, 250.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(80, 1400, -250);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 250.0, -10.0);
    glVertex3f(10.0, 250.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(80, 1400, -250);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 250.0, -10.0);
    glVertex3f(-10.0, 250.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(80, 1400, -250);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 250.0, -10.0);
    glVertex3f(10.0, 250.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();


    //pintu belakang l4 kiri
    glPushMatrix();//belakang kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(-80, 1400, -250);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, 10.0);
    glVertex3f(-10.0, 250.0, 10.0);
    glVertex3f(10.0, 250.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//kanan
    glColor3f(1, 0.0, 0);
    glTranslatef(-80, 1400, -250);
    glBegin(GL_POLYGON);
    glVertex3f(10.0, -50.0, -10.0);
    glVertex3f(10.0, 250.0, -10.0);
    glVertex3f(10.0, 250.0, 10.0);
    glVertex3f(10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //kiri
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-80, 1400, -250);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 250.0, -10.0);
    glVertex3f(-10.0, 250.0, 10.0);
    glVertex3f(-10.0, -50.0, 10.0);
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glColor3f(1, 0.0, 0);
    glTranslatef(-80, 1400, -250);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, -50.0, -10.0);
    glVertex3f(-10.0, 250.0, -10.0);
    glVertex3f(10.0, 250.0, -10.0);
    glVertex3f(10.0, -50.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang mendatar pintu belakang l4 atas
    glPushMatrix();//depan
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 1635, -250);
    glBegin(GL_POLYGON);
    glVertex3f(-200.0, -10.0, 10.0);
    glVertex3f(-200.0, 10.0, 10.0);
    glVertex3f(200.0, 10.0, 10.0);
    glVertex3f(200.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 1635, -250);
    glBegin(GL_POLYGON);
    glVertex3f(-200.0, -10.0, -10.0);
    glVertex3f(-200.0, 10.0, -10.0);
    glVertex3f(200.0, 10.0, -10.0);
    glVertex3f(200.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 1635, -250);
    glBegin(GL_POLYGON);
    glVertex3f(-200.0, 10.0, 10.0);
    glVertex3f(200.0, 10.0, 10.0);
    glVertex3f(200.0, 10.0, -10.0);
    glVertex3f(-200.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 1635, -250);
    glBegin(GL_POLYGON);
    glVertex3f(-200.0, 0.0, 10.0);
    glVertex3f(200.0, 0.0, 10.0);
    glVertex3f(200.0, 0.0, -10.0);
    glVertex3f(-200.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang mendatar pintu belakang l4 tengah
    glPushMatrix();//depan
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 1600, -250);
    glBegin(GL_POLYGON);
    glVertex3f(-200.0, -10.0, 10.0);
    glVertex3f(-200.0, 10.0, 10.0);
    glVertex3f(200.0, 10.0, 10.0);
    glVertex3f(200.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 1600, -250);
    glBegin(GL_POLYGON);
    glVertex3f(-200.0, -10.0, -10.0);
    glVertex3f(-200.0, 10.0, -10.0);
    glVertex3f(200.0, 10.0, -10.0);
    glVertex3f(200.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 1600, -250);
    glBegin(GL_POLYGON);
    glVertex3f(-200.0, 10.0, 10.0);
    glVertex3f(200.0, 10.0, 10.0);
    glVertex3f(200.0, 10.0, -10.0);
    glVertex3f(-200.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 1600, -250);
    glBegin(GL_POLYGON);
    glVertex3f(-200.0, 0.0, 10.0);
    glVertex3f(200.0, 0.0, 10.0);
    glVertex3f(200.0, 0.0, -10.0);
    glVertex3f(-200.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //tiang mendatar pintu belakang l4 bawah
    glPushMatrix();//depan
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 1565, -250);
    glBegin(GL_POLYGON);
    glVertex3f(-200.0, -10.0, 10.0);
    glVertex3f(-200.0, 10.0, 10.0);
    glVertex3f(200.0, 10.0, 10.0);
    glVertex3f(200.0, -10.0, 10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//belakang
    glColor3f(1.0, 0.0, 0.0);
    glTranslatef(0, 1565, -250);
    glBegin(GL_POLYGON);
    glVertex3f(-200.0, -10.0, -10.0);
    glVertex3f(-200.0, 10.0, -10.0);
    glVertex3f(200.0, 10.0, -10.0);
    glVertex3f(200.0, -10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//atas
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 1565, -250);
    glBegin(GL_POLYGON);
    glVertex3f(-200.0, 10.0, 10.0);
    glVertex3f(200.0, 10.0, 10.0);
    glVertex3f(200.0, 10.0, -10.0);
    glVertex3f(-200.0, 10.0, -10.0);
    glEnd();
    glPopMatrix();

    glPushMatrix();//bawah
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(30);
    glTranslatef(0, 1565, -250);
    glBegin(GL_POLYGON);
    glVertex3f(-200.0, 0.0, 10.0);
    glVertex3f(200.0, 0.0, 10.0);
    glVertex3f(200.0, 0.0, -10.0);
    glVertex3f(-200.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    //pagar lantai 2

        // pagar l1 depan ( kiri depan)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan(kanan depan)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();



    //pagar l1 samping kanan (titik tengah)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, 0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 samping kanan (tengah kiri 1)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, 345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, 345);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, 345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, 345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar l1 samping kanan(tengah kiri 1)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar l1 samping kanan (tengah kiri2)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, 520);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(10.96, 0.06, 0.06);
    glTranslatef(690, 500, 520);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, 520);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, 520);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 samping kanan (tengah kanan)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, -345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, -345);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, -345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, -345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar l1 samping kanan(tengah kanan 1)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, -172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, -172.5);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, -172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, -172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar l1 samping kanan (tengah kanan2)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, -520);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, -520);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, -520);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, -520);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar l1 samping kiri (titik tengah)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, 0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 samping kiri (tengah kiri 1)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, 345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, 345);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, 345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, 345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar l1 samping kiri(tengah kiri 1)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar l1 samping kiri (tengah kiri2)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, 520);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, 520);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, 520);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, 520);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 samping kiri (tengah kanan)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, -345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, -345);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, -345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, -345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar l1 samping kiri(tengah kanan 1)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, -172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, -172.5);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, -172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, -172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 samping kanan (tengah kanan2)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, -520);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, -520);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, -520);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, -520);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (titik tengah)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(0, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(0, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(0, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(0, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kiri)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan 1)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-172.5, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-172.5, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-172.5, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-172.5, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan 2)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-520, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-520, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-520, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-520, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(345, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(345, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(345, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(345, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan 1)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(172.5, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(172.5, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(172.5, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(172.5, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan 2)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(520, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(520, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(520, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(520, 500, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();



    // pagar l1 (kiri belakang)
    //pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-690, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 (kanan belakang)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(690, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 belakang (titik tengah)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(0, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(0, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(0, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(0, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kiri)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan 1)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-172.5, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-172.5, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-172.5, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-172.5, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan 2)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-520, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-520, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-520, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-520, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(345, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(345, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(345, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(345, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan 1)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(172.5, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(172.5, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(172.5, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(172.5, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan 2)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(520, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(520, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(520, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(520, 500, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar tidur depan atas
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 570, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-690.0, -50.0, 5.0);
    glVertex3f(-690.0, -40.0, 5.0);
    glVertex3f(690.0, -40.0, 5.0);
    glVertex3f(690.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 570, 690);
    glBegin(GL_POLYGON);
    glVertex3f(690.0, -50.0, -5.0);
    glVertex3f(690.0, -40.0, -5.0);
    glVertex3f(690.0, -40.0, 5.0);
    glVertex3f(690.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 550, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-690.0, -50.0, -5.0);
    glVertex3f(-690.0, -40.0, -5.0);
    glVertex3f(-690.0, -40.0, 5.0);
    glVertex3f(-690.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 570, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-690.0, -50.0, -5.0);
    glVertex3f(-690.0, -40.0, -5.0);
    glVertex3f(690.0, -40.0, -5.0);
    glVertex3f(690.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar tidur dean tengah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 550, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-690.0, -50.0, 5.0);
    glVertex3f(-690.0, -40.0, 5.0);
    glVertex3f(690.0, -40.0, 5.0);
    glVertex3f(690.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 550, 690);
    glBegin(GL_POLYGON);
    glVertex3f(690.0, -50.0, -5.0);
    glVertex3f(690.0, -40.0, -5.0);
    glVertex3f(690.0, -40.0, 5.0);
    glVertex3f(690.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 550, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-690.0, -50.0, -5.0);
    glVertex3f(-690.0, -40.0, -5.0);
    glVertex3f(-690.0, -40.0, 5.0);
    glVertex3f(-690.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 550, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-690.0, -50.0, -5.0);
    glVertex3f(-690.0, -40.0, -5.0);
    glVertex3f(690.0, -40.0, -5.0);
    glVertex3f(690.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    // pagar tidur dean bawah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 530, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-690.0, -50.0, 5.0);
    glVertex3f(-690.0, -40.0, 5.0);
    glVertex3f(690.0, -40.0, 5.0);
    glVertex3f(690.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan 
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 530, 690);
    glBegin(GL_POLYGON);
    glVertex3f(690.0, -50.0, -5.0);
    glVertex3f(690.0, -40.0, -5.0);
    glVertex3f(690.0, -40.0, 5.0);
    glVertex3f(690.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 530, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-690.0, -50.0, -5.0);
    glVertex3f(-690.0, -40.0, -5.0);
    glVertex3f(-690.0, -40.0, 5.0);
    glVertex3f(-690.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 530, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-690.0, -50.0, -5.0);
    glVertex3f(-690.0, -40.0, -5.0);
    glVertex3f(690.0, -40.0, -5.0);
    glVertex3f(690.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    // pagar tidur bawah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 510, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-690.0, -50.0, 5.0);
    glVertex3f(-690.0, -40.0, 5.0);
    glVertex3f(690.0, -40.0, 5.0);
    glVertex3f(690.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 510, 690);
    glBegin(GL_POLYGON);
    glVertex3f(690.0, -50.0, -5.0);
    glVertex3f(690.0, -40.0, -5.0);
    glVertex3f(690.0, -40.0, 5.0);
    glVertex3f(690.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 510, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-690.0, -50.0, -5.0);
    glVertex3f(-690.0, -40.0, -5.0);
    glVertex3f(-690.0, -40.0, 5.0);
    glVertex3f(-690.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 510, 690);
    glBegin(GL_POLYGON);
    glVertex3f(-690.0, -50.0, -5.0);
    glVertex3f(-690.0, -40.0, -5.0);
    glVertex3f(690.0, -40.0, -5.0);
    glVertex3f(690.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar tidur kanan atas
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(690.0, 570, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 690.0);
    glVertex3f(-5.0, -40.0, 690.0);
    glVertex3f(5.0, -40.0, 690.0);
    glVertex3f(5.0, -50.0, 690.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(690.0, 570, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -690.0);
    glVertex3f(5.0, -40.0, -690.0);
    glVertex3f(5.0, -40.0, 690.0);
    glVertex3f(5.0, -50.0, 690.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(690.0, 570, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -690.0);
    glVertex3f(-5.0, -40.0, -690.0);
    glVertex3f(-5.0, -40.0, 690.0);
    glVertex3f(-5.0, -50.0, 690.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(690.0, 570, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -690.0);
    glVertex3f(-5.0, -40.0, -690.0);
    glVertex3f(5.0, -40.0, -690.0);
    glVertex3f(5.0, -50.0, -690.0);
    glEnd();
    glPopMatrix();

    // pagar tidur kanan tengah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(690.0, 550, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 690.0);
    glVertex3f(-5.0, -40.0, 690.0);
    glVertex3f(5.0, -40.0, 690.0);
    glVertex3f(5.0, -50.0, 690.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(690.0, 550, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -690.0);
    glVertex3f(5.0, -40.0, -690.0);
    glVertex3f(5.0, -40.0, 690.0);
    glVertex3f(5.0, -50.0, 690.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(690.0, 550, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -690.0);
    glVertex3f(-5.0, -40.0, -690.0);
    glVertex3f(-5.0, -40.0, 690.0);
    glVertex3f(-5.0, -50.0, 690.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(690.0, 550, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -690.0);
    glVertex3f(-5.0, -40.0, -690.0);
    glVertex3f(5.0, -40.0, -690.0);
    glVertex3f(5.0, -50.0, -690.0);
    glEnd();
    glPopMatrix();

    // pagar tidur kanan tengah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(690.0, 530, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 690.0);
    glVertex3f(-5.0, -40.0, 690.0);
    glVertex3f(5.0, -40.0, 690.0);
    glVertex3f(5.0, -50.0, 690.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(690.0, 530, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -690.0);
    glVertex3f(5.0, -40.0, -690.0);
    glVertex3f(5.0, -40.0, 690.0);
    glVertex3f(5.0, -50.0, 690.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(690.0, 530, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -690.0);
    glVertex3f(-5.0, -40.0, -690.0);
    glVertex3f(-5.0, -40.0, 690.0);
    glVertex3f(-5.0, -50.0, 690.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(690.0, 530, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -690.0);
    glVertex3f(-5.0, -40.0, -690.0);
    glVertex3f(5.0, -40.0, -690.0);
    glVertex3f(5.0, -50.0, -690.0);
    glEnd();
    glPopMatrix();

    // pagar tidur kanan bawah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(690.0, 510, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 690.0);
    glVertex3f(-5.0, -40.0, 690.0);
    glVertex3f(5.0, -40.0, 690.0);
    glVertex3f(5.0, -50.0, 690.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(690.0, 510, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -690.0);
    glVertex3f(5.0, -40.0, -690.0);
    glVertex3f(5.0, -40.0, 690.0);
    glVertex3f(5.0, -50.0, 690.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(690.0, 510, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -690.0);
    glVertex3f(-5.0, -40.0, -690.0);
    glVertex3f(-5.0, -40.0, 690.0);
    glVertex3f(-5.0, -50.0, 690.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(690.0, 510, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -690.0);
    glVertex3f(-5.0, -40.0, -690.0);
    glVertex3f(5.0, -40.0, -690.0);
    glVertex3f(5.0, -50.0, -690.0);
    glEnd();
    glPopMatrix();

    // pagar tidur kiri atas
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-690.0, 570, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 690.0);
    glVertex3f(-5.0, -40.0, 690.0);
    glVertex3f(5.0, -40.0, 690.0);
    glVertex3f(5.0, -50.0, 690.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-690.0, 570, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -690.0);
    glVertex3f(5.0, -40.0, -690.0);
    glVertex3f(5.0, -40.0, 690.0);
    glVertex3f(5.0, -50.0, 690.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-690.0, 570, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -690.0);
    glVertex3f(-5.0, -40.0, -690.0);
    glVertex3f(-5.0, -40.0, 690.0);
    glVertex3f(-5.0, -50.0, 690.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-690.0, 570, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -690.0);
    glVertex3f(-5.0, -40.0, -690.0);
    glVertex3f(5.0, -40.0, -690.0);
    glVertex3f(5.0, -50.0, -690.0);
    glEnd();
    glPopMatrix();

    // pagar tidur kiri tengah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-690.0, 550, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 690.0);
    glVertex3f(-5.0, -40.0, 690.0);
    glVertex3f(5.0, -40.0, 690.0);
    glVertex3f(5.0, -50.0, 690.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-690.0, 550, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -690.0);
    glVertex3f(5.0, -40.0, -690.0);
    glVertex3f(5.0, -40.0, 690.0);
    glVertex3f(5.0, -50.0, 690.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-690.0, 550, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -690.0);
    glVertex3f(-5.0, -40.0, -690.0);
    glVertex3f(-5.0, -40.0, 690.0);
    glVertex3f(-5.0, -50.0, 690.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-690.0, 550, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -690.0);
    glVertex3f(-5.0, -40.0, -690.0);
    glVertex3f(5.0, -40.0, -690.0);
    glVertex3f(5.0, -50.0, -690.0);
    glEnd();
    glPopMatrix();

    // pagar tidur kiri tengah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-690.0, 530, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 690.0);
    glVertex3f(-5.0, -40.0, 690.0);
    glVertex3f(5.0, -40.0, 690.0);
    glVertex3f(5.0, -50.0, 690.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-690.0, 530, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -690.0);
    glVertex3f(5.0, -40.0, -690.0);
    glVertex3f(5.0, -40.0, 690.0);
    glVertex3f(5.0, -50.0, 690.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-690.0, 530, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -690.0);
    glVertex3f(-5.0, -40.0, -690.0);
    glVertex3f(-5.0, -40.0, 690.0);
    glVertex3f(-5.0, -50.0, 690.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-690.0, 530, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -690.0);
    glVertex3f(-5.0, -40.0, -690.0);
    glVertex3f(5.0, -40.0, -690.0);
    glVertex3f(5.0, -50.0, -690.0);
    glEnd();
    glPopMatrix();

    // pagar tidur kiri bawah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-690.0, 510, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 690.0);
    glVertex3f(-5.0, -40.0, 690.0);
    glVertex3f(5.0, -40.0, 690.0);
    glVertex3f(5.0, -50.0, 690.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-690.0, 510, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -690.0);
    glVertex3f(5.0, -40.0, -690.0);
    glVertex3f(5.0, -40.0, 690.0);
    glVertex3f(5.0, -50.0, 690.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-690.0, 510, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -690.0);
    glVertex3f(-5.0, -40.0, -690.0);
    glVertex3f(-5.0, -40.0, 690.0);
    glVertex3f(-5.0, -50.0, 690.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-690.0, 510, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -690.0);
    glVertex3f(-5.0, -40.0, -690.0);
    glVertex3f(5.0, -40.0, -690.0);
    glVertex3f(5.0, -50.0, -690.0);
    glEnd();
    glPopMatrix();

    // pagar tidur belakang atas
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 570, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-690.0, -50.0, 5.0);
    glVertex3f(-690.0, -40.0, 5.0);
    glVertex3f(690.0, -40.0, 5.0);
    glVertex3f(690.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 570, -690);
    glBegin(GL_POLYGON);
    glVertex3f(690.0, -50.0, -5.0);
    glVertex3f(690.0, -40.0, -5.0);
    glVertex3f(690.0, -40.0, 5.0);
    glVertex3f(690.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 570, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-690.0, -50.0, -5.0);
    glVertex3f(-690.0, -40.0, -5.0);
    glVertex3f(-690.0, -40.0, 5.0);
    glVertex3f(-690.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 570, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-690.0, -50.0, -5.0);
    glVertex3f(-690.0, -40.0, -5.0);
    glVertex3f(690.0, -40.0, -5.0);
    glVertex3f(690.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    //pagar tidur belakang tengah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 550, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-690.0, -50.0, 5.0);
    glVertex3f(-690.0, -40.0, 5.0);
    glVertex3f(690.0, -40.0, 5.0);
    glVertex3f(690.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.216);
    glTranslatef(0.0, 550, -690);
    glBegin(GL_POLYGON);
    glVertex3f(690.0, -50.0, -5.0);
    glVertex3f(690.0, -40.0, -5.0);
    glVertex3f(690.0, -40.0, 5.0);
    glVertex3f(690.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 550, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-690.0, -50.0, -5.0);
    glVertex3f(-690.0, -40.0, -5.0);
    glVertex3f(-690.0, -40.0, 5.0);
    glVertex3f(-690.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 550, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-690.0, -50.0, -5.0);
    glVertex3f(-690.0, -40.0, -5.0);
    glVertex3f(690.0, -40.0, -5.0);
    glVertex3f(690.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    //pagar tidur belakang tengah2
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 530, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-690.0, -50.0, 5.0);
    glVertex3f(-690.0, -40.0, 5.0);
    glVertex3f(690.0, -40.0, 5.0);
    glVertex3f(690.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 530, -690);
    glBegin(GL_POLYGON);
    glVertex3f(690.0, -50.0, -5.0);
    glVertex3f(690.0, -40.0, -5.0);
    glVertex3f(690.0, -40.0, 5.0);
    glVertex3f(690.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 530, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-690.0, -50.0, -5.0);
    glVertex3f(-690.0, -40.0, -5.0);
    glVertex3f(-690.0, -40.0, 5.0);
    glVertex3f(-690.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 530, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-690.0, -50.0, -5.0);
    glVertex3f(-690.0, -40.0, -5.0);
    glVertex3f(690.0, -40.0, -5.0);
    glVertex3f(690.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    //pagar tidur belakang bawah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 510, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-690.0, -50.0, 5.0);
    glVertex3f(-690.0, -40.0, 5.0);
    glVertex3f(690.0, -40.0, 5.0);
    glVertex3f(690.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 510, -690);
    glBegin(GL_POLYGON);
    glVertex3f(690.0, -50.0, -5.0);
    glVertex3f(690.0, -40.0, -5.0);
    glVertex3f(690.0, -40.0, 5.0);
    glVertex3f(690.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 510, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-690.0, -50.0, -5.0);
    glVertex3f(-690.0, -40.0, -5.0);
    glVertex3f(-690.0, -40.0, 5.0);
    glVertex3f(-690.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 510, -690);
    glBegin(GL_POLYGON);
    glVertex3f(-690.0, -50.0, -5.0);
    glVertex3f(-690.0, -40.0, -5.0);
    glVertex3f(690.0, -40.0, -5.0);
    glVertex3f(690.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //Pagar lantai 3
    // pagar l1 depan ( kiri depan)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();



    // pagar l1 depan(kanan depan)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 (kiri belakang)
    //pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 (kanan belakang)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar l1 samping kanan (titik tengah)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, 0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar l1 samping kanan (tengah kiri 1)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, 345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, 345);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, 345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, 345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar l1 samping kanan(tengah kiri 2)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar l1 samping kanan (tengah kiri2)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 samping kanan (tengah kanan)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, -345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, -345);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, -345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, -345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar l1 samping kanan(tengah kanan 1)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, -172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glVertex3f(5.0, 40.0, 5.0);
    glTranslatef(440, 930, -172.5);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, -172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, -172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar l1 samping kanan (tengah kanan2)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 9300, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar l1 samping kiri (titik tengah)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, 0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 samping kiri (tengah kiri 1)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, 345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, 345);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, 345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, 345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar l1 samping kiri(tengah kiri 1)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar l1 samping kiri (tengah kiri2)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 samping kiri (tengah kanan)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, -345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, -345);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, -345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, -345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar l1 samping kiri(tengah kanan 1)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, -172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, -172.5);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, -172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, -172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 samping kanan (tengah kanan2)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    // pagar l1 depan (titik tengah)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(0, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(0, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(0, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(0, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kiri)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan 1)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-172.5, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-172.5, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-172.5, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-172.5, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan 2)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(345, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(345, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(345, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(345, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan 1)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(172.5, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(172.5, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(172.5, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(172.5, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan 2)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 030, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    // pagar l1 belakang (titik tengah)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(0, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(0, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(0, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(0, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kiri)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan 1)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-172.5, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-172.5, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-172.5, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-172.5, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan 2)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-440, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(345, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(345, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(345, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(345, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan 1)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(172.5, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(172.5, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(172.5, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(172.5, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan 2)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(440, 930, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    // pagar tidur depan atas
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1000, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-440.0, -50.0, 5.0);
    glVertex3f(-440.0, -40.0, 5.0);
    glVertex3f(440.0, -40.0, 5.0);
    glVertex3f(440.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1000, 440);
    glBegin(GL_POLYGON);
    glVertex3f(440.0, -50.0, -5.0);
    glVertex3f(440.0, -40.0, -5.0);
    glVertex3f(440.0, -40.0, 5.0);
    glVertex3f(440.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1000, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-440.0, -50.0, -5.0);
    glVertex3f(-440.0, -40.0, -5.0);
    glVertex3f(-440.0, -40.0, 5.0);
    glVertex3f(-440.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1000, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-440.0, -50.0, -5.0);
    glVertex3f(-440.0, -40.0, -5.0);
    glVertex3f(440.0, -40.0, -5.0);
    glVertex3f(440.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();



    // pagar tidur depan tengah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 980, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-440.0, -50.0, 5.0);
    glVertex3f(-440.0, -40.0, 5.0);
    glVertex3f(440.0, -40.0, 5.0);
    glVertex3f(440.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 980, 440);
    glBegin(GL_POLYGON);
    glVertex3f(440.0, -50.0, -5.0);
    glVertex3f(440.0, -40.0, -5.0);
    glVertex3f(440.0, -40.0, 5.0);
    glVertex3f(440.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 980, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-440.0, -50.0, -5.0);
    glVertex3f(-440.0, -40.0, -5.0);
    glVertex3f(-440.0, -40.0, 5.0);
    glVertex3f(-440.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 980, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-440.0, -50.0, -5.0);
    glVertex3f(-440.0, -40.0, -5.0);
    glVertex3f(440.0, -40.0, -5.0);
    glVertex3f(440.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    // pagar tidur depan bawah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 960, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-440.0, -50.0, 5.0);
    glVertex3f(-440.0, -40.0, 5.0);
    glVertex3f(440.0, -40.0, 5.0);
    glVertex3f(440.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan 
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 960, 440);
    glBegin(GL_POLYGON);
    glVertex3f(440.0, -50.0, -5.0);
    glVertex3f(440.0, -40.0, -5.0);
    glVertex3f(440.0, -40.0, 5.0);
    glVertex3f(440.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 960, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-440.0, -50.0, -5.0);
    glVertex3f(-440.0, -40.0, -5.0);
    glVertex3f(-440.0, -40.0, 5.0);
    glVertex3f(-440.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 960, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-440.0, -50.0, -5.0);
    glVertex3f(-440.0, -40.0, -5.0);
    glVertex3f(440.0, -40.0, -5.0);
    glVertex3f(440.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    // pagar tidur bawah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 940, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-440.0, -50.0, 5.0);
    glVertex3f(-440.0, -40.0, 5.0);
    glVertex3f(440.0, -40.0, 5.0);
    glVertex3f(440.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 940, 440);
    glBegin(GL_POLYGON);
    glVertex3f(440.0, -50.0, -5.0);
    glVertex3f(440.0, -40.0, -5.0);
    glVertex3f(440.0, -40.0, 5.0);
    glVertex3f(440.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 940, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-440.0, -50.0, -5.0);
    glVertex3f(-440.0, -40.0, -5.0);
    glVertex3f(-440.0, -40.0, 5.0);
    glVertex3f(-440.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 940, 440);
    glBegin(GL_POLYGON);
    glVertex3f(-440.0, -50.0, -5.0);
    glVertex3f(-440.0, -40.0, -5.0);
    glVertex3f(440.0, -40.0, -5.0);
    glVertex3f(440.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar tidur kanan atas
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(440.0, 1000, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 440.0);
    glVertex3f(-5.0, -40.0, 440.0);
    glVertex3f(5.0, -40.0, 440.0);
    glVertex3f(5.0, -50.0, 440.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(440.0, 1000, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -440.0);
    glVertex3f(5.0, -40.0, -440.0);
    glVertex3f(5.0, -40.0, 440.0);
    glVertex3f(5.0, -50.0, 440.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(440.0, 1000, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -440.0);
    glVertex3f(-5.0, -40.0, -440.0);
    glVertex3f(-5.0, -40.0, 440.0);
    glVertex3f(-5.0, -50.0, 440.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(440.0, 1000, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -440.0);
    glVertex3f(-5.0, -40.0, -440.0);
    glVertex3f(5.0, -40.0, -440.0);
    glVertex3f(5.0, -50.0, -440.0);
    glEnd();
    glPopMatrix();


    // pagar tidur kanan tengah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(440.0, 980, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 440.0);
    glVertex3f(-5.0, -40.0, 440.0);
    glVertex3f(5.0, -40.0, 440.0);
    glVertex3f(5.0, -50.0, 440.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(440.0, 980, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -440.0);
    glVertex3f(5.0, -40.0, -440.0);
    glVertex3f(5.0, -40.0, 440.0);
    glVertex3f(5.0, -50.0, 440.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(440.0, 980, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -440.0);
    glVertex3f(-5.0, -40.0, -440.0);
    glVertex3f(-5.0, -40.0, 440.0);
    glVertex3f(-5.0, -50.0, 440.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(440.0, 980, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -440.0);
    glVertex3f(-5.0, -40.0, -440.0);
    glVertex3f(5.0, -40.0, -440.0);
    glVertex3f(5.0, -50.0, -440.0);
    glEnd();
    glPopMatrix();


    // pagar tidur kanan tengah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(440.0, 960, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 440.0);
    glVertex3f(-5.0, -40.0, 440.0);
    glVertex3f(5.0, -40.0, 440.0);
    glVertex3f(5.0, -50.0, 440.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(440.0, 960, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -440.0);
    glVertex3f(5.0, -40.0, -440.0);
    glVertex3f(5.0, -40.0, 440.0);
    glVertex3f(5.0, -50.0, 440.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(440.0, 960, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -440.0);
    glVertex3f(-5.0, -40.0, -440.0);
    glVertex3f(-5.0, -40.0, 440.0);
    glVertex3f(-5.0, -50.0, 440.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(440.0, 960, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -440.0);
    glVertex3f(-5.0, -40.0, -440.0);
    glVertex3f(5.0, -40.0, -440.0);
    glVertex3f(5.0, -50.0, -440.0);
    glEnd();
    glPopMatrix();



    // pagar tidur kanan bawah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(440.0, 940, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 440.0);
    glVertex3f(-5.0, -40.0, 440.0);
    glVertex3f(5.0, -40.0, 440.0);
    glVertex3f(5.0, -50.0, 440.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(440.0, 940, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -440.0);
    glVertex3f(5.0, -40.0, -440.0);
    glVertex3f(5.0, -40.0, 440.0);
    glVertex3f(5.0, -50.0, 440.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(440.0, 940, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -440.0);
    glVertex3f(-5.0, -40.0, -440.0);
    glVertex3f(-5.0, -40.0, 440.0);
    glVertex3f(-5.0, -50.0, 440.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(440.0, 940, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -440.0);
    glVertex3f(-5.0, -40.0, -440.0);
    glVertex3f(5.0, -40.0, -440.0);
    glVertex3f(5.0, -50.0, -440.0);
    glEnd();
    glPopMatrix();



    // pagar tidur kiri atas
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-440.0, 1000, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 440.0);
    glVertex3f(-5.0, -40.0, 440.0);
    glVertex3f(5.0, -40.0, 440.0);
    glVertex3f(5.0, -50.0, 440.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-440.0, 1000, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -440.0);
    glVertex3f(5.0, -40.0, -440.0);
    glVertex3f(5.0, -40.0, 440.0);
    glVertex3f(5.0, -50.0, 440.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-440.0, 1000, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -440.0);
    glVertex3f(-5.0, -40.0, -440.0);
    glVertex3f(-5.0, -40.0, 440.0);
    glVertex3f(-5.0, -50.0, 440.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-440.0, 1000, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -440.0);
    glVertex3f(-5.0, -40.0, -440.0);
    glVertex3f(5.0, -40.0, -440.0);
    glVertex3f(5.0, -50.0, -440.0);
    glEnd();
    glPopMatrix();

    // pagar tidur kiri tengah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-440.0, 980, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 440.0);
    glVertex3f(-5.0, -40.0, 440.0);
    glVertex3f(5.0, -40.0, 440.0);
    glVertex3f(5.0, -50.0, 440.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-440.0, 980, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -440.0);
    glVertex3f(5.0, -40.0, -440.0);
    glVertex3f(5.0, -40.0, 440.0);
    glVertex3f(5.0, -50.0, 440.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-440.0, 980, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -440.0);
    glVertex3f(-5.0, -40.0, -440.0);
    glVertex3f(-5.0, -40.0, 440.0);
    glVertex3f(-5.0, -50.0, 440.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-440.0, 980, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -440.0);
    glVertex3f(-5.0, -40.0, -440.0);
    glVertex3f(5.0, -40.0, -440.0);
    glVertex3f(5.0, -50.0, -440.0);
    glEnd();
    glPopMatrix();


    // pagar tidur kiri tengah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-440.0, 960, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 440.0);
    glVertex3f(-5.0, -40.0, 440.0);
    glVertex3f(5.0, -40.0, 440.0);
    glVertex3f(5.0, -50.0, 440.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-440.0, 960, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -440.0);
    glVertex3f(5.0, -40.0, -440.0);
    glVertex3f(5.0, -40.0, 440.0);
    glVertex3f(5.0, -50.0, 440.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-440.0, 960, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -440.0);
    glVertex3f(-5.0, -40.0, -440.0);
    glVertex3f(-5.0, -40.0, 440.0);
    glVertex3f(-5.0, -50.0, 440.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-440.0, 960, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -440.0);
    glVertex3f(-5.0, -40.0, -440.0);
    glVertex3f(5.0, -40.0, -440.0);
    glVertex3f(5.0, -50.0, -440.0);
    glEnd();
    glPopMatrix();



    // pagar tidur kiri bawah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-440.0, 940, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 440.0);
    glVertex3f(-5.0, -40.0, 440.0);
    glVertex3f(5.0, -40.0, 440.0);
    glVertex3f(5.0, -50.0, 440.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-440.0, 940, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -440.0);
    glVertex3f(5.0, -40.0, -440.0);
    glVertex3f(5.0, -40.0, 440.0);
    glVertex3f(5.0, -50.0, 440.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-440.0, 940, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -440.0);
    glVertex3f(-5.0, -40.0, -440.0);
    glVertex3f(-5.0, -40.0, 440.0);
    glVertex3f(-5.0, -50.0, 440.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-440.0, 940, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -440.0);
    glVertex3f(-5.0, -40.0, -440.0);
    glVertex3f(5.0, -40.0, -440.0);
    glVertex3f(5.0, -50.0, -440.0);
    glEnd();
    glPopMatrix();




    // pagar tidur belakang atas
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1000, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-440.0, -50.0, 5.0);
    glVertex3f(-440.0, -40.0, 5.0);
    glVertex3f(440.0, -40.0, 5.0);
    glVertex3f(440.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1000, -440);
    glBegin(GL_POLYGON);
    glVertex3f(440.0, -50.0, -5.0);
    glVertex3f(440.0, -40.0, -5.0);
    glVertex3f(440.0, -40.0, 5.0);
    glVertex3f(440.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1000, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-440.0, -50.0, -5.0);
    glVertex3f(-440.0, -40.0, -5.0);
    glVertex3f(-440.0, -40.0, 5.0);
    glVertex3f(-440.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1000, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-440.0, -50.0, -5.0);
    glVertex3f(-440.0, -40.0, -5.0);
    glVertex3f(440.0, -40.0, -5.0);
    glVertex3f(440.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();



    //pagar tidur belakang tengah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 980, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-440.0, -50.0, 5.0);
    glVertex3f(-440.0, -40.0, 5.0);
    glVertex3f(440.0, -40.0, 5.0);
    glVertex3f(440.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 980, -440);
    glBegin(GL_POLYGON);
    glVertex3f(440.0, -50.0, -5.0);
    glVertex3f(440.0, -40.0, -5.0);
    glVertex3f(440.0, -40.0, 5.0);
    glVertex3f(440.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 980, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-440.0, -50.0, -5.0);
    glVertex3f(-440.0, -40.0, -5.0);
    glVertex3f(-440.0, -40.0, 5.0);
    glVertex3f(-440.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 980, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-440.0, -50.0, -5.0);
    glVertex3f(-440.0, -40.0, -5.0);
    glVertex3f(440.0, -40.0, -5.0);
    glVertex3f(440.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar tidur belakang tengah2
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 960, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-440.0, -50.0, 5.0);
    glVertex3f(-440.0, -40.0, 5.0);
    glVertex3f(440.0, -40.0, 5.0);
    glVertex3f(440.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 960, -440);
    glBegin(GL_POLYGON);
    glVertex3f(440.0, -50.0, -5.0);
    glVertex3f(440.0, -40.0, -5.0);
    glVertex3f(440.0, -40.0, 5.0);
    glVertex3f(440.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 960, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-440.0, -50.0, -5.0);
    glVertex3f(-440.0, -40.0, -5.0);
    glVertex3f(-440.0, -40.0, 5.0);
    glVertex3f(-440.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 960, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-440.0, -50.0, -5.0);
    glVertex3f(-440.0, -40.0, -5.0);
    glVertex3f(440.0, -40.0, -5.0);
    glVertex3f(440.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar tidur belakang bawah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 940, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-440.0, -50.0, 5.0);
    glVertex3f(-440.0, -40.0, 5.0);
    glVertex3f(440.0, -40.0, 5.0);
    glVertex3f(440.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 940, -440);
    glBegin(GL_POLYGON);
    glVertex3f(440.0, -50.0, -5.0);
    glVertex3f(440.0, -40.0, -5.0);
    glVertex3f(440.0, -40.0, 5.0);
    glVertex3f(440.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 940, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-440.0, -50.0, -5.0);
    glVertex3f(-440.0, -40.0, -5.0);
    glVertex3f(-440.0, -40.0, 5.0);
    glVertex3f(-440.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 940, -440);
    glBegin(GL_POLYGON);
    glVertex3f(-440.0, -50.0, -5.0);
    glVertex3f(-440.0, -40.0, -5.0);
    glVertex3f(440.0, -40.0, -5.0);
    glVertex3f(440.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();
    
    //Pagar lantai 4
    // pagar l3 depan ( kiri depan)
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-390, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-390, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-390, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-390, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();



    // pagar l1 depan(kanan depan)
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(390, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(390, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(390, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(390, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 (kiri belakang)
    //pagar l1 depan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-390, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-390, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-390, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-390, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 (kanan belakang)
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(390, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(390, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(390, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(390, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();



    //pagar l1 samping kanan (titik tengah)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, 0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //
    //pagar l1 samping kanan (tengah kiri 1)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, 345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, 345);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, 345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, 345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar l1 samping kanan(tengah kiri 2)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar l1 samping kanan (tengah kiri2)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();



    //pagar l1 samping kanan (tengah kanan)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, -345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, -345);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, -345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, -345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar l1 samping kanan(tengah kanan 1)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, -172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glVertex3f(5.0, 40.0, 5.0);
    glTranslatef(390, 1400, -172.5);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, -172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, -172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar l1 samping kanan (tengah kanan2)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar l1 samping kiri (titik tengah)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, 0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, 0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 samping kiri (tengah kiri 1)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, 345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, 345);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, 345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, 345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar l1 samping kiri(tengah kiri 1)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, 172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar l1 samping kiri (tengah kiri2)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 samping kiri (tengah kanan)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, -345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, -345);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, -345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, -345);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar l1 samping kiri(tengah kanan 1)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, -172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, -172.5);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, -172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, -172.5);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 samping kanan (tengah kanan2)
    // pagar l1 depan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    // pagar l1 depan (titik tengah)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(0, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(0, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(0, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(0, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kiri)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan 1)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-172.5, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-172.5, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-172.5, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-172.5, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan 2)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(345, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(345, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(345, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(345, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan 1)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(172.5, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(172.5, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(172.5, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(172.5, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan 2)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 belakang (titik tengah)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(0, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(0, 1400, -390);
    glBegin(GL_POLYGON);
    glEnd();
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(0, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(0, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kiri)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-345, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan 1)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-172.5, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-172.5, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-172.5, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-172.5, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan 2)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(-390, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(345, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(345, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(345, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(345, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan 1)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(172.5, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(172.5, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(172.5, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(172.5, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    // pagar l1 depan (tengah kanan 2)
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, 5.0);
    glVertex3f(5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(-5.0, 40.0, 5.0);
    glVertex3f(-5.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.96, 0.06, 0.06);
    glTranslatef(390, 1400, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -5.0);
    glVertex3f(-5.0, 40.0, -5.0);
    glVertex3f(5.0, 40.0, -5.0);
    glVertex3f(5.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    // pagar tidur depan atas
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1470, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-390.0, -50.0, 5.0);
    glVertex3f(-390.0, -40.0, 5.0);
    glVertex3f(390.0, -40.0, 5.0);
    glVertex3f(390.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1470, 390);
    glBegin(GL_POLYGON);
    glVertex3f(390.0, -50.0, -5.0);
    glVertex3f(390.0, -40.0, -5.0);
    glVertex3f(390.0, -40.0, 5.0);
    glVertex3f(390.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1470, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-390.0, -50.0, -5.0);
    glVertex3f(-390.0, -40.0, -5.0);
    glVertex3f(-390.0, -40.0, 5.0);
    glVertex3f(-390.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1470, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-390.0, -50.0, -5.0);
    glVertex3f(-390.0, -40.0, -5.0);
    glVertex3f(390.0, -40.0, -5.0);
    glVertex3f(390.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();



    // pagar tidur depan tengah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1450, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-390.0, -50.0, 5.0);
    glVertex3f(-390.0, -40.0, 5.0);
    glVertex3f(390.0, -40.0, 5.0);
    glVertex3f(390.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1450, 390);
    glBegin(GL_POLYGON);
    glVertex3f(390.0, -50.0, -5.0);
    glVertex3f(390.0, -40.0, -5.0);
    glVertex3f(390.0, -40.0, 5.0);
    glVertex3f(390.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1450, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-390.0, -50.0, -5.0);
    glVertex3f(-390.0, -40.0, -5.0);
    glVertex3f(-390.0, -40.0, 5.0);
    glVertex3f(-390.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1450, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-390.0, -50.0, -5.0);
    glVertex3f(-390.0, -40.0, -5.0);
    glVertex3f(390.0, -40.0, -5.0);
    glVertex3f(390.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    // pagar tidur depan tengah2
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1430, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-390.0, -50.0, 5.0);
    glVertex3f(-390.0, -40.0, 5.0);
    glVertex3f(390.0, -40.0, 5.0);
    glVertex3f(390.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan 
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1430, 390);
    glBegin(GL_POLYGON);
    glVertex3f(390.0, -50.0, -5.0);
    glVertex3f(390.0, -40.0, -5.0);
    glVertex3f(390.0, -40.0, 5.0);
    glVertex3f(390.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1430, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-390.0, -50.0, -5.0);
    glVertex3f(-390.0, -40.0, -5.0);
    glVertex3f(-390.0, -40.0, 5.0);
    glVertex3f(-390.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1430, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-390.0, -50.0, -5.0);
    glVertex3f(-390.0, -40.0, -5.0);
    glVertex3f(390.0, -40.0, -5.0);
    glVertex3f(390.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    // pagar tidur bawah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1410, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-390.0, -50.0, 5.0);
    glVertex3f(-390.0, -40.0, 5.0);
    glVertex3f(390.0, -40.0, 5.0);
    glVertex3f(390.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1410, 390);
    glBegin(GL_POLYGON);
    glVertex3f(390.0, -50.0, -5.0);
    glVertex3f(390.0, -40.0, -5.0);
    glVertex3f(390.0, -40.0, 5.0);
    glVertex3f(390.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1410, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-390.0, -50.0, -5.0);
    glVertex3f(-390.0, -40.0, -5.0);
    glVertex3f(-390.0, -40.0, 5.0);
    glVertex3f(-390.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1410, 390);
    glBegin(GL_POLYGON);
    glVertex3f(-390.0, -50.0, -5.0);
    glVertex3f(-390.0, -40.0, -5.0);
    glVertex3f(390.0, -40.0, -5.0);
    glVertex3f(390.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();



    // pagar tidur kanan atas
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(390.0, 1470, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 390.0);
    glVertex3f(-5.0, -40.0, 390.0);
    glVertex3f(5.0, -40.0, 390.0);
    glVertex3f(5.0, -50.0, 390.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(390.0, 1470, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -390.0);
    glVertex3f(5.0, -40.0, -390.0);
    glVertex3f(5.0, -40.0, 390.0);
    glVertex3f(5.0, -50.0, 390.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(390.0, 1470, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -390.0);
    glVertex3f(-5.0, -40.0, -390.0);
    glVertex3f(-5.0, -40.0, 390.0);
    glVertex3f(-5.0, -50.0, 390.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(390.0, 1470, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -390.0);
    glVertex3f(-5.0, -40.0, -390.0);
    glVertex3f(5.0, -40.0, -390.0);
    glVertex3f(5.0, -50.0, -390.0);
    glEnd();
    glPopMatrix();


    // pagar tidur kanan tengah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(390.0, 1450, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 390.0);
    glVertex3f(-5.0, -40.0, 390.0);
    glVertex3f(5.0, -40.0, 390.0);
    glVertex3f(5.0, -50.0, 390.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(390.0, 1450, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -390.0);
    glVertex3f(5.0, -40.0, -390.0);
    glVertex3f(5.0, -40.0, 390.0);
    glVertex3f(5.0, -50.0, 390.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(390.0, 1450, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -390.0);
    glVertex3f(-5.0, -40.0, -390.0);
    glVertex3f(-5.0, -40.0, 390.0);
    glVertex3f(-5.0, -50.0, 390.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(390.0, 1450, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -390.0);
    glVertex3f(-5.0, -40.0, -390.0);
    glVertex3f(5.0, -40.0, -390.0);
    glVertex3f(5.0, -50.0, -390.0);
    glEnd();
    glPopMatrix();



    // pagar tidur kanan tengah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(390.0, 1430, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 390.0);
    glVertex3f(-5.0, -40.0, 390.0);
    glVertex3f(5.0, -40.0, 390.0);
    glVertex3f(5.0, -50.0, 390.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(390.0, 1430, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -390.0);
    glVertex3f(5.0, -40.0, -390.0);
    glVertex3f(5.0, -40.0, 390.0);
    glVertex3f(5.0, -50.0, 390.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(390.0, 1430, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -390.0);
    glVertex3f(-5.0, -40.0, -390.0);
    glVertex3f(-5.0, -40.0, 390.0);
    glVertex3f(-5.0, -50.0, 390.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(390.0, 1430, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -390.0);
    glVertex3f(-5.0, -40.0, -390.0);
    glVertex3f(5.0, -40.0, -390.0);
    glVertex3f(5.0, -50.0, -390.0);
    glEnd();
    glPopMatrix();



    // pagar tidur kanan bawah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(390.0, 1410, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 390.0);
    glVertex3f(-5.0, -40.0, 390.0);
    glVertex3f(5.0, -40.0, 390.0);
    glVertex3f(5.0, -50.0, 390.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(390.0, 1410, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -390.0);
    glVertex3f(5.0, -40.0, -390.0);
    glVertex3f(5.0, -40.0, 390.0);
    glVertex3f(5.0, -50.0, 390.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(390.0, 1410, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -390.0);
    glVertex3f(-5.0, -40.0, -390.0);
    glVertex3f(-5.0, -40.0, 390.0);
    glVertex3f(-5.0, -50.0, 390.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(390.0, 1410, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -390.0);
    glVertex3f(-5.0, -40.0, -390.0);
    glVertex3f(5.0, -40.0, -390.0);
    glVertex3f(5.0, -50.0, -390.0);
    glEnd();
    glPopMatrix();



    // pagar tidur kiri atas
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-390.0, 1470, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 390.0);
    glVertex3f(-5.0, -40.0, 390.0);
    glVertex3f(5.0, -40.0, 390.0);
    glVertex3f(5.0, -50.0, 390.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-390.0, 1470, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -390.0);
    glVertex3f(5.0, -40.0, -390.0);
    glVertex3f(5.0, -40.0, 390.0);
    glVertex3f(5.0, -50.0, 390.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-390.0, 1470, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -390.0);
    glVertex3f(-5.0, -40.0, -390.0);
    glVertex3f(-5.0, -40.0, 390.0);
    glVertex3f(-5.0, -50.0, 390.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-390.0, 1470, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -390.0);
    glVertex3f(-5.0, -40.0, -390.0);
    glVertex3f(5.0, -40.0, -390.0);
    glVertex3f(5.0, -50.0, -390.0);
    glEnd();
    glPopMatrix();


    // pagar tidur kiri tengah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-390.0, 1450, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 390.0);
    glVertex3f(-5.0, -40.0, 390.0);
    glVertex3f(5.0, -40.0, 390.0);
    glVertex3f(5.0, -50.0, 390.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-390.0, 1450, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -390.0);
    glVertex3f(5.0, -40.0, -390.0);
    glVertex3f(5.0, -40.0, 390.0);
    glVertex3f(5.0, -50.0, 390.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-390.0, 1450, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -390.0);
    glVertex3f(-5.0, -40.0, -390.0);
    glVertex3f(-5.0, -40.0, 390.0);
    glVertex3f(-5.0, -50.0, 390.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-390.0, 1450, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -390.0);
    glVertex3f(-5.0, -40.0, -390.0);
    glVertex3f(5.0, -40.0, -390.0);
    glVertex3f(5.0, -50.0, -390.0);
    glEnd();
    glPopMatrix();


    // pagar tidur kiri tengah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-390.0, 1430, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 390.0);
    glVertex3f(-5.0, -40.0, 390.0);
    glVertex3f(5.0, -40.0, 390.0);
    glVertex3f(5.0, -50.0, 390.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-390.0, 1430, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -390.0);
    glVertex3f(5.0, -40.0, -390.0);
    glVertex3f(5.0, -40.0, 390.0);
    glVertex3f(5.0, -50.0, 390.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-390.0, 1430, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -390.0);
    glVertex3f(-5.0, -40.0, -390.0);
    glVertex3f(-5.0, -40.0, 390.0);
    glVertex3f(-5.0, -50.0, 390.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-390.0, 1430, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -390.0);
    glVertex3f(-5.0, -40.0, -390.0);
    glVertex3f(5.0, -40.0, -390.0);
    glVertex3f(5.0, -50.0, -390.0);
    glEnd();
    glPopMatrix();



    // pagar tidur kiri bawah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-390.0, 1410, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, 390.0);
    glVertex3f(-5.0, -40.0, 390.0);
    glVertex3f(5.0, -40.0, 390.0);
    glVertex3f(5.0, -50.0, 390.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-390.0, 1410, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(5.0, -50.0, -390.0);
    glVertex3f(5.0, -40.0, -390.0);
    glVertex3f(5.0, -40.0, 390.0);
    glVertex3f(5.0, -50.0, 390.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-390.0, 1410, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -390.0);
    glVertex3f(-5.0, -40.0, -390.0);
    glVertex3f(-5.0, -40.0, 390.0);
    glVertex3f(-5.0, -50.0, 390.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(-390.0, 1410, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-5.0, -50.0, -390.0);
    glVertex3f(-5.0, -40.0, -390.0);
    glVertex3f(5.0, -40.0, -390.0);
    glVertex3f(5.0, -50.0, -390.0);
    glEnd();
    glPopMatrix();


    // pagar tidur belakang atas
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1470, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-390.0, -50.0, 5.0);
    glVertex3f(-390.0, -40.0, 5.0);
    glVertex3f(390.0, -40.0, 5.0);
    glVertex3f(390.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1470, -390);
    glBegin(GL_POLYGON);
    glVertex3f(390.0, -50.0, -5.0);
    glVertex3f(390.0, -40.0, -5.0);
    glVertex3f(390.0, -40.0, 5.0);
    glVertex3f(390.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1470, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-390.0, -50.0, -5.0);
    glVertex3f(-390.0, -40.0, -5.0);
    glVertex3f(-390.0, -40.0, 5.0);
    glVertex3f(-390.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1470, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-390.0, -50.0, -5.0);
    glVertex3f(-390.0, -40.0, -5.0);
    glVertex3f(390.0, -40.0, -5.0);
    glVertex3f(390.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();



    //pagar tidur belakang tengah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1450, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-390.0, -50.0, 5.0);
    glVertex3f(-390.0, -40.0, 5.0);
    glVertex3f(390.0, -40.0, 5.0);
    glVertex3f(390.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1450, -390);
    glBegin(GL_POLYGON);
    glVertex3f(390.0, -50.0, -5.0);
    glVertex3f(390.0, -40.0, -5.0);
    glVertex3f(390.0, -40.0, 5.0);
    glVertex3f(390.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1450, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-390.0, -50.0, -5.0);
    glVertex3f(-390.0, -40.0, -5.0);
    glVertex3f(-390.0, -40.0, 5.0);
    glVertex3f(-390.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1450, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-390.0, -50.0, -5.0);
    glVertex3f(-390.0, -40.0, -5.0);
    glVertex3f(390.0, -40.0, -5.0);
    glVertex3f(390.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar tidur belakang tengah2
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1430, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-390.0, -50.0, 5.0);
    glVertex3f(-390.0, -40.0, 5.0);
    glVertex3f(390.0, -40.0, 5.0);
    glVertex3f(390.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1430, -390);
    glBegin(GL_POLYGON);
    glVertex3f(390.0, -50.0, -5.0);
    glVertex3f(390.0, -40.0, -5.0);
    glVertex3f(390.0, -40.0, 5.0);
    glVertex3f(390.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1430, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-390.0, -50.0, -5.0);
    glVertex3f(-390.0, -40.0, -5.0);
    glVertex3f(-390.0, -40.0, 5.0);
    glVertex3f(-390.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1430, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-390.0, -50.0, -5.0);
    glVertex3f(-390.0, -40.0, -5.0);
    glVertex3f(390.0, -40.0, -5.0);
    glVertex3f(390.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();


    //pagar tidur belakang bawah
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1410, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-390.0, -50.0, 5.0);
    glVertex3f(-390.0, -40.0, 5.0);
    glVertex3f(390.0, -40.0, 5.0);
    glVertex3f(390.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kanan
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1410, -390);
    glBegin(GL_POLYGON);
    glVertex3f(390.0, -50.0, -5.0);
    glVertex3f(390.0, -40.0, -5.0);
    glVertex3f(390.0, -40.0, 5.0);
    glVertex3f(390.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 kiri
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1410, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-390.0, -50.0, -5.0);
    glVertex3f(-390.0, -40.0, -5.0);
    glVertex3f(-390.0, -40.0, 5.0);
    glVertex3f(-390.0, -50.0, 5.0);
    glEnd();
    glPopMatrix();

    //pagar l1 belakang
    glPushMatrix();
    glColor3f(0.91, 0.45, 0.21);
    glTranslatef(0.0, 1410, -390);
    glBegin(GL_POLYGON);
    glVertex3f(-390.0, -50.0, -5.0);
    glVertex3f(-390.0, -40.0, -5.0);
    glVertex3f(390.0, -40.0, -5.0);
    glVertex3f(390.0, -50.0, -5.0);
    glEnd();
    glPopMatrix();

    //alas lantai (4)1
    glPushMatrix();
    glColor3f(0.79, 0.73, 0.78);
    glTranslatef(0, 1300, 0);
    glBegin(GL_POLYGON);
    glVertex3f(400.0, 0.0, 400.0);
    glVertex3f(400.0, 0.0, -400.0);
    glVertex3f(-400.0, 0.0, -400.0);
    glVertex3f(-400.0, 0.0, 400.0);
    glEnd();
    glPopMatrix();

    //alas lantai (4)2
    glPushMatrix();
    glColor3f(0.79, 0.73, 0.78);
    glTranslatef(0, 1350, 0);
    glBegin(GL_POLYGON);
    glVertex3f(400.0, 0.0, 400.0);
    glVertex3f(400.0, 0.0, -400.0);
    glVertex3f(-400.0, 0.0, -400.0);
    glVertex3f(-400.0, 0.0, 400.0);
    glEnd();
    glPopMatrix();

    ground();
    cout << "X_GESER = " << x_geser << "Y_GESER = " << y_geser << "Z_GESER = " << z_geser << endl;
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    camera();
    draw();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50, 16.0 / 9.0, 2, 10000);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int) {
    glutPostRedisplay();
    glutWarpPointer(width / 2, height / 2);
    glutTimerFunc(1000 / FPS, timer, 0);
}

void passive_motion(int x, int y) {
    int dev_x, dev_y;
    dev_x = (width / 2) - x;
    dev_y = (height / 2) - y;
    yaw += (float)dev_x / 20.0;
    pitch += (float)dev_y / 20.0;
}

void camera() {
    if (motion.Forward) {
        camX += cos((yaw + 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90) * TO_RADIANS) * 2;
    }
    if (motion.Backward) {
        camX += cos((yaw + 90 + 180) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 + 180) * TO_RADIANS) * 2;
    }
    if (motion.Left) {
        camX += cos((yaw + 90 + 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 + 90) * TO_RADIANS) * 2;
    }
    if (motion.Right) {
        camX += cos((yaw + 90 - 90) * TO_RADIANS) * 2;
        camZ -= sin((yaw + 90 - 90) * TO_RADIANS) * 2;
    }
    if (motion.Naik) {
        terbang -= 2.0;
    }
    if (motion.Turun) {
        terbang += 2.0;
    }

    if (pitch >= 70)
        pitch = 70;
    if (pitch <= -90)
        pitch = -90;


    glRotatef(-pitch, 1.0, 0.0, 0.0);
    glRotatef(-yaw, 0.0, 1.0, 0.0);

    glTranslatef(-camX, -terbang, -350 - camZ);
    if (terbang < 25)
        terbang = 24;
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'W':
    case 'w':
        motion.Forward = true;
        break;
    case 'A':
    case 'a':
        motion.Left = true;
        break;
    case 'S':
    case 's':
        motion.Backward = true;
        break;
    case 'D':
    case 'd':
        motion.Right = true;
        break;
    case 'E':
    case 'e':
        motion.Naik = true;
        break;
    case 'Q':
    case 'q':
        motion.Turun = true;
        break;
    case '1':
        x_geser += 1.0;
        break;
    case '3':
        x_geser -= 1.0;
        break;
    case '=':
        y_geser += 1.0;
        break;
    case '-':
        y_geser -= 1.0;
        break;
    case 'i':
        z_geser -= 1.0;
        break;
    case 'k':
        z_geser += 1.0;
        break;
    case '`': // KELUAR DARI PROGRAM
        exit(1);
    }
}

void keyboard_up(unsigned char key, int x, int y) {
    switch (key) {
    case 'W':
    case 'w':
        motion.Forward = false;
        break;
    case 'A':
    case 'a':
        motion.Left = false;
        break;
    case 'S':
    case 's':
        motion.Backward = false;
        break;
    case 'D':
    case 'd':
        motion.Right = false;
        break;
    case 'E':
    case 'e':
        motion.Naik = false;
        break;
    case 'Q':
    case 'q':
        motion.Turun = false;
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(width, height);
    glutCreateWindow("TR GRAFKOM KELOMPOK 3");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutPassiveMotionFunc(passive_motion);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);

    glutMainLoop();
    return 0;
}