# include<stdio.h>//插入輸入輸出標頭檔案
# include<string.h>//字元陣列的函式定義的標頭檔案
# include<stdlib.h>//stdlib 標頭檔案即standard library標準庫標頭檔案stdlib 標頭檔案裡包含了C、C++語言的最常用的系統函式該 ,檔案包含了C語言標準庫函式的定義.
# define SPA 0//在C或C++語言源程式中允許用一個識別符號來表示一個字串，稱為“巨集”。 “define”為巨集定義命令。
# define MAN 1
# define COM 2
 /* 空位置設為0 ，玩家下的位置設為1 ，電腦下的位置設為2 */
#define ORDEX 15
int qipan[ORDEX][ORDEX]; //自己定義的預處理函式，以二維陣列形式構建棋盤 /* 15*15的棋盤 */
 
typedef struct//typedef的作用是在C中定義一個結構體型別
{
 int iFlag;
 int iX, iY;
}ScmPiece;
int g_iPieceLen;
ScmPiece g_ScmGame1, g_ScmGame2;
 
void start(); /* 程式的主要控制函式 */
void draw(); /* 畫棋盤 */
int Victory( ScmPiece * pScmPiece ); /* 判斷勝利 p q為判斷點座標 */
void AI(int *p,int *q);  /* 電腦下子 p q返回下子座標 */
int value(int p,int q);  /* 計算空點p q的價值 */
int qixing(int n,int p,int q); /* 返回空點p q在n方向上的棋型 n為1-8方向 從右順時針開始數 */
void yiwei(int n,int *i,int *j); /* 在n方向上對座標 i j 移位 n為1-8方向 從右順時針開始數 */
 
void InitGame(){
 int i;
 g_iPieceLen = ORDEX * ORDEX;
 g_ScmGame1.iX = 0;
 g_ScmGame1.iY = 0;
 g_ScmGame1.iFlag = COM;
 g_ScmGame2.iX = 7;
 g_ScmGame2.iY = 7;
 g_ScmGame2.iFlag = MAN;
 for( i=0; i < ORDEX*ORDEX; ++i )
  *( (int*)qipan + i ) = SPA;
}

void main()
{
 char k;
 do{
  InitGame();
  start();
  printf("還要再來一把嗎?輸入y或n："); getchar(); scanf("%c",&k);
  while(k!='y'&&k!='n'){ printf("輸入錯誤,請重新輸入\n"); scanf("%c",&k); }
  system("cls");
 }while(k=='y');
 printf("謝謝使用!\n");
}

void MakePiece( ScmPiece * pScmPiece, int iGameFlag ){ //人下
 if( iGameFlag )   
 {
  printf("請下子：");
  while( scanf( "%d%d", &pScmPiece->iX, &pScmPiece->iY ) )
  {
   if( ( pScmPiece->iX < 0 || pScmPiece->iX > ORDEX-1 ) || ( pScmPiece->iY < 0 || pScmPiece->iY > ORDEX-1 ) )
    printf( "座標錯誤!請重新輸入：");
   else if( qipan[pScmPiece->iX][pScmPiece->iY] )
    printf( "該位置已有子!請重新輸入：");
   else break;
  }
 }
 qipan[pScmPiece->iX][pScmPiece->iY] = pScmPiece->iFlag;
 --g_iPieceLen;
 system("cls");
 draw();
 if( iGameFlag == 0 )
  printf("電腦下在%d %d\n", pScmPiece->iX, pScmPiece->iY );
}

