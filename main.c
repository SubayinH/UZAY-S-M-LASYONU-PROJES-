#include <stdio.h>
#include <math.h>
#include <string.h>

#define PI 3.14159265359
#define GEZEGEN_SAYISI 8

// Gezegen isimleri
const char* gezegenIsimleri[GEZEGEN_SAYISI] = {
    "Merkur", "Venus", "Dunya", "Mars",
    "Jupiter", "Saturn", "Uranus", "Neptun"
};

// Gezegenlerin yerçekimi ivmeleri (m/s²)
// Güneşe yakından uzağa doğru sıralı
double gezegenYercekimi[GEZEGEN_SAYISI] = {
    3.7,   // Merkür
    8.87,  // Venüs
    9.81,  // Dünya
    3.71,  // Mars
    24.79, // Jüpiter
    10.44, // Satürn
    8.69,  // Uranüs
    11.15  // Neptün
};



// Mutlak değer için ternary operator kullanan yardımcı fonksiyon
double mutlakDeger(double sayi) {
    return (sayi < 0) ? -sayi : sayi;
}

// Deney fonksiyonları
void serbestDusme(double* gDizisi, double sure);
void yukariAtis(double* gDizisi, double hiz);
void agirlik(double* gDizisi, double kutle);
void potansiyelEnerji(double* gDizisi, double kutle, double yukseklik);
void hidrostatikBasinc(double* gDizisi, double yogunluk, double derinlik);
void arsimetKuvveti(double* gDizisi, double yogunluk, double hacim);
void sarkacPeriyodu(double* gDizisi, double uzunluk);
void ipGerilmesi(double* gDizisi, double kutle);
void asansor(double* gDizisi, double kutle, double ivme, int yon);

void menuGoster() {
    printf("\n");
    printf("========================================\n");
    printf("         UZAY SIMULASYONU MENUSU       \n");
    printf("========================================\n");
    printf("1. Serbest Dusme Deneyi\n");
    printf("2. Yukari Atis Deneyi\n");
    printf("3. Agirlik Deneyi\n");
    printf("4. Kutlecekimsel Potansiyel Enerji Deneyi\n");
    printf("5. Hidrostatik Basinc Deneyi\n");
    printf("6. Arsimet Kaldirma Kuvveti Deneyi\n");
    printf("7. Basit Sarkac Periyodu Deneyi\n");
    printf("8. Sabit Ip Gerilmesi Deneyi\n");
    printf("9. Asansor Deneyi\n");
    printf("-1. Programdan Cik\n");
    printf("========================================\n");
    printf("Seciminiz: ");
}



void serbestDusme(double* gDizisi, double sure) {
    // Negatif süreyi mutlak değere çevir
    sure = mutlakDeger(sure);

    printf("\n========================================\n");
    printf("   SERBEST DUSME DENEYI SONUCLARI\n");
    printf("   Sure: %.2f saniye\n", sure);
    printf("========================================\n\n");

    // Diziye pointer ile erişim
    for(int i = 0; i < GEZEGEN_SAYISI; i++) {
        double g = *(gDizisi + i);  // Pointer aritmetiği ile erişim
        double h = 0.5 * g * sure * sure;  // h = (1/2) * g * t²

        printf("%s'te dusulen yukseklik: %.2f metre\n",
               gezegenIsimleri[i], h);
    }
    printf("\n");
}


void yukariAtis(double* gDizisi, double hiz) {
    hiz = mutlakDeger(hiz);

    printf("\n========================================\n");
    printf("   YUKARI ATIS DENEYI SONUCLARI\n");
    printf("   Baslangic Hizi: %.2f m/s\n", hiz);
    printf("========================================\n\n");

    for(int i = 0; i < GEZEGEN_SAYISI; i++) {
        double g = *(gDizisi + i);
        double hMax = (hiz * hiz) / (2 * g);  // h_max = v₀² / 2g

        printf("%s'te maksimum yukseklik: %.2f metre\n",
               gezegenIsimleri[i], hMax);
    }
    printf("\n");
}

