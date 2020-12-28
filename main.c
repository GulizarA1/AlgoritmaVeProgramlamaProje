//K�t�phaneler
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
//Haz�r de�i�kenler
    const char matrix_bigram_strings[10][2] ={"th", "he", "in", "er", "an", "en", "ch", "de", "ei", "te"};
    const char matrix_trigram_strings[10][3]={"the", "and", "ing", "ent", "ion", "der", "sch", "ich", "nde", "die"};
    const char languages[2][7]={"english", "german"};
    char temizlenecek_metin[255];
    char temizlenmis_metin[255];
//Sat�rlarda bigramlarin ve trigramlarin, s�tunlarda ise dillerin yer aldigi frekans matrisi.
    const float frequency[2][20]={ 2.71, 2.33, 2.03, 1.78, 1.61, 1.13, 0.10, 0.10, 0.10, 0.10, 1.81, 0.73, 0.72, 0.42, 0.42, 0.10, 0.10, 0.10, 0.10, 0.10,
                                    0.10, 0.89, 1.71, 3.90, 1.07, 3.61, 2.36, 2.31, 1.98, 1.98, 0.10, 0.10, 0.10, 0.10, 0.10, 1.04, 0.76, 0.75, 0.72, 0.62
                                    };
    float distances [2][20];
    float calculated_frequencies[2][10];
//Fonsiyonlar

    //Metin temizleme fonksiyonu
    void filter_str(char str1[], char str2[]){ //str1 input ile al�nan metin, str2 temizlenmi� halinin tutulaca�� metin
         for(int i = 0; i<strlen(str1); i++){//input metninin sonuna kadar b�t�n karakterleri k���k harfe �eviririz
            str1[i] = tolower(str1[i]);
        }
        for(int i = 0; i<strlen(str1);i++){//input metninin sonuna kadar; karakter alfabetik veya bo�luk karakteri ise ikinci metine aktar�r�z
            if(isalpha(str1[i]) || str1[i])
                strncat(str2, str1+i, 1);
        }
    }//Metin temizleme fonksiyonu bitti

    //Frekans hesaplama (Bigram)
    void calculate_frequencies_bi(char str[]){
        char gecici[50];    //Kar��la�t�rmak i�in matrix string dizisinden ge�ici olarak kelime almam�z� sa�layan de�i�ken
        int sayac;  //Her kelimenin ka� defa stringde bulundu�unu tutar
        int uzunluk = strlen(str);  //Stringimizin uzunlu�u
        for(int i=0;i<10;i++){  //matrix dizimizin her ��esini ge�ici de�i�kene aktar�p, metin i�inde ka� defa ��kt���n� bulup frekans� hesaplayan d�ng�
            sayac = 0;  //D�ng� her ba�a geldi�inde s�f�rlan�r
            strcpy(gecici, matrix_bigram_strings[i]);   //D�ng� her ba�a geldi�inde matrixten yeni kelime al�n�r
            for(int j=0;j<strlen(str);j++)  //Stringin ba��ndan sonuna kelime ka� kere varsa say�l�r
                while((strstr(str+j, gecici)) != NULL){
                    sayac++;
                }
        calculated_frequencies[1][i]=sayac/uzunluk; //Kelime ka� defa var bulunduktan sonra toplam harf say�s�na b�l�nerek frekans bulunur
        }
    }//Frekans hesaplama (Bigram) bitti

    //Frekans hesaplama (Trigram)
    void calculate_frequencies_tri(char str[]){
        char gecici[50];    //Kar��la�t�rmak i�in matrix string dizisinden ge�ici olarak kelime almam�z� sa�layan de�i�ken
        int sayac;  //Her kelimenin ka� defa stringde bulundu�unu tutar
        int uzunluk = strlen(str);  //Stringimizin uzunlu�u
        for(int i=0;i<10;i++){  //matrix dizimizin her ��esini ge�ici de�i�kene aktar�p, metin i�inde ka� defa ��kt���n� bulup frekans� hesaplayan d�ng�
            sayac = 0;  //D�ng� her ba�a geldi�inde s�f�rlan�r
            strcpy(gecici, matrix_trigram_strings[i]);   //D�ng� her ba�a geldi�inde matrixten yeni kelime al�n�r
            for(int j=0;j<strlen(str);j++){  //Stringin ba��ndan sonuna kelime ka� kere varsa say�l�r
                while((strstr(str+j, gecici)) != NULL){
                    sayac++;
                }
            }
        calculated_frequencies[2][i]=sayac/uzunluk; //Kelime ka� defa var bulunduktan sonra toplam harf say�s�na b�l�nerek frekans bulunur
        }
    }//Frekans hesaplama (Trigram) bitti

    //Frekans uzakl�k hesaplama
    void calculate_distances(){
        for(int i=0;i<10;i++){
            distances[1][i] = calculated_frequencies[1][i] - frequency[1][i];   //�ngilizce bigramlar�n uzakl�klar�
            distances[1][i+10]= calculated_frequencies[2][i] - frequency[1][i+10];  //�ngilizce trigramlar�n uzakl�klar�
            distances[2][i] = calculated_frequencies[1][i] - frequency[2][i];   //Almanca bigramlar�n uzakl�klar�
            distances[2][i+10]= calculated_frequencies[2][i] - frequency[2][i+10];  //Almanca trigramlar�n uzakl�klar�
        }
    }
    //Hangi dil oldu�unu veren fonksiyon
    void dilitani(){
        float toplam_ing=0;
        float toplam_alm=0;

        //Fonksiyonlar� s�ras�yla �a��r�r�z
        filter_str(temizlenecek_metin,temizlenmis_metin);
        calculate_frequencies_bi(temizlenmis_metin);
        calculate_frequencies_tri(temizlenmis_metin);
        calculate_distances();

        //Distance dizisindeki de�erlerin toplam�n� al�p de�i�kenlere atar�z
        for(int i=0;i<20;i++){
            toplam_ing+=distances[1][i];
        }
        for(int i=0;i<20;i++){
            toplam_alm+=distances[2][i];
        }

        //Sonuca g�re dilin ne olabilece�ini s�yleriz
        if(abs(toplam_alm)<abs(toplam_ing)){
            printf("Metnin dili almanca olabilir.\nToplam Alm: %f, Toplam Ing: %f\n",toplam_alm,toplam_ing);
        }
        if(abs(toplam_alm)>abs(toplam_ing)){
            printf("Metnin dili ingilizce olabilir.\nToplam Alm: %f, Toplam Ing: %f\n",toplam_alm,toplam_ing);
        }
    }

    //Men� fonksiyonu
    void menu(){
        int giris = 0 ;
        while(giris != 2 ){ //2 girilince fonksiyondan ��k�l�r
            printf("1-Metnin dilini tanimla\n2-Programdan cik\n(Lutfen harf girmeyin)\n");//Kullanicidan giris beklenir
            scanf("%d",&giris);
            if(giris == 1){//1 girildiginde metin istenir, 1 veya 2 girilmezse men� tekrar g�sterilir
                printf("Bir metin giriniz: ");
                fflush(stdin);
                gets(temizlenecek_metin);   //�nput metni stringe atan�r
                dilitani(); //Sonucu veren fonksiyon �a��r�l�r
            }
        }
    }//Men� fonksiyonu bitti

//Main
    int main(void){
        menu();
        return(0);
    }
