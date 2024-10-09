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


void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glutSwapBuffers(); 
}


void reshape(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0); 
	glMatrixMode(GL_MODELVIEW); 
}

int main(int argc, char** argv) {

	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(200, 30);

	if (glutCreateWindow("Assignment 1 - Astro Bot") == 0) {
		printf("Error: Window creation failed.\n");
		return 1;
	}

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);


	glutMainLoop();

	return 0;
}




