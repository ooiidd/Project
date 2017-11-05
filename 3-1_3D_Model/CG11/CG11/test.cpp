#include <windows.h>
#include<iostream>
#include<stdio.h>
#include<gl/GL.h>
#include<gl/GLU.h>
#include<gl/GLAUX.H>
#include<stdlib.h>
#include<math.h>
#include<glut.h>
using namespace std;
#define PI 3.14159265358979323846
#define M 36
#define N 18

int clickX;
int clickY;
double angleX;
double angleY;
double temp_anX;
double temp_anY;
double zoom=5;
double upvecy=1.0;
double temp_zoomx=0, temp_zoomy=0;

float radius = 1;
float theta;
float phi;
float delta_theta;
float delta_phi;
GLuint	texture[1];

struct Point3D {
	float x;
	float y;
	float z;
};

Point3D vertex[5][M][N + 1];

float cameraX = 0;
float cameraY = 0;
float cameraZ = 5;

AUX_RGBImageRec *LoadBMP(char *Filename)				// Loads A Bitmap Image
{
	FILE *File = NULL;									// File Handle
	cout << Filename<<endl;
	if (!Filename)										// Make Sure A Filename Was Given
	{
		cout<<"file ÀÌ¸§µµ ¾øÀ½"<<endl;
		return NULL;									// If Not Return NULL
	}
	/*
	File = fopen(Filename, "r");							// Check To See If The File Exists
	*/
	fopen_s(&File,Filename,"r");
	if (File)											// Does The File Exist?
	{
		fclose(File);									// Close The Handle
		return auxDIBImageLoadA(Filename);				// Load The Bitmap And Return A Pointer
	}
	cout <<"return null2"<<endl;
	return NULL;										// If Load Failed Return NULL
}
int LoadGLTextures()									// Load Bitmaps And Convert To Textures
{
	int Status=FALSE;									// Status Indicator

	AUX_RGBImageRec *TextureImage[1];					// Create Storage Space For The Texture

	memset(TextureImage,0,sizeof(void *)*1);           	// Set The Pointer To NULL

	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	if (TextureImage[0]=LoadBMP("1.bmp"))
	{
		Status=TRUE;									// Set The Status To TRUE
		cout << "ÀÌ¹ÌÁö Ã£À½"<<endl;

		glGenTextures(1, &texture[0]);					// Create The Texture

		// Typical Texture Generation Using Data From The Bitmap
		glBindTexture(GL_TEXTURE_2D, texture[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	else{
		cout << "ÀÌ¹ÌÁö ¸øÃ£À½"<<endl;
	}
	if (TextureImage[0])									// If Texture Exists
	{
		if (TextureImage[0]->data)							// If Texture Image Exists
		{
			free(TextureImage[0]->data);					// Free The Texture Image Memory
		}

		free(TextureImage[0]);								// Free The Image Structure
	}

	return Status;										// Return The Status
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST);
	LoadGLTextures();
}
void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f,(GLfloat)500/(GLfloat)500,0.1f,100.0f);
}
void display(void)
{/*
	//test
	if(!LoadGLTextures())
	{
		return ;
	}
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
		
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();									// Reset The View
	glTranslatef(0.0f,0.0f,-5.0f);
	*/
	/*
	glClearColor(0.8, 0.8, 0.8, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, upvecy, 0.0);

	
	
GLUquadricObj *qObj = gluNewQuadric();
	gluQuadricNormals(qObj,GLU_SMOOTH);
	gluQuadricTexture(qObj,GL_TRUE);
	
	
	glEnable(GL_TEXTURE_2D);
	glTranslatef(1,0.5,0);
	glScalef(1, 1, 0.5);
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	

	gluSphere(qObj,0.8f,30,30);
	glDisable(GL_TEXTURE_2D);*/
	/*
	gluSphere(qObj,1.0f,24,24);
	
	


	/*
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
		// Front Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		// Back Face
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		// Top Face
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		// Bottom Face
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		// Right face
		glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, -1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, -1.0f,  1.0f);
		// Left Face
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f,  1.0f,  1.0f);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();
	*/
	//------------------------------
	
	glClearColor(0.8, 0.8, 0.8, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, upvecy, 0.0);

	


	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);

	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 10.0, 0.0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, 10.0);
	glEnd();

	
	
	//¸Ó¸®ºÎºÐ
	glPopMatrix();
	glPushMatrix();
	glScalef(1, 1, 0.9);
	glColor3f(1.0, 1.0, 0.9);
	glTranslatef(0.0, 1.5, 0);
	glutSolidSphere(1.0, 80, 80);


	//´«ºÎºÐ ½ÃÀÛ
	//¿À¸¥ÂÊ ´« 
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glTranslatef(0.17, 1.5, 0.19);
	glutSolidSphere(0.7, 80, 80);
	//´«¾Ë Èò»ö
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.22, 1.5, 0.317);
	glutSolidSphere(0.573, 80, 80);

	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glTranslatef(0.24, 1.494, 0.392);
	glutSolidSphere(0.5, 80, 80);

	glPopMatrix();
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(0.32, 1.45, 0.8);
	glutSolidSphere(0.135, 80, 80);

	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.314, 1.45, 0.84);
	glutSolidSphere(0.096, 80, 80);

	//´«½ç
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glTranslatef(0.2, 1.86, 0.84);
	glutSolidSphere(0.05, 80, 80);

	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glTranslatef(0.4, 1.93, 0.77);
	glutSolidSphere(0.05, 80, 80);

	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glTranslatef(0.6, 1.89, 0.68);
	glutSolidSphere(0.05, 80, 80);

	//¿À¸¥ÂÊ ´« ³¡

	//´« ¿ÞÂÊ ½ÃÀÛ

	glPopMatrix();
	glPushMatrix();

	glColor3f(0.0, 1.0, 0.0);
	glTranslatef(-0.17, 1.5, 0.19);
	glutSolidSphere(0.7, 80, 80);
	//´«¾Ë Èò»ö
	glPopMatrix();
	glPushMatrix();


	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-0.22, 1.5, 0.317);
	glutSolidSphere(0.573, 80, 80);

	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glTranslatef(-0.24, 1.494, 0.392);
	glutSolidSphere(0.5, 80, 80);

	glPopMatrix();
	glPushMatrix();
	glColor3f(0, 0, 0);
	glTranslatef(-0.32, 1.45, 0.8);
	glutSolidSphere(0.135, 80, 80);

	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-0.314, 1.45, 0.84);
	glutSolidSphere(0.096, 80, 80);

	//´«½ç
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glTranslatef(-0.2, 1.86, 0.84);
	glutSolidSphere(0.05, 80, 80);

	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glTranslatef(-0.4, 1.93, 0.77);
	glutSolidSphere(0.05, 80, 80);

	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0, 1.0, 0.0);
	glTranslatef(-0.6, 1.89, 0.68);
	glutSolidSphere(0.05, 80, 80);
	glPopMatrix();
	//´«½ç³¡

	//ÀÔ ºÎºÐ
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.9, 0.0, 0.0);
	glTranslatef(0, 0.9, 0.7);
	glScalef(1.1, 1.5, 1);
	glutSolidSphere(0.07, 80, 80);
	glPopMatrix();

	glPopMatrix();
	glPushMatrix();
	glColor3f(0.9, 0.0, 0.0);
	glTranslatef(0, 0.95, 0.75);
	glRotatef(45, 45, 0, 0);
	glScalef(1.1, 1.5, 1);
	glutSolidSphere(0.07, 80, 80);
	glPopMatrix();

	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0, 0.95, 0.75);
	glScalef(1.0, 1.5, 1);
	glutSolidSphere(0.07, 80, 80);
	glPopMatrix();
	//ÀÔ³¡
	//¸Ó¸®ºÎºÐ ³¡

	//¸öÅë ºÎºÐ
	glPushMatrix();
	GLUquadricObj *qObj = gluNewQuadric();
	gluQuadricNormals(qObj,GLU_SMOOTH);
	gluQuadricTexture(qObj,GL_TRUE);

	glColor3f(1.0, 1.0, 1.0);
	//glScalef(1, 1, 0.8);

	glEnable(GL_TEXTURE_2D);
	glScalef(1, 1, 0.8);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	gluSphere(qObj,1.0f,30,30);
	glDisable(GL_TEXTURE_2D);
	
	//glutSolidSphere(1, 30, 30);
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.25, -0.15, 0);
	
	glutSolidSphere(0.8, 30, 30);

	glPopMatrix();
	glPushMatrix();
	glScalef(1, 1, 0.8);
	glTranslatef(-0.25, -0.15, 0);
	glutSolidSphere(0.8, 30, 30);
	//¸öÅëºÎºÐ ³¡
	//Texture mapping
	
	//Texture mapping end
	//¿À¸¥ÂÊ ÆÈºÎºÐ ½ÃÀÛ
	glPopMatrix();
	glPushMatrix();

	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.95, 0.4, 0);
	glRotatef(90, 0.1, 1, 0);
	glutSolidCone(0.21, 0.9, 50, 50);

	glPopMatrix();
	//
	glPopMatrix();
	glPushMatrix();

	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(1.22, 0.4, 0.0);
	glRotatef(90, 0.1, 1, 0);
	glutSolidCone(0.12, 0.8, 50, 50);

	glPopMatrix();

	//ÆÈ¶Ò»ì 1
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.8, 0.44, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidSphere(0.22, 30, 30);

	glPopMatrix();
	//
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.9, 0.40, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidSphere(0.22, 30, 30);

	glPopMatrix();
	//
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.92, 0.38, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidSphere(0.20, 30, 30);

	glPopMatrix();

	//ÆÈ¶Ò»ì 2
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.95, 0.37, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidSphere(0.22, 30, 30);

	glPopMatrix();
	//ÆÈ¶Ò»ì 3
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(1.1, 0.36, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidSphere(0.155, 30, 30);

	glPopMatrix();
	//¼Õ
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(1.91, 0.35, 0);
	glRotatef(90, 0.1, 1, 0);
	glutSolidSphere(0.1, 30, 30);

	glPopMatrix();


	/////¿ÞÂÊÆÈ ºÎºÐ ½ÃÀÛ
	//ÆÈºÎºÐ ½ÃÀÛ
	glPopMatrix();
	glPushMatrix();

	glRotatef(180, 0, 1, 0);
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.9, 0.4, 0);
	glRotatef(90, -0.3, 1, 0);
	glutSolidCone(0.21, 0.9, 50, 50);

	glPopMatrix();
	//
	glPopMatrix();
	glPushMatrix();

	glRotatef(180, 0, 1, 0);
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(1.2, 0.4, 0);
	glRotatef(90, -0.5, 1, 0);
	glutSolidCone(0.14, 0.8, 50, 50);

	glPopMatrix();

	//ÆÈ¶Ò»ì 1
	glPopMatrix();
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.8, 0.42, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidSphere(0.22, 30, 30);

	glPopMatrix();
	//
	glPopMatrix();
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.9, 0.40, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidSphere(0.22, 30, 30);

	glPopMatrix();
	//
	glPopMatrix();
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.92, 0.38, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidSphere(0.20, 30, 30);

	glPopMatrix();

	//ÆÈ¶Ò»ì 2
	glPopMatrix();
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.95, 0.3, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidSphere(0.22, 30, 30);

	glPopMatrix();
	//ÆÈ¶Ò»ì 3
	glPopMatrix();
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(1.13, 0.36, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidSphere(0.156, 30, 30);

	glPopMatrix();
	//¼Õ
	glPopMatrix();
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glColor3f(2.0, 1.0, 1.0);
	glTranslatef(1.8, 0.74, 0);
	glRotatef(90, 0, 1, 0);
	glutSolidSphere(0.1, 30, 30);

	glPopMatrix();
	/////¿ÞÂÊ ÆÈ ºÎºÐ ³¡


	//¾ÆÀÌ½ºÅ©¸² ÄÜ ½ÃÀÛ

	glPopMatrix();
	glPushMatrix();
	//ÄÜ
	glRotatef(180, 0, 1, 0);
	glColor3f(0.7, 0.6, 0.4);
	glTranslatef(1.52, 1.2, 0);
	glRotatef(90.0, 115.0, 90, 0);
	glutSolidCone(0.13, 0.6, 50, 50);

	glPopMatrix();
	//¾ÆÀÌ½ºÅ©¸²
	glPopMatrix();
	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glColor3f(0.9, 0.5, 0.5);
	glTranslatef(1.45, 1.28, 0);
	glRotatef(90, 90, 90, 0);
	glutSolidSphere(0.15, 15, 20);

	glPopMatrix();

	//¾ÆÀÌ½ºÅ©¸² ³¡

	//´Ù¸® ½ÃÀÛ
	//¿À¸¥ÂÊ´Ù¸®//
	//¸ö ¹Ù·Î ¹Ø ´Ù¸®
	glPopMatrix();
	glPushMatrix();

	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.44, -0.7, 0);
	glRotatef(90.0, 90.0, 0.0, 0);
	glutSolidCone(0.4, 0.8, 50, 50);

	glPopMatrix();

	//µÎ¹øÂ° ´Ù¸®
	glPopMatrix();
	glPushMatrix();

	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.43, -1, 0);
	glRotatef(90.0, 90.0, 0.0, 0);
	glutSolidCone(0.2, 0.65, 50, 50);

	glPopMatrix();

	//¹ß
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.43, -1.6, 0.09);
	glScalef(0.8, 0.5, 1.2);
	glutSolidSphere(0.16, 30, 30);

	//¿ÞÂÊ´Ù¸®//
	//¸ö ¹Ù·Î ¹Ø ´Ù¸®
	glPopMatrix();
	glPushMatrix();

	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(-0.44, -0.7, 0);
	glRotatef(90.0, 90.0, 0.0, 0);
	glutSolidCone(0.4, 0.8, 50, 50);

	glPopMatrix();

	//µÎ¹øÂ° ´Ù¸®
	glPopMatrix();
	glPushMatrix();

	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(-0.43, -1, 0);
	glRotatef(90.0, 90.0, 0.0, 0);
	glutSolidCone(0.2, 0.65, 50, 50);

	glPopMatrix();
	//¹ß
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(-0.43, -1.6, 0.09);
	glScalef(0.8, 0.5, 1.2);
	glutSolidSphere(0.16, 30, 30);
	glPopMatrix();
	//´Ù¸® ³¡

	//glColor3f(1.0, 0.0, 0.0);
	//glTranslatef(-2, 0, 0);

	//glutSolidSphere(1, 30, 30);
	/*
	delta_theta = 2 * PI / M;
	delta_phi = PI / N;

	int i = 0, j = 0,k=0;
	for (k = 0; k < 3; k++) {
	for (j = 0; j <= N; j++) {
	for (i = 0; i < M; i++) {
	theta = i*delta_theta;
	phi = j*delta_phi - (PI / 2.0);
	vertex[k][i][j].x = radius*cos(theta)*cos(phi);
	vertex[k][i][j].y = radius*sin(theta)*cos(phi);
	vertex[k][i][j].z = radius * sin(phi);
	}
	}
	}
	//glLoadIdentity();
	for (j = 0; j < N; j++) {
	for (i = 0; i < M; i++) {
	theta = i*delta_theta;
	phi = j*delta_phi - (PI / 2);

	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(vertex[0][i][j].x, vertex[0][i][j].y, vertex[0][i][j].z);
	glVertex3f(vertex[0][(i + 1) % M][j].x, vertex[0][(i + 1) % M][j].y, vertex[0][(i + 1) % M][j].z);
	glVertex3f(vertex[0][(i + 1) % M][j + 1].x, vertex[0][(i + 1) % M][j + 1].y, vertex[0][(i + 1) % M][j + 1].z);
	glVertex3f(vertex[0][i][j + 1].x, vertex[0][i][j + 1].y, vertex[0][i][j + 1].z);
	glEnd();
	}
	}
	glPushMatrix();
	glTranslatef(0, 1, 0);

	for (j = 0; j < N; j++) {
	for (i = 0; i < M; i++) {
	theta = i*delta_theta;
	phi = j*delta_phi - (PI / 2);

	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(vertex[1][i][j].x, vertex[1][i][j].y, vertex[1][i][j].z);
	glVertex3f(vertex[1][(i + 1) % M][j].x, vertex[1][(i + 1) % M][j].y, vertex[1][(i + 1) % M][j].z);
	glVertex3f(vertex[1][(i + 1) % M][j + 1].x, vertex[1][(i + 1) % M][j + 1].y, vertex[1][(i + 1) % M][j + 1].z);
	glVertex3f(vertex[1][i][j + 1].x, vertex[1][i][j + 1].y, vertex[1][i][j + 1].z);
	glEnd();
	}
	}
	glLoadIdentity();
	glPopMatrix();
	glTranslatef(1, 0, 0);
	for (j = 0; j < N; j++) {
	for (i = 0; i < M; i++) {
	theta = i*delta_theta;
	phi = j*delta_phi - (PI / 2);

	glColor3f(0.0, 1.0, 1.0);
	glBegin(GL_POLYGON);
	glVertex3f(vertex[1][i][j].x, vertex[1][i][j].y, vertex[1][i][j].z);
	glVertex3f(vertex[1][(i + 1) % M][j].x, vertex[1][(i + 1) % M][j].y, vertex[1][(i + 1) % M][j].z);
	glVertex3f(vertex[1][(i + 1) % M][j + 1].x, vertex[1][(i + 1) % M][j + 1].y, vertex[1][(i + 1) % M][j + 1].z);
	glVertex3f(vertex[1][i][j + 1].x, vertex[1][i][j + 1].y, vertex[1][i][j + 1].z);
	glEnd();
	}
	}*/

	glFlush();
	glutSwapBuffers();
}



