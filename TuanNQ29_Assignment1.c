/* 
Viet mot chuong trinh quan ly mang so nguyen voi cac yeu cau sau:
Khi chay chuong trinh se hien loi gioi thieu chuong trinh "CT Quan Ly day so bang mang" va
huong dan su dung voi cac tinh nang cua chuong trinh:
- Nhap 'c' de tao mang so nguyen (Neu da co mang thi clear data cua mang cu).
- Nhap 'p' de in day (Neu day chua co gia tri thi bao day trong).
- Nhap 'i' de them mot phan tu vao day.
- Nhap 'd' de xoa mot phan tu tai vi tri thu k (neu vi tri k khong chua gia tri nao thi bao khong co
phan tu k).
- Nhap 's' de sap xep day so theo chieu tang dan.
- Nhap 'x' de sap xep day so theo chieu giam.
- Nhap 't' de tim kiem 1 so x co trong day khong (x nhap tu ban phim)?
- Nhap 'a' de in ra man hinh so lon nhat.
- Nhap 'w' de in ra man hinh so nho nhat.
- Neu nhap 'e' thi thoat chuong trinh.
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

void init();
void create_array();
void print_array();
void add_array();
void delete_array();
void sort_array_increase();
void sort_array_decrease();
void search_array();
void max_array();
void min_array();
void exit_program();
void swap(int *i, int *j);

static int mang[100]; /* Bien mang toan cuc gom 100 phan tu */
static int count; /* Bien dem toan cuc so phan tu cua mang */ 

int main()
{
    char nhap;

    while (1)
    {
        init(); /* Khoi tao man hinh gioi thieu va huong dan su dung */
        printf("\n\n -> Moi ban nhap: ");
        scanf("%c", &nhap);
        switch (nhap)
        {
        case 'c':
            create_array();
            system("pause");
            break;
        case 'p':
            print_array();
            system("pause");
            break;  
        case 'i':
            add_array();
            system("pause");
            break;
        case 'd':
            delete_array();
            system("pause");
            break;
        case 's':
            sort_array_increase();
            system("pause");
            break;
        case 'x':
            sort_array_decrease();
            system("pause");
            break;
        case 't':
            search_array();
            system("pause");
            break;
        case 'a':
            max_array();
            system("pause");
            break;
        case 'w':
            min_array();
            system("pause");
            break;
        case 'e':
            exit_program();
            break;
        
        default:
            break;
        }
        system("cls"); /* Lenh xoa man hinh */
    }

    return 0;
}

void init()
{
    printf("********** CT Quan ly day so bang mang **********");
    printf("\n\n\t - Nhap 'c' de tao mang so nguyen"); 
    printf("\n\t - Nhap 'p' de in day");
    printf("\n\t - Nhap 'i' de them mot phan tu vao day");
    printf("\n\t - Nhap 'd' de xoa mot phan tu tai vi tri thu k");
    printf("\n\t - Nhap 's' de sap xep theo chieu tang dan");
    printf("\n\t - Nhap 'x' de sap xep theo chieu giam");
    printf("\n\t - Nhap 't' de tim kiem mot so x co trong day hay khong");
    printf("\n\t - Nhap 'a' de in ra man hinh so lon nhat");
    printf("\n\t - Nhap 'w' de in ra man hinh so nho nhat");
    printf("\n\t - Nhap 'e' de thoat chuong trinh");
}

void create_array()
{
    int i;
    char term;

    /* Neu mang da co phan tu thi dua cac phan tu da co va bo dem ve 0 */
    if (count != 0)
    {
        memset(mang, 0, count*sizeof(int));
        count = 0;
    }

    /* Xu ly ngoai le khi nhap phan tu khong phai kieu so nguyen */
    while (1)
    {
        printf("\nXin moi nhap so phan tu cua mang: ");
        /* Neu count duoc nhap gom toan so nguyen va ky tu cuoi cung la ky tu xuong dong
		thi gia tri trong if bang 0 */
        /* Neu gia tri tra ve bang 1 tuc la input khong phai so nguyen */
        if(scanf("%d%c", &count, &term) != 2 || term != '\n') 
        {               
            fseek(stdin, 0, SEEK_END); /* Xoa bo dem khi nhap */
            continue;
        }
        /* Neu gia tri tra ve bang 0 tuc la input la so nguyen */
        else
        {
            fseek(stdin, 0, SEEK_END); /* Xoa bo dem khi nhap */
            break;
        }
    }
    
    for (i = 0; i < count; i++)
    {
        /* Xu ly ngoai le khi nhap phan tu khong phai kieu so nguyen */
        while (1)
        {
            printf("\n Moi nhap phan tu thu %d: ", i + 1);
            if(scanf("%d%c", &mang[i], &term) != 2 || term != '\n')
            {               
                fseek(stdin, 0, SEEK_END); /* Xoa bo dem khi nhap */
                continue;
            }
            else
            {
                fseek(stdin, 0, SEEK_END); /* Xoa bo dem khi nhap */
                break;
            }
        }
    }

    printf("\n\n Da nhap xong mang!\n\n");
}

