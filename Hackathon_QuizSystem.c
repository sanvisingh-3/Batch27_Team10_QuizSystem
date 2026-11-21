#include <stdio.h>
struct Question 
{
    char text[100];
    char optA[50];
    char optB[50];
    char optC[50];
    char optD[50];
    char correct;
};

int main() 
{
    struct Question quiz[20];
    int mainCh, subCh, modeCh, negMark, numQ;
    char userAns;
    char name[50];
    float score, percentage;
    char *subName;
    FILE *fp;

    while (1) 
	{
        printf("\n========================================\n");
        printf("   QUIZ & SCORE MANAGEMENT SYSTEM   \n");
        printf("========================================\n");
        printf("1. Start Quiz\n");
        printf("2. View Previous Results\n");
        printf("3. Exit\n");
        printf("Enter your choice (1-3): ");
        scanf("%d", &mainCh);

        if (mainCh == 1) 
		{
            score = 0.0;

            printf("\nEnter your name: ");
            scanf("%s", name);

            printf("\nChoose a Subject:\n");
            printf("1. Physics\n");
            printf("2. Maths\n");
            printf("3. Computer\n");
            printf("Enter your choice (1-3): ");
            scanf("%d", &subCh);

            if (subCh == 1) 
			{
                fp = fopen("physics.txt", "r");
                subName = "Physics";
            } else if (subCh == 2) 
			{
                fp = fopen("maths.txt", "r");
                subName = "Maths";
            } else if (subCh == 3) 
			{
                fp = fopen("computer.txt", "r");
                subName = "Computer";
            } else 
			{
                printf("\nInvalid subject choice! Returning to main menu...\n");
                continue;
            }

            if (fp == NULL) 
			{
                printf("\nError: Question file not found!\n");
                continue;
            }

            for (int i = 0; i < 20; i++) 
			{
                fgets(quiz[i].text, 100, fp);
                fgets(quiz[i].optA, 50, fp);
                fgets(quiz[i].optB, 50, fp);
                fgets(quiz[i].optC, 50, fp);
                fgets(quiz[i].optD, 50, fp);
                fscanf(fp, " %c\n", &quiz[i].correct);
            }
            fclose(fp);

            printf("\nHow many questions do you want to attempt (1-20)? ");
            scanf("%d", &numQ);

            if (numQ < 1 || numQ > 20) 
			{
                printf("\nInvalid number of questions! Returning to main menu...\n");
                continue;
            }

            printf("\nSelect Scoring Mode:\n");
            printf("1. Normal Scoring (+1 / 0)\n");
            printf("2. Negative Marking (+1 / -0.25)\n");
            printf("Enter your choice (1-2): ");
            scanf("%d", &modeCh);

            switch (modeCh) 
			{
                case 1:
                case 2:
                    negMark = (modeCh == 2) ? 1 : 0;

                    for (int q = 0; q < numQ; q++) 
					{
                        printf("\n%s", quiz[q].text);
                        printf(" %s", quiz[q].optA);
                        printf(" %s", quiz[q].optB);
                        printf(" %s", quiz[q].optC);
                        printf(" %s", quiz[q].optD);

                        while (1) 
						{
                            printf("Your Answer (A/B/C/D): ");
                            scanf(" %c", &userAns);

                            if (userAns >= 'a' && userAns <= 'z') 
							{
                                userAns = userAns - 32;
                            }
                            if (userAns == 'A' || userAns == 'B' || userAns == 'C' || userAns == 'D') 
							{
                                break;
                            }
                            printf("Invalid option! Please enter A, B, C, or D.\n");
                        }

                        if (userAns == quiz[q].correct) 
						{
                            printf("-> Correct! (+1.00)\n");
                            score += 1.0;
                        } 
						else 
						{
                            printf("-> Wrong! Correct answer is %c.\n", quiz[q].correct);
                            if (negMark == 1) 
							{
                                score -= 0.25;
                            }
                        }
                    }

                    if (score < 0) 
					{
                        score = 0.0;
                    }
                    percentage = (score / numQ) * 100.0;

                    printf("\n========================================\n");
                    printf("             FINAL REPORT             \n");
                    printf("========================================\n");
                    printf("Name        : %s\n", name);
                    printf("Subject     : %s\n", subName);
                    printf("Attempted   : %d Questions\n", numQ);
                    printf("Final Score : %.2f / %d.00\n", score, numQ);
                    printf("Percentage  : %.2f%%\n", percentage);

                    if (percentage >= 80.0) 
					{
                        printf("Performance : Excellent\n");
                    } 
					else if (percentage >= 60.0) 
					{
                        printf("Performance : Good\n");
                    } 
					else if (percentage >= 40.0) 
					{
                        printf("Performance : Average\n");
                    } 
					else 
					{
                        printf("Performance : Needs Improvement\n");
                    }

                    // To save results in results.txt file 
                    fp = fopen("results.txt", "a");
                    if (fp != NULL) 
					{
                        fprintf(fp, "Name: %s | Subject: %s | Attempted: %d | Score: %.2f / %d.00 | Percentage: %.2f%%\n", name, subName, numQ, score, numQ, percentage);
                        fclose(fp);
                    }
                    break;

                default:
                    printf("\nInvalid mode choice! Returning to main menu...\n");
                    break;
            }

        } 
		else if (mainCh == 2) 
		{
            printf("\n========================================\n");
            printf("           PREVIOUS RESULTS             \n");
            printf("========================================\n");
            fp = fopen("results.txt", "r");
            if (fp == NULL) {
                printf("No previous results found! Play a quiz first.\n");
            } else {
                char line[200];
                while (fgets(line, sizeof(line), fp)) {
                    printf("%s", line);
                }
                fclose(fp);
            }

        } 
		else if (mainCh == 3) 
		{
            printf("\nThank you for using Quiz System! Exiting...\n");
            break;

        } 
		else 
		{
            printf("\nInvalid choice! Please enter 1, 2, or 3.\n");
        }
    }

    return 0;
}
