#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct barang{
    int id;
    char nama[50];
	double harga;
} barang;

typedef struct itemKeranjang {
    int id;
    barang barang;
    int jumlah;
} itemKeranjang;

typedef struct node node;
struct node {
    barang data;
    node *next;
	node *prev;
};

// Stack Keranjang
#define MAX 2
typedef struct Keranjang {
    int top;
    itemKeranjang item[MAX];
} Keranjang;

typedef struct order {
    int id;
    char nama[50];
    Keranjang *keranjang;
} order;

typedef struct {
    order item[MAX];
    int count;
    int rear;
    int front;
} Queue;

Queue* initQueue() {
    Queue *q = malloc(sizeof(Queue));
    q->count = 0;
    q->front = 0;
    q->rear = 0;
    return q;
}

int isAntrianFull(Queue *q) {
    return q->count == MAX;
}

void enqueue(Queue *q, order pesanan) {
    if (isAntrianFull(q)) {
        printf("Queue penuh, tidak dapat melakukan enqueue\n");
        return;
    }
    q->item[q->rear] = pesanan;
    q->rear = (q->rear + 1) % MAX;
    q->count++;
}

order dequeue(Queue *q) {
    order temp;
    if (isAntrianEmpty(q)) {
        printf("Queue kosong, tidak dapat melakukan dequeue\n");
        return;
    }
    temp = q->item[q->front];
    q->front = (q->front+1) % MAX;
    q->count--;
    return temp;
}

int isAntrianEmpty(Queue *q) {
    return q->count == 0;
}

void listAntrian(Queue *q) {
    if (isAntrianEmpty(q)) {
        printf("Queue kosong, tidak ada yang dapat diprint\n");
        return;
    }
    int i = q->front;
    int jumlah = q->count;
    while (jumlah != 0) {
        printf("%d ", q->item[i]);
        i = (i + 1) % MAX;
        jumlah--;
    }
}

node *head = NULL;
node *tail = NULL;
node *temp = NULL;

int id_inc=1;
int id_keranjang_inc=1;
int id_order_inc=1;

void fillDataBarang() {
    barang listBarang[4] = {
        {id_inc, "Kopi Kapal Aapi", 3500},
        {++id_inc, "Minyak Bimoli 2L", 15000},
        {++id_inc, "Gula Aren 2kg", 30000},
        {++id_inc, "Pepsodent 150gr", 12000}
    };
    int i;
    for (i = 0; i < 4; i++) {
        barang cur = listBarang[i];
        node *baru = (node *)malloc(sizeof(node));
        baru->data.id = cur.id;
        strcpy(baru->data.nama, cur.nama);
        baru->data.harga = cur.harga;
        baru->next = NULL;
        baru->prev = tail;
        tail->next = baru;
        tail = baru;
    }
}

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
    fillDataBarang();

    // Inisialisasi Data Antrian
    Queue *daftarPesanan = initQueue();

    menu:
	printf("====================================\n");
	printf("       MENU UTAMA\n");
	printf("====================================\n");
	printf("1. Daftar Barang\n");
	printf("2. Pemesanan Barang\n");
	printf("3. Daftar Pesanan\n");
	printf("q/Q. Keluar\n");
	printf("\nMasukkan Pilihan Anda : ");
	char pilihan = getche();

	switch(pilihan)
	{
		case '1':
			daftarBarang();
			goto menu;
            break;

        case '2':
        	pemesananBarang(daftarPesanan);
        	goto menu;

		case '3':
			tampilkanDaftarPesanan(daftarPesanan);
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
        printf("4. Cari Barang\n");
        printf("q/Q. Kembali\n\n");
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

            case '4':
                cari();
                break;

            case 'q':
            case 'Q':
                exit = true;
                break;

            default:
                aksiNotFound();
                break;
        }
   	}

   	system("cls");
}

