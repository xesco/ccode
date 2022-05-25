#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <curl/curl.h>
#include "tdosctl.h"


/* init curl and download the gamelists */
CURL* tdos_init(void) {

    CURL *curl;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 0);

    // get gamelists
    tdos_get_gamelist(curl, Alpha, BASEURL);
    tdos_get_gamelist(curl, Byyear, BASEURL);

    return curl;
}


/* given a game title in the collection, return a URL ready to be curled
   to download the game.
*/
void tdos_title_to_url(CURL *curl, char url[], char title[], char base_url[]) {

    char year[5]; // we need an extra byte to end the string with '\0'
    char url_tmp[MAXURLLEN];
    char title_tmp[strlen(title)+5];

    // find year
    tdos_find_year_in_title(year, title);
    // protocol, base url and year
    sprintf(url_tmp, "https://%s/%s/%s.zip", base_url, "Games/Files", year);
    // add year to title
    sprintf(title_tmp, "%s/%s", year, title);
    // construct final url scaping title_tmp
    sprintf(url, "%s/%s", url_tmp, curl_easy_escape(curl, title_tmp, 0));
}


/* TODO: refactor this: too complex */
/* Extract the year from a game title */
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


/* get the gamelist by year or in alphabetic order, and save it into a file */
void tdos_get_gamelist(CURL *curl, enum tdos_LIST_TYPE type, char base_url[]) {

    char *resource;
    char *filename;
    char url[MAXURLLEN];

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
    tdos_easy_perform(curl, filename, url);
}


void tdos_get_game(CURL *curl, char title[], char base_url[]) {

    char url[MAXURLLEN];
    tdos_title_to_url(curl, url, title, base_url);
    tdos_easy_perform(curl, title, url);
}


void tdos_easy_perform(CURL *curl, char filename[], char url[]) {
    FILE *file = fopen(filename, "w");
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*) file);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, USERAGENT);
    curl_easy_perform(curl);
}


int main() {

    CURL *curl = tdos_init();

    tdos_get_game(curl, title, BASEURL);

    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return 0;
}

