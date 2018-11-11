import os


'''
***********************************************
***											***
***			find frequencies				***
***											***
***********************************************
'''


def find_frequency(n_grams):
	n_grams_f=[]
	frequency=[]
	j=0;
	previus=0

	for i in n_grams:
		if i in n_grams_f:
			position = n_grams_f.index(i)
			frequency[position] = int(frequency[position]) +1
		else:
			n_grams_f.append(i)
			frequency.append(1)
		
		if (int(j*100/len(n_grams))-previus>1):
			os.system("clear")
			print("Finding frequencies..." + str(int(j*100/len(n_grams))) + "%")
			previus=int(j*100/len(n_grams))
		j+=1;

	os.system("clear")
	print("Finding frequencies...100%")
	return n_grams_f,frequency

