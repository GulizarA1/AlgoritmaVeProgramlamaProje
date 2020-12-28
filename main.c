//Kütüphaneler
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
//Hazýr deðiþkenler
    const char matrix_bigram_strings[10][2] ={"th", "he", "in", "er", "an", "en", "ch", "de", "ei", "te"};
    const char matrix_trigram_strings[10][3]={"the", "and", "ing", "ent", "ion", "der", "sch", "ich", "nde", "die"};
    const char languages[2][7]={"english", "german"};
    char temizlenecek_metin[255];
    char temizlenmis_metin[255];
//Satýrlarda bigramlarin ve trigramlarin, sütunlarda ise dillerin yer aldigi frekans matrisi.
    const float frequency[2][20]={ 2.71, 2.33, 2.03, 1.78, 1.61, 1.13, 0.10, 0.10, 0.10, 0.10, 1.81, 0.73, 0.72, 0.42, 0.42, 0.10, 0.10, 0.10, 0.10, 0.10,
                                    0.10, 0.89, 1.71, 3.90, 1.07, 3.61, 2.36, 2.31, 1.98, 1.98, 0.10, 0.10, 0.10, 0.10, 0.10, 1.04, 0.76, 0.75, 0.72, 0.62
                                    };
    float distances [2][20];
    float calculated_frequencies[2][10];
//Fonsiyonlar

    //Metin temizleme fonksiyonu
    void filter_str(char str1[], char str2[]){ //str1 input ile alýnan metin, str2 temizlenmiþ halinin tutulacaðý metin
         for(int i = 0; i<strlen(str1); i++){//input metninin sonuna kadar bütün karakterleri küçük harfe çeviririz
            str1[i] = tolower(str1[i]);
        }
        for(int i = 0; i<strlen(str1);i++){//input metninin sonuna kadar; karakter alfabetik veya boþluk karakteri ise ikinci metine aktarýrýz
            if(isalpha(str1[i]) || str1[i])
                strncat(str2, str1+i, 1);
        }
    }//Metin temizleme fonksiyonu bitti

    //Frekans hesaplama (Bigram)
    void calculate_frequencies_bi(char str[]){
        char gecici[50];    //Karþýlaþtýrmak için matrix string dizisinden geçici olarak kelime almamýzý saðlayan deðiþken
        int sayac;  //Her kelimenin kaç defa stringde bulunduðunu tutar
        int uzunluk = strlen(str);  //Stringimizin uzunluðu
        for(int i=0;i<10;i++){  //matrix dizimizin her öðesini geçici deðiþkene aktarýp, metin içinde kaç defa çýktýðýný bulup frekansý hesaplayan döngü
            sayac = 0;  //Döngü her baþa geldiðinde sýfýrlanýr
            strcpy(gecici, matrix_bigram_strings[i]);   //Döngü her baþa geldiðinde matrixten yeni kelime alýnýr
            for(int j=0;j<strlen(str);j++)  //Stringin baþýndan sonuna kelime kaç kere varsa sayýlýr
                while((strstr(str+j, gecici)) != NULL){
                    sayac++;
                }
        calculated_frequencies[1][i]=sayac/uzunluk; //Kelime kaç defa var bulunduktan sonra toplam harf sayýsýna bölünerek frekans bulunur
        }
    }//Frekans hesaplama (Bigram) bitti

    //Frekans hesaplama (Trigram)
    void calculate_frequencies_tri(char str[]){
        char gecici[50];    //Karþýlaþtýrmak için matrix string dizisinden geçici olarak kelime almamýzý saðlayan deðiþken
        int sayac;  //Her kelimenin kaç defa stringde bulunduðunu tutar
        int uzunluk = strlen(str);  //Stringimizin uzunluðu
        for(int i=0;i<10;i++){  //matrix dizimizin her öðesini geçici deðiþkene aktarýp, metin içinde kaç defa çýktýðýný bulup frekansý hesaplayan döngü
            sayac = 0;  //Döngü her baþa geldiðinde sýfýrlanýr
            strcpy(gecici, matrix_trigram_strings[i]);   //Döngü her baþa geldiðinde matrixten yeni kelime alýnýr
            for(int j=0;j<strlen(str);j++){  //Stringin baþýndan sonuna kelime kaç kere varsa sayýlýr
                while((strstr(str+j, gecici)) != NULL){
                    sayac++;
                }
            }
        calculated_frequencies[2][i]=sayac/uzunluk; //Kelime kaç defa var bulunduktan sonra toplam harf sayýsýna bölünerek frekans bulunur
        }
    }//Frekans hesaplama (Trigram) bitti

    //Frekans uzaklýk hesaplama
    void calculate_distances(){
        for(int i=0;i<10;i++){
            distances[1][i] = calculated_frequencies[1][i] - frequency[1][i];   //Ýngilizce bigramlarýn uzaklýklarý
            distances[1][i+10]= calculated_frequencies[2][i] - frequency[1][i+10];  //Ýngilizce trigramlarýn uzaklýklarý
            distances[2][i] = calculated_frequencies[1][i] - frequency[2][i];   //Almanca bigramlarýn uzaklýklarý
            distances[2][i+10]= calculated_frequencies[2][i] - frequency[2][i+10];  //Almanca trigramlarýn uzaklýklarý
        }
    }
    //Hangi dil olduðunu veren fonksiyon
    void dilitani(){
        float toplam_ing=0;
        float toplam_alm=0;

        //Fonksiyonlarý sýrasýyla çaðýrýrýz
        filter_str(temizlenecek_metin,temizlenmis_metin);
        calculate_frequencies_bi(temizlenmis_metin);
        calculate_frequencies_tri(temizlenmis_metin);
        calculate_distances();

        //Distance dizisindeki deðerlerin toplamýný alýp deðiþkenlere atarýz
        for(int i=0;i<20;i++){
            toplam_ing+=distances[1][i];
        }
        for(int i=0;i<20;i++){
            toplam_alm+=distances[2][i];
        }

        //Sonuca göre dilin ne olabileceðini söyleriz
        if(abs(toplam_alm)<abs(toplam_ing)){
            printf("Metnin dili almanca olabilir.\nToplam Alm: %f, Toplam Ing: %f\n",toplam_alm,toplam_ing);
        }
        if(abs(toplam_alm)>abs(toplam_ing)){
            printf("Metnin dili ingilizce olabilir.\nToplam Alm: %f, Toplam Ing: %f\n",toplam_alm,toplam_ing);
        }
    }

    //Menü fonksiyonu
    void menu(){
        int giris = 0 ;
        while(giris != 2 ){ //2 girilince fonksiyondan çýkýlýr
            printf("1-Metnin dilini tanimla\n2-Programdan cik\n(Lutfen harf girmeyin)\n");//Kullanicidan giris beklenir
            scanf("%d",&giris);
            if(giris == 1){//1 girildiginde metin istenir, 1 veya 2 girilmezse menü tekrar gösterilir
                printf("Bir metin giriniz: ");
                fflush(stdin);
                gets(temizlenecek_metin);   //Ýnput metni stringe atanýr
                dilitani(); //Sonucu veren fonksiyon çaðýrýlýr
            }
        }
    }//Menü fonksiyonu bitti

//Main
    int main(void){
        menu();
        return(0);
    }
