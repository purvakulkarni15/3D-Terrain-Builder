#ifndef H_BB
#define H_BB

#include<vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

class ContourSet
{
	public:

	int heirarchy;
	int index;
	std::vector<cv::Point> contour;

};

#endif