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
			else if (color[0] <= 70 && color[1] <= 70 && color[2] <= 70)
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

cv::Size size;

void Image::getContours()
{

	cv::Mat grayScaleImage, blurImage;
	cv::Mat cannyOutput;
	cv::RNG rng(12345);

	cvtColor(image, grayScaleImage, cv::COLOR_BGR2GRAY);
	blur(grayScaleImage, blurImage, cv::Size(3, 3));

	Canny(grayScaleImage, cannyOutput, threshold, threshold * 2, 3);

	findContours(grayScaleImage, contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	cv::Mat drawing = cv::Mat::zeros(cannyOutput.size(), CV_8UC3);

	size = cannyOutput.size();

	for (int i = 0; i < contours.size(); i++)
	{
		cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		drawContours(drawing, contours, i, color, 1, 8, hierarchy, 0, cv::Point());
	}

	cv::imwrite("EDGE.bmp", drawing);
}


void Image::getHierarchy(std::vector<ContourSet> contourSet_cpy) {

	int index = 0;
	int heirarchy = 0;

	while (contourSet_cpy.size() != 0)
	{
		std::vector<int> topContourIndices;

		for (int i = 0; i < contourSet_cpy.size(); i++)
		{
			bool contained = false;

			for (int j = 0; j < contourSet_cpy.size(); j++)
			{
				if (i != j) 
				{
					for (int k = 0; k < contourSet_cpy[i].contour.size(); k++)
					{
						cv::Point2f pt = cv::Point2f(contourSet_cpy[i].contour[k].x, contourSet_cpy[i].contour[k].y);
						double dist = cv::pointPolygonTest(contourSet_cpy[j].contour, pt, true);

						if (dist > 0.1) 
						{
							contained = true;
							break;
						}
					}
				}
			}
			if (contained == false) {
				topContourIndices.push_back(i);
				contourSet[contourSet_cpy[i].index].heirarchy = heirarchy;

			}
		}

		std::vector<ContourSet> contourSet_bk;
		bool add = true;
		for (int i = 0; i < contourSet_cpy.size(); i++)
		{
			add = true;
			for (int j = 0; j < topContourIndices.size(); j++)
			{
				if (i == topContourIndices[j])
				{
					add = false;
					break;
				}
			}
			
			if (add) {
				contourSet_bk.push_back(contourSet_cpy[i]);
			}
		}

		contourSet_cpy.clear();
		contourSet_cpy = contourSet_bk;
		contourSet_bk.clear();
		topContourIndices.clear();
		heirarchy++;
	}

	int pIndex = 0;
	for (int i = 0; i < contourSet.size(); i++)
	{
		for (int j = 0; j < contourSet[i].contour.size(); j++)
		{
			Point3 p ;

			p.point.x = contourSet[i].contour[j].x;
			p.point.y = contourSet[i].contour[j].y;
			p.point.z = 0;

			p.contour = i;
			p.hierarchy = contourSet[i].heirarchy;
			p.index = pIndex;

			points.push_back(p);

			pIndex++;
		}
	}

}


void Image::getPoints() {

	int flagMinX = 0;
	int flagMinY = 0;
	int flagMaxX = 0;
	int flagMaxY = 0;

	int flagX;
	int flagY;
	int index = 0;

	for (int i = 0; i < contours.size(); i++)
	{
		ContourSet contourSetObj;

		std::vector<int> bbPts;
		std::vector<int> flags;


		flagMinX = 0;
		flagMinY = 0;
		flagMaxX = 0;
		flagMaxY = 0;

		flagX = 0;
		flagY = 0;

		
		for (int j = 0; j < contours[i].size(); j++)
		{
			//Check if the contour touch the image boundaries
			if (image.cols - 1 == contours[i][j].x) {
				bbPts.push_back(j);
				flags.push_back(2);
				flagMaxX++;
				flagX = 1;
			}

			if (image.rows - 1 == contours[i][j].y) {
				bbPts.push_back(j);
				flags.push_back(4);
				flagMaxY++;
				flagY = 1;
			}

			if (0 == contours[i][j].x) {
				bbPts.push_back(j);
				flags.push_back(1);
				flagMinX++;
				flagX = 1;
			}

			if (0 == contours[i][j].y) {
				bbPts.push_back(j);
				flags.push_back(3);
				flagMinY++;
				flagY = 1;
			}

		}

		if (!(flagMaxX || flagMaxY || flagMinX || flagMinY))
		{
			contourSetObj.contour = contours[i];
			contourSetObj.index = index++;
			contourSet.push_back(contourSetObj);
		}
		else if (flagMaxX || flagMaxY || flagMinX || flagMinY) {
			
			if (bbPts.size() > 1) {
				int start = 0, end = 0;
				int flag1, flag2;

				for (int k = 0; k < bbPts.size() - 1; k++) {
					
					if (abs(bbPts[k] - bbPts[k + 1]) != 1) {

						start = bbPts[k];
						end = bbPts[k + 1];
						flag1 = flags[k];
						flag2 = flags[k + 1];

						std::vector<cv::Point> vec;

						for (int k = start; k <= end; k++) {
							vec.push_back(contours[i][k]);
						}

						float x, y;

						if (((flag1 == 1 || flag1 == 2) && (flag2 == 3 || flag2 == 4)) ||
							((flag1 == 3 || flag1 == 4) && (flag2 == 1 || flag2 == 2))) {

							if (flag1 == 1) {
								x = 0;
							}
							else if (flag1 == 2) {
								x = image.cols - 1;
							}
							else if (flag1 == 3) {
								y = 0;
							}
							else if (flag1 == 4) {
								y = image.rows - 1;
							}

							if (flag2 == 1) {
								x = 0;
							}
							else if (flag2 == 2) {
								x = image.cols - 1;
							}
							else if (flag2 == 3) {
								y = 0;
							}
							else if (flag2 == 4) {
								y = image.rows - 1;
							}

							vec.push_back(cv::Point(x, y));
						}

						else if ((flag1 == 1 && flag2 == 2) || (flag1 == 3 && flag2 == 4) ||
							(flag1 == 2 && flag2 == 1) || (flag1 == 4 && flag2 == 3)) {

							if (flag1 == 1) {
								vec.push_back(cv::Point(0, image.rows - 1));
								vec.push_back(cv::Point(image.cols - 1, image.rows - 1));
							}
							else if (flag1 == 2) {
								vec.push_back(cv::Point(image.cols - 1, image.rows - 1));
								vec.push_back(cv::Point(0, image.rows - 1));
							}
							if (flag1 == 3) {
								vec.push_back(cv::Point(image.cols - 1, 0));
								vec.push_back(cv::Point(image.cols - 1, image.rows - 1));
							}
							else if (flag1 == 4) {
								vec.push_back(cv::Point(image.cols - 1, image.rows - 1));
								vec.push_back(cv::Point(image.cols - 1, 0));
							}

						}
						contourSetObj.contour = vec;
						contourSetObj.index = index++;
						contourSet.push_back(contourSetObj);

					}
				}
			}
			else 
			{
				contourSetObj.contour = contours[i];
				contourSetObj.index = index++;
				contourSet.push_back(contourSetObj);
			}

		}


	}

	cv::Mat drawing = cv::Mat::zeros(size, CV_8UC3);

	for (int i = 0; i < contourSet.size(); i++)
	{
		for (int j = 0; j < contourSet[i].contour.size(); j++) {

			cv::Vec3b color;
			color[0] = 250;
			color[1] = 250;
			color[2] = 0;

			drawing.at<cv::Vec3b>(cv::Point(contourSet[i].contour[j].x, contourSet[i].contour[j].y)) = color;
		}
	}
	
	cv::imwrite("Edge1.bmp", drawing);

}


