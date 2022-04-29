# classClothes
System classifying clothes-pictures with +120 labels.

## Preprocessor
If you'd like to use the preprocessor only, use the makefile named ´MakefilePrepro´ located in the ´extra´ directory.

### Preprocessor input
First, input the amount of picture you'd like to process.
Then, for each picture, enter the path of the desired picture (without the input prefix, see next section) then the 8 coordinates of the bbox.

### Prefixes and size
There are 2 prefixes, the input (which goes before the inputed picture path, basically the path to the dataset directory) and the output one (all the output pictures will be placed in the same directory architecture as they were inputed). You moight wanna place the processed pictures in a different folder, if so just change the output prefix in the file ´mainPrepro.cpp´.
You can also change the size of the outputed picture in this file (line 13).

### Wavelets options
Change these in the ´preprocessor.cpp´ file. Know that changing this file might break the automatic labelization.


