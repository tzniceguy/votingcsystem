#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

int main(void) {
    sqlite3 *db;
    char *err_message;
    int rc;

    // Opening the database and error handling
    rc = sqlite3_open("registration.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can not open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    // SQL statement to create the "students" table
    const char *create_table_sql = "CREATE TABLE IF NOT EXISTS students ("
                                   "id TEXT PRIMARY KEY,"
                                   "name TEXT NOT NULL,"
                                   "major TEXT,"
                                   "yos INTEGER"
                                   ");";

    // Execute the SQL statement to create the table
    rc = sqlite3_exec(db, create_table_sql, 0, 0, &err_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    /*
    Prompting the user to enter their details,
    where students will have to write their registration number, major (i.e., BIT), and year of study
    */

    char id[14];
    char name[50];
    char major[4];
    int yos;

    puts("Enter your registration number:");
    scanf("%s", id);
    puts("Enter your full name:");
    scanf("%s", name);
    puts("Enter your major (i.e., BCS/BTX/BAC/BIT):");
    scanf("%s", major);
    puts("Enter your year of study:");
    scanf("%d", &yos);

    // SQL statement to insert the user details into the "students" table
    char *insert_sql = sqlite3_mprintf("INSERT INTO students (id, name, major, yos) "
                                       "VALUES ('%s', '%s', '%s', '%d');",
                                       id, name, major, yos);

    // Execute the SQL statement to insert the user details
    rc = sqlite3_exec(db, insert_sql, 0, 0, &err_message);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
        sqlite3_close(db);
        return 1;
    }

    printf("User details inserted successfully.\n");

    sqlite3_close(db);
    return 0;
}
