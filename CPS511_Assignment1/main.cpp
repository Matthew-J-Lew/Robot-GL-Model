#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <gl/glut.h>
#include <utility>
#include <vector>

GLint windowWidth = 1280;
GLint windowHeight = 720;
GLint viewportWidth = windowWidth;
GLint viewportHeight = windowHeight;

// Variables to control joint angles
float bodyAngle = 0.0;
float leftElbowAngle = 0.0, rightElbowAngle = 0.0;
float leftKneeAngle = 0.0, rightKneeAngle = 0.0;
float leftHipAngle = 0.0, rightHipAngle = 0.0;
char activeJoint = ' '; // Currently selected joint

void drawBody() {
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 0.0f);
    glScalef(0.7f, 1.0f, 0.4f);
    glColor3f(1.0f, 1.0f, 1.0f); // Body
    glutSolidCube(1.0f);
    glPopMatrix();
}

void drawHead() {
    glPushMatrix();
    glTranslatef(0.0f, 1.15f, 0.0f);
    glColor3f(0.1f, 0.1f, 0.1f); // Face
    glutSolidSphere(0.7f, 30, 30);
    glPopMatrix();
}

void drawArm(bool isLeft) {
    glPushMatrix();

    // Upper Arm
    if (isLeft) {
        glTranslatef(-0.50f, 0.2f, 0.0f);
    }
    else {
        glTranslatef(0.50f, 0.2f, 0.0f);
    }

    glRotatef(-45.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f); // Arm

    gluCylinder(gluNewQuadric(), 0.15f, 0.15f, 0.5f, 20, 20);
    glTranslatef(0.0f, 0.0f, 0.5f);

    // Apply elbow rotation with constraints
    if (isLeft) {
        leftElbowAngle = fmax(-90.0f, fmin(leftElbowAngle, 0.0f));
        glRotatef(leftElbowAngle, 1.0f, 0.0f, 0.0f);
    }
    else {
        rightElbowAngle = fmax(-90.0f, fmin(rightElbowAngle, 0.0f));
        glRotatef(rightElbowAngle, 1.0f, 0.0f, 0.0f);
    }

    // Lower arm
    gluCylinder(gluNewQuadric(), 0.1f, 0.1f, 0.5f, 20, 20);

    glPopMatrix();
}

void drawLeg(bool isLeft) {
    glPushMatrix();

    // Upper leg
    if (isLeft) {
        glTranslatef(-0.22f, -0.5f, 0.0f);
    }
    else {
        glTranslatef(0.22f, -0.5f, 0.0f);
    }

    // Apply hip rotation
    if (isLeft) {
        leftHipAngle = fmax(-90.0f, fmin(leftHipAngle, 0.0f));
        glRotatef(leftHipAngle, 1.0f, 0.0f, 0.0f);
    }
    else {
        rightHipAngle = fmax(-90.0f, fmin(rightHipAngle, 0.0f));
        glRotatef(rightHipAngle, 1.0f, 0.0f, 0.0f);
    }

    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    glColor3f(0.9f, 0.9f, 0.9f); // Leg

    gluCylinder(gluNewQuadric(), 0.2f, 0.2f, 0.7f, 20, 20);
    glTranslatef(0.0f, 0.0f, 0.7f);

    // Apply knee rotation with constraints
    if (isLeft) {
        leftKneeAngle = fmax(0.0f, fmin(leftKneeAngle, 90.0f));
        glRotatef(leftKneeAngle, 1.0f, 0.0f, 0.0f);
    }
    else {
        rightKneeAngle = fmax(0.0f, fmin(rightKneeAngle, 90.0f));
        glRotatef(rightKneeAngle, 1.0f, 0.0f, 0.0f);
    }

    // Lower leg
    gluCylinder(gluNewQuadric(), 0.15f, 0.15f, 0.5f, 20, 20);

    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Position the bot
    glTranslatef(0.0f, 0.0f, -5.0f);
    glRotatef(bodyAngle, 0.0f, 1.0f, 0.0f);

    // Draw the bot
    glPushMatrix();

    // Draw body parts
    drawBody();   // Body
    drawHead();   // Head above the body
    drawArm(true);  // Left arm
    drawArm(false); // Right arm
    drawLeg(true);  // Left leg
    drawLeg(false); // Right leg

    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)width / (float)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y) {
    // Select joint to control
    if (key == 'q') {
        activeJoint = 'q'; // Left arm
    }
    else if (key == 'e') {
        activeJoint = 'e'; // Right arm
    }
    else if (key == 'a') {
        activeJoint = 'a'; // Left leg
    }
    else if (key == 'd') {
        activeJoint = 'd'; // Right leg
    }
    else if (key == 'z') {
        activeJoint = 'z'; // Left knee
    }
    else if (key == 'c') {
        activeJoint = 'c'; // Right knee
    }

    else if (key == 'b') {
        activeJoint = 'b'; // Rotate body
    }

    glutPostRedisplay();
}

void specialKeyboard(int key, int x, int y) {
    // Control movement based on the active joint
    if (key == GLUT_KEY_UP) {
        if (activeJoint == 'q') {
            leftElbowAngle -= 5.0;
        }
        else if (activeJoint == 'e') {
            rightElbowAngle -= 5.0;
        }
        else if (activeJoint == 'a') {
            leftHipAngle -= 5.0;
        }
        else if (activeJoint == 'd') {
            rightHipAngle -= 5.0;
        }
        else if (activeJoint == 'z') {
            leftKneeAngle -= 5.0;
        }
        else if (activeJoint == 'c') {
            rightKneeAngle -= 5.0;
        }
    }
    else if (key == GLUT_KEY_DOWN) {
        if (activeJoint == 'q') {
            leftElbowAngle += 5.0;
        }
        else if (activeJoint == 'e') {
            rightElbowAngle += 5.0;
        }
        else if (activeJoint == 'a') {
            leftHipAngle += 5.0;
        }
        else if (activeJoint == 'd') {
            rightHipAngle += 5.0;
        }
        else if (activeJoint == 'z') {
            leftKneeAngle += 5.0;
        }
        else if (activeJoint == 'c') {
            rightKneeAngle += 5.0;
        }
    }
    else if (key == GLUT_KEY_LEFT) {
        if (activeJoint == 'b') {
            bodyAngle -= 5.0;
        }
    }
    else if (key == GLUT_KEY_RIGHT) {
        if (activeJoint == 'b') {
            bodyAngle += 5.0;
        }
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(windowWidth, windowHeight);

    if (glutCreateWindow("Assignment 1 - Astro Bot") == 0) {
        printf("Error: Window creation failed.\n");
        return 1;
    }

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard); // Regular key handler
    glutSpecialFunc(specialKeyboard); // Special key handler

    // Enable depth testing
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}