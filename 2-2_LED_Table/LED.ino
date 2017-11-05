#define AA1 2
#define AA2 3
#define AA3 4

#define BB1 5
#define BB2 6
#define BB3 7

#define CC1 8
#define CC2 9
#define CC3 10

#define DD1 11
#define DD2 12
#define DD3 13

#define EE1 14
#define EE2 15
#define EE3 16

#define FF1 17
#define FF2 18
#define FF3 19

#define GG1 20
#define GG2 21
#define GG3 22

#define HH1 23
#define HH2 24
#define HH3 25

#define II1 26
#define II2 27
#define II3 28

#define JJ1 29
#define JJ2 30
#define JJ3 31
byte buffer[1024];
int bufferPosition;
int turn;
int player_color[2];
int player_time[2];//player have times
int col[2][100];
int row[2][100];
int k;
int p1_col[100];
int p1_row[100];

int one_player_val;
int color_check[12][12];//1~10
int col_ctr[10][32];
void setup() {
  Serial.begin(9600);
  pinMode(AA1,OUTPUT);
  pinMode(AA2,OUTPUT);
  pinMode(AA3,OUTPUT);
  pinMode(BB1,OUTPUT);
  pinMode(BB2,OUTPUT);
  pinMode(BB3,OUTPUT);
  pinMode(CC1,OUTPUT);
  pinMode(CC2,OUTPUT);
  pinMode(CC3,OUTPUT);
  pinMode(DD1,OUTPUT);
  pinMode(DD2,OUTPUT);
  pinMode(DD3,OUTPUT);
  pinMode(EE1,OUTPUT);
  pinMode(EE2,OUTPUT);
  pinMode(EE3,OUTPUT);
  pinMode(FF1,OUTPUT);
  pinMode(FF2,OUTPUT);
  pinMode(FF3,OUTPUT);
  pinMode(GG1,OUTPUT);
  pinMode(GG2,OUTPUT);
  pinMode(GG3,OUTPUT);
  pinMode(HH1,OUTPUT);
  pinMode(HH2,OUTPUT);
  pinMode(HH3,OUTPUT);
  pinMode(II1,OUTPUT);
  pinMode(II2,OUTPUT);
  pinMode(II3,OUTPUT);
  pinMode(JJ1,OUTPUT);
  pinMode(JJ2,OUTPUT);
  pinMode(JJ3,OUTPUT);
  bufferPosition=0;
}

void loop() {
  if(Serial.available()>0)
  {  
    Serial.println("loop start");
    byte data = Serial.read();
    Serial.write(data);
    buffer[bufferPosition++]=data;
    while(Serial.available())
    {
      Serial.read();
    }
    if(data=='1')//1이면 1인게임 시작. 이때 실행시키는 함수에서 while문으로 못빠져나오게 해야함
    {
      one_player();
    }
    if(data=='2')//2이면 2인게임 시작.마친가지.
    {
      two_player();
    }
  }
  
   for(int i=0;i<10;i++)
  {
    shiftcontrol(0,i,2);
    shiftcontrol(1,i,2);
    shiftcontrol(2,i,2);
    delay(50);
  }
  /*shiftcontrol(0,0,1);
  shiftcontrol(0,9,2);
  shiftcontrol(0,2,1);
  shiftcontrol(0,1,3);*/
  //shiftcontrol(1,2,3);
  //shiftcontrol(2,3,4);
  //digitalWrite(LATCH,HIGH);
}
  void shiftcontrol(int row,int col,int color)
{
  int a,b,c;
  int e,e1,e2,e3;
  switch(color)
  {
    case 0:{
      color_check[row][col]=0;
      a=1,b=1,c=1;break;}
    case 1:{
      color_check[row][col]=1;
      a=0,b=1,c=1;break;}
    case 2:{
      color_check[row][col]=2;
      a=1,b=0,c=1;break;}
    case 3:{
      color_check[row][col]=3;
      a=1,b=1,c=0;break;}
    case 4:{
      color_check[row][col]=4;
      a=1,b=0,c=0;break;}
    case 5:{
      color_check[row][col]=5;
      a=1,b=0,c=1;break;}
    case 6:{
      color_check[row][col]=6;
      a=1,b=1,c=0;break;}
  }
  e=col*3;
  e1=e;e2=e+1;e3=e+2;
  col_ctr[row][e1]=a;
  col_ctr[row][e2]=b;
  col_ctr[row][e3]=c;
  LED_change(row);
}

