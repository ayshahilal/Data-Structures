#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#define MAX 1000

typedef struct node{	//Kisinin bilgilerini tutmak icin olan structure yapisi
	int kimlikNo,arkadaslar[MAX];
	char adSoyad[MAX];
	struct node *right, *left;	//linked list ( left ve right'i var )
	
}NODE;

NODE *root;	//bilgilerin tutuldugu list'in head'i  

NODE *createNode() 	//yeni bir dugum icin memory allocation yapip bu dugumu return eder
{
	NODE *p;
	p=(NODE*)malloc(sizeof(NODE));
	if(p==NULL)		//eger memory allocation yapamadiysa hata mesaji verir
	{
		printf("HATA..\n");
		return;
	}
	return p;
}

void print(NODE *root)	//Fonksiyon cagirildiginda kisinin kimlik nosu ve ad-soyad ini ekrana yazdirir
{
	printf("\nKimlik no:%d Ad-Soyad:%s\n",root->kimlikNo,root->adSoyad);
}

NODE *insertNewUser(int no,char *ad,int *arkadas,int a)		//yeni kullanici ekleme fonksiyonu
{
	int i=0;		//Gerekli yerlerde parametre olarak kullanilir
	NODE *newNode; 	//yeni kullanici eklerken bellekten yer acmaliyiz ve bunu bir dugumde yapmaliyiz
	NODE *parent; 	//yerlestirilecegi zaman current'i tutuyor haldedir ve current NULL olunca bu parametre sayesinde newNode'u yerine yerlestiririz
	NODE *current;	//newNode icin yer ararken agaci gezmek icin kullanilan node
	newNode= createNode(); //yeni eklenecek olan kisi icin bellekte yer aciliyor ** bu fonksiyon bellekte yer acar ve geriye yer actigi node u dondurur
	newNode->kimlikNo = no; //yeni olusan node un kimlik no bilgisi eklenir (kullanicinin verdigi no)
	
	while( ad[i]!=NULL )	//yeni node un ad-soyad bilgisi mainden gelen ad'dan (char dizisi) tek tek karakterler alinarak kaydedilir 
	{
		newNode->adSoyad[i] = ad[i];
		i++;	
	}
	i=0;			// i'yi baska iste kullanmak icin 0'lar)
	while(i<a)		// mainden gelen bilgi (a tane arkadas) dogrultusunda a kez donguye girerek yeni node'un arkadaslar[] dizisine arkadaslari kaydeder
	{
		newNode->arkadaslar[i]=arkadas[i];
		i++;	
	}
	print(newNode);	// yeni olusturulan node' un kimlik no ve ad-soyad bilgileri ekrana yazdirilir  
	printf("Kisinin arkadaslari:   ");
	for(i=0 ; i<a ;i++)			//a tane arkadas oldugu icin a kez donguye girerek kisinin arkadaslarinin kimlik no'lari ekrana yazdirilir 
	{
		printf("%d  ", newNode->arkadaslar[i]);
	}
	newNode->left=newNode->right=NULL;	//yeni olusturulan bu node'un sagi ve solu NULL yapilir
	
	if(root == NULL)	//Henuz agac bossa (head yoksa) listenin ilk elemani bu yeni olusturulan node olur
	{
		root = newNode;	
		return root;	//main'e dondurur
	}
	else	//Eger agacin head'i varsa, binary tree kuralina uygun olarak bu node icin uygun yer bulunur ve yerlestirilir
	{
		current = root;	//root'un en basindaki eleman'i current node'u tutar
		while(1)		//icerde node yerlestirilip return yapmadigi surece donguden cikamaz
		{
			parent = current;			//current NULL oldugu zaman yeni node'u yerlestirmek icin current'in NULL olmadigi zamanki halinin tutulmasi gerekiyor
			if(current->kimlikNo > no)	//binary tree kuralinda yerlestirilecek node'un kimlik no bilgisi o andaki node'un kimlik nosundan kucukse sol tarafa yerlestirilir.
			{							
				current = current->left;//yukarida aciklanan sebep dolayisiyla current node'un kimlik no'su yerlestirilmek istenen kisinin nosundan buyukse sol tarafa git 
				if(current==NULL)		//sola dogru gittiginde gittigin node bossa yeni node'u yerlestirmek icin buraya girer
				{
					parent->left = newNode;	//artik current NULL oldugu icin daha once current'i gosteren node'u tuttugumuz parent' in left'ine yeni node'u yerlestirir 
					return newNode;			//yerlestirince de bu yeni node'u main menuye doner
				}
			}
			else	//binary tree kuralinda yerlestirilecek node'un kimlik no bilgisi o andaki node'un kimlik nosundan buyukse sag tarafa yerlestirilir.
			{
				current = current->right;//yukarida aciklanan sebep dolayisiyla current node'un kimlik no'su yerlestirilmek istenen kisinin nosundan kucukse sag tarafa git
				if(current==NULL)	 	//saga dogru gittiginde gittigin node bossa yeni node'u yerlestirmek icin buraya girer
				{		
					parent->right = newNode;//artik current NULL oldugu icin daha once current'i gosteren node'u tuttugumuz parent' in right'ina yeni node'u yerlestirir 
					return newNode;			//yerlestirince de bu yeni node'u main menuye doner
				}
			}
		}
	}
		
}


