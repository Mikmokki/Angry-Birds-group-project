#include "../src/utils.hpp"

void TestPolygonWidthCalculator()
{
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

int main()
{
    TestPolygonWidthCalculator();

    return 0;
}
