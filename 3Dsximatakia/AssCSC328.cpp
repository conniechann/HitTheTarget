
//Assignment CSC328A
//Makri Konstantina

#include "stdafx.h"
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <iostream>



GLfloat targetX1 = 0;
GLfloat targetX2 = 70;
GLfloat targetY1 = 500;
GLfloat targetY2 = 490;

GLfloat circleY = 20;
GLfloat circleX = 280;
GLfloat bullet = circleY;
GLfloat bulletX = circleX;

//GLfloat rectSpeed = 0.1;
//GLfloat shootCircle;
bool isSelected = false;
bool gotHit = false;
int hit = 1;
int edge = 0;

double green = 1;
double red = 0;
double blue = 0;

void Init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0, 600.0, 0.0, 600.0);
}

//initial circle
void drawCircle(GLfloat x, GLfloat y, GLfloat radius) {
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle     
	GLfloat twicePi = 2.0f * 3.14;
	glColor3f(red, green, blue);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}

	glEnd();
}

void foundTarget(GLfloat x, GLfloat y, GLfloat radius) {

	int i;
	int triangleAmount = 20;
	GLfloat twicePi = 2.0f * 3.14;
	glColor3f(1.5, 1, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}

	glEnd();
}

// moving circle
void drawBullet(GLfloat x, GLfloat y, GLfloat radius) {

	int i;
	int triangleAmount = 20;
	GLfloat twicePi = 2.0f * 3.14;
	glColor3f(red, green, blue);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y);
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}

	glEnd();
}

void Display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glBegin(GL_QUADS);
	glVertex2d(targetX1, targetY1);
	glVertex2d(targetX1, targetY2);
	glVertex2d(targetX2, targetY2);
	glVertex2d(targetX2, targetY1);
	glEnd();
	glFlush();
	drawBullet(bulletX, bullet, 20);
	glFlush();
	drawCircle(circleX, circleY, 20);

	if (gotHit == true)
	{
		foundTarget(circleX, 490, 30);
		hit = hit + 1;
		gotHit = false;

	}
	glFlush();
}

void IdleFunc() {

	Sleep(100);
	//moving target
	if (targetX1 < 600 && edge == 0) {
		targetX1 += 20;
		targetX2 += 20;
		if (targetX1 >= 560) {
			edge = 1;
		}

	}
	else {
		targetX1 -= 20;
		targetX2 -= 20;
		if (targetX1 <= 15) {
			edge = 0;
		}
	}

	//target hit
	if (isSelected == true) {

		bullet += 20;
		if (bullet >= 490 && bullet <= 500)
		{
			if (bulletX >= targetX1 && bulletX <= targetX2) {

				gotHit = true;
				foundTarget(circleX, circleY, 20);
				glFlush();
			}
		}
		if (bullet >= 600)
		{
			bullet = 20;
			isSelected = false;
		}
	}

	Display();
}

void KeyboardFunc(unsigned char key, int x, int y) {

	if (key == 's' || key == 'S') {


		isSelected = true;
		drawBullet(circleX, bullet, 20);
		glFlush();
		Display();
	}

}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(600, 600);
	glutCreateWindow("Hit the Target");
	Init();
	glutKeyboardFunc(KeyboardFunc);
	glutDisplayFunc(Display);
	glutIdleFunc(IdleFunc);
	glutMainLoop();

}
