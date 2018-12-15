#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 100 //panjang maksimal string

//komponen kartu
struct kartu
{
	char tanggal_pinjam[MAX_LEN];
	char tanggal_balik[MAX_LEN];
	int status;
};
typedef struct kartu Kartu; // typedef membentuk suatu variabel baru dengan kumpulan berbagai variabel dari type yang berbeda-beda

//komponen buku
struct buku
{
	Kartu card[MAX_LEN]; //array of kartu
	char judul_buku[MAX_LEN];
	char pengarang[MAX_LEN];
	char penerbit[MAX_LEN];
	int tahun;
	int stock;
	int id_buku;
};
typedef struct buku Buku; // typedef membentuk suatu variabel baru dengan kumpulan berbagai variabel dari type yang berbeda-beda

//komponen linked-list
struct node
{
	Buku x;
	struct node *next; 
};
typedef struct node Node;


void printHeader();
void defaultStock();
void adminSession();
void guestSession();
Node *head;

int main()
{
	int user;
	
	printHeader(); //header
	defaultStock(); //mengisi linked-list dengan stock awal
	
	//select session
	scanf("%d", &user);
	system("cls");
	if(user==1) adminSession();
	else if(user==2) guestSession();
	else printf("Error, pilihan tidak tersedia, silakan cek kembali\n");
	return 0;
}


/////////////////////////print function/////////////////////////////////
void printHeader()
{
		system("Color F3");
	printf("\n\t\t   Proyek Akhir   \n");
    printf("  	Gilang Ladisadewa  &  Evitabasa\n");
    printf("\t\tTEKNIK ELEKTRO\n");
    getch(); 
	printf("\n\n\nMenu Peminjaman Buku\n");
	printf("                                      \n");
	printf("pilih user :\n");
	printf("1. Administrator\n");
	printf("2. Guest\n");
	printf("Login Sebagai : ");
}
void setcolor(unsigned short color);
void printAdminMenu()
{
	printf("\n\n         MENU         \n");
	printf("=========================\n");
	printf("1.Lihat Detail Buku\n");
	printf("2.Pengembalian Buku\n");
	printf("3.Peminjaman Buku\n");
	printf("4.Tambah Data Buku\n");
	printf("5.Hapus Data Buku\n");
	printf("6.Cetak Daftar Buku\n");
	printf("7.Keluar\n");
	printf("Pilihan: ");
}

void printGuestMenu()
{
	printf("\n\n++++++++++MENU+++++++++++\n");
	printf("=========================\n");
	printf("1.Lihat Detail Buku\n");
	printf("2.Cetak Daftar Buku\n");
	printf("3.Keluar\n");
	printf("Pilihan: ");
}

/////////////////////////fungsi linked-list/////////////////////////////
void defaultStock()
{
	Node *reference; // linked list dengan pointer reference
	int i;
	
	//buku 1
	head = (Node *) malloc(sizeof(Node)); //alokasi memory untuk head
	strcpy(head->x.judul_buku, "Electrical Book"); // menyalin head dgn variabel judul buku
	strcpy(head->x.pengarang, "Evitabasa");
	strcpy(head->x.penerbit, "Universindo");
	head->x.tahun =		2016; //mengisi struct head dgn akses variabel tahun pd record x dgn data 2015
	head->x.stock =		10;
	head->x.id_buku = 1;
	for(i=0; i<head->x.stock; i++)
		head->x.card[i].status = 1; // banyak buku sesuai inputan stok
	
	//buku 2
	reference = head; //reference dipointing ke head
	reference->next = (Node *) malloc(sizeof(Node));//tambah node baru di akhir list
	reference = reference->next; //reference dipointing ke node baru
	reference->next = 0;
	strcpy(reference->x.judul_buku, "Mechanic Book");
	strcpy(reference->x.pengarang, "Gilang L");
	strcpy(reference->x.penerbit, "Universindo");
	reference->x.tahun = 1996;
	reference->x.stock = 10;	
	reference->x.id_buku = 2;
	for(i=0; i<reference->x.stock; i++)
		reference->x.card[i].status = 1;	
	

}

Node *searchBefore(Node *current) // untuk proses hapus
{
	Node *before = head;
	
	while(before->next != current && before != NULL)
	{
		before = before->next;
	}
	return before;
}

Node *searchAfter(Node *current) // untuk proses hapus
{
	Node *after = head;
	
	if(after==current) return after->next;
	else
	{
		while(after->next != current && after != NULL)
		{
			after = after->next;
		}
		if(after!=NULL) after = current->next;
		return after;
	}
}

Node *searchBuku(int id_buku) 
{
	Node *reference = head;

	while(reference != NULL && reference->x.id_buku != id_buku)
		reference = reference->next;
	return reference;
}

