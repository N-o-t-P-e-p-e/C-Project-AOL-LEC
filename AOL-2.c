#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Display();											// Ini adalah function prototyping untuk fungsi Display().
void SelectRow();										// Ini adalah function prototyping untuk fungsi SelectRow().
void SortBy();											// Ini adalah function prototyping untuk fungsi SortBy().
void Export();											// Ini adalah function prototyping untuk fungsi Export()

typedef struct											// Struct untuk menyimpan data properti secara sementara sebelum dimasukkan ke file.
{
    char location[50];									// Properti untuk struct Property.
    char city[50];
    int price;
    int rooms;
    int bathrooms;
    int carpark;
    char type[20];
    char furnish[20];
} Property;												

int main()												// Main function.
{
    int option = 0;										// Ini option untuk memilih menu.
    
    printf("What do you want to do?\n");				// Perintah yang akan ditampilkan di menu utama.
    printf("1. Display Data\n");
    printf("2. Search Data\n");
    printf("3. Sort Data\n");
    printf("4. Export Data\n");
    printf("5. Exit\n");

    while (1)											
    {
        printf("Your choice: ");

        if (scanf("%d", &option) != 1)                  // Melakukan input sekaligus cek apakah input user adalah angka.
        {
            printf("Option invalid. Please enter a number.\n");
            while (getchar() != '\n');                  // Clear input buffer.
            continue;
        }

        switch(option)									// Switch untuk menyesuaikan sesuai input user.
        {
            case 1:										// Ketika user menginput option == 1, maka.
                Display();								// Tampilkan menu Display().
                break;

            case 2:										// Ketika user menginput option == 2, maka.
                SelectRow();							// Tampilkan menu SelectRow().
                break;

            case 3:										// Ketika user menginput option == 3, maka.
                SortBy();								// Tampilkan menu SortBy().
                break;

            case 4:										// Ketika user menginput option == 4, maka.
                Export();								// tampilkan menu Export().
                break;

            case 5:										// Ketika user menginput option == 5, maka.
                return 0;								// Kembali / exit.
            
            default:									// Jika ada input selain 1-5.
                printf("Option invalid.\n");			// Tampilkan option invalid.
        }
    }
    
    return 0;
}

