#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <memory>

using namespace std;


class GN
{
public:
    cv::Mat e_, a_, b_, j_; // error, matrix A, vector B, Jacobian
    cv::Mat gx_, gy_; // Gradients
    cv::Mat gxx_, gxy_, gyx_, gyy_; // Gradients * (X или Y)
    cv::Mat t_; // Affine transformation matrix
    inline void reset() { t_ = cv::Mat::eye(2, 3, CV_64F);}
    inline void scaleBy(double s)
    {
        t_.at<double>(0, 2) *= s;
        t_.at<double>(1, 2) *= s;
    }

    template<class T1, class T2 = T1> static inline double scalMul(const cv::Mat & m1, const cv::Mat & m2)
    {
        assert(m1.rows == m2.rows && m2.cols == m2.cols);
        double sum = 0;
        const T1 * a = (const T1 *) m1.data;
        const T2 * b = (const T2 *) m2.data;
        for(const T1 * end = (const T1 *)m1.dataend; a < end; a++, b++)
            sum += double(*a) * double(*b);
        return sum;
    }
    template<class Ts, class Td> static void mulByX(const cv::Mat & src, cv::Mat & dst)
    {
        assert(src.rows == dst.rows && src.cols == dst.cols);
        const Ts * s = (const Ts *) src.data;
        Td * d = (Td *) dst.data;
        for(int h = src.rows, w = src.cols; h--; )
            for(int x = 0; x < w; x++)
                *(d++) = (*(s++) * x);// / ((w >> 4) + 1);
    }
    template<class Ts, class Td> static void mulByY(const cv::Mat & src, cv::Mat & dst)
    {
        assert(src.rows == dst.rows && src.cols == dst.cols);
        const Ts * s = (const Ts *) src.data;
        Td * d = (Td *) dst.data;
        for(int y = 0, h = src.rows, w = src.cols; y < h; y++)
            for(int x = w; x--; )
                *(d++) = (*(s++) * y);// / ((h >> 4) + 1);
    }

    inline cv::Mat calcShiftStep(const cv::Mat & i1, const cv::Mat & i2, const cv::Mat & mask)
    {
        const int ks = 32, ks2 = ks * ks;
        cv::Sobel(i2, gx_, CV_16S, 1, 0, CV_SCHARR);
        cv::Sobel(i2, gy_, CV_16S, 0, 1, CV_SCHARR);
        a_ = cv::Mat(2, 2, CV_64F);
        a_.at<double>(0, 0) = scalMul<int16_t>(gx_, gx_) / ks2;
        a_.at<double>(1, 1) = scalMul<int16_t>(gy_, gy_) / ks2;
        a_.at<double>(0, 1) = a_.at<double>(1, 0) = scalMul<int16_t>(gx_, gy_) / ks2;

        cv::subtract(i2, i1, e_, cv::noArray(), CV_16S);
        cv::multiply(e_, mask, e_, 1, CV_16S);

        b_ = cv::Mat(2, 1, CV_64F);
        b_.at<double>(0, 0) = scalMul<int16_t>(gx_, e_) / (100 * ks);
        b_.at<double>(1, 0) = scalMul<int16_t>(gy_, e_) / (100 * ks);

        cv::Mat du;
        cv::solve(a_, b_, du);
        cv::Mat dt = cv::Mat::eye(2, 3, CV_64F);
        dt.at<double>(0, 2) = du.at<double>(0, 0);
        dt.at<double>(1, 2) = du.at<double>(1, 0);
        return dt;
    }
    inline cv::Mat calcAffineStep(const cv::Mat & f0, const cv::Mat & f1, const cv::Mat & mask)
    {
        // Calculate gradients
        const double ks = 1.0 / 32, ks2 = ks * ks;
        cv::Mat gx, gy;
        cv::Sobel(f1, gx, CV_16S, 1, 0, CV_SCHARR);
        cv::Sobel(f1, gy, CV_16S, 0, 1, CV_SCHARR);
        gx.convertTo(gx_, CV_32S);
        gy.convertTo(gy_, CV_32S);

        // Calculate gradients multiplied by pos
        gxx_ = cv::Mat(f1.rows, f1.cols, CV_32S);
        gxy_ = cv::Mat(f1.rows, f1.cols, CV_32S);
        gyx_ = cv::Mat(f1.rows, f1.cols, CV_32S);
        gyy_ = cv::Mat(f1.rows, f1.cols, CV_32S);
        mulByX<int32_t, int32_t>(gx_, gxx_);
        mulByY<int32_t, int32_t>(gx_, gxy_);
        mulByX<int32_t, int32_t>(gy_, gyx_);
        mulByY<int32_t, int32_t>(gy_, gyy_);

        // Jacobian vector
        cv::Mat * j[6] =
        {
            &gxx_, &gxy_, &gx_,
            &gyx_, &gyy_, &gy_
        };

        // Calculate matrix A = j ^ 2
        a_ = cv::Mat(6, 6, CV_64F);
        for(int x = 0; x < 6; x++) for(int y = 0; y < 6; y++)
            a_.at<double>(y, x) = scalMul<int32_t>(*j[x], *j[y]) * ks2;

        // Calculate error
        cv::subtract(f1, f0, e_, cv::noArray(), CV_16S);
        cv::multiply(e_, mask, e_, 1, CV_16S);

        // Calculate vector B
        b_ = cv::Mat(6, 1, CV_64F);
        for(int y = 0; y < 6; y++)
            b_.at<double>(y, 0) = scalMul<int32_t, int16_t>(*j[y], e_) * (ks / 100);

        // Calculate step
        cv::Mat dt;
        cv::solve(a_, b_, dt);
        dt.rows = 2;
        dt.cols = 3;
        return dt;
    }

