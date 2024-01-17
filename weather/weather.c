#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

#define API_KEY "0c732fa73213e07f8227532ce520be9f"
#define API_ENDPOINT "http://api.openweathermap.org/data/2.5/weather"

// Function to extract a substring between two delimiters
char* extract_string(const char* source, const char* start, const char* end) {
    char* result;
    const char* start_pos = strstr(source, start);

    if (!start_pos) return NULL;

    start_pos += strlen(start);
    const char* end_pos = strstr(start_pos, end);

    if (!end_pos) return NULL;

    size_t length = end_pos - start_pos;
    result = malloc(length + 1);
    strncpy(result, start_pos, length);
    result[length] = '\0';

    return result;
}

// Function to parse the temperature and description from JSON
void parse_weather_info(const char* json_data) {
    // Extract temperature
    const char* temp_start = "\"temp\":";
    const char* temp_end = ",";
    char* temp_str = extract_string(json_data, temp_start, temp_end);

    if (temp_str) {
        double temperature_kelvin = atof(temp_str);
        double temperature_celsius = temperature_kelvin - 273.15;
        double temperature_fahrenheit = (temperature_celsius * 9 / 5) + 32;

        printf("Temperature: %.2f°C, %.2f°F\n", temperature_celsius, temperature_fahrenheit);

        free(temp_str);
    }

    // Extract description
    const char* desc_start = "\"description\":\"";
    const char* desc_end = "\"";
    char* desc_str = extract_string(json_data, desc_start, desc_end);

    if (desc_str) {
        printf("Description: %s\n", desc_str);
        free(desc_str);
    }
}

// Function to perform the HTTP request using libcurl
size_t write_callback(void* contents, size_t size, size_t nmemb, void* user_data) {
    // Pass the data to the parsing function
    parse_weather_info((char*)contents);
    return size * nmemb;
}

int main() {
    CURL* curl;
    CURLcode res;

    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        // Get user input for city and country
        char city[50], country[50];
        printf("Enter city: ");
        scanf("%s", city);
        printf("Enter country: ");
        scanf("%s", country);

        // Construct the API request URL
        char url[256];
        snprintf(url, sizeof(url), "%s?q=%s,%s&appid=%s", API_ENDPOINT, city, country, API_KEY);

        // Set the API request URL
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        // Perform the HTTP request
        res = curl_easy_perform(curl);

        // Check for errors
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        // Cleanup
        curl_easy_cleanup(curl);
    }

    // Cleanup libcurl
    curl_global_cleanup();

    return 0;
}
