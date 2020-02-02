#ifndef H_IMAGE
#define H_IMAGE

#include"Point3.h"
#include"ContourSet.h"
#include<vector>
#include<stack>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


class Image
{
	public:

	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;
	std::vector<Point3> points;
	std::vector<ContourSet> contourSet;

	cv::Mat image;
	cv::Mat srcImage;
	int threshold = 0;
	int maxThreshold = 255;

	Image();
	Image(cv::Mat image);
	void getFilteredImage();
	void getContours();
	void getPoints();
	void getHierarchy(std::vector<ContourSet> contourSet_cpy);
};

#endif
