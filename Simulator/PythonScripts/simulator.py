#
# Copyright 2017 by InfoMus Lab - DIST - University of Genova, http://www.infomus.org
#

"""Simulator sketch"""

# execfile( 'simulator.py' )

import eyesweb_mobile
import time
import random
import csv
import sensor_info

from csv_reader import read_csv
from my_callback import my_callback
from patches_manager import *

"""
Main
"""

ip_address = '127.0.0.1'
ip_port = 7834
kernel = eyesweb_mobile.kernel( ip_address, ip_port )

sculpture = read_csv('sculpture.csv')
(patches, callbacks) = init_patches_from_structure( kernel, sculpture )
user_simulation_patch = init_users_simulation_patch( kernel, True )
patches['user_simulation_patch'] = [ user_simulation_patch ]

start_all_patches(patches)

target_index = 0
print 'Waiting for CTRL+C to be pressed'
try:
	while True:
		time.sleep( 30 )
		
		if 'sma-infrared' in patches:
			sma_patches = patches[ 'sma-infrared' ]
		
			num_sma_patches = len(sma_patches)
			if num_sma_patches > 0:
				sma_index = random.randint(0, num_sma_patches - 1 )
				p = sma_patches[sma_index]
				
				target = random.uniform(-3.14, 3.14 )
				
				print 'Setting target for sma ' + str(sma_index) + ' to ' + str( target )
				p.set_block_parameter( 'sma_control', 'value', eyesweb_mobile.double_parameter(target) )

except KeyboardInterrupt:
	pass
	
stop_all_patches(patches)

patches.clear()
kernel = None

print 'End of script'