// Fungsi Display untuk menampilkan menu display.
void Display()
{
    // Variabel untuk menampung jumlah row yang harus ditampilkan.
    int rows;

    // Berfungsi untuk memvalidasi apakah input rows-nya sesuai ketentuan atau tidak.
    while (1)
    {
        printf("Number of rows: ");

        // Jika inputnya berupa huruf/kalimat.
        if (scanf("%d", &rows) != 1)
        {
            printf("Invalid input. Please enter a number.\n");

            // Clear buffer inputnya.
            while (getchar() != '\n');
            // Ulangi loopnya.
            continue;
        }

        // Jika inputnya kurang atau sama dengan 0.
        if (rows <= 0)
        {
            printf("Number of rows must be greater than 0.\n");

            // Clear buffer inputnya.
            while (getchar() != '\n');
            // Ulangi loopnya.
            continue;
        }

        // Clear buffer inputnya jika sesuai dengan ketentuan.
        while (getchar() != '\n');
        // Matikan loopnya.
        break;
    }

    // Variabel yang menyimpan path file data csv.
    char path[] = "DummyData.csv";

    // Membuka file dengan fungsi fopen yang merujuk pada path data dengan mode akses "r" atau "read".
    FILE *file = fopen(path, "r");

    // Jika file tidak ditemukan maka beri pesan error.
    if(file == NULL)
    {
        printf("[ERROR]: Failed to open file at location: %s\n", path);
        return;
    }
    
    // Satu baris yang akan kita ambil dalam scanning baris nanti.
    char line[1000];
    // Variabel count digunakan untuk menghitung berapa baris yang sudah ditampilkan, nanti akan dicocokkan dengan rows yang sudah di input.
    int count = 0;

    // Printf untuk print header tabel yang akan ditampilkan nanti.
    printf("\n%-20s %-15s %-10s %-6s %10s %-10s %-10s %-10s\n", "Location", "City", "Price", "Rooms", "Bathrooms", "Carpark", "Type", "Furnish");

    // FIX!! Metode yang berguna untuk tidak mengambil header yang ada dalam file csv! (KALAU DIHAPUS HEADER AKAN DIPRINT DAN OUTPUT BISA KACAU).
    fgets(line, sizeof(line), file);
    
    // Perulangan untuk menampilkan data. Jika masih terdapat baris pada file dan juga selama count tidak melebihi jumlah rows yang diminta.
    while (fgets(line, sizeof(line), file) != NULL && count < rows)
    {
        // Memanggil struct property. Tujuannya data yang sudah discan akan dipindahkan ke variabel 'sementara' yang ada di struct.
        Property prop;
        
        // Melakukan scanning data yang ada di file csv. Data dipecah/dipisahkan berdasarkan koma (sesuai format yang ada di dalam file csv). Kemudian data akan dipassing ke variabel yang diinisialisasi di dalam struct.
        sscanf(line, "%[^,],%[^,],%d,%d,%d,%d,%[^,],%s", prop.location, prop.city, &prop.price, &prop.rooms, &prop.bathrooms, &prop.carpark, prop.type, prop.furnish);

        // Menampilkan data yang sudah di passing ke dalam struct kemudian diformat dalam bentuk tabel.
        printf("%-20s %-15s %-10d %-7d %-9d %-10d %-10s %-10s\n", prop.location, prop.city, prop.price, prop.rooms, prop.bathrooms, prop.carpark, prop.type, prop.furnish);
        
        // Count bertambah untuk kebutuhan loop agar loop tidak berjalan melebihi rows yang diminta user.
        count++;
    }

    // Supaya rapi. :)
    printf("\n");

    // Close file setelah dibuka dan digunakan.
    fclose(file);

    // Pause sebelum kembali ke menu utama.
    printf("Press Enter to return to main menu...");

    // Clear buffer input sebelum menunggu enter. Tujuannya supaya tidak langsung lanjut tanpa menunggu enter.
    while (getchar() != '\n');
    getchar();
}

