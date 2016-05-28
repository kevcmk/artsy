#include "opencv2/opencv.hpp"
#include <string>
#include <chrono>




using namespace cv;


Mat ubbles(Mat & img, int scale) {

	double fx = scale;
	double fy = scale;
	Mat down;
	resize(img, down, Size(), 1/fx, 1/fy, INTER_LINEAR);

	Mat ubbles = Mat::zeros(img.rows, img.cols, img.type());

	int maxradius = (int) (fx / 2);
	int colstep = (int) (1.0 * fx);
	int rowstep = (int) (1.0 * fy);
	// int thickness = -1; // Negative thickness is a filled circle

	for (int i = 0; i < down.cols; i++) {
		for (int j = 0; j < down.rows; j++) {
            CvPoint point = cvPoint(i * colstep + maxradius, j * rowstep + maxradius);
            CvPoint downPoint = cvPoint(i,j);
            Vec3b bgr = down.at<Vec3b>(downPoint);
            int b = bgr[0];
            int g = bgr[1];
            int r = bgr[2];
			CvScalar color = Scalar(b,g,r);
            double average = (b + g + r) / 3.0;
            int radius = (maxradius) * (average / 255);
			// std::cout << "Point: " << point.x << " " << point.y << std::endl;
			// std::cout << "Color: " << color.val << std::endl;
			circle(ubbles, point, radius, color, -1);
		}
	}

	return ubbles;

}

unsigned long long int get_ms() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}


int main(int argc, char * argv[]) {


	VideoCapture cap(0);
	if (!cap.isOpened()) {
		std::cout << "Failed to open webcam." << std::endl;
		return -1;	
	}
	namedWindow("Bubbles", 1);

	
	Mat img;
    unsigned long long int ms;

	for (int frame = 0; frame < 500; frame++) {
        ms = get_ms();
		cap >> img;
		imshow("Ubbles", ubbles(img, 10));

        std::cout << get_ms() - ms << std::endl;
		if (waitKey(16) >= 0) { break; }
	}

	return 0;

}

