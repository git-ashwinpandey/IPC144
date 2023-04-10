/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
Full Name  :
Student ID#:
Email      :
Section    :

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            menuAppointment(data);
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            //addAppointment(data->appointments, data->maxAppointments,
            //               data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            //removeAppointment(data->appointments, data->maxAppointments,
            //                  data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
// ---------------------------------------------------------------------------


// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int i;
    displayPatientTableHeader();
    for (i = 0; i<max; i++)
    {
        if (patient[i].patientNumber != 0)
        {
            if (fmt == FMT_FORM)
            {
                printf("Name  : %s\n"
                       "Number: %05d\n"
                       "Phone : ", patient[i].name, patient[i].patientNumber);
                displayFormattedPhone(patient[i].phone.number);
                printf(" (%s)\n", patient[i].phone.description);
            }
            else
            {
                printf("%05d %-15s ", patient[i].patientNumber,
                       patient[i].name);
                displayFormattedPhone(patient[i].phone.number);
                printf(" (%s)\n", patient[i].phone.description);
            }
        }

        /*else
        {
            printf("*** No recors found ***\n");
        }*/
    }
    printf("\n");
}


// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int userInput;
    printf("Search Options\n");
    printf("==========================\n");
    printf("1) By patient number\n");
    printf("2) By phone number\n");
    printf("..........................\n");
    printf("0) Previous menu\n");
    printf("..........................\n");

    printf("Selection: ");
    userInput = inputIntRange(0, 2);

    switch (userInput) {
        case 1:
            searchPatientByPatientNumber(patient, max);
            break;
        case 2:
            searchPatientByPhoneNumber(patient, max);
            break;
        default:
            printf("\n");
    }
}


// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
    int emptyIndex = -1, foundSlot = 1, i=0;

    while (foundSlot)
    {
        while (foundSlot && i < max)
        {
            if (patient[i].patientNumber == 0)
            {
                emptyIndex = i;
                foundSlot = 0;
            }
            i++;

            if (i == max)
            {
                foundSlot = 0;
            }
        }

    }

    if (emptyIndex == -1)
    {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
    else
    {
        patient[emptyIndex].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[emptyIndex]);
        printf("*** New patient record added ***\n\n");
    }
    //clearInputBuffer();
}


// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int userInput, patientFound;

    printf("Enter the patient number: ");
    userInput = inputInt();
    printf("\n");
    patientFound = findPatientIndexByPatientNum(userInput, patient, max);

    if (patientFound == -1)
    {
        printf("ERROR: Patient record not found!\n");
    }
    else
    {
        menuPatientEdit(&patient[patientFound]);
    }
}


// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
    int userInput, patientIndex;
    char yesNo, charOptions[2] = {'y', 'n'};

    printf("Enter the patient number: ");
    userInput = inputInt();

    patientIndex = findPatientIndexByPatientNum(userInput, patient, max);

    if (patientIndex == -1)
    {
        printf("\nERROR: Patient record not found!\n\n");
        clearInputBuffer();
    }
    else
    {
        printf("\n");
        displayPatientData(&patient[patientIndex], FMT_FORM);
        printf("\n");
        printf("Are you sure you want to remove this patient record? (y/n): ");
        yesNo = inputCharOption(charOptions);

        if (yesNo == 'y')
        {
            patient[patientIndex].patientNumber = 0;
            strcpy(patient[patientIndex].name,"");
            strcpy(patient[patientIndex].phone.number,"");
            strcpy(patient[patientIndex].phone.description, "");
            printf("Patient record has been removed!\n\n");
        }
        else
        {
            printf("Operation aborted.\n\n");
        }
        clearInputBuffer();
    }
}


// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData* clinicData)
{
    int i, patientIndex;
    displayScheduleTableHeader(&clinicData->appointments->date, 1);
    sortRecords(clinicData->appointments, clinicData->maxAppointments);
    
    for(i = 0; i<clinicData->maxPatient; i++)
    {
        patientIndex = findPatientIndexByPatientNum(clinicData->appointments[i].patientNumber, clinicData->patients, MAX_RECORD);
        if (patientIndex != -1)
        {
            displayScheduleData(&clinicData->patients[patientIndex], &clinicData->appointments[i], 1);
        }
        
    }
}


// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData* clinicData)
{
    int year, month, day, maxDay, patientIndex, i;
    printf("Year          : ");
    year = inputIntPositive();
    printf("Month (%d - %d): ", MIN_MONTH, MAX_MONTH);
    month = inputIntRange(MIN_MONTH, MAX_MONTH);
    maxDay = monthDays(year, month);
    printf("Day (%d - %d): ", MIN_DAY, maxDay);
    month = inputIntRange(MIN_DAY, maxDay);

    sortRecords(clinicData->appointments, clinicData->maxAppointments);
    displayScheduleTableHeader(&clinicData->appointments->date, 0);

    for (i = 0; i < clinicData->maxPatient; i++)
    {
        if (clinicData->appointments[i].date.year == year && clinicData->appointments[i].date.month && clinicData->appointments[i].date.day)
        {
            patientIndex = findPatientIndexByPatientNum(clinicData->appointments[i].patientNumber, clinicData->patients, MAX_RECORD);
            if (patientIndex != -1)
            {
                displayScheduleData(&clinicData->patients[patientIndex], &clinicData->appointments[i], 0);
            }
        }

    }
}


// Add an appointment record to the appointment array
// Todo:


// Remove an appointment record from the appointment array
// Todo:


//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int userInput;
    int patientIndex = -1;
    printf("\nSearch by patient number: ");
    userInput = inputInt();

    printf("\n");
    patientIndex = findPatientIndexByPatientNum(userInput, patient, max);

    if (patientIndex == -1)
    {
        printf("*** No records found ***\n\n");
        clearInputBuffer();
        suspend();
        searchPatientData(patient, max);
    }
    else {
        displayPatientData(&patient[patientIndex], FMT_FORM);
        printf("\n");
        clearInputBuffer();
        suspend();
        searchPatientData(patient, max);
    }
}


// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    char userString[11];
    int patientFound = 0, i;

    printf("\nSearch by phone number: ");
    inputCString(userString, 10, 10);
    printf("\n");
    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if(strcmp(userString,patient[i].phone.number) == 0)
        {
            displayPatientData(&patient[i], FMT_TABLE);
            patientFound++;
        }
    }

    if (patientFound == 0)
    {
        printf("\n*** No records found ***\n");
    }
    printf("\n");
    clearInputBuffer();
    suspend();
    searchPatientData(patient, max);
}

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int counter = 0, highestNo = 0, flag = 1;

    while (flag)
    {
        if (patient[counter].patientNumber != 0 && counter < max)
        {
            if (highestNo < patient[counter].patientNumber)
            {
                highestNo = patient[counter].patientNumber;
            }


        }
        if (counter == max)
        {
            flag = 0;
        }
        counter++;

    }

    return highestNo+1;
}


// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
                                 const struct Patient patient[], int max)
{
    int patientIndex = -1, i;

    for (i = 0; i < max; i++)
    {
        if(patientNumber == patient[i].patientNumber)
        {
            patientIndex = i;
        }
    }

    return patientIndex;
}



