#include "preprocessor.h"

using namespace std;
using namespace cv;

Preprocessor::Preprocessor(unsigned short _size[2], string inP, string outP)
{
    this->size = _size;

    this->inPrefix = inP;
    this->outPrefix = outP;
}

void Preprocessor::process(string path, unsigned short* rawBbox)
{
    //Main picture preprocessing function
    //this function was designed to be able to run asynchronously

   //Input debugging
    cout << this->inPrefix + path << endl;

   //Picture loading and bbox computations
    Mat image = imread(inPrefix + path);
    short unsigned* bbox = simplifyBbox(rawBbox);

   //Generate the cropped resized picture
    Mat crop = image(Range(bbox[1], bbox[3]), Range(bbox[0], bbox[2]));
    Mat cropSized = resizeKeepRatio(crop, this->size);
    imwrite(this->outPrefix + "crop_" + path, cropSized);

    /*
   //Generate the wavelet resized picture
    Mat wavelets;
    imwrite(this->outPrefix + "wave_" + path, wavelets);

   //Generate the contout resized picture
    Mat contour;
    imwrite(this->outPrefix + "cont_" + path, contour);
    */

   //Clean after computations
    delete[] bbox;
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
    printf("%d:%d, %d %d %d %d\n", output.cols, output.rows, borders[2], borders[3], borders[0], borders[1]);
    copyMakeBorder(output, output, borders[2], borders[3], borders[0], borders[1], BORDER_REPLICATE);
    return output;
}

void normalInput(Preprocessor* preprocessor)
{
    unsigned int n;
    cin >> n;
    for (unsigned int i = 0; i < n; i++)
    {
        string file;
        cin >> file;
        short unsigned* bbox = new short unsigned[8]; //deallocated in simplifyBbox
        for (unsigned int j = 0; j < 8; j++) {cin >> bbox[j]; }
        preprocessor->process(file, bbox);
    }
}

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
}



//Code written by:
//      - Nemo Chentre
//
// Last modified: 25/04/2022