void random_set(int playernum)
{
  for(int i=0;i<10;i++){
    for(int t=0;t<32;t++)
    {
      col_ctr[i][t]=0;
    }
  }
  for(int i=0;i<12;i++)
  {
    for(int t=0;t<12;t++)
    {
      color_check[i][t]=-1;
    }
  }
  int a;
  //색을 랜덤으로 배정해줌.
  for(int i=0;i<7;i++)
  {
    for(int t=0;t<10;t++)
    {
      a=random(1,4);
      shiftcontrol(i,t,a);
      color_check[i+1][t+1]=a;
    }
  }
  if(playernum==1)
  {
    p1_row[0]=1;
    p1_col[0]=1;
    one_player_val=1;
    shiftcontrol(0,0,0);
    color_check[1][1]=0;
  }
  else if(playernum==2)
  {
    player_time[0] = player_time[1] =1;
    player_color[0]=0;
    player_color[1]=6;
    shiftcontrol(0,0,0);
    shiftcontrol(6,9,6);
    color_check[7][10]=6;
    color_check[1][1]=0;
    row[0][0] = col[0][0]=1;
    row[1][0] =7; 
    col[1][0]=10;
  }
}
//혼자 플레이할때
void one_player()
{
  int temp;
  Serial.println("one player start");
  int num;
  bool a=true;
  random_set(1);
  while(a)
  {
    if(Serial.available() > 0)
    {
      Serial.println(Serial.available());
      Serial.println("what?");
      byte data = Serial.read();
      Serial.println(Serial.available());
      Serial.write(data);
      data = Serial.read();
      if(data == '1')
        num=1;
      else if(data =='2')
        num=2;
      else if(data =='3')
        num=3;
      else if(data =='4')
        num=4;
      else if(data =='5')
        num=5;
      else{
        Serial.println("wrong thing : ");
        Serial.write(data);
      }
//      buffer[bufferPosition++] = data;
      temp=one_player_val;
      for(int i=0;i<temp;i++)
      {
        if(color_check[p1_row[i]][p1_col[i]-1] == num)
        {
          Serial.println("1==asdf");
          color_check[p1_row[i]][p1_col[i]-1]=0;
          shiftcontrol(p1_row[i]-1,p1_col[i]-2,0);
          one_player_val++;
          p1_row[one_player_val-1]=p1_row[i];
          p1_col[one_player_val-1]=p1_col[i]-1;
        }
        if(color_check[p1_row[i]][p1_col[i]+1] == num)
        {
          Serial.println("2==asdf");
          color_check[p1_row[i]][p1_col[i]+1]=0;
          shiftcontrol(p1_row[i]-1,p1_col[i],0);
          one_player_val++;
          p1_row[one_player_val-1]=p1_row[i];
          p1_col[one_player_val-1]=p1_col[i]+1;
        }
        if(color_check[p1_row[i]-1][p1_col[i]] == num)
        {
          Serial.println("3==asdf");
          color_check[p1_row[i]-1][p1_col[i]]=0;
          shiftcontrol(p1_row[i]-2,p1_col[i]-1,0);
          one_player_val++;
          p1_row[one_player_val-1]=p1_row[i]-1;
          p1_col[one_player_val-1]=p1_col[i];
        }
        if(color_check[p1_row[i]+1][p1_col[i]] == num)
        {
          Serial.println("4==asdf");
          color_check[p1_row[i]+1][p1_col[i]]=0;
          shiftcontrol(p1_row[i],p1_col[i]-1,0);
          one_player_val++;
          p1_row[one_player_val-1]=p1_row[i]+1;
          p1_col[one_player_val-1]=p1_col[i];
        }
      }//for문의 끝
//      Serial.println("for end");
//      Serial.println(Serial.available());
//      if(data=='\n'){
//        buffer[bufferPosition] = '\0';
//        Serial.println("bbb");
//        bufferPosition=0;
//      }
      if(one_player_val>=70)
      {
        Serial.println("end");
        a=false;
        //점수를 안드로이드로 보내줘야함. 추가필요
      }
      delay(100);
      Serial.read();
    }//if Serial의 끝
//    Serial.println("while end");
  }
}
void two_player()
{
  int temp;
  bool a;
  random_set(2);
  turn=1;
  while(a)
  {
    if(Serial.available())
    {
      if(turn==0)
        turn=1;
      else
        turn=0;
      int data=Serial.read();
      Serial.println(data);
      temp=player_time[turn];
      for(int n=0;n<temp;n++)
      {
        if (color_check[col[turn][n]][row[turn][n] - 1] == data)
      {
        color_check[col[turn][n]][row[turn][n] - 1] = player_color[turn];
        shiftcontrol(col[turn][n]-1,row[turn][n]-2,player_color[turn]);
        player_time[turn]++;
        col[turn][player_time[turn]-1] = col[turn][n];
        row[turn][player_time[turn]-1] = row[turn][n] - 1;
      }
    if (color_check[col[turn][n]][row[turn][n] + 1] == data)
      {
        color_check[col[turn][n]][row[turn][n] + 1] = player_color[turn];
        shiftcontrol(col[turn][n],row[turn][n],player_color[turn]);
        player_time[turn]++;
        col[turn][player_time[turn]-1] = col[turn][n];
        row[turn][player_time[turn]-1] = row[turn][n] + 1;
      }
    if (color_check[col[turn][n] + 1][row[turn][n]] == data)
      {
        color_check[col[turn][n] + 1][row[turn][n]] = player_color[turn];
        shiftcontrol(col[turn][n],row[turn][n]-1,player_color[turn]);
        player_time[turn]++;
        col[turn][player_time[turn]-1] = col[turn][n] + 1;
        row[turn][player_time[turn]-1] = row[turn][n];
      }
    if (color_check[col[turn][n] - 1][row[turn][n]] == data)
      {
        color_check[col[turn][n] - 1][row[turn][n]] = player_color[turn];
        shiftcontrol(col[turn][n]-2,row[turn][n]-1,player_color[turn]);
        player_time[turn]++;
        col[turn][player_time[turn]-1] = col[turn][n] - 1;
        row[turn][player_time[turn]-1] = row[turn][n];
      }
      }//for문의 끝.
      if(player_time[0]+player_time[1]>=70)
      {
        a=false;
        //점수 넘겨주는거 작성해야함.
      }
      Serial.read();
    }//if문의 끝
  }//while문의 끝.
}

