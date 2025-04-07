# Library for GENERIC_TORQUER Target
require 'cosmos'
require 'cosmos/script'

#
# Definitions
#
GENERIC_TORQUER_CMD_SLEEP = 0.25
GENERIC_TORQUER_RESPONSE_TIMEOUT = 5
GENERIC_TORQUER_TEST_LOOP_COUNT = 1
GENERIC_TORQUER_DEVICE_LOOP_COUNT = 5

#
# Functions
#
def get_generic_torquer_hk()
    cmd("GENERIC_TORQUER GENERIC_TORQUER_REQ_HK")
    wait_check_packet("GENERIC_TORQUER", "GENERIC_TORQUER_HK_TLM", 1, GENERIC_TORQUER_RESPONSE_TIMEOUT)
    sleep(GENERIC_TORQUER_CMD_SLEEP)
end

def get_generic_torquer_data()
    cmd("GENERIC_TORQUER GENERIC_TORQUER_REQ_DATA")
    wait_check_packet("GENERIC_TORQUER", "GENERIC_TORQUER_DATA_TLM", 1, GENERIC_TORQUER_RESPONSE_TIMEOUT)
    sleep(GENERIC_TORQUER_CMD_SLEEP)
end

def generic_torquer_cmd(*command)
    count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_COUNT") + 1

    if (count == 256)
        count = 0
    end

    cmd(*command)
    get_generic_torquer_hk()
    current = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_COUNT")
    if (current != count)
        # Try again
        cmd(*command)
        get_generic_torquer_hk()
        current = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_COUNT")
        if (current != count)
            # Third times the charm
            cmd(*command)
            get_generic_torquer_hk()
            current = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_COUNT")
        end
    end
    check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_COUNT >= #{count}")
end

def enable_generic_torquer()
    # Send command
    generic_torquer_cmd("GENERIC_TORQUER GENERIC_TORQUER_ENABLE_CC")
    # Confirm
    check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ENABLED == 'ENABLED'")
end

def disable_generic_torquer()
    # Send command
    generic_torquer_cmd("GENERIC_TORQUER GENERIC_TORQUER_DISABLE_CC")
    # Confirm
    check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ENABLED == 'DISABLED'")
end

def safe_generic_torquer()
    get_generic_torquer_hk()
    state = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ENABLED")
    if (state != "DISABLED")
        disable_generic_torquer()
    end
end

def confirm_generic_torquer_data()
    dev_cmd_cnt = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_COUNT")
    dev_cmd_err_cnt = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ERR_COUNT")
    
    get_generic_torquer_data()
    # Note these checks assume default simulator configuration
    raw_x = tlm("GENERIC_TORQUER GENERIC_TORQUER_DATA_TLM RAW_GENERIC_TORQUER_X")
    check("GENERIC_TORQUER GENERIC_TORQUER_DATA_TLM RAW_GENERIC_TORQUER_Y >= #{raw_x*2}")
    check("GENERIC_TORQUER GENERIC_TORQUER_DATA_TLM RAW_GENERIC_TORQUER_Z >= #{raw_x*3}")

    get_generic_torquer_hk()
    check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_COUNT >= #{dev_cmd_cnt}")
    check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ERR_COUNT == #{dev_cmd_err_cnt}")
end

def confirm_generic_torquer_data_loop()
    GENERIC_TORQUER_DEVICE_LOOP_COUNT.times do |n|
        confirm_generic_torquer_data()
    end
end

#
# Simulator Functions
#
def generic_torquer_prepare_ast()
    # Get to known state
    safe_generic_torquer()

    # Enable
    enable_generic_torquer()

    # Confirm data
    confirm_generic_torquer_data_loop()
end

def generic_torquer_sim_enable()
    cmd("SIM_CMDBUS_BRIDGE GENERIC_TORQUER_SIM_ENABLE")
end

def generic_torquer_sim_disable()
    cmd("SIM_CMDBUS_BRIDGE GENERIC_TORQUER_SIM_DISABLE")
end

def generic_torquer_sim_set_status(status)
    cmd("SIM_CMDBUS_BRIDGE GENERIC_TORQUER_SIM_SET_STATUS with STATUS #{status}")
end
