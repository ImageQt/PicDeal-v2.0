#ifndef CORE_H
#define CORE_H

#endif // CORE_H

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

//core.cpp所对应函数声明，如有需要，可进行修改

IplImage* Capture();//调用摄像头
void rgb2gray(IplImage* src,IplImage* dst);//彩色图像转灰度图像
IplImage* histogram(IplImage* src);//显示图像灰度直方图
void smooth(IplImage* src,IplImage* dst,int height,int width);//均值滤波
void filter(IplImage* src,IplImage* dst,int height,int width);//中值滤波
void colenhance(IplImage* src,IplImage* dst,int type);//假彩色增强
IplImage* connlig(IplImage* Input,int contrast,int light);//调整亮度和对比度
void histoequ(IplImage* src,IplImage* dst);//直方图均衡化
void laplace(IplImage* src,IplImage* dst);//拉普拉斯锐化
void canny(IplImage* pImage,IplImage* pNewImage,double threshold1,double threshold2, int aperture_size, bool preprocessing);//canny边缘检测
void facedetect(IplImage* src,IplImage* dst);//人脸识别
void FFT(IplImage* src,IplImage* dstA, IplImage* dstB);//傅立叶变换
IplImage* rotate(IplImage* src,double theta);//图像旋转
void piczoom(IplImage* src,IplImage* dst,int zoom);//图像缩放
void piccut(IplImage* src,IplImage* dst, int ltx,int lty,int rbx,int rby);//图像裁剪
