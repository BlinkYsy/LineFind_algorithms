#pragma once

#include <opencv2/core.hpp>

#include "line_detection_types.h"

class LineDetectionOperator {
public:
    LineDetectionResult Detect(
        const cv::Mat& image,
        const LineDetectionFrame& frame,
        const LineDetectionParams& params) const;

    LineDetectionResult DetectGray(
        const cv::Mat& grayImage,
        const LineDetectionFrame& frame,
        const LineDetectionParams& params) const;

    LineDetectionResult Detect(
        const cv::Mat& image,
        const std::vector<LineCaliper>& calipers,
        const LineDetectionParams& params) const;

    LineDetectionResult DetectGray(
        const cv::Mat& grayImage,
        const std::vector<LineCaliper>& calipers,
        const LineDetectionParams& params) const;

};