NODE *contains(int no,int secim)		//Aranan kisinin agacta olup olmadigini arar ve bulursa buldugu node'u doner bulamazsa da null donmus olur, maine null donduyse mainde bu kisinin agacta olmadigi bilinir,mesaj verilir
{
	NODE *node;	//node agaci gezmek icin kullanilacak olan dugumdur
	node=root;	//agaci en basindan gezmek icin node'u root'tan baslatiriz (burda root listenin en basindadir cunku global tanimlanmistir)
	while((node!=NULL) && (node->kimlikNo != no))	//agacin sonuna ulasana kadar ya da agactaki kimlik nosu eslesen kisiyi bulana kadar dongude kal
	{
		if(secim==1)	//eger secim 1 ise her karsilastirdigi kisinin kimlik nosunu yazdirir 
		printf("Karsilastirildi -> %d\n", node->kimlikNo);
		if(node->kimlikNo > no)	//binary tree dallanmasina uygun olarak aranan no bulunan node'un no'sundan kucukse sola dogru bakmaya devam et
		node=node->left;
		else 
		node=node->right;		//aranan no bulunan node'un no'sundan buyukse saga dogru bakmaya devam et
	}
	return node;		//node bulunduysa node'u doner bulunmadiysa null oldugu icin donguden cikmistir ve null doner
}

NODE *min(NODE *node)	//Bir node'u silerken yardimci olarak kullanilir ve node'un en leftine iner ve o node'u geriye doner(min no'su olan node olmus olur buyuzden fonksiyon adi min)
{
		while(node->left!=NULL)	//node'un lefti bos olmadigi surece git
		node=node->left;		//bir sola gec
		return node;			//en son geldigin node'u don
}

void friends(int no)		//Kisinin arkadaslar[] dizisinde tutulan akradaslarindan agacta kayitli olanlarini ekrana yazdirmak icin kullanilir
{
	int i,flag=0;
	if(!contains(no,0))	//contains() fonksiyonu agactaki arkadaslari gorulmek istenen kisi agacta mevcut mu bunun bilgisini verir.Mevcut degilse NULL doner ve ekrana kisinin olmadigi bilgisi yazilir
	{
		printf("Bu kisi mevcut degil!\n");
	}
	else	//eger contains() NULL donmezse kisinin agactaki arkadaslarini bulup yazdirmak icin buraya girer
	{
		printf("Kisinin agacta mevcut olan arkadaslari:\n");
		for(i=0 ; root->arkadaslar[i] != NULL ; i++)		//arkadaslar[] dizisinin sonuna kadar giderek tek tek arkadaslar agacta var mi buna bakar
		{	
			if(contains(root->arkadaslar[i] , 0) != NULL)	//contains(no,secim) fonksiyonuna aranan arkadasin numarasi yollanir, secim=0 cunku ararken karsilastirdigi kisileri ekrana yazsin istenmiyor                                                                                                                  
			{
				print(contains( root->arkadaslar[i] , 0)); //print(no) fonskiyonuna arkadas agacta varsa no'su yollanir ve print fonksiyonu ekrana kimlik no ve ad-soyad bilgisini yazar
				flag=1;	//eger buraya hic girmezse flag en bastaki gibi 0 olarak kalir ve donguden cikinca hic arkadasi yoksa ekrana mesaj verilir
			}	
		}
		if(flag==0)		//eger agacta hicbir arkadas bulunamazsa flag= 0 ' dir ve ekrana bu mesaj verilir 
		printf("Bu kisinin agacta kayitli bir arkadasi bulunmamaktadir\n");	
	}
}

