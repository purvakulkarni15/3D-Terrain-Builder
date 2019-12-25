#ifndef H_POINT
#define H_POINT

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Point3
{
	public:

	glm::vec3 point;
	float hierarchy;
	int contour;
	int contourIndex;
	int index;

	Point3();
	Point3(double x, double y, double z, int heirarchy);
	~Point3();

};

#endif