Keranjang* createKeranjang() {
    Keranjang *stack = malloc(sizeof(Keranjang));
    stack->top = -1;
    return stack;
}

int isKeranjangFull(Keranjang *s) {
    return s->top == MAX - 1;
}

int isKeranjangEmpty(Keranjang *s) {
    return s->top == -1;
}

void push(Keranjang *s, itemKeranjang item) {
    if (isKeranjangFull(s)) {
        printf("Stack penuh, data tidak dapat disimpan\n");
        return;
    }
    // Push item ke array, sekalian increment top
    s->item[++s->top] = item;
}

void pop(Keranjang *s) {
    if (isKeranjangEmpty(s)) {
        printf("Stack kosong, tidak ada yang bisa di-pop\n");
        return;
    }
    // Kurangi Top
    s->top--;
}

void pemesananBarang(Queue *daftarPesanan)
{
    //node *ptr;
    order *pesanan = malloc(sizeof(order));
    pesanan->id = id_order_inc;
    pesanan->keranjang = createKeranjang();
    id_order_inc++;

   	bool exit = false;
   	while (!exit) {
        system("cls");
        printf("Aksi :\n");
        printf("1. Tambah Isi Keranjang\n");
        printf("2. Ubah Isi Keranjang\n");
        printf("3. Kurangi Isi Keranjang\n");
        printf("4. Konfirmasi Pemesanan\n");
        printf("q/Q. Kembali\n\n");
        // Tampilkan isi Keranjang
        printf("==============================================\n");
        printf("	  ISI KERANJANG BARANG\n");
        printf("==============================================\n");
        double grandTotal=0;
        for (int i=0; i < pesanan->keranjang->top + 1; i++) {
            itemKeranjang b = pesanan->keranjang->item[i];
            printf("ID Detail\t: %d\n", b.id);
            printf("Nama Barang\t: %s\n", b.barang.nama);
            double total = b.barang.harga * b.jumlah;
            printf("Total\t\t: %.2f, (%.2f x %d)\n", total, b.barang.harga, b.jumlah);
            printf("==============================================\n");
            grandTotal += total;
        }
        printf("Grand Total : %.2f", grandTotal);
        printf("\n");
        // Tentukan Pilihan
        printf("Aksi : "); char input = getche();
        switch(input) {
            case '1':
                tambah_keranjang(pesanan->keranjang);
                break;

            case '2':
                ubah_keranjang(pesanan->keranjang);
                break;

            case '3':
                hapus_keranjang(pesanan->keranjang);
                break;

            case '4':
                konfirmasi_pesanan(daftarPesanan, pesanan);
                exit = true;
                // konfirmasi_pesanan(pesanan);
                break;

            case 'q':
            case 'Q':
                if (!isKeranjangEmpty(pesanan->keranjang)) {
                	// Keranjang sudah keisi, konfirmasi dulu
                    printf("\n\nData pesanan akan hilang sebelum dikonfirmasi terlebih dahulu.\n");
                    printf("Apakah anda yakin ingin kembali ?.\n");
                    printf("1. Ya\n");
                    printf("2. Tidak\n");
                    char pilihan = getche();
			        switch(pilihan) {
			            case '1':
			            	exit = true;
			                break;

			            case '2':
			            default:
			                break;
			        }
                } else {
                	// Keranjang kosong, langsung exit gakpapa
	                exit = true;
                }
                break;

            default:
                aksiNotFound();
                break;
        }
   	}
   	system("cls");
}

double getSubtotalPesanan(order pesanan) {
    Keranjang *keranjang = pesanan.keranjang;
    double subtotal=0;
    for (int i=0; i < keranjang->top + 1; i++) {
        subtotal += keranjang->item[i].barang.harga * keranjang->item[i].jumlah;
    }
    return subtotal;
}

