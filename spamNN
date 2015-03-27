#Using Neural Network:
# The package used is "neuralnet", which uses "resilient backpropagation" 
# method to train the neural network's structure.

# We read the spam data from the UCI website
# Again we shuffle the rows of spam table to have mixed outputs
library("neuralnet")
url<-"http://archive.ics.uci.edu/ml/machine-learning-databases/spambase/spambase.data"
spamtable<-read.table(file=url,header=FALSE,sep=",")
spamtable<-spamtable[sample(nrow(spamtable)),]

# The Matrix X is the input matrix, and Y is the output vector
X<-spamtable[,1:57]
Y<-spamtable[,58]

# trainX and trainY are for obtaining the neural networks
trainX<-X[1:800,]
trainY<-Y[1:800]

# we evaluate the performance using testX and testY 
testX<-X[801:1200,]
testY<-Y[801:1200]

# For neural network input arguments, we should combine 
# both trainX and trainY together
# Also, each of the columns should have a name, here we name
# each columns as "Vi"
train<-cbind(trainX,trainY)
colnames(train)<-c("V1","V2","V3","V4","V5","V6","V7","V8",
"V9","V10","V11","V12","V13","V14","V15","V16","V17","V18","V19","V20",
"V21","V22","V23","V24","V25","V26","V27","V28","V29","V30","V31","V32",
"V33","V34","V35","V36","V37","V38","V39","V40","V41","V42","V43","V44",
"V45","V46","V47","V48","V49","V50","V51","V52","V53","V54","V55","V56",
"V57","trainY")


trainY<-factor(trainY)
testY<-factor(testY)

# Now using "neuralnet" function, we can obtain the Neural network for our
# data. Since, thereare 57 different columns in the input matrix
# hence we only use the first 9 attributes to obtain the NN.
# Also, our NN has two hidden layers, each having 5 nodes
# the "threshold" value shows the  the threshold for the partial 
# derivatives of the error function as stopping criteria.
# also "rprop+" is the resilient backpropagation method
network<-neuralnet(trainY~V1+V2+V3+V4+V5+V6+V7+V8+V9,
train,hidden=c(3,6),threshold=0.02,algorithm='rprop+')

# Let's plot the neural network: The Error part in the plot shows the
# MSE between trainY, which is the output for training dataset,
# and the output for NN
#jpeg(file="D://LSU//Spring 2015//Machine Learning//Project//R//spamNN.jpeg",
#width = 12, height = 17, unit="in",res=200)
#plot(network,file="spamNN.jpeg")
#dev.off()
plot(network)


# In this part we compute the MSE of NN regarding to training set
# First we compute the NN output, using the attributes V1 to V9 in trainX
train_result<-compute(network,trainX[,1:9])$net.result

# Then we round the real outputs of NN, into binary output 0 or 1
# Basically we "clip" the vector train_result, using "pmin" and "pmax"
# Functions, by limiting all the values to be either 0 or 1
# In future, we should refine this function, and use some other proper methods
binary_train_result<-pmin(pmax(round(train_result),0),1)
train_output<-Y[1:800]

# Finally, we find the sum of all cases, where output of NN and true output are
# different. Also, we compute train_error, which is basically the MSE
# of NN for training data set, and for our proposed "threshold" function
print(sum(abs(train_output-binary_train_result)))
train_error<-sum((train_output-binary_train_result)^2)/2
print(train_error)

# The same procedure goes for the test data
test_result<-compute(network,testX[,1:9])$net.result
binary_test_result<-pmin(pmax(round(test_result),0),1)
true_test_value<-Y[801:1200]
print(sum(abs(binary_test_result-true_test_value)))
test_error<-sum((binary_test_result-true_test_value)^2)/2
print(test_error)
