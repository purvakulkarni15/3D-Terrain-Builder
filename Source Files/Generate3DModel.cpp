#include "Generate3DModel.h"



Generate3DModel::Generate3DModel()
{
}


Generate3DModel::~Generate3DModel()
{
}

void Generate3DModel::populateData()
{

	this->size = image.srcImage.size();
	this->rect = cv::Rect(0, 0, size.width, size.height);
	this->index = 0;

	mat = (Point3*)malloc(sizeof(Point3)* size.width * size.height);

	for (int i = 0; i < image.points.size(); i++)
	{
		int col = image.points[i].point.x;
		int row = image.points[i].point.y;

		mat[row*size.width + col] = image.points[i];
		mat[row*size.width + col].index = index;

		index++;
	}

	for (int i = 0; i < image.points.size(); i++)
	{
		points2D.push_back(cv::Point2f(image.points[i].point.x, image.points[i].point.y));
	}

}

cv::Subdiv2D Generate3DModel::delaunayTriangulation()
{
	cv::Subdiv2D subdiv(rect);

	for (std::vector<cv::Point2f>::iterator it = points2D.begin(); it != points2D.end(); it++)
	{
		subdiv.insert(*it);
	}

	return subdiv;
}


void Generate3DModel::enhanceGrid()
{
	std::vector<cv::Vec4f> edgeList;

	delaunayTriangulation().getEdgeList(edgeList);

	std::vector<cv::Point> pt(3);

	for (int i = 0; i < edgeList.size(); i++) {

		cv::Vec4f e = edgeList[i];
		pt[0] = cv::Point(cvRound(e[0]), cvRound(e[1]));
		pt[1] = cv::Point(cvRound(e[2]), cvRound(e[3]));

		int w1 = pt[0].x;
		int w2 = pt[1].x;

		int h1 = pt[0].y;
		int h2 = pt[1].y;

		if (abs(w1) < size.width && abs(h1) < size.height && abs(w2) < size.width && abs(h2) < size.height)
		{

			Point3 p1 = mat[h1 * size.width + w1];
			Point3 p2 = mat[h2 * size.width + w2];

			if (p1.hierarchy == p2.hierarchy && p1.contour != p2.contour) {

				int x = (p1.point.x + p2.point.x) / 2;
				int y = (p1.point.y + p2.point.y) / 2;

				mat[y * size.width + x].point.x = x;
				mat[y * size.width + x].point.y = y;
				mat[y * size.width + x].hierarchy = p1.hierarchy - 0.5;
				mat[y * size.width + x].index = index;

				cv::Point2f pt = cv::Point2f(x, y);
				points2D.push_back(pt);
				image.points.push_back(mat[y * size.width + x]);

				index++;

			}

			if (p1.contour == p2.contour) {

				int x = (p1.point.x + p2.point.x) / 2;
				int y = (p1.point.y + p2.point.y) / 2;

				cv::Point2f pt = cv::Point2f(x, y);

				if (cv::pointPolygonTest(image.contours[p1.contour], pt, true) < -5.0)
				{
					mat[y * size.width + x].point.x = x;
					mat[y * size.width + x].point.y = y;
					mat[y * size.width + x].hierarchy = p1.hierarchy - 0.5;
					mat[y * size.width + x].index = index;

					points2D.push_back(pt);
					image.points.push_back(mat[y * size.width + x]);

					index++;

				}
				else if (cv::pointPolygonTest(image.contours[p1.contour], pt, true) > 5.0)
				{
					mat[y * size.width + x].point.x = x;
					mat[y * size.width + x].point.y = y;
					mat[y * size.width + x].hierarchy = p1.hierarchy + 0.5;
					mat[y * size.width + x].index = index;

					points2D.push_back(pt);
					image.points.push_back(mat[y * size.width + x]);

					index++;

				}

			}
		}

	}
}

void Generate3DModel::createOBJFile()
{
	std::vector<cv::Vec6f> triangleList;
	delaunayTriangulation().getTriangleList(triangleList);
	std::vector<cv::Point> pt(3);

	FILE* fp = fopen("File.obj", "w");

	for (int i = 0; i < image.points.size(); i++)
	{
		float z = (float)image.points[i].hierarchy * 10.0;
		//float z = 0;
		fprintf(fp, "v %f %f %f\n", image.points[i].point.x, image.points[i].point.y, z);
	}


	for (int i = 0; i < triangleList.size(); i++) {

		cv::Vec6f t = triangleList[i];
		pt[0] = cv::Point(cvRound(t[0]), cvRound(t[1]));
		pt[1] = cv::Point(cvRound(t[2]), cvRound(t[3]));
		pt[2] = cv::Point(cvRound(t[4]), cvRound(t[5]));

		int w1 = pt[0].x;
		int w2 = pt[1].x;
		int w3 = pt[2].x;

		int h1 = pt[0].y;
		int h2 = pt[1].y;
		int h3 = pt[2].y;

		int index1 = mat[h1 * size.width + w1].index + 1;
		int index2 = mat[h2 * size.width + w2].index + 1;
		int index3 = mat[h3 * size.width + w3].index + 1;

		fprintf(fp, "f %d %d %d\n", index1, index2, index3);
	}

	fclose(fp);
}
