# -*- coding: utf-8 -*-
"""
Created on Mon Apr 20 22:36:29 2015

@author: IMAAD AHMED, ZAHRA KHATAMI, MUSTAFA HAJIJ, ALI MOHARRER, 
AND BRANDON OUBRE
"""

from __future__ import with_statement
from sklearn.metrics import accuracy_score

from sklearn.svm import SVC
from sklearn import svm
from sklearn import metrics
import numpy as np
import matplotlib.pyplot as plt
import PIL
from PIL import Image
import pylab as pl 
import math
from sklearn import cross_validation
import time
#from sklearn.learning_curve import learning_curve
#from sklearn.learning_curve import validation_curve
#from sklearn.metrics import precision_recall_fscore_support


# simple functions needed for the kernal
########################################
##############################################################################
def symmetrize(a):
    return a + a.T - np.diag(a.diagonal())    

def getmax(data):
    
    m=np.linalg.norm(data[0])
    for i in range(1,len(data)):
        t=np.linalg.norm(data[i])
        if(t>m):
            m=t
    return m        
        
        
def normalize(data):
    
    m=getmax(data)
    normalizeddata=data
    for i in range(0,len(data)):
        normalizeddata[i]=data[i]/m
    return normalizeddata\

#this function simply sums the enties of a vector
def summation(a):
    s=0
    for i in range(len(a)):
        s=s+a[i]
    return s    

# takes two vectors of the same length and returns a vector withe the same length
#and min values component of input two vectors
        
def minvec(a,b):
    re=np.empty(len(a))
    for i in range(len(a)):
        if(a[i]<b[i]):
            re[i]=a[i]
        else:
            re[i]=b[i]
    return re          
        

def myprod(v):
    p=1;
    for i in range(len(v)):
        p=p*v[i]
    return p    
############################################################################
############################################################################




#__________________________________________________

#some error analysis stuff

def numberofspam(y_pred):
    counter=0
    for i in range(len(y_pred)):
        if(y_pred[i]==1):
            counter=counter+1
    return counter    

def numberofmisclassified(y_test,y_pred):
    counter=0
    for i in range(len(y_pred)):
        if(y_pred[i]==1 and y_test[i]==0):
            counter=counter+1
        elif(y_pred[i]==0 and y_test[i]==1):
            counter=counter+1
        else:
            continue
    return counter        

def FalsePositiveRatio(y_test,y_pred):
    allspam=numberofmisclassified(y_test,y_pred)
    counter=0
    for i in range(len(y_test)):
        if (y_test[i]==0):
            if(y_pred[i]==1):
                counter=counter+1
    if (allspam==0):
        return 0           
    return float(counter)/float(allspam)
    

def FalsePositive(y_test,y_pred):
    counter=0
    for i in range(len(y_test)):
        if (y_test[i]==0):
            if(y_pred[i]==1):
                counter=counter+1
    return counter        


#_________________________________________________________________________ 


'''
Generally, a function k(x,y): V X V -> R is a valid kernel function 
 if it satisfies three properties:
0-k is bilinear map
1-symmetry: k(x,y)=k(y,x)
2-positive semi-definiteness.
'''

#the following is a collection of custem kernels of SVM


#A cus kernel #1:

def matprod(a,b):
    ar = np.empty((len(a), len(b)))
    for i in range(len(a)):
        for j in range(len(b)):
            ar[i,j]=np.dot(a[i],b[j].T)
    return ar # return a similarity matrix

#A cus kernel #2:

def gram3(a,b):
    ar = np.zeros((len(a), len(b)))
    for i in range(0,len(a)):
        for j in range(0,len(b)):
            d=np.linalg.norm(a[i]-b[j])
            Xn=np.linalg.norm(a[i])
            Yn=np.linalg.norm(b[j])
            ar[i,j]=1-d/(Xn+Yn+1)            
    return ar
#A cus kernel #3:    
def gram5(a,b):
    ar = np.empty((len(a), len(b)))
    for i in range(len(a)):
        for j in range(len(b)):
            d=np.linalg.norm(a[i]-b[j])*np.linalg.norm(a[i]-b[j])
            ar[i,j]=1/np.sqrt(d+2)
    return ar
#A cus kernel #4:
sigma=0.1

def gram7(a,b):
    ar = np.empty((len(a), len(b)))
    for i in range(len(a)):
        for j in range(len(b)):
            d=np.linalg.norm(a[i]-b[j])
            ar[i,j]=1-3/2*(d/sigma)+1/2*(d/sigma)*(d/sigma)*(d/sigma)
    return ar

#A cus kernel #5:
gamma=0.1


def gram8(a,b):
    ar = np.empty((len(a), len(b)))
    for i in range(len(a)):
        for j in range(len(b)):
            d=np.linalg.norm(a[i]-b[j])
            ar[i,j]=-math.pow(d,gamma)
    return ar

#A cus kernel #6:
thet=0.8 
def gram10(a,b):
    ar = np.empty((len(a), len(b)))
    for i in range(len(a)):
        for j in range(len(b)):
            d=np.linalg.norm(a[i]-b[j])
            if(d<thet):
                ar[i,j]=2/np.pi*np.arccos(d/thet)-2/np.pi*(d/thet)*np.sqrt(1-(d/thet)*(d/thet))
            else:
                ar[i,j]=0        
    return ar
