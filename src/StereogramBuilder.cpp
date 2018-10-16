#include "StereogramBuilder.h"

stereogramBuilder::stereogramBuilder() {
  std::cout << "stereogramBuilder::stereogramBuilder() " << this << std::endl;
}

stereogramBuilder::~stereogramBuilder() {
  std::cout << "stereogramBuilder::~stereogramBuilder() " << this << std::endl;
}

cv::Mat stereogramBuilder::generateBackground(const cv::Mat& texture,
                                              const cv::Size& size) const {
  cv::Mat background(size, texture.type());
  // produce background image, using input texture.
  for (int r = 0; r < background.rows; r += texture.rows) {
    for (int c = 0; c < background.cols; c += texture.cols) {
      // check and reduce fill area, if go outside the image borders
      int copyWidth = c + texture.cols < background.cols
                          ? texture.cols
                          : background.cols - c - 1;
      int copyHeight = r + texture.rows < background.rows
                           ? texture.rows
                           : background.rows - r - 1;

      texture(cv::Rect(0, 0, copyWidth, copyHeight))
          .copyTo(background(cv::Rect(c, r, copyWidth, copyHeight)));
    }
  }
  return background;
}

// generate autostereogramm
cv::Mat stereogramBuilder::generateStereogramm(const cv::Mat& texture,
                                               const cv::Mat& depthMap) {
  cv::Mat textureResized;
  cv::resize(texture, textureResized, cv::Size(REPEAT_OFFSET, REPEAT_OFFSET));

  int s = textureResized.cols;  // texture horizontal repeat interval

  cv::Mat background = generateBackground(
      textureResized,
      cv::Size(depthMap.cols + textureResized.cols, depthMap.rows));

  int nChannel =
      background.channels();  // background consist same type and same number of
                              // channel like input texture

  depthMap /= DEPTH_LAYERS_COUNT;
  for (int r = 0; r < depthMap.rows; ++r) {
    for (int c = 0; c < depthMap.cols; ++c) {
      if (depthMap.at<unsigned char>(r, c) > 0) {
        for (int nChannel = 0; nChannel < background.channels(); ++nChannel) {
          unsigned char pixel = background.at<unsigned char>(
              r,
              (c + depthMap.at<unsigned char>(r, c)) * background.channels() +
                  nChannel);
          for (int i = c + s; i < depthMap.cols + s; i += s)
            background.at<unsigned char>(
                r, i * background.channels() + nChannel) = pixel;
        }
      }
    }
  }
  return background;
}