void agirlik(double* gDizisi, double kutle) {
    kutle = mutlakDeger(kutle);

    printf("\n========================================\n");
    printf("   AGIRLIK DENEYI SONUCLARI\n");
    printf("   Kutle: %.2f kg\n", kutle);
    printf("========================================\n\n");

    for(int i = 0; i < GEZEGEN_SAYISI; i++) {
        double g = *(gDizisi + i);
        double G = kutle * g;  // G = m * g

        printf("%s'te agirlik: %.2f Newton\n",
               gezegenIsimleri[i], G);
    }
    printf("\n");
}

void potansiyelEnerji(double* gDizisi, double kutle, double yukseklik) {
    kutle = mutlakDeger(kutle);
    yukseklik = mutlakDeger(yukseklik);

    printf("\n========================================\n");
    printf("   POTANSIYEL ENERJI DENEYI SONUCLARI\n");
    printf("   Kutle: %.2f kg, Yukseklik: %.2f m\n", kutle, yukseklik);
    printf("========================================\n\n");

    for(int i = 0; i < GEZEGEN_SAYISI; i++) {
        double g = *(gDizisi + i);
        double Ep = kutle * g * yukseklik;  // Ep = m * g * h

        printf("%s'te potansiyel enerji: %.2f Joule\n",
               gezegenIsimleri[i], Ep);
    }
    printf("\n");
}

void hidrostatikBasinc(double* gDizisi, double yogunluk, double derinlik) {
    yogunluk = mutlakDeger(yogunluk);
    derinlik = mutlakDeger(derinlik);

    printf("\n========================================\n");
    printf("   HIDROSTATIK BASINC DENEYI SONUCLARI\n");
    printf("   Yogunluk: %.2f kg/m^3, Derinlik: %.2f m\n", yogunluk, derinlik);
    printf("========================================\n\n");

    for(int i = 0; i < GEZEGEN_SAYISI; i++) {
        double g = *(gDizisi + i);
        double P = yogunluk * g * derinlik;  // P = ρ * g * h

        printf("%s'te hidrostatik basinc: %.2f Pascal\n",
               gezegenIsimleri[i], P);
    }
    printf("\n");
}

void arsimetKuvveti(double* gDizisi, double yogunluk, double hacim) {
    yogunluk = mutlakDeger(yogunluk);
    hacim = mutlakDeger(hacim);

    printf("\n========================================\n");
    printf("   ARSIMET KALDIRMA KUVVETI SONUÇLARI\n");
    printf("   Yoğunluk: %.2f kg/m^3, Hacim: %.2f m^3\n", yogunluk, hacim);
    printf("========================================\n\n");

    for(int i = 0; i < GEZEGEN_SAYISI; i++) {
        double g = *(gDizisi + i);
        double Fk = yogunluk * g * hacim;  // Fk = ρ * g * V

        printf("%s'te kaldirma kuvveti: %.2f Newton\n",
               gezegenIsimleri[i], Fk);
    }
    printf("\n");
}

void sarkacPeriyodu(double* gDizisi, double uzunluk) {
    uzunluk = mutlakDeger(uzunluk);

    printf("\n========================================\n");
    printf("   SARKAC PERIYODU DENEYI SONUCLARI\n");
    printf("   Sarkac Uzunlugu: %.2f m\n", uzunluk);
    printf("========================================\n\n");

    for(int i = 0; i < GEZEGEN_SAYISI; i++) {
        double g = *(gDizisi + i);
        double T = 2 * PI * sqrt(uzunluk / g);  // T = 2π√(L/g)

        printf("%s'te sarkac periyodu: %.2f saniye\n",
               gezegenIsimleri[i], T);
    }
    printf("\n");
}

void ipGerilmesi(double* gDizisi, double kutle) {
    kutle = mutlakDeger(kutle);

    printf("\n========================================\n");
    printf("   IP GERILMESI DENEYI SONUCLARI\n");
    printf("   Kutle: %.2f kg\n", kutle);
    printf("========================================\n\n");

    for(int i = 0; i < GEZEGEN_SAYISI; i++) {
        double g = *(gDizisi + i);
        double T = kutle * g;  // T = m * g

        printf("%s'te ip gerilmesi: %.2f Newton\n",
               gezegenIsimleri[i], T);
    }
    printf("\n");
}

