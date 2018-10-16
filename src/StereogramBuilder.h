#ifndef STEREOGRAMBUILDER_H
#define STEREOGRAMBUILDER_H

#include <iostream>
#include <opencv2/opencv.hpp>

#define DEPTH_LAYERS_COUNT 16
#define REPEAT_OFFSET 200

class stereogramBuilder {
 public:
  stereogramBuilder();
  ~stereogramBuilder();

  cv::Mat generateStereogramm(const cv::Mat& texture, const cv::Mat& depthMap);

 private:
  cv::Mat generateBackground(const cv::Mat& texture,
                             const cv::Size& size) const;
};
#endif
