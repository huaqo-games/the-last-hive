#ifndef CONFIG_H
#define CONFIG_H

#define RINI_IMPLEMENTATION
#define RINI_VALUE_DELIMITER '='

#include <rini.h>
#include <stdio.h>

typedef struct {
    char *path;
    rini_config rini;
} Config;

void InitConfig(Config *config, const char* path) {
    config->rini = rini_load_config(path);
    if (config->rini.count == 0) {
        printf("Warning: Loaded config has no entries. Path: %s\n", config->path);
    }
}

int GetConfigInt(Config *config, const char *key) {
    return rini_get_config_value_fallback(config->rini, key, 0);
}

int GetConfigIntOrDefault(Config *config, const char *key, int default_value) {
    return rini_get_config_value_fallback(config->rini, key, default_value);
}

const char* GetConfigString(Config *config, const char *key) {
    return rini_get_config_value_text(config->rini, key); 
}

const char* GetConfigStringOrDefault(Config *config, const char *key, const char *default_value) {
    return rini_get_config_value_text_fallback(config->rini, key, default_value);
}

const char* GetConfigDescription(Config *config, const char *key) {
    return rini_get_config_value_description(config->rini, key);
}

int SetConfigInt(Config *config, const char *key, int value, const char *desc) {
    return rini_set_config_value(&config->rini, key, value, desc);
}

int SetConfigString(Config *config, const char *key, const char *text, const char *desc) {
    return rini_set_config_value_text(&config->rini, key, text, desc);
}

int SetConfigDescription(Config *config, const char *key, const char *desc) {
    return rini_set_config_value_description(&config->rini, key, desc);
}

int AddCommentLine(Config *config, const char *comment) {
    return rini_set_config_comment_line(&config->rini, comment);
}

void SaveConfig(Config *config) {
    rini_save_config(config->rini, config->path);
}

void CleanUpConfig(Config *config) {
    rini_unload_config(&config->rini);  
}

#endif // CONFIG_H
