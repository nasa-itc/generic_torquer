import sys
import glob

for p in glob.glob('/gems/gems/openc3-cosmos-nos3-*/targets/GENERIC_TORQUER/scripts'):
    if p not in sys.path:
        sys.path.append(p)

try:
    from openc3.script import cmd, tlm, check
    from nos3.generic_torquer_lib import *
except ImportError:
    pass

def run_generic_torquer_device_test():
    ##
    ## This script tests the cFS component device functionality.
    ## Currently this includes: 
    ##   Enable / disable, control hardware communications
    ##   Configuration, reconfigure generic_torquer instrument register
    ##


    ##
    ## Enable / disable, control hardware communications
    ##
    for n in range(GENERIC_TORQUER_TEST_LOOP_COUNT):
        safe_generic_torquer() # Get to known state

        # Manually command to disable when already disabled
        cmd_cnt = tlm("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T CMD_COUNT")
        cmd_err_cnt = tlm("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT")
        cmd("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_DISABLE_CC")
        get_generic_torquer_hk()
        check(f"GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T CMD_COUNT == {cmd_cnt}")
        check(f"GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT == {cmd_err_cnt+1}")

        # Enable
        enable_generic_torquer()

        get_generic_torquer_hk()

        # Confirm device counters increment without errors
        confirm_generic_torquer_data_loop()

        cmd_cnt = tlm("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T CMD_COUNT")
        cmd_err_cnt = tlm("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT")
        cmd("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_ENABLE_CC")
        get_generic_torquer_hk()
        check(f"GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T CMD_COUNT == {cmd_cnt}")
        check(f"GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT == {cmd_err_cnt+1}")

        # Reconfirm data remains as expected
        confirm_generic_torquer_data_loop()

        # Disable
        disable_generic_torquer()


    ##
    ##   Configuration, reconfigure generic_torquer instrument register
    ##
    for n in range(GENERIC_TORQUER_TEST_LOOP_COUNT):
        safe_generic_torquer() # Get to known state

        # Confirm configuration command denied if disabled
        cmd_cnt = tlm("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T CMD_COUNT")
        cmd_err_cnt = tlm("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT")
        cmd("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_PERCENT_ON_CC with TRQNUM 0, DIRECTION 0, PERCENT_ON 0")
        get_generic_torquer_hk()
        check(f"GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T CMD_COUNT == {cmd_cnt}")
        check(f"GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT == {cmd_err_cnt+1}")
        
        # Enable
        enable_generic_torquer()

        # Set configuration
        generic_torquer_cmd("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_PERCENT_ON_CC with TRQNUM 0, DIRECTION 0, PERCENT_ON 0")
        check("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T TORQUER_DIRECTION_0 == 0")
        check("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T TORQUER_PERCENT_ON_0 == 0")

        get_generic_torquer_hk()

        generic_torquer_cmd("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_PERCENT_ON_CC with TRQNUM 0, DIRECTION 1, PERCENT_ON 1")
        check("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T TORQUER_DIRECTION_0 == 1")
        check("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T TORQUER_PERCENT_ON_0 == 1")

    ##
    ##   Configuration All, reconfigure generic_torquer instrument register
    ##
    for n in range(GENERIC_TORQUER_TEST_LOOP_COUNT):
        safe_generic_torquer() # Get to known state

        # Confirm configuration command denied if disabled
        cmd_cnt = tlm("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T CMD_COUNT")
        cmd_err_cnt = tlm("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT")
        cmd("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_ALL_PERCENT_ON_CC with DIRECTION_0 0, PERCENT_ON_0 0, DIRECTION_1 0, PERCENT_ON_1 0, DIRECTION_2 0, PERCENT_ON_2 0")
        get_generic_torquer_hk()
        check(f"GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T CMD_COUNT == {cmd_cnt}")
        check(f"GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT == {cmd_err_cnt+1}")
        
        # Enable
        enable_generic_torquer()

        # Set configuration
        generic_torquer_cmd("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_ALL_PERCENT_ON_CC with DIRECTION_0 0, PERCENT_ON_0 0, DIRECTION_1 0, PERCENT_ON_1 0, DIRECTION_2 0, PERCENT_ON_2 0")

        check("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T TORQUER_DIRECTION_0 == 0")
        check("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T TORQUER_PERCENT_ON_0 == 0")

        check("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T TORQUER_DIRECTION_1 == 0")
        check("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T TORQUER_PERCENT_ON_1 == 0")

        check("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T TORQUER_DIRECTION_2 == 0")
        check("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T TORQUER_PERCENT_ON_2 == 0")

        generic_torquer_cmd("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_ALL_PERCENT_ON_CC with DIRECTION_0 1, PERCENT_ON_0 1, DIRECTION_1 1, PERCENT_ON_1 1, DIRECTION_2 1, PERCENT_ON_2 1")

        check("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T TORQUER_DIRECTION_0 == 1")
        check("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T TORQUER_PERCENT_ON_0 == 1")

        check("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T TORQUER_DIRECTION_1 == 1")
        check("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T TORQUER_PERCENT_ON_1 == 1")

        check("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T TORQUER_DIRECTION_2 == 1")
        check("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T TORQUER_PERCENT_ON_2 == 1")