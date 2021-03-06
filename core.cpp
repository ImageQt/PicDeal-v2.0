#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "core.h"
#define cvQueryHistValue_2D( hist, idx0, idx1 )  cvGetReal2D( (hist)->bins, (idx0), (idx1) )
//添加所需头文件、定义和命名空间
using namespace cv;
//以下为功能函数定义，如需要修改函数名称、传入参数和返回值等，请对应修改core.h文件中的函数声明

IplImage* Capture(){
    //调用摄像头
    //返回值为截取的图像
    return NULL;
}

void rgb2gray(IplImage* src,IplImage* dst){
    //彩色图像转灰度图像
    //src为源图像——三通道，dst为结果图像三单通道
    IplImage* temp=cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
    cvCvtColor(src,temp,CV_BGR2GRAY);
    cvCvtColor(temp,dst,CV_GRAY2RGB);
}

IplImage* histogram(IplImage* src){
    //显示图像灰度直方图
    //src为源图像，dst为结果图像
    //dst为包含src图像的灰度直方图的IplImage图像
    //不需要计算三通道，可调用rgb2gray函数转为灰度图像计算
    IplImage* hsv = cvCreateImage( cvGetSize(src), 8, 3 );
      IplImage* h_plane = cvCreateImage( cvGetSize(src), 8, 1 );
      IplImage* s_plane = cvCreateImage( cvGetSize(src), 8, 1 );
      IplImage* v_plane = cvCreateImage( cvGetSize(src), 8, 1 );
      IplImage* planes[] = { h_plane, s_plane };

      /* H 分量划分为16个等级，S分量划分为8个等级 */
      int h_bins = 16, s_bins = 8;
      int hist_size[] = {h_bins, s_bins};

      /*H 分量的变化范围 */
      float h_ranges[] = { 0, 180 };

      /* S 分量的变化范围*/
      float s_ranges[] = { 0, 255 };
      float* ranges[] = { h_ranges, s_ranges };

      /* 输入图像转换到HSV颜色空间 */
      cvCvtColor( src, hsv, CV_BGR2HSV );
      cvSplit( hsv, h_plane, s_plane, v_plane, 0 );

      /* 创建直方图，二维, 每个维度上均分 */
      CvHistogram * hist = cvCreateHist( 2, hist_size, CV_HIST_ARRAY, ranges, 1 );
      /* 根据H,S两个平面数据统计直方图 */
      cvCalcHist( planes, hist, 0, 0 );

      /* 获取直方图统计的最大值，用于动态显示直方图 */
      float max_value;
      cvGetMinMaxHistValue( hist, 0, &max_value, 0, 0 );


      /* 设置直方图显示图像 */
      int height = 240;
      int width = (h_bins*s_bins*6);
      IplImage* hist_img = cvCreateImage( cvSize(width,height), 8, 3 );
      cvZero( hist_img );

      /* 用来进行HSV到RGB颜色转换的临时单位图像 */
      IplImage * hsv_color = cvCreateImage(cvSize(1,1),8,3);
      IplImage * rgb_color = cvCreateImage(cvSize(1,1),8,3);
      int bin_w = width / (h_bins * s_bins);
      for(int h = 0; h < h_bins; h++)
      {
        for(int s = 0; s < s_bins; s++)
        {
          int i = h*s_bins + s;
          /* 获得直方图中的统计次数，计算显示在图像中的高度 */
          float bin_val = cvQueryHistValue_2D( hist, h, s );
          int intensity = cvRound(bin_val*height/max_value);

          /* 获得当前直方图代表的颜色，转换成RGB用于绘制 */
          cvSet2D(hsv_color,0,0,cvScalar(h*180.f / h_bins,s*255.f/s_bins,255,0));
          cvCvtColor(hsv_color,rgb_color,CV_HSV2BGR);
          CvScalar color = cvGet2D(rgb_color,0,0);

          cvRectangle( hist_img, cvPoint(i*bin_w,height),
            cvPoint((i+1)*bin_w,height - intensity),
            color, -1, 8, 0 );
        }
      }

      return hist_img;
}