void asansor(double* gDizisi, double kutle, double ivme, int yon) {
    kutle = mutlakDeger(kutle);
    ivme = mutlakDeger(ivme);

    printf("\n========================================\n");
    printf("   ASANSOR DENEYI SONUCLARI\n");
    printf("   Kutle: %.2f kg, Ivme: %.2f m/s^2\n", kutle, ivme);
    printf("   Yon: %s\n", yon == 1 ? "Yukari ivmelenme/Asagi yavaslama" : "Asagi ivmelenme/Yukari yavaslama");
    printf("========================================\n\n");

    for(int i = 0; i < GEZEGEN_SAYISI; i++) {
        double g = *(gDizisi + i);
        double N;

        if(yon == 1) {
            N = kutle * (g + ivme);  // Yukarı ivmelenme
        } else {
            N = kutle * (g - ivme);  // Aşağı ivmelenme
        }

        printf("%s'te hissedilen agirlik: %.2f Newton\n",
               gezegenIsimleri[i], N);
    }
    printf("\n");
}


int main() {
    char bilimInsani[100];
    int secim;

    // Bilim insanı adını al
    printf("========================================\n");
    printf("   UZAY SIMULASYONU PROGRAMINA\n");
    printf("         HOS GELDINIZ!\n");
    printf("========================================\n\n");
    printf("Lutfen adinizi girin: ");
    fgets(bilimInsani, sizeof(bilimInsani), stdin);
    // Satır sonu karakterini kaldır
    bilimInsani[strcspn(bilimInsani, "\n")] = 0;

    printf("\nMerhaba %s! Simulasyona basliyor...\n", bilimInsani);

    // Ana döngü
    while(1) {
        menuGoster();
        scanf("%d", &secim);

        if(secim == -1) {
            printf("\n%s, simulasyon sonlandırılıyor...\n", bilimInsani);
            printf("Iyi gunler dileriz!\n");
            break;
        }

        // Değişkenler
        double sure, hiz, kutle, yukseklik, yogunluk, derinlik, hacim, uzunluk, ivme;
        int yon;

        switch(secim) {
            case 1:
                printf("\nSure (saniye): ");
                scanf("%lf", &sure);
                serbestDusme(gezegenYercekimi, sure);
                break;

            case 2:
                printf("\nBaslangic hizi (m/s): ");
                scanf("%lf", &hiz);
                yukariAtis(gezegenYercekimi, hiz);
                break;

            case 3:
                printf("\nKutle (kg): ");
                scanf("%lf", &kutle);
                agirlik(gezegenYercekimi, kutle);
                break;

            case 4:
                printf("\nKutle (kg): ");
                scanf("%lf", &kutle);
                printf("Yukseklik (m): ");
                scanf("%lf", &yukseklik);
                potansiyelEnerji(gezegenYercekimi, kutle, yukseklik);
                break;

            case 5:
                printf("\nSivinin yogunlugu (kg/m^3): ");
                scanf("%lf", &yogunluk);
                printf("Derinlik (m): ");
                scanf("%lf", &derinlik);
                hidrostatikBasinc(gezegenYercekimi, yogunluk, derinlik);
                break;

            case 6:
                printf("\nSivinin yogunlugu (kg/m^3): ");
                scanf("%lf", &yogunluk);
                printf("Cismin batan hacmi (m^3): ");
                scanf("%lf", &hacim);
                arsimetKuvveti(gezegenYercekimi, yogunluk, hacim);
                break;

            case 7:
                printf("\nSarkac uzunlugu (m): ");
                scanf("%lf", &uzunluk);
                sarkacPeriyodu(gezegenYercekimi, uzunluk);
                break;

            case 8:
                printf("\nKutle (kg): ");
                scanf("%lf", &kutle);
                ipGerilmesi(gezegenYercekimi, kutle);
                break;

            case 9:
                printf("\nKutle (kg): ");
                scanf("%lf", &kutle);
                printf("Asansor ivmesi (m/s^2): ");
                scanf("%lf", &ivme);
                printf("Yon (1: Yukari ivmelenme/Asagi yavaslama, 2: Asagi ivmelenme/Yukari yavaslama): ");
                scanf("%d", &yon);
                asansor(gezegenYercekimi, kutle, ivme, yon);
                break;

            default:
                printf("\nGecersiz secim! Lutfen 1-9 arasi veya -1 girin.\n");
        }
    }

    return 0;
}
