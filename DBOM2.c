#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_BARANG 100

struct barang {
    int harga;
    char nama[50];
    char kondisi[100];
    char deskripsi[100];
};

struct barang daftarbarang[MAX_BARANG];
int jumlahbarang = 0;

struct Pesanan {
    int id;
    char nama[100];
    char status[100];
};

struct Feedback {
    char username[100];
    char komentar[256];
} feedback;

struct User {
    int member;
    char pass[100];
    float saldo;
};

void loginAdmin ();
void User();

void loginPengguna(); // wihel
void registrasi(); 
void menuAdmin();

void menuPengguna(); // fatya

void MenuBarang(); // asta
void bacaDataDariFile(); 
void tambahbarang();
void tampilkanbarang();
void hapusbarang();

void statusPesanan(); // tadea
int tampilPesanan(struct Pesanan daftar[], int jumlah);
int tambahPesanan(struct Pesanan daftar[], int jumlah);
int hapusPesanan(struct Pesanan daftar[], int jumlah);

void feedbackAdmin(); // vadyo

void menuKeuangan(); // aura
void totalPendapatan();
void historiTransaksi();

void menuPembelian(); // fatya & vadyo
void melihatbarang();
void searchingbarang();
void membelibarang(); 
void feedbackUser();

int bacaUser(struct User *user);
int simpanUser(struct User *user);

void menuInformasi();
void topupSaldo();
void lihatSaldo();
void membership();
void menggantiPass();

int main () {
    int pilihan;

    printf("=== MAIN MENU ===\n");
    printf("1. Admin\n");
    printf("2. Pengguna\n");
    printf("3. Exit\n");
    printf("Pilihan : "); scanf("%d", &pilihan);
    
    switch (pilihan) {
        case 1:
            system("cls");
            loginAdmin();
            break;
        case 2:
            system("cls");
            User();
            break;
        case 3:
            printf("\nTerimakasih sudah menggunakan program ini!\n");
            return 0;
        default:
            printf("\nPilihan tidak valid\n");
        }
return 0;
}

void loginAdmin () {
    int kesempatan = 3;
    char nama_admin[100], password_admin[100];

    printf("\n=== LOGIN ADMIN ===\n");
    while(kesempatan > 0) {
        printf("Nama        : "); scanf("%s", nama_admin);
        printf("Password    : "); scanf("%s", password_admin);
        
        if(strcmp(nama_admin, "ADMIN") == 0 && strcmp(password_admin, "123") == 0) {
            printf("\nLogin Berhasil!\n");
            menuAdmin();
            return;
        } else {
            kesempatan--;
            printf("\nLogin Gagal. Sisa kesempatan %d lagi.\n", kesempatan); 
        }
    }
    printf("Kesempatan habis. Silahkan mengulangi kembali.");
}

void User() {
    int pilihan;

    printf("\n=== MENU PENGGUNA ===\n");
    printf("1. Login\n");
    printf("2. Registrasi\n");
    printf("Pilihan : "); scanf("%d", &pilihan);
    getchar();

    switch (pilihan) {
        case 1:
            loginPengguna();break;
        case 2:
            registrasi(); break;
        default:
            printf("\nPilihan tidak valid.\n");
    }
}