void smooth(IplImage* src,IplImage* dst,int height,int width){
    //均值滤波
    //src为源图像，dst为结果图像
    //height为模板高度，width为模板宽度
    cvSmooth(src,dst,CV_GAUSSIAN,height,width);
}

void filter(IplImage* src,IplImage* dst,int height,int width){
    //中值滤波
    //src为源图像，dst为结果图像
    //height为模板高度，width为模板宽度
    cvSmooth(src,dst,CV_MEDIAN,height,width);
}

void colenhance(IplImage* src,IplImage* dst,int type){
    //假彩色增强
    //src为源图像，dst为结果图像
    /* type为假彩色增强类型，取值为1-6,分别对应：
     * 1——RGB
     * 2——RBG
     * 3——BRG
     * 4——BGR
     * 5——GRB
     * 6——GBR   */
    char color[4];
    switch (type) {
    case 1:
        strcpy(color,"rgb");
        //color="rgb";
        break;
    case 2:
        strcpy(color,"rbg");
        //color="rbg";
        break;
    case 3:
        strcpy(color,"brg");
        //color="brg";
        break;
    case 4:
        strcpy(color,"bgr");
        //color="bgr";
        break;
    case 5:
        strcpy(color,"grb");
        //color="grb";
        break;
    case 6:
        strcpy(color,"gbr");
        //color="gbr";
        break;
    default:
        break;
    }
        IplImage* R=cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
        IplImage* G=cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
        IplImage* B=cvCreateImage(cvGetSize(src),IPL_DEPTH_8U,1);
        cvSplit(src,B,G,R,0);

        if (!strcmp(color,"rgb"))
        {
            cvMerge(B,G,R,0,dst);
        }
        else if (!strcmp(color,"rbg"))
        {
            cvMerge(G,B,R,0,dst);
        }
        else if (!strcmp(color,"grb"))
        {
            cvMerge(B,R,G,0,dst);
        }
        else if (!strcmp(color,"gbr"))
        {
            cvMerge(R,B,G,0,dst);
        }
        else if (!strcmp(color,"bgr"))
        {
            cvMerge(R,G,B,0,dst);
        }
        else if (!strcmp(color,"brg"))
        {
            cvMerge(G,R,B,0,dst);
        }
}

IplImage* connlig(IplImage* Input,int contrast,int light){
    //调整亮度和对比度
    //src为源图像，dst为结果图像
    //contrast为对比度，取值为-1,0-10
    //light为亮度，取值为-1,0-10
    //contrast或light取值为-1时，对应项目不做变化
    IplImage* Output = NULL;
        if(contrast<0||light<0)
        {
            Output = Input;
            return Output;
        }
        Mat image = cvarrToMat(Input);
        Mat out_image = Mat::zeros(image.size(),image.type());
        for(int y = 0;y<image.rows;y++)
            for(int x = 0;x<image.cols;x++)
                for(int c=0;c<3;c++)
                    out_image.at<Vec3b>(y,x)[c] =  saturate_cast<uchar>( contrast*( image.at<Vec3b>(y,x)[c] ) + light );
        //saturate_cast保证数据0-255
        //new = alpha*src + beta
        IplImage temp=IplImage(out_image);
        Output = cvCloneImage(&temp) ;
        return Output;
}

void histoequ(IplImage* src,IplImage* dst){
    //直方图均衡化
    //src为源图像，dst为均衡化后的结果图像
    IplImage* redimage=cvCreateImage(cvGetSize(src),src->depth,1);
    IplImage* greenimage=cvCreateImage(cvGetSize(src),src->depth,1);
    IplImage* blueimage=cvCreateImage(cvGetSize(src),src->depth,1);
    cvSplit(src,blueimage,greenimage,redimage,NULL);
    cvEqualizeHist(redimage,redimage);
    cvEqualizeHist(greenimage,greenimage);
    cvEqualizeHist(blueimage,blueimage);
    cvMerge(blueimage,greenimage,redimage,NULL,dst);
}

