#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
void pj1(void);
void pj2(void);
void pj3(void);
void pj4(void);
int getch(void);
void menu(void);
int ddd;
int main(void)
{
	while(1)
	{
		system("clear");
		menu();
		getchar();
		switch(ddd)
		{
			case 1:
				pj1();
				break;
			case 2:
				pj2();
				break;
			case 3:
				pj3();
				break;
			case 4:
				pj4();
				break;
			case 5:
				system("clear");
				goto br;
			default:
				printf("잘못 입력했습니다. 다른값을 입력하시오: ");
		}
	}
	return 0;
br:
	return 0;
}



#include<stdio.h>
void menu(void)//메뉴 함수 타자연습 번호등을 출력하고 리턴값을 전역변수인 ddd에 저장함.
{
	printf(">> 영문 타자 연습 프로그램 <<\n\n");
	printf("1. 자리 연습        2. 낱말 연습\n\n");
	printf("3. 짧은 글 연습     4. 긴 글 연습\n\n");
	printf("5. 프로그램 종료\n\n\n번호를 선택하세요: ");
	scanf("%d",&ddd);
	return ;
}


#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int getch(void);
void pj1(void)// 자리연습 함수
{
	char word[]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";//모든 알파벳을 word배열에 대입시킴
	int count_word=0,wrong_num=0,right=0,allnum=0,ran;
	char abc,ch;
	srand(time(NULL));
	for(count_word=0;count_word<=19;count_word++)//20번 랜덤한 알파벳을 출력함
	{
		system("clear");
		printf(">> 영문 타자 연습 프로그램 : 자리연습 << (esc누르면 메뉴로 넘어갑니다)\n");
		printf("진행도: %2.f%%   오타수: %d  정확도:%2.f%%\n\n\n",count_word/20.0*100,wrong_num,(float)right/allnum*100);
		ran=rand() % 52;//알파벳의 갯수가 모두 52개 이므로 0~51인 52개의 수를 ran변수에 대입함.
		printf("%c\n",word[ran]);//랜덤한 알파벳을 출력함
		ch=getch();
		if(word[ran]==ch)//getch로 받은 알파벳이 출력한 알파벳과 같으면 맞은갯수와 몇번 입력받았는지를 하나씩 증가시킴
		{
			right++;
			allnum++;
		}
		else if((word[ran]!=ch)&&(ch!=27))//입력한 알파벳과 출력한알파벳이 다르고 입력값이 esc가 아니라면 틀린횟수,총입력수를 증가시킴
		{
			wrong_num++;
			allnum++;
			while(1)//틀렸을때 알파벳이 바뀌지 않아야 하므로 이 while문으로 빠지게 함.
			{
				system("clear");
				printf(">> 영문 타자 연습 프로그램 : 자리연습 << (esc누르면 메뉴로 넘어갑니다)\n");
				printf("진행도: %2.f%%   오타수: %d  정확도:%2.f%%\n\n\n",count_word/20.0    *100,wrong_num,(float)right/allnum*100);
				printf("%c\n",word[ran]);
				ch=getch();
				if(word[ran]==ch)
				{
					right++;
					allnum++;
					break;//맞으면 이 while문을 빠져나감
				}
				else if(ch==27)
					break;//esc를 눌러도 이 while문을 빠져나감
				else if(word[ran]!=ch)
				{
					allnum++;
					wrong_num++;
				}
			}
		}
		if(ch==27)
			goto read;//esc입력하면 바로 read문으로 점프
	}
	system("clear");
	printf(">> 영문 타자 연습 프로그램 : 자리연습 << (esc누르면 메뉴로 넘어갑니다)\n");
	printf("진행도: %2.f%%   오타수: %d  정확도:%2.f%%\n\n\n",count_word/20.0*100,wrong_num,(float)right/allnum*100);
	printf("\n엔터를 입력하면 종료");
	while(1)//마지막으로 진행도 오타수 정확도를 출력해주고 이 while문으로 빠진다.
	{
		abc=getch();
		if(abc==10)//입력값이 엔터 이면 다시 메뉴로 돌아감.
			break;
	}
	return ;
read:
	return ;
}


