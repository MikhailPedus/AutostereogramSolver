#include <iostream>
#include <opencv2/opencv.hpp>

static void help() {
        printf("\nThis is a points cloud 3d displayer.\n"
                "Usage: pointsCloudDisplayer\n"
                "		-c=<path>			# the path to point cloud storage in *.ply format\n"
                "\n");
}

int main(int argc, char **argv) {

#ifdef OPENCV_VIZCORE_HPP
    
	std::string pointsCloudStoragePath("outSolverCloud.ply");

    for (int i = 1; i < argc; i++)
	{
		const char* s = argv[i];
		if (strcmp(s, "-c") == 0) {
			pointsCloudStoragePath = argv[++i];
		}
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
#else
	std::cout << "Your opencv version compiled without viz module. Please rebuild opencv with vtk and try again.";
#endif
    return 0;
}
