#include <stdio.h>
#include <curl/curl.h>

int main() {
    curl_version_info_data *data; 
    data = curl_version_info(CURLVERSION_NOW);

    printf("libcurl version %s\n", data->version);
    printf("libcurl ssl version %s\n", data->ssl_version);
    printf("libcurl libz version %s\n", data->libz_version);

    printf("libcurl protocols:\n");
    for (int i=0; data->protocols[i]; ++i) {
        printf("\t%s\n", data->protocols[i]);
    }

    printf("libcurl version %u.%u.%u\n",
           (data->version_num >> 16) & 0xFF,
           (data->version_num >>  8) & 0xFF,
            data->version_num        & 0xFF);

    return 0;
}