NODE *deleteUser(NODE *node,int no)	//Numarasi yollanan kisi agacta varsa bulur ve siler
{
	NODE *current;		//silinmek istenen node bulundugunda tek cocugu varsa o cocugu kaybetmemek icin kullanilan degisken
	NODE *temp;			//silinmek istenen node bulundugunda 2 cocugu varsa
	if(node== NULL)		//eger node nullsa return null yapar, bu node da silinecek bir sey yoktur
	{
		return NULL;		
	}
	if(node->kimlikNo < no)	//eger silinmek istenen node'un kimlik no'su o anda bulundugun node'un kimlik no'sundan buyukse sag tarafa dogru bakmaya devam et 
	node->right=deleteUser(node->right,no);	//recursive olarak fonksiyonu tekrar cagir ve right tarafta bakip buldugun node'u node'un right'ina esitle
	
	else if(node->kimlikNo > no)			//eger silinmek istenen node'un kimlik no'su o anda bulundugun node'un kimlik no'sundan kucukse sol tarafa dogru bakmaya devam et 
	node->left=deleteUser(node->left,no);	//recursive olarak fonksiyonu tekrar cagir ve sol tarafta bakip buldugun node'u node'un sol'una esitle
	
	else if(node->kimlikNo == no)			//eger uzerinde durulan node'un kimlik nosu silmek istenilen kisinin nosuna esitse buraya gir
	{
		if( (node->left == NULL) && (node->right == NULL) ) //silinecek olan node un hic cocugu yoksa direk siler ve NULL doner
		{	
			free(node);
			return NULL;		
		}
		else if(node->left == NULL)	//Eger silinmek istenen node'un tek cocugu varsa ve sagindaysa buraya girer ve current'i sag taraftaki cocuk yapar, silinmek istenen node'u siler
		{
			current=node->right;
			free(node);				//silinmek istenen node
			return current;			//geriye return olarak silinen node'un sagindaki cocugu doner
		}
		else if(node->right == NULL)//Eger silinmek istenen node'un tek cocugu varsa ve solundaysa buraya girer ve current'i sol taraftaki cocuk yapar, silinmek istenen node'u siler
		{
			current = node->left;
			free(node);				//silinmek istenen node
			return current;			//geriye return olarak silinen node'un solundaki cocugu doner
		}
		else
		{							//Eger silinmek istenen node'un iki cocugu varsa bu durumda dugumun sag tarafindaki en kucuk kimlik no'lu node bulunur ve bulunan node silinecek node'un yerine konur
			temp = node->right;		//Temp'i node'un sagina esitleriz. Else'e geldiginde temp'i geri dondurmemiz gerekir cunku dondurdugumuz yer node un sagini temp'e esitler. Agac yapisini bozmamamak icin gereklidir
			current=min(current);	//dugumun sag tarafinin en soluna iner ve en kucuk kimlik no'lu node'u bulur 
			current->left = node->left;	//bu en kucuk degerli node, silinecek node'un yerine konacagi icin, silinecek node'un sol tarafi bu en kucuk node'un sol tarafina konur ki duzen bozulmasin
			free(node);				//Artik node silinir
			return temp;			//geriye yukarida aciklanan sebepten dolayi silinen node'un sagindaki node dondurulur
		}
	}
	
	return node;					//fonksiyondan cikacagi zaman node'u return eder
}

int size(NODE *root , int say)	//root linked list'in en basini gosteriyor haldedir ve en bastan baslayip sonuna gidene kadar recursive olarak agacta kac kisi oldugunu sayar
{	
	if(root != NULL)	//geldigi node bos ise return yapip sayiyi doner
	{
		say++;
		say=size(root->left , say);
		say=size(root->right, say);
		
	}
	return say;
}