void key(unsigned char key, int x, int y) {
	switch (key) {
	case 27:
		exit(0);
		break;
	case 97://a
		zoom -= 0.5;
		cameraX = zoom*sin(temp_zoomx)*cos(temp_zoomy);
		cameraY =-zoom*sin(temp_zoomy);
		cameraZ = zoom*cos(temp_zoomx)*cos(temp_zoomy);
		cout << temp_zoomx << " "<<temp_zoomy<<endl;
		break;
	case 122://z
		zoom += 0.5;
		cameraX = zoom*sin(temp_zoomx)*cos(temp_zoomy);
		cameraY =-zoom*sin(temp_zoomy);
		cameraZ = zoom*cos(temp_zoomx)*cos(temp_zoomy);
		cout << temp_zoomx << " "<<temp_zoomy<<endl;
		break;
	}
}

void specialKey(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		cameraX -= 1;
		break;
	case GLUT_KEY_RIGHT:
		cameraX += 1;
		break;
	case GLUT_KEY_UP:
		cameraY += 1;
		break;
	case GLUT_KEY_DOWN:
		cameraY -= 1;
		break;
	/*case 97://a
		zoom -= 0.5;
		break;
	case 122://z
		zoom += 0.5;
		break;*/
	}
}

void myMouseClick(GLint button, GLint state, GLint x, GLint y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		clickX = x;
		clickY = y;
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		angleX += temp_anX;
		angleY += temp_anY;//6.28333
		if (angleY >= 6.28333) angleY -= 6.28333;
		if (angleX >= 6.28333) angleY -= 6.28333;
	}
}

