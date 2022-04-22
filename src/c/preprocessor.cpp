#include "preprocessor.h"

using namespace std;
using namespace cv;

Preprocessor::Preprocessor(unsigned short _size[2])
{
    this->size = _size;
}

void Preprocessor::process(string path, unsigned short* bbox)
{
    cout << path << endl;

    for (int i = 0; i < 8; i++) {cout << bbox[i] << " ";}
    cout << endl;

    //Mat inpImg = imread(path);
    //cout << inpImg.size().width << inpImg.size().height << endl;
}

void normalInput(Preprocessor* preprocessor)
{
    unsigned int n;
    cin >> n;
    short unsigned* bbox = new short unsigned[8];
    for (unsigned int i = 0; i < n; i++)
    {
        string file;
        cin >> file;
        for (unsigned int j = 0; j < 8; j++) {cin >> bbox[j]; }
        preprocessor->process(file, bbox);
    }
    delete[] bbox;
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