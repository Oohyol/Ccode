#include <dos.h>    /*DOS接口函数*/
#include <math.h>    /*数学函数的定义*/
#include <conio.h>   /*屏幕操作函数*/
#include <stdio.h>   /*I/O函数*/
#include <stdlib.h>   /*库函数*/
#include <stdarg.h>   /*变量长度参数表*/
#include <graphics.h>   /*图形函数*/
#include <string.h>   /*字符串函数*/
#include <ctype.h>   /*字符操作函数*/
#define UP 0x48     /*光标上移键*/
#define DOWN 0x50   /*光标下移键*/
#define LEFT 0x4b   /*光标左移键*/
#define RIGHT 0x4d   /*光标右移键*/
#define ENTER 0x0d   /*回车键*/
void *rar;        /*全局变量，保存光标图象*/
struct palettetype palette; /*使用调色板信息*/
int   GraphDriver; /* 图形设备驱动*/
int   GraphMode; /* 图形模式值*/
int   ErrorCode;   /* 错误代码*/
int   MaxColors;   /* 可用颜色的最大数值*/
int   MaxX, MaxY; /* 屏幕的最大分辨率*/
double   AspectRatio; /* 屏幕的像素比*/
void drawboder(void); /*画边框函数*/
void initialize(void);   /*初始化函数*/
void computer(void);   /*计算器计算函数*/
void changetextstyle(int font, int direction, int charsize);   /*改变文本样式函数*/
void mwindow(char *header);   /*窗口函数*/
int specialkey(void) ;    /*获取特殊键函数*/
int arrow();      /*设置箭头光标函数*/
/*主函数*/
int main()
{
    initialize();/* 设置系统进入图形模式 */
    computer(); /*运行计算器 */
    closegraph();/*系统关闭图形模式返回文本模式*/
    return(0);    /*结束程序*/
}
/* 设置系统进入图形模式 */
void initialize(void)
{
    int xasp, yasp; /* 用于读x和y方向纵横比*/
    GraphDriver = DETECT; /* 自动检测显示器*/
    initgraph( &GraphDriver, &GraphMode, "" );
/*初始化图形系统*/
    ErrorCode = graphresult();   /*读初始化结果*/
    if( ErrorCode != grOk )   /*如果初始化时出现错误*/
    {
       printf("Graphics System Error: %s\n",
       grapherrormsg( ErrorCode ) ); /*显示错误代码*/
       exit( 1 );   /*退出*/
     }
     getpalette( &palette );   /* 读面板信息*/
     MaxColors = getmaxcolor() + 1; /* 读取颜色的最大值*/
     MaxX = getmaxx();     /* 读屏幕尺寸 */
     MaxY = getmaxy();   /* 读屏幕尺寸 */
     getaspectratio( &xasp, &yasp ); /* 拷贝纵横比到变量中*/
     AspectRatio = (double)xasp/(double)yasp;/* 计算纵横比值*/
}
/*计算器函数*/
void computer(void)
{
     struct viewporttype vp;   /*定义视口类型变量*/
     int color, height, width;
     int x, y,x0,y0, i, j,v,m,n,act,flag=1;
     float num1=0,num2=0,result;   /*操作数和计算结果变量*/
     char cnum[5],str2[20]={""},c,temp[20]={""};
     char str1[]="1230.456+-789*/Qc=^%";/* 定义字符串在按钮图形上显示的符号 */
     mwindow( "Calculator" );   /* 显示主窗口 */
     color = 7;      /*设置灰颜色值*/
     getviewsettings( &vp );     /* 读取当前窗口的大小*/
     width=(vp.right+1)/10;     /* 设置按钮宽度   */
     height=(vp.bottom-10)/10 ;   /*设置按钮高度   */
     x = width /2;    /*设置x的坐标值*/
     y = height/2; /*设置y的坐标值*/
     setfillstyle(SOLID_FILL, color+3);
     bar( x+width*2, y, x+7*width, y+height );
     /*画一个二维矩形条显示运算数和结果*/
     setcolor( color+3 );   /*设置淡绿颜色边框线*/
     rectangle( x+width*2, y, x+7*width, y+height );
      /*画一个矩形边框线*/
     setcolor(RED);   /*设置颜色为红色*/
     outtextxy(x+3*width,y+height/2,"0."); /*输出字符串"0."*/
     x =2*width-width/2;    /*设置x的坐标值*/
     y =2*height+height/2;   /*设置y的坐标值*/
     for( j=0 ; j<4 ; ++j ) /*画按钮*/
     {
        for( i=0 ; i<5 ; ++i )
        {
            setfillstyle(SOLID_FILL, color);
            setcolor(RED);
            bar( x, y, x+width, y+height ); /*画一个矩形条*/
            rectangle( x, y, x+width, y+height );
            sprintf(str2,"%c",str1[j*5+i]);
              /*将字符保存到str2中*/
            outtextxy( x+(width/2), y+height/2, str2);
            x =x+width+ (width / 2) ; /*移动列坐标*/
        }
        y +=(height/2)*3; /* 移动行坐标*/
        x =2*width-width/2;   /*复位列坐标*/
     }
     x0=2*width;
     y0=3*height;
     x=x0;
     y=y0;
     gotoxy(x,y); /*移动光标到x,y位置*/
     arrow();   /*显示光标*/
     putimage(x,y,rar,XOR_PUT);
     m=0;
     n=0;
     strcpy(str2,"");   /*设置str2为空串*/
     while((v=specialkey())!=45)   /*当压下Alt+x键结束程序，否则执行下面的循环*/
     {
        while((v=specialkey())!=ENTER)   /*当压下键不是回车时*/
        {
    putimage(x,y,rar,XOR_PUT); /*显示光标图象*/
    if(v==RIGHT)    /*右移箭头时新位置计算*/
       if(x>=x0+6*width)
                  /*如果右移，移到尾，则移动到最左边字符位置*/
       {
    x=x0;
    m=0;
        }
       else
       {
    x=x+width+width/2;
    m++;
        } /*否则，右移到下一个字符位置*/
    if(v==LEFT) /*左移箭头时新位置计算*/
       if(x<=x0)
       {
    x=x0+6*width;
    m=4;
       } /*如果移到头，再左移，则移动到最右边字符位置*/
       else
       {
   x=x-width-width/2;
   m--;
       } /*否则，左移到前一个字符位置*/
           if(v==UP) /*上移箭头时新位置计算*/
       if(y<=y0)
       {
   y=y0+4*height+height/2;
   n=3;
       } /*如果移到头，再上移，则移动到最下边字符位置*/
       else
       {
                 y=y-height-height/2;
                 n--;
              } /*否则，移到上边一个字符位置*/
    if(v==DOWN) /*下移箭头时新位置计算*/
       if(y>=7*height)
       {
   y=y0;
                 n=0;
       } /*如果移到尾，再下移，则移动到最上边字符位置*/
       else
       {
   y=y+height+height/2;
   n++;
       } /*否则，移到下边一个字符位置*/
           putimage(x,y,rar,XOR_PUT);   /*在新的位置显示光标箭头*/
       }
       c=str1[n*5+m];   /*将字符保存到变量c中*/
       if(isdigit(c)||c=='.')   /*判断是否是数字或小数点*/
       {
    if(flag==-1)   /*如果标志为-1，表明为负数*/
           {
              strcpy(str2,"-"); /*将负号连接到字符串中*/
              flag=1;
           } /*将标志值恢复为1*/
       sprintf(temp,"%c",c); /*将字符保存到字符串变量temp中*/
       strcat(str2,temp); /*将temp中的字符串连接到str2中*/
       setfillstyle(SOLID_FILL,color+3);
       bar(2*width+width/2,height/2,15*width/2,3*height/2);
       outtextxy(5*width,height,str2);   /*显示字符串*/
    }
    if(c=='+')
    {
       num1=atof(str2);   /*将第一个操作数转换为浮点数*/
       strcpy(str2,""); /*将str2清空*/
       act=1;   /*做计算加法标志值*/
       setfillstyle(SOLID_FILL,color+3);
       bar(2*width+width/2,height/2,15*width/2,3*height/2);
       outtextxy(5*width,height,"0."); /*显示字符串*/
    }
    if(c=='-')
    {
       if(strcmp(str2,"")==0) /*如果str2为空，说明是负号，而不是减号*/
    flag=-1;   /*设置负数标志*/
       else
       {
    num1=atof(str2);   /*将第二个操作数转换为浮点数*/
    strcpy(str2,""); /*将str2清空*/
    act=2; /*做计算减法标志值*/
    setfillstyle(SOLID_FILL,color+3);
    bar(2*width+width/2,height/2,15*width/2,3*height/2); /*画矩形*/
    outtextxy(5*width,height,"0."); /*显示字符串*/
       }
    }
    if(c=='*')
    {
       num1=atof(str2); /*将第二个操作数转换为浮点数*/
       strcpy(str2,""); /*将str2清空*/
       act=3; /*做计算乘法标志值*/
       setfillstyle(SOLID_FILL,color+3); 
       bar(2*width+width/2,height/2,15*width/2,3*height/2);
       outtextxy(5*width,height,"0."); /*显示字符串*/
     }
    if(c=='/')
    {
       num1=atof(str2); /*将第二个操作数转换为浮点数*/
       strcpy(str2,""); /*将str2清空*/
       act=4; /*做计算除法标志值*/
       setfillstyle(SOLID_FILL,color+3);
       bar(2*width+width/2,height/2,15*width/2,3*height/2);
       outtextxy(5*width,height,"0."); /*显示字符串*/
    }
    if(c=='^')
    {
       num1=atof(str2); /*将第二个操作数转换为浮点数*/
       strcpy(str2,""); /*将str2清空*/
       act=5; /*做计算乘方标志值*/
       setfillstyle(SOLID_FILL,color+3); /*设置用淡绿色实体填充*/
       bar(2*width+width/2,height/2,15*width/2,3*height/2); /*画矩形*/
       outtextxy(5*width,height,"0."); /*显示字符串*/
    }
    if(c=='%')
    {
       num1=atof(str2); /*将第二个操作数转换为浮点数*/
       strcpy(str2,"");   /*将str2清空*/
       act=6; /*做计算模运算乘方标志值*/
       setfillstyle(SOLID_FILL,color+3); /*设置用淡绿色实体填充*/
       bar(2*width+width/2,height/2,15*width/2,3*height/2); /*画矩形*/
       outtextxy(5*width,height,"0."); /*显示字符串*/
    }
    if(c=='=')
    {
       num2=atof(str2); /*将第二个操作数转换为浮点数*/
       switch(act)   /*根据运算符号计算*/
       {
    case 1:result=num1+num2;break; /*做加法*/
    case 2:result=num1-num2;break; /*做减法*/
    case 3:result=num1*num2;break; /*做乘法*/
    case 4:result=num1/num2;break; /*做除法*/
    case 5:result=pow(num1,num2);break; /*做x的y次方*/
    case 6:result=fmod(num1,num2);break; /*做模运算*/
       }
       setfillstyle(SOLID_FILL,color+3); /*设置用淡绿色实体填充*/
       bar(2*width+width/2,height/2,15*width/2,3*height/2); /*覆盖结果区*/
       sprintf(temp,"%f",result); /*将结果保存到temp中*/
       outtextxy(5*width,height,temp); /*显示结果*/
    }
    if(c=='c')
    {
       num1=0; /*将两个操作数复位0，符号标志为1*/
       num2=0;
       flag=1;
       strcpy(str2,""); /*将str2清空*/
       setfillstyle(SOLID_FILL,color+3);   /*设置用淡绿色实体填充*/
       bar(2*width+width/2,height/2,15*width/2,3*height/2); /*覆盖结果区*/
       outtextxy(5*width,height,"0."); /*显示字符串*/
    }
    if(c=='Q')exit(0);   /*如果选择了q回车，结束计算程序*/
    }
    putimage(x,y,rar,XOR_PUT); /*在退出之前消去光标箭头*/
    return;   /*返回*/
}
/*窗口函数*/
void mwindow( char *header )
{
    int height;
    cleardevice();    /* 清除图形屏幕 */
    setcolor( MaxColors - 1 );   /* 设置当前颜色为白色*/
    setviewport( 20, 20, MaxX/2, MaxY/2, 1 ); /* 设置视口大小 */
    height = textheight( "H" );            /* 读取基本文本大小   */
    settextstyle( DEFAULT_FONT, HORIZ_DIR, 1 );/*设置文本样式*/
    settextjustify( CENTER_TEXT, TOP_TEXT );/*设置字符排列方式*/
    outtextxy( MaxX/4, 2, header );   /*输出标题*/
    setviewport( 20,20+height+4, MaxX/2+4, MaxY/2+20, 1 );   /*设置视口大小*/
    drawboder(); /*画边框*/
}
void drawboder(void)   /*画边框*/
{
    struct viewporttype vp;   /*定义视口类型变量*/
    setcolor( MaxColors - 1 );   /*设置当前颜色为白色 */
    setlinestyle( SOLID_LINE, 0, NORM_WIDTH );/*设置画线方式*/
    getviewsettings( &vp );/*将当前视口信息装入vp所指的结构中*/
    rectangle( 0, 0, vp.right-vp.left, vp.bottom-vp.top ); /*画矩形边框*/
}
/*设计鼠标图形函数*/
int arrow()
{
    int size;
    int raw[]={4,4,4,8,6,8,14,16,16,16,8,6,8,4,4,4}; /*定义多边形坐标*/
    setfillstyle(SOLID_FILL,2); /*设置填充模式*/
    fillpoly(8,raw);     /*画出一光标箭头*/
    size=imagesize(4,4,16,16);   /*测试图象大小*/
    rar=malloc(size);   /*分配内存区域*/
    getimage(4,4,16,16,rar); /*存放光标箭头图象*/
    putimage(4,4,rar,XOR_PUT); /*消去光标箭头图象*/
    return 0;
}
/*按键函数*/
int specialkey(void)
{
    int key;
    while(bioskey(1)==0);   /*等待键盘输入*/
    key=bioskey(0);    /*键盘输入*/
    key=key&0xff? key&0xff:key>>8;   /*只取特殊键的扫描值，其余为0*/
    return(key);     /*返回键值*/
}
