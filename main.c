#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct barang{
    int id;
    char nama[50];
	double harga;
} barang;

typedef struct node node;
struct node {
    barang data;
    node *next;
	node *prev;
};

node *head = NULL;
node *tail = NULL;
node *temp = NULL;

int id_inc=1;

int main()
{
    // Inisialisasi data awal
    node *baru = (node *)malloc(sizeof(node));
    baru->next=NULL; baru->prev=NULL;
	baru->data.id = id_inc;
	strcpy(baru->data.nama, "Gulaku 1kg");
	baru->data.harga = 16500;
	head = tail = baru;
	id_inc++;

    menu:
	printf("====================================\n");
	printf("       MENU UTAMA\n");
	printf("====================================\n");
	printf("1. Daftar Barang\n");
	printf("Q. Keluar\n");
	printf("\nMasukkan Pilihan Anda : ");
	char pilihan = getche();

	switch(pilihan)
	{
		case '1':
			daftarBarang();
			goto menu;
            break;
		case '2':
			//createdata_sisipakhir();
			goto menu;
            break;

        case 'q':
        case 'Q':
            break;
		default:
            return 0;
	}
    return 0;
}

void daftarBarang()
{
    node *ptr;
    system("cls");
	if(head==NULL){
   		printf(" Tidak Ada Data Barang \n");
   		getch();
   		system("cls");
   		return;
   	}
   	bool exit = false;
   	while (!exit) {
        printf("Aksi :\n");
        printf("1. Tambah Barang\n");
        printf("2. Ubah Barang\n");
        printf("3. Hapus Barang\n");
        printf("Q. Kembali\n\n");
        printf("====================================\n");
        printf("	  DATA BARANG\n");
        printf("====================================\n");
        ptr = head;
        while (ptr != NULL) {
             printf("ID Barang\t: %d\n", ptr->data.id);
             printf("Nama Barang\t: %s\n", ptr->data.nama);
             printf("Harga Barang\t: %.2f\n", ptr->data.harga);
             printf("====================================\n");
             ptr = ptr->next;
        }
        printf("Aksi : "); char input = getche();
        switch(input) {
            case '1':
                tambah();
                break;

            case '2':
                ubah();
                break;

            case '3':
                hapus();
                break;

            case 'q':
            case 'Q':
                exit = true;
                break;
        }
   	}

   	system("cls");
}

void tambah()
{
	system("cls");
    float harga;
    char nama[30];
    printf("====================================\n");
    printf("	MEMBUAT DATA BARANG\n");
    printf("====================================\n");

    printf("Masukkan Nama Barang\t: ");
    fflush(stdin);
    gets(nama);

    printf("Masukkan Harga Barang\t: ");
    scanf("%f",&harga);

    node *baru = (node *)malloc(sizeof(node));
    baru->data.id = id_inc;
    strcpy(baru->data.nama, nama);
    baru->data.harga = harga;
    baru->next = NULL;
    baru->prev = tail;
    tail->next = baru;
    tail = baru;
    id_inc++;

	system("cls");
}

void ubah()
{
   	system("cls");
   	int id_cari;

	printf("====================================\n");
    printf("	UBAH DATA BARANG\n");
    printf("====================================\n");
	printf("Masukkan ID barang yang ingin diubah : ");
	scanf("%d", &id_cari);

	node *ubah = head;
	while(ubah != NULL && ubah->data.id != id_cari)
	{
		ubah = ubah->next;
	}
    // Jika data tidak ditemukan
    if (ubah == NULL) {
        printf("\nMaaf, data tidak ditemukan!");
        getch();
        system("cls");
        return;
    }

	float harga;
    char nama[30];
    printf("Masukkan Nama Barang\t: ");
    fflush(stdin);
    gets(nama);

    printf("Masukkan Harga Barang\t: ");
    scanf("%f",&harga);

    strcpy(ubah->data.nama, nama);
    ubah->data.harga = harga;
    // Ubah data
   	printf("\nData berhasil diubah!");

	getch();
	system("cls");
}

void hapus()
{
   	system("cls");
   	int id_cari;

	printf("====================================\n");
    printf("	HAPUS DATA BARANG\n");
    printf("====================================\n");
	printf("Masukkan ID barang yang ingin dihapus : ");
	scanf("%d", &id_cari);

	node *hapus = head;
	while(hapus != NULL && hapus->data.id != id_cari)
	{
		hapus = hapus->next;
	}
    // Jika data tidak ditemukan
    if (hapus == NULL) {
        printf("\nMaaf, data tidak ditemukan!");
        getch();
        system("cls");
        return;
    } else if (hapus->prev == NULL && hapus->next == NULL) {
        printf("\nMaaf, ini adalah data terakhir, tidak bisa dihapus!");
        getch();
        system("cls");
        return;
    }
    // Cek apakah head / tail / tengah
	if (hapus->prev == NULL) {
        // Hapus Head
        head = hapus->next;
        head->prev = NULL;
        free(hapus);
    } else if (hapus->next == NULL) {
        // Hapus tail
        tail = hapus->prev;
        tail->next = NULL;
        free(hapus);
    } else {
        // Hapus pertengahan
        hapus->prev->next = hapus->next;
        hapus->next->prev = hapus->prev;
        free(hapus);
    }
   	printf("\nData berhasil dihapus!");

	getch();
	system("cls");
}
