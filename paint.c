/*
paint.c
Copyright (C) 2019 Akshay Devan

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
*/

#include"text.h"

int screen_start = 0;
int screen_end = 0;
int curnt_line = 26;

int char_start = 0;
int char_end = 0;
int curnt_char = 80;
struct winsize term;
int resized = 0;
void status_bar(int,int);

void paint(int x,int y,int file_size){
    int i,j,ret;
    ioctl(STDOUT_FILENO,TIOCGWINSZ,&term);
    curnt_line = term.ws_row - 2;
    curnt_char = term.ws_col - 3;
    system("clear");
    status_bar(x,y);
    printf("%c[%d;%dH",27,1,1);
    
    if(y>=curnt_line){
        screen_start = y-(term.ws_row-2);
        curnt_line = y;
        y = y-screen_start;
        screen_end = screen_start + (term.ws_row-2);
    } else if(y>=screen_start){
        y = y-screen_start;
        screen_end = screen_start + (term.ws_row-2);
    } else {
        screen_start = screen_end - (term.ws_row-1);
        screen_end = screen_start + (term.ws_row-2);
        curnt_line = screen_end;
        y = 0;
    }
    
    if(x>=curnt_char){
        char_start = x-(term.ws_col-4);
        curnt_char = x;
        x = x-char_start;
        char_end = char_start + (term.ws_col-4);
    } else if(x>=char_start){
        x = x-char_start;
        char_end = char_start + (term.ws_col-4);
    } else {
        char_start = x;
        char_end = char_start + (term.ws_col-4);
        curnt_char = char_end;
        x = 0;
    }
    
    for(i=screen_start;i<=screen_end && getmem(j,i) != -1;i++){
        for(j=char_start;
            j<=char_end && getmem(j,i)!='\0' && getmem(j,i)!=10 && getmem(j,i)!=-1;
            j++)
            {
                printf("%c",getmem(j,i));
            }
        printf("\n\r");
    }
    printf("%c[%d;%dH",27,y+1,x+1);
}

void status_bar(int x,int y){
    int i = 0;
    ioctl(STDOUT_FILENO,TIOCGWINSZ,&term);
    printf("%c[%d;%dH",27,term.ws_row,0);
    printf("\e[k\e[48;2;255;255;255m");
    printf("\e\033[1m");
    while(i<term.ws_col){
        printf(" ");
        i++;        
    }
    printf("\e[k\e[38;2;0;0;0m");
    printf("%c[%d;%dH",27,term.ws_row,0);
    printf("Line %d,column %d",y+1,x+1);
    printf("%c[%d;%dH",27,term.ws_row,40);
    printf("%s",file_name);
    printf("\e[0m");
}

void resize(int sig){
    resized = 1;
}
