#include <windows.h>
#include <GL/glut.h>
#include <cmath>

// Animation & Camera Variables
float carPos1 = -25.0f;
float carPos2 = 25.0f;
float wheelRotate = 0.0f;
float cameraX = 0.0f;
float cameraY = 18.0f;
float cameraZ = 45.0f;

// Traffic light state
int trafficState = 0;       // 0 = Green, 1 = Yellow, 2 = Red
int trafficTimer = 0;

// --- Lighting & Depth ---
void initLighting() {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat lightPos[] = { 10.0f, 30.0f, 20.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
}

// --- Sun Drawing ---
void drawSun() {
    glDisable(GL_LIGHTING);
    glPushMatrix();
    glTranslatef(25.0f, 28.0f, -30.0f);
    glColor3f(1.0f, 0.85f, 0.0f);
    glutSolidSphere(3.5f, 40, 40);
    glPopMatrix();
    glEnable(GL_LIGHTING);
}

// --- Tree Model ---
void drawTree(float x, float z) {
    glPushMatrix();
    glTranslatef(x, 0, z);

    glColor3f(0.38f, 0.19f, 0.05f);
    glPushMatrix();
    glScalef(0.5f, 2.5f, 0.5f);
    glTranslatef(0, 0.5f, 0);
    glutSolidCube(1.0f);
    glPopMatrix();

    glColor3f(0.0f, 0.45f, 0.1f);
    glPushMatrix();
    glTranslatef(0, 1.8, 0);
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(2.0, 3.0, 16, 16);
    glPopMatrix();

    glColor3f(0.0f, 0.6f, 0.15f);
    glPushMatrix();
    glTranslatef(0, 3.2, 0);
    glRotatef(-90, 1, 0, 0);
    glutSolidCone(1.5, 2.2, 16, 16);
    glPopMatrix();

    glPopMatrix();
}

// --- House Model ---
void drawHouse(float x, float z) {
    glPushMatrix();
    glTranslatef(x, 0, z);

    glColor3f(0.95f, 0.85f, 0.7f);
    glPushMatrix();
    glTranslatef(0, 1.5, 0);
    glScalef(5, 3, 4);
    glutSolidCube(1);
    glPopMatrix();

    glColor3f(0.65f, 0.1f, 0.1f);
    glPushMatrix();
    glTranslatef(0, 3, 0);
    glRotatef(-90, 1, 0, 0);
    glRotatef(45, 0, 0, 1);
    glutSolidCone(4.5, 2.8, 4, 1);
    glPopMatrix();

    glColor3f(0.25f, 0.1f, 0.0f);
    glPushMatrix();
    glTranslatef(0, 0.8, 2.01);
    glScalef(1, 1.6, 0.1);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

// --- Car & Wheels ---
void drawWheel() {
    glColor3f(0.15f, 0.15f, 0.15f);
    glPushMatrix();
    glRotatef(wheelRotate, 0, 0, 1);
    glutSolidTorus(0.18, 0.45, 12, 24);
    glPopMatrix();
}

void drawCar(float x, float z, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, 0.9f, z);

    glColor3f(r, g, b);
    glPushMatrix();
    glScalef(4.5, 1.2, 2.2);
    glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.2, 1.0, 0);
    glScalef(2.5, 1.0, 1.8);
    glutSolidCube(1);
    glPopMatrix();

    float wx[] = {-1.5, 1.5, -1.5, 1.5};
    float wz[] = {-1.2, -1.2, 1.2, 1.2};

    for(int i = 0; i < 4; i++) {
        glPushMatrix();
        glTranslatef(wx[i], -0.4, wz[i]);
        drawWheel();
        glPopMatrix();
    }

    glPopMatrix();
}

