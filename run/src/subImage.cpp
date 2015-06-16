#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/opencv.hpp"
#include <iostream>
#include <string>
#include <vector>

using namespace cv;
using namespace std;

#define KEYVALUEOFESC 27
#define KEYVALUEOFUP 0
#define KEYVALUEOFDOWN 1

static Mat g_img_src;
static Mat g_img_dst;
static Mat g_img_sub;
static bool g_is_rect_inited = false;
static Point g_rect_tl;
static string g_window_name = "Image";
static int subImageNum = 0;

static void onMouse( int event, int x, int y, int, void* )
{  
    if(CV_EVENT_LBUTTONDOWN == event){
        g_is_rect_inited = true;
        g_rect_tl = Point(x, y);    
    }
    else if (CV_EVENT_MOUSEMOVE == event && g_is_rect_inited){      
        g_img_src.copyTo(g_img_dst);
        rectangle(g_img_dst, g_rect_tl, Point(x,y), Scalar_<uchar>::all(200), 2, 5);
        imshow(g_window_name, g_img_dst); 
        g_is_rect_inited = true;
    }
    else if (CV_EVENT_LBUTTONUP == event && g_rect_tl != Point(x,y)){   
        g_img_src(Rect(g_rect_tl, Point(x,y))).copyTo(g_img_sub);
        subImageNum++;
        string name = string("../subImage/subImage_") + to_string(subImageNum) + string(".jpg");
        imwrite(name, g_img_sub);
        g_is_rect_inited = false;
    }
}

void Info(const string &msg) {
    cout << msg << endl;
}

Mat readImage(string &filename) {
    Mat img = imread(filename, CV_LOAD_IMAGE_GRAYSCALE);  // Load the gray image
    if (img.empty()){
        Info("[ERROR] : please check your image file name.");
        exit(0);
    }

    return img;
}

Mat resizeImage(Mat &image) {
    int width = image.size().width;
    int height = image.size().height;

    Mat dst;
    double scale = min(10.0, width / 600.0);
    resize(image, dst, Size(width * 1.0 / scale, height * 1.0 / scale));

    return dst;
}

void resetWindow(vector<string> &imageList, int imageIndex) {
    string filename = imageList[imageIndex];
    g_img_src = readImage(filename);
    g_img_src = resizeImage(g_img_src);
    g_window_name = filename;
    g_is_rect_inited = false;
    destroyAllWindows();
    namedWindow(g_window_name, CV_WINDOW_KEEPRATIO);
    setMouseCallback(g_window_name, onMouse, 0);
}

int main(int argc, char** argv){
    if (argc < 2) {
        Info("Enter with format ./main [image path list]");
        exit(0);
    }
    Info("Press Esc to quit!");

    int imageIndex = 0;
    vector<string> imageList;
    for (int i = 1; i < argc; ++i) {
        string fileName = string("../image/") + string(argv[i]);
        imageList.push_back(fileName);
    }

    resetWindow(imageList, imageIndex);

    while(true){
        imshow(g_window_name, g_img_src);
        int c = waitKey(0);
        if ((c & 255) == KEYVALUEOFESC){ // Esc
            destroyAllWindows();
            Info("Exiting ...");
            break;
        } else {
            if ((c & 255) == KEYVALUEOFUP) { // up
                imageIndex--;
                if (imageIndex < 0)
                    imageIndex = imageList.size() - 1;
                Info("Previous image...");
            } else if ((c & 255) == KEYVALUEOFDOWN) {  // down
                imageIndex++;
                imageIndex %= imageList.size();
                Info("Next image...");
            }
            resetWindow(imageList, imageIndex);
        }
    }

    return EXIT_SUCCESS;
}