#include <stdio.h>
#include <termio.h>
int getch(void) //getch함수
{
	int ch;
	struct termios buf;
	struct termios save;
	tcgetattr(0, &save);
	buf=save;
	buf.c_lflag&=~(ICANON|ECHO);
	buf.c_cc[VMIN]=1;
	buf.c_cc[VTIME]=0;
	tcsetattr(0, TCSAFLUSH, &buf);
	ch=getchar();
	tcsetattr(0, TCSAFLUSH, &save);
	return ch;
}



#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int getch(void);
void pj2(void)//낱말연습 함수
{
	char word[100][20]={"add","salad","as","ad","dad","Dallas","fall","Alaska","LA","all","ask","from","close","make","sure","see","old","with","lesson","point","elementary","what","new","help","listen","grade","age","guess","play","here","teacher","many","head","happy","country","very","warm","like","soccer","nature","name","read","meet","year","give","ahead","movie","much","address","email","get","family","song","thank","friend","number","class","now","pop","member","picture","fat","grandparent","long","painting","cartoon","online","dog","same","dark","different","fashion","star","wavy","welcome","think","curly","engineer","gather","communication","cute","best","diligent","short","cousin","party","small","parent","big","live","tall","black","twin","find","right","live","bank","birthday","blond","sport"};
	char abc,word_1[20]={0},word_exit[20]="###";
	int ch,wrong=0,a,all=0,right=0;
	srand(time(NULL));
	for(a=0;a<20;a++)//20번 테스트함
	{
		system("clear");
		printf(">> 영문 타자 연습 프로그램 : 낱말 연습 <<(###을 입력하면 메뉴로 넘어감)\n\n");
		printf("진행도 : %3.f%%  오타수 : %2d  정확도 : %3.f%%\n\n\n",all/20.0*100,wrong,right/(float)all*100);
		ch=rand()%100;//100개중에 한개를 출력해야하므로 0~99가 나오게 100으로 나눠줌
		printf("%s\n\n",word[ch]);
		scanf("%s",&word_1);
		if(strcmp(word_exit,word_1)==0)//### 문장과 입력문장이 같으면 read문으로가서 탈출함
			goto read;
		if(strcmp(word_1,word[ch])==0)//입력문장과 출력문장이 같으면 모든 총횟수 , 맞은횟수를 1증가시킴
		{
			right++;
			all++;
		}
		else//틀리면 총횟수와 틀린횟수를 증가시킴
		{
			all++;
			wrong++;
		}
	}

	system("clear");
	printf(">> 영문 타자 연습 프로그램 : 낱말 연습 <<(###을 입력하면 메뉴로 넘어감)\n\n");
	printf("진행도 : %3.f%%  오타수 : %2d  정확도 : %3.f%%\n\n\n",all/20.0*100,wrong,right/(float)all*100);
	printf("엔터를 입력하면 종료");
	getchar();//엔터 제거
	while(1)//단어를 20번 다 입력하면 이 while문으로 빠짐
	{
		abc=getch();
		if(abc==10)//입력문장이 엔터이면 이 while문을 빠져나감
			break;
	}
	return ;
read:
	return ;
}


