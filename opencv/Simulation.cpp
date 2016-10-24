#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <opencv2/legacy/legacy.hpp>
#include <boost/random.hpp>
#include <boost/format.hpp>
#include "KAZE.h"
#include "config.h"
#include "utils.h"

cv::Mat translate(const cv::Mat& img, cv::Mat& dst, double angle, double scale, int noise_power, double blur_sigma)
{
    const int width_rot  = scale * std::abs(img.rows * std::cos(angle) + img.cols * std::sin(angle));
    const int height_rot = scale * std::abs(img.rows * std::sin(angle) + img.cols * std::cos(angle));
    cv::Mat m = cv::getRotationMatrix2D(cv::Point2f(img.cols / 2.0, img.rows / 2.0), angle, scale);
    m.at<double>(0, 2) += img.cols - img.cols / 2.0;
    m.at<double>(1, 2) += img.rows - img.rows / 2.0;
    cv::warpAffine(img, dst, m, cv::Size(img.cols * 2, img.rows * 2));

    //white noise
    if(noise_power)
    {
        boost::mt19937 rng;
        for(int y = 0; y < dst.rows; ++y)
            for(int x = 0; x < dst.cols; ++x)
            {
                const int c = dst.at<unsigned char>(y, x) + 
                    static_cast<int>(rand() % (2 * noise_power) - noise_power);
                dst.at<unsigned char>(y, x) = std::min(255, std::max(0, c));
            }
    }

    if(0 < blur_sigma)
    {
        cv::GaussianBlur(dst, dst, cv::Size(0, 0), blur_sigma);
    }

    return m;
}

toptions get_default_toptions(int w, int h)
{
    toptions options;
    options.soffset = DEFAULT_SCALE_OFFSET;
    options.omax = DEFAULT_OCTAVE_MAX;
    options.nsublevels = DEFAULT_NSUBLEVELS;
    options.dthreshold = DEFAULT_DETECTOR_THRESHOLD;
    options.diffusivity = DEFAULT_DIFFUSIVITY_TYPE;
    options.descriptor = DEFAULT_DESCRIPTOR_MODE;
    options.upright = DEFAULT_UPRIGHT;
    options.extended = DEFAULT_EXTENDED;
    options.sderivatives = DEFAULT_SIGMA_SMOOTHING_DERIVATIVES;
    options.save_scale_space = DEFAULT_SAVE_SCALE_SPACE;
    options.show_results = DEFAULT_SHOW_RESULTS;
    options.save_keypoints = DEFAULT_SAVE_KEYPOINTS;
    options.verbosity = DEFAULT_VERBOSITY;
    options.img_width = w;
    options.img_height = h;
    return options;
}


const float DRATIO = .6;		// NNDR Matching value
float Compute_Descriptor_Distance(Ipoint &p1, Ipoint &p2, float best)
{
    float dist = 0.0;
    int dsize = p1.descriptor_size;

    for(int i = 0; i < dsize; i++ )
    {
        dist += pow(p1.descriptor[i] - p2.descriptor[i],2);

        if( dist > best )
            break;
    }

    return dist;

} 

unsigned int Matching_Descriptor(std::vector<Ipoint> &ipts1, std::vector<Ipoint> &ipts2, std::vector<int> &indexes )
{
    float dist = 0.0, mind = 0.0, last_mind = 0.0;
    int mindex = -1;
    unsigned int correct_matches = 0;
    bool first = false;

    indexes.clear();

    for( unsigned int i = 0; i < ipts1.size(); i++ )
    {
        mind = 10000.0;
        last_mind = 10000.0;
        mindex = -1;
        first = false;

        for( unsigned int j = 0; j < ipts2.size(); j++ )
        {
            dist = Compute_Descriptor_Distance(ipts1[i],ipts2[j],1000.0);

            if( dist < mind )
            {
                if( first == false )
                {	mind = dist;
                    mindex = j;
                    first = true;
                }
                else
                {
                    last_mind = mind;
                    mind = dist;
                    mindex = j;
                }
            }
            else if( dist < last_mind )
            {
                last_mind = dist;
            }
        }

        if( mind < DRATIO*last_mind )
        {
            indexes.push_back(i);
            indexes.push_back(mindex);
            correct_matches++;
        }
    }

    return correct_matches;
}


std::vector<cv::KeyPoint> convert_Ipoint_Keypoint(const std::vector<Ipoint>& kps)
{
    std::vector<cv::KeyPoint> result;
    for(std::vector<Ipoint>::const_iterator p = kps.begin(); p != kps.end(); ++p)
        result.push_back(cv::KeyPoint(p->xf, p->yf, p->scale));
    return result;
}

std::vector<cv::DMatch> convert_KAZEMatch_DMatch(const std::vector<int>& match)
{
    std::vector<cv::DMatch> result;
    for(int i = 0; i < match.size(); i += 2)
        result.push_back(cv::DMatch(match[i], match[i + 1], 0));   //distanceはdummy
    return result;
}


void evaluation(const std::vector<cv::KeyPoint>& kp1, const std::vector<cv::KeyPoint>& kp2, const std::vector<cv::DMatch>& match, const cv::Mat& trans_mat)
{
    const double permit_err = 3.0;

    int good_cnt = 0, bad_cnt = 0;
    for(std::vector<cv::DMatch>::const_iterator p = match.begin(); p != match.end(); ++p)
    {
        const cv::KeyPoint src = kp1[p->queryIdx];
        const cv::KeyPoint dst = kp2[p->trainIdx];
        const double x = trans_mat.at<double>(0, 0) * src.pt.x + trans_mat.at<double>(0, 1) * src.pt.y + trans_mat.at<double>(0, 2);
        const double y = trans_mat.at<double>(1, 0) * src.pt.x + trans_mat.at<double>(1, 1) * src.pt.y + trans_mat.at<double>(1, 2);
        const double dx = x - dst.pt.x;
        const double dy = y - dst.pt.y;
        if(dx * dx + dy * dy < permit_err * permit_err)
            ++good_cnt;
        else
            ++bad_cnt;
    }
    std::cout << "total: " << match.size();
    std::cout << boost::format(", correct: %d (%d%%)") % good_cnt % (100 * good_cnt / match.size());
    std::cout << boost::format(", miss: %d (%d%%)") % bad_cnt % (100 * bad_cnt / match.size());
    std::cout << std::endl;
}


