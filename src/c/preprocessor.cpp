#include "preprocessor.h"

using namespace std;
using namespace cv;

#define WAVELET_LEVEL 4

Preprocessor::Preprocessor(unsigned short _size[2], string inP, string outP)
{
    this->size = _size;

    this->inPrefix = inP;
    this->outPrefix = outP;

    createPathIfNotExist(outP);
}

string Preprocessor::getOutPath() {return this->outPrefix; }

void Preprocessor::process(unsigned int id, string path, unsigned short* rawBbox)
{
    //Main picture preprocessing function
    //this function was designed to be able to run asynchronously

   //Input debugging
    string inPath = inPrefix + path;
    //string outPath = outPrefix + path.substr(0, path.find_last_of("/")+1);
    string outPath = outPrefix;
    //string outName = path.substr(path.find_last_of("/")+1);
    string outName = to_string(id) + ".jpg";

    if (!doesPathExist(inPath))
    {
        delete[] rawBbox; 
        printf("Error: File `%s` not reachable !\n", inPath.c_str());
        return;
    }

   //Picture loading and bbox computations
    Mat image = imread(inPrefix + path);
    short unsigned* bbox = simplifyBbox(rawBbox);

   //Generate the cropped resized picture
    Mat crop = image(Range(bbox[1], bbox[3]), Range(bbox[0], bbox[2]));
    unsigned short size2[2] = {this->size[0]*2, this->size[1]*2};
    //resize to 2 times final size (for wavelets)
    crop = resizeKeepRatio(crop, size2);
    Mat waveSrc = Mat(crop.cols, crop.rows, CV_32FC1);
    crop.copyTo(waveSrc);
    //resize to final size
    crop = resizeKeepRatio(crop, this->size);

    //Generate the gray frame
    Mat grayFrame = Mat(crop.cols, crop.rows, CV_8UC1);
    cvtColor(crop, grayFrame, COLOR_BGR2GRAY);
   
   //Generate the wavelet resized picture
    //Generate the gray wavelet source picture
    Mat grayWavelet = Mat(waveSrc.cols, waveSrc.rows, CV_8UC1);
    cvtColor(waveSrc, grayWavelet, COLOR_BGR2GRAY);
    grayWavelet.convertTo(waveSrc, CV_32FC1);
    //Generate the 2 wavelet pictures
    Mat waveH = Mat(crop.cols, crop.rows, CV_32FC1);
    Mat waveV = Mat(crop.cols, crop.rows, CV_32FC1);
    genWavelets(waveSrc, waveH, waveV, 4, HARD, 30);

    /*
   //Generate the contout resized picture
    Mat contour;
    */

    //check if path exists
    createPathIfNotExist(outPath);
    imwrite(outPath + "crop_" + outName, crop);
    imwrite(outPath + "gray_" + outName, grayFrame);
    imwrite(outPath + "wavH_" + outName, waveH);
    imwrite(outPath + "wavV_" + outName, waveV);
    //imwrite(outPath + "cont_" + outName, contour);
    
   //Clean after computations
    delete[] bbox;
}

void Preprocessor::processWithoutBbox(unsigned int id, string path)
{
    //Main picture preprocessing function
    //this function was designed to be able to run asynchronously

   //Input debugging
    string inPath = inPrefix + path;
    //string outPath = outPrefix + path.substr(0, path.find_last_of("/")+1);
    string outPath = outPrefix;
    //string outName = path.substr(path.find_last_of("/")+1);
    string outName = to_string(id) + ".bmp";

    if (!doesPathExist(inPath))
    {
        printf("Error: File `%s` not reachable !\n", inPath.c_str());
        return;
    }

    unsigned short size2[2] = {this->size[0]*2, this->size[1]*2};
   //Picture loading and bbox computations
    Mat image = imread(inPrefix + path);
    //Resize to 2*final size (for wavelets)
    image = resizeKeepRatio(image, size2);
    Mat waveSrc = Mat(image.cols, image.rows, CV_32FC1);
    image.copyTo(waveSrc);
    //Resize to size (for final pictures)
    image = resizeKeepRatio(image, this->size);
    Mat crop = Mat(image.cols, image.rows, CV_32FC1);
    image.copyTo(crop);

    //Generate the gray frame
    Mat grayFrame = Mat(crop.cols, crop.rows, CV_8UC1);
    cvtColor(crop, grayFrame, COLOR_BGR2GRAY);
   
   //Generate the wavelet resized picture
    //Transform the source picture to gray levels
    Mat grayWavelet = Mat(waveSrc.cols, waveSrc.rows, CV_8UC1);
    cvtColor(waveSrc, grayWavelet, COLOR_BGR2GRAY);
    grayWavelet.convertTo(waveSrc, CV_32FC1);
    //Generate the 2 wavelets pictures
    Mat waveH = Mat(crop.cols, crop.rows, CV_32FC1);
    Mat waveV = Mat(crop.cols, crop.rows, CV_32FC1);
    genWavelets(waveSrc, waveH, waveV, 4, HARD, 30);

    /*
   //Generate the contout resized picture
    Mat contour;
    */

    //check if path exists
    createPathIfNotExist(outPath);
    imwrite(outPath + "crop_" + outName, crop);
    imwrite(outPath + "gray_" + outName, grayFrame);
    imwrite(outPath + "wavH_" + outName, waveH);
    imwrite(outPath + "wavV_" + outName, waveV);
    //imwrite(outPath + "cont_" + outName, contour);
}

