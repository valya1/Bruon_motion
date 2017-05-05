

#include "stdafx.h"
#include <glut.h>
#include <vector>
#include<ctime>
#include<cmath>
#include <omp.h>
#include<iostream>
#define M_PI   3.14159265358979323846
#define DT 0.1
using namespace std;

struct Particle
{
	int num;
	float r;
	float m;
	float x;
	float y;
	float vx;
	float vy;
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
			glBegin(GL_POLYGON);
			if (i.num == 1)
				glColor3f(1,0,0);
			else
				glColor3f(0.1, 0.1, 1);
			for (int a = 0; a < 72; a++)
			{
				float x = i.r*cos(a*M_PI / 36);
				float y = i.r*sin(a*M_PI / 36);
				glVertex2f(i.x + x, i.y + y);
				x = i.r*cos((a + 1)*M_PI / 36);
				y = i.r*sin((a + 1)*M_PI / 36);
				glVertex2f(i.x + x, i.y + y);
			}
			glEnd();
		}
	}
	glutSwapBuffers();
}
void timer(int = 0)
{
	float d;
	for (int i = 0; i<p.size(); i++)
		for (int j = 0; j<p.size(); j++)
			if (i != j)
			{
				d = sqrt((p[i].x - p[j].x) * (p[i].x - p[j].x) + (p[i].y - p[j].y) * (p[i].y - p[j].y));
				if (d < p[i].r + p[j].r)
				{
					float f = 1000 * (p[i].r + p[j].r - d);
					/*float f = p[i].m*(abs(sqrt(p[i].vx*p[i].vx + p[i].vy*p[i].vy) - sqrt(p[j].vx*p[j].vx + p[j].vy*p[j].vy)));*/
					p[i].vx += f * (p[i].x - p[j].x) / d / p[i].m * DT;
					p[i].vy += f * (p[i].y - p[j].y) / d / p[i].m * DT;
					p[j].vx -= f * (p[i].x - p[j].x) / d / p[j].m * DT;
					p[j].vy -= f * (p[i].y - p[j].y) / d / p[j].m * DT;
				}
			}
	for (int i = 0; i < p.size(); ++i)
	{
		if ((p[i].x - p[i].r < 0) || (p[i].x + p[i].r >1366))
			p[i].vx = -p[i].vx;
		if ((p[i].y - p[i].r < 0) || (p[i].y + p[i].r >768))
			p[i].vy = -p[i].vy;
		p[i].x += p[i].vx * DT;
		p[i].y += p[i].vy * DT;
	}
	display();
	glutTimerFunc(7, timer, 0);
}

int main(int argc, char **argv)
{
	srand(time(NULL));
	for (int i = 0; i < 200; i++)
	{
		float m = 500;
		float r = pow(m, 1.0 / 3.0);
		Particle particle = { i, r, m, rand() % 1366, rand() % 768, rand() % 20500 / 500.0 - 10, rand() % 20500 / 500.0 - 10 };
		p.push_back(particle);
	}
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(1366, 768);
	glutCreateWindow("Brownian motion");
	glClearColor(0.9, 0.9, 0.9, 0.9);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1366, 768, 0, -1, 1);
	glutDisplayFunc(display);
	timer();
	glutMainLoop();
	return 0;
}

