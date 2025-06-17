#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;

int main()
{
    cv::Mat image;
    const string path = "/home/parsa/Downloads";
    image = cv::imread(path, cv::IMREAD_COLOR);

    if (image.empty()) {
        cout << "Could not open or find the image" << endl;
        return -1;
    }

    cv::imshow("Display window", image);
    cv::waitKey(0);
    return 0;
}