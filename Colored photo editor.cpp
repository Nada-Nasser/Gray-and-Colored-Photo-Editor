// FCI – Programming 1 – 2018 - Assignment 3
// Program Name: photo Editor.cpp
// Last Modification Date: 12/4/2018
// Author1 and ID and Group: Nada Nasser Al-Said       20170369  G.14
// Author2 and ID and Group: Hanan Mohamed Abdelrahim  20170375  G.14
// Author3 and ID and Group: Farah Mohamed Osama       20170351  G.13
// Teaching Assistant: Eng xxxxx
// Purpose: colors Scale Image Processor

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;

unsigned char input_image[SIZE][SIZE][RGB];
unsigned char input_image2[SIZE][SIZE][RGB];
unsigned char output_image[SIZE][SIZE][RGB];

void starting();
void loadImage(unsigned char img[SIZE][SIZE][RGB]);

void Black_White();//1
void Invert_filter();//2
void Merge_filter();//3
void Flip_Image();//4
void Rotate_Image();//5
void Darken_and_Lighten_Image();//6
void Detect_Image_Edges();//7
void Enlarge_Image();///8
void Shrink_Image();//9

void Mirror_Image();//a
void Shuffle_Image();//b
void Blur_Image();//c

void saveImage (unsigned char img[SIZE][SIZE][RGB]);//s

