# classClothes
System classifying clothes-pictures with +120 labels.

## Team
Application created by 4 students from Umeå University:
 - Arvid Börjesson
 - Némo Chentre
 - Jakob Lundkvist
 - Sairam Jasti

## Dataset
The dataset used to train the models and validate them is a **private** dataset created and owned by the french startup we are working with, *Enhancy*.

## Main application
The main application (compiled by using the *makefile* at the *root* of the directory) is a server application. You will not be able to input the data you wish to process directly into that application. To do so you need to use the client file (see next section).

### Client
The client handles the input of the server application. It will send your data to the server which will queue it for processing, but it will not gie you the output.

#### Usage:
To use the client, type: `./send.sh [file] [category]` where `[file]` is the path to the file to process (handles only relative for now) and `[category]` the category label (should be given by the compagny).

#### Options:
To start the server, simply add `-S` befor the 2 arguments: `./send.sh -S [file] [category]`.

To kill the server, you only need the kill flag `-K`. Note that sending the kill flag with a picture will not process it. `./send.sh -K`

### Output
The output should be given in text file named "[jobId]_Output.txt". The jobId will be given by the client once your data has been queued by the preprocessor.


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


