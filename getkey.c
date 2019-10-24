/*
getkey.c
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

int EscSq(void);

int resized;
struct termios original,custom;

void initkey(){
    tcgetattr(STDIN_FILENO,&original);
    custom = original;
    custom.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN | XCASE);
    custom.c_iflag &= ~(IGNBRK | BRKINT | IGNPAR | PARMRK | INPCK | ISTRIP | INLCR | IGNCR | ICRNL | IXON | IXOFF | ICANON | IUCLC | IXANY | IMAXBEL);
    custom.c_oflag &= ~(OPOST);
    tcsetattr(STDIN_FILENO,TCSAFLUSH,&custom);
}

void exitkey(){
    tcsetattr(STDIN_FILENO,TCSAFLUSH,&original);
}

int getkey(){
    char a = -1,key;
    
    while (a == -1){
        input_block_off;
        a = getchar();
        input_block_on;
        
        if (resized == 1){
           resized = 0;
           paint(x,y,file_size);
        }
    }
    
    if(a>=32 && a<=126){
        input_block_off;
        if(getchar() != -1){
            ungetc(a,stdin);
            input_block_on;
            return ClipBoard;
        }else{
            input_block_on;
            return a;
        }
    }
    else if(a == 27){
        input_block_off;
        key = EscSq();
        input_block_on;
        switch(key){
            case 1:return EscKey;
            case 65:return UpKey;
            case 66:return DownKey;
            case 67:return RightKey;
            case 68:return LeftKey;
            case 126:return DelKey;
        }
    }
    else{
        switch(a){
            case 13:return EnterKey;
            case 19:return SaveShortcut;
            case 15:return OpenShortcut;
            case 127:return BackspaceKey;
            default:return -1;
        }
    }
}

int EscSq(){
    char k;
    k = getchar();
    if(k == 91){
        k = getchar();
        if(k==51){
            k = getchar();
            if(k==126){
                return 126;
            }
        }
        if(k==65){
            return 65;
        }
        
        if(k==66){
            return 66;
        }
        
        if(k==67){
            return 67;
        }
        
        if(k==68){
            return 68;
        }
    }
    else if(k==-1){
        return 1;
    }
}

void getbuff(){
    char key;
    
    input_block_off;
    while((key = getchar()) != -1){
        if(key >= 32 && key <= 126){
            if(getmem(x,y)=='\0'){
                setmem(key,x++,y);
            }else{
                shiftmem(x,y,x+1,y);
                setmem(key,x++,y);
            }
        }
        else if(key == 13){
            if(getmem(x,y) == 0){
                insert_line(y);
            }else{
                split_line(x,y);
            }
            y++;
            x = 0;                 
            file_size++;
        }
    }
    input_block_on;
}