void myMouseMotion(GLint x, GLint y) {
	
	//bool prex_bo;
	double prex;
	prex = cameraX;
	double tempx, tempy;
	tempx = ((double)(clickX - x) / 360);
	tempy = ((double)(clickY - y) / 360);
	temp_anX = tempx;
	temp_anY = tempy;
	if (angleY + tempy >= 6.28333) angleY -= 6.28333;
	if (angleY + tempy <= -6.28333) angleY += 6.28333;

	cameraX = zoom*sin(temp_zoomx=(tempx+angleX))*cos(temp_zoomy=(tempy+angleY));
	cameraY = -zoom*sin(tempy+angleY);
	cameraZ = zoom*cos(tempx+angleX)*cos(tempy+angleY);
	/*if ((prex > 0 && cameraX > 0) || (prex < 0 && cameraX < 0)) {
		prex_bo = true;
	}
	else {
		prex_bo = false;
	}
	if (cameraZ < 0 && cameraY>=zoom*1-0.001) {
		upvecy = -upvecy;
	}*/
	if (tempy + angleY <= -1.56944 && tempy + angleY >= -4.71111){
		upvecy = -1.0;
	}
	else if (tempy + angleY >= 1.56945 && tempy + angleY <= 4.71111){
		upvecy = -1.0;
	}
	else upvecy = 1.0;
	cout << tempx+angleX << " " << tempy+angleY << "  " <<upvecy <<endl;
	cout << temp_zoomx << " " << temp_zoomy << endl;
}


void main(int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("cube");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(key);
	glutSpecialFunc(specialKey);
	glutIdleFunc(display);
	init();
	glutMouseFunc(myMouseClick);
	glutMotionFunc(myMouseMotion);

	glutMainLoop();

}
