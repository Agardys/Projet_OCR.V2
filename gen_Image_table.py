from PIL import Image, ImageDraw, ImageFont
import os

os.system("tree fonts")
police = input("choose a font : \n")

police += ".ttf"
#size = int(input("choose a size for the font : (80 is good) \n"))
os.system("tree Examples/training/ref_images")
num = int(input("\nchoose a number for the data : \n"))

def make (path):

	img = Image.new('RGB', (2000, 2000), color = (255, 255, 255)) #Taille de l'image
	letter = "A B C D E F G H I J K L M N\n\nO P Q R S T U V W X Y Z \n\na b c d e f g h i j k l m n o p q r s\n\nt u v w x y z & 0 1 2 3 4 5 6 7 8 9\n\n( $ . , ! ? )"
	d = ImageDraw.Draw(img)
	fonts_path = os.path.join(os.path.dirname(os.path.dirname(__file__)), 'fonts')

	size = 80
	font = ImageFont.truetype(os.path.join(fonts_path, police), size )
	d.text((3,0), letter, fill=(0,0,0),font=font) #(10,10) -> position du texte. Remplacer Hello World par le texte à écrire
	size = 40
	font = ImageFont.truetype(os.path.join(fonts_path, police), size )
	d.text((3,1000), letter, fill=(0,0,0),font=font)
	size = 20
	font = ImageFont.truetype(os.path.join(fonts_path, police), size )
	d.text((3,1500), letter, fill=(0,0,0),font=font)
	'''size = 10
	font = ImageFont.truetype(os.path.join(fonts_path, police), size )
	d.text((3,1750), letter, fill=(0,0,0),font=font)'''
	path = path
	img.save(path) #Sauvegarde le fichier en pil_text.png
	# (remplacer par bmp ou ce genre de chose pour une ext. diff.)

path = "Examples/training/ref_images/police%s.bmp" % num
make(path)


print ("\n /!\\ dbs Image Making : OK\n")



