#include <stdio.h>
#include <string.h>

void loginAdmin ();
void User();
void loginPengguna(); // X
void registrasi(); // X
void menuAdmin();
void manajemenBarang(); // X


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
        loginAdmin();
        break;
        case 2:
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

    switch (pilihan) {
        case 1:
            // loginPengguna();
        case 2:
            // registrasi(); 
        default:
            printf("\nPilihan tidak valid.\n");
    }
}

void menuAdmin() {
    int pilihan;

    printf("\n=== MENU ADMIN ===\n");
    printf("1. Manajemen Barang\n");
    printf("2. Status Pesanan\n");
    printf("3. Feedback\n");
    printf("4. Menu Keuangan\n");
    printf("Pilihan : "); scanf("%d", &pilihan);

    switch (pilihan) {
        case 1:
            // manajemenBarang();
            break;
        case 2:
            // statusPesanan();
            break;
        case 3:
            // feedback();
            break;
        case 4:
            // menuKeuangan();
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
            // menuPembelian();
            break;
        case 2:
            // menuInformasi();
            break;
        default:
            printf("\nPilihan tidak valid\n");
    }
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

void topupSaldo() {
    FILE *ftopup;
    ftopup = fopen("data_saldo.txt", "r+");
    float topup, saldo;

    if(!ftopup) {
        printf("\nGagal membuka file!\n");
        return;
    }

    printf("\n=== TOP-UP SALDO ===\n");
    printf("Input nominal saldo : "); scanf("%f", &topup);

    if(topup < 0) {
        printf("Gagal Top-Up. Tidak boleh angka negatif.\n");
    } else {
        saldo += topup;
        rewind(ftopup);
        fprintf(ftopup, "%.2f", saldo);
        printf("Top-up Berhasil! Saldo sekarang : %.2f\n", saldo);
    }
    fclose(ftopup);
}

void lihatSaldo() {
    FILE *flihat;
    flihat = fopen("data_saldo.txt", "r");
    float saldo;

    if(!flihat) {
        printf("\nGagal membuka file!\n");
        return;
    }

    printf("\n=== LIHAT SALDO ===\n");
    fscanf(flihat, "%.2f", &saldo);
    printf("Saldo sekarang : %.2f", saldo);
    fclose(flihat);
}

void membership() {
    FILE *fsaldo, *fmember;
    fsaldo = fopen("data_saldo.txt", "r+");
    fmember = fopen("data_member.txt", "r+");
    int status;
    float saldo;

    if(!fsaldo || !fmember) {
        printf("\nGagal membuka file!\n");
        return;
    }

    printf("\n=== MEMBERSHIP ===\n");
    fscanf(fmember, "%d", &status);
    fscanf(fsaldo, "%.2f", &saldo);

    if(status == 1) {
        printf("\nAnda sudah menjadi Member!\n");
    } else {
        printf("\nHARGA MEMBERSHIP : Rp. 100.000,00\n");
        if (saldo >= 100000) {
            saldo -= 100000;
            rewind(fsaldo);
            rewind(fmember);
            fprintf(fsaldo, "%.2f", saldo);
            fprintf(fmember, "1");
            printf("\nAnda berhasil menjadi Member!\n");
        } else {
            printf("\nSaldo tidak cukup untuk menjadi Member.\n");
        }
    }
    fclose(fsaldo);
    fclose(fmember);
}

void menggantiPass() {
    FILE *fpass;
    fpass = fopen("password.txt", "r+");
    char password[100], pass[100], pass_baru[100];

    fscanf(fpass, "%s", password);
    printf("Masukkan password lama : "); scanf("%s", pass);

    if(strcmp(password, pass) == 0) {
        printf("Masukkan password baru : "); scanf("%s", pass_baru);
        rewind(fpass);
        fprintf(fpass, "%s", pass_baru);
        printf("Password berhasil diubah!\n");
    } else {
        printf("Password lama salah!\n");
    }
    fclose(fpass);
}
