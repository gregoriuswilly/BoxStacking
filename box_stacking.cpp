/* Dynamic Programming implementation of Box Stacking problem */
#include<stdio.h>
#include<stdlib.h>
	 
/* Tipe bentukan box/balok */
struct Box{
	  // p --> panjang, l --> lebar, t --> tinggi
	  int p, l, t;
};
	 
// Fungsi untuk mencari nilai minimum dari dua integer
int min (int x, int y){ 
	return (x < y)? x : y; 
}
	 
// Fungsi untuk mencari nilai maksimum dari dua integer
int max (int x, int y){ 
	return (x > y)? x : y; 
}
	 
/* Funsgi untuk library function qsort(). 
   Fungsi qsort digunakan untuk mengurutkan balok dari luas alas 
   terbesar ke terkecil (tinggi terkecil ke terbesar).
   http://www.cplusplus.com/reference/clibrary/cstdlib/qsort/ */
int compare (const void *a, const void * b){
	return ( (*(Box *)b).l * (*(Box *)b).p ) - ( (*(Box *)a).l * (*(Box *)a).p );
}
	 
/* Fungsi utama untuk mengembalikan tumpukan tertinggi
	dari tipe ukuran balok yang diberikan */
int maxStackHeight( Box arr[], int n ){
   /* Membuat array dari semua rotasi berdasarkan ukuran balok yang tersedia
      Contoh, untuk balok {1, 2, 3}, didapatkan {{1, 2, 3}, {2, 1, 3}, {3, 1, 2}} */
	Box rot[3*n];
	int index = 0;
	for (int i = 0; i < n; i++){
    	// original box
    	rot[index].t = arr[i].t;
    	rot[index].l = max(arr[i].l, arr[i].p);
    	rot[index].p = min(arr[i].l, arr[i].p);
    	index++;
 
    	// First rotation
    	rot[index].t = arr[i].p;
    	rot[index].l = max(arr[i].t, arr[i].l);
    	rot[index].p = min(arr[i].t, arr[i].l);
    	index++;
 
    	// Second rotation
    	rot[index].t = arr[i].l;
    	rot[index].l = max(arr[i].t, arr[i].p);
    	rot[index].p = min(arr[i].t, arr[i].p);
    	index++;
	}
 
	// Jumlah balok saat ini (konfigurasi ukuran) = 3n
	n = 3*n;
 
	/* Mengurutkan array 'rot[]' dari tinggi terkecil ke terbesar*/
	qsort (rot, n, sizeof(rot[0]), compare);
 
	// Mencetak semua konfigurasi ukuran balok hasil rotasi
	printf("Konfigurasi hasil rotasi balok:\n");
	for (int i = 0; i < n; i++ ){
		printf("%d x %d x %d\n", rot[i].p, rot[i].l, rot[i].t);
	}
 
	/* Menginisialisasi nilai msh[i] untuk semua index
      msh[i] --> Maximum possible Stack Height with box i on top */
	int msh[n];
	for (int i = 0; i < n; i++ )
    	msh[i] = rot[i].t;
 
	/* Mengitung nilai msh[i] yang paling optimal */
	for (int i = 1; i < n; i++ ){
   		for (int j = 0; j < i; j++ ){
   			if ( rot[i].p < rot[j].p && rot[i].l < rot[j].l && msh[i] < msh[j] + rot[i].t){
				msh[i] = msh[j] + rot[i].t;
	    	}
   		}   		
   	}
      
   /* Mencari nilai maksimum dari msh[i]  */
	int max = -1;
	for ( int i = 0; i < n; i++ ){
		if ( max < msh[i] ){
			max = msh[i];
		}
	}
 
	return max;
}
	 
/* Driver program */
int main(){
	Box balok[] = { 
//		{ 1, 2, 3 },
	    { 4, 5, 6 },
//	    { 7, 8, 9 },
		};
	int n = sizeof(balok)/sizeof(balok[0]);
	
	printf("\nTinggi tumpukan maksimum adalah %d\n", maxStackHeight (balok, n) );
	
	return 0;
}