// Fungsi yang berguna untuk melakukan searching.
void SelectRow()
{
    // Variabel untuk menampung string column apa yang mau dicari.
    char option[50];
    // Variabel untuk menampung data apa dari suatu column yang akan dicari.
    char data[50];

    // Perintah sekaligus meminta input pengguna terkait column yang akan dicari.
    printf("Choose column: ");
    scanf("%s", option);

    // Perintah sekaligus meminta inptut pengguna terkait data dari column yang mau dicari.
    printf("What data do you want to find? ");
    scanf("%s", data);

    // Variabel yang menyimpan path file data csv.
    char path[] = "DummyData.csv";

    // Membuka file dengan fungsi fopen yang merujuk pada path data dengan mode akses "r" atau "read".
    FILE *file = fopen(path, "r");

    // Jika file tidak ditemukan maka beri pesan error.
    if(file == NULL)
    {
        printf("[ERROR]: Failed to open file at location: %s\n", path);
        return;
    }

    // Satu baris yang akan kita ambil dalam scanning baris nanti.
    char line[1000];
    // Variabel yang berguna untuk menyimpan nilai boolean terkait apakah data berhasil ditemukan.
    int found = 0;

    // FIX!! Metode yang berguna untuk tidak mengambil header yang ada dalam file csv! (KALAU DIHAPUS HEADER AKAN DIPRINT DAN OUTPUT BISA KACAU).
    fgets(line, sizeof(line), file);

    // Suppaya rapi. :)
    printf("\n");

    // Perulangan untuk menampilkan data. Jika masih terdapat baris pada file.
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Memanggil struct property. Tujuannya data yang sudah discan akan dipindahkan ke variabel 'sementara' yang ada di struct.
        Property prop;
        // Membuat variabel target data, defaultnya adalah NULL atau tidak ada.
        char *target = NULL;
        // Membuat variabel target data namun kali ini untuk tipe data integer, defaultnya adalah -1.
        int targetInt = -1;

        // Melakukan scanning data yang ada di file csv. Data dipecah/dipisahkan berdasarkan koma (sesuai format yang ada di dalam file csv). Kemudian data akan dipassing ke variabel yang diinisialisasi di dalam struct.
        sscanf(line, "%[^,],%[^,],%d,%d,%d,%d,%[^,],%s", prop.location, prop.city, &prop.price, &prop.rooms, &prop.bathrooms, &prop.carpark, prop.type, prop.furnish);

        // Melalukan comparing column yang diminta user apakah cocok dengan column yang ada di data csv.
        if(strcmp(option, "Location") == 0)
            // Jika column memang ada dalam data csv, maka jadikan nilai yang ada variabel struct sebagai target data yang ditampilkan nanti.
            target = prop.location;
        else if(strcmp(option, "City") == 0)
            target = prop.city;
        else if(strcmp(option, "Price") == 0)
            targetInt = prop.price;
        else if(strcmp(option, "Rooms") == 0)
            targetInt = prop.rooms;
        else if(strcmp(option, "Bathrooms") == 0)
            targetInt = prop.bathrooms;
        else if(strcmp(option, "Carpark") == 0)
            targetInt = prop.carpark;
        else if(strcmp(option, "Type") == 0)
            target = prop.type;
        else if(strcmp(option, "Furnish") == 0)
            target = prop.furnish;

        // Jika targetnya memang ada dan data yang ditarget itu susuai dengan data yang diminta user maka lanjutkan.
        if((target && strcmp(target, data) == 0) || (targetInt && targetInt == atoi(data)))
        {
            // Karena data sudah ditemukan namun belum dilabelkan sebagai "ditemukan", maka tampilkan judulnya terlebih dahulu. Hal ini dilakukan agar judul tidak terus menerus ditampilkan setiap kali data ditemukan.
            if(!found)
            {
                // Tampilkan judul dan header sebagai bentuk format tabel.
                printf("Data found. Detail of data:\n\n");
                printf("%-20s %-15s %-10s %-6s %10s %-10s %-10s %-10s\n", "Location", "City", "Price", "Rooms", "Bathrooms", "Carpark", "Type", "Furnish");
            }

            // Tampilkan data dalam format tabel.
            printf("%-20s %-15s %-10d %-7d %-9d %-10d %-10s %-10s\n", prop.location, prop.city, prop.price, prop.rooms, prop.bathrooms, prop.carpark, prop.type, prop.furnish);

            // Labelkan bahwa data sudah ditemukan.
            found = 1;
        }
    }

    // Jika data tidak ditemukan maka tampilkan kalau data tidak ditemukan.
    if(!found)
        printf("Data not found!\n");

    // Supaya rapi. :)
    printf("\n");

    // Tutup file setelah dibuka dan digunakan.
    fclose(file);

    // Pause sebelum kembali ke menu utama.
    printf("Press Enter to return to main menu...");

    // Clear buffer input sebelum menunggu enter. Tujuannya supaya tidak langsung lanjut tanpa menunggu enter.
    while (getchar() != '\n');
    getchar();
}

