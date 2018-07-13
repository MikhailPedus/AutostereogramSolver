#ifndef DEPTHMAPDISPLAYER_H
#define DEPTHMAPDISPLAYER_H

#include <opencv2/opencv.hpp>

void CallBackFunc(int event, int x, int y, int flags, void* userdata);
std::vector<cv::Point3f> convertMatToPointsCloud(const cv::Mat& img);
std::vector<cv::Point3f> apply_rotate_matrix(double x, double y, double z, const std::vector<cv::Point3f> &sourcePoints, int step);

class depthMapDisplayer {
public:
	depthMapDisplayer();
	~depthMapDisplayer();

	void display3D(const cv::Mat& depthMap);
private:
	void processKey(int key);
};
#endif
