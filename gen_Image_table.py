from PIL import Image, ImageDraw, ImageFont
import os


#size = int(input("choose a size for the font : (80 is good) \n")os.system("tree Examples/training/ref_images")

def make (path,size,fonts):

	img = Image.new('RGB', (2000, 2000), color = (255, 255, 255)) #Taille de l'image
	letter = "A B C D E F G H I J K L M N\n\nO P Q R S T U V W X Y Z \n\na b c d e f g h i j k l m n o p q r s\n\nt u v w x y z & 0 1 2 3 4 5 6 7 8 9\n\n( $ . , ! ? )"
	d = ImageDraw.Draw(img)
	fonts_path = os.path.join(os.path.dirname(os.path.dirname(__file__)), 'fonts')
	font = ImageFont.truetype(os.path.join(fonts_path, fonts), size )
	d.text((3,0), letter, fill=(0,0,0),font=font) #(10,10) -> position du texte. Remplacer Hello World par le texte à écrire
	path = path
	img.save(path) #Sauvegarde le fichier en pil_text.png
	# (remplacer par bmp ou ce genre de chose pour une ext. diff.)

i2 = 1
for i in range(1,51):
	print(i*2,"/100")
	font = "%d.ttf" % (i)
	size = 80
	path = "Examples/training/ref_images/police%s.bmp" % (i2)
	i2+=1
	make(path,size,font)
	size = 70
	path = "Examples/training/ref_images/police%s.bmp" % (i2)
	i2+=1
	make(path,size,font)
	size = 60
	path = "Examples/training/ref_images/police%s.bmp" % (i2)
	i2+=1
	make(path,size,font)
	size = 50
	path = "Examples/training/ref_images/police%s.bmp" % (i2)
	i2+=1
	make(path,size,font)
	size = 40
	path = "Examples/training/ref_images/police%s.bmp" % (i2)
	i2+=1
	make(path,size,font)

print ("\n /!\\ dbs Image Making : OK\n")



