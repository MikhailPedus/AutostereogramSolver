#include "StereogramSolver.h"
#include "gtest/gtest.h"

TEST(StereogramSolver, SolveStereogramOneThreadGray) {
  std::string stereogramPath("../stereogram/shark.jpg");
  int threadsCount = 1;
  std::string saveResultPath("outSolverDepthMap.jpg");
  std::string savePointsCloudPath("outSolverCloud.ply");
  bool LOAD_GRAYSCALE = true;

  cv::Mat stereogram = cv::imread(
      stereogramPath, LOAD_GRAYSCALE ? cv::IMREAD_GRAYSCALE : cv::IMREAD_COLOR);
  if (stereogram.empty()) {
    std::cout << "ERROR. Cannot load stereogram image by path:"
              << stereogramPath << std::endl;
    FAIL();
  }

  stereogramSolver solver;

  std::cout << "Start Solve stereogramm..." << std::endl;
  cv::Mat depthMap = solver.reconstructDepthMap(stereogram, threadsCount);
  if (depthMap.empty()) {
    std::cout << "ERROR. Result depth map is empty. Something Wrong..."
              << std::endl;
    FAIL();
  } else {
    std::cout << "Success!!" << std::endl;
#if (defined __OPENCV_VIZ_HPP__ || defined OPENCV_VIZ_HPP || defined HAVE_OPENCV_VIZ)
    std::vector<cv::Point3f> points = convertMatToPointsCloud(depthMap);
    ASSERT_TRUE(points.size() > 0);
#else
    std::cout << "Can not generate file:" << savePointsCloudPath
              << " because your opencv version compiled without viz module. "
                 "Please rebuild opencv with vtk and try again."
              << std::endl;
    FAIL();
#endif
  }
};

TEST(StereogramSolver, SolveStereogramOneThreadColor) {
  std::string stereogramPath("../stereogram/shark.jpg");
  int threadsCount = 1;
  std::string saveResultPath("outSolverDepthMap.jpg");
  std::string savePointsCloudPath("outSolverCloud.ply");
  bool LOAD_GRAYSCALE = false;

  cv::Mat stereogram = cv::imread(
      stereogramPath, LOAD_GRAYSCALE ? cv::IMREAD_GRAYSCALE : cv::IMREAD_COLOR);
  if (stereogram.empty()) {
    std::cout << "ERROR. Cannot load stereogram image by path:"
              << stereogramPath << std::endl;
    FAIL();
  }

  stereogramSolver solver;

  std::cout << "Start Solve stereogramm..." << std::endl;
  cv::Mat depthMap = solver.reconstructDepthMap(stereogram, threadsCount);
  if (depthMap.empty()) {
    std::cout << "ERROR. Result depth map is empty. Something Wrong..."
              << std::endl;
    FAIL();
  } else {
    std::cout << "Success!!" << std::endl;
#if (defined __OPENCV_VIZ_HPP__ || defined OPENCV_VIZ_HPP || defined HAVE_OPENCV_VIZ)
    std::vector<cv::Point3f> points = convertMatToPointsCloud(depthMap);
    ASSERT_TRUE(points.size() > 0);
#else
    std::cout << "Can not generate file:" << savePointsCloudPath
              << " because your opencv version compiled without viz module. "
                 "Please rebuild opencv with vtk and try again."
              << std::endl;
    FAIL();
#endif
  }
};

TEST(StereogramSolver, SolveStereogramFourThreadsGray) {
  std::string stereogramPath("../stereogram/shark.jpg");
  int threadsCount = 4;
  std::string saveResultPath("outSolverDepthMap.jpg");
  std::string savePointsCloudPath("outSolverCloud.ply");
  bool LOAD_GRAYSCALE = true;

  cv::Mat stereogram = cv::imread(
      stereogramPath, LOAD_GRAYSCALE ? cv::IMREAD_GRAYSCALE : cv::IMREAD_COLOR);
  if (stereogram.empty()) {
    std::cout << "ERROR. Cannot load stereogram image by path:"
              << stereogramPath << std::endl;
    FAIL();
  }

  stereogramSolver solver;

  std::cout << "Start Solve stereogramm..." << std::endl;
  cv::Mat depthMap = solver.reconstructDepthMap(stereogram, threadsCount);
  if (depthMap.empty()) {
    std::cout << "ERROR. Result depth map is empty. Something Wrong..."
              << std::endl;
    FAIL();
  } else {
    std::cout << "Success!!" << std::endl;
#if (defined __OPENCV_VIZ_HPP__ || defined OPENCV_VIZ_HPP || defined HAVE_OPENCV_VIZ)
    std::vector<cv::Point3f> points = convertMatToPointsCloud(depthMap);
    ASSERT_TRUE(points.size() > 0);
#else
    std::cout << "Can not generate file:" << savePointsCloudPath
              << " because your opencv version compiled without viz module. "
                 "Please rebuild opencv with vtk and try again."
              << std::endl;
    FAIL();
#endif
  }
};

TEST(StereogramSolver, SolveStereogramFourThreadsColor) {
  std::string stereogramPath("../stereogram/shark.jpg");
  int threadsCount = 4;
  std::string saveResultPath("outSolverDepthMap.jpg");
  std::string savePointsCloudPath("outSolverCloud.ply");
  bool LOAD_GRAYSCALE = false;

  cv::Mat stereogram = cv::imread(
      stereogramPath, LOAD_GRAYSCALE ? cv::IMREAD_GRAYSCALE : cv::IMREAD_COLOR);
  if (stereogram.empty()) {
    std::cout << "ERROR. Cannot load stereogram image by path:"
              << stereogramPath << std::endl;
    FAIL();
  }

  stereogramSolver solver;

  std::cout << "Start Solve stereogramm..." << std::endl;
  cv::Mat depthMap = solver.reconstructDepthMap(stereogram, threadsCount);
  if (depthMap.empty()) {
    std::cout << "ERROR. Result depth map is empty. Something Wrong..."
              << std::endl;
    FAIL();
  } else {
    std::cout << "Success!!" << std::endl;
#if (defined __OPENCV_VIZ_HPP__ || defined OPENCV_VIZ_HPP || defined HAVE_OPENCV_VIZ)
    std::vector<cv::Point3f> points = convertMatToPointsCloud(depthMap);
    ASSERT_TRUE(points.size() > 0);
#else
    std::cout << "Can not generate file:" << savePointsCloudPath
              << " because your opencv version compiled without viz module. "
                 "Please rebuild opencv with vtk and try again."
              << std::endl;
    FAIL();
#endif
  }
};
int main(int argc,char**argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
