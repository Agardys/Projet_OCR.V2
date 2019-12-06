import os
import sys 
from termcolor import colored
from googletrans import Translator 

os.system("ls")
file = input("\nchoose a file to translate : \n")
trans = Translator()
ff =open(file,"r").read()
print("\n")
print(ff)
res = trans.translate(ff, src = 'fr', dest = 'en')

if (0):
   print ("\n \n" + colored( "aucune traduction trouvee...",'red')+"\n \n \n \n")
else :
   print ("\n \n" +colored('traduction : ','yellow') + colored( res.text,'cyan')+ "\n \n \n \n")
