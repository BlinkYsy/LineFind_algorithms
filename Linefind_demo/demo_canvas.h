#pragma once

#include <string>
#include <vector>

#include <opencv2/core.hpp>

#include "line_detection_operator.h"

class DemoCanvasApp {
public:
    explicit DemoCanvasApp(std::vector<std::string> sampleImages);

    int Run();

private:
    enum class CreateMode {
        None = 0,
        ArrowCaliper = 1,
        RotatedRectangle = 2,
    };

    enum class DragMode {
        None = 0,
        CreatingArrowAxis = 1,
        CreatingArrowLength = 2,
        CreatingArrowWidth = 3,
        CreatingFrame = 4,
        MovingFrame = 5,
        ResizingFrame = 6,
        MovingArrowGroup = 7,
        ResizingArrowStart = 8,
        ResizingArrowEnd = 9,
        ResizingArrowLength = 10,
        PanningImageView = 11,
    };

    enum class RoiKind {
        None = 0,
        ArrowCaliper = 1,
        RotatedFrame = 2,
    };

    enum class ButtonId {
        OpenImage = 0,
        NextSample = 1,
        CreateRect = 2,
        CreateRotated = 3,
        Detect = 4,
        ClearRoi = 5,
        ClearResult = 6,
    };

    struct Button {
        ButtonId id;
        std::string label;
        cv::Rect rect;
    };

    struct ParamControl {
        std::string label;
        cv::Rect rowRect;
        cv::Rect minusRect;
        cv::Rect valueRect;
        cv::Rect plusRect;
    };

    struct Viewport {
        cv::Rect panelRect;
        cv::Rect imageRect;
        cv::Rect drawRect;
        float scale = 1.0f;
        float baseScale = 1.0f;
    };

    struct ResizeState {
        float startLocalX = 0.0f;
        float startLocalY = 0.0f;
        LineDetectionFrame originalFrame;
        int signX = 1;
        int signY = 1;
    };

    struct ArrowCaliperRoi {
        cv::Point2f axisStart = cv::Point2f(0.0f, 0.0f);
        cv::Point2f axisEnd = cv::Point2f(0.0f, 0.0f);
        float caliperLength = 60.0f;
        float caliperWidth = 20.0f;
        bool axisReady = false;
        bool lengthReady = false;
    };

    static void OnMouseThunk(int event, int x, int y, int flags, void* userdata);

    void OnMouse(int event, int x, int y, int flags);
    void HandleKey(int key);
    void Render();

    void BuildLayout();
    void DrawSidebar(cv::Mat& canvas);
    void DrawImagePanel(cv::Mat& canvas);
    void DrawStatus(cv::Mat& canvas);
    void DrawPixelGrid(cv::Mat& imageCanvas) const;
    void DrawResultOverlay(cv::Mat& imageCanvas) const;
    void DrawFrame(cv::Mat& imageCanvas, const LineDetectionFrame& frame, const cv::Scalar& color, int thickness) const;
    void DrawRotatedFrameCalipers(cv::Mat& imageCanvas) const;
    void DrawArrowCaliperPreview(cv::Mat& imageCanvas) const;

    bool LoadImageFromPath(const std::string& path);
    bool OpenImageWithDialog();
    bool LoadNextSample();
    void DetectLine();
    void ClearResult();
    void ClearRoi();
    void ResetCreateMode(CreateMode mode);

    void StartArrowAxisCreate(const cv::Point2f& imagePoint);
    void UpdateArrowAxisCreate(const cv::Point2f& imagePoint);
    void StartArrowLengthCreate();
    void UpdateArrowLengthCreate(const cv::Point2f& imagePoint);
    void StartArrowWidthCreate();
    void UpdateArrowWidthCreate(const cv::Point2f& imagePoint);
    void FinishArrowWidthCreate();

    void StartFrameCreate(const cv::Point2f& imagePoint);
    void UpdateFrameCreate(const cv::Point2f& imagePoint);
    void FinishFrameCreate();

