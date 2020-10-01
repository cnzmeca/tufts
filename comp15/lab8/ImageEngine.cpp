/*
 * ImageEngine.cpp
 *
 *   Created on:  Mar 29, 2015
 *       Author:  Chris Gregg
 *  Modified by:  Mark A. Sheldon, Fall 2016
 *                Sent error output to cerr.
 *                Checked for successful opening of output file.
 *                Miscelaneous code reorganization.
 */

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "ImageEngine.h"

using namespace std;

ImageEngine::ImageEngine()
{
	// Nothing to do
}

ImageEngine::~ImageEngine()
{
	// Nothing to do
}

//
// reads in a ppm file into Image
//
void ImageEngine::readImage(std::string filename)
{
	ifstream inputFile;

	inputFile.open(filename.c_str());
	if (not inputFile.is_open())  {
		cerr << "Unable to open file.\n";
		exit(1);
	}
        image.colors.clear();
        inputFile >> image.magic_number;
        inputFile >> image.width;
        inputFile >> image.height;
        inputFile >> image.max_color;
        cout << image.width << "," << image.height << "\n";
        // read in the colors
        for (int r = 0; r < image.height; r++) {
                vector<rgb> image_row;
                for (int c = 0; c < image.width; c++) {
                        rgb color;
                        inputFile >> color.red;
                        inputFile >> color.green;
                        inputFile >> color.blue;
                        image_row.push_back(color);
                }
                image.colors.push_back(image_row);
        }
}

//
// copy current image's metadata to new image
//
void ImageEngine::copyMetadata(Image &new_image)
{
	new_image.magic_number = image.magic_number;
	//new_image.comment    = image.comment;
	new_image.max_color    = image.max_color;
	new_image.width        = image.width;
	new_image.height       = image.height;
}

//
// scale the image up depending on factor
// Process: repeat each character in each
// row and each character in each column
//
void ImageEngine::scale_up(int factor)
{
	Image new_image;
	copyMetadata(new_image);

	for (int i = 0; i < image.height; i++)
	{
		vector<rgb> temp;
		for (int j = 0; j < image.width; j++)
		{
			for (int k = 0; k < factor; k++)
				temp.push_back(image.colors[i][j]);
		}
		for (int j = 0; j < factor; j++)
			new_image.colors.push_back(temp);
	}

	new_image.height *= factor;
	new_image.width *= factor;
	
	// copy new image to old image (vectors can do this
	// with an assignment overload)
	image = new_image;
}

//
// scale the image down depending on factor
// where factor means "divide image by factor"
// e.g., a factor of 2 will make the image twice as
// small in each direction
//
void ImageEngine::scale_down(int factor)
{
	Image new_image;
	copyMetadata(new_image);

	new_image.height /= factor;
	new_image.width /= factor;

	for (int i = 0; i < new_image.height; i++)
	{
		vector<rgb> temp;
		for (int j = 0; j < new_image.width; j++)
			temp.push_back(image.colors[factor*i][factor*j]);
		new_image.colors.push_back(temp);
	}
	// TODO: Students write code here

	// copy new image to old image (vectors can do this
	// with an assignment overload!)
	image = new_image;
}

//
// mirror the image left/right
//
void ImageEngine::mirror()
{
	Image new_image;
	copyMetadata(new_image);

	for (int i = 0; i < image.height; i++)
        {
                vector<rgb> temp;
                for (int j = image.width-1; j >= 0; j--)
                        temp.push_back(image.colors[i][j]);
                new_image.colors.push_back(temp);
        }

	
	// TODO: Students write code here

	// copy new image to old image (vectors can do this
	// with an assignment overload!)
	image = new_image;
}

//
// flip the image upside down
//
void ImageEngine::flip()
{
	Image new_image;
	copyMetadata(new_image);

	for (int i = image.height-1; i > 0; i--)
        {
                vector<rgb> temp;
                for (int j = 0; j < image.width; j++)
                        temp.push_back(image.colors[i][j]);
                new_image.colors.push_back(temp);
        }
	// TODO: Students write code here

	// copy new image to old image (vectors can do this
	// with an assignment overload!)
	image = new_image;
}

//
// this rotates the color scheme
// as follows: r-g-b becomes b-r-g
//
void ImageEngine::psychedelic()
{
	Image new_image;
	copyMetadata(new_image);

	for (int i = 0; i < image.height; i++)
        {
                vector<rgb> temp;
                for (int j = 0; j < image.width; j++)
                {
			rgb add;
			add.red = image.colors[i][j].green;
			add.green = image.colors[i][j].blue;
			add.blue = image.colors[i][j].red;
			
                	temp.push_back(add);
                }
                new_image.colors.push_back(temp);
        }

	// TODO: Students write code here

	// copy new image to old image (vectors can do this
	// with an assignment overload!)
	image = new_image;
}

//
// Save the current image into the named file.
//
void ImageEngine::save(string filename)
{
	ofstream outputfile;

	outputfile.open (filename.c_str());
        if (not outputfile.is_open()) {
                cerr << "Unable to open output file:  " << filename << endl;
                exit(1);
        }
	outputfile << image.magic_number << "\n";
	outputfile << image.width << " " << image.height << "\n";
	outputfile << image.max_color << "\n";
	vector<vector<rgb> >::iterator r;
	vector<rgb>::iterator c;

	for (r = image.colors.begin(); r != image.colors.end(); ++r) {
		for (c = r->begin(); c < r->end(); ++c) {
			outputfile << c->red   << " ";
			outputfile << c->green << " ";
			outputfile << c->blue  << "  ";
		}
		outputfile << "\n";
	}
	outputfile.close();
}
