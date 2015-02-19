
# 
# Transaction staller for memory 
# 
staller = pre_conf_object('staller','trans-staller') 
staller.stall_time = 100 
# 
# combined shared L2 cache: 512Kb Write-back 
# 
l2cache = pre_conf_object('l2cache', 'g-cache') 
l2cache.cpus = [conf.cpu0_0, conf.cpu0_1, conf.cpu0_2, conf.cpu0_3,conf.cpu1_0, conf.cpu1_1, conf.cpu1_2, conf.cpu1_3,conf.cpu2_0, conf.cpu2_1, conf.cpu2_2, conf.cpu2_3,conf.cpu3_0, conf.cpu3_1, conf.cpu3_2, conf.cpu3_3,conf.cpu4_0, conf.cpu4_1, conf.cpu4_2, conf.cpu4_3,conf.cpu5_0, conf.cpu5_1, conf.cpu5_2, conf.cpu5_3,conf.cpu6_0, conf.cpu6_1, conf.cpu6_2, conf.cpu6_3,conf.cpu7_0, conf.cpu7_1, conf.cpu7_2, conf.cpu7_3] 
l2cache.config_line_number = 4096 
l2cache.config_line_size = 128 
l2cache.config_assoc = 8 
l2cache.config_virtual_index = 0 
l2cache.config_virtual_tag = 0 
l2cache.config_write_back = 1 
l2cache.config_write_allocate = 1 
l2cache.config_replacement_policy = 'lru' 
l2cache.penalty_read = 5 
l2cache.penalty_write = 5 
l2cache.penalty_read_next = 0 
l2cache.penalty_write_next = 0 
l2cache.timing_model = staller 

SIM_add_configuration([staller, l2cache], None) 
# 
# combined private L1 cache: 8Kb Write-through 
# 
loop = 0
while loop < 8:
    l1cache = pre_conf_object(("l1cache" + str(loop)), 'g-cache') 
    l1cache.cpus = [ eval("conf.cpu" + str(loop) + "_0"), eval("conf.cpu" + str(loop) + "_1"), eval("conf.cpu" + str(loop) + "_2"), eval("conf.cpu" + str(loop) + "_3")] 
    l1cache.config_line_number = 64 
    l1cache.config_line_size = 128 
    l1cache.config_assoc = 4 
    l1cache.config_virtual_index = 0 
    l1cache.config_virtual_tag = 0 
    l1cache.config_write_back = 0 
    l1cache.config_write_allocate = 0 
    l1cache.config_replacement_policy = 'lru' 
    l1cache.penalty_read = 1 
    l1cache.penalty_write = 1 
    l1cache.penalty_read_next = 0 
    l1cache.penalty_write_next = 0 
    l1cache.timing_model = conf.l2cache 
    SIM_add_configuration([l1cache], None)
    loop = loop + 1

conf.l1cache0.snoopers = [conf.l1cache1, conf.l1cache2, conf.l1cache3, conf.l1cache4, conf.l1cache5, conf.l1cache6, conf.l1cache7]
conf.l1cache1.snoopers = [conf.l1cache0, conf.l1cache2, conf.l1cache3, conf.l1cache4, conf.l1cache5, conf.l1cache6, conf.l1cache7]
conf.l1cache2.snoopers = [conf.l1cache0, conf.l1cache1, conf.l1cache3, conf.l1cache4, conf.l1cache5, conf.l1cache6, conf.l1cache7]
conf.l1cache3.snoopers = [conf.l1cache0, conf.l1cache1, conf.l1cache2, conf.l1cache4, conf.l1cache5, conf.l1cache6, conf.l1cache7]
conf.l1cache4.snoopers = [conf.l1cache0, conf.l1cache1, conf.l1cache2, conf.l1cache3, conf.l1cache5, conf.l1cache6, conf.l1cache7]
conf.l1cache5.snoopers = [conf.l1cache0, conf.l1cache1, conf.l1cache2, conf.l1cache3, conf.l1cache4, conf.l1cache6, conf.l1cache7]
conf.l1cache6.snoopers = [conf.l1cache0, conf.l1cache1, conf.l1cache2, conf.l1cache3, conf.l1cache4, conf.l1cache5, conf.l1cache7]
conf.l1cache7.snoopers = [conf.l1cache0, conf.l1cache1, conf.l1cache2, conf.l1cache3, conf.l1cache4, conf.l1cache5, conf.l1cache6]
conf.l2cache.higher_level_caches = [conf.l1cache0, conf.l1cache1, conf.l1cache2, conf.l1cache3, conf.l1cache4, conf.l1cache5, conf.l1cache6, conf.l1cache7]
