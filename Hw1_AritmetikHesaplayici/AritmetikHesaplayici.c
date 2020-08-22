
//17011907 Ayse Hilal Dogan
//Veri Yapilari ODEV-1

#include <stdio.h>
#include <stdlib.h>
#define MAX 100

typedef struct{
	int sayiYigini[MAX];
	int topSayi ;	
	char isaretYigini[MAX];
	int topIsaret;
}STACK;

void initStack(STACK *s){

	s->topSayi=0;
	s->topIsaret=0;
}

int isEmpty(STACK *s , int flag) // flag 0 ise isarettir. flag 1 ise sayidir.
{   
	if(flag == 0)
	{
		if(s->topIsaret == 0 )
		return 1;
		else 
		return 0;	
	}
	else 
	{
		if(s->topSayi == 0 ) 
		return 1;
		else return 0;
	}
	
}

int isFull(STACK *s , int flag){ // flag 0 ise isarettir. flag 1 ise sayidir.
	
	if(flag == 0)
	{
		if(s->topIsaret == MAX )
		return 1;
		else 
		return 0;	
	}
	else 
	{
		if(s->topSayi == MAX ) 
		return 1;
		else return 0;
	}
}
int speek(STACK *s){ // sayi yigininin en ustundekini gosterir
	int x;
	if(isEmpty(s,1))
	return 0;
	else
	{
		x=s->topSayi-1;
		return s->sayiYigini[x];
	}
}
char ipeek(STACK *s){ // isaret yigininin en ustundekini gosterir
	char ch;
	if(isEmpty(s,0))
	return 0;
	else
	{
		ch=s->topIsaret-1;
		return s->isaretYigini[ch];
	}
}

char ipop(STACK *s){ // isaret yiginindan pop yapar
	if( isEmpty(s,0) )
	return 0;
	else
	{
		--s->topIsaret;
		return s->isaretYigini[s->topIsaret];
	}
	
}

int spop(STACK *s){ // sayi yiginindan pop yapar
	if( isEmpty(s,1) )
	return 0;
	else
	{
		--s->topSayi;
		return s->sayiYigini[s->topSayi];
	}
	
}


int ipush(STACK *s, char ch){ // isaret yiginina push yapar
	
	if(isFull(s,0))
	return 0;
	else
	{
	s->isaretYigini[s->topIsaret] = ch;
	++s->topIsaret;
	return 1;
	}

}
int spush(STACK *s, int x){ //sayi yiginina push yapar

	if(isFull(s,1))
	return 0;
	else
	{
	s->sayiYigini[s->topSayi] = x; 
	++s->topSayi;
	return 1;	
	}
	
}

int oncelikBelirle(char input ) // matematiksel isaretlerin ( + - / * ) onceligine gore deger verir
{
	if( (input == '*') || (input == '/')  )
	return 2;
	else if((input == '+') || (input == '-')  )
	return 1;
	else 
	return 0;
	
}

int stringToInt(char input[])  // string i integer a cevirir
{ 
    int integer = 0,i;
    for (i = 0; input[i] != '\0'; ++i) 
        integer = integer*10 + input[i] - '0'; 
    return integer;  //string in integer a cevrilmis hali
} 