    inline void test1()
    {
        int w = 20, h = 20;
        cv::Mat a(h, w, CV_8U), b;
        uint8_t * p = a.data;
        for(int y = 0; y < h; y++) for(int x = 0; x < w; x++)
            *(p++) = x * (w - x) + 2 * y;
        cv::Mat t = cv::Mat::eye(2, 3, CV_64F);
        t.at<double>(0, 2) = 2;

        for(int x = 0; x < 10; x++)
        {
            cv::warpAffine(a, b, t, cv::Size(h, w));
            cv::Mat du = calcShiftStep(a, b, a);
            cout << "!!! iteration " << x + 1 << endl;
            //cout << "gx = " << endl << gx_ << endl << endl;
            //cout << "gy = " << endl << gy_ << endl << endl;
            cout << "t = " << endl << t << endl << endl;
            cout << "a = " << endl << a_ << endl << endl;
            cout << "b = " << endl << b_ << endl << endl;
            cout << "du = " << endl << du << endl << endl;
            t.at<double>(0, 2) += du.at<double>(0, 0);
            t.at<double>(1, 2) += du.at<double>(1, 0);
        }
    }
    inline void test2()
    {
        int w = 10, h = 10;
        cv::Mat a(h, w, CV_8U), b;
        uint8_t * p = a.data;
        for(int y = 0; y < h; y++) for(int x = 0; x < w; x++)
            *(p++) = x * (w - x) + 2 * y;
        cv::Mat t = cv::Mat::eye(2, 3, CV_64F);
        t.at<double>(0, 2) = 2;

        for(int x = 0; x < 3; x++)
        {
            cv::warpAffine(a, b, t, cv::Size(h, w));
            cv::Mat du = calcAffineStep(a, b, b);
            cout << "!!! iteration " << x + 1 << endl;
            cout << "gx = " << endl << gx_ << endl << endl;
            cout << "gy = " << endl << gy_ << endl << endl;
            cout << "t = " << endl << t << endl << endl;
            cout << "e = " << cv::norm(e_) << endl;
            cout << "a = " << endl << a_ << endl << endl;
            cout << "b = " << endl << b_ << endl << endl;
            cout << "du = " << endl << du << endl << endl;

            t += du;
        }
    }
    bool demo(const cv::Mat & a, const cv::Mat & b, cv::Mat & out)
    {
        std::vector<cv::Mat> v = {a, b, b};
        cv::merge(v, out);

        int h = a.rows, w = a.cols;
        cv::Mat whiteBox(a.rows, a.cols, CV_8U, cv::Scalar(100)), mask;
        double e = 1E10;
        cv::Mat optT = t_.clone();
        double step = 1.0;
        for(int x = 0; x < 20; x++)
        {
            cv::Mat bt;
            cv::warpAffine(b, bt, t_, cv::Size(w, h), cv::INTER_LINEAR, cv::BORDER_CONSTANT, cv::Scalar(255));
            cv::warpAffine(whiteBox, mask, t_, cv::Size(w, h));
            cv::Mat du = calcAffineStep(a, bt, mask);


            double te = cv::norm(e_);
            if(te >= e)
            {
                optT.copyTo(t_);
                step *= 0.3;
                if(step > 0.05) continue;
                if(e / e_.total() > 150)
                {
                    cv::vconcat(out, cv::Mat(h, w, CV_8UC3, cv::Scalar(0, 0, 255)), out);
                    return false;
                }
                return true;
            }
            std::vector<cv::Mat> v = {a, bt, bt};
            cv::merge(v, bt);
            //if(!x) bt.copyTo(out);
            cv::vconcat(out, bt, out);

            t_.copyTo(optT);
            e = te;
            t_ += du * step;
        }
        return true;
    }
};