Node *sortingBuku(int id_buku)
{
	Node *reference, *before, *insert;
	insert = (Node *) malloc(sizeof(Node));
	insert->next = NULL;
	if(head!=NULL)
	{
		if(id_buku < head->x.id_buku) //insert in first node (head)
		{
			insert->next = head;
			head = insert;
		}
		else
		{
			reference = head;
			before = head;
			
			 
				reference->next = insert; //insert in last node
		}
	}
	else head = insert;
	return insert;
}

/////////////////////////fungsi pada menu///////////////////////////////
int getStockBuku(Node *current)
{
	int i=0;
	int current_stock=0;
	
	while(current->x.card[i].status!=0) 
	{
		if(current->x.card[i].status==1) current_stock++;
		i++;
	}
	return current_stock;
}

void printBuku(Node *reference)
{
	printf("%d\t", reference->x.id_buku);
	printf("%s\t", reference->x.judul_buku);
	printf("%s\t", reference->x.pengarang);
	printf("%s\t", reference->x.penerbit);
	printf("%d\t\t",reference->x.tahun);
	printf("%d\n", getStockBuku(reference));
}

void printDetail(Node *detail)
{
	int i=0;
	printf("\n\nID\tStatus\t\tJudul Buku\t\tTanggal Pinjam\tTanggal Kembali\n");
	while(detail->x.card[i].status!=0) // buku masih utuh sejumlah stok
	{
		if(detail->x.card[i].status!=-1) 
		{
			printf("%d\t", i);
			if(detail->x.card[i].status == 2) printf("Dipinjam\t");
			else if(detail->x.card[i].status == 1) printf("Available\t");
			printf("%s_%d\t", detail->x.judul_buku, i);
			printf("%s\t", detail->x.card[i].tanggal_pinjam);
			printf("%s\n", detail->x.card[i].tanggal_balik);
			i++;
		}
	}

}

void cetakListBuku() //void untuk mencetak daftar buku
{
	Node *reference;
	reference = head; //reference sama dengan head node selajutnya
	
	printf("\n\nID Buku\tJudul Buku\tNama Pengarang\tPenerbit\tTahun\t\tStock\n");
	if (reference != 0) 
	{ 
		while (reference->next != 0) // Ketika reference dngn pointer next tidak sama dengan 0
		{
			printBuku(reference);
			reference = reference->next;
		}
		printBuku(reference); //ke void print buku dgn passing variabel reference
	}
}

void detailBuku()
{
	Node *detail;
	int id_buku;
	
	printf("Masukkan ID Buku (Ketik 0 untuk melihat ID Buku) : ");
	scanf("%d", &id_buku);
	while(id_buku==0)
	{
		cetakListBuku();
		printf("\nMasukkan ID Buku (Ketik 0 untuk melihat ID Buku) : ");
		scanf("%d", &id_buku);
	}
	detail = searchBuku(id_buku); //menampilkan list buku
	if(detail!=NULL) // sudah mecapai akhir node, id tidak ditemukan
		printDetail(detail);
	else printf("\nID Buku tidak ditemukan, silakan cek kembali!");
}

void pinjamBuku()
{
	Node *current;
	char tanggal_pinjam[MAX_LEN];
	char tanggal_balik[MAX_LEN];
	int id_buku, current_stock, i=0;
	
	printf("Masukkan ID Buku yang akan dipinjam (Ketik 0 untuk melihat ID Buku) : ");
	scanf("%d", &id_buku);
	while(id_buku==0)
	{
		cetakListBuku();
		printf("\nMasukkan ID Buku yang akan dipinjam (Ketik 0 untuk melihat ID Buku) : ");
		scanf("%d", &id_buku);
	}
	current = searchBuku(id_buku);
	current_stock = getStockBuku(current);
	
	if(current!=NULL && current_stock!=0)
	{
		while(current->x.card[i].status!=0) 
		{
			if(current->x.card[i].status==1) 
				{
					getchar(); // menunggu input karakter
					printf("Tanggal Pinjam (format: dd-mm-yy) : ");	
					fgets(tanggal_pinjam,100,stdin); // fungsi seperti scanf
					tanggal_pinjam[strlen(tanggal_pinjam) - 1] = '\0'; // \0 untuk konstan karakter
					printf("Tanggal Kembali (format: dd-mm-yy) : ");	
					fgets(tanggal_balik,100,stdin);
					tanggal_balik[strlen(tanggal_balik) - 1] = '\0';
					strcpy(current->x.card[i].tanggal_pinjam, tanggal_pinjam);
					strcpy(current->x.card[i].tanggal_balik, tanggal_pinjam);
					current->x.card[i].status=2;
					break;
				}
			i++;
		}
	}
	else if(current_stock==0) printf("\nMaaf, saat ini stock sedang kosong");
	else printf("\nID Buku tidak ditemukan, silakan cek kembali!");
}

