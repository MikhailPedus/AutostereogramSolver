#include "DepthmapDisplayer.h"

static void help() {
	printf("\nThis is a depth map 3d displayer builder.\n"
		"Usage: depthmapDisplayer\n"
		"		-d=<path>			# the path to depth map image\n"
		"\n");
}

int main(int argc, char **argv) {

	cv::CommandLineParser parser(argc, argv,
		"{help||}{d||}");

	if (parser.has("help")) {
		help();
		return 0;
	}
	std::string depthMapPath = parser.get<std::string>("d");

	if (!parser.check()) {
		help();
		parser.printErrors();
		return -1;
	}

	cv::Mat depthMap = cv::imread(depthMapPath, cv::IMREAD_GRAYSCALE);
	if (depthMap.empty()) {
		std::cout << "ERROR. Cannot load depth map image by path:" << depthMapPath << std::endl;
		help();
		return -1;
	}

	depthMapDisplayer displayer;

	std::cout << "Start display process..." << std::endl;
	displayer.display3D(depthMap);

	return 0;
}
