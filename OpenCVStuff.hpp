//#pragma once
//
//#include <opencv2/core/core.hpp>
//#include <opencv2/core/types.hpp>
//#include <opencv2/imgproc.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <iostream>
//
//#define PBSTR "||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||"
//#define PBWIDTH 60
//
//
//
//
//void printProgress(double x, double y, double rows, double cols) {
//    using namespace cv;
//    using namespace std;
//
//    double percentage = ((x + 1) * cols + y) / (rows * cols);
//    int val = (int)(percentage * 100);
//    int lpad = (int)(percentage * PBWIDTH);
//    int rpad = PBWIDTH - lpad;
//    printf("\r%3d%% [%.*s%*s]", val, lpad, PBSTR, rpad, "");
//    fflush(stdout);
//}
//
//void writeAsciiImage(std::string fileName, double fontSize, std::string character, bool showImage, bool blackBG = true)
//{
//    using namespace cv;
//    using namespace std;
//
//    auto size = getTextSize(character, FONT_HERSHEY_COMPLEX_SMALL, fontSize, 1, 0);
//    auto side = size.height > size.width ? size.height : size.width;
//    Mat image = imread(fileName, IMREAD_COLOR); // Read the file
//    Mat blankImage(image.rows * side, image.cols * side, CV_8UC3, blackBG ? Scalar(0, 0, 0) : Scalar(255, 255, 255, 0));
//    VideoWriter video("ascii.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 60, blankImage.size());
//
//    for (double x = 0; x < image.rows; x++)
//    {
//        for (double y = 1; y < image.cols; y++)
//        {
//            putText(blankImage, character, Point2d(y * side, x * side),
//                FONT_HERSHEY_COMPLEX_SMALL, fontSize, Scalar(image.at<cv::Vec3b>((int)x, (int)y)), 1, false);
//            video << blankImage;
//            printProgress(x, y, image.rows, image.cols);
//
//        }
//    }
//    cout << "\n" << "Created Image. Writing to storage...\n";
//
//    if (showImage)
//    {
//        namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
//        imshow("Display window", blankImage); // Show our image inside it.
//        waitKey(0); // Wait for a keystroke in the window
//    }
//    video.release();
//    imwrite("ascii-" + fileName, blankImage);
//}