void start()
{
 int choice;
 //ScmPiece ScmGameTemp1, ScmGameTemp2;/* a1 b1儲存玩家上手座標 c1 d1儲存電腦上手座標 */
 printf("\t╔═══════════════════════════════╗\n");
 printf("\t║   1.人機對戰     2.人人對戰    ║\n");
 printf("\t║                ║\n");
 printf("\t╚═══════════════════════════════╝\n");
 printf("\t\t\t請輸入1或2：");
 while( scanf( "%d", &choice ), choice!=1 && choice!=2 )
  printf( "輸入錯誤，請重新輸入：" );
 system("cls");
 if( choice == 1 )
 {         /* 人機模式 */
  printf("\t\t\t歡迎使用五子棋人機對戰！\n\t\t下子請輸入座標（如13 6）中間以空格分隔。\n\n\n");
  draw();
  printf("先下請按1，後下請按2：");
  while( scanf( "%d", &choice ), choice!=1 && choice!=2 )
   printf( "輸入錯誤，請重新輸入：" );
  if( choice == 2 )
   MakePiece( &g_ScmGame2, 0 );
  choice = 1;
 }
 else
 {
  printf("歡迎使用五子棋人人對戰！下子請輸入座標(如13 6)。悔棋請輸入15 15。 \n\n\n");
  draw();
 }
 while( g_iPieceLen )
 {
  MakePiece( &g_ScmGame1, 1 );
  if( Victory( &g_ScmGame1 ) )
  {
   printf("you win!!!\n");
   return;
  } /* 玩家贏 */
  if( choice == 1 )
  {
   AI( &g_ScmGame2.iY, &g_ScmGame2.iX );
   MakePiece( &g_ScmGame2, 0 );
   if( Victory( &g_ScmGame2 ) )
   {    /* 電腦贏 */
    int iChoice;
    printf("要悔棋嗎？請輸入y或n：");
STARTFLAGE:
    setbuf( stdin, NULL );
    scanf( "%c", &iChoice );
    switch( (char)iChoice ){
    case 'y':
    case 'Y':
     g_iPieceLen += 2;
     qipan[g_ScmGame2.iX][g_ScmGame2.iY] = SPA;
     qipan[g_ScmGame1.iX][g_ScmGame1.iY] = SPA;
     system("cls"); draw();
     break;
    case 'n':
    case 'N':
     printf( "請不要灰心!!!\n" );
     return;
    default:
     printf("輸入錯誤，請重新輸入：");
     goto STARTFLAGE;
    }
   }
  }
  else
  {
   MakePiece( &g_ScmGame2, 1 );
   if( Victory( &g_ScmGame2 ) )
   {
    printf("you win!!!\n");
    return;
   }
  }
 }
 printf("和局\n");
}

void draw() /* 畫棋盤 */
{
 int i,j;
 char p[15][15][4];
 for(j=0;j<15;j++)
  for(i=0;i<15;i++){
   if(qipan[j][i]==SPA) strcpy(p[j][i]," \0");
   if(qipan[j][i]==MAN) strcpy(p[j][i],"●\0");
   if(qipan[j][i]==COM) strcpy(p[j][i],"◎\0");//strcpy把後面的複製字串過來 
  }
 printf("   0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 \n");
 printf("  ┌─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┬─┐\n");
 for(i=0,j=0;i<14;i++,j++){
 printf("  %2d│%s│%s│%s│%s│%s│%s│%s│%s│%s│%s│%s│%s│%s│%s│%s│%d\n",j,p[i][0],p[i][1],p[i][2],p[i][3],p[i][4],p[i][5],p[i][6],p[i][7],p[i][8],p[i][9],p[i][10],p[i][11],p[i][12],p[i][13],p[i][14],j);
 printf("  ├─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┼─┤\n");
 }
 printf("  14│%s│%s│%s│%s│%s│%s│%s│%s│%s│%s│%s│%s│%s│%s│%s│14\n",p[14][0],p[14][1],p[14][2],p[14][3],p[14][4],p[14][5],p[14][6],p[14][7],p[14][8],p[14][9],p[14][10],p[14][11],p[14][12],p[14][13],p[14][14]);
 printf("  └─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┴─┘\n");
 printf("   0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 \n");
}

