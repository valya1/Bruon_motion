// Bruon_project.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <glut.h>
#include <vector>
#include<cmath>
#define M_PI   3.14159265358979323846
#define DT 0.1
using namespace std;

struct Particle
{
	float x;
	float y;
	float vx;
	float vy;
	float m;
};

vector<Particle> p;
float sqr(float x)
{
	return x*x;
}
void changeSize(int w, int h)
{
	if (h == 0)
		h = 1;
	float ratio = 1.0* w / h;

	glMatrixMode(GL_PROJECTION);
	glViewport(0, 0, w, h);

	gluPerspective(45, ratio, 1, 1000);

	glMatrixMode(GL_MODELVIEW);
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto i : p)
	{
		if (i.m <= 2)
		{
			glPointSize(4);
			glBegin(GL_POINTS);
			glVertex2f(i.x, i.y);
			glEnd();
		}
		else
		{
			glBegin(GL_LINES);
			for (int a = 0; a < 72; a++)
			{
				float x = i.m*cos(a*M_PI / 36);
				float y = i.m*sin(a*M_PI / 36);
				glVertex2f(i.x+x, i.y+y);
				x = i.m*cos((a + 1)*M_PI / 36);
				y = i.m*sin((a + 1)*M_PI / 36);
				glVertex2f(i.x+x, i.y+y);
			}
			glEnd();
			}

		}
		glutSwapBuffers();
}
void timer(int = 0)
{
	for (auto i = p.begin(); i!=p.end();i++)
		for (auto j = p.begin(); j!=p.end();j++)
			if (i!=j)
			{
				float d = sqrt((i->x - j->x) * (i->x - j->x) + (i->y - j->y) * (i->y - j->y));
				if (d < i->m + j->m)
				{
					float f = 50 * (i->m + j->m - d);
					i->vx += f * (i->x - j->x) / d / i->m * DT;
					i->vy += f * (i->y - j->y) / d / i->m * DT;
					j->vx -= f * (i->x - j->x) / d / j->m * DT;
					j->vy -= f * (i->y - j->y) / d / j->m * DT;
				}
			}
	for (auto i = p.begin(); i != p.end(); ++i)
	{
		i->x += i->vx * DT;
		i->y += i->vy * DT;
		if (i->x < 0)
			i->x += 480;
		if (i->y < 0)
			i->y += 480;
		if (i->x > 480)
			i->x -= 480;
		if (i->y > 480)
			i->y -= 480;
	}
	display();
	glutTimerFunc(10, timer, 0);
}

int main(int argc, char **argv)
{
	for (int i = 0; i < 100; i++)
	{
		Particle particle = { rand() % 480, rand() % 480, rand() % 10000 / 500.0 - 10, rand() % 10000 / 500.0 - 10, rand()%5 +1};
		p.push_back(particle);
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(480, 480);
	glutInitWindowPosition(20, 1050 - 480 - 20);
	glutCreateWindow("Brownian motion");
	glClearColor(0, 0, 0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 480, 480, 0, -1, 1);
	glutDisplayFunc(display);
	timer();
	glutMainLoop();
	return 0;
}



