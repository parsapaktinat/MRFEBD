#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int mapRange(int, int, int, int, int);

int main()
{
    cv::Mat image;
    const string path = "/home/parsa/Downloads/images.jpeg";
    string asciiChars = " ,:;+*i!?t%B@$";
    image = cv::imread(path, cv::IMREAD_GRAYSCALE);
    cv::resize(image, image, cv::Size(image.size().width, image.size().height/2));

    if (image.empty()) {
        cerr << "Could not open or find the image" << endl;
        cin.get();
        return -1;
    }

    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            int grayScaleValue = static_cast<int>(image.at<uchar>(i, j));
            cout << asciiChars[mapRange(grayScaleValue, 0, 255, 0, 14)];
        }
        cout << endl;
    }

    return 0;
}

int mapRange(int value, int oldMin, int oldMax, int newMin, int newMax) {
    return (int) ceil(newMin + (value - oldMin) * (newMax - newMin) / (oldMax - oldMin));
}