static int DirectionValue( int * piX, int * piY, int iDirection ){
 switch( iDirection ){
 case 0:
  --*piX;
  break;
 case 4:
  ++*piX;
  break;
 case 1:
  --*piY;
  break;
 case 5:
  ++*piY;
  break;
 case 2:
  --*piX; --*piY;
  break;
 case 6:
  ++*piX; ++*piY;
  break;
 case 3:
  --*piX; ++*piY;
  break;
 case 7:
   ++*piX; --*piY;
  break;
 }
 if( (*piX >= 0 && *piX <= ORDEX-1) && (*piY >= 0 && *piY <= ORDEX-1) )
  return 1;
 else return 0;
}
static int SubVictory( ScmPiece * pScmPiece, int iDirection ){
 int iX = pScmPiece->iX;
 int iY = pScmPiece->iY;
 int iPieceCount = 1;
 while( DirectionValue( &iX, &iY, iDirection ) && qipan[iX][iY] == pScmPiece->iFlag )
  ++iPieceCount;
 iX = pScmPiece->iX;
 iY = pScmPiece->iY;
 while( DirectionValue( &iX, &iY, iDirection+4 ) && qipan[iX][iY] == pScmPiece->iFlag )
  ++iPieceCount;
 return iPieceCount;
}

int Victory( ScmPiece * pScmPiece )  /* 判斷勝利 p q為判斷點座標，勝利返回1，否則返回0 */
{
 int iDirection = 0;
 while( iDirection < 4 )
  if( SubVictory( pScmPiece, iDirection++ ) >= 5 )
   return 1;
 return 0;
}

void AI(int *p,int *q)   /* 電腦下子 *p *q返回下子座標 */
{
 int i,j,k,max=0,I,J;  /* I J為下點座標 */
 for(j=0;j<15;j++)
  for(i=0;i<15;i++)
   if(qipan[j][i]==SPA){  /* 歷遍棋盤，遇到空點則計算價值，取最大價值點下子。 */
    k=value(i,j);
    if(k>=max) { I=i; J=j; max=k; }
   }
 *p=I; *q=J;
}

int value(int p,int q) /* 計算空點p q的價值 以k返回 */
{
 int n=1,k=0,k1,k2,K1,K2,X1,Y1,Z1,X2,Y2,Z2,temp;
 int a[2][4][4]={40,400,3000,10000,6,10,600,10000,20,120,200,0,6,10,500,0,30,300,2500,5000,2,8,300,8000,26,160,0,0,4,20,300,0};
   /* 陣列a中儲存己方和對方共32種棋型的值 己方0對方1 活0衝1空活2空衝3 子數0-3（0表示1個子，3表示4個子） */
 while(n!=5){
  k1=qixing(n,p,q); n+=4;   /* k1,k2為2個反方向的棋型編號 */
  k2=qixing(n,p,q); n-=3;
  if(k1>k2) { temp=k1; k1=k2; k2=temp; } /* 使編號小的為k1,大的為k2 */
  K1=k1; K2=k2;  /* K1 K2儲存k1 k2的編號 */
  Z1=k1%10; Z2=k2%10; k1/=10; k2/=10; Y1=k1%10; Y2=k2%10; k1/=10; k2/=10; X1=k1%10; X2=k2%10;
   /* X Y Z分別表示 己方0對方1 活0衝1空活2空衝3 子數0-3（0表示1個子，3表示4個子） */
  if(K1==-1) { if(K2<0) { k+=0; continue; } else k+=a[X2][Y2][Z2]+5; continue; }; /* 空棋型and其他 */
  if(K1==-2) { if(K2<0) { k+=0; continue; } else k+=a[X2][Y2][Z2]/2; continue; };  /* 邊界衝棋型and其他 */
  if(K1==-3) { if(K2<0) { k+=0; continue; } else k+=a[X2][Y2][Z2]/3; continue; }; /* 邊界空衝棋型and其他 */
  if(((K1>-1&&K1<4)&&((K2>-1&&K2<4)||(K2>9&&K2<14)))||((K1>99&&K1<104)&&((K2>99&&K2<104)||(K2>109&&K2<114)))){
   /* 己活己活 己活己衝 對活對活 對活對衝 的棋型賦值*/
   if(Z1+Z2>=2) { k+=a[X2][Y2][3]; continue; }
   else { k+=a[X2][Y2][Z1+Z2+1]; continue; }
  }
  if(((K1>9&&K1<14)&&(K2>9&&K2<14))||((K1>109&&K1<114)&&(K2>109&&K2<114))){
   /* 己衝己衝 對衝對衝 的棋型賦值*/
   if(Z1+Z2>=2) { k+=10000; continue; }
   else { k+=0; continue; }
  }
  if(((K1>-1&&K1<4)&&((K2>99&&K2<104)||(K2>109&&K2<114)))||((K1>9&&K1<14)&&((K2>99&&K2<104)||(K2>109&&K2<114)))){
   /* 己活對活 己活對衝 己衝對活 己衝對衝 的棋型賦值*/
   if(Z1==3||Z2==3) { k+=10000; continue; }
   else { k+=a[X2][Y2][Z2]+a[X1][Y1][Z1]/4; continue; }
  }
  else { k+=a[X1][Y1][Z1]+a[X2][Y2][Z2]; continue; } /* 其他棋型的賦值 */
 }
 return k;
}

