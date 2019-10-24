/*
text.h
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

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<termios.h>
#include<unistd.h>
#include<signal.h>
#include<string.h>

int getkey(void);
char **initmemory(void);
void setmem(char,int,int);
char getmem(int,int);
void shiftmem(int,int,int,int);
int len(char **);
int memlen(char *);
int linelen(int);
void meminc(char *,int);
void linesinc(void);
void insert_line(int);
int merge_line(int);
void split_line(int,int);
void memfree(char **);
void memclear();
void paint(int,int,int);
void initkey(void);
void exitkey(void);
void getbuff(void);
void resize(int);

int file_size;
int x,y;
char file_name[10];
int resized;

#define input_block_off   fcntl(1,F_SETFL,O_NONBLOCK)
#define input_block_on   fcntl(1,F_SETFL,2)
#define move(i,j)   printf("%c[%d;%dH",27,j,i)
#define DelKey 133
#define LeftKey 132
#define RightKey 131
#define DownKey 130
#define UpKey 129
#define EscKey 127
#define BackspaceKey 128
#define EnterKey 13
#define SaveShortcut 19
#define SpaceKey 32
#define OpenShortcut 15
#define ClipBoard 16

#define halt while(getchar()!='q'){}
