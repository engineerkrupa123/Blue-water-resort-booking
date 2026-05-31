#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Resort
{
    int customerId;
    char name[50];
    long long phone;
    int roomNo;
    int days;
    float rentPerDay;
};

void addBooking();
void viewBookings();
void searchBooking();
void updateBooking();
void deleteBooking();
void generateBill();

int main()
{
    int choice;

    do
    {
        printf("\n====================================");
        printf("\n BLUE WATER RESORT BOOKING SYSTEM");
        printf("\n====================================");
        printf("\n1. Add Booking");
        printf("\n2. View All Bookings");
        printf("\n3. Search Booking");
        printf("\n4. Update Booking");
        printf("\n5. Delete Booking");
        printf("\n6. Generate Bill");
        printf("\n7. Exit");

        printf("\n\nEnter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                addBooking();
                break;

            case 2:
                viewBookings();
                break;

            case 3:
                searchBooking();
                break;

            case 4:
                updateBooking();
                break;

            case 5:
                deleteBooking();
                break;

            case 6:
                generateBill();
                break;

            case 7:
                printf("\nThank You!\n");
                break;

            default:
                printf("\nInvalid Choice!\n");
        }

    } while(choice != 7);

    return 0;
}

void addBooking()
{
    FILE *fp;
    struct Resort r;

    fp = fopen("resort.dat", "ab");

    if(fp == NULL)
    {
        printf("\nError Opening File!\n");
        return;
    }

    printf("\nEnter Customer ID: ");
    scanf("%d", &r.customerId);

    printf("Enter Customer Name: ");
    scanf(" %[^\n]", r.name);

    printf("Enter Phone Number: ");
    scanf("%lld", &r.phone);

    printf("Enter Room Number: ");
    scanf("%d", &r.roomNo);

    printf("Enter Number of Days: ");
    scanf("%d", &r.days);

    printf("Enter Rent Per Day: ");
    scanf("%f", &r.rentPerDay);

    fwrite(&r, sizeof(r), 1, fp);

    fclose(fp);

    printf("\nBooking Added Successfully!\n");
}

void viewBookings()
{
    FILE *fp;
    struct Resort r;

    fp = fopen("resort.dat", "rb");

    if(fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\n=========== BOOKINGS ===========\n");

    while(fread(&r, sizeof(r), 1, fp))
    {
        printf("\nCustomer ID   : %d", r.customerId);
        printf("\nName          : %s", r.name);
        printf("\nPhone         : %lld", r.phone);
        printf("\nRoom Number   : %d", r.roomNo);
        printf("\nDays Stayed   : %d", r.days);
        printf("\nRent Per Day  : %.2f", r.rentPerDay);
        printf("\n--------------------------------");
    }

    fclose(fp);
}

void searchBooking()
{
    FILE *fp;
    struct Resort r;
    int id, found = 0;

    fp = fopen("resort.dat", "rb");

    if(fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\nEnter Customer ID to Search: ");
    scanf("%d", &id);

    while(fread(&r, sizeof(r), 1, fp))
    {
        if(r.customerId == id)
        {
            found = 1;

            printf("\nBooking Found\n");
            printf("\nName        : %s", r.name);
            printf("\nPhone       : %lld", r.phone);
            printf("\nRoom Number : %d", r.roomNo);
            printf("\nDays        : %d", r.days);
            break;
        }
    }

    if(!found)
        printf("\nRecord Not Found!\n");

    fclose(fp);
}

void updateBooking()
{
    FILE *fp;
    struct Resort r;
    int id, found = 0;

    fp = fopen("resort.dat", "rb+");

    if(fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\nEnter Customer ID to Update: ");
    scanf("%d", &id);

    while(fread(&r, sizeof(r), 1, fp))
    {
        if(r.customerId == id)
        {
            found = 1;

            printf("\nEnter New Number of Days: ");
            scanf("%d", &r.days);

            printf("Enter New Rent Per Day: ");
            scanf("%f", &r.rentPerDay);

            fseek(fp, -sizeof(r), SEEK_CUR);
            fwrite(&r, sizeof(r), 1, fp);

            printf("\nRecord Updated Successfully!\n");
            break;
        }
    }

    if(!found)
        printf("\nRecord Not Found!\n");

    fclose(fp);
}

void deleteBooking()
{
    FILE *fp, *temp;
    struct Resort r;
    int id, found = 0;

    fp = fopen("resort.dat", "rb");

    if(fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    printf("\nEnter Customer ID to Delete: ");
    scanf("%d", &id);

    while(fread(&r, sizeof(r), 1, fp))
    {
        if(r.customerId == id)
        {
            found = 1;
        }
        else
        {
            fwrite(&r, sizeof(r), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("resort.dat");
    rename("temp.dat", "resort.dat");

    if(found)
        printf("\nBooking Deleted Successfully!\n");
    else
        printf("\nRecord Not Found!\n");
}

void generateBill()
{
    FILE *fp;
    struct Resort r;
    int id, found = 0;

    float roomRent, gst, totalBill;

    fp = fopen("resort.dat", "rb");

    if(fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\nEnter Customer ID: ");
    scanf("%d", &id);

    while(fread(&r, sizeof(r), 1, fp))
    {
        if(r.customerId == id)
        {
            found = 1;

            roomRent = r.days * r.rentPerDay;
            gst = roomRent * 0.18f;
            totalBill = roomRent + gst;

            printf("\n========== BILL ==========");
            printf("\nCustomer Name : %s", r.name);
            printf("\nRoom Number   : %d", r.roomNo);
            printf("\nDays Stayed   : %d", r.days);

            printf("\n\nRoom Rent     : %.2f", roomRent);
            printf("\nGST (18%%)     : %.2f", gst);
            printf("\nTotal Bill    : %.2f", totalBill);

            printf("\n==========================\n");
            break;
        }
    }

    if(!found)
        printf("\nRecord Not Found!\n");

    fclose(fp);
}