void printNext(NODE *node)	//bu fonksiyon agacin en basindan degil bulundugu yerden(mainden bu node bilgisi gelir) itibaren agacin sonuna kadar olan kisileri "in order" kuralina gore (kucukten buyuge) gezer ve print() ile bilgilerini yazdirir
{
	if(node!=NULL)
	{
		printNext(node->left);	//once kucukleri yazmak icin agacin en soluna kadar iner
		print(node);			//node'un kimlik no ve ad-soyad bilgisini ekrana yazan fonksiyon
		printNext(node->right);//buyukleri yazdirmak icin agacin en sagina kadar iner
	}
}

void printGreater(NODE *node,int no)	//kimlik nosu verilen kisiden buyuk olan kisileri bulur ve ekrana bilgilerini yazdirir
{										//mainden ilk buraya yollanan node bilgisi listenin en basini tutan root'tur
	if(node!=NULL)						//siradaki gelen node NULL degilse agaci gezmeye devam etmek icin buraya girer
	{
		printGreater(node->left,no);	//agacin sol tarafina bakmak icin fonksiyon recursive olarak cagirilir ve node'un bir solundaki node yollanir
		if(no < node->kimlikNo)			//buraya geldiginde elindeki node'un kimlik nosu (no) dan buyukse ekrana yazdirilir 
		print(node);					//bu fonksiyon eger no dan buyukse node'un kimlik nosunu ve ad-soyad'ini ekrana yazar
		printGreater(node->right,no);	////agacin sag tarafina bakmak icin fonksiyon recursive olarak cagirilir ve node'un bir sagindaki node yollanir
	}
}

void printInOrder(NODE *node)			//Agacin en basindan baslayarak butun node'lari recursive olarak gezer ve kimlik nolari kucukten buyuge olacak sekilde bilgilerini ekrana yazar
{										//mainden ilk buraya yollanan node bilgisi listenin en basini tutan root'tur
	if(node!=NULL)		
	{
		printNext(node->left);			//once kucukleri yazmak icin agacin en soluna kadar iner
		print(node);					//node'un kimlik no ve ad-soyad bilgisini ekrana yazan fonksiyon
		printNext(node->right);			//buyukleri yazdirmak icin agacin en sagina kadar iner
	}	
}

