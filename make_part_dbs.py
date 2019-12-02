import os
os.system("tree Examples/training/letters")
police = int(input("\nchoose your police to train  :\n"))

for i in range(97,123):  # a-z
 	string = "./segmentation_training Examples/training/letters/%d/%d.bmp Examples/training/police%d.txt" % (i,police,police) 
	os.system(string)

for i in range(65,91): # A-Z
 	string = "./segmentation_training Examples/training/letters/%d/%d.bmp Examples/training/police%d.txt" % (i,police,police) 
	os.system(string)

for i in range(48,58): # 0-9
 	string = "./segmentation_training Examples/training/letters/%d/%d.bmp Examples/training/police%d.txt" % (i,police,police) 
	os.system(string)

i=46 # .
string = "./segmentation_training Examples/training/letters/%d/%d.bmp Examples/training/police%d.txt" % (i,police,police) 
os.system(string)

i=44 # ,
string = "./segmentation_training Examples/training/letters/%d/%d.bmp Examples/training/police%d.txt" % (i,police,police) 
os.system(string)

i=33 # !
string = "./segmentation_training Examples/training/letters/%d/%d.bmp Examples/training/police%d.txt" % (i,police,police) 
os.system(string)

i=63 # ?
string = "./segmentation_training Examples/training/letters/%d/%d.bmp Examples/training/police%d.txt" % (i,police,police) 
os.system(string)

i=45 # -
string = "./segmentation_training Examples/training/letters/%d/%d.bmp Examples/training/police%d.txt" % (i,police,police) 
os.system(string)

file = "Examples/training/police%d.txt" % police

'''fp = open(file,'a')
fp.write(224 *"0.0\n")
fp.close()'''
