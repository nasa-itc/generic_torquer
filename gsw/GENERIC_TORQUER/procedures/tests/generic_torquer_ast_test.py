import sys
import glob
import time

for p in glob.glob('/gems/gems/openc3-cosmos-nos3-*/targets/GENERIC_TORQUER/scripts'):
    if p not in sys.path:
        sys.path.append(p)

try:
    from openc3.script import cmd, tlm, check, wait_check
    from nos3.generic_torquer_lib import *
except ImportError:
    pass

def run_generic_torquer_ast_test():
    ##
    ## This script tests the cFS component in an automated scenario.
    ## Currently this includes: 
    ##   Hardware failure
    ##   Hardware status reporting fault
    ##

    ##
    ## Hardware failure
    ##
    for n in range(GENERIC_TORQUER_TEST_LOOP_COUNT):
        # Prepare
        generic_torquer_prepare_ast()

        # Disable sim and confirm device error counts increase
        dev_cmd_cnt = tlm("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T DEVICE_COUNT")
        dev_cmd_err_cnt = tlm("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T DEVICE_ERR_COUNT")
        
        generic_torquer_sim_disable()

        time.sleep(1)

        cmd("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_REQ_HK_CC")

        wait_check(f"GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T DEVICE_COUNT >= {dev_cmd_cnt}", 5)
        wait_check(f"GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T DEVICE_ERR_COUNT >= {dev_cmd_err_cnt}", 5)

        # Enable sim and confirm return to nominal operation
        generic_torquer_sim_enable()

        time.sleep(1)

        confirm_generic_torquer_data_loop()