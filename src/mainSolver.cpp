#include "StereogramSolver.h"
static void help() {
	printf("\nThis is a autostereogram solver.\n"
		"Usage: stereogramBuilder\n"
		"		-s=<path>			# the path to stereogram image\n"
		"		[-t=<threadsCount>]		# the number of threads for faster multithread processing. Value by default:2\n"
		"		[-o=<path>]			# the path to save result image\n"
		"		[-g]				# load stereogram image as GRAYSCALE\n"
		"\n");
}

int main(int argc, char **argv) {

	cv::CommandLineParser parser(argc, argv,
		"{help||}{s||}{t|2|}{o|outSolver.jpg|}{g||}");

	if (parser.has("help")) {
		help();
		return 0;
	}
	std::string stereogramPath = parser.get<std::string>("s");
	int threadsCount = parser.get<int>("t");
	std::string saveResultPath = parser.get<std::string>("o");
	bool LOAD_GRAYSCALSE = false;
	if (parser.has("g")) LOAD_GRAYSCALSE = true;

	if (!parser.check()) {
		help();
		parser.printErrors();
		return -1;
	}

	cv::Mat stereogram = cv::imread(stereogramPath, cv::IMREAD_COLOR);
	if (stereogram.empty()) {
		std::cout << "ERROR. Cannot load stereogram image by path:" << stereogramPath << std::endl;
		help();
		return -1;
	}

	stereogramSolver solver;

	std::cout << "Start Solve stereogramm..." << std::endl;
	cv::Mat depthMask = solver.reconstructDepthMap(stereogram, threadsCount);
	if (depthMask.empty()) {
		std::cout << "ERROR. Result stereogramm is empty. Something Wrong..." << std::endl;
		help();
		return -1;
	}
	else {
		std::cout << "Success!!" << std::endl;
	}
	
	try {
		cv::imwrite(saveResultPath, depthMask);
	}
	catch (cv::Exception& e) {
		std::cout << "ERROR. Cannot save result depth map by path:" << saveResultPath << "\n" << e.what() << std::endl;
		help();
		return -1;
	}
	return 0;
}
