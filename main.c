#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>

int anaMenu();
int firmaGirisi();
int musteriGirisi();
void otobusEkle(int k);
void seferEkle(int k);
void seferNoAtama(int k);
void seferNoDecimal(int k);
void seferSiralama(int seferler);
void matris (int indis,int musteriSayisi);
void rezervasyonYapma(int c, int musteriSayisi,int seferSayisi);
void seferKoltukBilgisi(int seferler, int musteriSayisi);
void musteriBilgiGoster(int musteriSayisi, int seferler);
void otobusgoster();

struct otobus
{
    int otobusNo;
    bool uzunYol;
    char otobusModeli[100];
    int otobusKapasitesi;
    int doluKoltuk;
    int personelSayisi;
}o[50];

struct musteri
{
    char ad[20];
    char soyad[20];
    int koltukNo;
    char rezervasyonNo[8];
    char seferNo[6];

}m[50];

struct sefer
{
    char str[6];
    int strCevrilmis;
    int otobusNo;
    char sehir[100];
    char varisSehri[100];
    int toplamHasilat;
    int musteriUcret;
    int mm;
    int hh;
    int mm2;
    int hh2;
}sfr[50];


int main()
{

    int x,z, secim,i=0,k=0,m=0;
    int seferSayisi=0,musteriSayisi=0;
    char harf;
    baslangic:
    x=anaMenu();
    switch(x){
     firmaGirisi:
     case 1:
         secim=firmaGirisi();
         switch(secim) {
          case 1:
           i++;
           otobusEkle(i);
           goto firmaGirisi;
           break;
          case 2:
            k++;
            seferNoAtama(k);
            seferSayisi++;
            seferNoDecimal(k);
            seferEkle(k);
            goto firmaGirisi;
            break;
          case 3:
            seferKoltukBilgisi(seferSayisi,musteriSayisi);
            goto firmaGirisi;
            break;
          case 4:
            goto baslangic;
            break;
         default:
          printf("Hatali bir giris yaptiniz\n");
          goto firmaGirisi;
          break;
         }
     break;
     musteriGirisi:
     case 2:
          z=musteriGirisi();
          switch(z) {
          case 1:
            seferSiralama(seferSayisi);
            printf("Menuye donmek icin bir harfe basiniz: ");
            scanf("%s", &harf);
            if(harf!='\0')
                goto musteriGirisi;
            break;
          case 2:
            m++;
            rezervasyonYapma(m,musteriSayisi,seferSayisi);
            musteriSayisi++;
            goto musteriGirisi;
            break;
          case 3:
            goto baslangic;
            break;
          case 4:
            musteriBilgiGoster(musteriSayisi,seferSayisi);
            goto musteriGirisi;
          default:
            printf("Hatali bir giris yaptiniz\n");
            goto musteriGirisi;
            break;
          }
          break;
     case 3:
         printf("Cikis yaptiniz\n");
         return 1;
         break;
     default:
         printf("Hatali bir giris yaptiniz\n");
         goto baslangic;
        break;

    }

}

int anaMenu(){

    int secimAnaMenu;
    printf("ANA MENU \n");
    printf("1. FIRMA GIRISI \n");
    printf("2. MUSTERI GIRISI \n");
    printf("3. CIKIS \n");
    printf("Lutfen yapicaginiz islemi seciniz: \n");
    scanf("%d" , &secimAnaMenu);

    return secimAnaMenu;
}

int firmaGirisi() {

     int secim;

         printf("1- Otobus Ekle\n");
         printf("2- Sefer Bilgisi Ekle\n");
         printf("3- Sefer/Koltuk Bilgisi Ekle\n");
         printf("4- Bir Ust Menuye Don\n");
         printf("Lutfen yapicaginiz islemi seciniz: \n");
         scanf("%d" , &secim);

     return secim;

}

int musteriGirisi(){

   int secim;

         printf("1- Seferleri Listele\n");
         printf("2- Sefer Rezervasyon Yap\n");
         printf("3- Bir Ust Menuye Don\n");
         printf("4- Rezervasyon Goster\n");
         printf("Lutfen yapicaginiz islemi seciniz: \n");
         scanf("%d" , &secim);

     return secim;

}

