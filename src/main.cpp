
#include <iostream>
#include <opencv2/opencv.hpp>

/****************************************************/
#include "Demosaicing.hpp"
using namespace std;


int main(int argc, const char * argv[]) {

    cv::Mat src = cv::imread("original_img.bmp",cv::IMREAD_COLOR);
    cv::Mat bayer;

    Color2Bayer(src,bayer,0);

    cv::Mat dst1,dst2;

    Bilinear(bayer,dst1);
    NearestNeighbor(bayer,dst2);
    


    cv::imwrite("bayer_pattern_img.bmp",bayer);
    cv::imwrite("Bilnear_dst.bmp",dst1);
    cv::imwrite("NearestNeighbor_dst.bmp",dst2);
    cv::waitKey(0);
    cv::destroyAllWindows();
    
    return 0;
}



