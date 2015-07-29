// surf.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "highgui.h"
#include<legacy/legacy.hpp>
#include <nonfree/features2d.hpp>
#include"iostream"
using namespace std;
using namespace cv;

int _tmain(int argc, _TCHAR* argv[])
{
	 Mat img_1=imread("1.png",CV_LOAD_IMAGE_GRAYSCALE);//�궨��ʱCV_LOAD_IMAGE_GRAYSCALE=0��Ҳ���Ƕ�ȡ�Ҷ�ͼ��
    Mat img_2=imread("2.png",CV_LOAD_IMAGE_GRAYSCALE);//һ��Ҫ�ǵ�����·����б�߷�������Matlab�������෴��
    
    if(!img_1.data || !img_2.data)//�������Ϊ��
    {
        cout<<"opencv error"<<endl;
        return -1;
    }
    cout<<"open right"<<endl;

    //��һ������SURF���Ӽ��ؼ���
    int minHessian=400;

    SurfFeatureDetector detector(minHessian);
    std::vector<KeyPoint> keypoints_1,keypoints_2;//����2��ר���ɵ���ɵĵ����������洢������

    detector.detect(img_1,keypoints_1);//��img_1ͼ���м�⵽��������洢��������keypoints_1��
    detector.detect(img_2,keypoints_2);//ͬ��

    //��ͼ���л���������
    Mat img_keypoints_1,img_keypoints_2;

    drawKeypoints(img_1,keypoints_1,img_keypoints_1,Scalar::all(-1),DrawMatchesFlags::DEFAULT);
    drawKeypoints(img_2,keypoints_2,img_keypoints_2,Scalar::all(-1),DrawMatchesFlags::DEFAULT);

    imshow("surf_keypoints_1",img_keypoints_1);
    imshow("surf_keypoints_2",img_keypoints_2);

    //������������
    SurfDescriptorExtractor extractor;//���������Ӷ���

    Mat descriptors_1,descriptors_2;//������������ľ���

    extractor.compute(img_1,keypoints_1,descriptors_1);
    extractor.compute(img_2,keypoints_2,descriptors_2);

    //��burte force����ƥ����������
    BruteForceMatcher<L2<float>>matcher;//����һ��burte force matcher����
    vector<DMatch>matches;
    matcher.match(descriptors_1,descriptors_2,matches);

    //����ƥ���߶�
    Mat img_matches;
    drawMatches(img_1,keypoints_1,img_2,keypoints_2,matches,img_matches);//��ƥ������Ľ�������ڴ�img_matches��

    //��ʾƥ���߶�
    imshow("surf_Matches",img_matches);//��ʾ�ı���ΪMatches
    waitKey(0);
	return 0;
}
