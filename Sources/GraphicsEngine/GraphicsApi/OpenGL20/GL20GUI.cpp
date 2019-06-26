#include "GL20GUI.h"
#include <string.h>
#include <cstdio>


void GL20GUI::Label(int x, int y, int w, int h, const char * pText)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix(); 
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glDisable(GL_DEPTH_TEST);

	glRasterPos2f(x, y); 
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
	char buf[30];
	sprintf(buf, pText);
	const char * p = buf;
	do glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *p); while (*(++p));

	glEnable(GL_DEPTH_TEST); 

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}
