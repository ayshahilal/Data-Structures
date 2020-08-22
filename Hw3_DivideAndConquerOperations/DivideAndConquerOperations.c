#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void sort(int *Key , int*Lock , int low , int high,int n)	//RECURSIVE FONKSIYON
{
    int pivot;		//Siralamaya nereden devam edilecegini belirler. Secilen elemanin sagina buyukleri soluna kucukleri yerlestirdigimiz zaman hangi indiste yer aliyorsa, o indis pivot degeri olur
	int i;			//dongulerde kullanmak icin 
	int x=high-low+1;	//Random indis uretirken high ve low indislerinin arasinda bir sayi uretmesi icin gerekli hesaplama
    int randomSayi;	//random uretilen indisi tutmak icin
	int eleman;		//random uretilen indisteki elemani tutmak icin (Key dizisinde)
    
	time_t t;					
    srand((unsigned) time(&t)); //Her seferinde farkli bir random sayi uretmesi icin
    
    if(low<high)			//Arasi siralanacak eleman var mi diye bakar ( low<high degilse arada siralanacak eleman yoktur)
    {	
		
    	randomSayi = ( rand()%x ) + low;	//low ve high arasinda rastgele bir sayi uretir 
    	printf("\nRandom indis %d secildi! \n",randomSayi);
		eleman = Key[randomSayi];			//uretilen rastgele sayiyi indis olarak kullanir ve Key dizisinde bu indisteki elemani eleman degiskenine kaydeder
    	printf("* %d * icin siralama yapiliyor.. \n",eleman);
    
		pivot = ParcalaVeSirala(Lock,low,high,eleman);//Bu elemana gore siralama yapilacagi icin bu elemandan kucuk sayilari soluna,buyuk sayilari sagina koymak uzere ParcalaVeSirala fonksiyonuna gonderir ve elemanin yerlestigi indisi pivot degiskeninde kaydeder.
		printf("\n\nLock arrayi: \n");
		
		for(i=0 ; i<n ; i++)	//Siralama yapilan dizideki degisiklikleri gormek icin ekrana diziyi yazdirir
		{
			printf("%d ", Lock[i]);
		}
		printf("\n");
		
		ParcalaVeSirala(Key,low,high,eleman);	//Ayni elemana gore siralama yapmak icin Key dizisini ParcalaVeSirala fonksiyonuna gonderir
		
		printf("\n\nKey arrayi: \n");//Siralama yapilan dizideki degisiklikleri gormek icin ekrana diziyi yazdirir
		for(i=0 ; i<n ; i++)
		{
			printf("%d ", Key[i]);
		}
		printf("\n");
		sort(Key,Lock,low,pivot-1,n);        //Dizilerin sol tarafina dogru(low'dan pivot'in yerlestigi adrese kadar olan kisim) parcalara ayirip siralama yapmak icin sort fonksiyonunu recursive olarak cagirir
		sort(Key,Lock,pivot+1,high,n);      //Dizilerin sag tarafina dogru(lpivot'in yerlestigi adres'ten high'a kadar olan kisim) parcalara ayirip siralama yapmak icin sort fonksiyonunu recursive olarak cagirir
		
    }
}
 
 
int ParcalaVeSirala(int *dizi,int low,int high,int pivot) //Bu fonksiyon low'dan high'a kadar olan kisimda pivot'a gore duzenleme yapar(pivot'tan kucukler esitler ve buyukler olarak ayirir)
{
    int i;			//Farkli gorevler icin degisken
	int j=high+1;	//dizi uzerinde high+1 den baslayip gerileyerek gezmek icin indisi tutar
	int temp;		//exchange yaparken kullanilir
    int k; 			//pivot'a esit degerleri belirleyip pivot'in yanina yerlestirirken kullanilan indis 
    i=low; 			//dizi uzerinde gezerken kullanilacagi icin low'dan baslatilir
    
	printf("\nlow: %d" , low);
	printf("\thigh: %d",high);
	
	while( dizi[i] != pivot )	//pivot'in hangi indiste oldugunu bulur
	i++;
	
	temp = dizi[low];			//pivot'i low indisindeki elemanla yer degistirir boylece pivot siralama yapilan kismin en basindaki sayi olur digerleriyle karismaz, yeri en son belirlenir
	dizi[low] = dizi[i];	
	dizi[i] = temp;
       
	i=low; 	//i'nin tekrar low'dan baslamasi gerektigi icin tekrar low'a esitlendi
	
    do
    {
        do								//Bu kisimda pivot'tan daha buyuk bir sayi bulana kadar i indisini ilerletir 
            i++;
            
        while( i<=j && dizi[i]<=pivot);   
		   
        do								//Bu kisimda pivot'tan daha kucuk bir sayi bulana kadar j indisini geriletir 
            j--;
        while( i<=j && pivot<dizi[j] );   
		   
        if(i<j)							//Buraya geldiginde bir tane pivot'tan buyuk bir tane kucuk sayi bulmussa (i<j ise bu sart saglanir) bu sayilarin yerlerini degistirir
        {	
            temp=dizi[i];				//yer degistirme islem blogu
            dizi[i]=dizi[j];
            dizi[j]=temp;
        }
        
    }while(i<j);				//Yukaridaki islemleri i<j oldugu surece yani arada eleman bulundugu surece yapmaya devam etmesi icin sart
    							//Islem bittiginde dizinin low'unda pivot vardir. Ve j'sinin oldugu yer pivot'un yerlesmesi gereken yerdir. 
    dizi[low]=dizi[j];		    //Yukaridaki gerekceye gore dizi[low]'a j indisindeki eleman konulur 
    dizi[j]=pivot;				//j indisinin oldugu yere ise pivot yerlestirilir
	
	k=j-1;						//asagida pivotla ayni olan sayilari pivot'in sol tarafina yerlestirilecegi icin k indisini pivot'in oldugu yer(j) 'in bir soluna esitlenir
    
    for(i=low ; i<j ; i++)		//low indisinden pivot'in oldugu yere kadar ayni degerde bir sayi var mi diye bakilir(pivot'in soluna bakilmaz cunku pivot'tan <= olan sayilarin hepsi sol tarafta toplanmistir ve daginik haldedir)
    {
    	if( (dizi[i] == pivot) && (i!=k))	//Eger bulunursa yer degisimini yapmak icin isleme basla (i!=k kontrolu; ayni indis uzerinde gereksiz islem yapmamasi icindir)
    	{
    		temp=dizi[k];
    		dizi[k]= dizi[i];
    		dizi[i]=temp;
    		k--;				//pivot'in soluna bir sayi yerlestiyse bir soluna gecer (k--)
		}
	}
    
    return(j);					//pivot'in yerlestigi yeri geri donus yapar
}



