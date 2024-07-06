#include <stdio.h>           /* header stands for standard input and output*/
#include <stdlib.h>          /*header file stands for standard library*/
#include <string.h>
#define MAX 256

/*variables and arrays declaration*/

int ID,Price, Quantity;
char Med_Name[100], Med_Comp[100],Manuf_Date[100], Exp_Date[100];

FILE *aptr, *bptr;

/*function prototypes*/

void AddMedicine();
void Delete();
void UpdateMedicine();
void MedicinesInStock();
void GetMedicineInfo();
void SellMedicine();
void Quit();

int main() {       /*function main definition*/

    int option;

    /* loop to ask the user about the required option */

    do {
        printf(" 1) Add Medicine\n 2) Delete\n 3) Update Medicine\n 4) Medicines In Stock\n 5) Get Medicine Info\n 6) Sell Medicine\n 7) Quit\n");
        printf("Choose one from the above: ");
        scanf("%d", &option);

        /* switch function to call functions when needed */

        switch (option) {
            case 1:
                AddMedicine();
                break;
            case 2:
                Delete();
                break;
            case 3:
                UpdateMedicine();
                break;
            case 4:
                MedicinesInStock();
                break;
            case 5:
                GetMedicineInfo();
                break;
            case 6:
                SellMedicine();
                break;
            case 7:
                Quit();
                break;
            default:
                printf("NONE\n\n");
        }
    } while(option!=7);

    return 0;
}

void AddMedicine(){           /* add medicine function definition*/

    /* opening file to add data into it */

    if ((aptr = fopen( "C:\\Users\\lenovo\\CLionProjects\\PROJECT\\OUR PHARMACY.txt","a")) == NULL) {
        printf( "File could not be opened\n" );
    }
    else{

        /* printing data into the file */

        printf("Enter Medicine ID:\n");
        scanf("%d",&ID);
        fprintf(aptr,"\n\n%d",ID);

     printf("Enter Company Name:\n");
     scanf("%s",Med_Comp);
     fprintf(aptr,"%14s",Med_Comp);

     printf("Enter Medicine Name:\n");
     scanf("%s",Med_Name);
     fprintf(aptr,"%14s",Med_Name);

     printf("Enter Manufactured Date:\n");
     scanf("%s",Manuf_Date);
     fprintf(aptr,"%15s",Manuf_Date);

     printf("Enter Expiry Date:\n");
     scanf("%s",Exp_Date);
     fprintf(aptr,"%17s",Exp_Date);

     printf("Enter Quantity:\n");
     scanf("%d",&Quantity);
     fprintf(aptr,"%15d",Quantity);

     printf("Enter Price:\n");
     scanf("%d",&Price);
     fprintf(aptr,"%14d",Price);

     printf("Medicine with ID %d was added successfully\n",ID);
    }

    /* closing file */
    fclose(aptr);
}

void Delete() {                 /*Delete function definition*/

    printf("\nenter the ID of the medicine you want to delete: ");
    scanf("%d", &ID);

    int ctr = 0;                /*initializing a counter*/

    char str[MAX], temp[] = "C:\\Users\\lenovo\\CLionProjects\\PROJECT\\temp.txt";        /*creating a temporary file to copy data except the deleted ones into it*/

    /* opening original file to read data from it */

    aptr = fopen("C:\\Users\\lenovo\\CLionProjects\\PROJECT\\OUR PHARMACY.txt", "r");

    if (!aptr) {

        /* if the pointer to the file is NULL it will print that the file couldn't be opened */

        printf(" File not found or unable to open the file\n");
    }

    bptr = fopen(temp, "w");              // open the temporary file in write mode

    /*checking if the file will be opened*/

     if (!bptr) {
        printf("Unable to open a temporary file to write!!\n");
        fclose(aptr);
    }

    /*copy all contents to the temporary file except the specific line*/

    while (!feof(aptr)) {

        strcpy(str, "\0");
        fgets(str, MAX, aptr);

        if (!feof(aptr)) {
            ctr++;

            if (ctr != ID) {                       /* skip the line at given line number */

                fprintf(bptr, "%s", str);     /*printing all data in temporary file except the deleted line*/
            }
        }
    }

    /* closing 2 files */

    fclose(aptr);
    fclose(bptr);

    remove("C:\\Users\\lenovo\\CLionProjects\\PROJECT\\OUR PHARMACY.txt");  		// remove the original file
    rename(temp, "C:\\Users\\lenovo\\CLionProjects\\PROJECT\\OUR PHARMACY.txt"); 	// rename the temporary file to original name

    /*Read the file */

    bptr = fopen("C:\\Users\\lenovo\\CLionProjects\\PROJECT\\temp.txt", "r");
    printf("\nMedicine with ID %d is deleted successfully\n", ID);
    printf("Now the content of the file is : \n");

    char *single_line;       /*defining a pointer to the lines*/

    single_line = malloc(10000 * sizeof(char));            /*indicating maximum size for the single line that's read from the file*/

    /* loop for reading and getting data from the file and printing them on screen */

    while (!feof(bptr)) {
        fgets(single_line, 10000, bptr);
        puts(single_line);
    }
}

