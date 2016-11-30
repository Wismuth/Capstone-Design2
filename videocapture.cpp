#include <opencv\highgui.h>
#pragma comment(lib, "winmm.lib") //timeGetTime() 사용 위해
#include <opencv2/opencv.hpp>
#include <cstring>
#include <string.h>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>

int BitWise(cv::Mat videoCut, cv::Mat temple, cv::Mat result);

void onMouse(int evt, int x, int y, int flags, void* param);

double getWebcamNumber(double pixelFirstMean, double pixelSecondMean, double pixelThirdMean, double halfSizePixelFirstNumberMean, double halfSizePixelSecondNumberMean, double halfSizePixelThirdNumberMean, double halfColPixelFirstNumberMean, double halfColPixelSecondNumberMean, double halfColPixelThirdNumberMean, double webCamNumber);

std::vector<float> xPoint;
std::vector<float> yPoint;

float main(int argc, char* argv[]) {
	double webCamNumber = 0;
	int firstResult[5] = { 0 };
	int secondResult[11] = { 0 };
	int thirdResult[10] = { 0 };
	float xFirstLocationSize = 0.0f;
	float yFirstLocationSize = 0.0f;
	float xSecondLocationSize = 0.0f;
	float ySecondLocationSize = 0.0f;
	float xThirdLocationSize = 0.0f;
	float yThirdLocationSize = 0.0f;
	float error = 0.0f;
	int yMax = 0;
	int yMin = 800;
	int xMax = 0;
	int xMin = 800;
	int xArea;
	int yArea;
	double pixelFirstNumberMean = 0;
	double pixelSecondNumberMean = 0;
	double pixelThirdNumberMean = 0;
	double halfSizePixelFirstNumberMean = 0;
	double halfSizePixelSecondNumberMean = 0;
	double halfSizePixelThirdNumberMean = 0;

	double halfColPixelFirstNumberMean = 0;
	double halfColPixelSecondNumberMean = 0;
	double halfColPixelThirdNumberMean = 0;
	cv::VideoCapture capture(0);
	if (!capture.isOpened())
	{
		std::cout << "File is not open" << std::endl;
	}
	cv::Mat frame, dstFirstLocation, dstSecondLocation, dstThirdLocation;
	cv::Mat grayFirstNumber, graySecondNumber, grayThirdNumber; //gray 칼라로 변환
	cv::Mat cutImgFirstLocation, cutImgSecondLocation, cutImgThirdLocation;
	for (;;)
	{
		capture >> frame;

		cv::imshow("sourceWindow", frame);
		cv::setMouseCallback("sourceWindow", onMouse, NULL);
		if (xPoint.size() >= 6 && yPoint.size() >= 6)
		{
			xFirstLocationSize = xPoint[1] - xPoint[0];
			yFirstLocationSize = yPoint[1] - yPoint[0];
			xSecondLocationSize = xPoint[3] - xPoint[2];
			ySecondLocationSize = yPoint[3] - yPoint[2];
			xThirdLocationSize = xPoint[5] - xPoint[4];
			yThirdLocationSize = yPoint[5] - yPoint[4];
			cv::Rect rectFirstNumberLocation(xPoint[0], yPoint[0], xFirstLocationSize, yFirstLocationSize);
			cv::Rect rectSecondNumberLocation(xPoint[2], yPoint[2], xSecondLocationSize, ySecondLocationSize);
			cv::Rect rectThirdNumberLocation(xPoint[4], yPoint[4], xThirdLocationSize, yThirdLocationSize);
			cutImgFirstLocation = frame(rectFirstNumberLocation);
			cutImgSecondLocation = frame(rectSecondNumberLocation);
			cutImgThirdLocation = frame(rectThirdNumberLocation);
			cv::resize(cutImgFirstLocation, dstFirstLocation, cv::Size(120, 90), 0, 0, CV_INTER_CUBIC);
			cv::resize(cutImgSecondLocation, dstSecondLocation, cv::Size(120, 90), 0, 0, CV_INTER_CUBIC);
			cv::resize(cutImgThirdLocation, dstThirdLocation, cv::Size(120, 90), 0, 0, CV_INTER_CUBIC);
			cv::cvtColor(dstFirstLocation, grayFirstNumber, CV_BGR2GRAY);	//frame을 gray 칼라로 변환
			cv::cvtColor(dstSecondLocation, graySecondNumber, CV_BGR2GRAY);
			cv::cvtColor(dstThirdLocation, grayThirdNumber, CV_BGR2GRAY);
			cv::threshold(grayFirstNumber, dstFirstLocation, 110, 255, CV_THRESH_BINARY);
			cv::threshold(graySecondNumber, dstSecondLocation, 110, 255, CV_THRESH_BINARY);
			cv::threshold(grayThirdNumber, dstThirdLocation, 110, 255, CV_THRESH_BINARY);
			cv::imshow("첫번째 숫자", dstFirstLocation);
			cv::imshow("두번째 숫자", dstSecondLocation);
			cv::imshow("세번째 숫자", dstThirdLocation);
			if (!dstFirstLocation.empty() && !dstSecondLocation.empty() && !dstThirdLocation.empty())
			{
				for (int i = 0; i < 120; i++)
				{
					for (int j = 0; j < 90; j++)
					{
						pixelFirstNumberMean += (int)dstFirstLocation.at<unsigned char>(j, i) / 255;
						pixelSecondNumberMean += (int)dstSecondLocation.at<unsigned char>(j, i) / 255;
						pixelThirdNumberMean += (int)dstThirdLocation.at<unsigned char>(j, i) / 255;
					}
				}
				for (int i = 0; i < 120; i++)
				{
					for (int j = 0; j < 45; j++)
					{
						halfSizePixelFirstNumberMean += (int)dstFirstLocation.at<unsigned char>(j, i) / 255;
						halfSizePixelSecondNumberMean += (int)dstSecondLocation.at<unsigned char>(j, i) / 255;
						halfSizePixelThirdNumberMean += (int)dstThirdLocation.at<unsigned char>(j, i) / 255;
					}
				}
				for (int i = 0; i < 60; i++)
				{
					for (int j = 0; j < 90; j++)
					{
						halfColPixelFirstNumberMean += (int)dstFirstLocation.at<unsigned char>(j, i) / 255;
						halfColPixelSecondNumberMean+= (int)dstSecondLocation.at<unsigned char>(j, i) / 255;
						halfColPixelThirdNumberMean += (int)dstThirdLocation.at<unsigned char>(j, i) / 255;
					}
				}
			}
			double speed = getWebcamNumber(pixelFirstNumberMean / (120 * 90), pixelSecondNumberMean / (120 * 90), pixelThirdNumberMean / (120 * 90), halfSizePixelFirstNumberMean / (120 * 45), halfSizePixelSecondNumberMean / (120 * 45), halfSizePixelThirdNumberMean / (120 * 45), halfColPixelFirstNumberMean / (60 * 90), halfColPixelSecondNumberMean / (60 * 90), halfColPixelThirdNumberMean / (60 * 90), webCamNumber);
			std::cout << speed << std::endl;
			pixelFirstNumberMean = 0;
			pixelSecondNumberMean = 0;
			pixelThirdNumberMean = 0;
			halfSizePixelFirstNumberMean = 0;
			halfSizePixelSecondNumberMean = 0;
			halfSizePixelThirdNumberMean = 0;
			halfColPixelFirstNumberMean = 0;
			halfColPixelSecondNumberMean = 0;
			halfColPixelThirdNumberMean = 0;
			
		}
		cv::waitKey(33);
	}
	capture.release();
	return 0;

}

