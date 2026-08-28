//-----------------------------------------------------------------------------
// polygon_plugins.cpp
//
// MTRX3760 Lab 2 A4 extension of the ROS 2 Jazzy Pluginlib polygon example.
// House uses composition: it has one Square and one Triangle, and both receive
// the same side length during initialisation.
//-----------------------------------------------------------------------------

#include <polygon_base/regular_polygon.hpp>

#include <cmath>

namespace polygon_plugins
{

class Square : public polygon_base::RegularPolygon
{
    public:
        Square()
            : mSideLength( 0.0 )
        {
        }

        void initialize( double aSideLength )
        {
            mSideLength = aSideLength;
        }

        double area()
        {
            return mSideLength * mSideLength;
        }

    private:
        double mSideLength;
};

class Triangle : public polygon_base::RegularPolygon
{
    public:
        Triangle()
            : mSideLength( 0.0 )
        {
        }

        void initialize( double aSideLength )
        {
            mSideLength = aSideLength;
        }

        double area()
        {
            return 0.5 * mSideLength * GetHeight();
        }

    private:
        double GetHeight() const
        {
            return std::sqrt( mSideLength * mSideLength
                            - ( mSideLength / 2.0 ) * ( mSideLength / 2.0 ) );
        }

        double mSideLength;
};

class House : public polygon_base::RegularPolygon
{
    public:
        void initialize( double aSideLength )
        {
            // A house has a square body and a triangular roof. Both parts use
            // the same side length, as required by the lab specification.
            mSquare.initialize( aSideLength );
            mTriangle.initialize( aSideLength );
        }

        double area()
        {
            return mSquare.area() + mTriangle.area();
        }

    private:
        Square mSquare;
        Triangle mTriangle;
};

} // namespace polygon_plugins

#include <pluginlib/class_list_macros.hpp>

PLUGINLIB_EXPORT_CLASS( polygon_plugins::Square, polygon_base::RegularPolygon )
PLUGINLIB_EXPORT_CLASS( polygon_plugins::Triangle, polygon_base::RegularPolygon )
PLUGINLIB_EXPORT_CLASS( polygon_plugins::House, polygon_base::RegularPolygon )