//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient* patient)
{
    char userName[NAME_LEN];
    printf("Patient Data Input\n");
    printf("------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    //scanf(" %[^\n]", userName);
    inputCString(userName, 1, NAME_LEN);

    printf("\n");
    strcpy(patient->name, userName);
    inputPhoneData(&patient->phone);

}


// Get user input for phone contact information
void inputPhoneData(struct Phone* phone)
{
    int userInput;
    char phoneInput[PHONE_LEN+1];
    printf("Phone Information\n");
    printf("-----------------\n");
    printf("How will the patient like to be contacted?\n");
    printf("1. Cell\n");
    printf("2. Home\n");
    printf("3. Work\n");
    printf("4. TBD\n");
    printf("Selection: ");
    userInput = inputInt();
    printf("\n");
    switch (userInput) {
        case 1:
            strcpy(phone->description, "CELL");
            printf("Contact: %s\n"
                   "Number : ", phone->description);
            clearInputBuffer();
            inputCString(phoneInput, 10, 10);
            strcpy(phone->number, phoneInput);
            printf("\n");
            break;
        case 2:
            strcpy(phone->description, "HOME");
            printf("Contact: %s\n"
                   "Number : ", phone->description);
            clearInputBuffer();
            inputCString(phoneInput, 10, 10);
            strcpy(phone->number, phoneInput);
            clearInputBuffer();
            printf("\n");
            break;
        case 3:
            strcpy(phone->description, "WORK");
            printf("Contact: %s\n"
                   "Number : ", phone->description);
            clearInputBuffer();
            inputCString(phoneInput, 10, 10);
            strcpy(phone->number, phoneInput);
            printf("\n");
            break;
        case 4:
            strcpy(phone->description, "TBD");
            strcpy(phone->number, phoneInput);
            clearInputBuffer();
            break;
        default:
            printf("\n");
    }


}


//Sort the appointment in ascending order.
//Since there are array with empty structure values, max appoitment counts down 
//till it reaches a value for which patient number isn't 0. That's starting point for our sorting 
//algorithm

void sortRecords(struct Appointment appoints[], int max)
{
    int i, j;
    struct Appointment temp;
    
    for (i = max-1; i > 0; i--)
    {
        if (appoints[i].patientNumber != 0)
        {
            for (j = 0; j < i; j++)
            {
                if (appoints[j].date.year > appoints[j + 1].date.year)
                {
                    temp = appoints[j];
                    appoints[j] = appoints[j + 1];
                    appoints[j + 1] = temp;
                }
                else if ((appoints[j].date.year == appoints[j + 1].date.year) && (appoints[j].date.month > appoints[j + 1].date.month))
                {
                    temp = appoints[j];
                    appoints[j] = appoints[j + 1];
                    appoints[j + 1] = temp;
                }
                else if ((appoints[j].date.year == appoints[j + 1].date.year) && (appoints[j].date.month == appoints[j + 1].date.month) && appoints[j].date.day > appoints[j + 1].date.day)
                {
                    temp = appoints[j];
                    appoints[j] = appoints[j + 1];
                    appoints[j + 1] = temp;
                }
                else if ((appoints[j].date.year == appoints[j + 1].date.year) &&
                    (appoints[j].date.month == appoints[j + 1].date.month) &&
                    appoints[j].date.day == appoints[j + 1].date.day && appoints[j].time.hour > appoints[j + 1].time.hour)
                {
                    temp = appoints[j];
                    appoints[j] = appoints[j + 1];
                    appoints[j + 1] = temp;
                }
                else if ((appoints[j].date.year == appoints[j + 1].date.year) &&
                    (appoints[j].date.month == appoints[j + 1].date.month) &&
                    appoints[j].date.day == appoints[j + 1].date.day && appoints[j].time.hour == appoints[j + 1].time.hour
                    && appoints[j].time.min > appoints[j + 1].time.min)
                {
                    temp = appoints[j];
                    appoints[j] = appoints[j + 1];
                    appoints[j + 1] = temp;
                }

            }
        }
        
    }
}

int monthDays(int year, int month)
{
    int days;
    switch (month) {
    case 2:
        if ((year % 4) == 0 && (year % 100) != 0 || (year % 400) == 0)
        {
            days = 29;
        }
        else
        {
            days = 28;
        }
        break;
    case 4:
    case 6:
    case 9:
    case 11:
        days = 30;
        break;
    default:
        days = 31;
        break;
    }
    return days;
}

//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char* datafile, struct Patient patients[], int max)
{
    int counter = 0;
    FILE *fp = NULL;
    fp = fopen(datafile,"r");

    if (fp != NULL)
    {
        while (fscanf(fp, "%d|%[^|]|%[^|]|%[^\n]", &patients[counter].patientNumber,
                      patients[counter].name, patients[counter].phone.description
                      , patients[counter].phone.number) != EOF && counter < max)

        {
            counter++;
        }
    }
    else
    {
        printf("Failed to open file\n");
    }
    fclose(fp);
    printf("%d\n", counter);
    return counter;
}



// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char* datafile, struct Appointment appoints[], int max)
{
    int counter = 0;
    FILE *fp = NULL;
    fp = fopen(datafile,"r");

    if (fp != NULL)
    {
        while (fscanf(fp, "%d,%d,%d,%d,%d,%d", &appoints[counter].patientNumber,
                      &appoints[counter].date.year, &appoints[counter].date.month,
                      &appoints[counter].date.day, &appoints[counter].time.hour,
                      &appoints[counter].time.min) != EOF && counter < max)

        {
            counter++;
        }
    }
    else
    {
        printf("Failed to open file\n");
    }
    fclose(fp);
    printf("%d\n", counter);
    return counter;
}

