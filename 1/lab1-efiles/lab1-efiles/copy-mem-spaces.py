
mem0 = pre_conf_object('cpu_mem0', 'memory-space')
mem0.default_target = [conf.cpu_mem, 0, 0, conf.cpu_mem]
mem1 = pre_conf_object('cpu_mem1', 'memory-space')
mem1.default_target = [conf.cpu_mem, 0, 0, conf.cpu_mem]
mem2 = pre_conf_object('cpu_mem2', 'memory-space')
mem2.default_target = [conf.cpu_mem, 0, 0, conf.cpu_mem]
mem3 = pre_conf_object('cpu_mem3', 'memory-space')
mem3.default_target = [conf.cpu_mem, 0, 0, conf.cpu_mem]
mem4 = pre_conf_object('cpu_mem4', 'memory-space')
mem4.default_target = [conf.cpu_mem, 0, 0, conf.cpu_mem]
mem5 = pre_conf_object('cpu_mem5', 'memory-space')
mem5.default_target = [conf.cpu_mem, 0, 0, conf.cpu_mem]
mem6 = pre_conf_object('cpu_mem6', 'memory-space')
mem6.default_target = [conf.cpu_mem, 0, 0, conf.cpu_mem]
mem7 = pre_conf_object('cpu_mem7', 'memory-space')
mem7.default_target = [conf.cpu_mem, 0, 0, conf.cpu_mem]

SIM_add_configuration([mem0,mem1,mem2,mem3,mem4,mem5,mem6,mem7], None)