int main(){
	
	STACK s;
	initStack(&s);

	char input[MAX],islem,ch[3],tmp;
	int a,b,k,x=0,i=0,ab;
	
	printf("..ARITMETIK HESAPLAYICI..\n");
	printf("Aritmetik ifadeyi giriniz: \n");
	scanf("%s", input);
	
	while( input[i] != '\0' )
	{   
   	
	if( ( input[i] <= '9') && (input[i] >= '0') )
	
	{   while(( input[i] <= '9') && (input[i] >= '0'))
		{
		
			ch[x] = input[i];  // sayinin 9 dan buyuk bir sayi olabilme ihtimaline karsi sayiyi bir char dizisinde tutuyorum
			x++;
			i++;
		}
			ch[x]='\0';		//char dizisi oldugu icin bittiginin anlasilmasi icin sonun null karakteri ekliyorum
	
		spush( &s , stringToInt(ch) );
		x=0;
		ch[0]= '\0';
		
	}
	else if( input[i] == '(')
	{
		ipush( &s , input[i] );
		i++;
	}
		
	else if( input[i] == ')')
	{
		
		while( ipeek(&s) != '(' )
		{
			islem = ipop(&s);
			a=spop(&s);
			b=spop(&s);
			
			switch(islem)
			{
						  case '+':
						  { 
						  ab = a+b;
						  break; 
						  }
						   case '-':
						  { 
						  ab = b-a;
						  break; 
						  }
						   case '*':
						  { 
						  ab = a*b;
						  break; 
						  }
						   case '/':
						  { 
						  ab = b/a;
						  break; 
						  }	
			}
			spush(&s,ab);
			
		}
		tmp=ipop(&s);
		i++;
	}
	else if( (input[i] == '+') || (input[i] == '-') || (input[i] == '/') || (input[i] == '*') )
	{
		
		if(isEmpty(&s,0) == 1)
		{
		    ipush(&s,input[i]);
		}
		else if( ipeek(&s) == '(')
		ipush(&s,input[i]); // gelen isareti yigina yerlestir
		else if( (ipeek(&s)!=0) && (oncelikBelirle( ipeek(&s) ) < oncelikBelirle( input[i] ) ) ){
		ipush (&s, input[i] ); // gelen isareti yigina yerlestir
		}
		else
		{	
			while( (oncelikBelirle( ipeek(&s) ) > 1 ) )
			{  
				islem = ipop(&s); 
				a = spop(&s);
				b = spop(&s);
				switch(islem)
			{
						  case '+':
						  { 
						  ab = a+b;
						  break; 
						  }
						   case '-':
						  { 
						  ab = b-a;
						  break; 
						  }
						   case '*':
						  { 
						  ab = a*b;
						  break; 
						  }
						   case '/':
						  { 
						  ab = b/a;
						  break; 
						  }	
			}
			spush(&s,ab);
			}
			ipush(&s,input[i]);
		
		}
		i++;	
	}	
	printf("\nISARET YIGINI:  ");

	if(isEmpty(&s,0)){
		printf("BOS\t");
	}
	else
	{
		for(k=0; k < s.topIsaret; k++)
		{
		printf("%c   ", s.isaretYigini[k]);
		}
	}
	printf("\n  SAYI YIGINI:  ");
	if(isEmpty(&s,1))
	{
		printf("BOS\t");
	}
	else
	{
		for(k=0; k < s.topSayi; k++){
		printf("%d   ", s.sayiYigini[k]);
	}
	}
	printf("\n");
			
	}

	while( isEmpty(&s,0)==0 )
	{
		islem = ipop(&s);
		a = spop(&s);
		b = spop(&s);
		switch(islem)
		{				   case '+':
						  { 
						  ab = a+b;
						  break; 
						  }
						   case '-':
						  { 
						  ab = b-a;
						  break; 
						  }
						   case '*':
						  { 
						  ab = a*b;
						  break; 
						  }
						   case '/':
						  { 
						  ab = b/a;
						  break; 
						  }	
		}
		spush (&s,ab);
		
	}
	printf("\nISARET YIGINI:  ");
	if(isEmpty(&s,0)){
		printf("BOS\t");
	}
	else
	{
		for(k=0; k < s.topIsaret; k++)
		{
		printf("%c   ", s.isaretYigini[k]);
		}
	}
	printf("\nSAYI YIGINI:  ");
	if(isEmpty(&s,1))
	{
		printf("BOS\t");
	}
	else
	{
		for(k=0; k < s.topSayi; k++){
		printf("%d   ", s.sayiYigini[k]);
	}
	}
 printf("\n\n\nSONUC : %d\n", s.sayiYigini[0]);

return 0;
}


