#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <curl/curl.h>

#define MAXURLLEN 2048
#define BASE_URL "archive.org/download/Total_DOS_Collection_18_Archive"

enum tdos_LIST_TYPE { Byyear = 1, Alpha };

void tdos_title_to_url(CURL *curl, char url[], char title[], char base_url[]);
void tdos_find_year_in_title(char year[], char title[]);
void tdos_get_gamelist(CURL *curl, enum tdos_LIST_TYPE type, char base_url[]); 

char title[] = "Dune II- The Battle for Arrakis v1.07 (En)(It)(Es) (1992)(Virgin Games, Ltd.) [Strategy].zip";

int main() {

    //char url[MAXURLLEN];
    CURL *curl;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);

    //tdos_title_to_url(curl, url, title);
    tdos_get_gamelist(curl, Alpha, BASE_URL); 

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}

void tdos_title_to_url(CURL *curl, char url[], char title[], char base_url[]) {

    char year[5];
    char url_tmp[MAXURLLEN];
    char title_tmp[strlen(title)+5];

    // find year
    tdos_find_year_in_title(year, title);
    // protocol, base url and year
    sprintf(url_tmp, "https://%s/%s/%s.zip", base_url, "Games/Files", year);
    // add year to title
    sprintf(title_tmp, "%s/%s", year, title);
    // construct final url
    sprintf(url, "%s/%s", url_tmp, curl_easy_escape(curl, title_tmp, 0));
}


/* refactor this: too complex */
void tdos_find_year_in_title(char year[], char title[]) {

    int i = 0;
    while (title[i]) {
        if (title[i] == '(') {
            int j = i+1;
            while (j-i-1 < 4 && title[j] != ')') {
                year[j-i-1] = title[j];
                j++;
            }

            year[j-i-1] = '\0';
            if (title[j] == ')' && j-i-1 == 4) {
                int k = 0;
                while (isdigit(year[k]))
                    k++;
                if (k == 4 || (k == 3 && year[k] == 'x'))
                    break; // we got it!
            }
            i = j+1;
        } else i++;
    }
}

void tdos_get_gamelist(CURL *curl, enum tdos_LIST_TYPE type, char base_url[]) {

    char *resource;
    char url[MAXURLLEN];
    char *filename;
    FILE *file;

    switch (type) {
        case (Byyear):
            resource = "Lists/byyear.txt";
            filename = "byyear.txt";
            break;
        
        case (Alpha):
            resource = "Lists/alpha.txt";
            filename = "alpha.txt";
            break;
    }

    sprintf(url, "https://%s/%s", base_url, resource);
    file = fopen(filename, "w");

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*) file);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/7.83.0");
    curl_easy_perform(curl);
}