short unsigned* simplifyBbox(short unsigned* bbox)
{
    //Process the bbox to turn it into the smallest square including
    // every points of the stated bbox.
    //Output a 2 points (4 numbers) bbox and delete the input array.

    short unsigned* newBbox = new short unsigned[4]; //deallocated in process
    //Compute
    newBbox[0] = min(min(bbox[0], bbox[2]), min(bbox[4], bbox[6]));
    newBbox[1] = min(min(bbox[1], bbox[3]), min(bbox[5], bbox[7]));
    newBbox[2] = max(max(bbox[0], bbox[2]), max(bbox[4], bbox[6]));
    newBbox[3] = max(max(bbox[1], bbox[3]), max(bbox[5], bbox[7]));
    delete[] bbox; //free the inputed bbox allocated before calling preprocess
    return newBbox;
}

Mat resizeKeepRatio(Mat image, short unsigned* size)
{
    Mat output;
    double scaleFactor = max((image.rows/(double)size[0]), (image.cols/(double)size[1])); //Compute scaling factor
    short unsigned dstSize[2] = {image.cols/scaleFactor, image.rows/scaleFactor}; //Compute destination size with the good aspect ration
    resize(image, output, Size(dstSize[0], dstSize[1]), INTER_LINEAR);
    unsigned short borders[4] = {(size[0]-output.cols)/2+(size[0]-output.cols)%2,
                                (size[0]-output.cols)/2,
                                (size[1]-output.rows)/2+(size[1]-output.rows)%2,
                                (size[1]-output.rows)/2};
    copyMakeBorder(output, output, borders[2], borders[3], borders[0], borders[1], BORDER_REPLICATE);
    return output;
}

void normalInput(Preprocessor* preprocessor)
{
    unsigned int n;
    unsigned int id;
    string file;
    cin >> n;
    for (unsigned int i = 0; i < n; i++)
    {
        if (i%(n/80) == 0)
        {
            cout << "[" << string(((i/(double)n))*80, '#') << string(((1-(i/(double)n))*80), ' ') << "]" << endl;
            //printf("Processing... Please wait. Only %.3f percent left...\n", (1-(i/(double)n))*100);
        }
        cin >> id;
        cin >> file;
        short unsigned* bbox = new short unsigned[8]; //deallocated in simplifyBbox
        for (unsigned int j = 0; j < 8; j++) {cin >> bbox[j]; }
        preprocessor->process(id, file, bbox);
    }
}

/*
void csvInput(Preprocessor* preprocessor, string path)
{
    //Fucking annoying function that doesn't work
    cout << "opening file" << endl;
    fstream fin;
    fin.open(path, ios::in);

    vector<string> row;
    string line, word, temp;

    string file;
    short unsigned* bbox = new unsigned short[8];
    cout << "parsing file" << endl;
    while (fin >> temp)
    {
        row.clear();
        getline(fin, line);
        stringstream s(line);
        while(getline(s, word, ','))
        {
            row.push_back(word);
        }
        cout << row[0] << 1 << endl;
        path = row[0];
        cout << 3 << endl;
        for (unsigned short i = 0; i < 8; i++) 
        {
            cout << i << endl;
            short unsigned a = atoi(row[i+1].c_str());
            bbox[i] = a; 
        }
        cout << 2 << endl;
        preprocessor->process(file, bbox);
    }
    delete[] bbox;
}*/



//Code written by:
//      - Nemo Chentre
//
// Last modified: 27/04/2022