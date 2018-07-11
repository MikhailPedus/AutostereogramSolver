#include "StereogramBuilder.h"
#include "StereogramSolver.h"

int main(int argc, char **argv) {

	cv::Mat texture = cv::imread("d:/stereo/texture/3.jpg", cv::IMREAD_COLOR);
	cv::Mat depthMap = cv::imread("d:/stereo/depth/1.jpg", cv::IMREAD_GRAYSCALE);

	stereogramBuilder builder;

	std::cout << "Generate stereogramm" << std::endl;
	cv::Mat stereogramm = builder.generateStereogramm(texture, depthMap);
	cv::imshow("stereogramm", stereogramm);
	cv::waitKey(0);

//	cv::Mat stereogramm = cv::imread("d:/stereo/8.png", cv::IMREAD_COLOR);

	stereogramSolver solver;

	std::cout << "Decompose stereogramm" << std::endl;
	cv::Mat mask = solver.reconstructDepthMap(stereogramm, 12);
	cv::imshow("reconstructDepth", mask);
	cv::waitKey(0);
	

	return 0;
}
