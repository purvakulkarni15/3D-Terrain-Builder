#pragma once
#include<iostream>
#include "Point3.h"
#include "Image.h"

class Generate3DModel
{
	public:

	Image image;
	cv::Size size;
	cv::Rect rect;
	int index = 0;
	Point3* mat;
	std::vector<cv::Point2f> points2D;

	~Generate3DModel();
	Generate3DModel();
	cv::Subdiv2D delaunayTriangulation();


	void populateData();
	void enhanceGrid();
	void createOBJFile();

};

