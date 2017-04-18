//Muhammed Þara ProLab ödevi

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>


FILE *dosya;
char kayit_ad[200],a;
typedef struct dugum{
    char eleman;
    struct dugum *sonraki,*onceki;
}dugum;

struct dugum *imlec,*ilk,*son,*dugumbasi,*gecici,*ekleyici,*ekleyici1,*ekleyici2;
struct dugum *kat[1000];
char gelen,gelen1;
int cokkat=1000,kati=1,imlecinkati=0,imlecinyatay=0;

void ekleme();//ekleme islemini yapiyoruz
void kayit();//dosya kaydetme islemi
void open();//dosyalama acma islemi
void ekranayaz();//ekrana yazdirma islemi
void dizi();//yukaridan asagiya tutulan dizi
void kopyalayapistir();//kopyala yapistir islemleri
void yonlendirme();//yonler
void silme();// silme islemini yapiyoruz
void sec();//secim yapma islemi menu
void menu();





int main(){

    dugumbasi=malloc(sizeof(dugum));
    kat[0]=dugumbasi;
menu();

    do{

        gelen=getche();
        if(gelen==-32)
            gelen1=getche();
        sec();
        ekranayaz();

    }while(gelen!=27);

    return 0;
}
void ekleme(){
    struct dugum *yeniekle=malloc(sizeof(dugum));

    if(gelen==13)
        gelen=10;

    yeniekle->eleman=gelen;


    if(ilk!=NULL){
        if(imlec->sonraki==NULL){//sondan
            imlec->sonraki=yeniekle;
            yeniekle->onceki=imlec;
            yeniekle->sonraki=NULL;
            imlec=son=yeniekle;

        }else if(imlec->onceki==dugumbasi){//bas
            imlec->onceki=yeniekle;
            yeniekle->sonraki=imlec;
            yeniekle->onceki=dugumbasi;
            ilk=yeniekle;

        }else{//aradan
            imlec->sonraki->onceki=yeniekle;
            yeniekle->sonraki=imlec->sonraki;
            imlec->sonraki=yeniekle;
            yeniekle->onceki=imlec;
            imlec=imlec->sonraki;
        }

    }else{//ilk eleman
        ilk=son=yeniekle;
        yeniekle->onceki=yeniekle->sonraki=NULL;
        imlec=yeniekle;
    }
    dugumbasi->onceki=NULL;
    dugumbasi->sonraki=ilk;
    ilk->onceki=dugumbasi;

imlecinyatay++;
}

void kayit(){
 printf("\n\n  Kaydedilecek dosya adi giriniz : ");
           scanf("%s",kayit_ad);

dosya=fopen(kayit_ad,"w");
    if (dosya == NULL) { // dosyaya erisilemiyorsa NULL olur
        printf("Dosya Kayit Edilemedi...\n");
        exit(1);}

        int i;
    for(i=1;i<=kati;i++){
        for(gecici=kat[i-1];gecici!=kat[i]&&son!=NULL&&gecici!=NULL;gecici=gecici->sonraki){
            if(gecici!=dugumbasi)
                fputc(gecici->eleman,dosya);


        }


    }
    fclose(dosya);
    }

void open(){

     printf("\n\n  Acilacak dosya adi giriniz : ");
           scanf("%s",kayit_ad);
    dosya=fopen(kayit_ad,"r+");
    char c;

    if (dosya == NULL) { // dosyaya erisilemiyorsa NULL olur
        printf("Dosya Bulunamadi...\n");
        exit(1);}
        while ((c = fgetc(dosya)) != EOF) {
                gelen=c;
        ekleme();
        if(c==10||c==13){
            kat[kati++]=imlec;
        imlecinkati++;
        imlecinyatay=0;
        }

    }

}