// Fungsi untuk mengurutkan data.
void SortBy()
{
    // Variabel untuk menampung string column apa yang mau diurutkan.
    char column[50];
    // Variabel untuk menampung string order pengurutan (ascending / descending).
    char order[10];

    // Perintah sekaligus tempat input user dalam memasukkan nilai column yang akan diurutkan.
    printf("Choose column: ");
    scanf("%s", column);

    // Perintah sekaligus tempat input user dalam memasukkan nilai order pengurutan.
    printf("Sort ascending or descending?: ");
    scanf("%s", order);

    // Variabel yang menyimpan path file data csv.
    char path[] = "DummyData.csv";

    // Membuka file dengan fungsi fopen yang merujuk pada path data dengan mode akses "r" atau "read".
    FILE *file = fopen(path, "r");

    // Jika file tidak ditemukan maka beri pesan error.
    if(file == NULL)
    {
        printf("[ERROR]: Failed to open file at location: %s\n", path);
        return;
    }

    // Array of struct Property untuk menyimpan data sementara sebelum diurutkan.
    // Analoginya, semua data yang di scan nanti akan dimasukkan dan disimpan dalam array of struct ini terlebih dahulu, baru kemudian isi array itu baru diurutkan sesuai permintaan user.
    Property prop[10000];

    // Variabel n untuk menghitung jumlah data yang ada atau data yang sedang diproses.
    int n = 0;

    // Satu baris yang akan kita ambil dalam scanning baris nanti.
    char line[1000];

    // FIX!! Metode yang berguna untuk tidak mengambil header yang ada dalam file csv! (KALAU DIHAPUS HEADER AKAN DIPRINT DAN OUTPUT BISA KACAU).
    fgets(line, sizeof(line), file);

    // Perulangan untuk menampilkan data. Jika masih terdapat baris pada file maka perulangan akan terus berjalan.
    while (fgets(line, sizeof(line), file) != NULL)
    {
        // Melakukan scanning data yang ada di file csv. Data dipecah/dipisahkan berdasarkan koma (sesuai format yang ada di dalam file csv). Kemudian data akan dipassing ke variabel yang diinisialisasi di dalam struct.
        sscanf(line, "%[^,],%[^,],%d,%d,%d,%d,%[^,],%s", prop[n].location, prop[n].city, &prop[n].price, &prop[n].rooms, &prop[n].bathrooms, &prop[n].carpark, prop[n].type, prop[n].furnish);

        // Jumlah data bertambah setiap kali ada data yang berhasil discan.
        n++;
    }

    // Tutup file setelah dibuka dan digunakan. (Semua data sudah dipindah ke array, kemudian baru di sorting).
    fclose(file);

    // Algoritma Bubble Sort untuk mengurutkan data berdasarkan column dan order (ascending/descending) yang diminta user.
    for(int i = 0; i < n-1; i++)
    {
        for(int j = 0; j < n-i-1; j++)
        {
            // Variabel berupa boolean untuk menandai apakah perlu menukar posisi data atau tidak.
            int swap = 0;

            // Membandingkan column yang diminta user untuk diurutkan.
            if (strcmp(column, "Location") == 0)
                // Membandingkan order yang diminta user untuk mengurutkan data. (Menggunakan ternary operator).
                // Jika ascending maka bandingkan apakah data saat ini yang mana berupa string lebih besar dari data selanjutnya. (Membandingkan dengan nilai ASCII).
                // Jika descending maka bandingkan apakah data saat ini yang mana berupa string lebih kecil dari data selanjutnya. (Membandingkan dengan nilai ASCII).
                swap = (strcmp(order, "asc") == 0) ? (strcmp(prop[j].location, prop[j+1].location) > 0) : (strcmp(prop[j].location, prop[j+1].location) < 0);
            else if(strcmp(column, "City") == 0)
                swap = (strcmp(order, "asc") == 0) ? (strcmp(prop[j].city, prop[j+1].city) > 0) : (strcmp(prop[j].city, prop[j+1].city) < 0);
            else if(strcmp(column, "Price") == 0)
                // Membandingkan order yang diminta user untuk mengurutkan data. (Menggunakan ternary operator).
                // Jika ascending maka bandingkan apakah data saat ini lebih besar dari data selanjutnya. (Membandingkan berdasarkan besaran angka).
                // Jika descending maka bandingkan apakah data saat ini lebih kecil dari data selanjutnya. (Membandingkan berdasarkan besaran angka).
                swap = (strcmp(order, "asc") == 0) ? (prop[j].price > prop[j+1].price) : (prop[j].price < prop[j+1].price);
            else if(strcmp(column, "Rooms") == 0)
                swap = (strcmp(order, "asc") == 0) ? (prop[j].rooms > prop[j+1].rooms) : (prop[j].rooms < prop[j+1].rooms);
            else if(strcmp(column, "Bathrooms") == 0)
                swap = (strcmp(order, "asc") == 0) ? (prop[j].bathrooms > prop[j+1].bathrooms) : (prop[j].bathrooms < prop[j+1].bathrooms);
            else if(strcmp(column, "Carpark") == 0)
                swap = (strcmp(order, "asc") == 0) ? (prop[j].carpark > prop[j+1].carpark) : (prop[j].carpark < prop[j+1].carpark);
            else if(strcmp(column, "Type") == 0)
                swap = (strcmp(order, "asc") == 0) ? (strcmp(prop[j].type, prop[j+1].type) > 0) : (strcmp(prop[j].type, prop[j+1].type) < 0);
            else if(strcmp(column, "Furnish") == 0) 
                swap = (strcmp(order, "asc") == 0) ? (strcmp(prop[j].furnish, prop[j+1].furnish) > 0) : (strcmp(prop[j].furnish, prop[j+1].furnish) < 0);

            // Jika perlu menukar posisi data, maka lakukan penukaran posisi data.
            if(swap)
            {
                // Tukar posisi data menggunakan variabel temporary.
                Property temp = prop[j];
                prop[j] = prop[j+1];
                prop[j+1] = temp;
            }
        }
    }

    // Suppaya rapi tampilkan judulnya dulu. :)
    printf("\nData found. Detail of data:\n\n");

    // Tampilkan data yang sudah diurutkan dalam format tabel (Tampilkan header tabelnya dulu).
    printf("%-20s %-15s %-10s %-6s %10s %-10s %-10s %-10s\n", "Location", "City", "Price", "Rooms", "Bathrooms", "Carpark", "Type", "Furnish");

    // Perulangan untuk menampilkan data yang sudah diurutkan. Perulangan berjalan jika data masih kurang dari 10, jika sudah 10 maka berhenti.
    for(int i = 0; i < ((n < 10) ? n : 10); i++)
        // Print data yang sudah diurutkan dalam format tabel.
        printf("%-20s %-15s %-10d %-7d %-9d %-10d %-10s %-10s\n", prop[i].location, prop[i].city, prop[i].price, prop[i].rooms, prop[i].bathrooms, prop[i].carpark, prop[i].type, prop[i].furnish);

    // Supaya rapi. :)
    printf("\n");

    // Pause sebelum kembali ke menu utama.
    printf("Press Enter to return to main menu...");
    
    // Clear buffer input sebelum menunggu enter. Tujuannya supaya tidak langsung lanjut tanpa menunggu enter.
    while (getchar() != '\n');
    getchar();
}