void UpdateMedicine() {                /*function definition*/

    int option;

    printf("1- Change quantity\n2- Change price\n3- Change Name\n4- Change Company\n5- Change Manufacturing date\n6- Change Expiry date");
    printf("Enter your choice: ");
    scanf("%d",&option);

    switch (option) {
        case 1:
            printf("enter the quantity to be changed: ");
            scanf("%d",&Quantity);
            break;
        case 2:
            printf("enter the price to be changed: ");
            scanf("%d",&Price);
            break;
        case 3:
            printf("enter the name to be changed: ");
            scanf("%s",&Med_Name);
            break;
        case 4:
            printf("enter the company name to be changed: ");
            scanf("%s",&Med_Comp);
            break;
        case 5:
            printf("enter the manufacturing date to be changed: ");
            scanf("%s",&Manuf_Date);
            break;
        case 6:
            printf("enter the expiry date to be changed: ");
            scanf("%s",&Exp_Date);
            break;
        default:
            printf("NONE\n\n");
    }
}

void MedicinesInStock() {              /*function definition*/

    /*opening file*/

    if ((aptr = fopen( "C:\\Users\\lenovo\\CLionProjects\\PROJECT\\OUR PHARMACY.txt","r")) == NULL) {
        printf( "File could not be opened\n" );
    }
    else{

       char *single_line;                            /*defining a pointer to the lines*/

        single_line=malloc(10000*sizeof(char));              /*indicating maximum size for the single line that's read from the file*/

        /* loop for reading and getting data from the file and printing them on screen */

        while(!feof(aptr)){

            fgets(single_line, 10000,aptr);
            puts(single_line);
        }
    }

    fclose(aptr);        // closing the file
}

void GetMedicineInfo(){             /*function definition*/

    int FLAG=0;                      /*initializing a variable to check the presence of a medicine in the file or not*/
    char single_line[270];           /*initializing an array for reading line by line in the file*/

    printf("Enter the ID: ");
    scanf("%d",&ID);

    int search=1;          /*initializing a variable for searching for the medicine ID in the file*/

    if ((aptr = fopen("C:\\Users\\lenovo\\CLionProjects\\PROJECT\\OUR PHARMACY.txt","r")) == NULL) {
        printf( "File could not be opened\n" );
    }
    else {

        /*loop for reading the file line by line and searching for a specific ID*/

        while (fgets(single_line,sizeof single_line,aptr)!=NULL) {

            if (search==ID){              //if the specific ID is found then the line containing this ID will be printed out

                printf("\n%s\n",single_line);
                fclose(aptr);
                FLAG=1;       /* medicine is found in the file */
            }
            else{
                search++;
                continue;
            }
        }

        fclose(aptr);
    }
    if(FLAG==0)               // medicine not found in the file
        printf("\nMedicine with ID %d isn't found\n",ID);

    //trials for receiving name from the user

  /*  switch (number)
    {
        case 1:

            printf("Enter the ID: ");
            scanf("%d",&ID);

            int search=1;

            if ((aptr = fopen("C:\\Users\\lenovo\\CLionProjects\\PROJECT\\OUR PHARMACY.txt","r")) == NULL) {
                printf( "File could not be opened\n" );
            }
            else {

                while (fgets(single_line,sizeof single_line,aptr)!=NULL) {

                    if (search==ID){
                        printf("\n%s\n",single_line);
                        fclose(aptr);
                        FLAG=1;
                    }
                    else{
                       search++;
                       continue;
                    }
                }
                fclose(aptr);
            }
            if(FLAG==0)
                printf("\nMedicine with ID %d isn't found\n",ID);
            break;
        case 2:

            printf("Enter the name: ");
            scanf("%s",&Med_Name);

            if ((aptr = fopen( "C:\\Users\\lenovo\\CLionProjects\\PROJECT\\OUR PHARMACY.txt","r")) != NULL) {

                while (fgets(single_line, sizeof single_line, aptr) != NULL) {
                    int search = 1;

                    if ((Med_Name == medicines[0]) && search == 3) {

                        printf("\n%s\n", single_line);
                        fclose(aptr);
                        FLAG = 1;
                        break;
                    } else {
                        search++;
                        continue;
                    }
                }

                 else if (Med_Name==medicines[0]) {

                     if (search == 3) {
                         printf("\n%s\n", single_line);
                         fclose(aptr);
                         FLAG = 1;
                         break;
                     }
                     else {
                         search++;
                         continue;
                     }

            }
            else {
                 printf( "File could not be opened\n" );
            }
            fclose(aptr);
            break;
        default:
            printf("NONE\n\n");
    }}

}*/
}

void SellMedicine() {               /*function definition*/

    int FLAG = 0, search = 1, option;               /*variables declaration*/

    printf("Please enter the Id of the medicine: ");
    scanf("%d", &ID);

    /* opening file */

    if ((aptr = fopen("C:\\Users\\lenovo\\CLionProjects\\PROJECT\\OUR PHARMACY.txt", "r")) == NULL) {
        printf("File could not be opened\n");
    }
    else {

        char single_line[270];             /*initializing an array for reading line by line in the file*/

        /*loop for reading the file line by line and searching for a specific ID*/

        while (fgets(single_line, sizeof single_line, aptr) != NULL) {

            if (search == ID) {           //if the specific ID is found then the line containing this ID will be printed out

                printf("\n%s\n", single_line);
                fclose(aptr);
                FLAG = 1;
            }
            else {
                search++;
                continue;
            }

            /*checking if the user wants to buy the medicine or not */

            printf("Would you like to buy this medicine?\n1)Yes\n2)No\n");
            printf("Enter your choice: ");
            scanf("%d", &option);

            switch (option) {
                case 1:
                    printf("What is the quantity you need?: ");
                    scanf("%d", &Quantity);
                    printf("\nYou bought %d of the medicine\n", Quantity);
                    break;
                case 2:
                    break;
                default:
                    printf("None");
                    break;
            }
        }
        }

    fclose(aptr);
    if (FLAG == 0) {
        printf("\nMedicine with ID %d isn't found\n", ID);
    }
    }

void Quit(){}