void loginPengguna() {
    char username[50], password[50], uname[50], pass[50];
    int ditemukan = 0;
    FILE *fp;

    printf("\n=== LOGIN ===\n");
    printf("Username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    fp = fopen("user.txt", "r");
    if (fp == NULL) {
        printf("Belum terdaftar. Silakan registrasi terlebih dahulu.\n");
        return;
    }

    while (fscanf(fp, "%s %s", uname, pass) != EOF) {
        if (strcmp(username, uname) == 0 && strcmp(password, pass) == 0) {
            ditemukan = 1;
            break;
        }
    }
    fclose(fp);

    if (ditemukan){
        printf("Login berhasil! Selamat datang, %s\n", username); menuPengguna();
    }
    else{
        printf("Username atau password salah.\n");
    }
}

void registrasi() {
    char username[50], password[50];
    FILE *fp;

    printf("\n=== REGISTRASI ===\n");
    printf("Masukkan username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;

    printf("Masukkan password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    fp = fopen("user.txt", "a");
    if (fp == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }
    fprintf(fp, "%s %s\n", username, password);
    fclose(fp);

    printf("Registrasi berhasil!\n");
    User();
}

void menuAdmin() {
    int pilihan;

    printf("\n=== MENU ADMIN ===\n");
    printf("1. Manajemen Barang\n");
    printf("2. Status Pesanan\n");
    printf("3. Feedback\n");
    printf("4. Menu Keuangan\n");
    printf("5. Keluar\n");
    printf("Pilihan : "); scanf("%d", &pilihan);

    switch (pilihan) {
        case 1:
            bacaDataDariFile();
            MenuBarang();
            break;
        case 2:
            statusPesanan();
            break;
        case 3:
            feedbackAdmin();
            break;
        case 4:
            menuKeuangan();
            break;
        case 5:
            main();
            break;
        default:
            printf("\nPilihan tidak valid!\n");
    }
}

void menuPengguna() {
    int pilihan;

    printf("\n=== MENU PENGGUNA ===\n");
    printf("1. Menu Pembelian Barang\n");
    printf("2. Menu Informasi Akun\n");
    printf("Pilihan : "); scanf("%d", &pilihan);

    switch (pilihan) {
        case 1:
             menuPembelian();
            break;
        case 2:
            menuInformasi();
            break;
        default:
            printf("\nPilihan tidak valid\n");
    }
}

void MenuBarang() {
    int pilihan;
    do {
        printf("\n=== Menu Barang ===\n");
        printf(" 1. Tambah barang\n 2. Lihat daftar barang\n 3. Hapus barang\n 4. Keluar\n");
        printf("Pilihan: ");
        if (scanf("%d", &pilihan) != 1) {
            printf("Pilihan tidak valid.\n");
            while(getchar() != '\n');
            continue;
        }
        switch (pilihan) {
            case 1: tambahbarang(); break;
            case 2: tampilkanbarang(); break;
            case 3: hapusbarang(); break;
            case 4: menuAdmin(); break;
            default: printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 4);
}

void bacaDataDariFile() {
    FILE *file = fopen("data_barang.dat", "rb");
    if (file == NULL) {
        jumlahbarang = 0;
        return;
    }
    jumlahbarang = fread(daftarbarang, sizeof(struct barang), MAX_BARANG, file);
    fclose(file);
}

void tambahbarang() {
    if (jumlahbarang >= MAX_BARANG) {
        printf("Daftar barang telah penuh\n");
        return;
    }

    getchar();
    printf("Nama barang:\n");
    scanf("%49[^\n]", daftarbarang[jumlahbarang].nama);
    getchar();

    printf("Kondisi barang:\n");
    scanf("%99[^\n]", daftarbarang[jumlahbarang].kondisi);
    getchar();

    printf("Harga barang:\n");
    if (scanf("%d", &daftarbarang[jumlahbarang].harga) != 1) {
        printf("Harga tidak valid\n");
        while(getchar() != '\n');
        return;
    }
    getchar();

    printf("Deskripsi:\n");
    scanf("%99[^\n]", daftarbarang[jumlahbarang].deskripsi);
    getchar();

    FILE *file = fopen("data_barang.dat", "ab");
    if (file == NULL) {
        printf("Gagal membuka file untuk menyimpan.\n");
        return;
    }
    fwrite(&daftarbarang[jumlahbarang], sizeof(struct barang), 1, file);
    fclose(file);

    jumlahbarang++;
    printf("Barang berhasil ditambahkan dan disimpan ke file!\n");
}

void tampilkanbarang() {
    FILE *file = fopen("data_barang.dat", "rb");
    if (file == NULL) {
        printf("Belum ada data tersimpan.\n");
        return;
    }

    struct barang temp;
    int id = 1;
    printf("\n=== Daftar Barang ===\n");
    while (fread(&temp, sizeof(struct barang), 1, file)) {
        printf("ID: %d\n", id++);
        printf("Nama: %s\n", temp.nama);
        printf("Kondisi: %s\n", temp.kondisi);
        printf("Harga: %d\n", temp.harga);
        printf("Deskripsi: %s\n\n", temp.deskripsi);
    }
    fclose(file);
}

void hapusbarang(){
    FILE *file;
    int id;

    file = fopen("data_barang.dat", "rb");
    if (file == NULL) {
        printf("Gagal membuka file untuk membaca.\n");
        return;
    }
    jumlahbarang = fread(daftarbarang, sizeof(struct barang), MAX_BARANG, file);
    fclose(file);

    if (jumlahbarang == 0) {
        printf("Tidak ada data barang.\n");
        return;
    }

    printf("Masukkan ID barang yang ingin dihapus: ");
    if (scanf("%d", &id) != 1 || id < 1 || id > jumlahbarang){
        printf("Input tidak valid\n");
        while(getchar() != '\n');
        return;
    }

    memmove(&daftarbarang[id-1], &daftarbarang[id], (jumlahbarang - id) * sizeof(struct barang));
    jumlahbarang--;

    file = fopen("data_barang.dat", "wb");
    if (file == NULL) {
        printf("Gagal membuka file untuk menulis.\n");
        return;
    }
    fwrite(daftarbarang, sizeof(struct barang), jumlahbarang, file);
    fclose(file);

    printf("Barang berhasil dihapus!\n");
}

void statusPesanan() {
    struct Pesanan daftar[100];
    int jumlah = 0;
    int pilih;

    do {
        tampilPesanan(daftar, jumlah);

        printf("\nMenu:\n");
        printf("1. Tambah Pesanan\n");
        printf("2. Hapus Pesanan\n");
        printf("0. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilih);

        switch (pilih) {
            case 1:
                jumlah = tambahPesanan(daftar, jumlah);
                break;
            case 2:
                jumlah = hapusPesanan(daftar, jumlah);
                break;
            case 0:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilih != 0);
}

int tampilPesanan(struct Pesanan daftar[], int jumlah) {
    printf("\n--- DAFTAR PESANAN ---\n");
    if (jumlah == 0) {
        printf("Belum ada pesanan.\n");
        return 0;
    }

    for (int i = 0; i < jumlah; i++) {
        printf("ID: %d | Barang: %s | Status: %s\n", daftar[i].id, daftar[i].nama, daftar[i].status);
    }

    return jumlah;
}

int tambahPesanan(struct Pesanan daftar[], int jumlah) {
    daftar[jumlah].id = jumlah + 1;
    printf("Nama Barang: ");
    scanf(" %[^\n]", daftar[jumlah].nama);
    printf("Status: ");
    scanf("%s", daftar[jumlah].status);
    return jumlah + 1;
}

int hapusPesanan(struct Pesanan daftar[], int jumlah) {
    int idHapus;
    printf("ID yang akan dihapus: ");
    scanf("%d", &idHapus);
    int ketemu = 0;

    for (int i = 0; i < jumlah; i++) {
        if (daftar[i].id == idHapus) {
            while (i < jumlah - 1) {
                daftar[i] = daftar[i + 1];
                i++;
            }
            jumlah--;
            ketemu = 1;
            break;
        }
    }

    if (!ketemu) {
        printf("ID tidak ditemukan.\n");
    } else {
        
        for (int i = 0; i < jumlah; i++) {
            daftar[i].id = i + 1;
        }
    }

    return jumlah;
}

void feedbackAdmin() {
    FILE *file_feedback = fopen("feedback.dat", "ab");
    if (file_feedback == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    strcpy(feedback.username, "userdummy");
    strcpy(feedback.komentar, "Mainannya bagus dan cepat sampai!");

    fwrite(&feedback, sizeof(feedback), 1, file_feedback);
    fclose(file_feedback);
    printf("Feedback dummy berhasil ditambahkan.\n");
}

void menuKeuangan() {
    int pilihan;

    printf("=================================\n");
    printf("   MENU KEUANGAN DBOMBOMSHOP\n");
    printf("=================================\n");
    printf("1. Total Pendapatan\n");
    printf("2. Histori Transaksi\n");
    printf("Masukkan pilihan Anda (1/2): ");
    scanf("%d", &pilihan);

    switch (pilihan) {
        case 1:
            totalPendapatan();
            break;
        case 2:
            historiTransaksi();
            break;
        default:
            printf(">> Pilihan tidak valid. Silakan coba lagi.\n");
    }
}

void totalPendapatan() {
    FILE *file;
    char status[20];
    int jumlah;
    int total = 0;

    file = fopen("transaksi.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file transaksi.\n");
        return;
    }

    while (fscanf(file, "%s %d", status, &jumlah) != EOF) {
        if (strcmp(status, "berhasil") == 0) {
            total += jumlah;
        }
    }

    printf("\n>> TOTAL PENDAPATAN <<\n");
    printf("Total pendapatan dari semua transaksi: Rp %d\n", total);

    fclose(file);
}

void historiTransaksi() {
    FILE *file;
    char status[20];
    int jumlah;
    int nomor = 1;

    file = fopen("transaksi.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file transaksi.\n");
        return;
    }

    printf("\n>> HISTORI TRANSAKSI <<\n");
    printf("No.\tStatus\t\tJumlah\n");
    printf("-------------------------------\n");
    while (fscanf(file, "%s %d", status, &jumlah) != EOF) {
        printf("%d\t%-10s\tRp %d\n", nomor, status, jumlah);
        nomor++;
    }

    fclose(file);
}

void menuPembelian() {

}

void menuInformasi() {
    int pilihan;

    printf("\n=== MENU INFORMASI AKUN ===\n");
    printf("1. Topup Saldo\n");
    printf("2. Lihat Saldo\n");
    printf("3. Membership\n");
    printf("4. Mengganti Password\n");
    printf("Pilihan : "); scanf("%d", &pilihan);

    switch (pilihan) {
        case 1:
            topupSaldo();
            break;
        case 2:
            lihatSaldo();
            break;
        case 3:
            membership();
            break;
        case 4:
            menggantiPass();
            break;
        default:
            printf("\nPilihan tidak valid!\n");
    }
}

int bacaUser(struct User *user) {
    FILE *fuser;
    fuser = fopen("user.dat", "rb");
    int hasil;

    if(!fuser) {
        user->member = 0;
        user->saldo = 0.0;
        return 0;
    }

    hasil = fread(user, sizeof(struct User), 1, fuser);
    fclose(fuser);
    return hasil;
}

int simpanUser(struct User *user) {
    FILE *fuser;
    fuser = fopen("user.dat", "wb");
    int hasil;

    if(!fuser) {
        printf("\nGagal membuka file!\n");
        return 0;
    }

    hasil = fwrite(user, sizeof(struct User), 1, fuser);
    fclose(fuser);
    return hasil;
}

void topupSaldo() {
    struct User user;
    float topup;

    if(!bacaUser(&user)) {
        printf("\nGagal membuka file!\n");
        return;
    }

    printf("\n=== TOP-UP SALDO ===\n");
    printf("Input nominal saldo : "); scanf("%f", &topup);

    if(topup < 0) {
        printf("Gagal Top-Up. Tidak boleh angka negatif.\n");
    } else {
        user.saldo += topup;
        if(simpanUser(&user)) {
            printf("Top-up Berhasil! Saldo sekarang : %.2f\n", user.saldo);
        } else {
            printf("Top-up Gagal!\n");
        }
    }
}

void lihatSaldo() {
    struct User user;

    if(!bacaUser(&user)) {
        printf("\nGagal membuka file!\n");
    }

    printf("\n=== LIHAT SALDO ===\n");
    printf("Saldo sekarang : %.2f", user.saldo);
}

void membership() {
    struct User user;

    if (!bacaUser(&user)) {
        printf("\nGagal membuka file!\n");
    }

    printf("\n=== MEMBERSHIP ===\n");
    if (user.member == 1) {
        printf("\nAnda sudah menjadi Member!\n");
    } else {
        printf("\nHARGA MEMBERSHIP : Rp. 100.000,00\n");
        if (user.saldo >= 100000) {
            user.saldo -= 100000;
            user.member = 1;
            
            if (simpanUser(&user)) {
                printf("\nAnda berhasil menjadi Member!\n");
                printf("Saldo tersisa: %.2f\n", user.saldo);
            } else {
                printf("Membership Gagal!\n");
            }
        } else {
            printf("\nSaldo tidak cukup untuk menjadi Member.\n");
            printf("Saldo anda: %.2f\n", user.saldo);
        }
    }
}

void menggantiPass() {
    struct User user;  
    char password[100], pass[100], pass_baru[100];

    if(!bacaUser(&user)) {
        printf("\nGagal membuka file!\n");
    }

    printf("Masukkan password lama : "); scanf("%s", pass);

    if(strcmp(user.pass, pass) == 0) {
        printf("Masukkan password baru : "); scanf("%s", pass_baru);
        strcpy(user.pass, pass_baru);
        if(simpanUser(&user)) {
            printf("Password berhasil diubah!\n");
        } else {
            printf("Gagal simpan file!\n");
        }
    } else {
        printf("Password lama salah!\n");
    }
}