void ekranayaz(){
    system("cls");
    int i=1,j=10,sayfa=1;


    if(imlecinkati/10>0){
        sayfa=(imlecinkati/10);
        i=sayfa*10;
        sayfa++;
    }
    j=i+10;

    int u,yan;
    for(u=0,gecici=dugumbasi;u<kati&&gecici!=NULL;gecici=gecici->sonraki){
        kat[++u]=NULL;
    }
    for(u=0,yan=0,gecici=dugumbasi,kat[0]=dugumbasi;gecici!=NULL;gecici=gecici->sonraki,yan++){
        if(gecici!=NULL&&(gecici->eleman==10||gecici->eleman==13)){
                kat[++u]=gecici;
                yan=0;
        }

        if(gecici==imlec){
            imlecinkati=u;
            imlecinyatay=yan;
        }
    }
    if(u!=0)
        kati=u+1;


  printf("\t\t\tMenu icin CTRL+Y 'ye basiniz...\n ");
    printf(" --------------------------------------------------------------------------\n");
    printf("\t%d. Sayfadasiniz.   %d. Satirdasiniz.   %d. Harfi yaziyorsunuz.\t",sayfa,imlecinkati,imlecinyatay);
    printf("\n\n");

    for(i;i<=j;i++){
        for(gecici=kat[i-1];gecici!=kat[i]&&son!=NULL&&gecici!=NULL;gecici=gecici->sonraki){
            if(gecici!=dugumbasi)
                printf("%c",gecici->eleman);
            if(gecici==imlec)
                printf("|");
            if(gecici==ekleyici)
                printf("*");
        }

    if(i==j)
        break;
    }

    /*printf("\n\nekleyici1:%d  ekleyici2:%d  ekleyici:%d  imlec:%d\n",ekleyici1,ekleyici2,ekleyici,imlec);
            printf("kat:%d",kati);*/

}

void dizi(){
        int k;

        struct dugum *gerek;
    if(kati==cokkat-1){
        struct dugum *yenikat;

        yenikat=(dugum*)realloc(kat,sizeof(dugum)*cokkat*2);

        memcpy(*kat,yenikat,sizeof(dugum)*cokkat);

        free(kat);
        cokkat*=2;
        kat[0]=dugumbasi;
        ilk=dugumbasi->sonraki;
        kat[kati+1]=son=imlec;

    }else{
        int n;

        ekleme();
        if(kati==imlecinkati+1){//Son satir
            kat[kati++]=imlec;
            imlecinkati++;

        }else if(imlecinkati==0&&kati>1&&imlec->onceki==dugumbasi){
            for(n=++kati;n>++imlecinkati;n--)
                kat[n]=kat[n-1];
            kat[0]=imlec;
            imlec->onceki=dugumbasi;
            imlec->sonraki=kat[1];

        }else{//oncekiler Ara satirdan
            gerek=kat[imlecinkati+1];
            kat[++imlecinkati]=imlec;
            kati++;
            for(n=kati;n>imlecinkati;n--)
                kat[n]=kat[n-1];
            kat[imlecinkati+1]=gerek;
        }
        imlecinyatay=0;

    }

}

