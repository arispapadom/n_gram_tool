import os
import find_frequency
from operator import itemgetter, attrgetter

def characters_n_grams(parameters, input_file, output_file):

	_input = open(input_file)
	input_file_string = _input.read()

	_output = open(output_file,'w')

	#get argument values
	n=int(parameters['n'])
	f=int(parameters['f'])
	s=int(parameters['s'])
	n_grams=[]
	final_n_gram=[]

	#reolace spaces and new linews with "_" char
	input_file_string = str.replace(input_file_string,' ','_')
	input_file_string = str.replace(input_file_string,'\n','_')

	#extract n-grams according to "n" parameter
	for i in range(0,len(input_file_string)-n+1):
		n_grams.append(input_file_string[i:i+n])

	#extract consecutive n-grams if required
	for i in range(0,len(n_grams)-s+1):
		final_n_gram.append(''.join(n_grams[i:i+s]))
	
	#sort final_ngrams according to "o" argument
	if parameters['o']==1:
		final_n_gram.sort()
	elif parameters['o']==2:
		final_n_gram.sort(reverse=True)

	#find frequencies of each n-gram
	# output -> two lists (one for n-grams and one for their frequencies)
	n_grams_f,frequencies = find_frequency.find_frequency(final_n_gram)
	
	Reverse_Key=False;

	#sort by frequency if required
	if int(parameters['o'])>2:
		if int(parameters['o'])==3:
			Reverse_Key=True
		a=zip(frequencies,n_grams_f)
		a=list(a)
		b=sorted(a,key=itemgetter(0),reverse=Reverse_Key)
		n_grams_f = [a[1] for a in b]
		frequencies = [a[0] for a in b]

	#previous -> variable to print the completed percentage
	previus=0
	#write to file according to "v" parameter
	for i in range(0,len(n_grams_f)):
		if frequencies[i]>=int(parameters['f']):
			if parameters['view']:
				_output.write(n_grams_f[i] + "\t" + str(frequencies[i]) + "\n")
			else:
				_output.write(n_grams_f[i] + "\t" + "\n")

			if(int(i*100/len(n_grams_f))-previus>1):
				os.system("clear")
				print("Finding frequencies...100%")
				print("Writing to output..." + str(int(i*100/len(n_grams_f))) + "%")
				previus=int(i*100/len(n_grams_f))

	os.system("clear")
	print("Finding frequencies...100%")
	print("Writing to output...100%")

	_input.close()
	_output.close()