    bool HitTestImagePoint(int x, int y, cv::Point2f& imagePoint) const;
    bool HitTestInsideFrame(const cv::Point2f& imagePoint, const LineDetectionFrame& frame) const;
    bool HitTestResizeHandle(const cv::Point2f& imagePoint, const LineDetectionFrame& frame, int& signX, int& signY) const;
    bool HitTestArrowEndpoint(const cv::Point2f& imagePoint, bool& isStartHandle) const;
    bool HitTestArrowLengthHandle(const cv::Point2f& imagePoint) const;
    bool HitTestArrowAxis(const cv::Point2f& imagePoint) const;
    bool HitTestArrowCaliperBody(const cv::Point2f& imagePoint) const;
    cv::Point2f ScreenToImage(const cv::Point& screenPoint) const;
    cv::Point ImageToScreen(const cv::Point2f& imagePoint) const;
    cv::Point2f ToLocal(const LineDetectionFrame& frame, const cv::Point2f& imagePoint) const;

    void ApplySidebarClick(const cv::Point& point);
    void UpdateParameterFromControl(size_t paramIndex, bool increment);
    void ResetImageView();
    void ClampImageOffset(const cv::Size& drawSize);
    void ZoomAtScreenPoint(const cv::Point& screenPoint, float zoomMultiplier);
    std::pair<LineScanDirection, LineScanDirection> GetArrowValidScanDirections() const;
    void SyncArrowScanDirectionToAxis();
    void SyncArrowCaliperWidthToAxis();

    std::vector<LineCaliper> BuildArrowCalipers() const;
    std::vector<cv::Point2f> BuildArrowCaliperCorners(const LineCaliper& caliper) const;
    std::vector<cv::Point2f> BuildActiveRoiBoundary() const;
    bool ComputeDisplayedResultLine(cv::Point2f& start, cv::Point2f& end) const;
    std::pair<cv::Point2f, cv::Point2f> BuildArrowLengthHandlePoints() const;
    float ComputeArrowAxisLength() const;
    float ComputeArrowHalfLength() const;
    float ComputeArrowCaliperWidth() const;
    float ComputeMaxArrowCaliperWidth() const;

    std::string BuildStatusText() const;
    std::string BuildStatusDetailText() const;
    std::vector<std::pair<std::string, std::string>> BuildStatusDetailColumns() const;
    std::string BuildHelpText() const;

    std::vector<std::string> sampleImages_;
    int sampleIndex_ = -1;

    std::string windowName_ = "Linefind Demo";
    cv::Mat sourceImage_;
    cv::Mat grayImage_;
    std::string imagePath_;

    LineDetectionOperator detector_;
    LineDetectionParams params_;
    LineDetectionFrame frameRoi_;
    ArrowCaliperRoi arrowRoi_;
    LineDetectionResult result_;

    bool hasRoi_ = false;
    bool hasResult_ = false;
    RoiKind roiKind_ = RoiKind::None;
    CreateMode createMode_ = CreateMode::None;
    DragMode dragMode_ = DragMode::None;
    cv::Point2f dragStartImagePoint_ = cv::Point2f(0.0f, 0.0f);
    cv::Point dragStartScreenPoint_ = cv::Point(0, 0);
    cv::Point2f dragOffset_ = cv::Point2f(0.0f, 0.0f);
    cv::Point2f panStartOffset_ = cv::Point2f(0.0f, 0.0f);
    ResizeState resizeState_;

    cv::Size windowSize_ = cv::Size(1280, 870);
    cv::Rect sidebarRect_;
    cv::Rect imagePanelRect_;
    cv::Rect statusRect_;
    Viewport viewport_;
    float zoomFactor_ = 1.0f;
    cv::Point2f imageOffset_ = cv::Point2f(0.0f, 0.0f);
    bool viewNeedsReset_ = true;
    bool hasMouseImagePixel_ = false;
    cv::Point mouseImagePixel_ = cv::Point(0, 0);

    std::vector<Button> buttons_;
    std::vector<ParamControl> parameterControls_;
};
