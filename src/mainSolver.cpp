#include "StereogramSolver.h"
static void help() {
	printf("\nThis is a autostereogram solver.\n"
		"Usage: stereogramSolver\n"
		"		-s=<path>			# the path to stereogram image\n"
		"		[-t=<threadsCount>]		# the number of threads for faster multithread processing. Value by default:2\n"
		"		[-od=<path>]			# the path to save result depth map image\n"
		"		[-oc=<path>]			# the path to save result points cloud storage\n"
		"		[-g]				# load stereogram image as GRAYSCALE\n"
		"\n");
}

std::vector<cv::Point3f> convertMatToPointsCloud(const cv::Mat& img) {
        
        std::vector<cv::Point3f> outArray;
        if(img.type() == CV_8UC1) {
            for (int r = 0; r < img.rows; ++r) {
                for (int c = 0; c < img.cols; ++c) {
                    if(img.at<unsigned char>(r, c) > 5) {
                        outArray.push_back(cv::Point3f(r, c, img.at<unsigned char>(r, c)));
                    }
                }
            }
        } else {
            std::cout<< "std::vector<cv::Point3f> convertMatToPointsCloud(const cv::Mat& img) need CV_8UC1 mat as input. Current type is:" << img.type() <<std::endl;
        }
        return outArray;
}
int main(int argc, char **argv) {

	cv::CommandLineParser parser(argc, argv,
		"{help||}{s||}{t|2|}{od|outSolverDepthMap.jpg|}{oc|outSolverCloud.ply|}{g||}");

	if (parser.has("help")) {
		help();
		return 0;
	}
	std::string stereogramPath = parser.get<std::string>("s");
	int threadsCount = parser.get<int>("t");
	std::string saveResultPath = parser.get<std::string>("od");
	std::string savePointsCloudPath = parser.get<std::string>("oc");
	bool LOAD_GRAYSCALE = false;
	if (parser.has("g")) LOAD_GRAYSCALE = true;

	if (!parser.check()) {
		help();
		parser.printErrors();
		return -1;
	}

	cv::Mat stereogram = cv::imread(stereogramPath, LOAD_GRAYSCALE ? cv::IMREAD_GRAYSCALE : cv::IMREAD_COLOR);
	if (stereogram.empty()) {
		std::cout << "ERROR. Cannot load stereogram image by path:" << stereogramPath << std::endl;
		help();
		return -1;
	}

	stereogramSolver solver;

	std::cout << "Start Solve stereogramm..." << std::endl;
	cv::Mat depthMap = solver.reconstructDepthMap(stereogram, threadsCount);
	if (depthMap.empty()) {
		std::cout << "ERROR. Result depth map is empty. Something Wrong..." << std::endl;
		help();
		return -1;
	}
	else {
		std::cout << "Success!!" << std::endl;
		std::vector<cv::Point3f> points = convertMatToPointsCloud(depthMap);
#ifdef OPENCV_VIZCORE_HPP
		cv::viz::writeCloud(savePointsCloudPath, points);
		std::cout << "Generate file:" << savePointsCloudPath << std::endl;
#else
		std::cout << "Can not generate file:" << savePointsCloudPath << 
			" because your opencv version compiled without viz module. Please rebuild opencv with vtk and try again." << std::endl;
#endif
	}
	try {
		cv::imwrite(saveResultPath, depthMap);
	}
	catch (cv::Exception& e) {
		std::cout << "ERROR. Cannot save result depth map by path:" << saveResultPath << "\n" << e.what() << std::endl;
		help();
		return -1;
	}
	std::cout<< "Generate file:" << saveResultPath <<std::endl;
	return 0;
}
