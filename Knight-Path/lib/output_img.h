#ifndef OUTPUT_IMG_H
#define OUTPUT_IMG_H

#include <graphics.h> 

void output_image();

void loadBG(char filename[]);

void loadBG(char filename[],int w,int h);

void loadCHAR(char filename[],PIMAGE **ori_img,PIMAGE **ori_msk,int w,int h, int index);

void loadCHAR(char filename[],PIMAGE **ori_img,int w,int h,int index);

void put_tp_door_img();

#endif