// Fungsi Export untuk mengekspor data.
void Export()
{
    // Variabel untuk menampung nama file yang akan dibuat.
    char filename[100];

    // Variabel yang menyimpan path file data csv.
    char path[] = "DummyData.csv";

    // Variabel untuk menampung isi file (per line/baris) saat proses copy berlangsung nanti.
    char line[1000];

    // Perintah sekaligus tempat input user dalam memasukkan nama file yang akan dibuat.
    printf("File name: ");
    scanf("%s", filename);

    // Buka file sumber untuk dibaca menggunakan access mode "r" atau "read".
    FILE *file1 = fopen(path, "r");

    // Jika file tidak ditemukan maka beri pesan error.
    if(file1 == NULL)
    {
        printf("[ERROR]: Failed to open source file\n");
        return;
    }

    // Menambahkan eksensi file .csv terhadap file name yang diinput user.
    strcat(filename, ".csv");

    // Buka/membuat file yang dibuat untuk ditulis menggunakan access mode "w" atau "write".
    FILE *file2 = fopen(filename, "w");

    // Jika file tidak dapat dibuat maka beri pesan error dan tutup file sumber.
    if(file2 == NULL)
    {
        printf("[ERROR]: Failed to create file\n");
        fclose(file1);
        return;
    }

    // Copy seluruh isi file dan masukkan data dari file sumber ke file yang baru dibuat.
    while(fgets(line, sizeof(line), file1))
        fputs(line, file2);

    // Tutup kedua file (sumber dan file yang dibuat) setelah proses copy selesai.
    fclose(file1);
    fclose(file2);

    printf("Data successfully written to file %s!\n\n", filename);

    // Pause sebelum kembali ke menu utama.
    printf("Press Enter to return to main menu...");
    
    // Clear buffer input sebelum menunggu enter. Tujuannya supaya tidak langsung lanjut tanpa menunggu enter.
    while (getchar() != '\n');
    getchar();
}
