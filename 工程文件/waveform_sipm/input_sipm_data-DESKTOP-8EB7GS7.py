# -*- coding: utf-8 -*-
"""
Created on Mon Apr 10 15:19:49 2017

@author: Mr-Wlz
"""

import numpy as np

class data(object):

    data = 0

    size = 0

    _index_in_epoch = 0

    _epochs_completed = 0

    def __init__(self, data, size):

        self.data = data

        self.size = size

        self.index_in_epoch = 0
        
    def next_batch(self, batch_size):

        start = self._index_in_epoch

        self._index_in_epoch += batch_size

        if self._index_in_epoch > self.size[1]: # epoch中的句子下标是否大于所有语料的个数，如果为True,开始新一轮的遍历

            # Finished epoch

            self._epochs_completed += 1

            # Shuffle the data

            np.random.shuffle(self.data)  # 打乱

            # Start next epoch

            start = 0

            self._index_in_epoch = batch_size

        assert batch_size <= self.size[1]
        
        end = self._index_in_epoch

        return self.data[start:end,:]
    
    
def read_data_sets(str):    

    training_data = np.fromfile(str, dtype=np.int32)

    training_data_size = training_data[0:2]

    training_data = training_data[2:(training_data_size[0]*training_data_size[1]+2)]

    training_data=training_data.reshape((training_data_size[1],training_data_size[0]))

    training_data=training_data.astype(np.float32)

#    for i in range(training_data_size[1]):
#
#        av=float(np.sum(training_data[i,0:36]))
#
#        training_data[i,0:36] = training_data[i,0:36]/av   

    np.random.shuffle(training_data)

    sipm_data = data(training_data,training_data_size)

    return sipm_data

#                   _ooOoo_
#                  o8888888o
#                  88" . "88
#                  (| -_- |)
#                  O\  =  /O
#               ____/`---'\____
#             .'  \\|     |//  `.
#            /  \\|||  :  |||//  \
#           /  _||||| -:- |||||-  \
#           |   | \\\  -  /// |   |
#           | \_|  ''\---/''  |   |
#           \  .-\__  `-`  ___/-. /
#         ___`. .'  /--.--\  `. . __
#      ."" '<  `.___\_<|>_/___.'  >'"".
#     | | :  ` - `.;`\ _ /`;.`/ - ` : | |
#     \  \ `-.   \_ __\ /__ _/   .-` /  /
#======`-.____`-.___\_____/___.-`____.-'======
#                   `=---='
#^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
#            佛祖保佑       永无BUG
#*      佛曰:
#*      写字楼里写字间，写字间里程序员；
#*      程序人员写程序，又拿程序换酒钱。
#*      酒醒只在网上坐，酒醉还来网下眠；
#*      酒醉酒醒日复日，网上网下年复年。
#*      但愿老死电脑间，不愿鞠躬老板前；
#*      奔驰宝马贵者趣，公交自行程序员。
#*      别人笑我忒疯癫，我笑自己命太贱；
#*      不见满街漂亮妹，哪个归得程序员？
#*/