void laplace(IplImage* src,IplImage* dst){
    //拉普拉斯锐化
    //src为源图像，dst为锐化后的结果图像
    float Scalar[9] = {0,-1,0,-1,5,-1,0,-1,0};
    CvMat kernel = cvMat(3,3,CV_32F,Scalar);
    cvFilter2D(src,dst,&kernel,cvPoint(-1,-1));
}

void canny(IplImage* pImage,IplImage* pNewImage,double threshold1,double threshold2, int aperture_size, bool preprocessing){
    //canny边缘检测
    //src为源图像，dst为结果图像
    //srcA为参数A，srcB为参数B，type为算子内核，predeal为预处理开关（true为进行预处理，false为不处理
    if(pImage)					//读图像
        {
            cvCvtColor(pImage,pNewImage,CV_RGB2GRAY);							//读入图像转换为单通道的灰度图像
            if(preprocessing)
            {
                float Scalar[9] = {0,-1,0,-1,5,-1,0,-1,0};							//Laplace
                CvMat kernel = cvMat(3,3,CV_32F,Scalar);							//建立矩阵

                cvFilter2D(pNewImage,pNewImage,&kernel,cvPoint(-1,-1));				//卷积（锐化）
                cvSmooth(pNewImage,pNewImage,3,3);									//模糊
                cvCanny(pNewImage,pNewImage,threshold1,threshold2,aperture_size);	//Canny算子
            }
            cvCanny(pNewImage,pNewImage,threshold1,threshold2,aperture_size);	//Canny算子
        }
}

void facedetect(IplImage* src,IplImage* dst){
    //人脸识别
    //src为源图像，dst为结果图像
    //加载人脸识别特征库
        cvCopy(src,dst);
        CvHaarClassifierCascade *pHaarClassCascade;
        char* name=new char[100];
        strcpy(name,"/usr/share/opencv/haarcascades/haarcascade_frontalface_alt.xml");
        pHaarClassCascade = (CvHaarClassifierCascade*)cvLoad(name);
        IplImage *pGrayImage = cvCreateImage(cvGetSize(dst),IPL_DEPTH_8U,1);
        cvCvtColor(dst,pGrayImage,CV_BGR2GRAY);

        //人脸检测
        if(pHaarClassCascade != NULL && dst != NULL && pGrayImage != NULL)
        {
            //勾画出人脸位置的圆形的颜色库
            const static CvScalar colors[] =
            {
                CV_RGB(0,0,255),
                CV_RGB(0,128,255),
                CV_RGB(0,255,255),
                CV_RGB(0,255,0),
                CV_RGB(255,128,0),
                CV_RGB(255,255,0),
                CV_RGB(255,0,0),
                CV_RGB(255,0,255),
            };

            //内存空间开辟？？？？
            CvMemStorage *pcvMemStorage = cvCreateMemStorage(0);
            cvClearMemStorage(pcvMemStorage);
            //进行检测
            CvSeq *pcvSeqFaces = cvHaarDetectObjects(pGrayImage,pHaarClassCascade,pcvMemStorage);
            //标志出人脸
            for(int i = 0; i<pcvSeqFaces->total;i++)
            {
                CvRect *r = (CvRect*)cvGetSeqElem(pcvSeqFaces,i);
                CvPoint center;

                int radius;
                center.x = cvRound(r->x + r->width * 0.5);
                center.y = cvRound(r->y + r->height * 0.5);
                radius = cvRound((r->width + r->height) * 0.25);
                cvCircle(dst,center,radius,colors[i%8],2);
            }
            cvReleaseMemStorage(&pcvMemStorage);
        }
}

void FFT(IplImage* src,IplImage* dstA, IplImage* dstB){
    //傅立叶变换
    //src为源图像，dstA为傅立叶变换图像，dstB为傅立叶逆变换图像
}

