#include	<stdio.h>
#include	<stdlib.h>
#include	<math.h>
#include	<iostream>
#include	<GL\glut.h>
//#include    <GL\freeglut.h>

#define SPEED 0.1

GLdouble eye_x = 7.0, eye_y = 5.0, eye_z = 7.0;
GLdouble center_x = 0, center_y = 0, center_z = 0;

GLdouble rot_x = 0.0, rot_y = 0.0, rot_z = 0.0;

GLdouble light_x = 5.0, light_y = 0.0, light_z = 4.0;

int			mouseOldX = 0;
int			mouseOldY = 0;

/////////////////////////////////////////////////////////////////////////////////

GLfloat light_position[] = { 20.0, 20.0, 20.0, 0.0 };

GLdouble TH = 2, TL = 5, TD = 3;
GLdouble BH = 0.3, BL = 1.5, BD = 1.0;
GLdouble R = 0.03, PL = 10;
GLdouble SizeTeapot = 0.5;

void init()
{
	glClearColor(0.0, 0.0, 0.0, -1.0);
	glEnable(GL_DEPTH_TEST);

	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);
}

void drawTeapot(GLdouble size)
{
	GLfloat mat_emis[4] = { 0.0f, 0.6f, 0.0f, 0.0f };
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emis);
	glutSolidTeapot(size);
}

void drawBook(GLdouble BL, GLdouble BD, GLdouble BH)
{
	GLfloat mat_emis[4] = { 0.5412f, 0.169f, 0.886f, 0.0f };
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emis);
	glPushMatrix();
	glScalef(BL, BD, BH);
	glutSolidCube(1.0);
	glPopMatrix();
}

void drawTable(GLdouble TL, GLdouble TD, GLdouble TH)
{
	GLfloat mat_emis[4] = { 0.6636f, 0.114f, 0.067f, 0.0f };
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emis);
	glPushMatrix();
	glScalef(TL, TD, TH / 10);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-TL / 2 + TH / 10 / 2, -TD / 2 + TH / 10 / 2, -TH / 2 - TH / 10 / 2);
	glScalef(TH / 10, TH / 10, TH);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(TL / 2 - TH / 10 / 2, -TD / 2 + TH / 10 / 2, -TH / 2 - TH / 10 / 2);
	glScalef(TH / 10, TH / 10, TH);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-TL / 2 + TH / 10 / 2, TD / 2 - TH / 10 / 2, -TH / 2 - TH / 10 / 2);
	glScalef(TH / 10, TH / 10, TH);
	glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(TL / 2 - TH / 10 / 2, TD / 2 - TH / 10 / 2, -TH / 2 - TH / 10 / 2);
	glScalef(TH / 10, TH / 10, TH);
	glutSolidCube(1.0);
	glPopMatrix();
}


void drawPencil(GLdouble PL, GLdouble R)
{
	GLfloat mat_emis[4] = { 0.0f, 0.0f, 0.5f, 0.0f };
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emis);
	glPushMatrix();
	glRotated(90, 1.0, 0.0, 0.0);
	glScaled(1.0, 1.0, PL);
	glutSolidTorus(R, R, 100, 100);
	glPopMatrix();
}


void display()
{
	srand(NULL);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	float mat_dif[] = { 0.0f, 0.0f, 0.0f };
	float mat_amb[] = { 0.2f, 0.2f, 0.2f };
	float mat_spec[] = { 0.2f, 0.2f, 0.2f };
	float mat_shininess = 0.1f * 128;
	//GLfloat mat_emis[4] = { 1.0f, 0.0f, 0.0f, 0.0f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_amb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_dif);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_spec);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glRotatef(rot_x, 1, 0, 0);
	glRotatef(rot_y, 0, 1, 0);
	glRotatef(rot_z, 0, 0, 1);

	//glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			glPushMatrix();
			glTranslatef(3 * i * TL / 2, 3 * j * TD / 2, 0);
			drawTable(TL, TD, TH);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(3 * i * TL / 2, 3 * j * TD / 2, TH / 10 / 2 + BH / 2);
			glRotatef(i * j + rand() % 90, 0.0, 0.0, 1.0);
			drawBook(BL, BD, BH);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(3 * i * TL / 2 + TL / 2 - SizeTeapot, 3 * j * TD / 2 + TD / 2 - SizeTeapot, TH / 10 / 2 + SizeTeapot * 0.8);
			glRotatef(90, 1.0, 0.0, 0.0);
			glRotatef((i + 1) * j + rand() % 120, 0.0, 1.0, 0.0);
			drawTeapot(SizeTeapot);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(3 * i * TL / 2 - TL / 3, 3 * j * TD / 2, TH / 10 / 2 + 3 * R / 2);
			drawPencil(PL, R);
			glPopMatrix();

		}
	}

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glPushMatrix();
	glTranslated(light_position[0], light_position[1], light_position[2]);

	//glutSolidSphere(0.1, 5, 5);
	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.0, 60.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye_x, eye_y, eye_z,	// eye
		0, 0, 0,				// center
		0.0, 0.0, 1.0);		// up
}

void motion(int x, int y)
{
	//std::cout << x << " " << y << std::endl;
	rot_y -= ((mouseOldY - y) * 180.0f) / 200.0f;
	rot_z -= ((mouseOldX - x) * 180.0f) / 200.0f;
	rot_x = 0;

	if (rot_z > 360)
		rot_z -= 360;

	if (rot_z < -360)
		rot_z += 360;

	if (rot_y > 360)
		rot_y -= 360;

	if (rot_y < -360)
		rot_y += 360;

	mouseOldX = x;
	mouseOldY = y;

	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		mouseOldX = x;
		mouseOldY = y;
	}
}

void key(unsigned char key, int x, int y)
{
	if (key == 27 || key == 'q' || key == 'Q')		//quit requested
		exit(0);
	switch (key)
	{
	case '1':
		std::cout << "1. glOrtho" << std::endl;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-25, 25, -10, 10, -50, 50);
		break;
	case '2':
		std::cout << "2. gluPerspective" << std::endl;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(60, 1, 1.0, 400);
		break;
	case '3':
		std::cout << "2. glFrustum" << std::endl;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glFrustum(-1, 1, -1, 1, 1, 400);
		break;
	case '-':
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(eye_x += SPEED, eye_y += SPEED, eye_z += SPEED, // eye
			center_x += SPEED, center_y += SPEED, center_z += SPEED, // center
			0.0, 0.0, 1.0); // up
		glutPostRedisplay();
		break;
	case '+':
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(eye_x -= SPEED, eye_y -= SPEED, eye_z -= SPEED, // eye
			center_x -= SPEED, center_y -= SPEED, center_z -= SPEED, // center
			0.0, 0.0, 1.0); // up
		glutPostRedisplay();
		break;
	}
}

int main(int argc, char * argv[])
{
	glutInit(&argc, argv); //initialise glut
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);

	glutCreateWindow("OpenGL testWork for TopSystems");  // create window

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	init();
	glutMainLoop();
	return 0;
}