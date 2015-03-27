# First we download the spam data from the UCI repository website:

url<-"http://archive.ics.uci.edu/ml/machine-learning-databases/spambase/spambase.data"

# Then we locate all of data into a particular table, called "spamtable"
spamtable<-read.table(file=url,header=FALSE,sep=",")

# The spam data, is ordered by the last column! So basiacally, all the "spam (1)" 
# classes are at the top of the table, and all of the "Not Spam (1)" cases are
# at the bottom. Hence, we should shuffle the rows of "spamtable" in order to
# obtain a more general training data:
spamtable<-spamtable[sample(nrow(spamtable)),]

# Let's find the dimension of "spamtable"
dim(spamtable)

# This table has 4601 samples, each having 57 attributes, and the 58th column is
# the binary classification => {1,0}
# First, let's divide the input matrix, from the classifying vector:
X<-spamtable[,1:57]
Y<-spamtable[,58]

# where X is the input matrix and Y is the output (spam or not-spam) vector 
# Then, let's use 800 samples as training data, and 400 samples as test data
trainX<-X[1:800,]
trainY<-Y[1:800]
testX<-X[801:1200,]
testY<-Y[801:1200]

# R programming language requires the output vectors, explicitly factorized into
# {0,1} (or TRUE, FALSE) binary reponses, so:
trainY<-factor(trainY)
testY<-factor(testY)

#Now, we are ready to perform C5.0 algorithm on training dataset:
library(C50)
spamtree<-C5.0(trainX,trainY,trials=1)

# We set the trial=1, this basically means that algorithm runs just one time
# Since, C5.0 finds the "locally optimal" Decision Tree, it might be better
# to run this algorithm several times in order to find the best choice among
# those trials.
# Now, we obtained the DT "spamtree" using C5.0
# Let's find its certain performance metrics:
summary(spamtree)

# So basically this description shows the rules, in which each decision has
# been made. Then in "Decision Tree" part, the size of the tree (i.e., the
#number of its nodes, including both internal and leaves) is shown, as well
# as its Error rate (and also the number of incorrectly classified examples:
# which might be due to noisy data, or some lost attributes)
# Then it shows each class: 0 or 1, and shows the number of missclassified
# data at each class.
# The attributes section, still sort of unclear to us! It might show the 
# contribution rate for each of 57 (or less) attributes
# Now, before testing the spamtree performance on test data, let's plot
# the decision tree first. We will plot it into an external image file named 
# "spamDT.tiff":
tiff("spamDT.tiff",width=40,height=15,units='in',res=150)
plot(spamtree,trial=0,subtree=NULL)
dev.off()

# basically, since we have only one trial, we should set trial=0
# Also, subtree=NULL means we want to plot all the tree,
# we can change subtree, to e.g., subtree=4, then the plot shows all the
# structure below the node 4.
# Now, let's find the predictive performance of "spamtree" on the test data:
pred<-predict(spamtree,testX,type="class")

# Basically, "pred" is a vector, with boolean predictions, either 0 or 1
# type="class" means we need "pred" to be a boolean vector. We can change 
# type="prob", then "pred" vector gives us the ratios(probabilities)
# of each of 0 and 1 classes, for each row of testX (maybe then majority vote
# gives us the predicted answer)
# anyway, in order to test the performance, we can compare the "pred" vector
# with actual response vector testY, and obtain the performance:
performance<-sum(pred==testY)/length(testY)
