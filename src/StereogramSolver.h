#ifndef STEREOGRAMSOLVER_H
#define STEREOGRAMSOLVER_H
#include <thread>
#include <mutex>

#include <opencv2\opencv.hpp>

#define MIN_REPEAT_SEGMENTS_COUNT 4
#define MAX_REPEAT_SEGMENTS_COUNT 20
#define MATCH_BLOCKS_WIDTH 10

class stereogramSolver {
public:
	stereogramSolver();
	~stereogramSolver();

	cv::Mat reconstructDepthMap(const cv::Mat& stereogram, int countThreads = 1);
private:
	int findRepeatOffset(const cv::Mat& stereogram) const;
	void reconstructDepthMapPartImg(const cv::Mat partOfStereogram, cv::Mat* outDepthMap, int offset, int threadIndex);

	int m_countThreads;
	std::vector<std::thread*> m_threads;

	mutable std::mutex m_PrintLocker;
};
#endif