// --- Traffic Light ---
void drawTrafficLight(float x, float z) {
    glPushMatrix();
    glTranslatef(x, 0, z);

    // Pole
    glColor3f(0.2f, 0.2f, 0.2f);
    glPushMatrix();
    glTranslatef(0, 4.0f, 0);
    glScalef(0.3f, 8.0f, 0.3f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Light box
    glColor3f(0.1f, 0.1f, 0.1f);
    glPushMatrix();
    glTranslatef(0.0f, 7.0f, 0.0f);
    glScalef(1.0f, 2.4f, 0.8f);
    glutSolidCube(1.0f);
    glPopMatrix();

    // Red light
    if (trafficState == 2) glColor3f(1.0f, 0.0f, 0.0f);
    else glColor3f(0.35f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, 7.7f, 0.45f);
    glutSolidSphere(0.22f, 20, 20);
    glPopMatrix();

    // Yellow light
    if (trafficState == 1) glColor3f(1.0f, 1.0f, 0.0f);
    else glColor3f(0.35f, 0.35f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, 7.0f, 0.45f);
    glutSolidSphere(0.22f, 20, 20);
    glPopMatrix();

    // Green light
    if (trafficState == 0) glColor3f(0.0f, 1.0f, 0.0f);
    else glColor3f(0.0f, 0.35f, 0.0f);
    glPushMatrix();
    glTranslatef(0.0f, 6.3f, 0.45f);
    glutSolidSphere(0.22f, 20, 20);
    glPopMatrix();

    glPopMatrix();
}

// --- Main Display ---
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(cameraX, cameraY, cameraZ, 0, 0, 0, 0, 1, 0);

    // Ground
    glColor3f(0.25f, 0.7f, 0.25f);
    glBegin(GL_QUADS);
        glVertex3f(-60,0,-60);
        glVertex3f(60,0,-60);
        glVertex3f(60,0,60);
        glVertex3f(-60,0,60);
    glEnd();

    // Road
    glColor3f(0.18, 0.18, 0.18);
    glBegin(GL_QUADS);
        glVertex3f(-60,0.01,-7);
        glVertex3f(60,0.01,-7);
        glVertex3f(60,0.01,7);
        glVertex3f(-60,0.01,7);
    glEnd();

    // Road markings
    glColor3f(1, 1, 0);
    for(float i = -55; i < 60; i += 10) {
        glBegin(GL_QUADS);
            glVertex3f(i,0.02,-0.25);
            glVertex3f(i+5,0.02,-0.25);
            glVertex3f(i+5,0.02,0.25);
            glVertex3f(i,0.02,0.25);
        glEnd();
    }

    // Stop line near traffic signal
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
        glVertex3f(-2, 0.03, -7);
        glVertex3f(-1, 0.03, -7);
        glVertex3f(-1, 0.03, 7);
        glVertex3f(-2, 0.03, 7);
    glEnd();

    // Sky
    drawSun();

    // Houses
    drawHouse(-18, -18);
    drawHouse(0, -18);
    drawHouse(18, -18);

    // Trees
    drawTree(-26, -18);
    drawTree(-10, -18);
    drawTree(10, -18);
    drawTree(26, -18);
    drawTree(-35, -10);
    drawTree(35, -10);

    // Traffic lights (2 sides of road)
    drawTrafficLight(-3.0f, -9.5f);
    drawTrafficLight(-3.0f, 9.5f);

    // Cars
    drawCar(carPos1, -3.5f, 0.9f, 0.1f, 0.1f);
    drawCar(carPos2,  3.5f, 0.1f, 0.2f, 0.9f);

    glutSwapBuffers();
}

void update(int v) {
    trafficTimer++;

    // Traffic cycle change
    if (trafficTimer < 300) trafficState = 0;       // Green
    else if (trafficTimer < 380) trafficState = 1;  // Yellow
    else if (trafficTimer < 650) trafficState = 2;  // Red
    else trafficTimer = 0;

    // Car 1: stop at red signal near x = -4
    if (!(trafficState == 2 && carPos1 > -8.0f && carPos1 < -1.5f)) {
        carPos1 += 0.28f;
    }
    if (carPos1 > 40) carPos1 = -40;

    // Car 2: opposite direction, simple movement
    carPos2 -= 0.22f;
    if (carPos2 < -40) carPos2 = 40;

    // Wheel rotate only if at least one car moves
    if (!(trafficState == 2 && carPos1 > -8.0f && carPos1 < -1.5f)) {
        wheelRotate -= 20.0f;
    } else {
        wheelRotate -= 10.0f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'w') cameraZ -= 1.5;
    if (key == 's') cameraZ += 1.5;
    if (key == 'a') cameraX -= 1.5;
    if (key == 'd') cameraX += 1.5;
    if (key == 27) exit(0);
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1200, 800);
    glutCreateWindow("3D Smart City with Traffic Light");

    initLighting();
    glClearColor(0.5, 0.85, 1.0, 1.0);

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, 1.5, 1, 300);
    glMatrixMode(GL_MODELVIEW);

    glutMainLoop();
    return 0;
}
