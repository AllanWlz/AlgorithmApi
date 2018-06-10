# -*- coding: utf-8 -*-
"""
Created on Tue May 23 22:21:10 2017

@author: wangl
"""

import input_sipm_data

import tensorflow as tf

import numpy as np

import time

sipm_training_data=input_sipm_data.read_data_sets("C:/DATA/wave/training_set")

sipm_test_data=input_sipm_data.read_data_sets("C:/DATA/wave/test_set")

sipm_verifying_data=input_sipm_data.read_data_sets("C:/DATA/wave/verifying_set")


##########################################
num_of_nodes = 6

num_of_inputs = 36

num_of_loops = 10000

batch_size_start = 50

batch_size_end = 50

#########################################

x = tf.placeholder(tf.float32, shape=(None, num_of_inputs))
    
y_ = tf.placeholder(tf.float32, shape=(None, 1))

#########################################

def weight_variable(shape):
  initial = tf.truncated_normal(shape, stddev=1)
  return tf.Variable(initial)

def bias_variable(shape):
  initial = tf.constant(0.1, shape=shape)
  return tf.Variable(initial)

def conv2d(x, W):
  return tf.nn.conv2d(x, W, strides=[1, 1, 1, 1], padding='SAME')

def max_pool_2x2(x):
  return tf.nn.max_pool(x, ksize=[1, 2, 2, 1],
                        strides=[1, 2, 2, 1], padding='SAME')
  
  #######################################
  
sess = tf.InteractiveSession()

W_conv1 = weight_variable([3, 3, 1, 32])

b_conv1 = bias_variable([32])

x_image = tf.reshape(x, [-1,6,6,1])

h_conv1 =  2 * tf.nn.sigmoid(conv2d(x_image, W_conv1) + b_conv1) - 1

W_conv2 = weight_variable([3, 3, 32, 64])

b_conv2 = bias_variable([64])

h_conv2 =  2 * tf.nn.sigmoid((conv2d(h_conv1, W_conv2) + b_conv2)) - 1

W_fc1 = weight_variable([6 * 6 * 64, 512])

b_fc1 = bias_variable([512])

h_pool2_flat = tf.reshape(h_conv2, [-1, 6 * 6 * 64])

h_fc1 =  2 * tf.nn.sigmoid((tf.matmul(h_pool2_flat, W_fc1) + b_fc1)) - 1

keep_prob = tf.placeholder("float")

h_fc1_drop = tf.nn.dropout(h_fc1, keep_prob)

W_fc2 = weight_variable([512, 1])

b_fc2 = bias_variable([1])

y_conv=tf.matmul(h_fc1_drop, W_fc2) + b_fc2

cross_entropy = tf.reduce_sum(tf.square(y_- y_conv)) 

train_step = tf.train.AdamOptimizer(1e-4).minimize(cross_entropy)
    #learning_rate=0.1, beta1=0.95, beta2=0.99, epsilon=1e-08, use_locking=False
average = tf.reduce_mean(y_conv - y_)

totol_variance = tf.square(y_conv - y_ - average)
    
variance = tf.reduce_mean(totol_variance)
    
test_a = sipm_test_data.data[:,0:num_of_inputs]
    
test_b = sipm_test_data.data[:,num_of_inputs].reshape(sipm_test_data.size[1],1)

training_a = sipm_training_data.data[:,0:num_of_inputs]
    
training_b = sipm_training_data.data[:,num_of_inputs].reshape(sipm_training_data.size[1],1)

#sess = tf_debug.LocalCLIDebugWrapperSession(sess)

time0 = time.time()

sess.run(tf.global_variables_initializer())

for i in range(num_of_loops):
    
#    batch_size = int(((batch_size_end - batch_size_start) / num_of_loops) * i) + batch_size_start
    
#       batch_size = 2000

    batch_size = 1000
    
    batch = sipm_training_data.next_batch(batch_size)

    a = batch[:,0:num_of_inputs]

    b = batch[:,num_of_inputs].reshape(batch_size,1)

    sess.run(train_step,feed_dict = {x: a, y_: b,keep_prob: 0.5})
    
    if i % 200 == 0:
  
        print('Had Finished : %d'%(i))

        time1 = time.time()
  
        print('Total time used: %f s'%(time1 - time0))
  
        print('std =  %f' %(np.sqrt(variance.eval(feed_dict = {x: test_a, y_: test_b,keep_prob: 1}))))
        
        print('std =  %f' %(np.sqrt(variance.eval(feed_dict = {x: a, y_: b,keep_prob: 1}))))
        
#        print('std =  %f' %(np.sqrt(variance.eval(feed_dict = {x: training_a, y_: training_b}))))
        
        print('Batchsize = %d'%(batch_size))
        
        print('\r\n')