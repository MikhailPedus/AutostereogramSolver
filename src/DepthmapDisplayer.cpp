#include "DepthmapDisplayer.h"

#define DISPLAY_WINDOW 1000

//camera position
double angleX = 0, angleXtmp = 0;
double angleY = 0, angleYtmp = 0;
double angleZ = 0, angleZtmp = 0;

cv::Point rightClockPos;
bool moveInProgress = false;

std::vector<cv::Point3f> pointsCloud;
cv::Mat display3DMat(DISPLAY_WINDOW, DISPLAY_WINDOW, CV_8UC3, cv::Scalar::all(0));

depthMapDisplayer::depthMapDisplayer() {
	std::cout << "depthMapDisplayer::depthMapDisplayer() " << this << std::endl;

	cv::namedWindow("DepthmapDisplayer", 1);
	//set the callback function for any mouse event
	cv::setMouseCallback("DepthmapDisplayer", CallBackFunc, NULL);
}

depthMapDisplayer::~depthMapDisplayer() {
	std::cout << "depthMapDisplayer::~depthMapDisplayer() " << this << std::endl;
}

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
	if (event == cv::EVENT_LBUTTONDOWN)
	{
		//std::cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << std::endl;
		moveInProgress = true;
		rightClockPos.x = x;
		rightClockPos.y = y;
	}
	else if (event == cv::EVENT_LBUTTONUP)
	{
		//std::cout << "Left button of the mouse is released - position (" << x << ", " << y << ")" << std::endl;
		moveInProgress = false;
		angleX = angleXtmp;
		angleY = angleYtmp;

		std::vector<cv::Point3f> rotatedPointsCloud = apply_rotate_matrix(angleXtmp, angleYtmp, angleZtmp, pointsCloud, 1);
		display3DMat.setTo(0);
		for (int i = 0; i < rotatedPointsCloud.size(); i++) {
			cv::circle(display3DMat,
				cv::Point(static_cast<float>(rotatedPointsCloud[i].x + DISPLAY_WINDOW / 2), static_cast<float>(rotatedPointsCloud[i].y + DISPLAY_WINDOW / 2)),
				1,
				cv::Scalar(0, pointsCloud[i].z, 0));
		}
		cv::imshow("DepthmapDisplayer", display3DMat);
	}
	else if (event == cv::EVENT_MOUSEMOVE)
	{
		if (moveInProgress) {
			//std::cout << "Mouse move over the window - position (" << x << ", " << y << ")" << std::endl;
			
			int xDiff = x - rightClockPos.x;
			int yDiff = y - rightClockPos.y;

			if (xDiff || yDiff) {
				angleXtmp = angleX + double(xDiff) * 0.01;
				angleYtmp = angleY + double(yDiff) * 0.01;

				std::vector<cv::Point3f> rotatedPointsCloud = apply_rotate_matrix(angleXtmp, angleYtmp, angleZtmp, pointsCloud, pointsCloud.size()/200);
				display3DMat.setTo(0);
				for (int i = 0; i < rotatedPointsCloud.size(); i++) {
					cv::circle(display3DMat,
						cv::Point(static_cast<float>(rotatedPointsCloud[i].x + DISPLAY_WINDOW / 2), static_cast<float>(rotatedPointsCloud[i].y + DISPLAY_WINDOW / 2)),
						1,
						cv::Scalar(0, pointsCloud[i].z, 0));
				}
				cv::imshow("DepthmapDisplayer", display3DMat);
			}
		}
	}
	else if (event == cv::EVENT_RBUTTONDOWN)
	{
		angleX = 0;
		angleY = 0;

		std::vector<cv::Point3f> rotatedPointsCloud = apply_rotate_matrix(angleX, angleY, angleZ, pointsCloud, 1);
		display3DMat.setTo(0);
		for (int i = 0; i < rotatedPointsCloud.size(); i++) {
			cv::circle(display3DMat,
				cv::Point(static_cast<float>(rotatedPointsCloud[i].x + DISPLAY_WINDOW / 2), static_cast<float>(rotatedPointsCloud[i].y + DISPLAY_WINDOW / 2)),
				1,
				cv::Scalar(0, pointsCloud[i].z, 0));
		}
		cv::imshow("DepthmapDisplayer", display3DMat);
	}
}

