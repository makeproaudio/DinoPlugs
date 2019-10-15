import os, re

scriptpath = os.path.dirname(os.path.realpath(__file__))
projectpath = os.path.abspath(os.path.join(scriptpath, os.pardir))

def main():
	print("writing resource files")
  
	rc=open(projectpath + "\\resources\\auto.rc", "w+")
	cf=open(projectpath + "\\resourceconfig.h", "w+")
	cf.write("//AUTO-GENERATED from python script\n")
	for(root, dirs, files) in os.walk(projectpath + "\\resources"):
		for dir in dirs:
			if dir != root and "Images.xcassets" not in dir:
				for root2, dirs2, files2 in os.walk(projectpath + "\\resources\\" + dir):
					for file in files2:
						name=os.path.splitext(file)[0].upper()
						name = re.sub(r'\W+', '', name)
						name = re.sub('\s', "", name)
						name = "FN_" + name
						ext=os.path.splitext(file)[1].upper()[1:]
						rc.write(name + " " + ext + " " + name + "\n")
						cf.write("#define " + name + " \"" + file + "\"\n")
						
if __name__ == '__main__':
	main()