class Frame
{
public:
    std::vector<cv::Mat> pyramid;
    Frame(const cv::Mat & frame, int count = 5)
    {
        pyramid.resize(count);
        cv::cvtColor(frame, pyramid[0], CV_BGR2GRAY);
        int w = pyramid[0].cols, h = pyramid[0].rows;

        for(int l = 1; l < count; l++)
        {
            pyramid[l] = cv::Mat(h >> 1, w >> 1, CV_8U);
            uint8_t * dst = pyramid[l].data;//, * end = dst + ((w * h) >> 2) - 1;
            const uint8_t * src = pyramid[l - 1].data;
            for(int y = (h >> 1); y--;)
            {
                for(int x = (w >> 1); x--;)
                {
                    *(dst++) = (src[0] + src[1] + src[w] + src[w + 1]) >> 2;
                    src += 2;
                }
                src += w;
            }
            //assert(src == pyramid[l - 1].data + w * h);
            w >>= 1;
            h >>= 1;
        }
    }
};

int main(int argc, char *argv[])
{
    //gradTest();
    cv::VideoCapture cap(0); // open the default camera
    if(!cap.isOpened())  // check if we succeeded
        return -1;
    std::unique_ptr<Frame> prev;
    cv::Mat map;
    cv::Point pos(0, 0);
    int pyrct = 7;
    bool updPrev = true;
    bool pause = false;
    GN gnn;
    gnn.test2();
    for(;;)
    {
        cv::Mat frame, res;
        cap >> frame; // get a new frame from camera
        //cv::cvtColor(frame, res, CV_BGR2GRAY);

        std::unique_ptr<Frame> f(new Frame(frame, pyrct));
        //GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        //Canny(edges, edges, 0, 30, 3);
        if(prev != nullptr && !pause)
        {
            int lvl = 5;
            const cv::Mat & i1 = prev->pyramid[lvl];
            const cv::Mat & i2 = f->pyramid[lvl];
            cv::Mat r;
            std::vector<cv::Mat> v = {i1, i2, i2};
            cv::merge(v, r);
            cv::Mat out, all;
            gnn.reset();
            while(gnn.demo(prev->pyramid[lvl], f->pyramid[lvl], out) && lvl > 1)
            {
                if(all.empty()) all = out;
                else
                {
                    if(out.rows > all.rows) cv::vconcat(all, cv::Mat(out.rows - all.rows, all.cols, CV_8UC3, cv::Scalar(0, 0, 0)), all);
                    else if(all.rows > out.rows) cv::vconcat(out, cv::Mat(all.rows - out.rows, out.cols, CV_8UC3, cv::Scalar(0, 0, 0)), out);
                    cv::hconcat(all, out, all);
                }
                lvl--;
                gnn.scaleBy(2);
            }
            if(all.empty()) all = out;
            cv::imshow("all", all);

        }
        char k = cv::waitKey(1);
        if(k == 'i')
            updPrev = !updPrev;
        if(k == 'p')
            pause = !pause;
        if(k == 'q') break;
        if(updPrev)
        {
            prev = std::move(f);
        }
    }
    return 0;
}