void tampilkanDaftarPesanan(Queue *daftarPesanan) {
    if (isAntrianEmpty(daftarPesanan)) {
        printf("Pesanan kosong, tidak ada yang dapat ditampilkan.\n");
        getch();
        return;
    }
    bool exit = false;
   	while (!exit) {
        system("cls");
        printf("Aksi :\n");
        printf("1. Selesai Pesanan\n");
        printf("q/Q. Kembali\n\n");
        // Tampilkan isi Keranjang
        printf("==============================================\n");
        printf("	  DAFTAR PESANAN BARANG\n");
        printf("==============================================\n");
        double grandTotal=0;
        int i = daftarPesanan->front;
        int jumlah = daftarPesanan->count;
        while (jumlah != 0) {
            order cur = daftarPesanan->item[i];
            double subtotal = getSubtotalPesanan(cur);
            printf("ID Pesanan\t: %d\n", cur.id);
            printf("Nama Pemesan\t: %s\n", cur.nama);
            printf("Jumlah Barang\t: %d\n", cur.keranjang->top+1);
            printf("Subtotal\t: %.2f\n", subtotal);
            printf("==============================================\n");
            i = (i + 1) % MAX;
            jumlah--;
            grandTotal += subtotal;
        }
        printf("Grand Total : %.2f", grandTotal);
        printf("\n");
        // Tentukan Pilihan
        printf("Aksi : "); char input = getche();
        switch(input) {
            case '1':
                //tambah_keranjang(pesanan->keranjang);
                break;

            case 'q':
            case 'Q':
                exit = true;
                break;

            default:
                aksiNotFound();
                break;
        }
   	}
   	system("cls");
}

void tambah_keranjang(Keranjang *keranjang) {
    // Cek apakah sudah full?
    if (isKeranjangFull(keranjang)) {
        printf("\n\nKeranjang penuh, harap kurangi keranjang terlebih dahulu.");
        getch();
        return;
    }
    // Loop Tambah Keranjang
    bool selesaiTambah = false;
    while (!selesaiTambah) {
        // Cek apakah sudah full?
        if (isKeranjangFull(keranjang)) {
            printf("\nKeranjang sudah penuh, harap kurangi keranjang jika ingin menambah yang lain.");
            getch();
            return;
        }
        system("cls");
        // Menampilkan Data Barang
        printf("====================================\n");
        printf("	  DATA BARANG\n");
        printf("====================================\n");
        node *ptr = head;
        while (ptr != NULL) {
            printf("ID Barang\t: %d\n", ptr->data.id);
            printf("Nama Barang\t: %s\n", ptr->data.nama);
            printf("Harga Barang\t: %.2f\n", ptr->data.harga);
            printf("====================================\n");
            ptr = ptr->next;
        }
        // Pilih Barang
        printf("Inputkan ID Barang : ");
        int id_cari;
        scanf("%d", &id_cari);
        node *cari = head;
        while(cari != NULL && cari->data.id != id_cari)
        {
            cari = cari->next;
        }
        // Jika data tidak ditemukan
        if (cari == NULL) {
            printf("\nMaaf, data tidak ditemukan!\n");
            getch();
            // continue;
        } else {
            // Cari apakah sudah ada di keranjang
            bool exist = false;
            for (int i =0; i < keranjang->top+1; i++) {
                itemKeranjang item = keranjang->item[i];
                if (item.barang.id == cari->data.id) {
                    // Sudah ada di keranjang
                    exist = true;
                    break;
                }
            }
            if (exist) {
                printf("Barang sudah ada di keranjang, silakan pilih ubah barang atau pilih barang yang lain.\n\n");
            } else {
                int jumlah;
                printf("Inputkan Jumlah : "); scanf("%d", &jumlah);
                // Tambahkan data ke Stack
                itemKeranjang baru;
                baru.id = id_keranjang_inc;
                baru.barang = cari->data;
                baru.jumlah = jumlah;
                push(keranjang, baru);
                id_keranjang_inc++;
            }
        }

        printf("Apakah anda ingin menambahkan barang lagi?\n");
        printf("1. Ya\n");
        printf("2. Tidak\n");
        char pilihan = getche();
        switch(pilihan) {
            case '1':
                break;

            case '2':
            default:
                selesaiTambah = true;
                break;
        }
    }
}

