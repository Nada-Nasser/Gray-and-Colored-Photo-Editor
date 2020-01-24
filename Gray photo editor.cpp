// FCI – Programming 1 – 2018 - Assignment 3
// Program Name: photo Editor.cpp
// Last Modification Date: 12/4/2018
// Author1 and ID and Group: Nada Nasser Al-Said       20170369  G.14
// Author2 and ID and Group: Hanan Mohamed Abdelrahim  20170375  G.14
// Author3 and ID and Group: Farah Mohamed Osama       20170351  G.13
// Teaching Assistant: Eng xxxxx
// Purpose: Gray Scale Image Processor

#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include "bmplib.cpp"

using namespace std;

unsigned char input_image[SIZE][SIZE];
unsigned char input_image2[SIZE][SIZE];
unsigned char output_image[SIZE][SIZE];

void starting();
void loadImage(unsigned char img[SIZE][SIZE]);

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

void saveImage (unsigned char img[SIZE][SIZE]);//s

int main()
{
    while(true){
        char choice;
        starting();
        cin >> choice;
        if(choice!='s' && choice!='0')
           loadImage(input_image);

        if(choice == '1')
           Black_White();

        else if(choice == '2')
            Invert_filter();

        else if(choice == '3')
            Merge_filter();

        else if(choice == '4')
            Flip_Image();

        else if(choice == '5')
            Rotate_Image();

        else if(choice == '6')
            Darken_and_Lighten_Image();

        else if(choice == '7')
            Detect_Image_Edges();

        else if(choice == '8')
            Enlarge_Image();

        else if(choice == '9')
            Shrink_Image();

        else if(choice == 'a')
            Mirror_Image();

        else if(choice == 'b')
            Shuffle_Image();

        else if(choice == 'c')
            Blur_Image();

        else if(choice == 's')
            saveImage(output_image);

        else if(choice == '0')
            break;

        else
            cout << "invalid choice!!"<<endl;
    }
  return 0;
}

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
void loadImage (unsigned char img[SIZE][SIZE]) { ///FE 2L RUN BYTLB the source image file name DE 2SM 2L IMAGE 2LY HY7SLHA EDIT
   char imageFileName[100];

   // Get gray scale image file name
   cout << "please Enter the file name of image to process : ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   readGSBMP(imageFileName, img);
}
//_________________________________________
void Black_White()//1
{
    for(int i=0;i<SIZE;i++){
        for(int j=0;j<SIZE;j++){
            if(input_image[i][j]>127)
                output_image[i][j]=255;
            else
                output_image[i][j]=0;
        }
    }
}
//_________________________________________
void Invert_filter()//2
{
    for(int i=0 ; i<SIZE ;i++){
        for (int j=0 ; j<SIZE ; j++){
            if (input_image[i][j]==0){
                input_image[i][j] = 255;
            }
            else if(input_image[i][j]==255){
                input_image[i][j] = 0;
            }
            else
                input_image[i][j] = (255-input_image[i][j]);
            output_image[i][j] = input_image[i][j];
        }
    }
}
//_________________________________________
void Merge_filter()//3
{
    cout << "Please enter name of image file to merge with \n";
    loadImage(input_image2);
    for(int i=0 ; i<SIZE ;i++)
        for (int j=0 ; j<SIZE ; j++)
            output_image[i][j] = (input_image[i][j] + input_image2[i][j])/2;
}
//_________________________________________
void Flip_Image()//4
{
    char sub;
    int choice;
    cout << "please choose how you want your image to be flipped:\n"
         << "1- vertically \n"
         << "2- horizontally\n";
    cin >> choice;
    if (choice==1){
        for(int i=0 ; i<SIZE ;i++){
            for (int j=0 ; j<SIZE ; j++){
                sub=input_image[i][j];
                output_image[i][j]=input_image[SIZE-1-i][j];
                output_image[SIZE-1-i][j]=sub;
            }
        }
    }
    else{
        for(int i=0 ; i<SIZE ;i++){
            for (int j=0 ; j<SIZE ; j++){
                sub=input_image[i][j];
                output_image[i][j]=input_image[i][SIZE-j-1];
                output_image[i][SIZE-j-1]=sub;
            }
        }
    }
}
//_________________________________________
void Rotate_Image()//5
{
    cout<<"Do you want to rotate"<<endl
        <<"1. 90 degrees"        <<endl
        <<"2. 180degrees"        <<endl
        <<"3. 270 degrees"       <<endl;

    int choice;
    cin>>choice;
    if (choice == 1){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                    output_image[j][SIZE-i]= input_image[i][j];
            }
        }
    }
    if (choice == 2){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                    output_image[i][j] = input_image[SIZE-i][SIZE-j];
            }
        }
    }
    if (choice == 3){
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j< SIZE; j++) {
                    output_image[SIZE-j][i] = input_image[i][j];
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
    if(choose == 'd' || choose == 'D'){
        for(int i=0 ; i<SIZE ;i++){
            for (int j=0 ; j<SIZE ; j++){
                input_image[i][j] = input_image[i][j] - 0.5*(input_image[i][j]);
                output_image[i][j]=input_image[i][j];
            }
        }
    }
    else if(choose == 'l' || choose == 'L'){
        for(int i=0 ; i<SIZE ;i++){
            for (int j=0 ; j<SIZE ; j++){
                unsigned char x = 0.5*input_image[i][j];
                unsigned char y = (127 + x);
                if(y<=0){
                    y=y+225;
                }
                input_image[i][j]=y;
                output_image[i][j]=input_image[i][j];
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
            if(input_image[i][j]>128)
                input_image[i][j]=255;
            else
                input_image[i][j]=0;
        }
    }

    for(int i=1 ; i<SIZE-1 ;i++){
        for (int j=1 ; j<SIZE -1; j++){
            if (input_image[i][j]!=input_image[i][j-1]||
                input_image[i][j]!=input_image[i][j+1]||
                input_image[i][j]!=input_image[i-1][j]||
                input_image[i][j]!=input_image[i+1][j])
                output_image[i][j]=0;
            else
                output_image[i][j]=255;
        }
    }
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
                output_image[l][k]=input_image[i][j];
                output_image[l][k-1]=input_image[i][j];
                output_image[l-1][k]=input_image[i][j];
                output_image[l-1][k-1]=input_image[i][j];
            }
        }
    }
    if (choice==2){
        for (int i = 0, l=0; i <= SIZE/2; i++, l+=2) {
            for (int j = SIZE/2, k=0; j< SIZE; j++, k+=2){
                output_image[l][k]=input_image[i][j];
                output_image[l][k-1]=input_image[i][j];
                output_image[l-1][k]=input_image[i][j];
                output_image[l-1][k-1]=input_image[i][j];
            }
        }
    }
    if (choice == 3){
        for (int i = SIZE/2, l=0; i <= SIZE; i++, l+=2) {
            for (int j = 0, k=0; j< SIZE/2; j++, k+=2) {
                output_image[l][k]=input_image[i][j];
                output_image[l][k-1]=input_image[i][j];
                output_image[l-1][k]=input_image[i][j];
                output_image[l-1][k-1]=input_image[i][j];
            }
        }
    }
    if (choice == 4){
        for (int i = SIZE/2, l=0; i <= SIZE; i++, l+=2) {
            for (int j = SIZE/2, k=0; j< SIZE; j++, k+=2) {
                output_image[l][k]=input_image[i][j];
                output_image[l][k-1]=input_image[i][j];
                output_image[l-1][k]=input_image[i][j];
                output_image[l-1][k-1]=input_image[i][j];
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
        for(int i=0 , k=0 ; i<=128  ; i+=step , k++){
        for(int j=0 , l=0 ; j<=128  ; j+=step , l++){
            output_image[k][l]=input_image[i][j];
            }
        }
        ///Q2
        for(int i=128 , k = SIZE/quarter ; i<=SIZE     ; i+=step , k++){
        for(int j=0   ,l = 0       ; j<=128      ; j+=step , l++){
            output_image[k][l]=input_image[i][j];
            }
        }
        ///Q3:
        for(int i=0,k=0 ; i<=128 ; i+=step,k++){
        for(int j=128 , l=SIZE/quarter ; j<=SIZE ; j+=step ,l++){
                output_image[k][l]=input_image[i][j];
            }
        }
        ///Q4
        for(int i=128 , k = SIZE/quarter     ; i<=SIZE ; i+=step,k++ ){
        for(int j=128 , l = SIZE/quarter     ; j<=SIZE ; j+=step,l++){
            output_image[k][l]=input_image[i][j];
            }
        }
        for(int i=0 ; i<SIZE ; i++){
        for(int j=0 ; j<SIZE; j++){
            if(i > SIZE/step || j > SIZE/step)
                output_image[i][j]=255;
            }
        }
    }
}
void Mirror_Image()//a
{
    cout<<"choose the half you want to mirror\n"
        <<"1- Left 1/2\n"
        <<"2- Right 1/2\n"
        <<"3- Upper 1/2\n"
        <<"4- Lower 1/2\n";
    int choice;
    cin>>choice;
    switch (choice) {
        case 1:
            for(int i=0 ; i<SIZE ;i++){
                for (int j=0 ; j<SIZE/2 ; j++){
                   output_image[i][j]= input_image[i][j];
                   output_image[i][SIZE-j-1]=input_image[i][j];
                }
            }
            break;
        case 2:
            for(int i=0 ; i<SIZE ;i++){
                for (int j=0 ; j<SIZE/2 ; j++){
                   output_image[i][j]= input_image[i][SIZE-j-1];
                   output_image[i][SIZE-j-1]=input_image[i][SIZE-j-1];
                }
            }
            break;
        case 3:
            for(int i=0 ; i<SIZE/2 ;i++){
                for (int j=0 ; j<SIZE ; j++){
                   output_image[i][j]= input_image[i][j];
                   output_image[SIZE-i-1][j]=input_image[i][j];
                }
            }
            break;
        case 4:
            for(int i=0 ; i<SIZE/2 ;i++){
                for (int j=0 ; j<SIZE ; j++){
                   output_image[i][j]= input_image[SIZE-i-1][j];
                   output_image[SIZE-i-1][j]=input_image[SIZE-i-1][j];
                }
            }
            break;
    }
}
//_________________________________________
void Blur_Image()//c
{
    for(int i=0 ; i<SIZE ;i++)
        for(int j=0 ; j<SIZE ;j++)
            output_image[i][j] = ( input_image[i][j]+input_image[i+1][j+1]+input_image[i+1][j]+input_image[i][j+1]+input_image[i-1][j-1]+input_image[i-1][j]+input_image[i][j-1]
                                                    +input_image[i+4][j+4]+input_image[i+4][j]+input_image[i][j+4]+input_image[i-4][j-4]+input_image[i-4][j]+input_image[i][j-4]
                                                    +input_image[i+3][j+3]+input_image[i+3][j]+input_image[i][j+3]+input_image[i-3][j-3]+input_image[i-3][j]+input_image[i][j-3]
                                                    +input_image[i+2][j+2]+input_image[i+2][j]+input_image[i][j+2]+input_image[i-2][j-2]+input_image[i-2][j]+input_image[i][j-2] )/25 ;
}
//_________________________________________
void Shuffle_Image()
{
    int choice;
cout<<"Which order do you want to print the image"<<endl;
cout<<"1.  1-2-3-4"<<endl;
cout<<"2.  1-2-4-3"<<endl;
cout<<"3.  1-3-2-4"<<endl;
cout<<"4.  1-3-4-2"<<endl;
cout<<"5.  1-4-3-2"<<endl;
cout<<"6.  1-4-2-3"<<endl;
cout<<"7.  2-1-3-4"<<endl;
cout<<"8.  2-1-4-3"<<endl;
cout<<"9.  2-3-1-4"<<endl;
cout<<"10. 2-3-4-1"<<endl;
cout<<"11. 2-4-1-3"<<endl;
cout<<"12. 2-4-3-1"<<endl;
cout<<"13. 3-1-2-4"<<endl;
cout<<"14. 3-1-4-2"<<endl;
cout<<"15. 3-2-1-4"<<endl;
cout<<"16. 3-2-4-1"<<endl;
cout<<"17. 3-4-1-2"<<endl;
cout<<"18. 3-4-2-1"<<endl;
cout<<"19. 4-1-2-3"<<endl;
cout<<"20. 4-1-3-2"<<endl;
cout<<"21. 4-2-1-3"<<endl;
cout<<"22. 4-2-3-1"<<endl;
cout<<"23. 4-3-1-2"<<endl;
cout<<"24. 4-3-2-1"<<endl;

cin>>choice;
if (choice==1){
         for (int i = 0; i <= SIZE/2; i++) {
          for (int j = 0; j< SIZE/2; j++) {
                output_image[i][j]=input_image[i][j];
          }
         }
         for (int i = 0; i <= SIZE/2; i++) {
          for (int j = SIZE/2; j< SIZE; j++) {
                output_image[i][j]=input_image[i][j];
          }
         }
         for (int i = SIZE/2; i <= SIZE; i++) {
          for (int j = 0; j< SIZE/2; j++) {
                output_image[i][j]=input_image[i][j];
          }
         }
         for (int i = SIZE/2; i <= SIZE; i++) {
          for (int j = SIZE/2; j< SIZE; j++) {
                output_image[i][j]=input_image[i][j];
          }
         }
    }

    if (choice==2){
         for (int i = 0; i <= SIZE/2; i++) {
          for (int j = 0; j< SIZE/2; j++) {
                output_image[i][j]=input_image[i][j];
          }
         }
         for (int i = 0; i <= SIZE/2; i++) {
          for (int j = SIZE/2; j< SIZE; j++) {
                output_image[i][j]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l = SIZE/2; i <= SIZE, l<SIZE; i++, l++) {
          for (int j = SIZE/2, k = 0; j< SIZE, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l = SIZE/2; i <= SIZE, l<SIZE; i++, l++) {
          for (int j = 0, k =SIZE/2; j< SIZE/2, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
    }
    if (choice==3){
        for (int i = 0; i <= SIZE/2; i++) {
          for (int j = 0; j< SIZE/2; j++) {
                output_image[i][j]=input_image[i][j];
          }
         }
         for (int i = 0, l = SIZE/2; i <= SIZE/2, l<SIZE; i++, l++) {
          for (int j = SIZE/2, k=0; j< SIZE, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=0; i <= SIZE, l<SIZE/2; i++, l++) {
          for (int j = 0, k=SIZE/2; j< SIZE/2, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2; i <= SIZE; i++) {
          for (int j = SIZE/2; j< SIZE; j++) {
                output_image[i][j]=input_image[i][j];
          }
         }
    }
    if (choice==4){
        for (int i = 0; i <= SIZE/2; i++) {
          for (int j = 0; j< SIZE/2; j++) {
                output_image[i][j]=input_image[i][j];
          }
         }
         for (int i = 0, l=SIZE/2; i <= SIZE/2, l<SIZE; i++, l++) {
          for (int j = SIZE/2, k=SIZE/2; j< SIZE, k<SIZE; j++,k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=0; i <= SIZE, l<SIZE; i++, l++) {
          for (int j = 0, k=SIZE/2; j< SIZE/2, k<SIZE; j++,k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=SIZE/2; i <= SIZE, l<SIZE; i++, l++) {
          for (int j = SIZE/2, k=0; j< SIZE, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
    }
    if (choice==5){
    for (int i = 0; i <= SIZE/2; i++) {
          for (int j = 0; j< SIZE/2; j++) {
                output_image[i][j]=input_image[i][j];
          }
         }
         for (int i = 0, l=SIZE/2; i <= SIZE/2, l<SIZE; i++, l++) {
          for (int j = SIZE/2, k=SIZE/2; j< SIZE, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2; i <= SIZE; i++) {
          for (int j = 0; j< SIZE/2; j++) {
                output_image[i][j]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=0; i <= SIZE, l<SIZE/2; i++, l++) {
          for (int j = SIZE/2, k=SIZE/2; j< SIZE, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
    }
    if (choice==6){
        for (int i = 0; i <= SIZE/2; i++) {
          for (int j = 0; j< SIZE/2; j++) {
                output_image[i][j]=input_image[i][j];
          }
         }
         for (int i = 0, l=SIZE/2; i <= SIZE/2, l<SIZE; i++, l++) {
          for (int j = SIZE/2, k=0; j< SIZE, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=SIZE/2; i <= SIZE, l<SIZE; i++, l++) {
          for (int j = 0, k=SIZE/2; j< SIZE/2, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=0; i<= SIZE, l<SIZE/2; i++, l++) {
          for (int j = SIZE/2, k=SIZE/2; j< SIZE, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
    }
    if (choice==7){
        for (int i = 0, l=0; i <= SIZE/2, l<SIZE/2; i++, l++) {
          for (int j = 0, k=SIZE/2; j< SIZE/2, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = 0, l=0; i <= SIZE/2, l<SIZE/2; i++, l++) {
          for (int j = SIZE/2, k=0; j< SIZE, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2; i <= SIZE; i++) {
          for (int j = 0; j< SIZE/2; j++) {
                output_image[i][j]=input_image[i][j];
          }
         }
         for (int i = SIZE/2; i <= SIZE; i++) {
          for (int j = SIZE/2; j< SIZE; j++) {
                output_image[i][j]=input_image[i][j];
          }
         }
    }
    if(choice==8){
        for (int i = 0, l=0; i <= SIZE/2, l<SIZE/2; i++, l++) {
          for (int j = 0, k=SIZE/2; j< SIZE/2, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = 0, l=0; i <= SIZE/2, l<SIZE/2; i++, l++) {
          for (int j = SIZE/2, k=0; j< SIZE, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=SIZE/2; i <= SIZE, l<SIZE; i++, l++) {
          for (int j = 0, k=SIZE/2; j< SIZE/2, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=SIZE/2; i <= SIZE, l<SIZE; i++, l++) {
          for (int j = SIZE/2, k=0; j< SIZE, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
    }
    if (choice==9){
        for (int i = 0, l=SIZE/2; i <= SIZE/2, l<SIZE; i++, l++) {
          for (int j = 0, k=0; j< SIZE/2, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = 0, l=0; i <= SIZE/2, l<SIZE/2; i++, l++) {
          for (int j = SIZE/2, k=0; j< SIZE, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=0; i <= SIZE, l<SIZE/2; i++, l++) {
          for (int j = 0, k=SIZE/2; j< SIZE/2, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2; i <= SIZE; i++) {
          for (int j = SIZE/2; j< SIZE; j++) {
                output_image[i][j]=input_image[i][j];
          }
         }
    }
    if (choice==10){
        for (int i = 0, l=SIZE/2; i <= SIZE/2, l<SIZE; i++, l++) {
          for (int j = 0, k=SIZE/2; j< SIZE/2, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = 0, l=0; i <= SIZE/2, l<SIZE/2; i++, l++) {
          for (int j = SIZE/2, k=0; j< SIZE, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=0; i <= SIZE, l<SIZE/2; i++, l++) {
          for (int j = 0, k=SIZE/2; j< SIZE/2, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=SIZE/2; i <= SIZE, l<SIZE; i++,l++) {
          for (int j = SIZE/2, k=0; j< SIZE, k<SIZE/2; j++,k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
    }
    if (choice==11){
            for (int i = 0, l=SIZE/2; i <= SIZE/2, l<SIZE; i++, l++) {
          for (int j = 0, k=0; j< SIZE/2, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = 0, l=0; i <= SIZE/2, l<SIZE/2; i++, l++) {
          for (int j = SIZE/2, k=0; j< SIZE, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=SIZE/2; i <= SIZE, l<SIZE; i++, l++) {
          for (int j = 0, k=SIZE/2; j< SIZE/2, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=0; i <= SIZE, l<SIZE/2; i++,l++) {
          for (int j = SIZE/2, k=SIZE/2; j< SIZE, k<SIZE; j++,k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
    }
    if (choice==12){
        for (int i = 0, l=SIZE/2; i <= SIZE/2, l<SIZE; i++, l++) {
          for (int j = 0, k=SIZE/2; j< SIZE/2, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = 0, l=0; i <= SIZE/2, l<SIZE/2; i++, l++) {
          for (int j = SIZE/2, k=0; j< SIZE, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2; i <= SIZE; i++) {
          for (int j = 0; j< SIZE/2; j++) {
                output_image[i][j]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=0; i <= SIZE, l<SIZE/2; i++,l++) {
          for (int j = SIZE/2, k=SIZE/2; j< SIZE, k<SIZE; j++,k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
    }
    if(choice==13){
        for (int i = 0, l=0; i <= SIZE/2, l<SIZE/2; i++, l++) {
          for (int j = 0, k=SIZE/2; j< SIZE/2, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = 0, l=SIZE/2; i <= SIZE/2, l<SIZE; i++,l++) {
          for (int j = SIZE/2, k=0; j< SIZE, k<SIZE/2; j++,k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=0; i <= SIZE, l<SIZE/2; i++, l++) {
          for (int j = 0, k=0; j< SIZE/2, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2; i <= SIZE; i++) {
          for (int j = SIZE/2; j< SIZE; j++) {
                output_image[i][j]=input_image[i][j];
          }
         }
    }
    if (choice==14){
         for (int i = 0, l=0; i <= SIZE/2, l<SIZE/2; i++, l++) {
          for (int j = 0, k=SIZE/2; j< SIZE/2, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = 0, l=SIZE/2; i <= SIZE/2, l<SIZE; i++,l++) {
          for (int j = SIZE/2, k=SIZE/2; j< SIZE, k<SIZE; j++,k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=0; i <= SIZE, l<SIZE/2; i++, l++) {
          for (int j = 0, k=0; j< SIZE/2, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=SIZE/2; i <= SIZE, l<SIZE; i++, l++) {
          for (int j = SIZE/2, k=0; j< SIZE, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
    }
    if (choice==15){
         for (int i = 0, l=SIZE/2; i <= SIZE/2, l<SIZE; i++, l++) {
          for (int j = 0, k=0; j< SIZE/2, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = 0; i <= SIZE/2; i++) {
          for (int j = SIZE/2; j< SIZE; j++) {
                output_image[i][j]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=0; i <= SIZE, l<SIZE/2; i++, l++) {
          for (int j = 0, k=0; j< SIZE/2, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2; i <= SIZE; i++) {
          for (int j = SIZE/2; j< SIZE; j++) {
                output_image[i][j]=input_image[i][j];
          }
         }
    }
    if (choice==16){
         for (int i = 0, l=SIZE/2; i <= SIZE/2, l<SIZE; i++, l++) {
          for (int j = 0, k=SIZE/2; j< SIZE/2, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = 0; i <= SIZE/2; i++) {
          for (int j = SIZE/2; j< SIZE; j++) {
                output_image[i][j]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=0; i <= SIZE, l<SIZE/2; i++, l++) {
          for (int j = 0, k=0; j< SIZE/2, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=SIZE/2; i <= SIZE, l<SIZE; i++, l++) {
          for (int j = SIZE/2, k=0; j< SIZE, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
    }
    if (choice==17){
        for (int i = 0, l=SIZE/2; i <= SIZE/2, l<SIZE; i++, l++) {
          for (int j = 0, k=0; j< SIZE/2, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = 0, l=SIZE/2; i <= SIZE/2, l<SIZE; i++, l++) {
          for (int j = SIZE/2, k=SIZE/2; j< SIZE, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
          for (int i = SIZE/2, l=0; i <= SIZE, l<SIZE/2; i++, l++) {
          for (int j = 0, k=0; j< SIZE/2, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=0; i <= SIZE, l<SIZE/2; i++,l++) {
          for (int j = SIZE/2, k=SIZE/2; j< SIZE, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
    }
    if (choice==18){
          for (int i = 0, l=SIZE/2; i <= SIZE/2, l<SIZE; i++, l++) {
          for (int j = 0, k=SIZE/2; j< SIZE/2, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = 0, l=SIZE/2; i <= SIZE/2, l<SIZE; i++, l++) {
          for (int j = SIZE/2, k=0; j< SIZE, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }

          for (int i = SIZE/2, l=0; i <= SIZE, l<SIZE/2; i++, l++) {
          for (int j = 0, k=0; j< SIZE/2, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=0; i <= SIZE, l<SIZE/2; i++,l++) {
          for (int j = SIZE/2, k=SIZE/2; j< SIZE, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
    }
    if (choice==19){
        for (int i = 0, l=0; i <= SIZE/2, l<SIZE/2; i++, l++) {
          for (int j = 0, k=SIZE/2; j< SIZE/2,k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = 0, l=SIZE/2; i <= SIZE/2, l<SIZE; i++, l++) {
          for (int j = SIZE/2, k=0; j< SIZE, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=SIZE/2; i <= SIZE, l<SIZE; i++, l++) {
          for (int j = 0, k=SIZE/2; j< SIZE/2, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=0; i <= SIZE, l<SIZE/2; i++, l++) {
          for (int j = SIZE/2, k=0; j<SIZE, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
    }
    if (choice==20){
        for (int i = 0, l=0; i <= SIZE/2, l<SIZE/2; i++, l++) {
          for (int j = 0, k=SIZE/2; j< SIZE/2, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = 0, l=SIZE/2; i <= SIZE/2, l<SIZE; i++, l++) {
          for (int j = SIZE/2, k=SIZE/2; j< SIZE, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2; i <= SIZE; i++) {
          for (int j = 0; j< SIZE/2; j++) {
                output_image[i][j]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=0; i <= SIZE, l<SIZE/2; i++,l++) {
          for (int j = SIZE/2, k=0; j< SIZE, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
    }
    if (choice==21){
        for (int i = 0, l=SIZE/2; i <= SIZE/2, l<SIZE; i++, l++) {
          for (int j = 0, k=0; j< SIZE/2, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = 0; i <= SIZE/2; i++) {
          for (int j = SIZE/2; j< SIZE; j++) {
                output_image[i][j]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=SIZE/2; i <= SIZE, l<SIZE; i++, l++) {
          for (int j = 0, k=SIZE/2; j< SIZE/2, k<SIZE; j++,k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
          for (int i = SIZE/2, l=0; i <= SIZE, l<SIZE/2; i++,l++) {
          for (int j = SIZE/2, k=0; j< SIZE, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
    }
    if (choice==22){
         for (int i = 0, l=SIZE/2; i <= SIZE/2, l<SIZE; i++, l++) {
          for (int j = 0, k=SIZE/2; j< SIZE/2, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = 0; i <= SIZE/2; i++) {
          for (int j = SIZE/2; j< SIZE; j++) {
                output_image[i][j]=input_image[i][j];
          }
         }
         for (int i = SIZE/2; i <= SIZE; i++) {
          for (int j = 0; j< SIZE/2; j++) {
                output_image[i][j]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=0; i <= SIZE, l<SIZE/2; i++,l++) {
          for (int j = SIZE/2, k=0; j< SIZE, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
    }
    if (choice==23){
       for (int i = 0, l=SIZE/2; i <= SIZE/2, l<SIZE; i++, l++) {
          for (int j = 0, k=0; j< SIZE/2, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = 0, l=SIZE/2; i <= SIZE/2, l<SIZE; i++, l++) {
          for (int j = SIZE/2, k=SIZE/2; j< SIZE, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=0; i <= SIZE, l<SIZE/2; i++,l++) {
          for (int j = 0, k=SIZE/2; j< SIZE/2, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
         for (int i = SIZE/2, l=0; i <= SIZE, l<SIZE/2; i++,l++) {
          for (int j = SIZE/2, k=0; j< SIZE, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
          }
         }
    }
    if (choice==24){
        for (int i = 0, l=SIZE/2; i <= SIZE/2, l<SIZE; i++, l++) {
            for (int j = 0, k=SIZE/2; j< SIZE/2, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
            }
        }
        for (int i = 0, l=SIZE/2; i <= SIZE/2, l<SIZE; i++, l++) {
            for (int j = SIZE/2, k=0; j< SIZE, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
            }
        }
        for (int i = SIZE/2, l=0; i <= SIZE, l<SIZE/2; i++,l++) {
            for (int j = 0, k=SIZE/2; j< SIZE/2, k<SIZE; j++, k++) {
                output_image[l][k]=input_image[i][j];
            }
        }
        for (int i = SIZE/2, l=0; i <= SIZE, l<SIZE/2; i++,l++) {
            for (int j = SIZE/2, k=0; j< SIZE, k<SIZE/2; j++, k++) {
                output_image[l][k]=input_image[i][j];
            }
        }
    }
}
//_________________________________________
void saveImage (unsigned char img[SIZE][SIZE]) {
   char imageFileName[100];

   // Get gray scale image target file name
   cout << "Please enter file name to save the edited photo in : ";
   cin >> imageFileName;

   // Add to it .bmp extension and load image
   strcat (imageFileName, ".bmp");
   writeGSBMP(imageFileName, img);
}
