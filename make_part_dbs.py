import os
import time
os.system("tree Examples/training/letters")
police = int(input("\nchoose your police to train  :\n"))

t = 0 #sec
for i in range(97,123):  # a-z
	time.sleep(t)
	print "\n\n letter : ",chr(i) 
 	string = "./segmentation_training Examples/training/letters/%d/%d.bmp Examples/training/police%d.txt" % (i,police,police) 
	os.system(string)

for i in range(65,91): # A-Z
	time.sleep(t)
	print "\n\n letter : ",chr(i) 
 	string = "./segmentation_training Examples/training/letters/%d/%d.bmp Examples/training/police%d.txt" % (i,police,police) 
	os.system(string)

for i in range(48,58): # 0-9
	time.sleep(t)
	print "\n\n number : ",chr(i) 
 	string = "./segmentation_training Examples/training/letters/%d/%d.bmp Examples/training/police%d.txt" % (i,police,police) 
	os.system(string)

i=46 # .
time.sleep(t)
print "\n\n special : ",chr(i) 
string = "./segmentation_training Examples/training/letters/%d/%d.bmp Examples/training/police%d.txt" % (i,police,police) 
os.system(string)

i=44 # ,
time.sleep(t)
print "\n\n special : ",chr(i)
string = "./segmentation_training Examples/training/letters/%d/%d.bmp Examples/training/police%d.txt" % (i,police,police) 
os.system(string)

i=33 # !
print "\n\n special : ",chr(i) 
string = "./segmentation_training Examples/training/letters/%d/%d.bmp Examples/training/police%d.txt" % (i,police,police) 
os.system(string)

i=63 # ?
time.sleep(t)
print "\n\n special : ",chr(i)
string = "./segmentation_training Examples/training/letters/%d/%d.bmp Examples/training/police%d.txt" % (i,police,police) 
os.system(string)

i=45 # -
time.sleep(t)
print "\n\n letter : ",chr(i)
string = "./segmentation_training Examples/training/letters/%d/%d.bmp Examples/training/police%d.txt" % (i,police,police) 
os.system(string)

file = "Examples/training/police%d.txt" % police

fp = open(file,'a')
fp.write(224 *"0.0\n")
fp.close()

fd = open(file, 'r')
n = 0
for line in fd:
    n += 1

if (n == 15232):
	print "\n /!\\ dbs checking : OK\n"
else:
	print "\n /!\\ dbs checking : KO\n"

