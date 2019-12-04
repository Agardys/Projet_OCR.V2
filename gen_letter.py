from PIL import Image, ImageDraw, ImageFont
import os

os.system("tree fonts")
police = input("choose a font : \n")

police += ".ttf"
size = int(input("choose a size for the font : \n"))
os.system("tree Examples/training/letters")
num = int(input("\nchoose a number for the data : \n"))

def make (letter,path):

	img = Image.new('RGB', (30, 30), color = (255, 255, 255)) #Taille de l'image
	letter = letter
	d = ImageDraw.Draw(img)
	fonts_path = os.path.join(os.path.dirname(os.path.dirname(__file__)), 'fonts')
	font = ImageFont.truetype(os.path.join(fonts_path, police), size )
	d.text((3,0), letter, fill=(0,0,0),font=font) #(10,10) -> position du texte. Remplacer Hello World par le texte à écrire
	path = path
	img.save(path) #Sauvegarde le fichier en pil_text.png
	# (remplacer par bmp ou ce genre de chose pour une ext. diff.)


for i in range(97,123):  # a-z
	path = "Examples/training/letters/%d/%d.bmp" % (i,num)
	make(chr(i),path)

for i in range(65,91): # A-Z
 	path = "Examples/training/letters/%d/%d.bmp" % (i,num)
 	make(chr(i),path)

for i in range(48,58): # 0-9
 	path = "Examples/training/letters/%d/%d.bmp" % (i,num)
 	make(chr(i),path)

i=46 # .
path = "Examples/training/letters/%d/%d.bmp" % (i,num)
make(chr(i),path)

i=44 # ,
path = "Examples/training/letters/%d/%d.bmp" % (i,num)
make(chr(i),path)

i=33 # !
path = "Examples/training/letters/%d/%d.bmp" % (i,num)
make(chr(i),path)

i=63 # ?
path = "Examples/training/letters/%d/%d.bmp" % (i,num)
make(chr(i),path)

i=45 # -
path = "Examples/training/letters/%d/%d.bmp" % (i,num)
make(chr(i),path)

