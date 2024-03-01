#include "tlpi_hdr.h"
#include "stdio.h"
int
main(int argc, char *argv[])
{
    char *argVec[10];           /* Larger than required */
    char *envVec[] = { "GREET=salut", "BYE=adieu", NULL };

    if (argc != 2 || strcmp(argv[1], "--help") == 0)
        // usageErr("%s pathname\n", argv[0]);
        printf("usage: %s pathname\n", argv[0]);
        

    argVec[0] = strrchr(argv[1], '/');      /* Get basename from argv[1] */
    printf("argVec[0]: %s\n", argVec[0]);
    if (argVec[0] != NULL)
        argVec[0]++;
    else
        argVec[0] = argv[1];
    argVec[1] = "hello world";
    argVec[2] = "goodbye";
    argVec[3] = NULL;           /* List must be NULL-terminated */

    execve(argv[1], argVec, envVec);
    printf("execve\n");
    exit(EXIT_FAILURE);
    // errExit("execve");          /* If we get here, something went wrong */
}