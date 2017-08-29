import re
import os
import find_frequency
from operator import itemgetter, attrgetter

#den douleuei to -s

def word_n_grams(parameters, input_file, output_file):

	_input = open(input_file)
	input_file_string = _input.read()

	_output = open(output_file,'w')

	n=int(parameters['n'])
	f=int(parameters['f'])
	s=int(parameters['s'])
	n_grams=[]
	final_n_grams=[]
	final_n_gram=[]

	word_n_gramsRegex = re.compile(r"\w+")

	n_grams=word_n_gramsRegex.findall(input_file_string)
	
	for i in range(0,len(n_grams)-s+1):
		final_n_gram.append(' '.join(n_grams[i:i+s]))
	
	
	if parameters['o']==1:
		final_n_gram.sort()
	elif parameters['o']==2:
		final_n_gram.sort(reverse=True)
	
	n_grams_f,frequencies = find_frequency.find_frequency(final_n_gram)
	
	Reverse_Key=False;
	
	if int(parameters['o'])>2:
		if int(parameters['o'])==3:
			Reverse_Key=True
		a=zip(frequencies,n_grams_f)
		a=list(a)
		b=sorted(a,key=itemgetter(0),reverse=Reverse_Key)
		n_grams_f = [a[1] for a in b]
		frequencies = [a[0] for a in b]
	
	previus=0	
	for i in range(0,len(n_grams_f)):
		if frequencies[i]>=int(parameters['f']):
			if parameters['view']:
				_output.write(n_grams_f[i] + "\t" + str(frequencies[i]) + "\n")
			else:
				_output.write(n_grams_f[i] + "\t" + "\n")
			

			if(int(i*100/len(n_grams_f))-previus>1):
				os.system("cls")
				print("Finding frequencies...100%")
				print("Writing to output..." + str(int(i*100/len(n_grams_f))) + "%")
				previus=int(i*100/len(n_grams_f))

	os.system("cls")
	print("Finding frequencies...100%")
	print("Writing to output...100%")

	_input.close()
	_output.close()