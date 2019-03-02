#include "Demosaicing.hpp"
#include <opencv2/opencv.hpp>



int Color2Bayer(cv::Mat &src,cv::Mat &dst,int BayerPattern)
{
    // BayerPattern 0->GRBG, 1->RGGB , 2-> BGGR, 3->GBRG
    float GKernel[2][2] = {0};
    float BKernel[2][2] = {0};
    float RKernel[2][2] = {0};
    
    switch (BayerPattern) {
        case 0:
            GKernel[0][0] = 1; GKernel[1][1] = 1;
            BKernel[1][0] = 1; RKernel[0][1] = 1;
            break;
        case 1:
            GKernel[0][1] = 1; GKernel[1][0] = 1;
            RKernel[0][0] = 1; BKernel[1][1] = 1;
            break;
        case 2:
            GKernel[0][1] = 1; GKernel[1][0] = 1;
            RKernel[1][1] = 1; BKernel[0][0] = 1;
            break;
        case 3:
            GKernel[0][0] = 1; GKernel[1][1] = 1;
            RKernel[1][0] = 1; BKernel[0][1] = 1;
            break;
        default:
            std::cerr<<"Wrong bayer pattern flag"<<std::endl;
            return -1;
    }
    
    cv::Mat GK(2,2,CV_32F,GKernel),BK(2,2,CV_32F,BKernel),RK(2,2,CV_32F,RKernel);
    
    GK.convertTo(GK, CV_8U);
    BK.convertTo(BK, CV_8U);
    RK.convertTo(RK, CV_8U);
    
    cv::copyMakeBorder(GK, GK, 0, src.rows-2, 0, src.cols-2, cv::BORDER_REFLECT_101);
    cv::copyMakeBorder(BK, BK, 0, src.rows-2, 0, src.cols-2, cv::BORDER_REFLECT_101);
    cv::copyMakeBorder(RK, RK, 0, src.rows-2, 0, src.cols-2, cv::BORDER_REFLECT_101);
    
    std::vector<cv::Mat> bgrVec(3);
    cv::split(src,bgrVec);
    
    bgrVec[0] = bgrVec[0].mul(BK);
    bgrVec[1] = bgrVec[1].mul(GK);
    bgrVec[2] = bgrVec[2].mul(RK);
    
    cv::merge(bgrVec, dst);
    
    return 0;
}


void Bilinear(cv::Mat &Src,cv::Mat &Dst)
{
    
    double BRKernel[3][3] = { { 0.25,0.5,0.25 },{ 0.5,1,0.5 },{ 0.25,0.5,0.25 } };
    double GKernel[3][3] = { { 0,0.25,0 },{ 0.25,1,0.25 },{ 0,0.25,0 } };
    
    cv::Mat BRK(3, 3, CV_64F, BRKernel);
    cv::Mat GK(3, 3, CV_64F, GKernel);
    
    std::vector<cv::Mat> bgrVec(3);
    cv::split(Src, bgrVec);
    cv::filter2D(bgrVec[0], bgrVec[0], -1, BRK);
    cv::filter2D(bgrVec[1], bgrVec[1], -1, GK);
    cv::filter2D(bgrVec[2], bgrVec[2], -1, BRK);
    
    cv::merge(bgrVec, Dst);
    
}

void NearestNeighbor(cv::Mat &Src, cv::Mat &Dst)
{
    
    std::vector<cv::Mat> bgrVec(3);
    cv::split(Src, bgrVec);
    
    double GKernel[4] = { 1.0,1.0,0.0,0.0 };
    double BRKernel[4] = { 1.0,1.0,1.0,1.0 };
    
    cv::Mat GK(2, 2, CV_64F, GKernel);
    cv::Mat BRK(2, 2, CV_64F, BRKernel);
    
    cv::filter2D(bgrVec[0],bgrVec[0] , -1, BRK,cv::Point(0,0));
    cv::filter2D(bgrVec[1],bgrVec[1] , -1, GK ,cv::Point(0,0));
    cv::filter2D(bgrVec[2],bgrVec[2] , -1, BRK,cv::Point(0,0));
    
    cv::merge(bgrVec, Dst);
}
