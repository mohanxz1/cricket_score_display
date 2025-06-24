#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct for batsman data
struct batsman {
    char name[50]; 
    int runs, balls, ones, twos, threes, fours, sixes;
    float str; 
} pl1[100], pl3[100]; 

// Struct for bowler data
struct bowler {
    char name[50]; 
    int runsgv, wkttkn; 
    float overs;
    float econ; 
    int maiden_overs; 
} pl2[100], pl4[100];

// Global variables to store team names and dynamic filenames for the current match
char team1_name_global[50];
char team2_name_global[50];
char current_match_team1_batsman_file[150]; 
char current_match_team1_bowler_file[150];
char current_match_team2_batsman_file[150];
char current_match_team2_bowler_file[150];

// Store number of players for the current match
int num_batsmen_team1, num_bowlers_team1;
int num_batsmen_team2, num_bowlers_team2;

// Global variables for match details
char venue_global[100];
char date_input_global[50]; // To store date as input (dd,mm,yyyy)
char date_formatted_global[50]; // To store date as output (dd/mm/yyyy)
char toss_winner_global[50];
char toss_decision_global[50];

// Global variables for extras for each innings
int team1_innings_wides = 0; 
int team1_innings_no_balls = 0; 
int team1_innings_byes = 0; 
int team1_innings_leg_byes = 0; 

int team2_innings_wides = 0; 
int team2_innings_no_balls = 0; 
int team2_innings_byes = 0; 
int team2_innings_leg_byes = 0; 


// Function to read batsman data from a file into the provided array
void read_batsman_data(FILE *fp, struct batsman players[], int count) {
    rewind(fp); 
    for (int i = 0; i < count; i++) {
        int items_read = fscanf(fp, " \"%[^\"]\" %d %d %d %d %d %d %d %f",
                                 players[i].name, &players[i].runs, &players[i].balls,
                                 &players[i].ones, &players[i].twos, &players[i].threes,
                                 &players[i].fours, &players[i].sixes, &players[i].str);
        if (items_read != 9) {
            players[i].name[0] = '\0'; 
            printf("Warning: Incomplete batsman data read for player %d. Read %d items.\n", i + 1, items_read);
            break; 
        }
    }
}

// Function to read bowler data from a file into the provided array
void read_bowler_data(FILE *fp, struct bowler players[], int count) {
    rewind(fp); 
    for (int i = 0; i < count; i++) {
        int items_read = fscanf(fp, " \"%[^\"]\" %d %f %d %f %d",
                                 players[i].name, &players[i].runsgv, &players[i].overs,
                                 &players[i].wkttkn, &players[i].econ,
                                 &players[i].maiden_overs);
        if (items_read != 6) { 
            players[i].name[0] = '\0'; 
            printf("Warning: Incomplete bowler data read for player %d. Read %d items.\n", i + 1, items_read);
            break; 
        }
    }
}


