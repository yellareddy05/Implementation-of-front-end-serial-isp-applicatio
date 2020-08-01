 #include<stdint.h>
#include<stdarg.h>
#include<string.h>
#include<time.h>
#include"myuart.h"
#include"myuart.c"
#include"myhextodec.c"
//#include"mydectohex.c"
char hex[4];
//int cnt;

void dtoh(int v)
{
        int val,i;
        for(i=3;i>=0;i--)
        {
                val=v%16;
                if(val<=9)

                        hex[i]=val+48;
                else
                        hex[i]=val+55;
                v=v/16;
        }
        hex[4]=0;
        //puts(arr);

}

int main()
{
int a,fd,tx,rx,ch,cnt1=0,cnt=0;
        float mytime;
        int i=0,h=0;
        char choice;
        char arr[10];
        char hex1[20];
        char (*buf)[100]=NULL,temp[100];
        FILE *fp;
        time_t starttime,endtime;
        printf("SERIAL PORT FOR ISP FLASH PROGRAMMER\n");
        printf("FOR AT89S51 AND AT89S52\n");
        printf("DEVELOPED BY\n");
        printf("P.YELLA REDDY\n");
        printf("INDIA\n");
        printf("RELEASED ON\n");
        printf("12-07-2020\n");
        usleep(1000000);
        system("clear");
label:printf("ENTER THE COM PORT NUMBER CURRENTLY USED\n");
      printf("INPUT:1 to MAX<depends on os version>\n");
      scanf("%d",&a);
      system("clear");
      if(a==1)
      {
              printf("opening serial port\n ");
              if((fd=serialOpen("/dev/ttyS0",57600))<0)
              {
                      fprintf(stderr,"unable to open serial device:%s\n"strerror(errno));
                      return 1;
              }
              puts("Serial port is opened\n");
}
      else
      {
              printf("you have entered the wrong port number\n");
              goto label;
      }
      usleep(1000000);
      __fpurge(stdin);
      system("clear");
      printf("Steps:\n");
      printf("1.Initially connect ISP to target board\n");
      printf("2.If already connected remove and Reconnected\n");
label2:printf("3.Press Enter\n");
       scanf("%c",&choice);
       if(choice!=10)
               goto label2;
       usleep(1000000);
       system("clear");
       printf("Checking UART synchronization...\n");
       for(tx='A';tx<'A'+26;tx++);
       {
               serialPutchar(fd,tx);
               printf("written:%c\n",tx);
               rx=serialGetchar(fd);
               printf("Readport:%c\n",rx);
               usleep(10000);
               system("clear");
       }
label1:printf("Enter the hex filename");
       scanf("%s",hex1);
       for(h=0;hex1[h];h++)
{
               if(hex1[h]>=65 && hex1[h]<=90)
                       hex1[h]+=32;
       }
       printf("after conversation\n");
       starttime=time(NULL);
       serialPutchar(fd,'1');
       printf("Making RESET high..\n");
       do
       {
               rx=serialGetchar(fd);
       }
       while(rx!='.');

       fp=fopen(hex1,"r");
       if(fp==NULL)
       {
               printf("NO SUCH FILE\n");
               return 1;
       }

       while((ch=fgetc(fp))!=EOF)
       {
               if(ch==':')
                       cnt++;
       }
       rewind(fp);
       while(fgets(temp,100,fp))
       {
               buf=realloc(buf,(cnt+1)*sizeof(*buf));
               strcpy(buf[cnt1],temp);
cnt1++;
       }
       fclose(fp);
       printf("programming...\n");
       //printf("Remaining line count:%d\n",cnt);
       //printf("ADDR\tOpcode forcontroller FLASH memory\n");

       int num,num1,j,l,n;
       //char op;

       while(cnt)
       {
               printf("Remaining line count:%d\n",cnt);
               printf("ADDR\tOpcode for controller FLASH memory\n");
               arr[0]=buf[i][1];
               arr[1]=buf[i][2];
               arr[2]='\0';
               num=hatoi(arr);
               int k=9;
               for(j=0;j<num;j++)
               {
                       int m=0;
                       for(l=3;l<7;l++)
                       {
                               serialPutchar(fd,buf[i][1]);
                               arr[m]=buf[i][l];
                               m++;
                               do
                               {
                                       rx=serialGetchar(fd);
                               }while(rx!='.');
}
                       arr[m]='\0';
                       num1=htoi(arr);
                       num1++;
                       for(n=0;n<2;n++)
                       {
                               serialPutchar(fd,buf[i][k]);
                               k++;
                               do
                               {
                                       rx=serialGetchar(fd);
                               }while(rx!='.');
                       }
                       serialPutchar(fd,'#');
                       do
                       {
                               rx=serialGetchar(fd);
                       }while(rx!='.');

                       serialPutchar(fd,'#');
                       do
                       {
                               rx=serialGetchar(fd);
                       } while(rx!='#');
                       printf("%c%c%c%c\t%c%c\n",buf[i][3],buf[i][4],buf[i][5],buf[i][6],buf[i][k-2],buf[i][k-1]);
                       usleep(100000);
                       dtoh(num1);
                       buf[i][3]=hex[0];
                       buf[i][4]=hex[1];
                       buf[i][5]=hex[2];
                       buf[i][6]=hex[3];
}
               i++;
               cnt--;
               system("clear");
       }
       serialPutchar(fd,'*');
       do
       {
               rx=serialGetchar(fd);
       }while(rx!='*');
       serialPutchar(fd,'0');
       printf("making RESET low....\n");
       do
       {
               rx=serialGetchar(fd);
       }while(rx!='.');
       printf("chip programmed\n");
       endtime=time(NULL);
       mytime=endtime-starttime;
       printf("Time taken is %f seconds\n",mytime);
       __fpurge(stdin);
label3:printf("Press ENTER to continue\n");
       scanf("%c",&choice);
       if(choice!=10)
               goto label3;
       __fpurge(stdin);
       printf("Press y/Y to use again\n");
       scanf("%c",&choice);
       if(choice=='y'||choice=='Y')
               goto label1;
       else
return 0;
}
