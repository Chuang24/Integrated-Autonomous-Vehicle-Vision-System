#include <opencv2/opencv.hpp>
#include <iostream>
#include <opencv2/core/utility.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include <cstring>
using namespace std;
using namespace cv;

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
	//open the video file for reading
	VideoCapture cap(0);
	//VideoCapture cap("C:/working footage/Cars On The Road.mp4");
	//VideoCapture cap(0);
	// if not success, exit program
	if (cap.isOpened() == false)
	{
		cout << "Cannot open the video file" << endl;
		cin.get(); //wait for any key press
		return -1;
	}

	//Uncomment the following line if you want to start the video in the middle
	cap.set(CAP_PROP_POS_MSEC, 300); 

	// declares all required variables
	Rect2d roi;
	Mat frame;

	//get the frames rate of the video
	double fps = cap.get(CAP_PROP_FPS);
	cout << "Frames per seconds : " << fps << endl;

	 //create a tracker object
	Ptr<Tracker> tracker = TrackerCSRT::create();

	// get bounding box
	cap >> frame;
	roi = selectROI("tracker", frame);
	//roi = {481,332,86,66 };
	//roi = { 468,317,116,99 };
	//initialize the tracker
	tracker->init(frame, roi);

	// perform the tracking process
	printf("Start the tracking process, press ESC to quit.\n");
	for (;; ) {
		// get frame from the video
		cap >> frame;
		// stop the program if no more images
		if (frame.rows == 0 || frame.cols == 0)
			break;
		// update the tracking result
		tracker->update(frame, roi);
		// draw the tracked object
		rectangle(frame, roi, Scalar(255, 0, 0), 2, 1);
		// show image with the tracked object
		imshow("tracker", frame);
		//quit on ESC button
		if (waitKey(1) == 27)break;
	}
	return 0;
	
	
	String window_name = "My First Video";

	namedWindow(window_name, WINDOW_NORMAL); //create a window

	return 0;

}