int main(int argc, char *argv[])
{
    if(argc == 1)
    {
        std::cerr << "usage:" << std::endl;
        std::cerr << argv[0] << " imgfile" << std::endl;
        return -1;
    }


    //load source image as grayscale
    cv::Mat img_src = cv::imread(argv[1], 0);
    cv::Mat img_src_32, img_dst, img_dst_32, img_match_sift, img_match_kaze;

    //initialize
    img_src.convertTo(img_src_32, CV_32F, 1.0/255.0,0);

    //initialize SIFT feature detector descriptor
    cv::SiftFeatureDetector sift_detector;
    cv::SiftDescriptorExtractor sift_extractor;
    cv::BruteForceMatcher<cv::L2<float> > matcher;

    //SIFT feature extraction from source image
    std::vector<cv::KeyPoint> sift_kp_src;
    sift_detector.detect(img_src, sift_kp_src);
    cv::Mat sift_src;
    sift_extractor.compute(img_src, sift_kp_src, sift_src);

    //initialize KAZE feature detector descriptor
    toptions kazeopt_src = get_default_toptions(img_src.cols, img_src.rows);
    KAZE kazeevol_src(kazeopt_src);

    //KAZE feature extraction from source image
    kazeevol_src.Create_Nonlinear_Scale_Space(img_src_32);
    std::vector<Ipoint> kaze_kp_src;
    kazeevol_src.Feature_Detection(kaze_kp_src);
    kazeevol_src.Feature_Description(kaze_kp_src);

    translate(img_src, img_dst, 0, 1.0, 0, 0);
    toptions kazeopt_dst = get_default_toptions(img_dst.cols, img_dst.rows);
    KAZE kazeevol_dst(kazeopt_dst);

    double rot = 0.0;
    double scale = 1.0;
    int noise = 0;
    double blur = 0;
    int key;
    while(key = cv::waitKey(10))
    {
        bool show = true;
        if(key == 65362) scale = std::min(scale + 0.1, 1.5);
        else if(key == 65364) scale = std::max(scale - 0.1, 0.5);
        else if(key == 65361) rot += 5;
        else if(key == 65363) rot -= 5;
        else if(key == 'z') noise = std::min(noise + 5, 50);
        else if(key == 'x') noise = std::max(noise - 5, 0);
        else if(key == 'c') blur = std::min(blur + 0.5, 20.0);
        else if(key == 'v') blur = std::max(blur - 0.5, 0.0);
        else show = false;

        if(show)
        {
            std::cout << "**********" << std::endl;
            std::cout << "scale factor : " << scale << std::endl;
            std::cout << "rotation : " << rot << " degree" << std::endl;
            std::cout << "white noise max power : " << noise << std::endl;
            std::cout << "gaussian blur sigma : " << blur << std::endl;
        }

        const cv::Mat m = translate(img_src, img_dst, rot, scale, noise, blur);

        //feature extraction from destination image
        std::vector<cv::KeyPoint> sift_kp_dst;
        sift_detector.detect(img_dst, sift_kp_dst);
        cv::Mat sift_dst;
        sift_extractor.compute(img_dst, sift_kp_dst, sift_dst);

        //match SIFT
        cv::vector<cv::DMatch> corr;
        matcher.match(sift_src, sift_dst, corr);
        cv::drawMatches(img_src, sift_kp_src, img_dst, sift_kp_dst, corr, img_match_sift);
        cv::putText(img_match_sift, "SIFT", cv::Point(30, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 3);

        //initialize KAZE feature detector descriptor
        img_dst.convertTo(img_dst_32, CV_32F, 1.0/255.0,0);

        //KAZE feature extraction from source image
        kazeevol_dst.Create_Nonlinear_Scale_Space(img_dst_32);
        std::vector<Ipoint> kaze_kp_dst;
        kazeevol_dst.Feature_Detection(kaze_kp_dst);
        kazeevol_dst.Feature_Description(kaze_kp_dst);

        //match KAZE
        std::vector<int> kaze_corr;
        Matching_Descriptor(kaze_kp_src, kaze_kp_dst, kaze_corr);

        //draw KAZEmatch
        const std::vector<cv::DMatch> kaze_corr2 = convert_KAZEMatch_DMatch(kaze_corr);
        const std::vector<cv::KeyPoint> kaze_kp1 = convert_Ipoint_Keypoint(kaze_kp_src);
        const std::vector<cv::KeyPoint> kaze_kp2 = convert_Ipoint_Keypoint(kaze_kp_dst);
        cv::drawMatches(img_src, kaze_kp1, img_dst, kaze_kp2, kaze_corr2, img_match_kaze);
        cv::putText(img_match_kaze, "KAZE", cv::Point(30, 30), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 255), 3);

        cv::Mat result;
        cv::Mat src[] = {img_match_sift, img_match_kaze};
        cv::vconcat(src, 2, result);

        cv::imshow("hoge", result);

        if(show)
        {
            std::cout << "SIFT:";
            evaluation(sift_kp_src, sift_kp_dst, corr, m);

            std::cout << "KAZE:";
            evaluation(kaze_kp1, kaze_kp2, kaze_corr2, m);
        }
    }
}
