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
## Data without Device
##
initial_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT")
initial_device_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_ERR_COUNT")
cmd("GENERIC_TORQUER GENERIC_TORQUER_REQ_DATA")
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
## Data w/ Device
##
initial_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT")
initial_device_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_ERR_COUNT")

cmd("GENERIC_TORQUER GENERIC_TORQUER_REQ_DATA")

svb0 = tlm("SIM_42_TRUTH SIM_42_TRUTH_DATA SVB_0")
svb1 = tlm("SIM_42_TRUTH SIM_42_TRUTH_DATA SVB_1")
svb2 = tlm("SIM_42_TRUTH SIM_42_TRUTH_DATA SVB_2")

torquer_alpha = tlm("GENERIC_TORQUER GENERIC_TORQUER_DATA_TLM GENERIC_TORQUER_ALPHA")
torquer_beta = tlm("GENERIC_TORQUER GENERIC_TORQUER_DATA_TLM GENERIC_TORQUER_BETA")
torquer_error = tlm("GENERIC_TORQUER GENERIC_TORQUER_DATA_TLM GENERIC_TORQUER_ERROR_CODE")

truth_42_alpha = -Math.atan2(svb2, svb0)
truth_42_beta = Math.atan2(svb1, svb0)

truth_42_alpha_diff = (torquer_alpha - truth_42_alpha).abs()
truth_42_beta_diff = (torquer_beta - truth_42_beta).abs()
diff_margin = 0.025

wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T CMD_ERR_COUNT == #{initial_error_count}", 30)
wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM_T DEVICE_ERR_COUNT == #{initial_device_error_count}", 30)
if torquer_error == 0
  wait_check_expression("truth_42_alpha_diff <= diff_margin # #{truth_42_alpha_diff} <= #{diff_margin}", 15)

  wait_check_expression("truth_42_beta_diff <= diff_margin # #{truth_42_beta_diff} <= #{diff_margin}", 15)
end

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




# require 'cosmos'
# require 'cosmos/script'
# require "cfs_lib.rb"
# #require 'math'

# ##
# ## NOOP
# ##
# initial_command_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_COUNT")
# initial_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_ERR_COUNT")
# initial_device_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ERR_COUNT")
# cmd("GENERIC_TORQUER GENERIC_TORQUER_NOOP_CC")
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_COUNT > #{initial_command_count}", 30)
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_ERR_COUNT == #{initial_error_count}", 30)
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ERR_COUNT == #{initial_device_error_count}", 30)

# sleep(5)

# ##
# ## Successful Disable
# ##
# initial_command_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_COUNT")
# initial_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_ERR_COUNT")
# initial_device_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ERR_COUNT")
# cmd("GENERIC_TORQUER GENERIC_TORQUER_DISABLE_CC")
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_COUNT > #{initial_command_count}", 30)
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_ERR_COUNT == #{initial_error_count}", 30)
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ERR_COUNT == #{initial_device_error_count}", 30)
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ENABLED == 'DISABLED'", 30)

# sleep(5)

# ##
# ## Failed Disable (doubled)
# ##
# initial_command_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_COUNT")
# initial_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_ERR_COUNT")
# initial_device_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ERR_COUNT")
# cmd("GENERIC_TORQUER GENERIC_TORQUER_DISABLE_CC")
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_COUNT > #{initial_command_count}", 30)
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_ERR_COUNT == #{initial_error_count}", 30)
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ERR_COUNT > #{initial_device_error_count}", 30)
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ENABLED == 'DISABLED'", 30)

# sleep(5)

# ##
# ## Device Config
# ##
# initial_command_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_COUNT")
# initial_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_ERR_COUNT")
# initial_device_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ERR_COUNT")
# trq_num = ask "Enter Configuration Value (integer between 0 and 2):"
# direction = ask "Enter Configuration Value (integer between 0 and 1):"
# percent = ask "Enter Configuration Value (integer between 0 and 100):"
# cmd("GENERIC_TORQUER GENERIC_TORQUER_PERCENT_ON_CC with TRQNUM #{trq_num} DIRECTION #{direction} PERCENT_ON #{percent}")
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_COUNT > #{initial_command_count}", 30)
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_ERR_COUNT == #{initial_error_count}", 30)
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ERR_COUNT == #{initial_device_error_count}", 30)

# sleep(5)

