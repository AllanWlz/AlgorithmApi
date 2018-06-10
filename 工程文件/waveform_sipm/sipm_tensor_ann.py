# -*- coding: utf-8 -*-
"""
Created on Mon Apr 10 14:46:31 2017

@author: Mr-Wlz
"""
import input_sipm_data

import numpy as np

sipm_training_data=input_sipm_data.read_data_sets("K:/DATA/waveform/非零积分信号输出/0.8_output/training_set")

sipm_test_data=input_sipm_data.read_data_sets("K:/DATA/waveform/非零积分信号输出/0.8_output/test_set")

sipm_verifying_data=input_sipm_data.read_data_sets("K:/DATA/waveform/非零积分信号输出/0.8_output/verifying_set")
#----------------------------

import tensorflow as tf

#from tensorflow.python import debug as tf_debug

runing_time = 10000

num_of_nodes = 10

sess = tf.InteractiveSession()

with tf.device('/cpu:0'):
    
    target_row = 37
    #----------------------------
    
    x = tf.placeholder(tf.float32, shape=(None, 36))
    
    y_ = tf.placeholder(tf.float32, shape=(None, 1))
    
    #----------------------------
    
    W1 = tf.Variable(tf.truncated_normal([36,num_of_nodes]))
    
    b1 = tf.Variable(tf.truncated_normal([num_of_nodes]))
    
    h1 =  2 * tf.nn.sigmoid(tf.matmul(x,W1) + b1) - 1
    
    W2 = tf.Variable(tf.truncated_normal([num_of_nodes,num_of_nodes]))
    
    b2 = tf.Variable(tf.truncated_normal([num_of_nodes]))
    
    h2 =  2 * tf.nn.sigmoid(tf.matmul(h1,W2) + b2)- 1
    
    W3 = tf.Variable(tf.truncated_normal([num_of_nodes,1]))
    
    b3 = tf.Variable(tf.truncated_normal([1]))
    
#    h3 =  2 * tf.nn.sigmoid(tf.matmul(h1,W2) + b2)- 1
    
#    W4 = tf.Variable(tf.truncated_normal([num_of_nodes,1]))
    
#    b4 = tf.Variable(tf.truncated_normal([1]))
    
    
    
    y = tf.matmul(h2,W3) + b3
    
    cross_entropy = tf.reduce_sum(tf.square(y_-y))
    
    train_step = tf.train.GradientDescentOptimizer(0.00001).minimize(cross_entropy)
    
    #sess = tf_debug.LocalCLIDebugWrapperSession(sess)
    sess.run(tf.global_variables_initializer())
    
    for i in range(runing_time):
    
      batch = sipm_training_data.next_batch(5000)
    
      a = batch[:,0:36]
    
      b = batch[:,target_row].reshape(5000,1)
    
      sess.run(train_step,feed_dict = {x: a, y_: b})
      
      #print(cross_entropy.eval(feed_dict = {x: a, y_: b}))
    
    average = tf.reduce_mean(y - y_)
    
    totol_variance = tf.square(y - y_ - average)
    
    variance = tf.reduce_mean(totol_variance)
    
    a = sipm_test_data.data[:,0:36]
    
    b = sipm_test_data.data[:,target_row].reshape(sipm_test_data.size[1],1)
    
    print('runing_time = %d'%(num_of_nodes))
    
    print('num_of_nodes = %d '%(num_of_nodes))
    
    print('std =  %f' %(np.sqrt(variance.eval(feed_dict = {x: a, y_: b}))))
    
    print('avg_err = %f'%(average.eval(feed_dict = {x: a, y_: b})))
    
    
    #print(variance.eval(feed_dict = {x: a, y_: b}))



#^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
#                    _ooOoo_
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
#^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^