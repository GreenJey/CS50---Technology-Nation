char* indexes(const char* path)
{
    // If path contains a . (ASCII 46) return NULL
    if (strchr(path, 46) != NULL) {
        return NULL;
    }
    
    // Check for index.html
    char* index_html_path = calloc(strlen(path) + 11, 1);
    index_html_path = strcat(index_html_path, path);
    if (path[strlen(path) - 1] != '/') 
    {
        index_html_path = strcat(index_html_path, "/");
    }
    index_html_path = strcat(index_html_path, "index.html");
    if (access(index_html_path, R_OK) == 0) {
        return index_html_path;
    }
    else {
        free(index_html_path);
    }
    
    // Check for index.php
    char* index_php_path = calloc(strlen(path) + 10, 1);
    index_php_path = strcat(index_php_path, path);
    if (path[strlen(path) - 1] != '/') {
        index_php_path = strcat(index_php_path, "/");
    }
    index_php_path = strcat(index_php_path, "index.php");
    if (access(index_php_path, R_OK) == 0) {
        return index_php_path;
    }
    else 
    {
        return NULL;
    }

}

/**
 * Interprets PHP file at path using query string.
 */
void interpret(const char* path, const char* query)
{
    // ensure path is readable
    if (access(path, R_OK) == -1)
    {
        error(403);
        return;
    }

    // open pipe to PHP interpreter
    char* format = "QUERY_STRING=\"%s\" REDIRECT_STATUS=200 SCRIPT_FILENAME=\"%s\" php-cgi";
    char command[strlen(format) + (strlen(path) - 2) + (strlen(query) - 2) + 1];
    if (sprintf(command, format, query, path) < 0)
    {
        error(500);
        return;
    }
    FILE* file = popen(command, "r");
    if (file == NULL)
    {
        error(500);
        return;
    }

    // load interpreter's content
    char* content;
    size_t length;
    if (load(file, &content, &length) == false)
    {
        error(500);
        return;
    }

    // close pipe
    pclose(file);

    // subtract php-cgi's headers from content's length to get body's length
    char* haystack = content;
    char* needle = strstr(haystack, "\r\n\r\n");
    if (needle == NULL)
    {
        free(content);
        error(500);
        return;
    }

    // extract headers
    char headers[needle + 2 - haystack + 1];
    strncpy(headers, content, needle + 2 - haystack);
    headers[needle + 2 - haystack] = '\0';

    // respond with interpreter's content
    respond(200, headers, needle + 4, length - (needle - haystack + 4));

    // free interpreter's content
    free(content);
}

/**
 * Loads a file into memory dynamically allocated on heap.
 * Stores address thereof in *content and length thereof in *length.
 */
bool load(FILE* file, BYTE** content, size_t* length)
{
    
    // Create temporary variable to buffer the reads
    // BYTE read_byte_buffer = 0;
    int buffer = 0;
    
    // Create pointer to store file contents
    BYTE* file_contents = calloc(1, 1);
    
    // Create index counter
    int index = 0;
    
    // Read file to file_contents
    while ((buffer = fgetc(file)) != EOF) {
        
        // Get the next character
        // buffer = fgetc(file);
        
        // Add buffer to contents
        *(file_contents + index) = buffer;
        // file_contents[index] =  buffer;
        
        // Increment the index
        index++;
        
        // Extend file_contents
        file_contents = realloc(file_contents, index + 1);
        
    }
    
    if (file_contents != NULL) {
        
        // Write EOF
        // *(file_contents + index) = buffer;

        // Assign file_contents pointer to *content
        *content = file_contents;
        // memcpy(*content, file_contents, index + 1);

        // Assign index + 1 to length
        *length = index;

        return true;

    }
    
    else {
        return false;
    }
    
}

/**
 * Returns MIME type for supported extensions, else NULL.
 */