#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
int getch(void);
void pj3(void)
{
	char word[30][100]={"Courage is resistance to fear, mastery of fear - not absence of fear","Poetry is the mother tongue of mankind","Misery loves company","Man is but a reed, the weaken in nature, but he is a thinking reed","Who reflects too much will accomplish little","Man should keep his friendship in constant repair","The right people in the right jobs","Time is the rider that breaks youth","A deep distress hath humanized my soul","Who reflects too much will accomplish little","Nature does not proceed by leaps","Man is a voluntary agent","Men have no right to what is not reasonable","Wealth brings with it many anxieties","Being in a ship is being in a jail, with the chance of being drowned","Life is a progress from want to want, not from enjoyment to enjoyment","Life is half spent before we know what it is","The first virtue of a painting is to be a feast for the eyes","Love truth, but pardon error","It is a wise father that knows his own child","A man apt to promise is apt to forget","We are not hypocrites in our sleep","Genius does what it must, and talent does what it can","The right people in the right jobs","Experience is the only prophecy of wise men","You never miss the water till the well runs dry","A little learning is a dangerous thing","No one can be more wise than destiny","Old men are always young enough to learn, with profit","Music has charms to soothe a savage breast"};

	char abc,word_1[100]={0};
	int p,right_1,ln,ch,wrong=0,all=0,a,b,c,now_speed=0,high_speed=0;
	clock_t start_clock=0,end_clock=0,diff_clock;
	float high_score=0,score=0;
	srand(time(NULL));
	for(a=0;a<5;a++)//5번 테스트함
	{
		for(p=0;p<100;p++)//word_1 초기화
		{
			word_1[p]=0;
		}
		all=0;
		right_1=0;
		system("clear");
		ch=rand()%30;//30개의 문장중 하나를 출력하기위해 30으로 나눠서 ch가 0~29가 나오게함
		ln=strlen(word[ch]);
		start_clock=time(NULL);//시작시간을 저장
		for(b=0;b<100;b++)//100번까지만 입력을 받아준다 100개 이상받을일은 없을거 같으므로
		{
			system("clear");
			printf("\n>> 영문 타자 연습 프로그램 : 짧은 글 연습 <<(esc누르면 메뉴로 넘어감)\n\n");
			printf("현재 타수 : %.f  최고 타수 : %.f  ",score,high_score);
			printf("진행도 : %3.f%%  정확도 : %3.f%%\n\n\n",(a)/5.0*100,right_1/(float)all*100);
			printf("%s\n",word[ch]);//입력해야할 문장을 출력해줌
			for (c=0;c<b;c++)//지금까지 입력한 영타를 출력해줌
				printf("%c",word_1[c]);
			word_1[b]=getch();//한개씩 입력받아 word_1배열에 각각 저장시킴
			end_clock = time(NULL);//입력받고 난후의 시간을 end_clock에 저장시킴
			diff_clock = end_clock - start_clock;//end클록과 start클록의 차이를 계산하여 diff클록에 저장함
			score = right_1/(float)diff_clock*60;//diff클록이 초 단위이므로 60으로 곱하여 분당 타수를 계산하여줌 여기서 맞은갯수만 계산에 넣음
			if (word_1[b]==word[ch][b])//출력값과 입력값이 같으면 맞은횟수와 전체 횟수를 1증가시킴
			{
				right_1++;
				all++;
			}
			else if(word_1[b]!=127&&word_1[b]!=10)//출렵값과 입력값이 다르고, 입력값이 엔터가 아니면 틀린횟수와 전체횟수를 1증가시킴
			{
				wrong++;
				all++;
			}
			if(word_1[b]==127 && b>=1)//입력값이 백스페이스 이고 b가 1보다 크거나 같으면 이 if문 안에 들어간다 b가 0일때는 지울수있는게 없기때문
			{
				if(word_1[b-1]==word[ch][b-1])//만약 같은것을 지웠다면 맞은 횟수를 하나 지움
				{
					right_1--;
				}
				else if(word_1[b-1]!=127&&word_1[b-1]!=10)//만약 다른것을 지웠다 그리고 엔터가 아니라면 틀린횟수만 지움
					wrong--;
				all--;//백스페이스를 누르면 무조건 all변수를 1감소시킴
				b=b-2;//그리고 백스페이스를 누르면 b를 2감소시킴
			}
			if(word_1[b]==127 && b<1)
				;
			if(word_1[b]==10)//엔터를 누르면 if문에 들어감
			{
				if(high_score<score)//만약 원래 있던 high스코어보다 지금 계산된 score가 더 크면 지금 스코어를 high스코어에 저장함
					high_score=score;
				if(a==4)
				{
					system("clear");
					printf("\n>> 영문 타자 연습 프로그램 : 짧은 글 연습 <<(esc누르면 메뉴로 넘어감)\n\n");
					printf("현재 타수 : %.f  최고 타수 : %.f  ",score,high_score);
					printf("진행도 : %3.f%%  정확도 : %3.f%%\n\n\n",(a+1)/5.0*100,right_1/(float)all*100);
					printf("%s\n",word[ch]);
					printf("%s\n",word_1);
				}
				all=ln-b+all;
				break;
			}
			if(word_1[b]==27)//esc 를 누르면 read로 감
				goto read;
		}
	}
	printf("\n esc누르면 종료");
	while(1)//5번의 실행이 끝나면 while문으로 들어옴 
	{
		abc=getch();
		if (abc==27)//esc를 누르면 이 while문을 벗어남
			break;
	}

	return ;
read:
	return ;
}




