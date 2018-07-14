#include "sun.h"

//----------------------------------------------------------------------------------------------------
vectors::vectors()
{
	x = 0;
	y = 0;
	z = 0;
}

vectors::vectors(const vectors &other)
{
	x = other.x;
	y = other.y;
	z = other.z;
}

vectors::vectors(double x, double y, double z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}


vectors operator+(const vectors & one, const vectors & two)
{
	double x = one.x + two.x;
	double y = one.y + two.y;
	double z = one.z + two.z;
	return vectors(x, y, z);
}

vectors operator-(const vectors &one, const vectors &two)
{
	double x = one.x - two.x;
	double y = one.y - two.y;
	double z = one.z - two.z;
	return vectors(x, y, z);
}

vectors operator*(int a, const vectors& v)
{
	double x = a * v.x;
	double y = a * v.y;
	double z = a * v.z;
	return vectors(x, y, z);
}

vectors operator*(const vectors &v, double a)
{
	double x = a * v.x;
	double y = a * v.y;
	double z = a * v.z;
	return vectors(x, y, z);
}

ostream  &operator<<(ostream &output, sun &s)
{
	output << "位置为: " << s.location.x << "," << s.location.y << "," << s.location.z << endl;
	return output;
}

void vectors::single()
{
	double model = sqrt(x*x + y * y + z * z);
	x = x / model;
	y = y / model;
	z = z / model;
}

//-------------------------------------------------------------------------------------------------------
sun::sun(double m, vectors x, vectors v)
	:location(x), velocity(v)
{
	this->m = m;
}

sun::sun(double m)
{
	vectors x(0, 0, 0);
	location = x;
	velocity = x;
	this->m = m;
}

sun::sun(const sun &other)
{
	location = other.location;
	velocity = other.velocity;
	accelerrate = other.accelerrate;
	m = other.m;
}

sun::sun()
{
	m = 1;
}

//------------------------------------------------------------------------------------------------------
imitate::imitate(sun sun1, sun sun2, sun sun3)
	:prevSunA(sun1), prevSunB(sun2), prevSunC(sun3),
	sunA(sun1.m), sunB(sun2.m), sunC(sun3.m),
	nextSunA(sun1.m), nextSunB(sun2.m), nextSunC(sun3.m)
{
	G = 5 ;
	intervalTime = 0.1;
	totalTime = 1000;
}

imitate::imitate()
{
	G = 5;
	intervalTime = 0.01;
	totalTime = 100;
}

double imitate::calculateR(const sun &sun1, const sun &sun2)
{
	double R = sqrt(pow((sun1.location.x - sun2.location.x), 2) + pow((sun1.location.y - sun2.location.y), 2)
		+ pow((sun1.location.z - sun2.location.z), 2));
	return R;
}

vectors imitate::calculateAcc(const sun &sun1, const sun &sun2)
{
	double R = calculateR(sun1, sun2);
	double a = G * sun2.m / R / R;
	vectors direction = sun2.location - sun1.location;
	direction.single();

	return vectors(direction.x*a, direction.y*a, direction.z*a);
}

void imitate::getAllAcc()
{
	vectors ACCab = calculateAcc(sunA, sunB);
	vectors ACCac = calculateAcc(sunA, sunC);
	vectors ACCbc = calculateAcc(sunB, sunC);
	vectors ACCba = calculateAcc(sunB, sunA);
	vectors ACCca = calculateAcc(sunC, sunA);
	vectors ACCcb = calculateAcc(sunC, sunB);
	sunA.accelerrate = ACCab + ACCac;
	sunB.accelerrate = ACCba + ACCbc;
	sunC.accelerrate = ACCca + ACCcb;
}

bool imitate::ifCrash()
{
	double Rab = calculateR(sunA, sunB);
	double Rac = calculateR(sunA, sunC);
	double Rbc = calculateR(sunB, sunC);
	if (Rab <= (sunA.m + sunB.m) / 10 || Rac <= (sunA.m + sunC.m) / 10 || Rbc <= (sunB.m + sunC.m) / 10)return true;
	else return false;
}

void imitate::totalImitate()
{
	double X1, X2, X3;
	double T0 = 1, T;//确定太阳的热辐射强度
	double E0 = 1, E;//确定太阳的光照强度

	sunA.location = prevSunA.velocity*intervalTime + prevSunA.location;
	sunB.location = prevSunB.velocity*intervalTime + prevSunB.location;
	sunC.location = prevSunC.velocity*intervalTime + prevSunC.location;
	int times = totalTime / intervalTime;

	for (size_t i = 1; i <= 200; i++)//时刻决定于i的大小
	{
		getAllAcc();
		nextSunA.location = 2 * sunA.location - prevSunA.location + sunA.accelerrate*(intervalTime*intervalTime);
		nextSunB.location = 2 * sunB.location - prevSunB.location + sunB.accelerrate*(intervalTime*intervalTime);
		nextSunC.location = 2 * sunC.location - prevSunC.location + sunC.accelerrate*(intervalTime*intervalTime);
		prevSunA = sunA;
		prevSunB = sunB;
		prevSunC = sunC;
		sunA = nextSunA;
		sunB = nextSunB;
		sunC = nextSunC;
		glBegin(GL_POINTS);
		glColor3f(1.0f, 0.0f, 0.0f);
		//for(int i=0;i<n;i++)
		glPointSize(10);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(sunA.location.x*0.05, sunA.location.y*0.05, sunA.location.z*0.05);
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(sunB.location.x*0.05, sunB.location.y*0.05, sunB.location.z*0.05);
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex3f(sunC.location.x*0.05, sunC.location.y*0.05, sunC.location.z*0.05);
		glEnd();
		glFlush();
		if (ifCrash())
		{
			cout << "crash!!!" << endl;
			break;
		}
		//sunA.location.x;
		Sleep(50);
		/*cout << sunA << sunB << sunC;*/
		X1 = sqrt((pow(observe.location.x  - sunA.location.x, 2) + pow(observe.location.x - sunA.location.x, 2) + pow(observe.location.x - sunA.location.x, 2)));
		X2 = sqrt((pow(observe.location.x - sunB.location.x, 2) + pow(observe.location.x - sunB.location.x, 2) + pow(observe.location.x - sunB.location.x, 2)));
		X3 = sqrt((pow(observe.location.x - sunC.location.x, 2) + pow(observe.location.x - sunC.location.x, 2) + pow(observe.location.x - sunC.location.x, 2)));
		T = T0 / pow(X1, 3) + T0 / pow(X2, 3) + T0 / pow(X3, 3);
		E = E0 / pow(X1, 2) + E0 / pow(X1, 2) + E0 / pow(X1, 2);
		cout << "时刻" << i << ":" << endl;
		cout << "该点的温度为：" << T << endl;
		cout << "该点的亮度为：" << E << endl;
		cout << endl;


	}
}
