#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

#define OUT_IMG_WIDTH 331
#define OUT_IMG_HEIGHT 100

#define N_COLUMNS 12
#define KEYPOINTS_PER_COLUMN 4

#define Y_INTERVAL_PTS (OUT_IMG_HEIGHT / (KEYPOINTS_PER_COLUMN - 1))
#define X_INTERVAL_PTS (OUT_IMG_WIDTH / (N_COLUMNS - 1))

struct Point {
	int x;
	int y;
};

const static Point keypoints[] = {
	{2022, 2460},
    {1944, 2706},
    {1836, 3000},
    {1752, 3270},
    {1734, 2244},
    {1560, 2424},
    {1296, 2646},
    {1074, 2820},
    {1590, 1902},
    {1344, 1956},
    {1014, 2040},
    {702,  2094},
    {1644, 1524},
    {1362, 1452},
    {1050, 1344},
    {762,  1260},
    {1762, 1296},
    {1602, 1128},
    {1368, 900},
    {1182, 588},
    {2082, 1164},
    {2028, 888},
    {1962, 528},
    {1878, 182},
    {2448, 1188},
    {2514, 924},
    {2598, 516},
    {2706, 216},
    {2754, 1278},
    {2934, 1128},
    {3186, 882},
    {3360, 612},
    {2892, 1482},
    {3138, 1416},
    {3462, 1308},
    {3750, 1224},
    {2910, 1890},
    {3162, 1950},
    {3522, 2028},
    {3834, 2070},
    {2796, 2238},
    {3006, 2442},
    {3258, 2634},
    {2492, 2796},
    {2508, 2478},
    {2616, 2718},
    {2748, 2988},
    {2874, 3252},
};

// Output image that pixels will be put into
cv::Mat out_img(OUT_IMG_HEIGHT, OUT_IMG_WIDTH, CV_8UC3, cv::Scalar::all(0));

// Columns
Point col1[OUT_IMG_HEIGHT];
Point col2[OUT_IMG_HEIGHT];

// Pointers to each column so we can efficiently switch between them
Point *c1 = col1, *c2 = col2;

// Allocates memory, must be freed by caller
std::vector<Point> bresenhams2(Point p1, Point p2);

int main(int argc, char** argv)
{
	if (argc < 2) {
		printf("Usage:\n    %s [image-file]\n", argv[0]);
		exit(1);
	}

	// Read input image
	cv::Mat img = cv::imread(argv[1], cv::IMREAD_ANYCOLOR);
	if (!img.data) {
		fprintf(stderr, "[error]: could not read image data\n");
		exit(1);
	}

    // Set output display properties
    cv::namedWindow("Out img", cv::WINDOW_NORMAL);

    // Explicitly fill first column
	for (int i = 0; i < KEYPOINTS_PER_COLUMN - 1; ++i) {
		Point k1 = keypoints[i];
		Point k2 = keypoints[i+1];

        // Interpolate
		auto pts = bresenhams2(k1, k2);

        // Subsample
		for (int j = 0, k = 0;
			 j < pts.size() && k < Y_INTERVAL_PTS;
			 j += (pts.size() / Y_INTERVAL_PTS), k++) {
			int idx = Y_INTERVAL_PTS * i + k;
			c1[idx] = pts[j];
			assert(idx < OUT_IMG_HEIGHT && "idx must be < OUT_IMG_HEIGHT");
			out_img.at<cv::Vec3b>(idx, 0) = img.at<cv::Vec3b>(c1[idx].y, c1[idx].x);
		}
	}
	// Need to explicitly add the last point
	c1[OUT_IMG_HEIGHT - 1] = keypoints[KEYPOINTS_PER_COLUMN - 1];

	// Write to out_img
	for (int i = 0; i < OUT_IMG_HEIGHT; ++i) {
		out_img.at<cv::Vec3b>(i, 0) = img.at<cv::Vec3b>(c1[i].y, c1[i].x);
	}

    // Repeat for rest of columns
    for (int pair_idx = 1; pair_idx < N_COLUMNS; ++pair_idx) {
        // Fill second column
	    for (int i = 0; i < KEYPOINTS_PER_COLUMN - 1; ++i) {
	    	Point k1 = keypoints[i + KEYPOINTS_PER_COLUMN * pair_idx];
	    	Point k2 = keypoints[i + KEYPOINTS_PER_COLUMN * pair_idx + 1];

            // Interpolate
	    	auto pts = bresenhams2(k1, k2);

            // Subsample
	    	for (int j = 0, k = 0;
	    		 j < pts.size() && k < Y_INTERVAL_PTS;
	    		 j += (pts.size() / Y_INTERVAL_PTS), ++k) {
	    		int idx = Y_INTERVAL_PTS * i + k;
	    		assert(idx < OUT_IMG_HEIGHT && "idx must be < OUT_IMG_HEIGHT");
	    		c2[idx] = pts[j];
	    	}
	    }
        // Add last point explicitly
	    c2[OUT_IMG_HEIGHT - 1] = keypoints[KEYPOINTS_PER_COLUMN * pair_idx - 1];

	    // Write second column to img
        
	    for (int i = 0; i < OUT_IMG_HEIGHT; ++i) {
            assert(X_INTERVAL_PTS * pair_idx < OUT_IMG_WIDTH);
	    	out_img.at<cv::Vec3b>(i, X_INTERVAL_PTS * pair_idx) = img.at<cv::Vec3b>(c2[i].y, c2[i].x);
	    }
        cv::imshow("Out img", out_img);
        cv::waitKey(0);

        // Interpolate between both columns
        for (int i = 0; i < OUT_IMG_HEIGHT; ++i) {
            auto pts = bresenhams2(c1[i], c2[i]);

            // Subsample
            for (int j = 0, k = 0;
                 j < pts.size() && k < X_INTERVAL_PTS;
                 j += (pts.size() / X_INTERVAL_PTS), ++k) {
                out_img.at<cv::Vec3b>(i, X_INTERVAL_PTS * (pair_idx - 1) + k) = img.at<cv::Vec3b>(pts[j].y, pts[j].x);
            }
        }
        cv::imshow("Out img", out_img);
        cv::waitKey(0);
        
        // Swap c1, c2 so we don't have to refill the first column
        Point *tmp = c1;
        c1 = c2;
        c2 = tmp;
    }
}

std::vector<Point> bresenhams2(Point p1, Point p2)
{
    int dx = p2.x - p1.x;
    const char incx = (dx > 0) ? 1 : -1;
    dx = abs(dx) << 1;

    int dy = p2.y - p1.y;
    const char incy = (dy > 0) ? 1 : -1;
    dy = abs(dy) << 1;

    auto pts = std::vector<Point>();
    pts.push_back(p1);

    int x = p1.x, y = p1.y;
    if (dx >= dy) {
        int error = dy - (dx >> 1);
        while (x != p2.x) {
            if (error >= 0 && (error || (incx > 0))) {
                error -= dx;
                y += incy;
            }

            error += dy;
            x += incx;
            Point p = {x, y};
            pts.push_back(p);
        }
    } else {
        int error = dx - (dx >> 1);
        while (y != p2.y) {
            if (error >= 0 && (error || (incy > 0))) {
                error -= dy;
                x += incx;
            }

            error += dx;
            y += incy;
            Point p = {x, y};
            pts.push_back(p);
        }
    }

    return pts;
}