double getWebcamNumber(double pixelFirstMean, double pixelSecondMean, double pixelThirdMean, double halfSizePixelFirstNumberMean, double halfSizePixelSecondNumberMean, double halfSizePixelThirdNumberMean, double halfColPixelFirstNumberMean, double halfColPixelSecondNumberMean, double halfColPixelThirdNumberMean, double webCamNumber)
{
	double firstNum = 0;
	double secondNum = 0;
	double thirdNum = 0;
	if (pixelFirstMean >= (double)4940 / (double)(120 * 90) && (double)pixelFirstMean <= (double)4980 / (double)(120 * 90))
	{
		firstNum = 8;
	}
	else if (pixelFirstMean >= (double)5100 / (double)(120 * 90) && pixelFirstMean <= (double)5230 / (double)(120 * 90))
	{
		firstNum = 0;
	}
	else if (pixelFirstMean >= (double)5800 / (double)(120 * 90) && pixelFirstMean <= (double)5880 / (double)(120 * 90))
	{
		firstNum = 9;
	}
	else if (pixelFirstMean >= (double)5590 / (double)(120 * 90) && pixelFirstMean <= (double)5620 / (double)(120 * 90))
	{
		firstNum = 6;
	}
	else if (pixelFirstMean >= (double)6550 / (double)(120 * 90) && pixelFirstMean <= (double)6800 / (double)(120 * 90))
	{
		if (halfColPixelFirstNumberMean >= (double)3420 / (double)(60 * 90) && halfColPixelFirstNumberMean <= (double)3430 / (double)(60 * 90))
		{
			firstNum = 2;
		}
		else
		{
			firstNum = 3;
		}
	}
	else if (pixelFirstMean >= (double)6810 / (double)(120 * 90) && pixelFirstMean <= (double)6840 / (double)(120 * 90))
	{
		firstNum = 5;
	}
	else if (pixelFirstMean >= (double)7310 / (double)(120 * 90) && pixelFirstMean <= (double)7340 / (double)(120 * 90))
	{
		if (halfSizePixelFirstNumberMean >= (double)2760 / (double)(120 * 45) && halfSizePixelFirstNumberMean <= (double)2780 / (double)(120 * 45))
		{
			firstNum = 7;
		}
		else
		{
			firstNum = 4;
		}
	}
	else if (pixelFirstMean >= (double)8750 / (double)(120 * 90) && pixelFirstMean <= (double)8760 / (double)(120 * 90))
	{
		firstNum = 1;
	}
	else
	{
		firstNum = 100;
	}
	if (pixelSecondMean >= (double)4940 / (double)(120 * 90) && pixelSecondMean <= (double)4980 / (double)(120 * 90))
	{
		secondNum = 8;
	}
	else if (pixelSecondMean >= (double)5100 / (double)(120 * 90) && pixelSecondMean <= (double)5230 / (double)(120 * 90))
	{
		secondNum = 0;
	}
	else if (pixelSecondMean >= (double)5800 / (double)(120 * 90) && pixelSecondMean <= (double)5880 / (double)(120 * 90))
	{
		secondNum = 9;
	}
	else if (pixelSecondMean >= (double)5590 / (double)(120 * 90) && pixelSecondMean <= (double)5620 / (double)(120 * 90))
	{
		secondNum = 6;
	}
	else if (pixelSecondMean >= (double)6550 / (double)(120 * 90) && pixelSecondMean <= (double)6800 / (double)(120 * 90))
	{
		if (halfColPixelSecondNumberMean >= (double)3420 / (double)(60 * 90) && halfColPixelSecondNumberMean <= (double)3430 / (double)(60 * 90))
		{
			secondNum = 2;
		}
		else
		{
			secondNum = 3;
		}
	}
	else if (pixelSecondMean >= (double)6810 / (double)(120 * 90) && pixelSecondMean <= (double)6840 / (double)(120 * 90))
	{
		secondNum = 5;
	}
	else if (pixelSecondMean >= (double)7310 / (double)(120 * 90) && pixelSecondMean <= (double)7340 / (double)(120 * 90))
	{
		if (halfSizePixelSecondNumberMean >= (double)2760 / (double)(120 * 45) && halfSizePixelSecondNumberMean <= (double)2780 / (double)(120 * 45))
		{
			secondNum = 7;
		}
		else
		{
			secondNum = 4;
		}
	}
	else if (pixelSecondMean >= (double)8750 / (double)(120 * 90) && pixelSecondMean <= (double)8760 / (double)(120 * 90))
	{
		secondNum = 1;
	}
	if (pixelThirdMean >= (double)4940 / (double)(120 * 90) && pixelThirdMean <= (double)4980 / (double)(120 * 90))
	{
		thirdNum = 8;
	}
	else if (pixelThirdMean >= (double)5100 / (double)(120 * 90) && pixelThirdMean <= (double)5230 / (double)(120 * 90))
	{
		thirdNum = 0;
	}
	else if (pixelThirdMean >= (double)5800 / (double)(120 * 90) && pixelThirdMean <= (double)5880 / (double)(120 * 90))
	{
		thirdNum = 9;
	}
	else if (pixelThirdMean >= (double)5590 / (double)(120 * 90) && pixelThirdMean <= (double)5620 / (double)(120 * 90))
	{
		thirdNum = 6;
	}
	else if (pixelThirdMean >= (double)6550 / (double)(120 * 90) && pixelThirdMean <= (double)6800 / (double)(120 * 90))
	{
		if (halfColPixelThirdNumberMean >= (double)3420 / (double)(60 * 90) && halfColPixelThirdNumberMean <= (double)3430 / (double)(60 * 90))
		{
			thirdNum = 2;
		}
		else
		{
			thirdNum = 3;
		}
	}
	else if (pixelThirdMean >= (double)6810 / (double)(120 * 90) && pixelThirdMean <= (double)6840 / (double)(120 * 90))
	{
		thirdNum = 5;
	}
	else if (pixelThirdMean >= (double)7310 / (double)(120 * 90) && pixelThirdMean <= (double)7340 / (double)(120 * 90))
	{
		if (halfSizePixelThirdNumberMean >= (double)2760 / (120 * 45) && halfSizePixelThirdNumberMean <= (double)2780 / (120 * 45))
		{
			thirdNum = 7;
		}
		else
		{
			thirdNum = 4;
		}
	}
	else if (pixelThirdMean >= (double)8750 / (double)(120 * 90) && pixelThirdMean <= (double)8760 / (double)(120 * 90))
	{
		thirdNum = 1;
	}
	if (firstNum != 100)
	{
		webCamNumber = firstNum * 10 + secondNum + thirdNum / 10;;
		return webCamNumber;
	}
	else
	{
		return webCamNumber;
	}
}

int BitWise(cv::Mat videoCut, cv::Mat temple, cv::Mat result)
{
	bitwise_xor(videoCut, temple, result);
	int sum = 0;
	for (int i = 0; i < result.rows; i++)
	{
		for (int j = 0; j < result.cols; j++)
		{
			sum += result.data[i*result.cols + j];
		}
	}
	return sum;
}
void onMouse(int evt, int x, int y, int flags, void* param)
{
	if (evt == CV_EVENT_LBUTTONDOWN)
	{
		xPoint.push_back(x);
		yPoint.push_back(y);
	}
}





