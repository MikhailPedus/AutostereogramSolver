#include "StereogramBuilder.h"

static void help() {
	printf("\nThis is a autostereogram builder.\n"
		"Usage: stereogramBuilder\n"
		"		-t=<path>			# the path to texture image\n"
		"		-d=<path>			# the path to depth map image\n"
		"		[-o=<path>]			# the path to save result image\n"
		"		[-g]				# load texture image as GRAYSCALE\n"
		"\n");
}

int main(int argc, char **argv) {

	cv::CommandLineParser parser(argc, argv,
		"{help||}{t||}{d||}{o|outBuilder.jpg|}{g||}");

	if (parser.has("help")) {
		help();
		return 0;
	}
	std::string texturePath = parser.get<std::string>("t");
	std::string depthMapPath = parser.get<std::string>("d");
	std::string saveResultPath = parser.get<std::string>("o");
	bool LOAD_GRAYSCALSE = false;
	if (parser.has("g")) LOAD_GRAYSCALSE = true;
	
	if (!parser.check()) {
		help();
		parser.printErrors();
		return -1;
	}

	cv::Mat texture = cv::imread(texturePath, LOAD_GRAYSCALSE ? cv::IMREAD_GRAYSCALE : cv::IMREAD_COLOR);
	if (texture.empty()) {
		std::cout << "ERROR. Cannot load texture image by path:" << texturePath << std::endl;
		help();
		return -1;
	}
	cv::Mat depthMap = cv::imread(depthMapPath, cv::IMREAD_GRAYSCALE);
	if (depthMap.empty()) {
		std::cout << "ERROR. Cannot load depth map image by path:" << depthMapPath << std::endl;
		help();
		return -1;
	}

	stereogramBuilder builder;
	
	std::cout << "Start generate stereogramm process..." << std::endl;
	cv::Mat stereogram = builder.generateStereogramm(texture, depthMap);
	if (stereogram.empty()) {
		std::cout << "ERROR. Result stereogramm is empty. Something Wrong..." << std::endl;
		help();
		return -1;
	}
	else {
		std::cout << "Success!!" << std::endl;
	}

	try {
		cv::imwrite(saveResultPath, stereogram);
	}
	catch (cv::Exception& e) {
		std::cout << "ERROR. Cannot save result stereo image by path:" << saveResultPath << "\n" << e.what() << std::endl;
		help();
		return -1;
	}

	return 0;
}
