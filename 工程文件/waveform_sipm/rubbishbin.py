# -*- coding: utf-8 -*-
"""
Created on Sun Oct 15 19:20:51 2017

@author: wangl
"""

p = np.zeros(8)
p[3] = point_y[0]
p[7] = point_x[0]
p[0] = (point_y[1] - p[3]) / l  
p[4] = (point_x[1] - p[7]) / l  
p[1] = (point_y[2] - p[3]) / l  
p[5] = (point_x[2] - p[7]) / l
p[2] = (point_y[3] - p[3] - p[0] * l - p[1] * l) / (l * l)  
p[6] = (point_x[3] - p[7] - p[4] * l - p[5] * l) / (l * l)  
for i in np.arange(l):
    for j in np.arange(l):
        [x,y] = QRF.deformation(i,j,p)
        imgout[i,j] = img0[x,y]