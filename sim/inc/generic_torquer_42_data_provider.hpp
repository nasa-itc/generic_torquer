#ifndef NOS3_GENERIC_TORQUER42DATAPROVIDER_HPP
#define NOS3_GENERIC_TORQUER42DATAPROVIDER_HPP

#include <boost/property_tree/ptree.hpp>

#include <sim_data_42socket_provider.hpp>

namespace Nos3
{
    // vvv This is pretty standard for a 42 data provider (if one is needed for your sim)
    class Generic_torquer42DataProvider : public SimData42SocketProvider
    {
    public:
        // Constructors / destructor
        Generic_torquer42DataProvider(const boost::property_tree::ptree& config);

        // Accessors
        boost::shared_ptr<SimIDataPoint> get_data_point(void) const;

    private:
        // Disallow these
        ~Generic_torquer42DataProvider(void) {};
        Generic_torquer42DataProvider& operator=(const Generic_torquer42DataProvider&) {};

        int16_t _sc;  // Which spacecraft number to parse out of 42 data
    };
}

#endif