//LED를 직접적으로 바꿔주는 함수.switch문 추가해야함 아직 0행 밖에 안됌.
void LED_change(int row)
{
  int t;
  int a[4]={0,};
  for(int j=0;j<4;j++)
  {
    t=1;
   for(int i=((j+1)*8-1);i>=((j)*8);i--)
    {
    a[j]=a[j]+(col_ctr[row][i]*t);
    t*=2;
    }
  }
  switch(row)
  {
    case 0:
    {
      digitalWrite(AA2,LOW);
      for(int i=3;i>=0;i--)
        shiftOut(AA1,AA3,LSBFIRST,a[i]);
      digitalWrite(AA2,HIGH);
      break;
    }
    case 1:
    {
      digitalWrite(BB2,LOW);
      for(int i=3;i>=0;i--)
        shiftOut(BB1,BB3,LSBFIRST,a[i]);
      digitalWrite(BB2,HIGH);
      break;
    }
    case 2:
    {
      digitalWrite(CC2,LOW);
      for(int i=3;i>=0;i--)
        shiftOut(CC1,CC3,LSBFIRST,a[i]);
      digitalWrite(CC2,HIGH);
      break;
    }
    case 3:
    {
      digitalWrite(DD2,LOW);
      for(int i=3;i>=0;i--)
        shiftOut(DD1,DD3,LSBFIRST,a[i]);
      digitalWrite(DD2,HIGH);
      break;
    } 
    case 4:
    {
      digitalWrite(EE2,LOW);
      for(int i=3;i>=0;i--)
        shiftOut(EE1,EE3,LSBFIRST,a[i]);
      digitalWrite(EE2,HIGH);
      break;
    }
    case 5:
    {
      digitalWrite(FF2,LOW);
      for(int i=3;i>=0;i--)
        shiftOut(FF1,FF3,LSBFIRST,a[i]);
      digitalWrite(FF2,HIGH);
      break;
    }
    case 6:
    {
      digitalWrite(GG2,LOW);
      for(int i=3;i>=0;i--)
        shiftOut(GG1,GG3,LSBFIRST,a[i]);
      digitalWrite(GG2,HIGH);
      break;
    }
    case 7:
    {
      digitalWrite(HH2,LOW);
      for(int i=3;i>=0;i--)
        shiftOut(HH1,HH3,LSBFIRST,a[i]);
      digitalWrite(HH2,HIGH);
      break;
    }
    case 8:
    {
      digitalWrite(II2,LOW);
      for(int i=3;i>=0;i--)
        shiftOut(II1,II3,LSBFIRST,a[i]);
      digitalWrite(II2,HIGH);
      break;
    }
    case 9:
    {
      digitalWrite(JJ2,LOW);
      for(int i=3;i>=0;i--)
        shiftOut(JJ1,JJ3,LSBFIRST,a[i]);
      digitalWrite(JJ2,HIGH);
      break;
    }
    
  }
}
