<h1 align="center">
    <b>
        <br>
        # Tugas Besar 1 IF3230 Sistem Paralel dan Terdistribusi
        <br>
    </b>
</h1>

<h2 align="center">
    <b>
        <br>
        OpenMPI - Dijkstra Algorithm
        <br>
        <br>
    </b>
</h2>

## Petunjuk Penggunaan Program
* Compile: <br>
  ketikan ```make``` pada direktori tempat ```makefile``` berada
* Run: <br>
  ketikan ```run``` pada direktori tempat ```makefile``` berada

## Laporan Pengerjaan
### Deskripsi Solusi Paralel
Solusi paralel yang dilakukan adalah data parallelism karena data yang ada dibagi-bagi ke *processor* yang ada, sehingga *processor* pusat hanya bertugas untuk menerima hasil dari pemrosesan algoritma dijkstra yang dilakukan oleh *processor* lain. Hasil pemrosesan algoritma dijkstra merupakan satu baris dari matriks jarak antar node. <br>
<div align="center">
    <img src="./assets/data_task_parallelism.png" width="300" height="200"/>
</div>
<br>
<div align="center">
    <img src="./assets/data_parallelism.png" width="300" height="200"/>
</div>

Cara kerja program:
1. Program menginisiasi graf dalam bentuk matriks berukuran N x N
2. Untuk setiap baris dan kolom, program mengisi nilai *random* yang didapat dari funsi ```rand()``` dengan seed ```13517020``` atau ```13517137```
3. Program mulai menjalankan algoritma dijkstra untuk mencari nilai cost minimum yang dibutuhkan dari node-x untuk mencapai node-y
   * Jika jumlah *processor* yang digunakan hanya 1, program akan menjalankan algoritma dijkstra secara serial
   * Jika jumlah *processor* yang digunakan lebih dari 1, program akan menjalankan algoritma dijkstra secara paralel
     * *processor* dengan nilai ```rank = 0``` menerima hasil pemrosesan graf menggunakan algoritma dijkstra dari *processor-processor* lain
     * *processor* dengan nilai ```rank ≠ 0``` melakukan pemrosesan graf menggunakan algoritma dijkstra untuk dikirimkan ke *processor* dengan nilai ```rank = 0```

### Analisis Solusi
* Kelebihan:
  * Lebih hemat *memori space* karena alokasi *memory* menyesuaikan input jumlah nodes
* Kelemahan:
  * Graf digenerate pada setiap *processor*
* Solusi yang lebih baik:
  * Semua *process* algoritma djikstra membaca dan menuliskan pada address yang sama

### Jumlah Thread yang Digunakan


### Pengukuran Kinerja Algoritma Paralel dengan Serial
| Jumlah Processor | Jumlah Node | Waktu 1 (μs) | Waktu 2 (μs) | Waktu 3 (μs) |
|:----------------:|:-----------:|:------------:|:------------:|:------------:|
|      1 (Serial)  |         100 |        49307 |        34070 |        33892 |
|      1 (Serial)  |         500 |      1741475 |      1176024 |      1033807 |
|      1 (Serial)  |        1000 |     14905097 |      8278146 |      9279655 |
|      1 (Serial)  |        3000 |    238046050 |  |  |
|      2 (Paralel) |         100 |        64976 |        39307 |        53852 |
|      2 (Paralel) |         500 |      1075717 |      1271727 |      1280256 |
|      2 (Paralel) |        1000 |     12198962 |      9334894 |     10188746 |
|      2 (Paralel) |        3000 |  |  |  |
|      3 (Paralel) |         100 |        50223 |        41098 |        47145 |
|      3 (Paralel) |         500 |       740905 |       684402 |       772519 |
|      3 (Paralel) |        1000 |  |  |  |
|      3 (Paralel) |        3000 |  |  |  |
|      4 (Paralel) |         100 |        43992 |        40993 |        55301 |
|      4 (Paralel) |         500 |       535659 |       546592 |       828609 |
|      4 (Paralel) |        1000 |  |  |  |
|      4 (Paralel) |        3000 |  |  |  |
|      5 (Paralel) |         100 |        45598 |        42189 |        42876 |
|      5 (Paralel) |         500 |       357208 |       359947 |       673483 |
|      5 (Paralel) |        1000 |  |  |  |
|      5 (Paralel) |        3000 |  |  |  |
|      6 (Paralel) |         100 |        40593 |       124807 |        40528 |
|      6 (Paralel) |         500 |       245153 |       287382 |       284934 |
|      6 (Paralel) |        1000 |  |  |  |
|      6 (Paralel) |        3000 |  |  |  |

### Analisis Perbandingan Kinerja Serial dan Paralel
| Serial | Paralel |
|--------|---------|
|  |  |
|  |  |

## Pembagian Tugas
* 13517020 mengerjakan fungsi algoritma dijkstra, output to file, makefile dan laporan
* 13517137 mengerjakan fungsi graph generator, output to file, makefile dan laporan