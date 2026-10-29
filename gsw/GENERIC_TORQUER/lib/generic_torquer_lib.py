# Library for GENERIC_TORQUER Target
import sys
import glob

for p in glob.glob('/gems/gems/openc3-cosmos-nos3-*/targets/GENERIC_TORQUER/scripts'):
    if p not in sys.path:
        sys.path.append(p)

try:
    from openc3.script import cmd, tlm, check, wait_check, wait_check_packet
    import time
except ImportError:
    pass

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
def get_generic_torquer_hk():
    cmd("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_REQ_HK_CC")
    wait_check_packet("GENERIC_TORQUER_DEBUG", "GENERIC_TORQUER_HK_TLM_T", 1, GENERIC_TORQUER_RESPONSE_TIMEOUT)
    time.sleep(GENERIC_TORQUER_CMD_SLEEP)

def generic_torquer_cmd(command_string):
    count = tlm("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T CMD_COUNT") + 1

    if (count == 256):
        count = 0

    cmd(command_string)
    get_generic_torquer_hk()
    current = tlm("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T CMD_COUNT")
    if (current != count):
        # Try again
        cmd(command_string)
        get_generic_torquer_hk()
        current = tlm("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T CMD_COUNT")
        if (current != count):
            # Third times the charm
            cmd(command_string)
            get_generic_torquer_hk()
            current = tlm("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T CMD_COUNT")
            
    check(f"GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T CMD_COUNT >= {count}")

def enable_generic_torquer():
    # Send command
    generic_torquer_cmd("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_ENABLE_CC")
    # Confirm
    check("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T DEVICE_ENABLED == 'ENABLED'")

def disable_generic_torquer():
    # Send command
    generic_torquer_cmd("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_DISABLE_CC")
    # Confirm
    check("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T DEVICE_ENABLED == 'DISABLED'")

def safe_generic_torquer():
    get_generic_torquer_hk()
    state = tlm("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T DEVICE_ENABLED")
    if (state != "DISABLED"):
        disable_generic_torquer()

def confirm_generic_torquer_data():
    dev_cmd_cnt = tlm("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T DEVICE_COUNT")
    dev_cmd_err_cnt = tlm("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T DEVICE_ERR_COUNT")
    
    get_generic_torquer_hk()
    #Note these checks assume default simulator configuration
    
    cmd_cnt_initial = tlm("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T CMD_COUNT")
    trq_num0 = 0
    direction0 = 0
    percent0 = 50
    generic_torquer_cmd(f"GENERIC_TORQUER_DEBUG GENERIC_TORQUER_PERCENT_ON_CC with TRQNUM {trq_num0}, DIRECTION {direction0}, PERCENT_ON {percent0}")
    wait_check(f"GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T CMD_COUNT > {cmd_cnt_initial}", 15)
    cmd_cnt_initial = tlm("GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T CMD_COUNT")
    generic_torquer_cmd(f"GENERIC_TORQUER_DEBUG GENERIC_TORQUER_ALL_PERCENT_ON_CC with DIRECTION_0 {direction0}, PERCENT_ON_0 {percent0}, DIRECTION_1 {direction0}, PERCENT_ON_1 {percent0}, DIRECTION_2 {direction0}, PERCENT_ON_2 {percent0}")
    wait_check(f"GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T CMD_COUNT > {cmd_cnt_initial}", 15)

    get_generic_torquer_hk()
    check(f"GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T DEVICE_COUNT >= {dev_cmd_cnt}")
    check(f"GENERIC_TORQUER_DEBUG GENERIC_TORQUER_HK_TLM_T DEVICE_ERR_COUNT == {dev_cmd_err_cnt}")

def confirm_generic_torquer_data_loop():
    for n in range(GENERIC_TORQUER_DEVICE_LOOP_COUNT):
        confirm_generic_torquer_data()

#
# Simulator Functions
#
def generic_torquer_prepare_ast():
    # Get to known state
    safe_generic_torquer()

    # Enable
    enable_generic_torquer()

    # Confirm data
    confirm_generic_torquer_data_loop()

def generic_torquer_sim_enable():
    cmd("SIM_CMDBUS_BRIDGE GENERIC_TORQUER_SIM_ENABLE")

def generic_torquer_sim_disable():
    cmd("SIM_CMDBUS_BRIDGE GENERIC_TORQUER_SIM_DISABLE")

def generic_torquer_sim_set_status(status):
    cmd(f"SIM_CMDBUS_BRIDGE GENERIC_TORQUER_SIM_SET_STATUS with STATUS {status}")