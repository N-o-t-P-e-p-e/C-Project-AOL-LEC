#include <stdio.h>
#include <string.h>

int main()
{
    // Variabel ini digunakan untuk menyimpan string input dari pengguna.
    char string[101];

    // Membaca string dari input pengguna.
    scanf("%s", string);

    // Variabel ini digunakan untuk menyimpan string yang telah dibalik.
    char stringReverse[101];

    // Mendapatkan panjang string input.
    int len = strlen(string);

    // Variabel ini digunakan sebagai indeks untuk stringReverse.
    int j = 0;

    // Membalik string dan menyimpannya di stringReverse.
    for(int i = len - 1; i >= 0; i--)
        stringReverse[j++] = string[i];

    // Mengubah huruf besar menjadi huruf kecil dan sebaliknya.
    for(int i = 0; i < len; i++)
    {
        // Cek apakah karakter adalah huruf besar.
        if(stringReverse[i] >= 'A' && stringReverse[i] <= 'Z')
            // Ubah ke huruf kecil dengan menambahkan 32 pada nilai ASCIInya.
            stringReverse[i] += 32;
        // Cek apakah karakter adalah huruf kecil.
        else if(stringReverse[i] >= 'a' && stringReverse[i] <= 'z')
            // Ubah ke huruf besar dengan mengurangi 32 pada nilai ASCIInya.
            stringReverse[i] -= 32;
    }

    // Mencetak string yang telah dibalik dan diubah hurufnya.
    for(int i = 0; i < len; i++)
        printf("%c", stringReverse[i]);

    // Supaya rapi. :)
    printf("\n");

    return 0;
}