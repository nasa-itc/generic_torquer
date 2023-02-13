#ifndef NOS3_GENERIC_TORQUERDATAPROVIDER_HPP
#define NOS3_GENERIC_TORQUERDATAPROVIDER_HPP

#include <boost/property_tree/xml_parser.hpp>
#include <ItcLogger/Logger.hpp>
#include <generic_torquer_data_point.hpp>
#include <sim_i_data_provider.hpp>

namespace Nos3
{
    class Generic_torquerDataProvider : public SimIDataProvider
    {
    public:
        /* Constructors */
        Generic_torquerDataProvider(const boost::property_tree::ptree& config);

        /* Accessors */
        boost::shared_ptr<SimIDataPoint> get_data_point(void) const;

    private:
        /* Disallow these */
        ~Generic_torquerDataProvider(void) {};
        Generic_torquerDataProvider& operator=(const Generic_torquerDataProvider&) {};

        mutable double _request_count;
    };
}

#endif