#A cus kernel #7:

Ce=1.1    
def compuations13(a,b):
    ar = np.zeros(len(a))
    for i in range(len(a)):
        ar[i]=(2*np.sqrt(a[i]+Ce)*np.sqrt(b[i]+Ce))/(a[i]+b[i]+2*Ce)
    return ar    

def gram13(a,b):
    ar = np.empty((len(a), len(b)))
    for i in range(len(a)):
        for j in range(len(b)):
            ar[i,j]=myprod(compuations13(a[i],b[j]))
    return np.nan_to_num(ar) # return a similarity matrix 

   


def kernalfunction(matprod,X_train,X_test,y_train,state):
    print("custom Kernel computation ...")
    svc = SVC(kernel='precomputed',probability=True, random_state=state,cache_size=7000)
    kernel_train = matprod(X_train, X_train)
    svc.fit(kernel_train, y_train)
    kernel_test = matprod(X_test, X_train)
    y_pred = svc.predict(kernel_test)
    print 'accuracy score: %0.3f' % accuracy_score(y_test, y_pred)
    print 'ratio false positive ', FalsePositiveRatio(y_test,y_pred)
    print '# of false positive ', FalsePositive(y_test,y_pred)
    print ""
    return 
#____________________________________________________________________________
#____________________________________________________________________________
#____________________________________________________________________________
#____________________________________________________________________________
#____________________________________________________________________________



#reading the data
print "reading the data set"

with open('C:\Users\steve\Desktop\machine learning project\spambase_data.txt') as f:
    lines = f.read().splitlines()

data=[]
for i in range(len(lines)):
    line=lines[i].split(",")
    nline=[float(i) for i in line]
    data.append(nline)   
X=[]
y=[]
for i in range(len(data)):
    y.append(data[i][-1])
    data[i].pop()
    X.append(data[i])
    
X=np.asarray(X)
y=np.asarray(y)      



print "Finishing loading the data..." 
#use this for some test to save time
#Xpart=X[::3]
#ypart=y[::3]

# replace X amd y here by Xpart and ypart to speed up the testing
X_train, X_test, y_train, y_test = cross_validation.train_test_split(
     X, y, test_size=0.1, random_state=0)

print(X_train.shape, y_train.shape,X_test.shape, y_test.shape)

       
       
# using SVM classifier with various kernals 
# the following are the default kernals 

print "starting SVM linear training..."   
start_time = time.clock()
linear_svm =svm.LinearSVC()
linear_svm.fit(X_train, y_train)      
linear_svm_time = time.clock() - start_time
print 'score for linear SVM', linear_svm.score(X_test, y_test)
print 'time for linear SVM', linear_svm_time


y_pred = linear_svm.predict(X)
thh=FalsePositive(y, y_pred)
print '# false score ',thh
print 'false positive ratio ', FalsePositiveRatio(y,y_pred)


print ""

#________________________________

print "starting SVM non-linear training..."   
start_time = time.clock()
kernel_svm = svm.SVC(kernel='rbf')
kernel_svm.fit(X_train, y_train)
kernel_svm_score = kernel_svm.score(X_test, y_test)
nonlinear_svm_time = time.clock() - start_time

print 'score for non linear SVM', kernel_svm_score
print 'time for non linear SVM', nonlinear_svm_time


y_pred = kernel_svm.predict(X)
thh=FalsePositive(y, y_pred)
print '# false score ',thh
print 'false positive ratio ', FalsePositiveRatio(y,y_pred)


print ""



#________________________________________

print "starting SVM non-linear training..."   
start_time = time.clock()
kernel_svm = svm.SVC(kernel='poly')
kernel_svm.fit(X_train, y_train)
kernel_svm_score = kernel_svm.score(X_test, y_test)
nonlinear_svm_time = time.clock() - start_time

print 'score for non linear SVM', kernel_svm_score
print 'time for non linear SVM', nonlinear_svm_time



y_pred = kernel_svm.predict(X_test)
thh=FalsePositive(y_test, y_pred)
print '# false score ',thh
print 'false positive ratio ', FalsePositiveRatio(y_test,y_pred)

print ""


     
for fig_num, kernel in enumerate(('linear', 'rbf', 'poly')):
    print "starting training.."
    clf = svm.SVC(kernel=kernel, gamma=10,probability=True, random_state=0,cache_size=7000)
    clf.fit(X_train, y_train)
    clf.score(X_test, y_test)
    print 'accuracy '+ kernel + ':', clf.score(X_test, y_test)
    y_pred = clf.predict(X_test)
    thh=FalsePositive(y_test, y_pred)
    print '# false score ',thh
    print 'false positive ratio ', FalsePositiveRatio(y_test,y_pred)
    print "" 

#here we using custem SVM kernels
kernalfunction(matprod,X_train,X_test,y_train,0)
kernalfunction(gram3,X_train,X_test,y_train,0)
kernalfunction(gram5,X_train,X_test,y_train,0)
kernalfunction(gram7,X_train,X_test,y_train,0)
kernalfunction(gram8,X_train,X_test,y_train,0)
kernalfunction(gram10,X_train,X_test,y_train,0)
kernalfunction(gram13,X_train,X_test,y_train,0)