void otobusEkle(int i) {

    kapasiteAlma:
    printf("Kac kisilik bir otobus oldugunu giriniz: \n");
    scanf("%d" ,&o[i-1].otobusKapasitesi);

    if(o[i-1].otobusKapasitesi%4!=0) {
        printf("Girdiginiz deger 4'un kati olmalidir.\n");
        goto kapasiteAlma;
    }

    srand(time(NULL));

    if(o[i-1].otobusKapasitesi>30) {
        o[i-1].uzunYol=true;
        o[i-1].personelSayisi=3;
    }

    else if(o[i-1].otobusKapasitesi==30) {

        int personel[2]={2,3};
        o[i-1].personelSayisi= personel[ ( rand() % 2 ) ];
        if(o[i-1].personelSayisi==3) {
            o[i-1].uzunYol=true;
        }
        else{
            o[i-1].uzunYol=false;
        }
    }
    else{
        o[i-1].uzunYol=false;
        o[i-1].personelSayisi=2;
    }

    printf("Otobusun modelini giriniz: \n");
    scanf("%s" ,&o[i-1].otobusModeli);

    o[i-1].otobusNo=i;
    o[i-1].doluKoltuk=0;

}

void seferEkle(int k){

   int m,hh,mm,hh2,mm2;

   printf("Otobus Numarasini giriniz:\n");
   scanf("%d" ,&sfr[k-1].otobusNo);

   m=sfr[k-1].otobusNo-1;

    saatSorma:
    printf("Kalkis ve varis saatlerini {hh:mm} seklinde giriniz\n");
    scanf("%d:%d\n", &sfr[k-1].hh, &sfr[k-1].mm);
    scanf("%d:%d", &sfr[k-1].hh2, &sfr[k-1].mm2);

    int saatFarki=0, dakikaFarki=0;
    hh=sfr[k-1].hh;
    mm=sfr[k-1].mm;
    hh2=sfr[k-1].hh2;
    mm2=sfr[k-1].mm2;

    if(mm!=18){
        sfr[k-1].mm=18;
        mm=18;
    }


        while(hh != hh2){

            if (hh==23) {
                hh=0;
            }
            hh++;
            saatFarki++;
        }
        if(mm2<18){
        dakikaFarki=60-18;
        if(mm2>0){
            dakikaFarki+=mm2;
        }
        }
        else if(mm2==18){
            saatFarki++;
        }
        else {
            saatFarki++;
           dakikaFarki=mm2-18;
        }


    if(o[m].uzunYol!=true && saatFarki>=4 && dakikaFarki>0 ) {
       printf("Bu otobus icin uygun bir zaman araligi secmediniz:\n");
       goto saatSorma;

    }

   printf("Otobusun yola cikacagi sehri giriniz:\n");
   scanf("%s" ,&sfr[k-1].sehir);

   printf("Otobusun varis yerini giriniz:\n");
   scanf("%s" ,&sfr[k-1].varisSehri);

   printf("Toplam hasilati giriniz:\n");
   scanf("%d" ,&sfr[k-1].toplamHasilat);

   sfr[k-1].musteriUcret= sfr[k-1].toplamHasilat / o[m].otobusKapasitesi;

}


