#include "../src/utils.hpp"
#include "../src/converters.hpp"

const float EPSILON = 0.0001f;
inline bool Equal(float a, float b)
{
    // <= instead of < for NaN comparison safety
    return std::abs(a - b) <= EPSILON;
}

void TestPolygonWidthCalculator()
{
    std::cout << "DimensionsFromPolygon should get the dimensions from b2PolygonShape" << std::endl;
    const float WIDTH = 6.0f;
    const float HEIGHT = 3.0f;
    b2PolygonShape *polygon = new b2PolygonShape();
    polygon->SetAsBox(WIDTH, HEIGHT);

    b2Vec2 dimensions = utils::DimensionsFromPolygon(polygon);

    if (dimensions.x == WIDTH && dimensions.y == HEIGHT)
    {
        std::cout << "DimensionsFromPolygon works as expected" << std::endl;
    }
    else
    {
        std::cerr << "DimensionsFromPolygon not working." << std::endl;
        std::cerr << "Expected width: " << WIDTH << ", got: " << dimensions.x << std::endl;
        std::cerr << "Expected height: " << HEIGHT << ", got: " << dimensions.y << std::endl;
    }
}

void TestOpenFileSafe()
{
    std::cout << "OpenFileSafe should always return a file where writing is possible" << std::endl;
    std::ofstream output = utils::OpenFileSafe("testi");
    if (output.good())
    {
        std::cout << "OpenFileSafe works as expected" << std::endl;
    }
    else
    {
        std::cerr << "OpenFileSafe couldn't open a file" << std::endl;
    }
}

void TestConverters()
{
    bool failed = false;
    std::cout << "RadiansToDegrees should convert angle correctly" << std::endl;
    float degrees = utils::RadiansToDegrees(0);
    if (degrees != 0)
    {
        std::cerr << "RadiansToDegrees failed to convert 0 radians to degrees correctly" << std::endl;
        std::cerr << degrees << " != "
                  << 0 << std::endl;
        failed = true;
    }
    degrees = utils::RadiansToDegrees(2 * M_PI);
    if (!Equal(degrees, 360))
    {
        std::cerr << "RadiansToDegrees failed to convert 2 * PI radians to degrees correctly" << std::endl;
        std::cerr << degrees << " != "
                  << 360 << std::endl;
        failed = true;
    }

    if (failed)
    {
        std::cerr << "RadiansToDegrees failed" << std::endl;
    }
    else
    {
        std::cout << "RadiansToDegrees works correctly" << std::endl;
    }
    failed = false;

    std::cout << "DegreesToRadians should convert angle correctly" << std::endl;
    float radians = utils::DegreesToRadians(0);
    if (radians != 0)
    {
        std::cerr << "DegreesToRadians failed to convert 0 degrees to radians correctly" << std::endl;
        std::cerr << radians << " != "
                  << 0 << std::endl;
        failed = true;
    }
    radians = utils::DegreesToRadians(360);
    if (!Equal(radians, 2 * M_PI))
    {
        std::cerr << "DegreesToRadians failed to convert 360 degrees to radians correctly" << std::endl;
        std::cerr << radians << " != "
                  << 2 * M_PI << std::endl;
        failed = true;
    }

    if (failed)
    {
        std::cerr << "DegreesToRadians failed" << std::endl;
    }
    else
    {
        std::cout << "DegreesToRadians works correctly" << std::endl;
    }
}

int main()
{
    TestPolygonWidthCalculator();
    TestOpenFileSafe();
    TestConverters();

    return 0;
}
