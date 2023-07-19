#include <iostream>
#include <opencv2/opencv.hpp>
#include <cmath>

using namespace std;
using namespace cv;

// Tính histogram của ảnh
void calculateHistogram(const Mat& image, vector<int>& histogram)
{
    histogram.resize(256, 0);

    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            int pixelValue = image.at<uchar>(i, j);
            histogram[pixelValue]++;
        }
    }
}

// Hiển thị histogram
void showHistogram(const vector<int>& histogram)
{
    int histWidth = 512;
    int histHeight = 400;
    int binWidth = cvRound(static_cast<double>(histWidth) / histogram.size());

    Mat histogramImage(histHeight, histWidth, CV_8UC1, Scalar(255));

    int maxCount = *max_element(histogram.begin(), histogram.end());
    for (int i = 0; i < histogram.size(); i++)
    {
        int binHeight = cvRound(static_cast<double>(histogram[i]) / maxCount * histHeight);
        rectangle(histogramImage, Point(i * binWidth, histHeight - binHeight), Point((i + 1) * binWidth, histHeight), Scalar(0), -1);
    }

    imshow("Histogram", histogramImage);
}

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

    // Tìm giá trị lớn nhất trong ảnh (r_max)
    int r_max = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            int pixelValue = image.at<uchar>(i, j);
            if (pixelValue > r_max)
                r_max = pixelValue;
        }
    }

    // Hằng số c cho biến đổi log
    double c = 255 / log(1 + r_max);

    // Thực hiện biến đổi log
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            // Lấy giá trị pixel tại vị trí (i, j)
            int pixelValue = image.at<uchar>(i, j);

            // Tính giá trị log mới
            int newPixelValue = c * log(1 + pixelValue);

            // Đảm bảo giá trị mới nằm trong khoảng [0, 255]
            newPixelValue = min(max(newPixelValue, 0), 255);

            // Gán giá trị mới cho pixel trong ảnh biến đổi
            transformed_image.at<uchar>(i, j) = newPixelValue;
        }
    }

    // Tính và hiển thị histogram của ảnh gốc
    vector<int> histogram_original;
    calculateHistogram(image, histogram_original);
    showHistogram(histogram_original);

    // Tính và hiển thị histogram của ảnh sau khi biến đổi
    vector<int> histogram_transformed;
    calculateHistogram(transformed_image, histogram_transformed);
    showHistogram(histogram_transformed);

    // Hiển thị ảnh gốc và ảnh sau khi biến đổi
    imshow("Ảnh gốc", image);
    imshow("Ảnh sau khi biến đổi", transformed_image);
    waitKey(0);

    return 0;
}