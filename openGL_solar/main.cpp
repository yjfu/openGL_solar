#include <GL\glut.h>  
#include <windows.h>
#include <sstream>
#include <tchar.h>
#include "data.h"
#include<math.h>  
#include"Star.h"
#include<iostream>  

using namespace std;

void Rotate();

Star solar[9];

GLdouble angle = 100.0;

typedef unsigned char byte;

int load_texture(const char *file){
	unsigned int ID;
	int width, height, i;
	GLubyte *image, t;
	FILE *fp;
	BITMAPFILEHEADER FileHeader;
	BITMAPINFOHEADER InfoHeader;

	errno_t err = fopen_s(&fp, file, "rb");
	if (err){
		perror("LoadBitmap");        
		return -1;
	}
	fread(&FileHeader, sizeof(BITMAPFILEHEADER), 1, fp);

	fread(&InfoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
	width = InfoHeader.biWidth;
	height = InfoHeader.biHeight;
	if (InfoHeader.biSizeImage == 0){
		InfoHeader.biSizeImage = width*height * 3;
	}
	fseek(fp, FileHeader.bfOffBits, SEEK_SET);  //将文件指针移动到实际图像数据处
	image = (byte *)malloc(sizeof(byte)*InfoHeader.biSizeImage); //申请空间

	fread(image, 1, InfoHeader.biSizeImage, fp);

	for (i = 0; i<InfoHeader.biSizeImage; i += 3){
		t = image[i];
		image[i] = image[i + 2];
		image[i + 2] = t;
	}
	fclose(fp);

	glGenTextures(1, &ID);

	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, image);

	return ID;
}
void lPosition()
{
	float y, z;
	y = light_radius*cos(light_angle);
	z = light_radius*sin(light_angle);
	float light_position[] = { 3.0,y,z, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
}

void set_solar_attr() {
	GLUquadricObj* g_text = gluNewQuadric();
	for (int i = 0; i < 9; i++) {
		solar[i].set_sun_pos(pos[0]);
		solar[i].set_axis(axis);
		solar[i].set_radius(radius[i]);
		solar[i].set_pos(pos[i]);
		solar[i].set_material(spec_amb_diff[i], spec_amb_diff[i], shininess[i], color[i]);
		string s = "pic/" + star_name[i] + ".bmp";
		solar[i].set_texture(load_texture(s.c_str()));
	}
	gluQuadricTexture(g_text, GLU_TRUE);              //建立纹理坐标  
	gluQuadricDrawStyle(g_text, GLU_FILL);            //用面填充 
	for (int i = 0; i < 9; i++) {
		solar[i].set_text_buffer(g_text);
	}
}



void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	GLfloat white_light[] = { 1.0, 1.0,1.0, 1.0 };
	lPosition();

	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, white_light);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
	//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR); 
	glEnable(GL_TEXTURE_2D);
	set_solar_attr();
}





void display(void)
{
	lPosition();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (int i = 0; i < 9; i++)
		solar[i].draw(0,i);


	Rotate();


	glutSwapBuffers();
}


void myidle()
{
	for (int i = 0; i < 9; i++) {
		solar[i].day += delta_day[i];
		if (solar[i].day >= 360)
			solar[i].day -= 360;
	}
	
	glutPostRedisplay();
}


void Rotate(){ 
	for (int i = 0; i < 9; i++) {
		solar[i].year += delta_year[i];
		if (solar[i].year >= 360)
			solar[i].year -= 360;
	}
	
	glutPostRedisplay();
}

void reset_axis() {
	for (int i = 0; i < 9; i++) {
		solar[i].set_sun_pos(pos[0]);
		solar[i].set_axis(axis);
	}
}


void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(angle, (GLfloat)w / (GLfloat)h, 1.0, 200.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -50.0);
}

wchar_t *chr2wch(const char *buffer)
{
	size_t len = strlen(buffer);
	size_t wlen = MultiByteToWideChar(CP_ACP, 0, (const char*)buffer, int(len), NULL, 0);
	wchar_t *wBuf = new wchar_t[wlen + 1];
	MultiByteToWideChar(CP_ACP, 0, (const char*)buffer, int(len), wBuf, int(wlen));
	wBuf[wlen] = 0;
	return wBuf;
}

void process_picks(GLint nPicks, GLuint pickBuffer[])
{
	GLint i;
	GLuint name, *ptr;
	ptr = pickBuffer;
	for (i = 0; i<nPicks;i++){
		name = *ptr; 
		ptr += 3; 
		ptr += name - 1; 
		std::stringstream ss;
		ss << star_name[*ptr];
		string msg;
		ss >> msg;
		TCHAR t[50];
		_stprintf_s(t, _T("%s%s"),_T("点击星球："), chr2wch(msg.c_str()));
		MessageBox(NULL, t, TEXT("点击信息"), MB_OK | MB_ICONINFORMATION);
		ptr++;
	}
}

void mymouse(GLint button, GLint action, GLint x, GLint y)
{
	GLuint pickBuffer[20];
	GLint nPicks, vp[4];
	if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN) {
		glSelectBuffer(20, pickBuffer);
		glRenderMode(GL_SELECT);
		glInitNames(); 
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		glGetIntegerv(GL_VIEWPORT, vp);
		gluPickMatrix(GLdouble(x), GLdouble(vp[3] - y), 10.0, 10.0, vp);
		gluPerspective(angle, (GLfloat)vp[2]/ (GLfloat)vp[3], 1.0, 200.0);
		glMatrixMode(GL_MODELVIEW);
		for (int i = 0; i < 9; i++)
			solar[i].draw(1, i);
		
		reshape(vp[2], vp[3]);
		glPopMatrix();
		glFlush();
		nPicks = glRenderMode(GL_RENDER);
		process_picks(nPicks, pickBuffer);
		glutPostRedisplay();
	}
}



int main(int argc, char** argv)
{
	cout << argc << endl;
	cout << &argc << endl;


	for (int i = 0; i<argc; i++)
	{
		cout << *argv[i] << endl;
	}

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("solar system");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(myidle);
	glutMouseFunc(mymouse);

	glutMainLoop();
	return 0;
}