# ##
# ## HK without Device
# ##
# initial_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_ERR_COUNT")
# initial_device_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ERR_COUNT")
# cmd("GENERIC_TORQUER GENERIC_TORQUER_REQ_HK")
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_ERR_COUNT == #{initial_error_count}", 30)
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ERR_COUNT == #{initial_device_error_count}", 30)

# sleep(5)

# ##
# ## Data without Device
# ##
# initial_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_ERR_COUNT")
# initial_device_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ERR_COUNT")
# cmd("GENERIC_TORQUER GENERIC_TORQUER_REQ_DATA")
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_ERR_COUNT == #{initial_error_count}", 30)
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ERR_COUNT == #{initial_device_error_count}", 30)

# sleep(5)

# ##
# ## Successful Enable
# ##
# initial_command_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_COUNT")
# initial_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_ERR_COUNT")
# initial_device_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ERR_COUNT")
# cmd("GENERIC_TORQUER GENERIC_TORQUER_ENABLE_CC")
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_COUNT > #{initial_command_count}", 30)
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_ERR_COUNT == #{initial_error_count}", 30)
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ERR_COUNT == #{initial_device_error_count}", 30)
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ENABLED == 'ENABLED'", 30)

# sleep(5)

# ##
# ## Failed Enable (doubled)
# ##
# initial_command_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_COUNT")
# initial_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_ERR_COUNT")
# initial_device_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ERR_COUNT")
# cmd("GENERIC_TORQUER GENERIC_TORQUER_ENABLE_CC")
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_COUNT > #{initial_command_count}", 30)
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_ERR_COUNT == #{initial_error_count}", 30)
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ERR_COUNT > #{initial_device_error_count}", 30)
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ENABLED == 'ENABLED'", 30)

# sleep(5)

# ##
# ## Housekeeping w/ Device
# ##
# initial_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_ERR_COUNT")
# initial_device_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ERR_COUNT")
# cmd("GENERIC_TORQUER GENERIC_TORQUER_REQ_HK")
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_ERR_COUNT == #{initial_error_count}", 30)
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ERR_COUNT == #{initial_device_error_count}", 30)

# sleep(5)

# ##
# ## Data w/ Device
# ##

# initial_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_ERR_COUNT")
# initial_device_error_count = tlm("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ERR_COUNT")

# cmd("GENERIC_TORQUER GENERIC_TORQUER_REQ_DATA")

# truth_42_wn_0_initial = tlm("SIM_42_TRUTH SIM_42_TRUTH_DATA W_0")
# truth_42_wn_1_initial = tlm("SIM_42_TRUTH SIM_42_TRUTH_DATA W_1")
# truth_42_wn_3_initial = tlm("SIM_42_TRUTH SIM_42_TRUTH_DATA W_2")
 
# cmd("GENERIC_TORQUER GENERIC_TORQUER_PERCENT_ON_CC with TRQNUM #{trq_num}, DIRECTION #{direction}, PERCENT_ON #{percent}")
# sleep(5)

# if direction == 0
#   wait_check("SIM_42_TRUTH SIM_42_TRUTH_DATA W_0 >= #{truth_42_wn_0}")
# else
#   wait_check("SIM_42_TRUTH SIM_42_TRUTH_DATA W_0 <= #{truth_42_wn_0}")

# diff_margin = 0.025

# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_ERR_COUNT == #{initial_error_count}", 30)
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ERR_COUNT == #{initial_device_error_count}", 30)
# if torquer_error == 0
#   wait_check_expression("truth_42_alpha_diff <= diff_margin # #{truth_42_alpha_diff} <= #{diff_margin}", 15)
#   wait_check_expression("truth_42_beta_diff <= diff_margin # #{truth_42_beta_diff} <= #{diff_margin}", 15)
# end

# sleep(5)

# ##
# ## Reset Counters
# ##
# cmd("GENERIC_TORQUER GENERIC_TORQUER_DISABLE_CC") # disable to be able to properly check that device count gets reset
# cmd("GENERIC_TORQUER GENERIC_TORQUER_RST_COUNTERS_CC")
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_COUNT == 0", 30)
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM CMD_ERR_COUNT == 0", 30)
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_COUNT == 0", 30)
# wait_check("GENERIC_TORQUER GENERIC_TORQUER_HK_TLM DEVICE_ERR_COUNT == 0", 30)

# ##
# ## Reenable so test can be run multiple times
# ##
# cmd("GENERIC_TORQUER GENERIC_TORQUER_ENABLE_CC")