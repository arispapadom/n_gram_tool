def call_help():
	print("")
	print("N-grams tool V1.0 : N-grams extraction tool")
	print("\nCopyright: Aristeidis Papadomanolakis, papadomano@ceid.upatras.gr")
	print("\nThis software is available for non-commercial use only.")
	print("It must not be modified and distributed without prior permission")
	print("of the author. The author is not responsible for implications from")
	print("the use of this software.")
	print("\n usage: n_grams_tool.py [options] input_file output_file")
	print("\noptions: ")
	print("\t option1: -w \t extraction of word n-grams")
	print("\t          -c \t extraction of character n-grams")
	print("\t   default: -c\n")
	print("\n\t option2: -n[number] \t extraction of [number]-grams")
	print("\t   parameter required")
	print("\n\t option3: -f[number] \t output n-grams with frequency >= [number]")
	print("\t   default: if parameter does not exist all n-grams produced")
	print("\n\t option4: -s[number] \t manage [number] consecutive n-grams")
	print("\t   default: -s1\n")
	print("\t option5: -v \t make visible the frequencies to the output\n")
	print("\t option6: -o1 \t output in n-gram descending order")
	print("\t          -o2 \t output in n-gram ascending order")
	print("\t          -o3 \t output in frequencies descending order")
	print("\t          -o4 \t output in frequencies ascending order")
	print("\t   default: extracts n-grams according to the input\n")
	print("\nArguments:")
	print("\t input_file -> file you want to transform in n-grams")
	print("\t output_file -> file you want to save the output n-grams")