#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
int getch(void);
void pj4(void)//긴글 함수
{
	char word[4][10][200]={{"The Selfish Giant","Every afternoon, as they were coming from school, the children used","to go and play in the Giant's garden.","It was a large lovely garden, with soft green grass. Here and there","over the grass stook beautiful flowers like stars, and there were","twelve peachtrees that in the springtime broke out into delicate blos-","soms of pink and pear I, and in the autumn bore rich fruit. The birds","sat in the trees and sang so sweetly that the children used to stop","their games in order to listen to them. \"How happy we are here!\" they","cried to each other."},{"Rapunzel","There once lived a man and his wife, who had long wished for a child,","but in vain. Now there was at the back of their house a little window","which over looked a beautiful garden full of the finest vegetables and","flowers; but there was a high wall all round it, and no one ventured","into it, for it belonged to a witch of great might, and of whom all","the world was afraid. One day, when the wife was standing at the win-","dow, and looking into the garden, she saw a bed filled with the finest","rampion; and it looked so fresh and green that she began to wish for","some; and at length she longed for it greatly."},{"Narcissus","Long, long ago, there lived in Greece a young boy named Narcissus.","All day long he tended his sheep in the hills, and drove them from","place to place to find the very best pasture.","One day he came to a little stream and wanted to drink form it. The","water was very clear and reflected everything that leaned over it.","While Narcissus was waiting for the sheep to drink, he chanced to see","his own face in the water.","He had never seen his likeness before, and he was so pleased with the","pretty picture that he looked at it for a long time. "},{"Gulliver's Travels","I am Lemuel Gulliver. I was born in England. When I grew up, I had a","great wish to go round the world, and in the year 1699, I got on board","a ship bound for the South Seas. For some time things went all right.","But one day a great storm drove us far to the south and at last the","whip ran on a rock and split her bow. We let down a boat and left the","wreck. But a big wave sank the boat, and I lost sight of my poor","friends.","I swam on and on, and just when I felt I must give myself up, I found","I could touch the sand. I was now safe."}};
	int all=0,ch,a,b,c,p,t,wrong=0,right=0,d,k=0;
	clock_t start_clock=0,end_clock=0,diff_clock;
	float score=0;
	char abc,word_1[10][200]={0};

	srand(time(NULL));
	ch=rand()%4;//0~3의 4개의숫자를 랜덤으로 받음
	start_clock=time(NULL);
	for(b=0;b<5;b++)
	{
		for(c=0;c<200;c++)//총200 번의 입력할 공간을 주는데 200번 이상 입력할거 같지 않아서....
		{
			system("clear");
			printf(">> 영문 타자 연습 프로그램 : 긴 글 연습 <<(esc누르면 종료)\n\n");
			printf("현재 타수 : %.f  정확도 : %3.f%%\n\n\n",score,right/(float)all*100);
			for(a=0;a<5;a++)
				printf("%s\n",word[ch][a]);
			printf("\n\n");
			for(t=0;t<=k;t++)//내가 입력한 영타를 출력하는 for문
			{
				if(t!=k)
				{
					p=strlen(word_1[t]);
					for(d=0;d<p;d++)
						if(word_1[t][d]!=10)
							printf("%c",word_1[t][d]);
					printf("\n");
				}
				else
				{
					for(d=0;d<c;d++)
						printf("%c",word_1[t][d]);
				}
			}
			word_1[b][c]=getch();
			end_clock = time(NULL);
			diff_clock=end_clock - start_clock;
			score = right/(float)diff_clock*60;//분당 타수 pj3과 동일
			if(word_1[b][c]==word[ch][b][c])
			{
				right++;
				all++;
			}
			else if(word_1[b][c]!=127&&word_1[b][c]!=10)
			{
				wrong++;
				all++;
			}
			if(word_1[b][c]==127 && c>=1)
			{
				if(word_1[b][c-1]==word[ch][b][c-1])
				{
					right--;
				}
				else if(word_1[b][c-1]!=127&&word_1[b][c-1]!=10)
					wrong--;
				all--;
				c=c-2;
			}
			if(word_1[b][c]==127 && b<1)
				;
			if(word_1[b][c]==10)
			{
				if(strlen(word[ch][b]) > strlen(word_1[b]))//입력한 길이보다 입력해야할 길이가 길면 모든횟수를 증가시킴
					all=all+strlen(word[ch][b])-c;
				k++;
				break;
			}
			if(word_1[b][c]==27)
				goto read;
		}
	}
	for(b=5;b<10;b++)//이건 다음 다섯 줄이다 위의 다섯줄이랑 코드는 같음.
	{
		for(c=0;c<200;c++)
		{
			system("clear");
			printf(">> 영문 타자 연습 프로그램 : 긴 글 연습 <<(esc 누르면 종료)\n\n")    ;

			printf("현재 타수 : %.f  정확도 : %3.f%%\n\n\n",score,right/(float)all*100);
			for(a=5;a<10;a++)
				printf("%s\n",word[ch][a]);
			printf("\n\n");
			for(t=5;t<=k;t++)
			{
				if(t!=k)
				{
					p=strlen(word_1[t]);
					for(d=0;d<p;d++)
						if(word_1[t][d]!=10)
							printf("%c",word_1[t][d]);
					printf("\n");
				}
				else
				{
					for(d=0;d<c;d++)
						printf("%c",word_1[t][d]);
				}
			}
			word_1[b][c]=getch();
			end_clock = time(NULL);
			diff_clock=end_clock - start_clock;
			score = right/(float)diff_clock*60;
			if(word_1[b][c]==word[ch][b][c])
			{
				right++;
				all++;
			}
			else if(word_1[b][c]!=127&&word_1[b][c]!=10)
			{
				wrong++;
				all++;
			}
			if(word_1[b][c]==127 && c>=1)
			{
				if(word_1[b][c-1]==word[ch][b][c-1])
				{
					right--;
				}
				else if(word_1[b][c-1]!=127&&word_1[b][c-1]!=10)
					wrong--;
				all--;
				c=c-2;
			}
			if(word_1[b][c]==127 && b<1)
				c--;
			if(word_1[b][c]==10)
			{
				if(strlen(word[ch][b]) > strlen(word_1[b]))
					all=all+strlen(word[ch][b])-c;
				k++;
				break;
			}
			if(word_1[b][c]==27)
				goto read;
		}
	}
	printf("\n esc 누르면 종료");
	while(1)//다 끝나면 이 while문으로 내려옴
	{
		abc=getch();
		if(abc==27)//입력값이 esc라면 while문 종료
			break;
	}
	return ;
read:
	return ;
}
