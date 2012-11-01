// VideoFrameSplitter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include "VideoFrameSplitter.h"

using namespace std;

int main() { 
  CvCapture *capture = cvCreateFileCapture("C:\\Materials\\6.avi");
  double fps = cvGetCaptureProperty(capture, CV_CAP_PROP_FPS);
  IplImage *frame, *left, *right;
  CvVideoWriter *leftWriter, *rightWriter;
  left = right = NULL;
  CvRect leftR, rightR;
  bool first = true;

  while (1) {
    frame = cvQueryFrame(capture);
    if (!frame) break;

    if (first) {
      leftWriter = cvCreateVideoWriter("C:\\Materials\\6l.avi", CV_FOURCC('D','I','V','X'),fps,cvSize(frame->width/2, frame->height));
      rightWriter = cvCreateVideoWriter("C:\\Materials\\6r.avi", CV_FOURCC('D','I','V','X'),fps,cvSize(frame->width/2, frame->height));
      first = false;
    }
    
    leftR = cvRect(0, 0, frame->width/2, frame->height);
    rightR = cvRect(frame->width/2, 0, frame->width/2, frame->height);
    
    cvSetImageROI(frame, leftR);
    if (left) cvReleaseImage(&left);
    left = cvCreateImage(cvGetSize(frame), frame->depth, frame->nChannels);
    cvCopy(frame, left);
    cvWriteFrame(leftWriter, left);
    cvResetImageROI(frame);

    cvSetImageROI(frame, rightR);
    if (right) cvReleaseImage(&right);
    right = cvCreateImage(cvGetSize(frame), frame->depth, frame->nChannels);
    cvCopy(frame, right);
    cvWriteFrame(rightWriter, right);
    cvResetImageROI(frame);
  }

  cvReleaseVideoWriter(&leftWriter);
  cvReleaseVideoWriter(&rightWriter);
  cvReleaseCapture(&capture);
  cvReleaseImage(&frame);
  cvReleaseImage(&left);
  cvReleaseImage(&right);

  printf("Done\n");
  return 0;
}