require 'cosmos'
require 'cosmos/script'
require "cfs_lib.rb"
#require 'math'

##
## NOOP
##
initial_command_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_COUNT")
initial_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT")
initial_device_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_ERR_COUNT")
cmd("GENERIC_TORQUER GENERIC_TORQUER_NOOP_CC")
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_COUNT > #{initial_command_count}", 30)
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT == #{initial_error_count}", 30)
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_ERR_COUNT == #{initial_device_error_count}", 30)

sleep(5)

##
## Successful Disable
##
initial_command_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_COUNT")
initial_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT")
initial_device_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_ERR_COUNT")
cmd("GENERIC_TORQUER GENERIC_TORQUER_DISABLE_CC")
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_COUNT > #{initial_command_count}", 30)
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT == #{initial_error_count}", 30)
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_ERR_COUNT == #{initial_device_error_count}", 30)
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_ENABLED == 'DISABLED'", 30)

sleep(5)

##
## Failed Disable (doubled)
##
initial_command_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_COUNT")
initial_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT")
initial_device_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_ERR_COUNT")
cmd("GENERIC_TORQUER GENERIC_TORQUER_DISABLE_CC")
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_COUNT > #{initial_command_count}", 30)
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT == #{initial_error_count}", 30)
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_ERR_COUNT > #{initial_device_error_count}", 30)
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_ENABLED == 'DISABLED'", 30)

sleep(5)

##
## HK without Device
##
initial_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT")
initial_device_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_ERR_COUNT")
cmd("GENERIC_TORQUER GENERIC_TORQUER_SEND_HK_CC")
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT == #{initial_error_count}", 30)
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_ERR_COUNT == #{initial_device_error_count}", 30)

sleep(5)

##
## Successful Enable
##
initial_command_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_COUNT")
initial_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT")
initial_device_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_ERR_COUNT")
cmd("GENERIC_TORQUER GENERIC_TORQUER_ENABLE_CC")
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_COUNT > #{initial_command_count}", 30)
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT == #{initial_error_count}", 30)
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_ERR_COUNT == #{initial_device_error_count}", 30)
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_ENABLED == 'ENABLED'", 30)

sleep(5)

##
## Failed Enable (doubled)
##
initial_command_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_COUNT")
initial_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT")
initial_device_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_ERR_COUNT")
cmd("GENERIC_TORQUER GENERIC_TORQUER_ENABLE_CC")
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_COUNT > #{initial_command_count}", 30)
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT == #{initial_error_count}", 30)
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_ERR_COUNT > #{initial_device_error_count}", 30)
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_ENABLED == 'ENABLED'", 30)

sleep(5)

##
## Housekeeping w/ Device
##
initial_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT")
initial_device_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_ERR_COUNT")
cmd("GENERIC_TORQUER GENERIC_TORQUER_SEND_HK_CC")
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT == #{initial_error_count}", 30)
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_ERR_COUNT == #{initial_device_error_count}", 30)

sleep(5)

##
## Device Config
##
initial_command_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_COUNT")
initial_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT")
initial_device_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_ERR_COUNT")
trq_num = ask "Enter Configuration Value (integer between 0 and 2):"
direction = ask "Enter Configuration Value (integer between 0 and 1):"
percent = ask "Enter Configuration Value (integer between 0 and 100):"
cmd("GENERIC_TORQUER GENERIC_TORQUER_PERCENT_ON_CC with TRQNUM #{trq_num}, DIRECTION #{direction}, PERCENT_ON #{percent}")
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_COUNT > #{initial_command_count}", 30)
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT == #{initial_error_count}", 30)
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_ERR_COUNT == #{initial_device_error_count}", 30)

sleep(5)

#
# Configure and Data w/ Device
#
initial_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT")
initial_device_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_ERR_COUNT")