int main()
{
    int n,i,*Key,*Lock;
    printf("AYSE HILAL DOGAN	17011907        \n\n\n");
    printf("Bu program KEY dizisinde tutulan anahtar degerlerini ve LOCK dizisinde tutulan kilit buyukluklerini birbirlerine eslestirir.. \n");
    printf("Acilmasi gereken toplam oda sayisini giriniz:");
    scanf("%d",&n);
     
    Key = (int*)malloc(n*sizeof(int));
    Lock = (int*)malloc(n*sizeof(int));
    
	printf("\nKey Dizisi Icin Anahtar Degerlerini Girin:\n");
    for(i=0;i<n;i++)
        scanf("%d",&Key[i]);
	
	printf("\nLock Dizisi Icin Kilit Buyukluklerini Girin:\n");
	for(i=0;i<n;i++)
        scanf("%d",&Lock[i]);
		        
   
    printf("\nDIZI LOCK: \n");  
    for(i=0;i<n;i++)
        printf("%d ",Lock[i]);
    
	 printf("\nDIZI KEY: \n");	
    for(i=0;i<n;i++)
        printf("%d ", Key[i]);  
		  
    printf("\n");	
	    
	sort(Key,Lock,0,n-1,n);		//Dizileri siralama yapmak icin recursive fonksiyona baslangic (0) ve son (n) ndisleriyle beraber yollar
    
	printf("\n\nSiralama ve eslestirme yapildiktan sonra Key dizisi :\n");
    
    for(i=0 ; i<n ; i++)			//Siralanmis dizileri yazdir
       printf("%d ",Key[i]);
	
	printf("\nSiralama ve eslestirme yapildiktan sonra Lock dizisi :\n");

    for(i=0 ; i<n ; i++)
       printf("%d ",Lock[i]);   
       
    
    return 0;        
}
 

