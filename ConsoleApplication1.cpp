#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main()
{
    // Đọc ảnh từ file
    Mat image = imread("anime.jpg", IMREAD_GRAYSCALE);

    if (image.empty())
    {
        cout << "Không thể đọc ảnh!" << endl;
        return -1;
    }

    // Kích thước của ảnh
    int rows = image.rows;
    int cols = image.cols;

    // Tạo bản sao của ảnh gốc để thực hiện biến đổi
    Mat transformed_image = image.clone();

    // Thực hiện biến đổi ảnh âm bản
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            // Lấy giá trị pixel tại vị trí (i, j)
            int pixelValue = image.at<uchar>(i, j);

            // Tính giá trị âm bản mới
            int newPixelValue = 255 - pixelValue;

            // Gán giá trị âm bản mới cho pixel trong ảnh biến đổi
            transformed_image.at<uchar>(i, j) = newPixelValue;
        }
    }

    // Hiển thị ảnh gốc và ảnh sau khi biến đổi
    imshow("Anh goc", image);
    imshow("Anh sau khi bien doi", transformed_image);
    waitKey(0);

    return 0;
}