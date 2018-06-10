# -*- coding: utf-8 -*-
"""
Created on Mon Apr 17 19:44:46 2017

@author: wangl
"""
import struct

target_row = 37

import input_sipm_data

import numpy as np

sipm_verifying_data=input_sipm_data.read_data_sets("H:/DATA/waveform/非零积分信号输出/0.8_output/verifying_set")

for i in range(2):
    for j in range(2):
        blanket = np.array([])
        for k in range(sipm_verifying_data.size[1]):
            if sipm_verifying_data.data[k][36] == i:
                if sipm_verifying_data.data[k][37] == j:
                    blanket = [blanket,sipm_verifying_data.data[k]]
        a = blanket[:,0:36]

        b = blanket[:,36].reshape(sipm_test_data.size[1],1)    
                

totol_variance = tf.square(y - y_)

variance = tf.reduce_mean(totol_variance)

a = sipm_verifying_data.data[:,0:36]

b = sipm_verifying_data.data[:,target_row].reshape(sipm_verifying_data.size[1],1)

v = y.eval(feed_dict = {x: a, y_: b})

loc = sipm_verifying_data.data[:,36:38]

output=np.concatenate((loc,v),axis=1)

output.tofile("H:/DATA/waveform/非零积分信号输出/0.8_output/x_2_output")

