import os
import sys
import string
import time
import help
import character_n_grams
import word_n_grams

def main_check():
	valid=0;
	not_valid=0;

	global parameters,argv

	parameters={'n':0,'t':'c','f':1,'s':1,'o':0,'view':0}	
	args=sys.argv

	argv=[]
	for i in range(1,len(args)):
		argv.append(args[i][0:2])

	if len(args)==2 and args[1]=='-h':
		help.call_help()
		sys.exit()
	if len(args)<=3:
		print("Not enough arguments. Type -h for help")
		sys.exit()
	if len(args)>9:
		print("Too many arguments. Type -h for help")
		sys.exit()

	for i in range(1,len(args)):
		if args[i][0]=='-':
			valid+=1
		else:
			not_valid+=1

	if not_valid>2:
		print("\nWorng syntax in input options. Type -h for help")
		sys.exit()

	if len(args)!=valid+3:
		print("\nMissing input or output file. Type -h for help")
		sys.exit()

	if '-c' in argv and '-w' in argv:
		print("\nYou can not use parameters -w  and -c at the same time. Type -h for help.")
		sys.exit()

	if not('-n' in argv):
		print("\nParameter -n is required. Type -h for help.")
		sys.exit()

	if '-w' in argv:
		parameters['t']='w'

	if '-o' in argv:
		parameters['o']=1

	if '-v' in argv:
		parameters['view']=1

	for i in range(1,len(args)-2):
		check=argv[i-1]
		more=0;
		for j in range(0,len(argv)):
			if check in argv[j]:
				more+=1;
		if more>1:
			print("\nOne option in more than one time")
			sys.exit()

		if 'n' in args[i][1] or 'f' in args[i][1] or 's' in args[i][1] or 'o' in args[i][1]:
			if str.isdecimal(args[i][2:]):
				parameters[args[i][1]]=int(args[i][2:])
				if 'o' in args[i][1] and str.isdecimal(args[i][2:]):
					if int(args[i][2:])>4:
						print("\nNumber in parameter -o can not be greater than 4. Type -h for help")
						sys.exit()
			else:
					print("\nNot a number in parameter -" + args[i][1] +". Type -h for help.")
					sys.exit()
		elif (not 'c' in args[i][1]) and (not 'w' in args[i][1]) and (not 'o' in args[i][1]) and (not 'v' in args[i][1]):
			print("\nUnknown parameter -"+ args[i][1] +". Type -h for help.") 
			sys.exit()

	if not os.path.isfile(args[len(args) - 2]):
		print("\nInput file "+ args[len(args) - 2] + " does not exist.")
		sys.exit()


main_check()
if '-w' in argv:
	start=time.time()
	word_n_grams.word_n_grams(parameters, sys.argv[len(sys.argv)-2], sys.argv[len(sys.argv)-1])
	end=time.time()
else:
	start=time.time()
	character_n_grams.characters_n_grams(parameters, sys.argv[len(sys.argv)-2], sys.argv[len(sys.argv)-1])
	end=time.time()
	
final_time = end-start

days = divmod(final_time,86400)
_hours = days[1]
days=int(days[0])
hours = divmod(_hours,3600)
_minutes = hours[1]
hours=int(hours[0])
minutes = divmod(_minutes,60)
seconds = round(minutes[1],2)
minutes=int(minutes[0])

print("\nExcecution time: Days: "+ str(days)+ " Hours: " + str(hours) + " Minutes: " + str(minutes) + " Seconds: " + str(seconds))
