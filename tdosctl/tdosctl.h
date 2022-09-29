/* tdosctl.h */

#define MAXURLLEN 2048
#define BASEURL "archive.org/download/Total_DOS_Collection_18_Archive"
#define USERAGENT "libcurl-agent/7.83.0"

enum tdos_LIST_TYPE { ByYear = 1, Alpha };

CURL* tdos_init(void);
void tdos_find_year_in_title(char year[], char title[]);
void tdos_title_to_url(CURL *curl, char url[], char title[], char base_url[]);
void tdos_get_game(CURL *curl, char title[], char base_url[]);
void tdos_get_gamelist(CURL *curl, enum tdos_LIST_TYPE type, char base_url[]); 
void tdos_easy_perform(CURL *curl, char filename[], char url[]);

char TITLE[] = "Dune II- The Battle for Arrakis v1.07 (En)(It)(Es) (1992)(Virgin Games, Ltd.) [Strategy].zip";

