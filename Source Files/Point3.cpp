#include "Point3.h"



Point3::Point3()
{
}

Point3::Point3(double  x, double  y, double  z, int heirarchy)
{
	point.x = x;
	point.y = y;
	point.z = z;

	this->hierarchy = heirarchy;
}


Point3::~Point3()
{
}