void print_array()
{  
    int i;

    if (count == 0)
    {
        printf("\nMang dang trong!");
    }
    else
    {
        printf("\nMang da co la: ");
        for (i = 0; i < count; i++)
        {
            printf("\t%d", mang[i]);
        }
    }
    printf("\n\n");
}

void add_array()
{
    char term;
    print_array();

    /* Xu ly ngoai le khi nhap phan tu khong phai kieu so nguyen */
    while (1)
    {
        printf("\nMoi nhap phan tu tiep theo: ");
        if(scanf("%d%c", &mang[count], &term) != 2 || term != '\n')
        {               
            fseek(stdin, 0, SEEK_END); /* Xoa bo dem khi nhap */
            continue;
        }
        else
        {
            fseek(stdin, 0, SEEK_END); /* Xoa bo dem khi nhap */
            count++;
            break;
        }
    }

    printf("\nDa them phan tu vao mang!\n\n");
}

void delete_array()
{
    print_array();
    int k, i;
    char term;
    
    /* Xu ly ngoai le khi nhap phan tu khong phai kieu so nguyen */
    while (1)
    {
        printf("\nMoi ban nhap vi tri phan tu muon xoa: ");
        if(scanf("%d%c", &k, &term) != 2 || term != '\n')
        {               
            fseek(stdin, 0, SEEK_END); /* Xoa bo dem khi nhap */
            continue;
        }
        else
        {
            fseek(stdin, 0, SEEK_END); /* Xoa bo dem khi nhap */
            break;
        }
    }

    if (k > count || k <= 0) 
    {
        printf("\nMang khong co phan tu thu %d\n", k);
    }
    else
    {
        count--;
        for (i = k - 1; i < count; i++)
        {
            mang[i] = mang[i+1];
        }
        mang[count] = 0;
        printf("\n\nDa xoa phan tu trong mang!\n\n");
    }   
}

void swap(int *i, int *j)
{
    int temp;

    temp = *i;
    *i = *j;
    *j = temp;

    return;
}

void sort_array_increase()
{
    print_array();
    int i, j;

    printf("\nDang sap xep tang dan. Vui long doi...");
    sleep(1);
    for (i = 0; i < count-1; i++)
    {
        for (j = i + 1; j < count; j++)
        {
            if (mang[i] > mang[j])
            {
                swap(&mang[i], &mang[j]);
            }
        }
    }

    printf("\n\nDa sap xep xong!\n");
    print_array();
}

void sort_array_decrease()
{
    print_array();
    int i, j;

    printf("\nDang sap xep giam dan. Vui long doi...");
    sleep(1);
    for (i = 0; i < count-1; i++)
    {
        for (j = i + 1; j < count; j++)
        {
            if (mang[i] < mang[j])
            {
                swap(&mang[i], &mang[j]);
            }
        }
    }

    printf("\n\nDa sap xep xong!\n");
    print_array();
}

void search_array()
{
    int k, i, check = 0, vitri[count], dem = 0;
    char term;
    
    /* Xu ly ngoai le khi nhap phan tu khong phai kieu so nguyen */
    while (1)
    {
        printf("\nVui long nhap phan tu muon tim kiem trong mang: ");
        if(scanf("%d%c", &k, &term) != 2 || term != '\n')
        {               
            fseek(stdin, 0, SEEK_END); /* Xoa bo dem khi nhap */
            continue;
        }
        else
        {
            fseek(stdin, 0, SEEK_END); /* Xoa bo dem khi nhap */
            break;
        }
    }

    for (i = 0; i < count; i++)
    {
        if (k == mang[i])
        {
            check = 1;
            vitri[dem++]=i;
        }
    }

    if (check == 1)
    {
        printf("\nPhan tu da nhap co xuat hien trong mang!\n");
        printf("\nVi tri trong mang: ");
        for(i=0; i < dem; i++)
        {
            printf("\t%d", vitri[i] + 1);
        }
        printf("\n");
    }
    else
    {
        printf("\nPhan tu da nhap khong xuat hien trong mang!\n");
    }

    print_array();
}

void max_array()
{
    int max = mang[0], i;
    print_array();

    for (i = 1; i < count; i++)
    {
        if (max < mang[i])
        {
            max = mang[i];
        }
    }
    
    printf("\nPhan tu lon nhat trong mang la: %d\n\n", max);
}

void min_array()
{
    int min = mang[0], i;
    print_array();

    for (i = 1; i < count; i++)
    {
        if (min > mang[i])
        {
            min = mang[i];
        }
    }
    
    printf("\nPhan tu nho nhat trong mang la: %d\n\n", min);
}

void exit_program()
{
    printf("\nDang thoat chuong trinh...\n\n");
    sleep(1);
    exit(0);
}
