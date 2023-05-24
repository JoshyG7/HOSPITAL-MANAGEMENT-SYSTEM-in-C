#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
void admitPatient();
void patientList();
void dischargePatient();
void addDoctor();
void doctorList();
struct patient{
    int id;
    char patientName[50];
    char patientAddress[50];
    char disease[50];
    char date[12];
}p;

struct doctor{
    int id;
    char name[50];
    char address[50];
    char specialize[50];
    char date[12];
}d;

FILE *fp;

int main(){
    int ch;
    char q;
    printf("\t\t\t##########################################");
    printf("\n\t\t\t\t\tWELCOME TO");
    printf("\n\t\t\t\tHOSPITAL MANAGEMENT SYSTEM");
    printf("\n\t\t\t#########################################");
    printf("\n\nPress Enter key to continue......");
    scanf("%c",&q);
    if(q=='\n'){
    while(1){
        printf("\n\n\t\t----------------------------------------------------------");
        printf("\n\t\t\t\t\tHOSPITAL");
        printf("\n\t\t----------------------------------------------------------");
        printf("\n\n1.Add Patients Record\n");
        printf("2.List Patients Record\n");
        printf("3.Delete Patients Record\n");
        printf("4.Add Doctor Record\n");
        printf("5.List Doctors Record\n");
        printf("0.Exit\n\n");
        printf("Choose form 1 to 0: ");
        scanf("%d", &ch);

        switch(ch){
        case 0:
            exit(0);

        case 1:
            admitPatient();
            break;

        case 2:
            patientList();
            break;

        case 3:
            dischargePatient();
            break;

        case 4:
            addDoctor();
            break;

        case 5:
            doctorList();
            break;

        default:
            printf("Invalid Choice...\n\n");

        }
        printf("\n\nPress Any Key To Continue...");
    }
    }
    return 0;
}

void admitPatient(){
    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(p.date, myDate);

    fp = fopen("patient.txt", "ab");
    printf("\n\n\t\t!!!!!!!!!!!!!!!! Add Patients Record !!!!!!!!!!!!!!!!!!!!!\n\n");
    printf("Enter Patient id: ");
    scanf("%d", &p.id);

    printf("Enter Patient name: ");
    fflush(stdin);
    gets(p.patientName);

    printf("Enter Patient Address: ");
    fflush(stdin);
    gets(p.patientAddress);

    printf("Enter Patient Disease: ");
    fflush(stdin);
    gets(p.disease);

    printf("\nPatient Added Successfully");

    fwrite(&p, sizeof(p), 1, fp);
    fclose(fp);
}

void patientList(){

    system("cls");
    printf("\n\n\t\t!!!!!!!!!!!!!!!! List Patients Record !!!!!!!!!!!!!!!!!!!!!\n");
    printf("%-10s %-30s %-30s %-20s %s\n", "Id", "Patient Name", "Address", "Disease", "Date");
    printf("----------------------------------------------------------------------------------------------------------\n");

    fp = fopen("patient.txt", "rb");
    while(fread(&p, sizeof(p), 1, fp) == 1){
        printf("%-10d %-30s %-30s %-20s %s\n", p.id, p.patientName, p.patientAddress, p.disease, p.date);
    }

    fclose(fp);
}


void dischargePatient(){
    int id, f=0;
    system("cls");
    printf("\n\n\t\t!!!!!!!!!!!!!!!! Delete Patients Record !!!!!!!!!!!!!!!!!!!!!\n");
    printf("Enter Patient id to discharge: ");
    scanf("%d", &id);

    FILE *ft;

    fp = fopen("patient.txt", "rb");
    ft = fopen("temp.txt", "wb");

    while(fread(&p, sizeof(p), 1, fp) == 1){

        if(id == p.id){
            f=1;
        }else{
            fwrite(&p, sizeof(p), 1, ft);
        }
    }

    if(f==1){
        printf("\n\nPatient Delete Record Successfully.");
    }else{
        printf("\n\nRecord Not Found !");
    }

    fclose(fp);
    fclose(ft);

    remove("patient.txt");
    rename("temp.txt", "patient.txt");

}

void addDoctor(){

    char myDate[12];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(myDate, "%02d/%02d/%d", tm.tm_mday, tm.tm_mon+1, tm.tm_year + 1900);
    strcpy(d.date, myDate);

    int f=0;

    system("cls");
    printf("\n\n\t\t!!!!!!!!!!!!!!!! Add Doctor Record !!!!!!!!!!!!!!!!!!!!!\n");

    fp = fopen("doctor.txt", "ab");

    printf("Enter Doctor id: ");
    scanf("%d", &d.id);

    printf("Enter Doctor Name: ");
    fflush(stdin);
    gets(d.name);

    printf("Enter Doctor Address: ");
    fflush(stdin);
    gets(d.address);

    printf("Doctor Specialize in: ");
    fflush(stdin);
    gets(d.specialize);

    printf("Doctor Added Successfully\n\n");

    fwrite(&d, sizeof(d), 1, fp);
    fclose(fp);
}
void doctorList(){
    system("cls");
    printf("\n\n\t\t!!!!!!!!!!!!!!!! List Doctors Record !!!!!!!!!!!!!!!!!!!!!\n");

    printf("%-10s %-30s %-30s %-30s %s\n", "id", "Name", "Address", "Specialize","Date");
    printf("-------------------------------------------------------------------------------------------------------------------\n");

    fp = fopen("doctor.txt", "rb");
    while(fread(&d, sizeof(d), 1, fp) == 1){
        printf("%-10d %-30s %-30s %-30s %s\n", d.id, d.name, d.address, d.specialize, d.date);
    }

    fclose(fp);
}