int main() {
    int choice, i;
    FILE *fbat, *fball;

    // Get team names from the user
    printf("Enter Team 1 name: ");
    scanf(" %[^\n]s", team1_name_global);

    printf("Enter Team 2 name: ");
    scanf(" %[^\n]s", team2_name_global);

    printf("\n--- Match Details ---\n");
    printf("Enter Venue: ");
    scanf(" %[^\n]s", venue_global);
    printf("Enter Date (eg. dd,mm,yyyy): "); 
    scanf(" %[^\n]s", date_input_global);

    // Format the date input to dd/mm/yyyy
    int day, month, year;
    if (sscanf(date_input_global, "%d,%d,%d", &day, &month, &year) == 3) {
        sprintf(date_formatted_global, "%02d/%02d/%d", day, month, year);
    } else {
        strcpy(date_formatted_global, "Invalid Date"); 
    }

    printf("Enter Toss Winner (%s or %s): ", team1_name_global, team2_name_global);
    scanf(" %[^\n]s", toss_winner_global);
    printf("Enter Toss Decision (bat or bowl): ");
    scanf(" %[^\n]s", toss_decision_global);

    // Generate unique filenames for the current match
    sprintf(current_match_team1_batsman_file, "%s_vs_%s_team1_batsman.txt", team1_name_global, team2_name_global);
    sprintf(current_match_team1_bowler_file, "%s_vs_%s_team1_bowler.txt", team1_name_global, team2_name_global);
    sprintf(current_match_team2_batsman_file, "%s_vs_%s_team2_batsman.txt", team1_name_global, team2_name_global);
    sprintf(current_match_team2_bowler_file, "%s_vs_%s_team2_bowler.txt", team1_name_global, team2_name_global);

    // Determine batting order based on toss
    char *bat_first_team_name;
    char *bowl_first_team_name;
    struct batsman *bat_first_batsmen_array;
    struct bowler *bat_first_bowlers_array;
    struct batsman *bowl_first_batsmen_array;
    struct bowler *bowl_first_bowlers_array;
    int *num_bat_first_batsmen_ptr;
    int *num_bat_first_bowlers_ptr;
    int *num_bowl_first_batsmen_ptr;
    int *num_bowl_first_bowlers_ptr;
    char *bat_first_batsman_file;
    char *bat_first_bowler_file;
    char *bowl_first_batsman_file;
    char *bowl_first_bowler_file;
    int *bat_first_innings_wides_ptr;
    int *bat_first_innings_no_balls_ptr;
    int *bat_first_innings_byes_ptr;
    int *bat_first_innings_leg_byes_ptr;
    int *bowl_first_innings_wides_ptr;
    int *bowl_first_innings_no_balls_ptr;
    int *bowl_first_innings_byes_ptr;
    int *bowl_first_innings_leg_byes_ptr;


    // Assign pointers based on toss result
    if ((strcmp(toss_winner_global, team1_name_global) == 0 && strcmp(toss_decision_global, "bat") == 0) ||
        (strcmp(toss_winner_global, team2_name_global) == 0 && strcmp(toss_decision_global, "bowl") == 0)) {
        // Team 1 bats first
        bat_first_team_name = team1_name_global;
        bowl_first_team_name = team2_name_global;
        bat_first_batsmen_array = pl1;
        bowl_first_batsmen_array = pl3;
        bat_first_bowlers_array = pl2;
        bowl_first_bowlers_array = pl4;
        num_bat_first_batsmen_ptr = &num_batsmen_team1;
        num_bowl_first_batsmen_ptr = &num_batsmen_team2;
        num_bat_first_bowlers_ptr = &num_bowlers_team1;
        num_bowl_first_bowlers_ptr = &num_bowlers_team2;
        bat_first_batsman_file = current_match_team1_batsman_file;
        bat_first_bowler_file = current_match_team1_bowler_file;
        bowl_first_batsman_file = current_match_team2_batsman_file;
        bowl_first_bowler_file = current_match_team2_bowler_file;
        bat_first_innings_wides_ptr = &team1_innings_wides;
        bat_first_innings_no_balls_ptr = &team1_innings_no_balls;
        bat_first_innings_byes_ptr = &team1_innings_byes;
        bat_first_innings_leg_byes_ptr = &team1_innings_leg_byes;
        bowl_first_innings_wides_ptr = &team2_innings_wides; // Wides by 1st batting team's bowlers
        bowl_first_innings_no_balls_ptr = &team2_innings_no_balls;
        bowl_first_innings_byes_ptr = &team2_innings_byes;
        bowl_first_innings_leg_byes_ptr = &team2_innings_leg_byes;

    } else {
        // Team 2 bats first
        bat_first_team_name = team2_name_global;
        bowl_first_team_name = team1_name_global;
        bat_first_batsmen_array = pl3;
        bowl_first_batsmen_array = pl1;
        bat_first_bowlers_array = pl4;
        bowl_first_bowlers_array = pl2;
        num_bat_first_batsmen_ptr = &num_batsmen_team2;
        num_bowl_first_batsmen_ptr = &num_batsmen_team1;
        num_bat_first_bowlers_ptr = &num_bowlers_team2;
        num_bowl_first_bowlers_ptr = &num_bowlers_team1;
        bat_first_batsman_file = current_match_team2_batsman_file;
        bat_first_bowler_file = current_match_team2_bowler_file;
        bowl_first_batsman_file = current_match_team1_batsman_file;
        bowl_first_bowler_file = current_match_team1_bowler_file;
        bat_first_innings_wides_ptr = &team2_innings_wides;
        bat_first_innings_no_balls_ptr = &team2_innings_no_balls;
        bat_first_innings_byes_ptr = &team2_innings_byes;
        bat_first_innings_leg_byes_ptr = &team2_innings_leg_byes;
        bowl_first_innings_wides_ptr = &team1_innings_wides; // Wides by 1st batting team's bowlers
        bowl_first_innings_no_balls_ptr = &team1_innings_no_balls;
        bowl_first_innings_byes_ptr = &team1_innings_byes;
        bowl_first_innings_leg_byes_ptr = &team1_innings_leg_byes;
    }


    // --- Input and save data for the team batting first (1st Innings) ---
    printf("\nEnter number of batsmen for %s: ", bat_first_team_name);
    scanf("%d", num_bat_first_batsmen_ptr);
    fbat = fopen(bat_first_batsman_file, "w");
    if (fbat == NULL) {
        printf("Error opening %s for writing.\n", bat_first_batsman_file);
        return 1;
    }
    for (i = 0; i < *num_bat_first_batsmen_ptr; i++) {
        printf("\nEnter name of batsman %d: ", i + 1);
        scanf(" %[^\n]s", bat_first_batsmen_array[i].name);
        printf("Enter ones, twos, threes, fours, sixes: ");
        scanf("%d %d %d %d %d", &bat_first_batsmen_array[i].ones, &bat_first_batsmen_array[i].twos, &bat_first_batsmen_array[i].threes, &bat_first_batsmen_array[i].fours, &bat_first_batsmen_array[i].sixes);
        printf("Enter the balls played: ");
        scanf("%d", &bat_first_batsmen_array[i].balls);
        bat_first_batsmen_array[i].runs = (1 * bat_first_batsmen_array[i].ones) + (2 * bat_first_batsmen_array[i].twos) + (3 * bat_first_batsmen_array[i].threes) + (4 * bat_first_batsmen_array[i].fours) + (6 * bat_first_batsmen_array[i].sixes);
        bat_first_batsmen_array[i].str = (bat_first_batsmen_array[i].balls > 0) ? (bat_first_batsmen_array[i].runs * 100.0) / bat_first_batsmen_array[i].balls : 0;
        fprintf(fbat, "\"%s\" %d %d %d %d %d %d %d %.2f\n", bat_first_batsmen_array[i].name, bat_first_batsmen_array[i].runs, bat_first_batsmen_array[i].balls,
                        bat_first_batsmen_array[i].ones, bat_first_batsmen_array[i].twos, bat_first_batsmen_array[i].threes, bat_first_batsmen_array[i].fours, bat_first_batsmen_array[i].sixes, bat_first_batsmen_array[i].str);
    }
    fclose(fbat);

    // --- Input Extras for the team batting first (conceded by the team bowling first) ---
    printf("\n--- %s 1st Innings Extras ---\n", bat_first_team_name);
    printf("Enter Wides given by %s bowlers (against %s): ", bowl_first_team_name, bat_first_team_name);
    scanf("%d", bat_first_innings_wides_ptr);
    printf("Enter No-balls given by %s bowlers: ", bowl_first_team_name);
    scanf("%d", bat_first_innings_no_balls_ptr);
    printf("Enter Byes given by %s fielders: ", bowl_first_team_name);
    scanf("%d", bat_first_innings_byes_ptr);
    printf("Enter Leg-Byes given by %s fielders: ", bowl_first_team_name);
    scanf("%d", bat_first_innings_leg_byes_ptr);


    // --- Input and save data for the team bowling first (who bowls in 1st Innings) ---
    printf("\nEnter number of bowlers for %s: ", bowl_first_team_name);
    scanf("%d", num_bowl_first_bowlers_ptr);
    fball = fopen(bowl_first_bowler_file, "w");
    if (fball == NULL) {
        printf("Error opening %s for writing.\n", bowl_first_bowler_file);
        return 1;
    }
    for (i = 0; i < *num_bowl_first_bowlers_ptr; i++) {
        printf("\nEnter name of bowler %d: ", i + 1);
        scanf(" %[^\n]s", bowl_first_bowlers_array[i].name);
        printf("Enter runs given, overs bowled, wickets taken, maiden overs: "); 
        scanf("%d %f %d %d", &bowl_first_bowlers_array[i].runsgv, &bowl_first_bowlers_array[i].overs, &bowl_first_bowlers_array[i].wkttkn, &bowl_first_bowlers_array[i].maiden_overs);
        bowl_first_bowlers_array[i].econ = (bowl_first_bowlers_array[i].overs > 0) ? (bowl_first_bowlers_array[i].runsgv / bowl_first_bowlers_array[i].overs) : 0;
        fprintf(fball, "\"%s\" %d %.6f %d %.6f %d\n", bowl_first_bowlers_array[i].name, bowl_first_bowlers_array[i].runsgv, bowl_first_bowlers_array[i].overs, bowl_first_bowlers_array[i].wkttkn, bowl_first_bowlers_array[i].econ,
                        bowl_first_bowlers_array[i].maiden_overs); // Changed precision to %.6f
    }
    fclose(fball);


    // --- Input and save data for the team batting second (2nd Innings) ---
    printf("\nEnter number of batsmen for %s: ", bowl_first_team_name);
    scanf("%d", num_bowl_first_batsmen_ptr);
    fbat = fopen(bowl_first_batsman_file, "w");
    if (fbat == NULL) {
        printf("Error opening %s for writing.\n", bowl_first_batsman_file);
        return 1;
    }
    for (i = 0; i < *num_bowl_first_batsmen_ptr; i++) {
        printf("\nEnter name of batsman %d: ", i + 1);
        scanf(" %[^\n]s", bowl_first_batsmen_array[i].name);
        printf("Enter ones, twos, threes, fours, sixes: ");
        scanf("%d %d %d %d %d", &bowl_first_batsmen_array[i].ones, &bowl_first_batsmen_array[i].twos, &bowl_first_batsmen_array[i].threes, &bowl_first_batsmen_array[i].fours, &bowl_first_batsmen_array[i].sixes);
        printf("Enter the balls played: ");
        scanf("%d", &bowl_first_batsmen_array[i].balls);
        bowl_first_batsmen_array[i].runs = (1 * bowl_first_batsmen_array[i].ones) + (2 * bowl_first_batsmen_array[i].twos) + (3 * bowl_first_batsmen_array[i].threes) + (4 * bowl_first_batsmen_array[i].fours) + (6 * bowl_first_batsmen_array[i].sixes);
        bowl_first_batsmen_array[i].str = (bowl_first_batsmen_array[i].balls > 0) ? (bowl_first_batsmen_array[i].runs * 100.0) / bowl_first_batsmen_array[i].balls : 0;
        fprintf(fbat, "\"%s\" %d %d %d %d %d %d %d %.2f\n", bowl_first_batsmen_array[i].name, bowl_first_batsmen_array[i].runs, bowl_first_batsmen_array[i].balls,
                        bowl_first_batsmen_array[i].ones, bowl_first_batsmen_array[i].twos, bowl_first_batsmen_array[i].threes, bowl_first_batsmen_array[i].fours, bowl_first_batsmen_array[i].sixes, bowl_first_batsmen_array[i].str);
    }
    fclose(fbat);

    // --- Input Extras for the team batting second (conceded by the team bowling second) ---
    printf("\n--- %s 2nd Innings Extras ---\n", bowl_first_team_name);
    printf("Enter Wides given by %s bowlers (against %s): ", bat_first_team_name, bowl_first_team_name);
    scanf("%d", bowl_first_innings_wides_ptr);
    printf("Enter No-balls given by %s bowlers: ", bat_first_team_name);
    scanf("%d", bowl_first_innings_no_balls_ptr);
    printf("Enter Byes given by %s fielders: ", bat_first_team_name);
    scanf("%d", bowl_first_innings_byes_ptr);
    printf("Enter Leg-Byes given by %s fielders: ", bat_first_team_name);
    scanf("%d", bowl_first_innings_leg_byes_ptr);


    // --- Input and save data for the team bowling second (who bowls in 2nd Innings) ---
    printf("\nEnter number of bowlers for %s: ", bat_first_team_name);
    scanf("%d", num_bat_first_bowlers_ptr);
    fball = fopen(bat_first_bowler_file, "w");
    if (fball == NULL) {
        printf("Error opening %s for writing.\n", bat_first_bowler_file);
        return 1;
    }
    for (i = 0; i < *num_bat_first_bowlers_ptr; i++) {
        printf("\nEnter name of bowler %d: ", i + 1);
        scanf(" %[^\n]s", bat_first_bowlers_array[i].name);
        printf("Enter runs given, overs bowled, wickets taken, maiden overs: "); 
        scanf("%d %f %d %d", &bat_first_bowlers_array[i].runsgv, &bat_first_bowlers_array[i].overs, &bat_first_bowlers_array[i].wkttkn, &bat_first_bowlers_array[i].maiden_overs);
        bat_first_bowlers_array[i].econ = (bat_first_bowlers_array[i].overs > 0) ? (bat_first_bowlers_array[i].runsgv / bat_first_bowlers_array[i].overs) : 0;
        fprintf(fball, "\"%s\" %d %.6f %d %.6f %d\n", bat_first_bowlers_array[i].name, bat_first_bowlers_array[i].runsgv, bat_first_bowlers_array[i].overs, bat_first_bowlers_array[i].wkttkn, bat_first_bowlers_array[i].econ,
                        bat_first_bowlers_array[i].maiden_overs); // Changed precision to %.6f
    }
    fclose(fball);


    printf("\nAll details recorded and saved to files.\n"); // This message is intentionally kept as it confirms file operations

    // Main menu loop
    while (1) {
        printf("\n========== MENU ==========\n");
        printf("1. %s Batsman Details\n", team1_name_global);
        printf("2. %s Batsman Details\n", team2_name_global);
        printf("3. %s Bowler Details\n", team1_name_global);
        printf("4. %s Bowler Details\n", team2_name_global);
        printf("5. Match Summary\n");
        printf("6. Exit\n");
        printf("==========================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        int plno; // Player number

        switch (choice) {
            case 1: // Display Team 1 Batsman Details
                printf("\nEnter the batsman number to see details: ");
                scanf("%d", &plno);
                if (plno < 1 || plno > num_batsmen_team1) {
                    printf("Invalid batsman number!\n");
                    break;
                }
                plno--; 

                fbat = fopen(current_match_team1_batsman_file, "r");
                if (fbat == NULL) {
                    printf("Error opening %s for reading.\n", current_match_team1_batsman_file);
                    break;
                }
                read_batsman_data(fbat, pl1, num_batsmen_team1);
                fclose(fbat);

                if (pl1[plno].name[0] != '\0') {
                    printf("\nBatsman Details - %s\n", team1_name_global);
                    printf("--------------------------------------------------------\n");
                    printf(" Name                 Runs  Balls  Fours  Sixes  SR\n"); 
                    printf("--------------------------------------------------------\n");
                    printf(" %-20s %-5d %-6d %-6d %-6d %-7.2f\n", 
                           pl1[plno].name, pl1[plno].runs, pl1[plno].balls, pl1[plno].fours, pl1[plno].sixes, pl1[plno].str);
                } else {
                    printf("Could not retrieve details for batsman %d.\n", plno + 1);
                }
                break;

            case 2: // Display Team 2 Batsman Details
                printf("\nEnter the batsman number to see details: ");
                scanf("%d", &plno);
                if (plno < 1 || plno > num_batsmen_team2) {
                    printf("Invalid batsman number!\n");
                    break;
                }
                plno--;

                fbat = fopen(current_match_team2_batsman_file, "r");
                if (fbat == NULL) {
                    printf("Error opening %s for reading.\n", current_match_team2_batsman_file);
                    break;
                }
                read_batsman_data(fbat, pl3, num_batsmen_team2);
                fclose(fbat);

                if (pl3[plno].name[0] != '\0') {
                    printf("\nBatsman Details - %s\n", team2_name_global);
                    printf("--------------------------------------------------------\n");
                    printf(" Name                 Runs  Balls  Fours  Sixes  SR\n"); 
                    printf("--------------------------------------------------------\n");
                    printf(" %-20s %-5d %-6d %-6d %-6d %-7.2f\n", 
                           pl3[plno].name, pl3[plno].runs, pl3[plno].balls, pl3[plno].fours, pl3[plno].sixes, pl3[plno].str);
                } else {
                    printf("Could not retrieve details for batsman %d.\n", plno + 1);
                }
                break;

            case 3: // Display Team 1 Bowler Details
                printf("\nEnter the bowler number to see details: ");
                scanf("%d", &plno);
                if (plno < 1 || plno > num_bowlers_team1) {
                    printf("Invalid bowler number!\n");
                    break;
                }
                plno--;

                fball = fopen(current_match_team1_bowler_file, "r");
                if (fball == NULL) {
                    printf("Error opening %s for reading.\n", current_match_team1_bowler_file);
                    break;
                }
                read_bowler_data(fball, pl2, num_bowlers_team1);
                fclose(fball);

                if (pl2[plno].name[0] != '\0') {
                    printf("\nBowler Details - %s\n", team1_name_global);
                    printf("------------------------------------------------------------\n"); // Adjusted width
                    printf(" Name                 Overs  Runs  Wickets  Maidens  Economy\n"); 
                    printf("------------------------------------------------------------\n"); // Adjusted width
                    printf(" %-20s %-6.1f %-5d %-8d %-8d %-8.2f\n", 
                           pl2[plno].name, pl2[plno].overs, pl2[plno].runsgv, pl2[plno].wkttkn, pl2[plno].maiden_overs, pl2[plno].econ);
                } else {
                    printf("Could not retrieve details for bowler %d.\n", plno + 1);
                }
                break;

            case 4: // Display Team 2 Bowler Details
                printf("\nEnter the bowler number to see details: ");
                scanf("%d", &plno);
                if (plno < 1 || plno > num_bowlers_team2) {
                    printf("Invalid bowler number!\n");
                    break;
                }
                plno--;

                fball = fopen(current_match_team2_bowler_file, "r");
                if (fball == NULL) {
                    printf("Error opening %s for reading.\n", current_match_team2_bowler_file);
                    break;
                }
                read_bowler_data(fball, pl4, num_bowlers_team2);
                fclose(fball);

                if (pl4[plno].name[0] != '\0') {
                    printf("\nBowler Details - %s\n", team2_name_global);
                    printf("------------------------------------------------------------\n"); // Adjusted width
                    printf(" Name                 Overs  Runs  Wickets  Maidens  Economy\n"); 
                    printf("------------------------------------------------------------\n"); // Adjusted width
                    printf(" %-20s %-6.1f %-5d %-8d %-8d %-8.2f\n", 
                           pl4[plno].name, pl4[plno].overs, pl4[plno].runsgv, pl4[plno].wkttkn, pl4[plno].maiden_overs, pl4[plno].econ);
                } else {
                    printf("Could not retrieve details for bowler %d.\n", plno + 1);
                }
                break;

            case 5: { // Display and Save Match Summary
                int total_runs_team1_innings = 0;
                int total_wickets_team1_innings = 0;
                float total_overs_team2_bowled = 0.0; 

                int total_runs_team2_innings = 0;
                int total_wickets_team2_innings = 0;
                float total_overs_team1_bowled = 0.0; 

                int max_runs_team1 = -1; 
                int max_wkts_bowler_team1 = -1; 

                int max_runs_team2 = -1; 
                int max_wkts_bowler_team2 = -1; 
                
                printf("\n============================================\n");
                printf("           MATCH SUMMARY\n");
                printf("============================================\n");

                printf("\n%s vs %s\n", team1_name_global, team2_name_global);
                printf("Venue: %s\n", venue_global);
                printf("Date: %s\n", date_formatted_global); 
                printf("Toss: %s won the toss and elected to %s\n", toss_winner_global, toss_decision_global);


                // --- Team 1 (Nepal) 1st Innings 
                printf("\n--- %s 1st Innings ---\n", bat_first_team_name); 
                
                fbat = fopen(bat_first_batsman_file, "r"); 
                if (fbat == NULL) {
                    printf("Error reading %s.\n", bat_first_batsman_file);
                    break;
                }
                read_batsman_data(fbat, bat_first_batsmen_array, *num_bat_first_batsmen_ptr); 
                fclose(fbat);

                printf("\n%s Batsman Performance:\n", bat_first_team_name); 
                printf("--------------------------------------------------------\n");
                printf(" Name                 Runs  Balls  Fours  Sixes  SR\n"); 
                printf("--------------------------------------------------------\n");
                for (i = 0; i < *num_bat_first_batsmen_ptr; i++) { 
                    if (bat_first_batsmen_array[i].name[0] != '\0') { 
                        printf(" %-20s %-5d %-6d %-6d %-6d %-7.2f\n", 
                               bat_first_batsmen_array[i].name, bat_first_batsmen_array[i].runs, bat_first_batsmen_array[i].balls, bat_first_batsmen_array[i].fours, bat_first_batsmen_array[i].sixes, bat_first_batsmen_array[i].str);
                        total_runs_team1_innings += bat_first_batsmen_array[i].runs; 
                        if (bat_first_batsmen_array[i].runs > max_runs_team1) { 
                            max_runs_team1 = bat_first_batsmen_array[i].runs; 
                        }
                    }
                }

                // Team 2 (USA) Bowler Performance 
                fball = fopen(bowl_first_bowler_file, "r"); 
                if (fball == NULL) {
                    printf("Error reading %s.\n", bowl_first_bowler_file);
                    break;
                }
                read_bowler_data(fball, bowl_first_bowlers_array, *num_bowl_first_bowlers_ptr); 
                fclose(fball);

                printf("\n%s Bowler Performance:\n", bowl_first_team_name); 
                printf("------------------------------------------------------------\n"); // Adjusted width
                printf(" Name                 Overs  Runs  Wickets  Maidens  Economy\n"); 
                printf("------------------------------------------------------------\n"); // Adjusted width
                for (i = 0; i < *num_bowl_first_bowlers_ptr; i++) { 
                    if (bowl_first_bowlers_array[i].name[0] != '\0') { 
                        printf(" %-20s %-6.1f %-5d %-8d %-8d %-8.2f\n", 
                               bowl_first_bowlers_array[i].name, bowl_first_bowlers_array[i].overs, bowl_first_bowlers_array[i].runsgv, bowl_first_bowlers_array[i].wkttkn, bowl_first_bowlers_array[i].maiden_overs, bowl_first_bowlers_array[i].econ);
                        total_wickets_team1_innings += bowl_first_bowlers_array[i].wkttkn; 
                        total_overs_team2_bowled += bowl_first_bowlers_array[i].overs;
                        if (bowl_first_bowlers_array[i].wkttkn > max_wkts_bowler_team2) { 
                            max_wkts_bowler_team2 = bowl_first_bowlers_array[i].wkttkn; 
                        }
                    }
                }

                // Add extras conceded by Team 2 bowlers to Team 1's total score
                total_runs_team1_innings += *bat_first_innings_wides_ptr;
                total_runs_team1_innings += *bat_first_innings_no_balls_ptr;
                total_runs_team1_innings += *bat_first_innings_byes_ptr;
                total_runs_team1_innings += *bat_first_innings_leg_byes_ptr;

                printf("\n%s 1st Innings Totals:\n", bat_first_team_name); 
                printf("Total Score: %d/%d\n", total_runs_team1_innings, total_wickets_team1_innings); 
                printf("Extras: %d (Wides: %d, No-Balls: %d, Byes: %d, Leg Byes: %d)\n",
                       *bat_first_innings_wides_ptr + *bat_first_innings_no_balls_ptr + *bat_first_innings_byes_ptr + *bat_first_innings_leg_byes_ptr,
                       *bat_first_innings_wides_ptr, *bat_first_innings_no_balls_ptr, *bat_first_innings_byes_ptr, *bat_first_innings_leg_byes_ptr);
                printf("Highest Batsman Score (%s): %d\n", bat_first_team_name, (max_runs_team1 == -1 ? 0 : max_runs_team1)); 
                printf("Best Bowling (%s): %d Wickets\n", bowl_first_team_name, (max_wkts_bowler_team2 == -1 ? 0 : max_wkts_bowler_team2)); 

                // --- Team 2 (USA) 2nd Innings 
                printf("\n--- %s 2nd Innings ---\n", bowl_first_team_name); 

                fbat = fopen(bowl_first_batsman_file, "r"); 
                if (fbat == NULL) {
                    printf("Error reading %s.\n", bowl_first_batsman_file);
                    break;
                }
                read_batsman_data(fbat, bowl_first_batsmen_array, *num_bowl_first_batsmen_ptr); 
                fclose(fbat);

                printf("\n%s Batsman Performance:\n", bowl_first_team_name); 
                printf("--------------------------------------------------------\n");
                printf(" Name                 Runs  Balls  Fours  Sixes  SR\n"); 
                printf("--------------------------------------------------------\n");
                for (i = 0; i < *num_bowl_first_batsmen_ptr; i++) { 
                    if (bowl_first_batsmen_array[i].name[0] != '\0') { 
                        printf(" %-20s %-5d %-6d %-6d %-6d %-7.2f\n", 
                               bowl_first_batsmen_array[i].name, bowl_first_batsmen_array[i].runs, bowl_first_batsmen_array[i].balls, bowl_first_batsmen_array[i].fours, bowl_first_batsmen_array[i].sixes, bowl_first_batsmen_array[i].str);
                        total_runs_team2_innings += bowl_first_batsmen_array[i].runs; 
                        if (bowl_first_batsmen_array[i].runs > max_runs_team2) { 
                            max_runs_team2 = bowl_first_batsmen_array[i].runs;
                        }
                    }
                }

                // Team 1 (Nepal) Bowler Performance 
                fball = fopen(bat_first_bowler_file, "r"); 
                if (fball == NULL) {
                    printf("Error reading %s.\n", bat_first_bowler_file);
                    break;
                }
                read_bowler_data(fball, bat_first_bowlers_array, *num_bat_first_bowlers_ptr); 
                fclose(fball);

                printf("\n%s Bowler Performance:\n", bat_first_team_name); 
                printf("------------------------------------------------------------\n"); // Adjusted width
                printf(" Name                 Overs  Runs  Wickets  Maidens  Economy\n"); 
                printf("------------------------------------------------------------\n"); // Adjusted width
                for (i = 0; i < *num_bat_first_bowlers_ptr; i++) { 
                    if (bat_first_bowlers_array[i].name[0] != '\0') { 
                        printf(" %-20s %-6.1f %-5d %-8d %-8d %-8.2f\n", 
                               bat_first_bowlers_array[i].name, bat_first_bowlers_array[i].overs, bat_first_bowlers_array[i].runsgv, bat_first_bowlers_array[i].wkttkn, bat_first_bowlers_array[i].maiden_overs, bat_first_bowlers_array[i].econ);
                        total_wickets_team2_innings += bat_first_bowlers_array[i].wkttkn; 
                        total_overs_team1_bowled += bat_first_bowlers_array[i].overs;
                        if (bat_first_bowlers_array[i].wkttkn > max_wkts_bowler_team1) {
                            max_wkts_bowler_team1 = bat_first_bowlers_array[i].wkttkn;
                        }
                    }
                }

                // Add extras conceded by Team 1 bowlers to Team 2's total score
                total_runs_team2_innings += *bowl_first_innings_wides_ptr;
                total_runs_team2_innings += *bowl_first_innings_no_balls_ptr;
                total_runs_team2_innings += *bowl_first_innings_byes_ptr;
                total_runs_team2_innings += *bowl_first_innings_leg_byes_ptr;

                printf("\n%s 2nd Innings Totals:\n", bowl_first_team_name); 
                printf("Total Score: %d/%d\n", total_runs_team2_innings, total_wickets_team2_innings); 
                printf("Extras: %d (Wides: %d, No-Balls: %d, Byes: %d, Leg Byes: %d)\n",
                       *bowl_first_innings_wides_ptr + *bowl_first_innings_no_balls_ptr + *bowl_first_innings_byes_ptr + *bowl_first_innings_leg_byes_ptr,
                       *bowl_first_innings_wides_ptr, *bowl_first_innings_no_balls_ptr, *bowl_first_innings_byes_ptr, *bowl_first_innings_leg_byes_ptr);
                printf("Highest Batsman Score (%s): %d\n", bowl_first_team_name, (max_runs_team2 == -1 ? 0 : max_runs_team2));
                printf("Best Bowling (%s): %d Wickets\n", bat_first_team_name, (max_wkts_bowler_team1 == -1 ? 0 : max_wkts_bowler_team1));


                printf("\n--- RESULT ---\n");
                // Compare scores based on who batted first
                if (strcmp(bat_first_team_name, team1_name_global) == 0) {
                    // Team 1 batted first
                    if (total_runs_team1_innings > total_runs_team2_innings) {
                        printf("%s won by %d runs.\n", team1_name_global, total_runs_team1_innings - total_runs_team2_innings);
                    } else if (total_runs_team2_innings > total_runs_team1_innings) {
                        printf("%s won by %d runs.\n", team2_name_global, total_runs_team2_innings - total_runs_team1_innings);
                    } else {
                        printf("Match Tied.\n");
                    }
                } else {
                    // Team 2 batted first
                    if (total_runs_team2_innings > total_runs_team1_innings) {
                        printf("%s won by %d runs.\n", team2_name_global, total_runs_team2_innings - total_runs_team1_innings);
                    } else if (total_runs_team1_innings > total_runs_team2_innings) {
                        printf("%s won by %d runs.\n", team1_name_global, total_runs_team1_innings - total_runs_team2_innings);
                    } else {
                        printf("Match Tied.\n");
                    }
                }

                // Write summary to a central all_match_summaries.txt file in APPEND mode
                FILE *fsummary = fopen("all_match_summaries.txt", "a");
                if (fsummary != NULL) {
                    fprintf(fsummary, "\n============================================\n");
                    fprintf(fsummary, "           MATCH SUMMARY\n");
                    fprintf(fsummary, "============================================\n");
                    fprintf(fsummary, "\n%s vs %s\n", team1_name_global, team2_name_global);
                    fprintf(fsummary, "Venue: %s\n", venue_global);
                    fprintf(fsummary, "Date: %s\n", date_formatted_global);
                    fprintf(fsummary, "Toss: %s won the toss and elected to %s\n", toss_winner_global, toss_decision_global);

                    // 1st Innings Summary (Dynamic Team)
                    fprintf(fsummary, "\n--- %s 1st Innings ---\n", bat_first_team_name);
                    fprintf(fsummary, "\n%s Batsman Performance:\n", bat_first_team_name);
                    fprintf(fsummary, "--------------------------------------------------------\n");
                    fprintf(fsummary, " Name                 Runs  Balls  Fours  Sixes  SR\n"); 
                    fprintf(fsummary, "--------------------------------------------------------\n");
                    for (i = 0; i < *num_bat_first_batsmen_ptr; i++) {
                        if (bat_first_batsmen_array[i].name[0] != '\0') {
                            fprintf(fsummary, " %-20s %-5d %-6d %-6d %-6d %-7.2f\n",
                                    bat_first_batsmen_array[i].name, bat_first_batsmen_array[i].runs, bat_first_batsmen_array[i].balls, bat_first_batsmen_array[i].fours, bat_first_batsmen_array[i].sixes, bat_first_batsmen_array[i].str);
                        }
                    }
                    fprintf(fsummary, "\n%s Bowler Performance:\n", bowl_first_team_name);
                    fprintf(fsummary, "------------------------------------------------------------\n"); // Adjusted width
                    fprintf(fsummary, " Name                 Overs  Runs  Wickets  Maidens  Economy\n"); 
                    fprintf(fsummary, "------------------------------------------------------------\n"); // Adjusted width
                    for (i = 0; i < *num_bowl_first_bowlers_ptr; i++) {
                        if (bowl_first_bowlers_array[i].name[0] != '\0') {
                            fprintf(fsummary, " %-20s %-6.1f %-5d %-8d %-8d %-8.2f\n",
                                    bowl_first_bowlers_array[i].name, bowl_first_bowlers_array[i].overs, bowl_first_bowlers_array[i].runsgv, bowl_first_bowlers_array[i].wkttkn, bowl_first_bowlers_array[i].maiden_overs, bowl_first_bowlers_array[i].econ);
                        }
                    }
                    fprintf(fsummary, "\n%s 1st Innings Totals:\n", bat_first_team_name);
                    fprintf(fsummary, "Total Score: %d/%d\n", total_runs_team1_innings, total_wickets_team1_innings); // Removed (X.X Overs)
                    fprintf(fsummary, "Extras: %d (Wides: %d, No-Balls: %d, Byes: %d, Leg Byes: %d)\n",
                            *bat_first_innings_wides_ptr + *bat_first_innings_no_balls_ptr + *bat_first_innings_byes_ptr + *bat_first_innings_leg_byes_ptr,
                            *bat_first_innings_wides_ptr, *bat_first_innings_no_balls_ptr, *bat_first_innings_byes_ptr, *bat_first_innings_leg_byes_ptr);
                    fprintf(fsummary, "Highest Batsman Score (%s): %d\n", bat_first_team_name, (max_runs_team1 == -1 ? 0 : max_runs_team1));
                    fprintf(fsummary, "Best Bowling (%s): %d Wickets\n", bowl_first_team_name, (max_wkts_bowler_team2 == -1 ? 0 : max_wkts_bowler_team2));

                    // 2nd Innings Summary (Dynamic Team)
                    fprintf(fsummary, "\n--- %s 2nd Innings ---\n", bowl_first_team_name);
                     fprintf(fsummary, "\n%s Batsman Performance:\n", bowl_first_team_name);
                    fprintf(fsummary, "--------------------------------------------------------\n");
                    fprintf(fsummary, " Name                 Runs  Balls  Fours  Sixes  SR\n"); 
                    fprintf(fsummary, "--------------------------------------------------------\n");
                    for (i = 0; i < *num_bowl_first_batsmen_ptr; i++) {
                        if (bowl_first_batsmen_array[i].name[0] != '\0') {
                            fprintf(fsummary, " %-20s %-5d %-6d %-6d %-6d %-7.2f\n",
                                    bowl_first_batsmen_array[i].name, bowl_first_batsmen_array[i].runs, bowl_first_batsmen_array[i].balls, bowl_first_batsmen_array[i].fours, bowl_first_batsmen_array[i].sixes, bowl_first_batsmen_array[i].str);
                        }
                    }
                    fprintf(fsummary, "\n%s Bowler Performance:\n", bat_first_team_name);
                    fprintf(fsummary, "------------------------------------------------------------\n"); // Adjusted width
                    fprintf(fsummary, " Name                 Overs  Runs  Wickets  Maidens  Economy\n"); 
                    fprintf(fsummary, "------------------------------------------------------------\n"); // Adjusted width
                    for (i = 0; i < *num_bat_first_bowlers_ptr; i++) {
                        if (bat_first_bowlers_array[i].name[0] != '\0') {
                            fprintf(fsummary, " %-20s %-6.1f %-5d %-8d %-8d %-8.2f\n",
                                    bat_first_bowlers_array[i].name, bat_first_bowlers_array[i].overs, bat_first_bowlers_array[i].runsgv, bat_first_bowlers_array[i].wkttkn, bat_first_bowlers_array[i].maiden_overs, bat_first_bowlers_array[i].econ);
                        }
                    }
                    fprintf(fsummary, "\n%s 2nd Innings Totals:\n", bowl_first_team_name);
                    fprintf(fsummary, "Total Score: %d/%d\n", total_runs_team2_innings, total_wickets_team2_innings); 
                    fprintf(fsummary, "Extras: %d (Wides: %d, No-Balls: %d, Byes: %d, Leg Byes: %d)\n",
                            *bowl_first_innings_wides_ptr + *bowl_first_innings_no_balls_ptr + *bowl_first_innings_byes_ptr + *bowl_first_innings_leg_byes_ptr,
                            *bowl_first_innings_wides_ptr, *bowl_first_innings_no_balls_ptr, *bowl_first_innings_byes_ptr, *bowl_first_innings_leg_byes_ptr);
                    fprintf(fsummary, "Highest Batsman Score (%s): %d\n", bowl_first_team_name, (max_runs_team2 == -1 ? 0 : max_runs_team2));
                    fprintf(fsummary, "Best Bowling (%s): %d Wickets\n", bat_first_team_name, (max_wkts_bowler_team1 == -1 ? 0 : max_wkts_bowler_team1));


                    fprintf(fsummary, "\n--- RESULT ---\n");
                     if (strcmp(bat_first_team_name, team1_name_global) == 0) {
                        if (total_runs_team1_innings > total_runs_team2_innings) {
                            fprintf(fsummary, "%s won by %d runs.\n", team1_name_global, total_runs_team1_innings - total_runs_team2_innings);
                        } else if (total_runs_team2_innings > total_runs_team1_innings) {
                            fprintf(fsummary, "%s won by %d runs.\n", team2_name_global, total_runs_team2_innings - total_runs_team1_innings);
                        } else {
                            fprintf(fsummary, "Match Tied.\n");
                        }
                    } else {
                        if (total_runs_team2_innings > total_runs_team1_innings) {
                            fprintf(fsummary, "%s won by %d runs.\n", team2_name_global, total_runs_team2_innings - total_runs_team1_innings);
                        } else if (total_runs_team1_innings > total_runs_team2_innings) {
                            fprintf(fsummary, "%s won by %d runs.\n", team1_name_global, total_runs_team1_innings - total_runs_team2_innings);
                        } else {
                            fprintf(fsummary, "Match Tied.\n");
                        }
                    }
                    fclose(fsummary);
                } else {
                    printf("Unable to open all_match_summaries.txt for writing.\n");
                }
                break;
            }

            case 6: 
                printf("Exiting program...\n");
                exit(0);
                break;

            default: 
                printf("Enter a valid choice!\n");
                break;
        }
    }
    return 0;
}
