#include <iostream>
#include <C:/opencv/build/include/opencv2/imgproc.hpp>
#include <C:/opencv/build/include/opencv2/opencv_lib.hpp>
#include <C:/opencv/build/include/opencv2/opencv.hpp>
#include <C:/opencv/build/include/opencv2/highgui/highgui.hpp>



using namespace cv;
using namespace std;

int main(void)
{
	//映像の読み込み//

	uchar hue, sat, val; // Hue, Saturation, Valueを表現する変数
	Mat src_video(Size(640, 480), CV_8UC1, Scalar::all(255)); // サイズを指定する
	Mat smooth_video(Size(640, 480), CV_8UC1, Scalar::all(255)); // ノイズを除去した映像を保存する
	Mat hsv_video(Size(640, 480), CV_8UC1, Scalar::all(255)); // HSVに変換した映像を保存する
	Mat frame(Size(640, 480), CV_8UC1, Scalar::all(255));
	Mat dst_img(Size(640, 480), CV_8UC1, Scalar::all(0)); // 認識結果を表示する

	
	char windowName[] = "!";
	namedWindow(windowName, WINDOW_AUTOSIZE);//表示ウィンドウの設定
	char hsvwindow[] = "HSV変換結果";
	namedWindow(hsvwindow, WINDOW_AUTOSIZE);
	char dstwindow[] = "認識結果";
	namedWindow(dstwindow, WINDOW_AUTOSIZE);

	// 動画ファイルのパスの文字列を格納するオブジェクトを宣言する
	std::string filepath = "C:/Users/81901/Desktop/研究室/Project1/wave.mp4";
	// 動画ファイルを取り込むためのオブジェクトを宣言する
	cv::VideoCapture capture;
	// 動画ファイルを開く
	capture.open(filepath);
	if (capture.isOpened() == false) {
		// 動画ファイルが開けなかったときは終了する
		return 0;
	}

	/*VideoCapture capture(0);
	// カメラが使えない場合はプログラムを止める
	if (!capture.isOpened())
		return -1;*/

	
	while (waitKey(1) == -1)
	{
		dst_img = Scalar::all(0);
		// カメラから1フレーム取得する
		do {
			capture >> frame;
		} while (frame.empty());

		src_video = frame;
		imshow(windowName, src_video);

		// HSV表色系へ色情報を変換
		// 先にノイズを消しておく
		medianBlur(src_video, smooth_video, 5);
		cvtColor(smooth_video, hsv_video, COLOR_BGR2HSV);
		imshow(hsvwindow, hsv_video);

		// H,S,Vの要素に分割する
		for (int y = 0; y < hsv_video.rows; y++) {
			for (int x = 0; x < hsv_video.cols; x++) {
				hue = hsv_video.at<Vec3b>(y, x)[0];
				sat = hsv_video.at<Vec3b>(y, x)[1];
				val = hsv_video.at<Vec3b>(y, x)[2];
				// 色の検出
				if ((hue < 35 && hue > 20) && sat > 127) {
					dst_img.at<uchar>(y, x) = 255;
				}
				else {
					dst_img.at<uchar>(y, x) = 0;
				}
			}
		}
		imshow(dstwindow, dst_img);
	}
	destroyAllWindows();
	return 0;
}