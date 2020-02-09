/*
txt.c
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

void quit(void);
void save(void);
int file_open(void);
void handelkey(void);


void main(){
    x = 0,y = 0,file_size = 0;
    signal(SIGWINCH,resize);
    strcpy(file_name,"untitled");
    initkey();
    initmemory();
    paint(x,y,file_size);
    while(1){
        handelkey();
        paint(x,y,file_size);
    }
}

void quit(){
    system("clear");
    printf("Do you want to close?(y/n)");
    switch(getchar()){
        case 'Y':
        case 'y':system("clear");memclear();exitkey();exit(0);
    }
    system("clear");
}

void save(){
    FILE *output;
    int i,j;
    char *name = malloc(sizeof(char) * 255);
    system("clear");
    printf("Enter file name:");
    exitkey();
    scanf("%s",name);
    initkey();
    getchar();
    output = fopen(name,"w+");
    for(i=0;i<=file_size;i++){
        for(j=0;getmem(j,i)!='\0' && getmem(j,i)!=10;j++){
            fprintf(output,"%c",getmem(j,i));
            }
       fprintf(output,"%c",10);
    }
    fclose(output);
    free(name);
}

int file_open(){
    FILE *input;
    char *name,key;
    name = malloc(sizeof(char) * 255);
    system("clear");
    x = 0;
    y = 0;
    printf("Enter file name:");
    exitkey();
    scanf("%s",name);
    initkey();
    getchar();
    //strcpy(file_name,name);
    input = fopen(name,"r+");
    if(!input){
        return -1;
    }
    while((key = fgetc(input))!=EOF){
      if(key >= 32 && key <= 126){
          setmem(key,x++,y);
      } else if(key == 10){
          insert_line(y);
          y++;
          x = 0;
          file_size += 1;
      }
    }
    fclose(input);
    free(name);
    x = 0;
    y = 0;
    return 0;
}

void handelkey(){
    int key;
    key = getkey();
    switch(key){
        case -1:break;
        case EscKey:
                    quit();
                    break;
        
        case EnterKey:
                    if(getmem(x,y) == 0){
                        insert_line(y);
                    }else{
                        split_line(x,y);
                    }
                    y++;
                    x = 0;                 
                    file_size++;
                    break;
                      
        case SaveShortcut:
                    save();
                    setmsg(2);
                    break;
        case OpenShortcut:
                    if(file_open() == -1){
                        setmsg(1);
                    }else{
                        setmsg(0);
                    }
                    break;
        
        case BackspaceKey:
                    if(x>0){
                        shiftmem(x,y,x-1,y);
                        x--;
                    }else if(x==0 && y>0){
                        x = merge_line(y);
                        y--;
                    }
                    break;
        
        case DelKey:
                    if(getmem(x,y)!=0){
                        shiftmem(x+1,y,x,y);
                    }else if(getmem(0,y+1)!=-1){
                        x = merge_line(y+1);
                    }
                    break;
                          
        case LeftKey:
                    if(x>0){
                        x--;
                    }
                    else if(x==0 && y>0){
                        y--;
                        x = linelen(y);
                    }
                    break;
        
        case RightKey:
                    if(getmem(x,y)!=0)
                        x++;
                    else if(getmem(0,y+1)!=-1){
                        y++;
                        x=0;
                    }
                    break;
        case UpKey:
                    if(y>0 && getmem(x,y-1)!=0){
                        y--;
                    }else if(getmem(x,y-1)==0){
                        y--;
                        x = linelen(y);
                    }
                    break;
        case DownKey:
                    if(getmem(x,y+1)!=-1 && getmem(x,y+1)!=0){
                        y++;
                    }else if(getmem(x,y+1)==0){
                        y++;
                        x = linelen(y);
                    }
                    break;
        
        case TabKey:
                    if(getmem(x,y) == '\0'){
                        setmem(' ',x++,y);
                        setmem(' ',x++,y);
                        setmem(' ',x++,y);
                    }else{
                        shiftmem(x,y,x+3,y);
                        setmem(' ',x++,y);
                        setmem(' ',x++,y);
                        setmem(' ',x++,y);
                    }
        case CLIPBOARD:
                    getbuff();
                    break;
                    
        default:
                    if(getmem(x,y)=='\0'){
                        setmem(key,x++,y);
                    }else{
                        shiftmem(x,y,x+1,y);
                        setmem(key,x++,y);
                    }
                    
    }
}