void kopyalayapistir(){//24 ctrlx 22ctrl v 3 ctrlc

    struct dugum *ekleyicigibi,gerek;
    int n;

    if(ekleyici1==NULL&&ekleyici2==NULL){
    ekleyici1=ekleyici;
    ekleyici2=imlec;
    }
    for(gecici=dugumbasi;gecici!=ekleyici1&&gecici!=son;gecici=gecici->sonraki){
        if(gecici==ekleyici2){
            ekleyicigibi=ekleyici1;
            ekleyici1=ekleyici2;
            ekleyici2=ekleyicigibi;
            break;
        }
    }
    int u,yan;
    for(u=0,gecici=dugumbasi;u<kati&&gecici!=NULL;gecici=gecici->sonraki){
        kat[++u]=NULL;
    }
    for(u=0,yan=0,gecici=dugumbasi,kat[0]=dugumbasi;gecici!=NULL;gecici=gecici->sonraki,yan++){
        if(gecici!=NULL&&(gecici->eleman==10||gecici->eleman==13)){
                kat[++u]=gecici;
                yan=0;
        }

        if(gecici==imlec){
            imlecinkati=u;
            imlecinyatay=yan;
        }
    }
    if(u!=0)
        kati=u+1;

    if(ekleyici!=NULL){
    if(gelen==24){//kes
         if(ekleyici1==dugumbasi&&ekleyici2==son){
            dugumbasi->onceki=ilk=son=NULL;
            imlec=dugumbasi;
        }else if(ekleyici1==dugumbasi){
            ekleyici1=ekleyici1->sonraki;
            dugumbasi->sonraki=ilk=ekleyici2->sonraki;
            ilk->sonraki->onceki=dugumbasi;
            imlec=dugumbasi;
        }else if(ekleyici2->sonraki!=NULL){
            ekleyici1->onceki->sonraki=ekleyici2->sonraki;
            ekleyici2->sonraki->onceki=ekleyici1->onceki;
            imlec=ekleyici2->sonraki;
        }
        else{
            /*if(ekleyici1->onceki!=NULL)
                son=imlec=ekleyici1->onceki;
            else
                son=imlec;*/
               son=imlec=ekleyici1->onceki;
            imlec->sonraki=NULL;

      }
    }
    }
    if(gelen==3){//kopyala
        for(gecici=ekleyici1,ekleyicigibi=ekleyici2;gecici!=NULL;gecici=gecici->sonraki){
            ekleyici=malloc(sizeof(dugum));
            ekleyici->eleman=gecici->eleman;
            if(ekleyici1==gecici){
                ekleyici->sonraki=ekleyici->onceki=NULL;
                ekleyici1=ekleyicigibi=ekleyici;
            }else{
                ekleyici->sonraki=NULL;
                ekleyici->onceki=ekleyicigibi;
                ekleyicigibi->sonraki=ekleyici;
                ekleyicigibi=ekleyici;
            }
            if(gecici==ekleyici2){
               ekleyici2=ekleyicigibi;
                break;
            }
        }

    }

    if(gelen==22){
        if(imlec!=son){//araya yapiþtirma
            imlec->sonraki->onceki=ekleyici2;
            ekleyici2->sonraki=imlec->sonraki;
            ekleyici1->onceki=imlec;
            imlec->sonraki=ekleyici1;
            imlec=ekleyici2;
        }else if(imlec==son){
            ekleyici2->sonraki=NULL;
            ekleyici1->onceki=imlec;
            imlec->sonraki=ekleyici1;
            son=imlec=ekleyici2;
        }else if(imlec==dugumbasi){
            ekleyici2->sonraki=dugumbasi->sonraki;
            dugumbasi->sonraki=ekleyici1;
            ekleyici1->onceki=dugumbasi;
            imlec->onceki=ekleyici2;
            imlec=ekleyici2;
            ilk=ekleyici1;
        }else if(imlec==NULL){
            dugumbasi->sonraki=ilk=son=ekleyici1;
            imlec=ekleyici2;
            ekleyici1=ekleyici2=NULL;
        }
        //gelen=3;
      //  kopyalayapistir();
      ekleyici1=NULL;
        ekleyici2=NULL;

    }


}
void  yonlendirme(){
    int k;

    if(ilk!=NULL){
        if(gelen1==72)
        {   if(imlecinkati!=0)
                imlecinkati-=1;
            imlec=kat[imlecinkati];
            imlec=imlec->sonraki;
            for(k=1;k<=imlecinyatay&&imlec->eleman!=13&&imlec->eleman!=10&&imlec->eleman!=10;k++)
                imlec=imlec->sonraki;
            imlec=imlec->onceki;
            imlecinyatay=k-1;

        } else if(gelen1==80)
        {
            if(imlecinkati!=kati-1){
                imlecinkati+=1;
            imlec=kat[imlecinkati];
                imlec=imlec->sonraki;
            for(k=1;k<=imlecinyatay&&imlec->eleman!=10&&imlec->eleman!=13&&imlec!=son;k++){
                    imlec=imlec->sonraki;
            }
            if(imlec!=son){
                imlec=imlec->onceki;
                imlecinyatay=k-1;
            }

            }
            ekleyici=NULL;
        }else if(gelen1==77)
        {
            if(imlec->sonraki!=NULL){
                imlec=imlec->sonraki;
                imlecinyatay++;
                if(imlec->eleman==13){
                    imlecinyatay=0;
                    imlecinkati++;
                }
            }
            ekleyici=NULL;
        }else if(gelen1==75)
        {
            if(imlec!=dugumbasi){
                imlec=imlec->onceki;
                imlecinyatay--;
                if(imlec->eleman==13){
                    int i;
                    for(imlecinyatay=0,i=0,gecici=imlec;gecici->eleman!=13;i++,gecici=gecici->onceki)
                        imlecinyatay++;
                    imlecinkati--;
                }
            }
            ekleyici=NULL;
        }

    if(gelen1==-115){
        if(ekleyici==NULL)
            ekleyici=imlec;
        gelen1=72;
            if(imlecinkati!=0)
                imlecinkati-=1;
            imlec=kat[imlecinkati];
            imlec=imlec->sonraki;
            for(k=1;k<=imlecinyatay&&imlec->eleman!=13;k++)
                imlec=imlec->sonraki;
            imlec=imlec->onceki;
            imlecinyatay=k-1;

    }
    else if(gelen1==-111){
        if(ekleyici==NULL)
            ekleyici=imlec;
        gelen1=80;
            if(imlecinkati!=kati-1){
                imlecinkati+=1;
            imlec=kat[imlecinkati];
                imlec=imlec->sonraki;
            for(k=1;k<=imlecinyatay&&imlec->eleman!=13&&imlec!=son;k++)
                imlec=imlec->sonraki;
            if(imlec!=son){
                imlec=imlec->onceki;
                imlecinyatay=k-1;
            }
    }
    }else if(gelen1==116){
        if(ekleyici==NULL)
            ekleyici=imlec;
        gelen1=77;
            if(imlec->sonraki!=NULL){
                imlec=imlec->sonraki;
                imlecinyatay++;
                if(imlec->eleman==13){
                    imlecinyatay=0;
                    imlecinkati++;
                }
    }
    }else if(gelen1==115){
        if(ekleyici==NULL)
            ekleyici=imlec;
        gelen1=75;
            if(imlec!=dugumbasi){
                imlec=imlec->onceki;
                imlecinyatay--;
                if(imlec->eleman==13){
                    int i;
                    for(imlecinyatay=0,i=0,gecici=imlec;gecici->eleman!=13;i++,gecici=gecici->onceki)
                        imlecinyatay++;
                    imlecinkati--;
                }
            }
    }

    }

}

