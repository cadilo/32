#include "Graph.h"
#include <glut.h>
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "rus");

	glutInit(&argc, argv);
	MakeGraph();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(WinW, WinH);
	glutCreateWindow("Graph");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(Click);
	glutPassiveMotionFunc(Movement);
	glutMainLoop();
}