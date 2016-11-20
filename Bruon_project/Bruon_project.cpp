// Bruon_project.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <glut.h>
#include <vector>
#include<ctime>
#include <omp.h>
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
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	for (auto i : p)
	{
		if (i.m <= 2)
		{
			glPointSize(6);
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
#pragma parrallel for
 	for (auto i = p.begin(); i!=p.end();i++)
		for (auto j = p.begin(); j!=p.end();j++)
			if (i!=j)
			{
				float d = sqrt((i->x - j->x) * (i->x - j->x) + (i->y - j->y) * (i->y - j->y));
				if (d < i->m + j->m)
				{
					float f = 100 * (i->m + j->m - d);
					i->vx += f * (i->x - j->x) / d / i->m * DT;
					i->vy += f * (i->y - j->y) / d / i->m * DT;
					j->vx -= f * (i->x - j->x) / d / j->m * DT;
					j->vy -= f * (i->y - j->y) / d / j->m * DT;
				}
			}
	#pragma parallel for
	for (auto i = p.begin(); i != p.end(); ++i)
	{
		if ((i->x - i->m < 0) || (i->x + i->m >1366))
			i->vx = -i->vx;
		if ((i->y - i->m < 0) || (i->y + i->m >768))
			i->vy = -i->vy;
		i->x += i->vx * DT;
		i->y += i->vy * DT;
	}
	display();
	glutTimerFunc(1, timer, 0);
}

int main(int argc, char **argv)
{
	srand(0);
	for (int i = 0; i < 200; i++)
	{
		Particle particle = { rand() % 1366, rand() % 768, rand() % 100000 / 500.0 - 10 , rand() % 100000 / 500.0 - 10, 6};
		p.push_back(particle);
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1366, 768);
	glutCreateWindow("Brownian motion");
	glClearColor(0.1, 0.3, 0.3, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1366, 768, 0, -1, 1);
	glutDisplayFunc(display);
	timer();
	glutMainLoop();
	return 0;
}

