# -*- coding: utf-8 -*-
"""
Created on Mon Apr 10 14:46:31 2017

@author: Mr-Wlz
"""
import input_sipm_data

import tensorflow as tf

import numpy as np

import time

sipm_training_data=input_sipm_data.read_data_sets("K:/DATA/wave/training_set")

sipm_test_data=input_sipm_data.read_data_sets("K:/DATA/wave/test_set")

sipm_verifying_data=input_sipm_data.read_data_sets("K:/DATA/wave/verifying_set")

##########################################
num_of_nodes = 20

num_of_inputs = 36

num_of_loops = 1000000

batch_size_start = 100

batch_size_end = 100000

lamda1 = 0.01;

lamda2 = 0.001;

lamda3 = 0.001;
#########################################
sess = tf.InteractiveSession()
    #----------------------------
with tf.device('/cpu:0'):   
    
    x = tf.placeholder(tf.float32, shape=(None, num_of_inputs))
    
    y_ = tf.placeholder(tf.float32, shape=(None, 1))
        
#----------------------------
        
    W1 = tf.Variable(tf.truncated_normal([num_of_inputs,num_of_nodes],0,5))
        
    b1 = tf.Variable(tf.truncated_normal([num_of_nodes]))
        
    h1 =  2 * tf.nn.sigmoid(tf.matmul(x,W1) + b1) - 1
        
   # W2 = tf.Variable(tf.truncated_normal([num_of_nodes,num_of_nodes],0,5))
        
   # b2 = tf.Variable(tf.truncated_normal([num_of_nodes]))
        
   # h2 =  2 * tf.nn.sigmoid(tf.matmul(h1,W2) + b2)- 1
        
    W3 = tf.Variable(tf.truncated_normal([num_of_nodes,1],0,100))
        
    b3 = tf.Variable(tf.truncated_normal([1]))
        
    #h3 =  2 * tf.nn.sigmoid(tf.matmul(h1,W2) + b2)- 1
        
    #W4 = tf.Variable(tf.truncated_normal([num_of_nodes,1]))
        
    #b4 = tf.Variable(tf.truncated_normal([1]))
        
    y = tf.matmul(h1,W3) + b3
    
    cross_entropy = tf.reduce_sum(tf.square(y_-y)) #+ lamda1 * tf.reduce_sum(tf.reduce_sum(tf.square(W1))) + lamda2 * tf.reduce_sum(tf.reduce_sum(tf.square(W2))) + lamda3 * tf.reduce_sum(tf.square(W3))
        
    train_step = tf.train.AdamOptimizer(learning_rate=0.1, beta1=0.6, beta2=0.9, epsilon=1e-05, use_locking=False).minimize(cross_entropy)
    #GradientDescentOptimizer
    #AdamOptimizer(learning_rate=0.1, beta1=0.95, beta2=0.99, epsilon=1e-08, use_locking=False)
    average = tf.reduce_mean(y - y_)
    
    totol_variance = tf.square(y - y_ - average)
        
    variance = tf.reduce_mean(totol_variance)
        
    test_a = sipm_test_data.data[:,0:num_of_inputs]
        
    test_b = sipm_test_data.data[:,num_of_inputs].reshape(sipm_test_data.size[1],1)
    
    training_a = sipm_training_data.data[:,0:num_of_inputs]
        
    training_b = sipm_training_data.data[:,num_of_inputs].reshape(sipm_training_data.size[1],1)
    
    #sess = tf_debug.LocalCLIDebugWrapperSession(sess)
    
    time0 = time.time()
    
    sess.run(tf.global_variables_initializer())
    
    for i in range(num_of_loops):
        
        batch_size = int(((batch_size_end - batch_size_start) / num_of_loops) * i) + batch_size_start
        
#       batch_size = 2000
        
        batch = sipm_training_data.next_batch(batch_size)

        a = batch[:,0:num_of_inputs]

        b = batch[:,num_of_inputs].reshape(batch_size,1)

        sess.run(train_step,feed_dict = {x: a, y_: b})
        
        if i % 1000 == 0:
      
            print('Had Finished : %d'%(i))
    
            time1 = time.time()
      
            print('Total time used: %f s'%(time1 - time0))
      
            print('std =  %f' %(np.sqrt(variance.eval(feed_dict = {x: test_a, y_: test_b}))))
            
  #          print('std =  %f' %(np.sqrt(variance.eval(feed_dict = {x: training_a, y_: training_b}))))
            
            print('Batchsize = %d'%(batch_size))
            
            print('\r\n')
        
     #       print(sess.run(W2))
            
     #      print(sess.run(W1))
          # print(sess.run(lamda1 * tf.reduce_sum(tf.reduce_sum(tf.square(W1))) + lamda2 * tf.reduce_sum(tf.reduce_sum(tf.square(W2))) + lamda3 * tf.reduce_sum(tf.square(W3))))
    #print(cross_entropy.eval(feed_dict = {x: a, y_: b}))
        
    
        
#    print(num_of_nodes)
#        
#    print(np.sqrt(variance.eval(feed_dict = {x: a, y_: b})))
#        
#    print(average.eval(feed_dict = {x: a, y_: b}))
#        
#    print(a[1,0:50])
        
#    print(y.eval(feed_dict = {x: a, y_: b}))
    

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