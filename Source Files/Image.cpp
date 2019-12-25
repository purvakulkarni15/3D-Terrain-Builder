#include"Image.h"

Image::Image()
{

}

Image::Image(cv::Mat image)
{
	this->image = image;
}


void Image::getFilteredImage()
{
	cv::Mat grayScaleImage;
	cv::Mat rgbImage;

	cvtColor(image, grayScaleImage, cv::COLOR_BGR2GRAY);
	cvtColor(grayScaleImage, rgbImage, cv::COLOR_GRAY2BGR);

	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			cv::Vec3b color = rgbImage.at<cv::Vec3b>(cv::Point(j, i));

			if (color[0] >= 150 && color[1] >= 150 && color[2] >= 150)
			{
				color[0] = 255;
				color[1] = 255;
				color[2] = 255;
			}
			else if (color[0] <= 150 && color[1] <= 150 && color[2] <= 150)
			{
				color[0] = 0;
				color[1] = 0;
				color[2] = 0;
			}
			else 
			{
				color[0] = 255;
				color[1] = 255;
				color[2] = 255;

			}

			image.at<cv::Vec3b>(cv::Point(j, i)) = color;
		}
	}

	cv::imwrite("CleanedImage.bmp", image);
}

void Image::getContours()
{

	cv::Mat grayScaleImage, blurImage;
	cv::Mat cannyOutput;
	cv::RNG rng(12345);

	cvtColor(image, grayScaleImage, cv::COLOR_BGR2GRAY);
	blur(grayScaleImage, blurImage, cv::Size(3, 3));

	Canny(grayScaleImage, cannyOutput, threshold, threshold * 2, 3);

	findContours(grayScaleImage, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_NONE, cv::Point(0, 0));

	cv::Mat drawing = cv::Mat::zeros(cannyOutput.size(), CV_8UC3);

	for (int i = 0; i < contours.size(); i++)
	{
		cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 1, 8, hierarchy, 0, cv::Point());
	}

	cv::imwrite("EDGE.bmp", drawing);
}

void Image::getPoints()
{
	std::stack<float> hierarchyStack;

	float currHierarchy = 0;

	for (int i = 0; i < hierarchy.size(); i++) 
	{

		if (hierarchy[i][1] != -1)
		{
			currHierarchy = hierarchyStack.top();
			hierarchyStack.pop();
		}

		if (hierarchy[i][0] != -1)
		{
			hierarchyStack.push(currHierarchy);
		}

		for (int j = 0; j < contours[i].size(); j+=2)
		{
			Point3 p;
			p.point.x = contours[i][j].x;
			p.point.y = contours[i][j].y;
			p.point.z = 0;

			p.hierarchy = currHierarchy;
			p.contour = i;
			p.contourIndex = j; 

			if ((points.size() > 0) && !(points[points.size() - 1].point.x == p.point.x && points[points.size() - 1].point.y == p.point.y))
			{
				points.push_back(p);
			}
			else if (points.size() == 0)
			{
				points.push_back(p);
			}
		}

		if (hierarchy[i][2] != -1)
		{
			currHierarchy++;
		}

	}
}
