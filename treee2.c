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

Simpul* search(Simpul *root, char nilai[len])
{
    if(root==NULL || root->data_simpul == nilai[len]) 
        return root;
    else if(strcmp(nilai, root->data_simpul) > 0) 
        return search(root->kanan, nilai);
    else 
        return search(root->kiri, nilai);
}

//fungsi untuk menemukan nilai minimum pada node
Simpul* find_minimum(Simpul *root)
{
    if(root == NULL)
        return NULL;
    else if(root->kiri != NULL) 
        return find_minimum(root->kanan); 
    return root;
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

//fungsi untuk menghapus node
Simpul* delete(Simpul *root, char nilai[len])
{
    //search input yang mau dihapus
    if(root==NULL)
        return NULL;
    if(strcmp(nilai, root->data_simpul) > 0)
		root->kanan = delete(root->kanan, nilai);
	else if(strcmp(nilai, root->data_simpul) < 0)
		root->kiri = delete(root->kiri, nilai);
	else
    {
        //No Child
        if(root->kiri==NULL && root->kanan==NULL)
        {
            free(root);
            return NULL;
        }

        //One Child
        else if(root->kiri==NULL || root->kanan==NULL)
        {
            struct Simpul *temp;
            if(root->kiri==NULL)
                temp = root->kanan;
            else
                temp = root->kiri;
            free(root);
            return temp;
        }

        //Two Child
        else
        {
            struct Simpul *temp = find_minimum(root->kanan);
            root->data_simpul[len] = temp->data_simpul[len];
            root->kanan = delete(root->kanan, temp->data_simpul);
        }
    }
    return root;
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
	
	printf("In Order Sebelum Delete Node : "); 
    deret_inorder(root); 
    //printf("\nPre Order 	: ");
    //deret_preorder(root); 
    //printf("\nPost Order 	: ");
    //deret_postorder(root); 
    
    root = delete(root, "Lagi");
    root = delete(root, "Test");
    root = delete(root, "Coba");
    printf("\n\nIn Order Setelah Delete Node : "); 
    deret_inorder(root);

    return 0;
}