void ubah_keranjang(Keranjang *keranjang){
	system("cls");
	//Pilih Barang
	int id_cari;
	printf("====================================\n");
    printf("		UBAH KERANJANG\n");
    printf("====================================\n");
	printf("Inputkan ID Barang : "); scanf("%d", &id_cari);
	// Cari apakah sudah ada di keranjang
	int i;
	bool exist = false;
    for (i = 0; i < keranjang->top+1; i++) {
        itemKeranjang item = keranjang->item[i];
        if (item.id == id_cari) {
            // Sudah ada di keranjang
            exist = true;
            break;
        }
    }
    if (exist) {
        //ubah jumlah barang
		int jumlah;
        printf("Inputkan Jumlah : "); scanf("%d", &jumlah);
        // Tambahkan data ke Stack
        itemKeranjang item = keranjang->item[i];
        item.jumlah = jumlah;
        keranjang->item[i] = item;
        printf ("\nPerubahan Sudah Disimpan !");
        getch();
    } else {
        printf("Data tidak ditemukan!");
        getch();
    }
}

void hapus_keranjang(Keranjang *keranjang){
    if (isKeranjangEmpty(keranjang)) {
        printf("\n\nKeranjang masih kosong.");
        getch();
        return;
    }
	printf("\nApakah anda yakin ingin mengurangi isi keranjang ini?\n");
    printf("1. Ya\n");
    printf("2. Tidak\n");
    char pilihan = getche();
    switch(pilihan) {
        case '1':
            pop(keranjang);
            printf("\n\nIsi keranjang berhasil dikurangi.");
            getch();
            break;

        case '2':
        default:
            break;
    };
}

void konfirmasi_pesanan(Queue *daftarPesanan, order *pesanan) {
    char nama[50];
    printf("\n\n");
    printf("Nama Pemesan : "); fflush(stdin); gets(pesanan->nama);
    enqueue(daftarPesanan, *pesanan);
    printf("Pesanan berhasil dikonfirmasi.");
    getch();
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

void cari()
{
    bool exit = false;
    while (!exit) {
        system("cls");
        char keyword[30];

        printf("====================================\n");
        printf("	CARI DATA BARANG\n");
        printf("====================================\n");
        printf("Masukkan kata kunci barang yang ingin dicari : ");
        fflush(stdin); gets(keyword);

        //printf("%s", keyword);
        int i = 0;
        barang hasilCari[100];
        node *cari = head;
        // Lanjut sampek tail
        while(cari != NULL)
        {
            // Apakah nama mengandung keyword yg dicari?
            if(strstr(cari->data.nama, keyword) != NULL) {
                hasilCari[i] = cari->data;
                i++;
            }
            cari = cari->next;
        }
        // Jika data tidak ditemukan
        if (i == 0) {
            printf("\nMaaf, data tidak ditemukan!\n");
        } else {
            // Tampilkan hasil pencarian
            printf("Data Berhasil Ditemukan\n");
            for (int j = 0; j < i; j++) {
                barang b = hasilCari[j];
                printf("ID Barang\t: %d\n", b.id);
                printf("Nama Barang\t: %s\n", b.nama);
                printf("Harga Barang\t: %.2f\n", b.harga);
                printf("====================================\n");
            }
        }
        printf("Apakah anda ingin mencari lagi?\n");
        printf("1. Ya\n");
        printf("2. Tidak\n");
        char pilihan = getche();
        switch(pilihan) {
            case '1':
                break;

            case '2':
            default:
                exit = true;
                break;
        }
    }
    system("cls");
}

void aksiNotFound() {
    printf("\nAksi yang anda inputkan tidak valid.");
    getch();
    system("cls");
}
