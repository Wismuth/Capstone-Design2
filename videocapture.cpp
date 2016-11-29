
//Kookmin University Computer Science - Capstone Design - FINAL PROJECT_ TEAM 20
//Upload by 20123366 Park Jina
//This code has been made for the first semester of Capstone Design.

#include <Windows.h>
#include <iostream>
#include <opencv2\opencv.hpp>
#include <opencv\highgui.h>
#pragma comment(lib, "winmm.lib") //timeGetTime() 
#include <cstring>
#include <string.h>
#include <string>

int BitWise(cv::Mat videoCut, cv::Mat temple, cv::Mat result);

int main(int argc, char* argv[]) {
	int result[3][11] = { 0 };
	cv::Mat frame;
	cv::Mat gray; //to transform gray color
	cv::Mat bin_img; 
	cv::Mat otsu_img;
	cv::Mat ad_img;
	//IplImage *frame;
	char file_name[20];
	sprintf_s(file_name, "img.bmp");            //make file name
	int count = 0;
	float m_fStartTime = (float)timeGetTime() * 0.001f;

	cv::namedWindow("Test", 1);
	cv::VideoCapture capture;     //CvCapture* capture = cvCaptureFromCAM(0);
	capture.open("C:/Users/user/Desktop/FinalProject-capstone_20/opencvex/opencvex/Video6.mp4"); //2)video path
	//cvNamedWindow("Test",1);
	//capture.open(0); 
 
	while (capture.read(frame)){ 
		//frame = cvQueryFrame(capture);


		capture >> frame;
		//cv::imshow("Test", frame);   

		cv::cvtColor(frame, gray, CV_BGR2GRAY);	

		cv::threshold(gray, bin_img, 145, 255, CV_THRESH_BINARY);
		//cv::threshold(gray, otsu_img, 0, 255, CV_THRESH_BINARY|CV_THRESH_OTSU);
		//cv::adaptiveThreshold(gray, ad_img, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 7, 8);


		cv::Rect rect(250, 100, 480, 300);
		cv::Rect rectFirst(175, 35, 114, 222);
		cv::Rect rectSecond(280, 36, 114, 222);
		cv::Rect rectThird(364, 31, 114, 222);
		cv::Rect rectType(0, 39, 114, 222);
		cv::Mat cut_img = bin_img(rect); 
		cv::imshow("resize image", cut_img);

		float NowTime = (float)timeGetTime() * 0.001f;
		cv::Mat typeCut = cut_img(rectType);
		cv::Mat firstNumCut = cut_img(rectFirst);
		cv::Mat secondNumCut = cut_img(rectSecond);
		cv::Mat thirdNumCut = cut_img(rectThird);

		cv::String filename, tempName, secname, thrname;
		filename = cv::format("capture%03d.bmp", count);
		tempName = cv::format("first.bmp", count); 
		secname = cv::format("sec.bmp", count); 
		thrname = cv::format("thr.bmp", count); 

		cv::imwrite(filename.c_str(), cut_img); //save an image into folder
		cv::imwrite(tempName.c_str(), firstNumCut);
		cv::imwrite(secname.c_str(), secondNumCut);
		cv::imwrite(thrname.c_str(), thirdNumCut);
		cv::imshow("First number", firstNumCut); //show images
		cv::imshow("Second number", secondNumCut);
		cv::imshow("Third number", thirdNumCut);

		cv::waitKey(1);
		count++; // to save filename image 



cv::Mat srcNumZero, srcNumOne, srcNumTwo, srcNumThree, srcNumFour, srcNumFive, srcNumSix, srcNumSeven, srcNumEight, srcNumNine, srcEmpty, srcCase;
cv::Mat res, srcOne, srcTwo, srcThree, srcFour, srcFive, srcSix, srcSeven, srcEight, srcNine, srcZero, srcBlank, srcType; //result 

int minFirst=0, minSecond=0, minThird=0;
float firstNum=0, secondNum=0, thirdNum=0;

int i, j;

int height, width;

int resint = 0;

int type;
int speedOrRpm;
srcNumZero = cv::imread("C:/Users/user/Desktop/FinalProject-capstone_20/number/no0.bmp", -1);
srcNumOne = cv::imread("C:/Users/user/Desktop/FinalProject-capstone_20/number/no1.bmp", -1);
srcNumTwo = cv::imread("C:/Users/user/Desktop/FinalProject-capstone_20/number/no2.bmp", -1);
srcNumThree = cv::imread("C:/Users/user/Desktop/FinalProject-capstone_20/number/no3.bmp", -1);
srcNumFour = cv::imread("C:/Users/user/Desktop/FinalProject-capstone_20/number/no4.bmp", -1);
srcNumFive = cv::imread("C:/Users/user/Desktop/FinalProject-capstone_20/number/no5.bmp", -1);
srcNumSix = cv::imread("C:/Users/user/Desktop/FinalProject-capstone_20/number/no6.bmp", -1);
srcNumSeven = cv::imread("C:/Users/user/Desktop/FinalProject-capstone_20/number/no7.bmp", -1);
srcNumEight = cv::imread("C:/Users/user/Desktop/FinalProject-capstone_20/number/no8.bmp", -1);
srcNumNine = cv::imread("C:/Users/user/Desktop/FinalProject-capstone_20/number/no9.bmp", -1);
srcEmpty = cv::imread("C:/Users/user/Desktop/FinalProject-capstone_20/number/none.bmp", -1);
srcCase = cv::imread("C:/Users/user/Desktop/FinalProject-capstone_20/number/speed.bmp", -1);
type = BitWise(typeCut, srcCase, srcType);
if (type > 1600000)
speedOrRpm = 0;
else
speedOrRpm = 1;
result[0][0] = BitWise(firstNumCut, srcNumZero, srcZero);
result[0][1] = BitWise(firstNumCut, srcNumOne, srcOne);
result[0][2] = BitWise(firstNumCut, srcNumTwo, srcTwo);
result[0][3] = BitWise(firstNumCut, srcNumThree, srcThree);
result[0][4] = BitWise(firstNumCut, srcNumFour, srcFour);
result[0][5] = BitWise(firstNumCut, srcNumFive, srcFive);
result[0][6] = BitWise(firstNumCut, srcNumSix, srcSix);
result[0][7] = BitWise(firstNumCut, srcNumSeven, srcSeven);
result[0][8] = BitWise(firstNumCut, srcNumEight, srcEight);
result[0][9] = BitWise(firstNumCut, srcNumNine, srcNine);
result[0][10] = BitWise(firstNumCut, srcEmpty, srcBlank);
result[1][0] = BitWise(secondNumCut, srcNumZero, srcZero);
result[1][1] = BitWise(secondNumCut, srcNumOne, srcOne);
result[1][2] = BitWise(secondNumCut, srcNumTwo, srcTwo);
result[1][3] = BitWise(secondNumCut, srcNumThree, srcThree);
result[1][4] = BitWise(secondNumCut, srcNumFour, srcFour);
result[1][5] = BitWise(secondNumCut, srcNumFive, srcFive);
result[1][6] = BitWise(secondNumCut, srcNumSix, srcSix);
result[1][7] = BitWise(secondNumCut, srcNumSeven, srcSeven);
result[1][8] = BitWise(secondNumCut, srcNumEight, srcEight);
result[1][9] = BitWise(secondNumCut, srcNumNine, srcNine);
result[1][10] = BitWise(secondNumCut, srcEmpty, srcBlank);
result[2][0] = BitWise(thirdNumCut, srcNumZero, srcZero);
result[2][1] = BitWise(thirdNumCut, srcNumOne, srcOne);
result[2][2] = BitWise(thirdNumCut, srcNumTwo, srcTwo);
result[2][3] = BitWise(thirdNumCut, srcNumThree, srcThree);
result[2][4] = BitWise(thirdNumCut, srcNumFour, srcFour);
result[2][5] = BitWise(thirdNumCut, srcNumFive, srcFive);
result[2][6] = BitWise(thirdNumCut, srcNumSix, srcSix);
result[2][7] = BitWise(thirdNumCut, srcNumSeven, srcSeven);
result[2][8] = BitWise(thirdNumCut, srcNumEight, srcEight);
result[2][9] = BitWise(thirdNumCut, srcNumNine, srcNine);
result[2][10] = BitWise(thirdNumCut, srcEmpty, srcBlank);
minFirst = result[0][0];
minSecond = result[1][0];
minThird = result[2][0];
for (i = 0; i < 11; i++)
	std::cout << result[1][i] << " ";
std::cout << std::endl;
switch (speedOrRpm)
{
case 0:
	std::cout << "rpm" << std::endl;
	break;
case 1:
	std::cout << "speed" << std::endl;
	break;
default:
	std::cout << "error" << std::endl;
	break;
}
for (int i = 1; i < 11; i++)
{
	if (result[0][i] < minFirst)
	{
		minFirst = result[0][i];
		if (i < 10)
			firstNum = i;
		else
			firstNum = 0;
	}
	if (result[1][i] < minSecond)
	{
		minSecond = result[1][i];
		if (i < 10)
			secondNum = i;
		else
			secondNum = 0;
	}
	if (result[2][i] < minThird)
	{
		minThird = result[2][i];
		if (i < 10)
			thirdNum = i;
		else
			thirdNum = 0;
	}
		
}
std::cout << firstNum << secondNum << thirdNum << std::endl;


if (cvWaitKey(33) >= 27)  //esc
break;


	}

	capture.release();
	cvDestroyWindow("Test");

	return 0;

}


int BitWise(cv::Mat videoCut, cv::Mat temple, cv::Mat result)
{
	bitwise_xor(videoCut, temple, result);
	int sum = 0;
	for (int i = 0; i < result.rows; i++)
	{
		for(int j = 0; j < result.cols; j++)
		{
			sum += result.data[i*result.cols + j];
		}
	}
	return sum;
}