void depthMapDisplayer::display3D(const cv::Mat& depthMap) {
	pointsCloud = convertMatToPointsCloud(depthMap);
	
	std::vector<cv::Point3f> rotatedPointsCloud = apply_rotate_matrix(angleX, angleY, angleZ, pointsCloud, 1);
	display3DMat.setTo(0);
	for (int i = 0; i < rotatedPointsCloud.size(); i++) {
		cv::circle(display3DMat,
			cv::Point(static_cast<float>(rotatedPointsCloud[i].x + DISPLAY_WINDOW/2), static_cast<float>(rotatedPointsCloud[i].y + DISPLAY_WINDOW/2)), 
			1,
			cv::Scalar(0, pointsCloud[i].z, 0));
	}
	cv::imshow("DepthmapDisplayer", display3DMat);
	cv::waitKey(0);
}
void depthMapDisplayer::processKey(int key) {
	double k = 180; //coeff each rotation step. big k - slow rotation. small k - fast rotation
	switch (key) {
	case 55:
		//down
		std::cout<< "Rotate x coordinate" << std::endl;
		angleX -= CV_PI / k;
		std::cout << "Current angle" << angleX << angleY << angleZ << std::endl;
		break;
	case 56:
		//up
		std::cout << "Rotate x coordinate" << std::endl;
		angleX += CV_PI / k;
		std::cout << "Current angle" << angleX << angleY << angleZ << std::endl;
		break;
	case 52:
		std::cout << "Rotate y coordinate" << std::endl;
		angleY -= CV_PI / k;
		std::cout << "Current angle" << angleX << angleY << angleZ << std::endl;
		break;
	case 53:
		std::cout << "Rotate y coordinate" << std::endl;
		angleY += CV_PI / k;
		std::cout << "Current angle" << angleX << angleY << angleZ << std::endl;
		break;
	case 49:
		//left
		std::cout << "Rotate z coordinate" << std::endl;
		angleZ -= CV_PI / k;
		std::cout << "Current angle" << angleX << angleY << angleZ << std::endl;
		break;
	case 50:
		//right
		std::cout << "Rotate z coordinate" << std::endl;
		angleZ += CV_PI / k;
		std::cout << "Current angle" << angleX << angleY << angleZ << std::endl;
		break;
	case 32:
		//space
		std::cout << "clear rotate" << std::endl;
		angleX = 0;
		angleY = 0;
		angleZ = 0;
		std::cout << "Current angle" << angleX << " " << " " << angleY << " " << angleZ << std::endl;
		break;
	default: std::cout << "pressed key" << key <<std::endl; break;
	}
}

std::vector<cv::Point3f> convertMatToPointsCloud(const cv::Mat& img) {
	std::vector<cv::Point3f> outArray;
	for (int r = 0; r < img.rows; ++r) {
		for (int c = 0; c < img.cols; ++c) {
			if (img.at<unsigned char>(r, c) > 2) {
				outArray.push_back(cv::Point3f(img.cols/2 - c, img.rows / 2 - r, img.at<unsigned char>(r, c)));
			}
		}
	}
	return outArray;
}

std::vector<cv::Point3f> apply_rotate_matrix(double x, double y, double z, const std::vector<cv::Point3f> &sourcePoints, int step) {

	std::cout << "step:" << step << std::endl;

	std::vector<cv::Point3f> out;

	cv::Mat rotateX(3, 3, CV_32FC1);
	cv::Mat rotateY(3, 3, CV_32FC1);
	cv::Mat rotateZ(3, 3, CV_32FC1);

	rotateX.at<float>(0, 0) = 1; rotateX.at<float>(0, 1) = 0; rotateX.at<float>(0, 2) = 0;
	rotateX.at<float>(1, 0) = 0; rotateX.at<float>(1, 1) = cos(x); rotateX.at<float>(1, 2) = sin(x) * (-1);
	rotateX.at<float>(2, 0) = 0; rotateX.at<float>(2, 1) = sin(x); rotateX.at<float>(2, 2) = cos(x);

	rotateY.at<float>(0, 0) = cos(y); rotateY.at<float>(0, 1) = 0; rotateY.at<float>(0, 2) = sin(y);
	rotateY.at<float>(1, 0) = 0;      rotateY.at<float>(1, 1) = 1; rotateY.at<float>(1, 2) = 0;
	rotateY.at<float>(2, 0) = sin(y) * (-1); rotateY.at<float>(2, 1) = 0; rotateY.at<float>(2, 2) = cos(y);

	rotateZ.at<float>(0, 0) = cos(z); rotateZ.at<float>(0, 1) = sin(z)*(-1); rotateZ.at<float>(0, 2) = 0;
	rotateZ.at<float>(1, 0) = sin(z); rotateZ.at<float>(1, 1) = cos(z); rotateZ.at<float>(1, 2) = 0;
	rotateZ.at<float>(2, 0) = 0; rotateZ.at<float>(2, 1) = 0; rotateZ.at<float>(2, 2) = 1;

	cv::Mat pointInMat(3, sourcePoints.size(), CV_32FC1);

	for (size_t i = 0; i < sourcePoints.size(); i+=step) {
		pointInMat.at<float>(0, i) = sourcePoints[i].x;
		pointInMat.at<float>(1, i) = sourcePoints[i].y;
		pointInMat.at<float>(2, i) = sourcePoints[i].z;
	}
	cv::Mat tempXRotate, tempXYRotate, tempXYZRotate;

	cv::gemm(rotateX, pointInMat, 1, cv::noArray(), 0, tempXRotate);
	cv::gemm(rotateY, tempXRotate, 1, cv::noArray(), 0, tempXYRotate);
	cv::gemm(rotateZ, tempXYRotate, 1, cv::noArray(), 0, tempXYZRotate);

	for (int i = 0; i < tempXYZRotate.cols; i++) {
		out.push_back(cv::Point3f(tempXYZRotate.at<float>(0, i), tempXYZRotate.at<float>(1, i), tempXYZRotate.at<float>(2, i)));
	}
	return out;
}