void seferNoAtama(int k) {
   char hexadecimal[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
   int i;
   noAtama:
   srand(time(NULL));

   for( i = 2 ; i < 6; i++ ) {
        sfr[k-1].str[0]='1';
        sfr[k-1].str[1]='8';
        sfr[k-1].str[i] = hexadecimal[ ( rand() % 16 ) ];

   }

   for (int j=0; j<5 ; j++) {

   if(k-1==j)
   j++;
   if(sfr[k-1].str==sfr[j].str){
    goto noAtama;
   }
   }

   printf("1. Sefer No: ");
   puts( sfr[k-1].str);

}

void seferNoDecimal(int k) {

   sfr[k-1].strCevrilmis=0;
   int j=0,temp;
   for(int i=5; i>=0;i--) {

    char a = sfr[0].str[i];
     if(a=='A')
       sfr[k-1].strCevrilmis+=pow(16,j)*10;
     else if(a=='B')
        sfr[k-1].strCevrilmis+=pow(16,j)*11;
     else if (a=='C')
        sfr[k-1].strCevrilmis+=pow(16,j)*12;
     else if (a=='D')
        sfr[k-1].strCevrilmis+=pow(16,j)*13;
     else if (a=='E')
        sfr[k-1].strCevrilmis+=pow(16,j)*14;
     else if (a=='F')
        sfr[k-1].strCevrilmis+=pow(16,j)*15;
     else {
      int z=pow(16,j);
      sfr[k-1].strCevrilmis+= z * (sfr[k-1].str[i]-'0');
     }
     j++;

   }
    printf("\nDecimal version : %d\n", sfr[k-1].strCevrilmis);
}

void seferSiralama(int seferler){

    int cevrilmis[seferler];
    int i,j,m,temp;

for(i=0; i<seferler ; i++) {

    cevrilmis[i] = sfr[i].strCevrilmis;

}

for(i=0;i<seferler-1;i++){
        for(j=0; j<seferler-i-1;j++){
            if(cevrilmis[j+1]>cevrilmis[j]){
                temp=cevrilmis[j+1];
                cevrilmis[j+1]=cevrilmis[j];
                cevrilmis[j]=temp;
            }
        }
    }

 for(i=0; i<seferler; i++){

    for(j=0; j<seferler; j++){
        if(cevrilmis[i] == sfr[j].strCevrilmis) {
            printf("Sefer No:\t");
            puts(sfr[j].str);
            printf("\t");
            printf("Otobus No: %d\t", sfr[j].otobusNo);
            printf("Kalkis: ");
            printf("%d:%d \t",sfr[j].hh,sfr[j].mm);
            printf("Inis: ");
            printf("%d:%d \t",sfr[j].hh2,sfr[j].mm2);
            m=sfr[j].otobusNo-1;
            printf("Musait Koltuk: %d \t", o[m].otobusKapasitesi-o[m].doluKoltuk);
            printf("Kisi Basi Ucret: %d\n",sfr[j].musteriUcret);

        }
    }

}
}


void seferKoltukBilgisi(int seferler, int musteriSayisi){

for(int i=0;i<seferler;i++){
    puts(sfr[i].str);
}
char sefer[8];

printf("Sefer No? (Lutfen secim yapiniz)\n");
scanf("%s", &sefer);
int indis;

for(int j=0; j<seferler;j++){
    if(sefer==sfr[j].str){
       indis=sfr[j].otobusNo-1;
    }
}


    int N;
    N=o[indis].otobusKapasitesi/4;
    int A[N][4];
    int koltukNo=1;

    for(int i=0; i<4; i++) {
        printf("\t%d", i+1);
    }

    printf("\n");

    for(int i=0; i<N;i++){
        printf("%d\t", i+1);
        for(int j=0;j<4;j++) {
             A[i][j]=koltukNo;
            for(int k=0; k<musteriSayisi; k++) {
            if(A[i][j]==m[k].koltukNo){
                printf("[ x ]\t");
                goto koltukBastirma;
            }
            }

            printf("[ %d ]\t", koltukNo);
            koltukBastirma:
            koltukNo++;
        }
      printf("\n");
    }

    int indis2;
    for(int j=0; j<seferler;j++){
    if(indis+1==sfr[j].otobusNo){
       indis2=j;
    }
  }
    printf("\nBilgiler:\n");
    printf("Toplam Hasilat: %d\n", sfr[indis2].toplamHasilat);
    printf("Bos Koltuk Sayisi: %d\n", o[indis].otobusKapasitesi-o[indis].doluKoltuk);
    printf("Kalkis Yeri:");
    puts(sfr[indis2].sehir);
    printf("Varis Yeri:");
    puts(sfr[indis2].varisSehri);
    printf("Kalkis Saati: %d:%d\n", sfr[indis2].hh, sfr[indis2].mm);
    printf("Kalkis Saati: %d:%d\n", sfr[indis2].hh2, sfr[indis2].mm2);
    printf("Otobus Numarasi: %d\n\n",o[indis].otobusNo);

}


void rezervasyonYapma(int c, int musteriSayisi, int seferSayisi){

char Ad[20], Soyad[20];
char Harf;
int koltukNo;
char seferNo[6];

rezervasyon:
printf("Sefer numarasiniz giriniz: ");
scanf("%s", &seferNo);

int l;

for(int i=0; i<seferSayisi; i++) {
    if(seferNo==sfr[i].str){
        l=sfr[i].otobusNo-1;
    }
}


    int N;
    N=o[l].otobusKapasitesi/4;
    int A[N][4];
    int koltuklar=1;

    for(int i=0; i<4; i++) {
        printf("\t%d", i+1);
    }

    printf("\n");

    for(int i=0; i<N;i++){
        printf("%d\t", i+1);
        for(int j=0;j<4;j++) {
             A[i][j]=koltuklar;
            for(int k=0; k<musteriSayisi; k++) {
            if(A[i][j]==m[k].koltukNo){
                printf("[ x ]\t");
                goto koltukBastirma;
            }
            }

            printf("[ %d ]\t", koltuklar);
            koltukBastirma:
            koltuklar++;
        }
      printf("\n");
    }


printf("Adinizi giriniz: ");
scanf("%s", &Ad);
printf("Soyadinizi giriniz: ");
scanf("%s", &Soyad);
koltukNo:
printf("Koltuk numarasini seciniz: ");
scanf("%d", &koltukNo);

for(int i=0; i<musteriSayisi; i++){

 if(koltukNo==m[i].koltukNo){
    printf("Bu koltuk dolu, baska bir deger giriniz\n");
    goto koltukNo;
 }
}

onaylama:
printf("Onayliyor musunuz: E-e / H-h ");
scanf("%c", &Harf);

if(Harf=='e' || Harf=='E'){
   char rezNo[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
   int i;
   srand(time(NULL));

   for( i = 0 ; i < 8; i++ ) {

        m[c-1].rezervasyonNo[i] = rezNo[ ( rand() % 16 ) ];

   }

   m[c-1].koltukNo=koltukNo;

   for(int i=0; i<strlen(Ad); i++){
     m[c-1].ad[i]=Ad[i];
   }
   for(int i=0; i<strlen(Soyad); i++){
     m[c-1].soyad[i]=Soyad[i];
   }

  o[l].doluKoltuk++;

}

else if(Harf=='h' || Harf=='H'){

 goto rezervasyon;
}

else{
    printf("Duzgun bir deger girmediniz.\n");
    goto onaylama;
}

}


void musteriBilgiGoster(int musteriSayisi, int seferler){

char rezNo[8];

for(int i=0; i<musteriSayisi;i++) {

    printf("Rezervasyon numaralari: ");
    puts(m[i].rezervasyonNo);
    printf("\n");
}
printf("Rezervasyon numaranizi giriniz: ");
scanf("%s", &rezNo);



for(int i=0;i<musteriSayisi;i++) {
    if(rezNo[i]==m[i].rezervasyonNo){
        printf("Koltuk Numarasi: %d", m[i].koltukNo);
        printf("Ad: ");
        puts(m[i].ad);
        printf("Soyad: ");
        puts(m[i].soyad);
        for(int j=0;j<seferler;j++) {
            if(m[i].seferNo==sfr[j].str){
              printf("Kalkis: ");
              puts(sfr[j].sehir);
              printf("Varis: ");
              puts(sfr[j].varisSehri);
              printf("Kalkis Saati: %d:%d", sfr[j].hh, sfr[j].mm);
              printf("Varis Saati: %d:%d", sfr[j].hh2, sfr[j].mm2);
              printf("Ucret: %d", sfr[j].musteriUcret);
            }
        }
    }
}

}
