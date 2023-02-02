#include <ItcLogger/Logger.hpp>

#include <generic_torquer_data_point.hpp>

#include <generic_torquer_42_data_provider.hpp>

namespace Nos3
{
    REGISTER_DATA_PROVIDER(Generic_torquer42DataProvider,"GENERIC_TORQUER_42_PROVIDER");

    extern ItcLogger::Logger *sim_logger;

    /*************************************************************************
     * Constructors
     *************************************************************************/

    Generic_torquer42DataProvider::Generic_torquer42DataProvider(const boost::property_tree::ptree& config) : SimData42SocketProvider(config)
    {
        sim_logger->trace("Generic_torquer42DataProvider::Generic_torquer42DataProvider:  Constructor executed");

        connect_reader_thread_as_42_socket_client(
            config.get("simulator.hardware-model.data-provider.hostname", "localhost"),
            config.get("simulator.hardware-model.data-provider.port", 4242) );

        _sc = config.get("simulator.hardware-model.data-provider.spacecraft", 0);
    }

    /*************************************************************************
     * Non-mutating public worker methods
     *************************************************************************/

    void Generic_torquer42DataProvider::cmd_torque(int trq_num, double trq_value)
    {
        char buffer [56];
        sprintf (buffer, "SC[%i].AC.MTB[%i].Mcmd = %lf\n[EOF]\n", _sc, trq_num, trq_value);

        send_command_to_socket(std::string(buffer));
    }

    boost::shared_ptr<SimIDataPoint> Generic_torquer42DataProvider::get_data_point(void) const
    {
        sim_logger->trace("Generic_torquer42DataProvider::get_data_point:  Executed");

        // Get the 42 data
        const boost::shared_ptr<Sim42DataPoint> dp42 =
            boost::dynamic_pointer_cast<Sim42DataPoint>(SimData42SocketProvider::get_data_point());

        // vvv Prepare the specific data... this may need changed in your use case
        SimIDataPoint *dp = new Generic_torquerDataPoint(_sc, dp42);

        return boost::shared_ptr<SimIDataPoint>(dp);
    }
}
