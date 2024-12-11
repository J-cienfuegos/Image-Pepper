#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

/***********************************************************************************
*************************
* read an image from a given file, the file contains data in the following
format:
* string_representing_an_identifier
* int_for_image_width int_for_image_height
* int_for_max_pixel_value
* 2D_array_representing_pixel_values
*
* parameters:
* filename: a string representing the name of the file containing the
image
* image: a 2D array that holds the pixel values
* col: an integer that represents the width of an image (no. of
pixels per row)
* row: an integer that represents the height of an image (no. of
pixels per col)
* maxVal: an integer that represents the maximum pixel value
* p_val: a string that represents the image identifier
*
* return: no return values
***********************************************************************************
*************************/

void readImage(char filename[], int image[700][700], int &col, int &row,
               int &maxVal, char p_val[]) {
  
  ifstream myImage(filename);
  if (!myImage.is_open()) {
    cout << "The file could not be opened." << endl;
  }
  
  myImage >> p_val;
  myImage >> col;
  myImage >> row;
  myImage >> maxVal;
  
  // Read contents from file into image array
  for (int r = 0; r < row; r++) {
    for (int c = 0; c < col; c++) {
      myImage >> image[r][c];
    }
  }
  
  // Display the image array when the input file reading is "sample_image.pgm"
    for (int r = 0; r < row; r++){
      for (int c = 0; c < col; c++){
        cout << image[r][c] << " ";
      }
      cout << endl;
    }
  myImage.close();
}

/***********************************************************************************
****************************
* saves an image to a given file, the file should contain data in the following
format:
* string_representing_an_identifier
* int_for_image_width int_for_image_height
* int_for_max_pixel_value
* 2D_array_representing_pixel_values
*
* parameters:
* filename: a string representing the name of the file into which the
image should be saved
* pepper: a 2D array that holds the pixel values of the processed
image
* col: an integer that represents the width of an image (no. of
pixels per row)
* row: an integer that represents the height of an image (no. of
pixels per col)
* maxVal: an integer that represents the maximum pixel value
* p_val: a string that represents the image identifier
*
* return: no return values
***********************************************************************************
*************************/

void saveImage(char filename[], int pepper[700][700], int col, int row,
               int maxVal, char p_val[]) {
  ofstream myImage;
  myImage.open(filename);
  cout << "p_val is " << p_val << endl;
  cout << "col is: " << col << endl;
  cout << "row is: " << row << endl;
  cout << "maxVal is: " << maxVal << endl;

  myImage << p_val << endl;
  myImage << col << " " << row << endl;
  myImage << maxVal << endl;

  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      myImage << pepper[i][j] << " ";
    }
    myImage << "\n";
  }
  myImage.close();
}

void sumArray(int image[700][700], int sum[][700], int row, int col) {
    for (int r = 0; r < row; r++){
      for(int c = 0; c < col; c++){
        int currentsum = 0;
        
        for(int dr = -1; dr <= 1; dr++){
          for(int dc = -1; dc <= 1; dc++){
              int nr = r + dr;
              int nc = c + dc;
            
              if (nr < 0) nr = 0;
              if (nr >= row) nr = row - 1;
              if (nc < 0) nc = 0;
              if (nc >= col) nc = col - 1;

              currentsum += image[nr][nc];
          }
        }
        sum[r][c] = currentsum;
      }
    }
}

void averageArray(int sum[700][700], double avg[][700], int col, int row) {
    for ( int r = 0; r < row; r++){
      for ( int c = 0; c < col; c++){
        avg[r][c] = sum[r][c] / 9.0;
      }
    }
}

void pepperImage(int image[700][700], double avg[][700], int col, int row) {
    for (int r = 0; r < row; r++){
      for (int c = 0; c < col; c++){
          if (image[r][c] > avg[r][c]){
              image[r][c] = 0;
          }
      }
    }
}

int main(){
  char filename[20] = "sample_image.pgm";
  int image[700][700]; 
  int sum[700][700];
  int col, row, maxVal;
  double avg[700][700]; 
  char p_val[] = "P2";
  
  // Read the image.pgm
  readImage(filename, image, col, row, maxVal, p_val);
  
  // Find the sum of pixels
  sumArray(image, sum, row, col);
  
  // Find the average of pixels
  averageArray(sum, avg, col, row);
  
  // Pepper the image
  pepperImage(image, avg, col, row);
  
  // Save the resulting image to peppered_image.pgm
  strcpy(filename, "peppered_image.pgm");
  saveImage(filename, image, col, row, maxVal, p_val);
  
  return 0;
}