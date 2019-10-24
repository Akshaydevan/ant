#include"text.h"

void quit(void);
void save(void);
void file_open(void);
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
    char nm[10];
    system("clear");
    printf("Enter file name:");
    exitkey();
    scanf("%s",nm);
    initkey();
    getchar();
    output = fopen(nm,"w+");
    for(i=0;i<=file_size;i++){
        for(j=0;getmem(j,i)!='\0' && getmem(j,i)!=10;j++){
            fprintf(output,"%c",getmem(j,i));
            }
       fprintf(output,"%c",10);
    }
    fclose(output);
}

void file_open(){
    FILE *input;
    char name[10],key;
    system("clear");
    x = 0;
    y = 0;
    printf("Enter file name:");
    exitkey();
    scanf("%s",&name);
    initkey();
    getchar();
    strcpy(file_name,name);
    input = fopen(name,"r+");
    if(!input){
        exit(0);
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
    x = 0;
    y = 0;
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
                    break;
        case OpenShortcut:
                    file_open();
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
        
        case ClipBoard:
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