void main()			//ANA FONKSIYON
{
	NODE *node;			//Gerekli yerlerde kullanmak icin bir struct yapisi olusturulur
	int i,j; 			//Gerekli yerlerde(diziyi ilerletme vs) kullanilmak icin parametreler
	int no;				//File'dan string olarak okunan kimlik no bilgisini int'a cevirdiginde bunu tutmak icin bir degisken tutulur
	int numara;			//Eklemek istenen kisinin File'da bilgisi olup olmadigini karsilastirmak icin numara degiskenine kaydeder
	int *arkadas;		//File'dan okunan arkadaslar bilgisi icin dinamik bir int dizisi, kullanilacagi zaman yer memory allocation yapilir isi bitince free() edilir
	int a;				//yeni eklenen kisinin kac arkadasi oldugunu a degiskeniyle sayar
	int secim;			//switch case icin secimi kaydeder,dallanirken kullanilir
	int stop;			//File da kisi bilgisi bulundugunda donguden cikmak icin kullanilan degisken
	int exit=1;			//switch case'de kullanici cikmak isterse donguden cikmak icin exit=0 yapilir
	char line[MAX];		//her satir alindiginde bu char dizisinde tutulur
	char num[11];		//kisinin kimlik nosunu string olarak alirken kullanilan char dizisi
	char *ad;			//kisinin ad-soyad bilgisini tutan char dizisi

	FILE *fp;		
	
	while(exit){
		printf("\n\nEXIT (0)\nInsert New User (1)\nDelete User(2)\nContains(3)\nFriends(4)\nSize(5)\nPrint Next(6)\nPrint Greater(7)\nPrint In Order(8)\n");
		scanf("%d", &secim); 	//secimi secim parametresine kaydeder
		
		switch(secim){			//Kullanicinin secimine gore dallanir
				
			case 0: exit=0;	//PROGRAMDAN CIKMAK ICIN OLAN KISIM
					break;	
			case 1: 		//YENI KISI EKLEMEK ICIN OLAN KISIM
					fp=fopen( "Input.txt" , "r");	//File'i read metoduyla acar
					if(!fp)							//acamazsa acamadigi bilgisini ekrana verir ve return -1 yapar
					{						
					printf("Dosya bulunamadi..\n");
					return -1;
					}
					printf("Eklemek istediginiz kullanicinin kimlik nosunu giriniz:   ");
					scanf("%d", &numara);	//numara degiskeninde kullanicidan aldigi int degeri tutar
					stop=0;					//File da kisi bilgisi bulundugunda stop=1 olur
					
					if(contains(numara,0) !=NULL)		//Eklenmek istenen kisi agacta zaten mevcutsa NULL donmez ve ekrana mesaj verilir
					printf("Bu kisi zaten agacta mevcut..\n");
					else								//Eger eklenmek istenen kisi agacta yoksa buraya girer
					{
						while( ((fgets(line, MAX-1 ,fp)) != NULL) && (!stop)  )	//file bitene kadar ya da kisi agaca yerlesene kadar satir satir file okunur
						{
							i=0; j=0; a=0;	//Kullanilacak butun parametreler her yeni satirda 0'lanir
					
							while( (line[i]<'0' ) || (line[i] >'9'))	//File'in basinda rakam harici bir sey varsa i'yi ilerlet
							i++;
						
							while( line[i] != ',')	//satirin basindaki kimlik nosunu okur
							{
							num[j]=line[i];			//dosyadan char char olarak numarayi alir
							j++;
							i++;	
							}
							i++;					//virgul'u gecmek icin i'yi arttirir
							no = atoi(num);			//string olarak kaydedilen numarayi int'e cevirir
							printf("\n %d\t",no);	//okudugu kimlik nosunu ekrana yazar
						
							if(no==numara)			//eger dosyadan okunun kimlik no ile kisinin eklemek istedigi kisinin nosu uyusursa bulundu mesaji verir ve dosyadan diger bilgiler okunur
							{
							printf("Bulundu..\n");
						
							j=0;					//dosyadan isim okurken dizide ilerlemek icin degisken
							arkadas = (int*)malloc(MAX * sizeof(int));	//arkdas dizisi icin memory allocation
							ad=(char*)malloc(MAX*sizeof(char));			//ad (char dizisi) icin memory allocation
				
							while( line[i] != ',')	//kisinin ismini dosyadan okuyarak belirler, ad string'ine(char dizisi) kaydeder
							{
							ad[j] = line[i];
							j++;
							i++;	
							}
							ad[j]='\0';				//string oldugu icin sonuna '\0' koyar
							i++;					//virgulu gecmek icin i++ 
							while(i< strlen(line) )	//kisinin arkadaslarinin no larini satir bitesiye kadar dosyadan okur,diziye kaydeder
							{	
							j=0;
							while( line[i] != '-')	//arkadas kimlik no bilgileri no-no1-no2 formatinda oldugu icin
							{
							num[j] = line[i];
							j++;
							i++;
							}
							num[j]='\0';			//string olarak okudugu icin sonuna '\0' koyar
							i++;					// - yi gecmek icin i++
							arkadas[a]=atoi(num);	//string olarak kaydedilen no'yu int'e cevir ve arkadas dizisine kaydet 
							a++;					//arkadas sayisini 1 arttir
							}
							
							insertNewUser(no,ad,arkadas,a); //bilgileri dosyadan okunan kisiyi olusturmak icin fonksiyona gidilir
							free(arkadas);					//artik kisi agaca eklendiyse arkadas ve ad parametreleri sifirlanir 
							free(ad);
							stop=1;					//Kisi eklendiyse stop=1 olur ve buradan cikinca ekrana mesaj verilir
							}	
							for(i=1; i<11;i++)		//daha sonra kullanirken eski kaydedilen bilgiyle karismamasi icin num dizisi NULL yapilir
							{
								num[i]=NULL;
							}
						}
						if(stop==1)					//Eger kisi eklendiyse stop=1 dir
						{
						printf("\n* %d * kimlik nolu kullanici agaca eklendi\n", numara);
						}
						else						//Stop=0 oldugu durum
						{
						printf("Kullanici bilgileri dosyada bulunamadi\n");
						}
					}		
					
					fclose(fp); 					//dosyayi kapat
					break;	
			case 2:		//AGACTAN BIR KISI SILMEK ICIN OLAN KISIM
					
					printf("Silmek istediginiz kisinin kimlik nosunu giriniz :    ");
					scanf("%d", &numara);
					if(root!=NULL)		//eger agac bossa girme
					{
						if(contains(numara,0) != NULL)	//silinmek istenen kisi agacta varsa girer
						{
						root=deleteUser(root,numara);	//deleteUser fonksiyonu kisiyi siler ve root'u gunceller, guncel halini return eder
						printf("Basariyla silindi..\n");
						}
						else
						printf("Silmek istediginiz kisi agacta yok\n");
					
					}
					else
					printf("Agac bos..\n");
					
					break;
			case 3:		//KISININ AGACTA OLUP OLMADIGINI OGRENMEK ICIN OLAN KISIM
					printf("Aramak istediginiz kisinin kimlik nosunu giriniz :    ");
					scanf("%d", &numara);
					if(root!=NULL)	//agac bossa girme
					{
						node=contains(numara,1);	//contains(no,secim) fonksiyonu istenen no'da olan kisi agacta varsa bulundugu node'u return eder. secim=1 sectigimizde ararken karsilastirdigi kisilerin kimlik no'larini yazar
						if((node!=NULL) ) //Eger kisi agacta varsa kimlik no ve ad-soyad bilgilerini yazmak icin buraya girer
						{
							print(node); //kimlik no, ad-soyad bilgilerini yazar
							printf("\n");
						}
						else
						printf("Agacta boyle bir kisi yok..");	
					}
					else
					printf("Henuz agac bos..\n");
					break;
			case 4:		//ISTENEN KISININ AGACTAKI ARKADASLARININ BILGILERINI GORMEK ICIN OLAN KISIM
					if(root!=NULL)	//agac bossa girme
					{
						printf("Aramak istediginiz kisinin kimlik nosunu giriniz :    ");
						scanf("%d", &numara);
						friends(numara);	//friends fonksiyonuna numarayi yolla 
					}
					else
					printf("Henuz agac bos..\n");
										
					break;
			case 5: 		//AGACTA KAC KISI OLDUGUNU OGRENMEK ICIN OLAN KISIM
					printf("\nAgacta %d kisi var\n", size(root,0));	//size fonksiyonu agacta kac kisi oldugunu sayar ve int olarak doner, bunu ekrana yazdir
					break;		
			case 6: 		//ISTENEN KISININ ALT AGACINDAKI KISILERI KUCUKTEN BUYUGE GORMEK ICIN OLAN KISIM
					printf("Alt agacini kucukten buyuge sirali sekilde gormek istediginiz kisinin kimlik nosunu giriniz :    ");
					scanf("%d", &numara);
					node=contains(numara,0);	//Eger kisi agacta yoksa null doner
					if(node!=NULL)				//Eger null donmediyse bilgilerini yazdir
					printNext(node);			//kimlik no, ad-soyad bilgisi yazdir
					else						//null donduyse kisinin olmadigi mesajini ver
					printf("Boyle bir kisi agacta mevcut degil..\n");
					break;
			case 7: 		//AGACTA KENDISINDEN BUYUK KISILERI GORMEK ICIN OLAN KISIM
					printf("Agacta kendisinden buyuk kisileri gormek istediginiz kisinin kimlik nosunu giriniz:   ");
					scanf("%d", &numara);
					if(contains(numara,0)!=NULL)	//eger kisi agacta yoksa girme
					{
						printGreater(root,numara);	//sirayla yazdirmak icin fonksiyonu cagir
					}
					else	//contains() null donduyse boyle bir kisi agacta yoktur
					printf("Boyle bir kisi agacta mevcut degil..\n");
					break;
				
			case 8: 	//AGACTAKI BUTUN KISILERI KUCUKTEN BUYUGE(INORDER) OLARAK YAZDIR
					if(root!=NULL)		//agac bossa girme
					printInOrder(root); //kucukten buyuge yazdirmak icin fonksiyonu cagir
					else
					printf("Henuz agac bos..\n");
		
					break;
			default:
					printf("YANLIS SECIM ! \n");
		}
	}   	
}