# Torquer 0
truth_42_wn_0_initial = tlm("SIM_42_TRUTH SIM_42_TRUTH_DATA WN_0")
trq_num0 = ask "Enter Configuration Value (integer between 0 and 2):"
direction0 = ask "Enter Configuration Value (integer between 0 and 1):"
percent0 = ask "Enter Configuration Value (integer between 0 and 100):"
torque0 = ask "Enter Configuration Value (integer greater than 0):"
cmd("GENERIC_TORQUER GENERIC_TORQUER_PERCENT_ON_CC with TRQNUM #{trq_num0}, DIRECTION #{direction0}, PERCENT_ON #{percent0}")
cmd("GENERIC_REACTION_WHEEL GENERIC_RW_SET_TORQUE_CC with WHEEL_NUMBER #{trq_num0}, TORQUE #{torque0}")
sleep(5)
if direction0 == 0
    wait_check("SIM_42_TRUTH SIM_42_TRUTH_DATA WN_0 <= #{truth_42_wn_0_initial}", 15)
else
    wait_check("SIM_42_TRUTH SIM_42_TRUTH_DATA WN_0 >= #{truth_42_wn_0_initial}", 15)
end

# Torquer 1
truth_42_wn_1_initial = tlm("SIM_42_TRUTH SIM_42_TRUTH_DATA W_1")
trq_num1 = ask "Enter Configuration Value (integer between 0 and 2):"
direction1 = ask "Enter Configuration Value (integer between 0 and 1):"
percent1 = ask "Enter Configuration Value (integer between 0 and 100):"
torque1 = ask "Enter Configuration Value (integer greater than 0):"
cmd("GENERIC_TORQUER GENERIC_TORQUER_PERCENT_ON_CC with TRQNUM #{trq_num1}, DIRECTION #{direction1}, PERCENT_ON #{percent1}")
cmd("GENERIC_REACTION_WHEEL GENERIC_RW_SET_TORQUE_CC with WHEEL_NUMBER #{trq_num1}, TORQUE #{torque1}")
sleep(5)
if direction1 == 0
    wait_check("SIM_42_TRUTH SIM_42_TRUTH_DATA WN_1 <= #{truth_42_wn_1_initial}", 15)
else
    wait_check("SIM_42_TRUTH SIM_42_TRUTH_DATA WN_1 >= #{truth_42_wn_1_initial}", 15)
end

# Torquer 2
truth_42_wn_2_initial = tlm("SIM_42_TRUTH SIM_42_TRUTH_DATA W_2")
trq_num2 = ask "Enter Configuration Value (integer between 0 and 2):"
direction2 = ask "Enter Configuration Value (integer between 0 and 1):"
percent2 = ask "Enter Configuration Value (integer between 0 and 100):"
torque2 = ask "Enter Configuration Value (integer greater than 0):"
cmd("GENERIC_TORQUER GENERIC_TORQUER_PERCENT_ON_CC with TRQNUM #{trq_num2}, DIRECTION #{direction2}, PERCENT_ON #{percent2}")
cmd("GENERIC_REACTION_WHEEL GENERIC_RW_SET_TORQUE_CC with WHEEL_NUMBER #{trq_num2}, TORQUE #{torque2}")
sleep(5)
if direction2 == 0
    wait_check("SIM_42_TRUTH SIM_42_TRUTH_DATA WN_2 <= #{truth_42_wn_2_initial}", 15)
else
    wait_check("SIM_42_TRUTH SIM_42_TRUTH_DATA WN_2 >= #{truth_42_wn_2_initial}", 15)
end

wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT == #{initial_error_count}", 30)
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_ERR_COUNT == #{initial_device_error_count}", 30)

sleep(5)

##
## Reset Counters
##
cmd("GENERIC_TORQUER GENERIC_TORQUER_DISABLE_CC") # disable to be able to properly check that device count gets reset
cmd("GENERIC_TORQUER GENERIC_TORQUER_RST_COUNTERS_CC")
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_COUNT == 0", 30)
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT == 0", 30)
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_COUNT == 0", 30)
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_ERR_COUNT == 0", 30)

##
## Reenable so test can be run multiple times
##
cmd("GENERIC_TORQUER GENERIC_TORQUER_ENABLE_CC")