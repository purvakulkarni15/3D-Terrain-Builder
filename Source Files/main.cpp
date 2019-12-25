#include "Generate3DModel.h"

int main()
{
	Generate3DModel generate3DModel = Generate3DModel();
	cv::Mat srcImage = cv::imread("image.bmp", cv::IMREAD_COLOR);

	if (srcImage.empty())
	{
		std::cout << "Could not open file", "Error";
	}
	else
	{
		generate3DModel.image = Image(srcImage);
		generate3DModel.image.srcImage = srcImage;
		generate3DModel.image.getFilteredImage();
		generate3DModel.image.getContours();
		generate3DModel.image.getPoints();
	}

	generate3DModel.populateData();
	generate3DModel.enhanceGrid();
	generate3DModel.createOBJFile();

}
