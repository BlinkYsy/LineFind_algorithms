#include <vector>
#include <string>

#include "demo_canvas.h"

int main() {
    std::vector<std::string> sampleImages = {
        "D:\\Visual Studio 2022\\LineFind_algorithms\\testImage\\output_20260317-145938.345.jpg",
        "D:\\Visual Studio 2022\\LineFind_algorithms\\testImage\\010.jpg",
        "D:\\Visual Studio 2022\\LineFind_algorithms\\testImage\\011.jpg",
        "D:\\Visual Studio 2022\\LineFind_algorithms\\testImage\\012.jpg",
        "D:\\Visual Studio 2022\\LineFind_algorithms\\testImage\\013.jpg",
        "D:\\Visual Studio 2022\\LineFind_algorithms\\testImage\\014.jpg",
    };

    DemoCanvasApp app(sampleImages);
    return app.Run();
}
