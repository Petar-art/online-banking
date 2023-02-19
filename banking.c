#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <dirent.h>
/* struct the user */
struct user{
char usr_phone[50], usr_password[50], usr_account[50],usr_pin[10];
float balance;
char usr_adres[50], usr_name[50];
};

/*create the Admin*/
int ValidAdmin(){
char  admin_pin[30];
char admin_username[30];

printf("\n\t Enter username: ");
scanf("%s", &admin_username);
printf("\n\t Enter password: ");
scanf("%s", &admin_pin);
maskPin(admin_pin);
/*set the condition to compare the string to validate the admin and to return true*/
if(strcmp(admin_username, "admin") == 0 && strcmp(admin_pin, "59891")==0){
    return 1;
}
else
    return 0;
}

void maskPin (int admin_pin[]) {
char hidden; int i=0;
while ((hidden=_getch())!=13){
    admin_pin[i]=hidden;
    printf("*");
    i++;
}
admin_pin[i]='\0';
}


int main () {
/*structure the main windows app*/
    system("color 3F");
    time_t now;
    time(&now);
/*app users*/
struct user usr,usr1;
    char phone[50], account[50], password[50], pin[10];
    char adres[50], name[50];
    char EnteredPin[10];
    int opt, choise, option,amount;
    float balance = 200;
    char filename [40];
    char cont = 'y';
/*the fie pointer*/
FILE *fp;
printf("\n");

    printf("\t\t\t\t\t            %s", ctime(&now));
printf("\n\t\t\t\t\t====*Dobrodosli na bankomat NLB Komercionalne banke====*");
printf("\n\n\t Sta zelite da uradite?");
printf("\n\n\t 1.Otvoite nalog.");
printf("\n\t 2.Ulogujete se u postojeci nalog.");
printf("\n\n\t 3.Ulogujete se kao admin.");
printf("\n\t Vas izbor je: ");
scanf("%d", &opt);

if (opt !=1 && opt !=2 && opt !=3){
    Beep(610,1500);
    printf("\n\t Wrong selection please try again.");
}

    if (opt == 1) {
                    /*if the os is Windows clear the screen using cls */
    system("cls");
                    /* use printf to promt the user to enter the values and scanf to store the values*/
    printf("\n\t Molimo vas unesite vas broj mobilnog telefona: ");
    scanf("%s", usr.usr_phone);
    printf("\n\t Molimo vas unesite vasu adresu: ");
    scanf("%s", usr.usr_adres);
    printf("\n\t Molimo unesite broj vaseg naloga: ");
    scanf("%s", usr.usr_account);
    printf("\n\t Molimo vas unesite vas password: ");
    scanf("%s", usr.usr_password);
    printf("\n\t Molimo unesite vas zeljeni PIN kartice: ");
    scanf("%s", usr.usr_pin);
    printf("\n\t Molimo unesite vase Ime i Prezime: ");
    scanf("%s", usr.usr_name);
    usr.balance = 0;
    /*a function to copy the string from struct usr and name the file based on the pin*/
    strcpy(filename, usr.usr_name);
    /* use the file pointer named fp to write the struct data of the user in the file type .txt using the "w" command meaning write*/
    fp = fopen(strcat(filename, ".txt"),"w");
    fwrite(&usr, sizeof(struct user),1,fp);
    if (fwrite != 0) {
        printf("\n\t Nalog uspesno napravljen!");
        while (cont == 'y'){
            printf("\n\t Da li zelite da se ulogujete[y/n]?");
            scanf("%s",&cont);
        }

    }
    else {
        printf("\n\t Niste uspeli da kreirate nalog, molimo pokusajte ponovo.");
    }
    fclose(fp);
}

    if(opt == 2){
        system("cls");
        printf("\n\t Molimo vas unesite vase ime:\t");
        scanf("%s",name);
        printf("\n\t Molimo vas unesite vas PIN:\t");
        scanf("%s",EnteredPin);
        strcpy(filename,name);
        fp = fopen(strcat(filename,".txt"),"r");
        if(fp == NULL){
            printf("\n Nalog nije registrovan molimo vas pokusajte ponovo.");
        }
        else {
        fread(&usr,sizeof(struct user),1,fp);
        fclose(fp);
        if(!strcmp(EnteredPin,usr.usr_pin)){
            printf("\n\t\tWelcome %s",usr.usr_name);;
            while(cont == 'y'){
                system("clear");
                printf("\n\t Pritisnite 1. za pregled sredstava");
                printf("\n\t Pritisnite 2. da depozitujete sredstva");
                printf("\n\t Pritisnite 3. da skinete sredstva");
                printf("\n\t Pritisnite 4. za online transfer sredstava");
                printf("\n\t Pritisnite 5. da promenite sifru naloga");
                printf("\n\t Vas izbor je:\t");
                scanf("%d",&choise);

                switch(choise){
                    case 1:
                        system("cls");
                        printf("\n Vas trenutni balans iznosi RSD %.2f",usr.balance);
                        break;
                    case 2:
                        printf("\n Unesite sumu:\t");
                        scanf("%f",&amount);
                        usr.balance += amount;
                        fp = fopen(filename,"w");
                        fwrite(&usr,sizeof(struct user),1,fp);
                        if(fwrite != NULL) printf("\n Uspesno ste depozitovali sredstva.");
                        fclose(fp);
                        break;
                    case 3:
                        printf("\n Unesite sumu: \t");
                        scanf("%f",&amount);
                        usr.balance -= amount;
                        fp = fopen(filename,"w");
                        fwrite(&usr,sizeof(struct user),1,fp);
                        if(fwrite != NULL) printf("\n Uspesno ste preuzeli RSD %.2f",amount);
                        fclose(fp);
                        break;

                    case 4:
                        printf("\n Molimo vas unesite broj telefona racuna:\t");
                        scanf("%s",phone);
                        printf("\n Molimo vas unesite kolicinu sredstava:\t");
                        scanf("%f",&amount);
                        strcpy(filename,name);
                        fp = fopen(strcat(filename,".txt"),"r");
                        if(fp == NULL) printf("\n Broj naloga nije registrovan");
                        else {
                            fread(&usr1,sizeof(struct user),1,fp);

                        fclose(fp);
                        if(amount > usr.balance) printf("\n Nedovoljna kolicina sredstava na racunu");
                        else {


                            fp = fopen(filename,"w");
                            usr1.balance += amount;
                            fwrite(&usr1,sizeof(struct user),1,fp);

                            fclose(fp);
                            if(fwrite != NULL){
                                printf("\n Uspesno ste poslali Rs.%.2f to %s",amount,phone);
                                strcpy(filename,usr.usr_phone);
                                fp = fopen(strcat(filename,".dat"),"w");
                                usr.balance -= amount;
                                fwrite(&usr,sizeof(struct user),1,fp);
                                fclose(fp);
                            }


                        }
                        break;
                 case 5:
                        printf("\n Molimo vas unesite novu sifru:\t");
                        scanf("%s",EnteredPin);
                        fp = fopen(filename,"w");
                        strcpy(usr.usr_pin,EnteredPin);
                        fwrite(&usr,sizeof(struct user),1,fp);
                        if(fwrite != NULL)
                        printf("\n Sifra uspesno promenjena");
                        }
                    break;
                default:
                    printf("\n Nevalidni pokusaj");
                }


                printf("\n Da li zelite da nastavite sa transakcijama [y/n]\t");
                scanf("%s",&cont);

            }
        }
        else {
            printf("\n Nevalidan PIN pokusajte ponovo");
        }
        }

    }



/*login as admin*/
if (opt == 3) {
    while(!ValidAdmin()) {
    do {
        system("cls");
        printf("\n");
        printf("\t\t\t\t\t            %s", ctime(&now));
        printf("\n\t\t\t\t\t====*Dobrosao Administratore===*\n\t Admin Menu: ");
        printf("\n\n\t Sta zelis da uradis?");
        printf("\n\t 1.Obrises korisnicki nalog.");
        printf("\n\t 2.Dodaj administrativni nalog.");
        scanf("%d", &choise);

    } while (choise != 3); // loop until user chooses to exit
}
}
}

