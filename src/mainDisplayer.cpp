#include <iostream>
#include <opencv2/opencv.hpp>

static void help() {
        printf("\nThis is a points cloud 3d displayer.\n"
                "Usage: pointsCloudDisplayer\n"
                "		-c=<path>			# the path to point cloud storage in *.ply format\n"
                "\n");
}

int main(int argc, char **argv) {

    cv::CommandLineParser parser(argc, argv,
            "{help||}{c||}");

    if (parser.has("help")) {
            help();
            return 0;
    }
    std::string pointsCloudStoragePath = parser.get<std::string>("c");

    if (!parser.check()) {
            help();
            parser.printErrors();
            return -1;
    }

    cv::Mat points;
    try {
        points = cv::viz::readCloud(pointsCloudStoragePath);
    } catch(cv::Exception& e) {
        std::cout<< e.what() <<std::endl;
    }

    if (points.empty()) {
        std::cout << "ERROR. Cannot load point cloud storage by path:" << pointsCloudStoragePath << std::endl;
        help();
        return -1;
    }
    cv::viz::Viz3d myWindow("pointsCloudDisplayer");

    myWindow.showWidget("pointsCloudDisplayer",  cv::viz::WPaintedCloud(points));

    myWindow.spin();

    return 0;
}
