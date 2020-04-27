#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <malloc.h>
#include <Windows.h>

    struct Hospital{
    int id;
    char hospName[50];
    char hospAddress[50];
    int staffNum;
    };

    struct HospInd{
        int ind;
        int address;
        };
    struct Staff{
    int id;
    char name[50];
    char surname[50];
    char speciality[50];
    int hospId;
    };

        struct Hospital hosp ;
        struct HospInd hospI;
        struct Staff staff;
        FILE *hospital;
        char hospFileName[] = "Hospital.fl";
        FILE *hospInd = NULL;
        char hospIndFileName[] = "Hosp.ind";
        FILE *staffFile = NULL;
        char staffFileName[] = "Staff.fl";
        int staffLoc=0;
        int staffId =0;
        int hospId =0;
        int hospNum = 0;
        int staffNum = 0;
        struct Hospital *hosps;
        struct HospInd * hospInds;
        struct Staff* staffs;

        void init()
        {
            hospNum = 0;
            staffNum = 0;
           hospital = fopen(hospFileName,"r");
           while (!feof(hospital)) {
           fread ( &hosp , sizeof (struct Hospital) , 1 , hospital );
           hospNum++;
           }
            hospNum --;
            hospId = hosp.id;
           //printf("%d",hosp.id);
           //printf("%d", hospNum);

           staffFile = fopen(staffFileName,"r");
           while (!feof(staffFile)) {
           fread ( &staff , sizeof (struct Staff) , 1 , staffFile);
           if(staff.id > staffId){staffId = staff.id;}
           staffNum++;
           }
           staffNum --;

           //printf("%d", staffId);
           //printf("%d", staffNum);
        }

        void insertm()
        {

            printf("Введіть назву лікарні ");
            while(fgetc(stdin)!='\n');
            gets(hosp.hospName);
            printf("Введіть адресу лікарні ");
            gets(hosp.hospAddress);
            hospId++;
            hosp.id = hospId;
            hosp.staffNum = 0;
            hospI.ind = hosp.id;
            hospI.address = hospNum+1;
            hosps = (struct Hospital*)malloc(hospNum * sizeof(struct Hospital));
            hospital = fopen(hospFileName,"rb");
            fread ( hosps , sizeof (struct Hospital) , hospNum , hospital );
            /*for(int i =0; i<hospNum; i++){
                printf("%d",hosps[i].id);
                printf(hosps[i].hospName);
                printf("\n");
                printf("%d",hosps[i].staffNum);
                printf("\n");

            }*/
            fclose(hospital);
            hospInds = (struct HospInd*)malloc(hospNum * sizeof(struct HospInd));
            hospital = fopen(hospFileName,"wb");
            fwrite(hosps,sizeof (struct Hospital) , hospNum , hospital);
            fwrite ( &hosp , sizeof ( struct Hospital) , 1, hospital );
            fclose(hospital);

            hospInd = fopen(hospIndFileName,"rb");
            fread ( hospInds , sizeof (struct HospInd) , hospNum , hospInd );
            /*for(int i =0; i<hospNum; i++){
                printf("%d",hospInds[i].ind);
                printf("%d",hospInds[i].address);
                printf("\n");

            }*/
            fclose(hospInd);
            hospInd = fopen(hospIndFileName,"wb");
            fwrite(hospInds,sizeof (struct HospInd) , hospNum , hospInd);
            fwrite ( &hospI , sizeof ( struct HospInd) , 1, hospInd );
            fclose(hospInd);
            printf("Лікарню додано\n");
            free(hosps);
            free(hospInds);
        }

        void getS(){
        getm();
        if(hospI.address ==0){
            return;
        }
        printf("Введіть id лікаря ");
        scanf("%d", &staff.id);
        staffs = (struct Staff*)malloc(staffNum * sizeof(struct Staff));
        hosps = (struct Hospital*)malloc(hospNum * sizeof(struct Hospital));

        hospital = fopen(hospFileName,"rb");
        fread ( hosps , sizeof (struct Hospital) , hospNum , hospital );
        fclose(hospital);
             int j = 0;
            for(int i =0; i <hospI.address-1;i++){
                j = j +hosps[i].staffNum;
            }
            //printf("%d",j);
            //printf("\n");
            //printf("%d",hosp.staffNum);


        staffFile = fopen(staffFileName,"rb");
        fread ( staffs , sizeof (struct Staff) , staffNum , staffFile );
        staff.hospId =0;
        for(int i = j; i<j+hosp.staffNum; i++){
        if (staffs[i].id == staff.id)
                {staff = staffs[i];
                staffLoc = i;
                printf("id = %d",staff.id);
                printf("\n");
                printf("Ім'я : %s",staff.name);
                printf("\n");
                printf("Прізвище : %s",staff.surname);
                printf("\n");
                printf("Спеціальність : %s",staff.speciality);
                printf("\n");
                printf("id лікарні %d",staff.hospId);
                printf("\n");
                //printf("%d",staffLoc);
                break;
                }
        }
            if(staff.hospId ==0){
                printf("Такого лікаря в списку немає \n");
            }

        fclose(staffFile);
        free(staffs);
        free(hosps);


    }


        void getm(){
        printf("Введіть id лікарні ");
        scanf("%d", &hosp.id);
        hospInds = (struct HospInd*)malloc(hospNum * sizeof(struct HospInd));
        hospInd = fopen(hospIndFileName,"rb");
        fread ( hospInds , sizeof (struct HospInd) , hospNum , hospInd );
        hospI.address =0;
        for(int i =0; i<hospNum; i++){
            if (hospInds[i].ind == hosp.id)
                {hospI.address = hospInds[i].address;}
            }
        fclose(hospInd);
        if(hospI.address ==0){
            printf("У списку немає лікарні з таким id \n");
            free(hospInds);
            return;
        }
        hospital = fopen(hospFileName,"rb");
        fseek(hospital,(hospI.address-1) * sizeof(struct Hospital),SEEK_SET);
        fread(&hosp,sizeof ( struct Hospital) , 1, hospital);
        printf("id = %d",hosp.id);
        printf("\n");
        printf("Назва : %s",hosp.hospName);
        printf("\n");
        printf("Адреса : %s",hosp.hospAddress);
        printf("\n");
        printf("Кількість лікарів = %d",hosp.staffNum);
         printf("\n");
        fclose(hospital);
        free(hospInds);

        }


        void inserts(){
        printf("Введіть ім'я лікаря ");
        while(fgetc(stdin)!='\n');
        gets(staff.name);
        printf("Введіть прізвище лікаря ");
        gets(staff.surname);
        printf("Введіть спеціалізацію ");
        gets(staff.speciality);
        staffId++;
        staff.id = staffId;
        getm();
        if(hospI.address ==0){
            return;
        }
        staff.hospId = hosp.id;
        struct Staff *staffs2 = (struct Staff*)malloc((staffNum+1) * sizeof(struct Staff));
        staffs = (struct Staff*)malloc(staffNum * sizeof(struct Staff));

        staffFile= fopen(staffFileName,"rb");
        fread ( staffs , sizeof (struct Staff) , staffNum , staffFile );
           /* for(int i =0; i<staffNum; i++){
                printf("___________\n");
                printf(staffs[i].name);
                printf("\n");
        }*/
        fclose(staffFile);

        hosps = (struct Hospital*)malloc(hospNum * sizeof(struct Hospital));
        hospital = fopen(hospFileName,"rb");
        fread ( hosps , sizeof (struct Hospital) , hospNum , hospital );
        fclose(hospital);

            int j = 0;
            for(int i =0; i <hospI.address;i++){
                j = j +hosps[i].staffNum;
            }
            //printf("%d",j);

            for(int i =0; i <j; i++){
                staffs2[i] = staffs[i];
            }
            staffs2[j] = staff;
            for(int i =j+1; i<staffNum+1; i++){
                staffs2[i] = staffs[i-1];
            }
        staffNum++;
        staffFile= fopen(staffFileName,"wb");
        fwrite(staffs2,sizeof (struct Staff) ,  staffNum , staffFile);
        fclose(staffFile);
        int k = hospI.address -1;
        //printf("%d",k);
        hosps[k].staffNum++;
        hospital = fopen(hospFileName,"wb");
        fwrite(hosps,sizeof ( struct Hospital) ,hospNum, hospital);
        fclose(hospital);
        /*for(int i =0; i <staffNum; i++){
            printf("\n");
            printf("%d",staffs2[i].id);
            printf(staffs2[i].name);

        }*/
        printf("Лікар доданий до списку \n");
        free(hosps);
        free(staffs);

        }

        void delm(){
        getm();
        if(hospI.address ==0){return;}
        struct Hospital * hosps2;
        struct HospInd*hospInds2;
        hosps = (struct Hospital*)malloc(hospNum * sizeof(struct Hospital));
        hospInds = (struct HospInd*)malloc(hospNum * sizeof(struct HospInd));
        hospital = fopen(hospFileName,"rb");
        fread ( hosps , sizeof (struct Hospital) , hospNum , hospital );
        fclose(hospital);
        int hospStaffNum = hosp.staffNum;
         int j = 0;
            for(int i =0; i <hospI.address-1;i++){
                j = j +hosps[i].staffNum;
            }
        hospInd = fopen(hospIndFileName,"rb");
        fread ( hospInds , sizeof (struct HospInd) , hospNum , hospInd );
        fclose(hospInd);
        hospNum--;
        hosps2 = (struct Hospital*)malloc(hospNum * sizeof(struct Hospital));
        hospInds2 = (struct HospInd*)malloc(hospNum * sizeof(struct HospInd));
        for(int i = hospI.address-1; i<hospNum; i++){
            hosps[i] = hosps[i+1];
            hospInds[i] = hospInds[i+1];
            hospInds[i].address--;
        }
        for(int i =0; i< hospNum; i++){
            hosps2[i] = hosps[i];
        }
        for(int i =0; i< hospNum; i++){
            hospInds2[i] = hospInds[i];
        }
        hospital = fopen(hospFileName,"wb");
        fwrite(hosps2,sizeof (struct Hospital) , hospNum , hospital);
        fclose(hospital);
        hospInd = fopen(hospIndFileName,"wb");
        fwrite(hospInds2,sizeof (struct HospInd) , hospNum , hospInd);
        fclose(hospInd);
        free(hosps);
        free(hosps2);
        free(hospInds2);
        free(hospInds);

        staffs = (struct Staff*)malloc(staffNum * sizeof(struct Staff));
        staffFile= fopen(staffFileName,"rb");
        fread ( staffs , sizeof (struct Staff) , staffNum , staffFile );
        fclose(staffFile);

        staffNum = staffNum - hospStaffNum;
        struct Staff *staffs2 = (struct Staff*)malloc((staffNum) * sizeof(struct Staff));
        for(int i =j; i<staffNum; i++ ){
            staffs[i] = staffs[i+hospStaffNum];
        }
        for(int i =0 ; i< staffNum; i++){
            staffs2[i]=staffs[i];
        }
        staffFile= fopen(staffFileName,"wb");
        fwrite(staffs2,sizeof (struct Staff) ,  staffNum , staffFile);
        fclose(staffFile);
        printf("Лікарню видалено \n");
        free(staffs);
        free(staffs2);
        }

        void dels(){
        getS();

        if(staff.hospId ==0){
                return;
            }
        struct Staff * staffs2 =(struct Staff*)malloc((staffNum-1) * sizeof(struct Staff));
        staffs =(struct Staff*)malloc(staffNum * sizeof(struct Staff));
        staffNum--;
        staffFile= fopen(staffFileName,"rb");
        fread ( staffs , sizeof (struct Staff) , staffNum , staffFile );
        fclose(staffFile);
         for(int i = staffLoc; i<staffNum; i++){
            staffs[i] = staffs[i+1];
        }
        for(int i =0; i< staffNum; i++){
            staffs2[i] = staffs[i];
        }
        staffFile= fopen(staffFileName,"wb");
        fwrite(staffs2,sizeof (struct Staff) ,  staffNum , staffFile);
        fclose(staffFile);

        hosps = (struct Hospital*)malloc(hospNum * sizeof(struct Hospital));
        hospital = fopen(hospFileName,"rb");
        fread ( hosps , sizeof (struct Hospital) , hospNum , hospital );
        fclose(hospital);

        hosps[hospI.address-1].staffNum--;
        hospital = fopen(hospFileName,"wb");
        fwrite(hosps,sizeof (struct Hospital) , hospNum , hospital);
        fclose(hospital);
        printf("Лікаря видалено \n");
        free(staffs);
        free(hosps);
        free(staffs2);
    }

    void updatem(){
    getm();
    if(hospI.address ==0){
            return;
        }
    hosps = (struct Hospital*)malloc(hospNum * sizeof(struct Hospital));
    hospital = fopen(hospFileName,"rb");
    fread ( hosps , sizeof (struct Hospital) , hospNum , hospital );
    fclose(hospital);
    //printf("%d",hospI.address);
    printf("Введіть нову назву лікарні ");
    while(fgetc(stdin)!='\n');
    gets(hosps[hospI.address-1].hospName);
    printf("Введіть нову адресу лікарні ");
    gets(hosps[hospI.address-1].hospAddress);

    hospital = fopen(hospFileName,"wb");
    fwrite(hosps,sizeof (struct Hospital) , hospNum , hospital);
    fclose(hospital);
    printf("Дані оновлено");
    free(hosps);

    }

    void updates(){
    getS();
    if(staff.hospId ==0){
            return;
    }
    staffs = (struct Staff*)malloc(staffNum * sizeof(struct Staff));
    staffFile = fopen(staffFileName,"rb");
    fread ( staffs , sizeof (struct Staff) , staffNum , staffFile );
    fclose(staffFile);

    printf("Введіть ім'я лікаря ");
    while(fgetc(stdin)!='\n');
    gets(staffs[staffLoc].name);
    printf("Введіть призвіще лікаря ");
    gets(staffs[staffLoc].surname);
    printf("Введіть спеціалізацію ");
    gets(staffs[staffLoc].speciality);

    staffFile= fopen(staffFileName,"wb");
    fwrite(staffs,sizeof (struct Staff) ,  staffNum , staffFile);
    fclose(staffFile);
    printf("Дані оновлено\n");
    free(staffs);
    }
    void print(){
    init();
    printf("\nВсього лікарень : %d", hospNum);
    printf("\nВсього лікарів : %d",staffNum);

    hosps = (struct Hospital*)malloc(hospNum * sizeof(struct Hospital));
    hospital = fopen(hospFileName,"rb");
    fread ( hosps , sizeof (struct Hospital) , hospNum , hospital );
    fclose(hospital);
    printf("\n\tid\tК-сть лікарів\t\tНазва\t\t\t   Адреса");
    for(int i =0; i< hospNum; i++){
        printf("\n\t%d",hosps[i].id);
        printf("\t   %d",hosps[i].staffNum);
        printf("\t\t  %s",hosps[i].hospName);
        printf("  \t\t\t%s",hosps[i].hospAddress);


    }
    printf("\n");
    staffs = (struct Staff*)malloc(staffNum * sizeof(struct Staff));
    staffFile = fopen(staffFileName,"rb");
    fread ( staffs , sizeof (struct Staff) , staffNum , staffFile );
    fclose(staffFile);
    printf("\n\tid\tid лікарні\t Iм'я\t\tПрізвище\t\tСпеціальність");
    for(int i =0; i< staffNum; i++){
      printf("\n\t%d",staffs[i].id);
      printf("\t   %d",staffs[i].hospId);
      printf("\t\t%s",staffs[i].name);
      printf("\t\t%s",staffs[i].surname);
      printf(" \t\t%s",staffs[i].speciality);
    }
    printf("\n");
    free(hosps);
    free(staffs);
    }


int main()
{
    int option=0;
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
hospital = fopen(hospFileName,"w");
hospInd = fopen(hospIndFileName,"w");
staffFile = fopen(staffFileName,"w");
init();
while(1){
    printf("\n\t1 - Додати лікарню (insert-m) \n\t2 - Додати лікаря (insert-s) \n\t3 - Переглянути інформацію про лікарню (get-m)");
    printf("\n\t4 - Переглянути інформацію про лікаря (get-s)\n\t5 - Оновити дані лікарні (update-m)\n\t6 - Оновити дані лікаря (update-s)");
    printf("\n\t7 - Видалити лікарню (del-m)\n\t8 - Видалити лікаря (del-s)\n\t9 - Вивести на екран списки \n");

    scanf("%d",&option);
    switch (option){
    case 1: insertm(); init();break;
    case 2: inserts(); init();break;
    case 3:getm();break;
    case 4:getS();break;
    case 5 : updatem();break;
    case 6: updates();break;
    case 7 : delm();break;
    case 8: dels();break;
    case 9 : print();break;
    }
    while(fgetc(stdin)!='\n');
    if(option<0||option>9){
        printf("Введені невірні дані\n");
    }
}
}