IplImage* rotate(IplImage* src,double theta){
    //图像旋转
    //src为源图像，dst为旋转后图像，degree为顺时针旋转度数0-360
        Mat image=cvarrToMat(src,true);
        unsigned char * pImg = image.data;
        int oldWidth = image.cols;
        int oldHeight = image.rows;
        int channels = image.channels();
        float fSrcX1,fSrcY1,fSrcX2,fSrcY2,fSrcX3,fSrcY3,fSrcX4,fSrcY4;
        fSrcX1 = (float) (- (oldWidth  - 1) / 2);
        fSrcY1 = (float) (  (oldHeight - 1) / 2);
        fSrcX2 = (float) (  (oldWidth  - 1) / 2);
        fSrcY2 = (float) (  (oldHeight - 1) / 2);
        fSrcX3 = (float) (- (oldWidth  - 1) / 2);
        fSrcY3 = (float) (- (oldHeight - 1) / 2);
        fSrcX4 = (float) (  (oldWidth  - 1) / 2);
        fSrcY4 = (float) (- (oldHeight - 1) / 2);
        Mat image_gray;
        unsigned char *pImg_copy = image_gray.data;
        float fDstX1,fDstY1,fDstX2,fDstY2,fDstX3,fDstY3,fDstX4,fDstY4;
        float pi=3.1415926;
        theta=theta/180*pi;
        fDstX1 =  cos(theta) * fSrcX1 + sin(theta) * fSrcY1;
        fDstY1 = -sin(theta) * fSrcX1 + cos(theta) * fSrcY1;
        fDstX2 =  cos(theta) * fSrcX2 + sin(theta) * fSrcY2;
        fDstY2 = -sin(theta) * fSrcX2 + cos(theta) * fSrcY2;
        fDstX3 =  cos(theta) * fSrcX3 + sin(theta) * fSrcY3;
        fDstY3 = -sin(theta) * fSrcX3 + cos(theta) * fSrcY3;
        fDstX4 =  cos(theta) * fSrcX4 + sin(theta) * fSrcY4;
        fDstY4 = -sin(theta) * fSrcX4 + cos(theta) * fSrcY4;
        int newWidth  = ( max( fabs(fDstX4 - fDstX1), fabs(fDstX3 - fDstX2) ) + 0.5);
        int newHeight = ( max( fabs(fDstY4 - fDstY1), fabs(fDstY3 - fDstY2) )  + 0.5);
        int newchannals=channels;
        float dx = -0.5*(newWidth-1)*cos(theta) - 0.5*(newHeight-1)*sin(theta) + 0.5*(oldWidth-1);
        float dy = 0.5*newWidth*sin(theta) - 0.5*newHeight*cos(theta) + 0.5*(oldHeight-1);
        image_gray.create(newHeight, newWidth, CV_8UC3);
        int x,y;
        for (int i=0; i<newHeight; i++)
        {
            for (int j=0; j<newWidth; j++)
            {
                for(int k=0; k<newchannals; k++){
                    x = float(j)*cos(theta) + float(i)*sin(theta) + dx+0.5;  //j0
                    y = float(-j)*sin(theta) + float(i)*cos(theta) + dy+0.5;  //i0

                    if ((x<0) || (x>=oldWidth) || (y<0) || (y>=oldHeight))
                    {
                              image_gray.at<Vec3b>(i,j)[k] = 255;

                    }
                    else
                    {
                            image_gray.at<Vec3b>(i,j)[k] = image.at<Vec3b>(y,x)[k];
                    }
                }
            }
        }
        IplImage temp2=IplImage(image_gray);
        IplImage* dst = cvCloneImage(&temp2) ;
        return dst;
}

void piczoom(IplImage* src,IplImage* dst,int zoom){
    //图像缩放
    //src为源图像，dst为结果图像
    //zoom为缩放倍数，取值为0.3-5,小于1时为缩小
}

void piccut(IplImage* src,IplImage* dst, int ltx,int lty,int rbx,int rby){
    //图像裁剪
    //src为源图像，dst为结果图像，后面四个参数为裁剪区域像素坐标
    //(ltx,lty)为左上角像素坐标，(rbx,rby)为右下角像素坐标，裁剪区域为两点所确定的矩形
    //不用处理鼠标响应事件
}
