//使用了openGL


#pragma once
#include<iostream>
using namespace std;
#include<cmath>
#include <GL/glut.h>
#include <stdlib.h>
#include<Windows.h>

struct vectors
{
public:
	vectors();
	vectors(const vectors&);
	vectors(double, double, double);
	friend vectors operator +(const vectors&, const vectors&);
	friend vectors operator -(const vectors&, const vectors&);
	friend vectors operator *(int, const vectors&);
	friend vectors operator *(const vectors&, double);
	void single();/*单位化*/

	double x;
	double y;
	double z;
};

struct sun
{
public:
	sun(double m, vectors x, vectors y);
	sun(double m);
	sun(const sun&);
	sun();

	double m;/*质量*/
	vectors location;/*当前位置*/
	vectors velocity;/*速度*/
	vectors accelerrate;/*加速度*/
	friend ostream &operator<<(ostream &, sun &);
};


class imitate
{
	//friend void display();
public:
	//friend void display();
	explicit imitate(sun, sun, sun);
	imitate();
	void totalImitate();/*模拟函数*/
	
private:
	double calculateR(const sun&, const sun&);/*计算某sun之间的距离*/
	vectors calculateAcc(const sun&, const sun&);/*计算某两个sun之间的加速度*/
	void getAllAcc();/*得到所有sun的加速度*/
	bool ifCrash();/*判断是否碰撞*/

	double G;
	double totalTime;/*总时间*/
	double intervalTime;/*间隔时间*/
	sun prevSunA;
	sun prevSunB;
	sun prevSunC;
	sun sunA;
	sun sunB;
	sun sunC;
	sun observe;
	sun nextSunA;
	sun nextSunB;
	sun nextSunC;
	
};

