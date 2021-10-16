/* command_action.c */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <command/command_actions.h>
#include <config/config_handler.h>
#include <parsing/argument_parser.h>
#include <mem/mem.h>

#define TRUE  1
#define FALSE 0

#define INSTRUCTION_ARRAY_S 12

struct command_instructions {
    char  *c_name;          // command name.
    char  *c_attributes[2]; // command attributes.
    int    c_is_int;
};

struct command_instructions c_instructions_array[INSTRUCTION_ARRAY_S] = {
        {.c_name = SET_CHECK_INTERVAL,   .c_attributes[0] = C_INTERVAL_OP,  .c_attributes[1] = NULL,        .c_is_int = TRUE},
        {.c_name = SET_PARSE_INTERVAL,   .c_attributes[0] = P_INTERVAL_OP,  .c_attributes[1] = NULL,        .c_is_int = TRUE},
        {.c_name = SET_DEBUG_LOG,        .c_attributes[0] = D_ENABL_OP,     .c_attributes[1] = NULL,        .c_is_int = TRUE},
        {.c_name = SET_DEFAULT_DIR_PATH, .c_attributes[0] = D_PATH_OP,      .c_attributes[1] = NULL,        .c_is_int = FALSE},
        {.c_name = SET_ENABLE_DEF_DIR,   .c_attributes[0] = D_ENABL_OP,     .c_attributes[1] = NULL,        .c_is_int = TRUE},
        {.c_name = ADD_CHECK,            .c_attributes[0] = CHECK_ID,       .c_attributes[1] = CHECK_ID_D,  .c_is_int = FALSE},
        {.c_name = ADD_TARGET,           .c_attributes[0] = TARGET_ID,      .c_attributes[1] = TARGET_ID_D, .c_is_int = FALSE},
        {.c_name = REMOVE_CHECK,         .c_attributes[0] = CHECK_ID,       .c_attributes[1] = CHECK_ID_D,  .c_is_int = FALSE},
        {.c_name = REMOVE_TARGET,        .c_attributes[0] = TARGET_ID,      .c_attributes[1] = TARGET_ID_D, .c_is_int = FALSE},
        {.c_name = LIST_OPTIONS,         .c_attributes[0] = C_INTERVAL_OP,  .c_attributes[1] = CHECK_ID,    .c_is_int = FALSE},
        {.c_name = LIST_TARGETS,         .c_attributes[0] = TARGET_ID,      .c_attributes[1] = TARGET_ID_D, .c_is_int = FALSE},
        {.c_name = LIST_CHECKS,          .c_attributes[0] = CHECK_ID,       .c_attributes[1] = CHECK_ID_D,  .c_is_int = FALSE}
};


void help() {

    printf("Usage:\n \tsorter [OPTION] ...\n\n"
           "\t--set-check-interval      [value] Change the value of check interval.\n"
           "\t--set-parse-interval      [value] Change the value of parse interval.\n"
           "\t--set-default-dir-path    [path] Change the default directory path.\n"
           "\t--set-enable-default-dir  [value] 0:1 Enable the to transfer files in default dir.\n"
           "\t--set-debug-log           [value] 0:1 Change the log to debug mode (1).\n"
           "\t--add-check               [path] Add new check.\n"
           "\t--add-target              [ext] [path] Add new target.\n"
           "\t--remove-check            [row number] remove check.\n"
           "\t--remove-target           [row number] remove target.\n"
           "\t--list-checks list checks.\n"
           "\t--list-targets list targets.\n"
           "\t--list-options list options.\n");

    exit(0);
}

static inline int get_instructions(const char *c_name) {
    for (int instructions = 0; instructions < INSTRUCTION_ARRAY_S; instructions++) {
        if (strcmp(c_instructions_array[instructions].c_name, c_name) == 0)
            return instructions;
    }

    return -1;
}

void list_command(const char *what_to_list) {
    int index_of_instruction = get_instructions(what_to_list);
    if (index_of_instruction == -1) return;

    struct command_instructions instructions = c_instructions_array[index_of_instruction];
    // Read the config file.
    char *config = read_config();
    if (config == NULL) return;

    char *location_of_interest = strstr(config, instructions.c_attributes[0]);
    if (!location_of_interest) {
        free(config);
        return;
    }

    // Make a copy of the location_of_interest, so we do not break the data of config.
    char tmp[strlen(location_of_interest + 1)];
    strcpy(tmp, location_of_interest);

    char *current_element = strtok(location_of_interest, "\n");
    int row = 1;

    int skip_first = FALSE;
    if (!strcmp(instructions.c_name, LIST_CHECKS) || !strcmp(instructions.c_name, LIST_TARGETS))
        skip_first = TRUE;

    while (current_element != NULL && strcmp(current_element, instructions.c_attributes[1]) != 0) {
        if (row == 1 && skip_first) current_element = strtok(NULL, "\n");

        printf("%d: %s\n", row, current_element);
        row++;
        current_element = strtok(NULL, "\n");
    }

    free(config);
}

static int is_integer(const char *value) {
    char digits[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
    int found = FALSE;

    int index = 0;
    while ( digits[index] != '\0' ) {
        while ( *(value++) != '\0' )
            if (digits[index] == *value) {
                found = TRUE;
                break;
            }
        if (!found) return FALSE;
    }

    return TRUE;
}

void set_value(const char *option, const char *new_value) {
    int index_of_instructions = get_instructions(option);
    if (index_of_instructions == -1) return;

    struct command_instructions instructions = c_instructions_array[index_of_instructions];
    // Check if we want the new_value to be integer.
    if (instructions.c_is_int) {
        if (!is_integer(new_value)) return;
    }

    char *config = read_config();
    if (config == NULL) return;

    // Here we replace the old value with the new.
    // TODO - Make an array in which i will put each option in a different index.
    // TODO - Build the option with the new value.
    // TODO - Rebuild the config file.
    // TODO - Write the result back the the config.conf

    free(config);
}

void add_target(const char *new_target) {
    // TODO - add the target @new_target in the targets.
}

void add_check(const char *new_check) {
    // TODO - add the check @new_check in the checks.
}

void remove_target(int row_line) {
    // TODO - remove target in line @row_line.
}

void remove_check(int row_line) {
    // TODO - remove check in line @row_line.
}
