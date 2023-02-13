#include <generic_torquer_data_provider.hpp>

namespace Nos3
{
    REGISTER_DATA_PROVIDER(Generic_torquerDataProvider,"GENERIC_TORQUER_PROVIDER");

    extern ItcLogger::Logger *sim_logger;

    Generic_torquerDataProvider::Generic_torquerDataProvider(const boost::property_tree::ptree& config) : SimIDataProvider(config)
    {
        sim_logger->trace("Generic_torquerDataProvider::Generic_torquerDataProvider:  Constructor executed");
        _request_count = 0;
    }

    boost::shared_ptr<SimIDataPoint> Generic_torquerDataProvider::get_data_point(void) const
    {
        sim_logger->trace("Generic_torquerDataProvider::get_data_point:  Executed");

        /* Prepare the provider data */
        _request_count++;

        /* Request a data point */
        SimIDataPoint *dp = new Generic_torquerDataPoint(_request_count);

        /* Return the data point */
        return boost::shared_ptr<SimIDataPoint>(dp);
    }
}