int main()
{
    cout << "It's My Bonus";
    while(true){
        char choice;
        starting();
        cin >> choice;
        if(choice!='s' && choice!='0'){
           loadImage(input_image);
        }
        if(choice == '1'){
            Black_White();
        }
        else if(choice == '2'){
            Invert_filter();
        }
        else if(choice == '3'){
            Merge_filter();
        }
        else if(choice == '4'){
            Flip_Image();
        }
        else if(choice == '5'){
            Rotate_Image();
        }
        else if(choice == '6'){
            Darken_and_Lighten_Image();
        }
        else if(choice == '7'){
            Detect_Image_Edges();
        }
        else if(choice == '8'){
            Enlarge_Image();
        }
        else if(choice == '9'){
            Shrink_Image();
        }
        else if(choice == 's'){
            saveImage(output_image);
        }
        else if(choice == 'c'){
            Blur_Image();
        }
        else if(choice == '0'){
            break;
        }
        else
            cout << "invalid choice!!"<<endl;
    }
  return 0;
}
//_________________________________________
void starting()
{
    cout << "\nAhlan ya user ya habibi :D\n";
    cout << "Please select a filter to apply or 0 to exit: \n";
    cout << "1- Black & White Filter\n"
         << "2- Invert Filter\n"
         << "3- Merge Filter\n"
         << "4- Flip Image\n"
         << "5- Rotate Image\n"
         << "6- Darken and Lighten Image\n"
         << "7- Detect Image Edges\n"
         << "8- Enlarge Image\n"
         << "9- Shrink Image\n"
         << "a- Mirror 1/2 Image\n"
         << "b- Shuffle Image\n"
         << "c- Blur Image\n"
         << "s- Save the image to a file\n"
         << "0- Exit\n";
}
//_________________________________________
void loadImage (unsigned char img[SIZE][SIZE][RGB])
{
    char imageFileName[100];

    // Get gray scale image file name
    cout << "Enter the source image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    readRGBBMP(imageFileName, img);
}
//_________________________________________
void Black_White()//1
{
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
             int k=0;
            if( (input_image[i][j][k] + input_image[i][j][k+1] + input_image[i][j][k+2])/3 > 128 )
                for( k=0; k<RGB ; k++)
                        output_image[i][j][k] = 255;
            else
                for( k=0 ; k<RGB ;k++)
                        output_image[i][j][k] = 0;
        }
    }
}
//_________________________________________
void Invert_filter()//2
{
    for(int i=0 ; i<SIZE ;i++){
        for (int j=0 ; j<SIZE ; j++){
            for(int k=0 ; k<RGB ; k++){
                if (input_image[i][j][k]==0){
                    input_image[i][j][k] = 255;
                }
                else if(input_image[i][j][k]==255){
                    input_image[i][j][k] = 0;
                }
                else
                    input_image[i][j][k] = (255-input_image[i][j][k]);
                output_image[i][j][k] = input_image[i][j][k];
            }
        }
    }
}
//_________________________________________
void Merge_filter()//3
{
    cout << "Please enter name of image file to merge with \n";
    loadImage(input_image2);
    for(int i=0 ; i<SIZE ;i++){
        for (int j=0 ; j<SIZE ; j++){
            for(int k=0 ; k<RGB ; k++){
                unsigned char x = (input_image[i][j][k]+140)/2;
                unsigned char y = (input_image2[i][j][k]+140)/2;
                output_image[i][j][k] = (x + y)/2;
            }
        }
    }
}
//_________________________________________
void Flip_Image()//4
{
    char sub;
    int choice;
    cout<<"please choose how you want your imageto be flipped: \n"
        <<"1- vertically \n"
        <<"2- horizontally\n\n";
    cin>>choice;
    if (choice==1){
        for(int i=0 ; i<SIZE ;i++){
            for (int j=0 ; j<SIZE ; j++){
                for(int k=0 ; k<RGB ; k++){
                    sub=input_image[i][j][k];
                    output_image[i][j][k]=input_image[SIZE-1-i][j][k];
                    output_image[SIZE-1-i][j][k]=sub;
                }
            }
        }
    }
    else{
        for(int i=0 ; i<SIZE ;i++){
            for (int j=0 ; j<SIZE ; j++){
                for(int k=0 ; k<RGB ; k++){
                    sub=input_image[i][j][k];
                    output_image[i][j][k]=input_image[i][SIZE-j-1][k];
                    output_image[i][SIZE-j-1][k]=sub;
                }
            }
        }
    }
}
//_________________________________________
void Rotate_Image()//5
{
    cout<<"Do you want to rotate"<<endl<<"1. 90 degrees"<<endl<<"2. 180degrees"<<endl<<"3. 270 degrees"<<endl;
    int choice;
    cin>>choice;
    if (choice == 1){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                for(int k=0 ; k<RGB ; k++)
                    output_image[j][SIZE-i][k]= input_image[i][j][k];
            }
        }
    }
    if (choice == 2){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                for(int k=0 ; k<RGB ; k++)
                    output_image[i][j][k] = input_image[SIZE-i][SIZE-j][k];
            }
        }
    }
    if (choice == 3){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                for(int k=0 ; k<RGB ; k++)
                    output_image[SIZE-j][i][k]= input_image[i][j][k];
            }
        }
    }
}
//_________________________________________
void Darken_and_Lighten_Image()//6
{
    char choose;
    cout << "Do you want to (d)arken or (l)ighten?";
    cin >> choose;
    if(choose == 'd'){
        for(int i=0 ; i<SIZE ;i++){
            for (int j=0 ; j<SIZE ; j++){
                for(int k=0 ; k<RGB ; k++){
                    input_image[i][j][k] = input_image[i][j][k] - 0.5*(input_image[i][j][k]);
                    output_image[i][j][k]=input_image[i][j][k];
                }
            }
        }
    }
    else if(choose == 'l'){
        for(int i=0 ; i<SIZE ;i++){
            for (int j=0 ; j<SIZE ; j++){
                for(int k=0 ; k<RGB ; k++){
                    unsigned char x = 0.5*input_image[i][j][k];
                    unsigned char y = (127 + x);
                    if(y<=0){
                        y=y+225;
                    }
                    input_image[i][j][k]=y;
                    output_image[i][j][k]=input_image[i][j][k];
                }
            }
        }
    }
    else {
        cout <<"invalid choice\n";
    }
}
//_________________________________________
void Detect_Image_Edges()//7
{
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            for( int k=0 ; k<RGB ; k++)
                if(input_image[i][j][k]>128)
                    input_image[i][j][k]=255;
                else
                    input_image[i][j][k]=0;
        }
    }

    for(int i=1 ; i<SIZE-1 ;i++){
        for (int j=1 ; j<SIZE -1; j++){
            for( int k=0 ; k<RGB ; k++)
                if (input_image[i][j][k]!=input_image[i][j-1][k]||
                    input_image[i][j][k]!=input_image[i][j+1][k]||
                    input_image[i][j][k]!=input_image[i-1][j][k]||
                    input_image[i][j][k]!=input_image[i+1][j][k])
                    output_image[i][j][k]=0;
                else
                    output_image[i][j][k]=255;
        }
    }
    /*for(int i=0 ; i<SIZE ; i++){
        for(int j=0 ; j<SIZE ; j++){
            int k=0;
            if((input_image[i][j][k]-input_image[i+1][j+1][k]>40) || (input_image[i][j][k]-input_image[i+1][j][k]>40) || (input_image[i][j][k]-input_image[i][j+1][k]>40) ||(input_image[i][j][k]-input_image[i-1][j-1][k]>40) || (input_image[i][j][k]-input_image[i-1][j][k]>40) || (input_image[i][j][k]-input_image[i][j-1][k]>40) ){
                for( k=0 ; k<RGB ; k++)
                    output_image[i][j][k]=0;
            }
            else{
                for( k=0 ; k<RGB ; k++)
                    output_image[i][j][k]=255;}
        }
    }*/
}
//_________________________________________
void Enlarge_Image(){
    cout<<"which quarter do you want to enlarge?"<<endl
        <<"1. First quarter" <<endl
        <<"2. second quarter"<<endl
        <<"3. Third quarter" <<endl
        <<"4. Fourth quarter"<<endl;
    int choice;
    cin>>choice;
    if (choice==1){
        for (int i = 0, l=0; i <= SIZE/2; i++, l+=2) {
            for (int j = 0, k=0; j< SIZE/2; j++, k+=2) {
                for(int r=0 ; r<RGB ; r++){
                    output_image[l][k][r]=input_image[i][j][r];
                    output_image[l][k-1][r]=input_image[i][j][r];
                    output_image[l-1][k][r]=input_image[i][j][r];
                    output_image[l-1][k-1][r]=input_image[i][j][r];
                }
            }
        }
    }
    if (choice==2){
        for (int i = 0, l=0; i <= SIZE/2; i++, l+=2) {
            for (int j = SIZE/2, k=0; j< SIZE; j++, k+=2){
                 for(int r=0 ; r<RGB ; r++){
                    output_image[l][k][r]=input_image[i][j][r];
                    output_image[l][k-1][r]=input_image[i][j][r];
                    output_image[l-1][k][r]=input_image[i][j][r];
                    output_image[l-1][k-1][r]=input_image[i][j][r];
                 }
            }
        }
    }
    if (choice == 3){
        for (int i = SIZE/2, l=0; i <= SIZE; i++, l+=2) {
            for (int j = 0, k=0; j< SIZE/2; j++, k+=2) {
                for(int r=0 ; r<RGB ; r++){
                    output_image[l][k][r]=input_image[i][j][r];
                    output_image[l][k-1][r]=input_image[i][j][r];
                    output_image[l-1][k][r]=input_image[i][j][r];
                    output_image[l-1][k-1][r]=input_image[i][j][r];
                }
            }
        }
    }
    if (choice == 4){
        for (int i = SIZE/2, l=0; i <= SIZE; i++, l+=2) {
            for (int j = SIZE/2, k=0; j< SIZE; j++, k+=2) {
                for(int r=0 ; r<RGB ; r++){
                    output_image[l][k][r]=input_image[i][j][r];
                    output_image[l][k-1][r]=input_image[i][j][r];
                    output_image[l-1][k][r]=input_image[i][j][r];
                    output_image[l-1][k-1][r]=input_image[i][j][r];
                }
            }
        }
    }
}
//_________________________________________
void Shrink_Image()//9
{
    int step;
    int quarter;
    bool is_valid = true;
    char choose;
    cout << "Shrink to :\n1-(1/2) \n2-(1/3) \n3-(1/4)?";
    cin >> choose;
    if(choose == '1'){
        step = 2;
        quarter = 4;
    }
    else if(choose == '2'){
        step = 3;
        quarter = 6;
    }
    else if(choose == '3'){
        step = 4;
        quarter = 8;
    }
    else{
        cout << "invalid choice\n";
        is_valid = false;
    }
    if(is_valid){
        ///Q1:
        for(int i=0 , k=0 ; i<=128  ; i+=step , k++){
            for(int j=0 , l=0 ; j<=128  ; j+=step , l++){
                for(int m=0 , n=0 ; m<RGB   ; m++  , n++)
                    output_image[k][l][m]=input_image[i][j][n];
            }
        }
        ///Q2
        for(int i=128,k = SIZE/quarter ; i<=SIZE ; i+=step,k++){
            for(int j=0,l = 0 ; j<=128 ; j+=step,l++){
                for(int m=0 , n=0 ; m<RGB   ; m++  , n++)
                    output_image[k][l][m]=input_image[i][j][n];
            }
        }
        ///Q3:
        for(int i=0, k=0 ; i<=128 ; i+=step,k++){
            for(int j=128,l=SIZE/quarter ; j<=SIZE ; j+=step,l++){
                for(int m=0 , n=0 ; m<RGB   ; m++  , n++)
                    output_image[k][l][m]=input_image[i][j][n];
            }
        }
        ///Q4
        for(int i=128 , k = SIZE/quarter ; i<=SIZE ; i+=step,k++ ){
            for(int j=128,l = SIZE/quarter ; j<=SIZE ; j+=step,l++){
                for(int m=0 , n=0 ; m<RGB   ; m++  , n++)
                    output_image[k][l][m]=input_image[i][j][n];
            }
        }
        ///To make what's left of image white :
        for(int i=0 ; i<SIZE ; i++){
            for(int j=0 ; j<SIZE; j++){
                for(int k=0 ; k<RGB ; k++){
                    if(i > SIZE/step || j > SIZE/step)
                    output_image[i][j][k]=255;
                }
            }
        }
    }
}
//_________________________________________
void Blur_Image()//c
{
        for(int i=0 ; i<SIZE ;i++)
        for(int j=0 ; j<SIZE ;j++)
        for(int k=0 ; k<RGB ;k++)
            output_image[i][j][k] = (input_image[i][j][k]+input_image[i+1][j+1][k]+input_image[i+1][j][k]+input_image[i][j+1][k]+input_image[i-1][j-1][k]+input_image[i-1][j][k]+input_image[i][j-1][k]
                                    +input_image[i][j][k]+input_image[i+4][j+4][k]+input_image[i+4][j][k]+input_image[i][j+4][k]+input_image[i-4][j-4][k]+input_image[i-4][j][k]+input_image[i][j-4][k]
                                    +input_image[i][j][k]+input_image[i+3][j+3][k]+input_image[i+3][j][k]+input_image[i][j+3][k]+input_image[i-3][j-3][k]+input_image[i-3][j][k]+input_image[i][j-3][k]
                                    +input_image[i][j][k]+input_image[i+5][j+5][k]+input_image[i+5][j][k]+input_image[i][j+5][k]+input_image[i-5][j-5][k]+input_image[i-5][j][k]+input_image[i][j-5][k]
                                    +input_image[i][j][k]+input_image[i+6][j+6][k]+input_image[i+6][j][k]+input_image[i][j+6][k]+input_image[i-6][j-6][k]+input_image[i-6][j][k]+input_image[i][j-6][k]
                                    +input_image[i][j][k]+input_image[i+2][j+2][k]+input_image[i+2][j][k]+input_image[i][j+2][k]+input_image[i-2][j-2][k]+input_image[i-2][j][k]+input_image[i][j-2][k] )/42;

}
//_________________________________________
void saveImage (unsigned char img[SIZE][SIZE][RGB])
{
    char imageFileName[100];

    // Get gray scale image target file name
    cout << "Enter the target image file name: ";
    cin >> imageFileName;

    // Add to it .bmp extension and load image
    strcat (imageFileName, ".bmp");
    writeRGBBMP(imageFileName, img);
}
