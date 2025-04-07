require 'cosmos'
require 'cosmos/script'
require "generic_torquer_lib.rb"

##
## This script tests the cFS component device functionality.
## Currently this includes: 
##   Enable / disable, control hardware communications
##   Configuration, reconfigure generic_torquer instrument register
##


##
## Enable / disable, control hardware communications
##
GENERIC_TORQUER_TEST_LOOP_COUNT.times do |n|
    safe_generic_torquer() # Get to known state

    # Manually command to disable when already disabled
    cmd_cnt = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_COUNT")
    cmd_err_cnt = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT")
    cmd("GENERIC_TORQUER GENERIC_TORQUER_DISABLE_CC")
    get_generic_torquer_hk()
    check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_COUNT == #{cmd_cnt}")
    check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT == #{cmd_err_cnt+1}")

    # Enable
    enable_generic_torquer()

    # Confirm device counters increment without errors
    confirm_generic_torquer_data_loop()

    # Manually command to enable when already enabled
    cmd_cnt = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_COUNT")
    cmd_err_cnt = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT")
    cmd("GENERIC_TORQUER GENERIC_TORQUER_ENABLE_CC")
    get_generic_torquer_hk()
    check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_COUNT == #{cmd_cnt}")
    check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT == #{cmd_err_cnt+1}")

    # Reconfirm data remains as expected
    confirm_generic_torquer_data_loop()

    # Disable
    disable_generic_torquer()
end


##
##   Configuration, reconfigure generic_torquer instrument register
##
GENERIC_TORQUER_TEST_LOOP_COUNT.times do |n|
    safe_generic_torquer() # Get to known state

    # Confirm configuration command denied if disabled
    cmd_cnt = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_COUNT")
    cmd_err_cnt = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT")
    cmd("GENERIC_TORQUER GENERIC_TORQUER_CONFIG_CC with DEVICE_CONFIG 10")
    get_generic_torquer_hk()
    check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_COUNT == #{cmd_cnt}")
    check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT == #{cmd_err_cnt+1}")
    
    # Enable
    enable_generic_torquer()

    # Set configuration
    generic_torquer_cmd("GENERIC_TORQUER GENERIC_TORQUER_CONFIG_CC with DEVICE_CONFIG #{n+1}")
    check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_CONFIG == #{n+1}")
end
