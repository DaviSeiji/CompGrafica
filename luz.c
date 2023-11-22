//Davi Seiji Kawai Santos
//156373

#include <glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

GLfloat posLuz[] = { 0.0, 0.0, 1.0, 1.0 };
GLfloat rotAng = 0.0;
GLfloat luzx = 0.0, luzy = 0.0;

GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };

void esfera(float r, int a, int b) {
    glutSolidSphere(r, a, b);
}

float coordx(int x) {
    float a;

    a = (x - 200) / 200.0;

    return a;
}

float coordy(int y) {
    float b;

    b = (y - 200) * -1 / 200.0;

    return b;
}

void configuraLuz() {
    glLightfv(GL_LIGHT0, GL_POSITION, posLuz);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void displayFunc() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.0, 1.0, 10.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); 

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);  
    glEnable(GL_SPECULAR);       

    glPushMatrix();
    glRotatef(rotAng, 0.0, 0.0, 1.0);

    GLfloat matAmbient[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat matDiffuse[] = {0.8, 0.8, 0.8, 1.0};
    GLfloat matSpecular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat matShininess[] = {100.0};

    glMaterialfv(GL_FRONT, GL_AMBIENT, matAmbient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matDiffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpecular);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess);

    glColor3f(1.0, 0.0, 0.0);
    glPushMatrix();
    glTranslatef(1.5, 0.0, 0.0);
    esfera(0.5, 20, 20);
    glPopMatrix();

    glColor3f(1.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(0.0, 1.5, 0.0);
    esfera(0.5, 20, 20);
    glPopMatrix();

    glColor3f(0.0, 1.0, 0.0);
    glPushMatrix();
    glTranslatef(-1.5, 0.0, 0.0);
    esfera(0.5, 20, 20);
    glPopMatrix();

    glColor3f(0.0, 0.0, 1.0);
    glPushMatrix();
    glTranslatef(0.0, -1.5, 0.0);
    esfera(0.5, 20, 20);
    glPopMatrix();

    glPopMatrix();

    configuraLuz();

    glutSwapBuffers();
}

void update(int value) {
    rotAng += 1.0;
    if (rotAng > 360) {
        rotAng -= 360;
    }

    configuraLuz();

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void MouseInt(int botao, int estado, int x, int y) {
    if (estado == GLUT_DOWN) {
        luzx = coordx(x);
        luzy = coordy(y);
        posLuz[0] = luzx;
        posLuz[1] = luzy;
    }
}

int main(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Esferas Girando com Lanterna");
    glEnable(GL_DEPTH_TEST);
    glutMouseFunc(MouseInt);
    glutDisplayFunc(displayFunc);
    glutTimerFunc(25, update, 0);
    glutMainLoop();

    return 0;
}