void kembaliBuku()
{
	Node *current;
	int id_buku, id_peminjam;
	
	printf("Masukkan ID Buku yang akan dikembalikan(Ketik 0 untuk melihat ID Buku) : ");
	scanf("%d", &id_buku);
	while(id_buku==0)
	{
		cetakListBuku();
		printf("\nMasukkan ID Buku yang akan dikembalikan (Ketik 0 untuk melihat ID Buku) : ");
		scanf("%d", &id_buku);
	}
	
	current = searchBuku(id_buku);
	
	if(current!=NULL)
	{
		printf("Masukkan ID Detail (Ketik -1 untuk melihat Detail Buku) : ");
		scanf("%d", &id_peminjam);
		while(id_peminjam==-1)// -1 untuk menampilkan detail buku
		{
			printDetail(current); // meampilkan detail buku
			printf("\nMasukkan ID Detail (Ketik -1 untuk melihat Detail Buku) : ");
			scanf("%d", &id_peminjam);
		}
		if(current->x.card[id_peminjam].status == 2)
		{
			current->x.card[id_peminjam].status = 1;
			strcpy(current->x.card[id_peminjam].tanggal_balik, "");
			strcpy(current->x.card[id_peminjam].tanggal_pinjam, "");
		}
		else printf("\nID Detail salah, silakan cek kembali!");
	}
	else printf("\nID Buku tidak ditemukan, silakan cek kembali!");

}

void hapusBuku()
{
	Node *hapus, *before, *after;
	int id_buku;
		
		after = searchAfter(head);
		head = after;
		printf("\nData berhasil dihapus!");
	}



void tambahBuku()
{
	Node *insert;

	 
	 
	char judul_buku[MAX_LEN];
	char pengarang[MAX_LEN];
	char penerbit[MAX_LEN];
	int tahun;
	
	int stock;
	int id_buku;
	int i;
	
	printf("Masukkan Data Baru:\n");
	printf("ID Buku : ");	
	scanf("%d", &id_buku);
	getchar(); 
	printf("Judul Buku : ");	
	fgets(judul_buku,100,stdin);
	judul_buku[strlen(judul_buku) - 1] = '\0'; 
	printf("Pengarang : ");	
	fgets(pengarang,100,stdin);
	pengarang[strlen(pengarang) - 1] = '\0';
	printf("Penerbit : ");	
	fgets(penerbit,100,stdin);
	penerbit[strlen(penerbit) - 1] = '\0';
	printf("Tahun : ");	
	scanf("%d", &tahun);
	printf("Stock : ");	
	scanf("%d", &stock);
	
//	insert->next = (Node *) malloc(sizeof(Node));
	
	
	insert = sortingBuku(id_buku); //sorting buku
	insert->x.id_buku = id_buku;
	insert->x.tahun = tahun;
	insert->x.stock = stock;
	strcpy(insert->x.judul_buku, judul_buku);
	strcpy(insert->x.pengarang, pengarang);
	strcpy(insert->x.penerbit, penerbit);
	
	for(i=0; i<stock; i++)
		insert->x.card[i].status = 1; //looping slot buku sebanyak stok, status =1 berarti available
		
	
	printf("\nData telah ditambahkan!");
}

/////////////////////////admin session//////////////////////////////////
void adminSession()
{
	int menu;
	printf("\n\nSelamat Datang, Administrator!\n");
	while(1)
	{
		printAdminMenu();
		scanf("%d", &menu);
		system("cls");
		if(menu==1) detailBuku();
		else if(menu==2) kembaliBuku();
		else if(menu==3) pinjamBuku();
		else if(menu==4) tambahBuku();
		else if(menu==5) hapusBuku();
		else if(menu==6) cetakListBuku();
		else if(menu==7) break;
		else printf("\n\nError, menu tidak tersedia, silakan dicek kembali\n\n");
	}
}

/////////////////////////guest session//////////////////////////////////
void guestSession()
{
	int menu;
	printf("\n\nSelamat Datang, Guest!\n");
	while(1)
	{
		printGuestMenu();
		scanf("%d", &menu);
		system("cls");
		if(menu==1) detailBuku();
		else if(menu==2) cetakListBuku();
		else if(menu==3) break;
		else printf("\n\nError, menu tidak tersedia, silakan dicek kembali\n\n");
	}
}

/////////////////////////end of program/////////////////////////////////
