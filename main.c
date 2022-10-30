#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <time.h>
#include <string.h>
#include <dirent.h>

//rename 19.04.2000_23.59.59 to 20000419_235959

int main(int argc, char * argv[]) {
    char * defaultWay = "E:/folder";
    DIR * dir;
    struct dirent * A;

    char * way;
    char oldWay[500], newWay[500];
    char name[100], format[20], newName[16] = {0};
    char * temp, * str;

    if(1 < argc) way = argv[1];
    else way = defaultWay;

    if(dir = opendir(way)) {
        while(A = readdir(dir)) {
            str = A->d_name;

            memset(oldWay, 0, 500);
            memset(newWay, 0, 500);

            strcat(oldWay, way);
            strcat(oldWay, "/");
            strcat(oldWay, str);

            strcat(newWay, way);
            strcat(newWay, "/");

            if(str[0] == '.') continue;

            *((uint32_t *)newName) = *((uint32_t *)(str + 6));
            *((uint16_t *)(newName + 4)) = *((uint16_t *)(str + 3));
            *((uint16_t *)(newName + 6)) = *((uint16_t *)str);

            newName[8] = '_';

            *((uint16_t *)(newName + 9)) = *((uint16_t *)(str + 11));
            *((uint16_t *)(newName + 11)) = *((uint16_t *)(str + 14));
            *((uint16_t *)(newName + 13)) = *((uint16_t *)(str + 17));

            strcat(newWay, newName);

            temp = strrchr(A->d_name, '.');
            if(temp) {
                memset(format, 0, 20);
                strcat(format, temp + 1);
                strcat(newWay, ".");
                strcat(newWay, format);

                printf("%s\n", newWay);

                rename(oldWay, newWay);
            }

        }
    } else printf("Folder isn't find\n");

    return 0;
}
