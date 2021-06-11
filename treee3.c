#include <stdio.h>
#include <stdlib.h>

#define len 50 
typedef struct Simpul
{
    char data_simpul[len];
    struct Simpul *kiri;
    struct Simpul *kanan;
} Simpul;

Simpul* create_simpul (char nilai[len]){
	
    Simpul* simpul = (Simpul *)malloc(sizeof(Simpul));
    strcpy(simpul->data_simpul, nilai);
    simpul->kanan = NULL;
    simpul->kiri = NULL;
    
    return simpul;
}

void insert(Simpul *root, char nilai[len]){
	
    if(strcmp(nilai, root->data_simpul) > 0){
        if(root->kanan == NULL){
            root->kanan = create_simpul(nilai);
        }
		else{
            insert(root->kanan, nilai);
        }
    }
    
    if(strcmp(nilai, root->data_simpul) < 0){
        if(root->kiri == NULL){
            root->kiri = create_simpul(nilai);
        }
		else{
            insert(root->kiri, nilai);
        }
    }
}

/*Simpul* tree (char deret_angka[], int ukuran_deret){
	int i;
    Simpul *root;
    
    for(i = 0; i < ukuran_deret; i++){
        if(i == 0){
            root = create_simpul(deret_angka[i]);
            continue;
        }
        insert(root, deret_angka[i]);
    }
    return root;
}*/

void deret_inorder(Simpul *root){
    if (root == NULL)
    {
	return;
	}
    deret_inorder(root->kiri);
    printf("%s ",root->data_simpul);
    deret_inorder(root->kanan);
}

void deret_preorder(Simpul *root){
    if (root == NULL)
    {
	return;
	}
    printf("%s ",root->data_simpul);
    deret_preorder(root->kiri);
    deret_preorder(root->kanan);
}

void deret_postorder(Simpul *root){
    if (root == NULL)
	{
	return;
	}
    deret_postorder(root->kiri);
    deret_postorder(root->kanan);
    printf("%s ",root->data_simpul);
}

int main()
{
	//int deret_angka[] = { 19, 8, 10, 1, 006, 2, 17, 04, 20, 01 };
    //int ukuran_deret = sizeof(deret_angka) / sizeof(deret_angka[0]);

    Simpul *root = create_simpul("Admin");
	//printf("Struktur BST Dari Deret (Angka NPM + Tanggal Lahir)\n");
	
	insert(root, "Ezra");
	insert(root, "Akbar");
	insert(root, "Frans");
	insert(root, "Adit");
	insert(root, "Test");
	insert(root, "Coba");
	insert(root, "Lagi");
	
	printf("In Order 	: "); 
    deret_inorder(root); 
    printf("\nPre Order 	: ");
    deret_preorder(root); 
    printf("\nPost Order 	: ");
    deret_postorder(root); 

    return 0;
}
