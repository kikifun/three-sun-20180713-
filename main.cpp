#include <GL/glut.h>
#include <stdlib.h>
#include<cmath>
#include<iostream>
#include"sun.h"
static GLdouble axix = 2.5, axiy = 2.5, z = 2.5;//相机位置
double x1 = -2, y11 = 2, z1 = 0, x2 = 2.5, y2 = -5, z2 = 0, x3 = 6, y3 = 6, z3 = 0;//3个太阳的坐标
double v1x = 0, v1y = 0, v1z = 0, v2x = 0, v2y = 3, v2z = -4.5, v3x = 0, v3y = 0, v3z = -4.5;//三个太阳的速度
double sun1_m = 8, sun2_m = 5, sun3_m = 3;//三个太阳的质量
double x, y, zz;//观察点的坐标

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);//设置着色模式
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glLoadIdentity();             /* clear the matrix *///重置当前指定的矩阵为单位矩阵
														/* viewing transformation  */
	gluLookAt(axix, axiy, z, 0.0, 0.0, 0.0, 2.5, 2.5, 5.0);//gluLookAt函数定义一个视图矩阵
														   /*第一组eyex, eyey,eyez 相机在世界坐标的位置
														   第二组centerx, centery, centerz 相机镜头对准的物体在世界坐标的位置
														   第三组upx, upy, upz 相机向上的方向在世界坐标中的方向*/

	glScalef(1.0, 2.0, 1.0);      /* modeling transformation */
								  //glutWireCube(1.0);
	GLfloat R = 2;
	int n = 10000;
	GLfloat Pi = 3.1415926536;
	glBegin(GL_LINES);

	//三个坐标轴，深色为正轴，浅色为负轴，x为红色，y为绿色，z为紫色
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, 0.0f, 0.0f);

	glColor3f(0.5f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-10.0f, 0.0f, 0.0f);


	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 10.0f, 0.0f);

	glColor3f(0.0f, 0.5f, 0.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, -10.0f, 0.0f);


	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, 10.0f);

	glColor3f(0.0f, 0.0f, 0.5f);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 0.0f, -10.0f);
	glEnd();


	vectors sun1_x(x1, y11, z1);
	vectors sun1_v(v1x,v1y,v1z);
	//double sun1_m = 1;
	sun sun1(sun1_m, sun1_x, sun1_v);

	vectors sun2_x(x2, y2, z2);
	vectors sun2_v(v2x, v2y, v2z);
	//double sun2_m = 5;
	sun sun2(sun2_m, sun2_x, sun2_v);

	vectors sun3_x(x3, y3, z3);
	vectors sun3_v(v3x,v3y,v3z);
	//double sun3_m = 1;
	sun sun3(sun3_m, sun3_x, sun3_v);
	imitate imi(sun1, sun2, sun3);
	imi.totalImitate();
	vectors observe(x,y,z);
	glFlush();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);//在窗口中定义一个像素矩形，最终将图像映射到这个矩形中
	glMatrixMode(GL_PROJECTION);//指定哪一个矩阵是当前矩阵
	glLoadIdentity();//重置当前指定的矩阵为单位矩阵.
					 // glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 1.5, 20.0);//指定了观察的视景体在世界坐标系中的具体大小
	glMatrixMode(GL_MODELVIEW);
	/*指定哪一个矩阵是当前矩阵。创建一个投影矩阵并且与当前矩阵相乘，得到的矩阵设定为当前变换，
	但要先通过glMatrixMode设定成投影矩阵才会得到想要的投影矩阵变换。*/
}
//通过按awsd键来转换视角
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 'd':
		axix += 1.0;
		glutPostRedisplay();
		break;
	case 'a':
		axix -= 1.0;
		glutPostRedisplay();
		break; 
	case 'w':
		z -= 1.0;
		glutPostRedisplay();
		break;
	case 's':
		z += 1.0;
		glutPostRedisplay();
		break;
	case 27:
		exit(0);
		break;
	}
}

int main(int argc, char** argv)
{
	cout << "请记住，当画面稳定后，按asdw键盘可以转换视角观察!!!\n请记住，当画面稳定后，按asdw键盘可以转换视角观察!!!\n请记住，当画面稳定后，按asdw键盘可以转换视角观察!!!\n";
	cout << "使用默认数据输入1，自己输入三体数据输入2：";
	int a;
	cin >> a;
	if (a == 2)
	{//sun1参数输入
		cout << "\n请输入sun1的x,y,z坐标(控制在10以内的小数）：";
		cin >> x1 >> y11 >> z1;
		cout << "\n请输入sun1的质量：";
		cin >> sun1_m;
		cout << "\n请输入sun1的x,y,z坐标方向上的速度(控制在5以内的小数）：";
		cin >> v1x >> v1y >> v1z;

		//sun2参数输入
		cout << "\n请输入sun2的x,y,z坐标(控制在10以内的小数）：";
		cin >> x2 >> y2 >> z2;
		cout << "\n请输入sun2的质量：";
		cin >> sun2_m;
		cout << "\n请输入sun1的x,y,z坐标方向上的速度(控制在5以内的小数）：";
		cin >> v2x >> v2y >> v2z;

		//sun3参数输入
		cout << "\n请输入sun3的x,y,z坐标(控制在10以内的小数）：";
		cin >> x3 >> y3 >> z3;
		cout << "\n请输入sun3的质量：";
		cin >> sun3_m;
		cout << "请输入sun1的x,y,z坐标方向上的速度(控制在5以内的小数）：";
		cin >> v3x >> v3y >> v3z;
	}
	cout << "输入观察点的坐标（控制在10以内的小数）： ";
	cin >> x >> y >> z;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(400, 100);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
