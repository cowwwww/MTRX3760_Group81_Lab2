//-----------------------------------------------------------------------------
// area_node.cpp
//
// Small test for the A4 Pluginlib extension. The required test uses side 10.0.
//-----------------------------------------------------------------------------

#include <pluginlib/class_loader.hpp>
#include <polygon_base/regular_polygon.hpp>

#include <cstdio>
#include <memory>
#include <stdexcept>

int main( int argc, char** argv )
{
    (void) argc;
    (void) argv;

    pluginlib::ClassLoader<polygon_base::RegularPolygon> loader(
        "polygon_base", "polygon_base::RegularPolygon" );

    try
    {
        const double sideLength = 10.0;

        std::shared_ptr<polygon_base::RegularPolygon> square =
            loader.createSharedInstance( "polygon_plugins::Square" );
        square->initialize( sideLength );

        std::shared_ptr<polygon_base::RegularPolygon> triangle =
            loader.createSharedInstance( "awesome_triangle" );
        triangle->initialize( sideLength );

        std::shared_ptr<polygon_base::RegularPolygon> house =
            loader.createSharedInstance( "polygon_plugins::House" );
        house->initialize( sideLength );

        std::printf( "Square area: %.2f\n", square->area() );
        std::printf( "Triangle area: %.2f\n", triangle->area() );
        std::printf( "House area: %.2f\n", house->area() );

        try
        {
            house->initialize( 0.0 );
            std::printf( "Validation test: FAILED\n" );
            return 1;
        }
        catch( const std::invalid_argument& )
        {
            std::printf( "Validation test: non-positive side length rejected\n" );
        }
    }
    catch( const pluginlib::PluginlibException& ex )
    {
        std::printf( "Plugin load failed: %s\n", ex.what() );
        return 1;
    }

    return 0;
}