const char* lookup(const char* path)
{
    // Return NULL if no path
    if (strlen(path) == 0) {
        return NULL;
    }
    
    // use strrchr() to find last . (ASCII 46) in path
    char* dot_ptr = strrchr(path, 46);

    // create mime
    char* mime = malloc(17);
    // char mime[16] = {0};

    // check for file extensions and strcopy MIME types
    if (dot_ptr == NULL) {
        return NULL;
    }
    else if (strcasecmp(dot_ptr, ".css") == 0)
    {
        strcpy(mime, "text/css");
    }
    else if (strcasecmp(dot_ptr, ".html") == 0)
    {
        strcpy(mime, "text/html");
    }
    else if (strcasecmp(dot_ptr, ".gif") == 0)
    {
        strcpy(mime, "image/gif");
    }
    else if (strcasecmp(dot_ptr, ".ico") == 0)
    {
        strcpy(mime, "image/x-icon");
    }
    else if (strcasecmp(dot_ptr, ".jpg") == 0)
    {
       strcpy(mime, "image/jpeg");
    }
    else if (strcasecmp(dot_ptr, ".js") == 0)
    {
       strcpy(mime, "text/javascript");
    }
    else if (strcasecmp(dot_ptr, ".php") == 0)
    {
       strcpy(mime, "text/x-php");
    }
    else if (strcasecmp(dot_ptr, ".png") == 0)
    {
       strcpy(mime, "image/png");
    }
    else {
        
        // If none of the above
        free(mime);
        return NULL;
        
    }
    
    // Return mime
    // free(mime);
    return mime;
    
}

/**
 * Parses a request-line, storing its absolute-path at abs_path 
 * and its query string at query, both of which are assumed
 * to be at least of length LimitRequestLine + 1.
 */
bool parse(const char* line, char* path, char* query)
{
    
    // REF: "method request-target HTTP-version\r\n"
    
    // Look for "GET "; trigger 405 and return false if not

    // Create temporary method string
    char method[] = "0000";
    
    // Copy in first four characters of line
    strncpy(method, line, 4);
    
    // Check for "GET "
    if (strcmp(method, "GET ") != 0) {
        error(405);
        return false;
    }

    // Find spaces (ASCII 32) in line to clarify target start and end locations
    char* first_space_ptr = strchr(line, 32);
    char* second_space_ptr = strrchr(line, 32);
    
    // 400 any requests with no spaces
    if (first_space_ptr == NULL || second_space_ptr == NULL) {
        error(400);
        return false;
    }
    
    // If not HTTP/1.1, trigger 505 and return false
    if (strcasecmp(second_space_ptr, " HTTP/1.1\r\n") != 0) {
        error(505);
        return false;
    }
    
    // Define full target
    char* target = malloc(strlen(line));
    // char target[LimitRequestLine + 1];
    strncpy(target, first_space_ptr + 1, second_space_ptr - first_space_ptr);
    
    // Add null terminator to target
    target[second_space_ptr - first_space_ptr - 1] = '\0';
    
    // Look for spaces in target; trigger 400 and return false if found
    if (strchr(target, 32) != NULL) {
        error(400);
        free(target);
        return false;
    }

    // Look for / at start of target; trigger 501 and return false if not
    if (target[0] != '/') {
        error(501);
        free(target);
        return false;
    }
    
    // Look for errant quotation marks; trigger 400 and return false if found
    char* quote_ptr = strstr(target, "\"");
    if (quote_ptr != NULL) {
        error(400);
        free(target);
        return false;
    }
    
    // Look for ? in target, split target into path and query if necessary
    char* question_ptr = strstr(target, "?");
    
    if (question_ptr == NULL) {
        // path = target;
        strcpy(path, target);
        free(target);
        return true;
    }
    else {
        
        // Define path_loc with pointer arithmatic
        char* path_loc = malloc(strlen(line));
        strncpy(path_loc, target, question_ptr - target);

        // Add null terminator to path
        path_loc[question_ptr - target] = '\0';
        
        // Assign path and target
        strcpy(path, path_loc);
        question_ptr = question_ptr + 1;
        strcpy(query, question_ptr);
        free(target);
        free(path_loc);
        return true;
    }
}


bool parse(const char* line, char* abs_path, char* query)
{
         //перевіряємо чи у рядку запиту line є GET, /request, HTTP/1.1. Виділяємо з line  окремо змінну запит request.
        
             if (нема "GET")
        {
            error(405);
        }
        if (запит не починається на "/")
        {
            error(501);
        }
        if (у запиті є '"')
        {
            error(400);
        }
        if (нема "HTTP/1.1")
        {
            error(505);
        }
                
        if (у запиті є файл .php і є змінні )
        {
           //виділяємо запит (наприклад index.php ) і повертаємо його через змінну abs_path
           
           // повертаємо змінні через змінну query
        }
        else
        {
         // abs_path = request
           
           // query=""
        }

        if ( якщо abs_path містить '?')
        {
            error(400);
        }
        if (якщо query містьть '"')
        {
            error(400);
        }
    return true;
}