int qixing(int n,int p,int q)   /* 返回空點p q在n方向上的棋型號 n為1-8方向 從右順時針開始數 */
{
 int k,m=0; /* 棋型號註解: 己活000-003 己衝010-013 對活100-103 對衝110-113 己空活020-023 己空衝030-033 對空活120-123 對空衝130-133 空-1 邊界衝-2 邊界空衝-3*/
 yiwei(n,&p,&q);
 if(p<0||p>14||q<0||q>14) k=-2;          /* 邊界衝棋型 */
 switch(qipan[q][p]){
  case COM:{
     m++; yiwei(n,&p,&q);
     if(p<0||p>14||q<0||q>14) { k=m+9; return k; }
     while(qipan[q][p]==COM) { m++; yiwei(n,&p,&q); if(p<0||p>14||q<0||q>14) { k=m+9; return k; } }
     if(qipan[q][p]==SPA) k=m-1;       /* 己方活棋型 */
      else k=m+9;           /* 己方衝棋型 */
     }break;
  case MAN:{
     m++; yiwei(n,&p,&q);
     if(p<0||p>14||q<0||q>14) { k=m+109; return k; }
     while(qipan[q][p]==MAN) { m++; yiwei(n,&p,&q); if(p<0||p>14||q<0||q>14) { k=m+109; return k; } }
     if(qipan[q][p]==SPA) k=m+99;       /* 對方活棋型 */
     else k=m+109;          /* 對方衝棋型 */
     }break;
  case SPA:{
     yiwei(n,&p,&q);
     if(p<0||p>14||q<0||q>14) { k=-3; return k; }   /* 邊界空衝棋型 */
     switch(qipan[q][p]){
     case COM:{
        m++; yiwei(n,&p,&q);
        if(p<0||p>14||q<0||q>14) { k=m+29; return k; }
        while(qipan[q][p]==COM) { m++; yiwei(n,&p,&q); if(p<0||p>14||q<0||q>14) { k=m+29; return k; } }
        if(qipan[q][p]==SPA) k=m+19;      /* 己方空活棋型 */
        else k=m+29;          /* 己方空衝棋型 */
        }break;
     case MAN:{
        m++; yiwei(n,&p,&q);
        if(p<0||p>14||q<0||q>14) { k=m+129; return k; }
        while(qipan[q][p]==MAN) { m++; yiwei(n,&p,&q); if(p<0||p>14||q<0||q>14) { k=m+129; return k; } }  
        if(qipan[q][p]==SPA) k=m+119;      /* 對方空活棋型 */
        else k=m+129;          /* 對方空衝棋型 */
        }break;
     case SPA: k=-1; break;           /* 空棋型 */
     }
    }break;
 }
 return k;
}

void yiwei(int n,int *i,int *j)  /* 在n方向上對座標 i j 移位 n為1-8方向 從右順時針開始數 */
{
 switch(n){
 case 1: *i+=1; break;
 case 2: *i+=1; *j+=1; break;
 case 3: *j+=1; break;
 case 4: *i-=1; *j+=1; break;
 case 5: *i-=1; break;
 case 6: *i-=1; *j-=1; break;
 case 7: *j-=1; break;
 case 8: *i+=1; *j-=1; break;
 }
}