void silme(){
    if(imlecinkati==1&&imlecinyatay==0)
    {

    }
else{
struct dugum *silinen=malloc(sizeof(dugum));

if(ilk==NULL){


}
else if(imlec->sonraki==NULL&&son!=dugumbasi){//son sil
    int i;

    if(son->eleman==13){

        silinen=imlec;
        son=imlec=imlec->onceki;
        son->sonraki=NULL;
        kati--;
        imlecinkati--;
        for(gecici=son,i=0;gecici->eleman!=13&&gecici!=dugumbasi;i++,gecici=gecici->onceki){}
        imlecinyatay=i;

      }else{
     imlec->onceki->sonraki=NULL;
      son=imlec->onceki;
      silinen=imlec;
      imlec=imlec->onceki;

      }
}
 else if(imlec->sonraki!=NULL){
     int i;

            if(imlec->eleman==13){


        silinen=imlec;
    imlec->onceki->sonraki=imlec->sonraki;
    imlec=imlec->onceki;
        kati--;
        imlecinkati--;

        for(gecici=imlec,i=0; gecici->eleman!=13&&gecici!=dugumbasi;i++,gecici=gecici->onceki){    }

            imlecinyatay=i;

        }

        else{
            silinen=imlec;
    imlec->onceki->sonraki=imlec->sonraki;
    imlec=imlec->onceki;

        }
    }
 free(silinen);
}}

void sec(){
    if(gelen==-32){
        yonlendirme();
    }else if(gelen==13||gelen==10)
    {
        dizi();
    }

    else if(gelen==27){
        menu();
    }
    else if (gelen==19)
    {

        kayit();

    }
    else if (gelen==15)
    {
        open();
    }
    else if (gelen==25)

    {
        main();
    }
    else if(gelen==8&&imlec!=dugumbasi){
       silme();

    }else if(gelen==3||gelen==22||gelen==24)
        kopyalayapistir();
    else
        ekleme();
}
void menu(){
    system("cls");
   printf("\tProgram Icerisinde Yapilmak Istenilen Islemler\n\n\n");

          printf("\t\tCTRL+O    ------>  Dosya Acma\n\n");
          printf("\t\tCTRL+S    ------>  Dosya Kaydetme\n\n");
          printf("\t\tESC       ------>  Programdan Cik\n\n ");
          printf("\t\tENTER     ------>  Devam Et \n\n\n");
          printf("\tDevam Etmek Icin Enter'a Basiniz...");
          gelen=getche();

       if (gelen==15)
        {
        open();
        }
        if(gelen==27)
            exit(1);

          if(gelen!=13)
          {
              menu();
          }



}
