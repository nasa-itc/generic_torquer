/*******************************************************************************
** File: generic_torquer_checkout.c
**
** Purpose:
**   This checkout can be run without cFS and is used to quickly develop and 
**   test functions required for a specific component.
**
*******************************************************************************/

/*
** Include Files
*/
#include "generic_torquer_checkout.h"

/*
** Global Variables
*/
uart_info_t Generic_torquerUart; // TODO
GENERIC_TORQUER_Device_HK_tlm_t Generic_torquerHK; // TODO
GENERIC_TORQUER_Device_Data_tlm_t Generic_torquerData; // TODO

/*
** Component Functions
*/
void print_help(void) 
{
    printf(PROMPT "command [args]\n"
        "---------------------------------------------------------------------\n"
        "help                               - Display help                    \n"
        "exit                               - Exit app                        \n"
        "hk                                 - Print current housekeeping      \n"
        "  h                                - ^                               \n"
        "torque percent# direction#         - Torque percent (0-100) and direction (0-1) \n"
        "  t # #                            - ^                               \n"
        "\n"
    );
}


int get_command(const char* str)
{
    int status = CMD_UNKNOWN;
    char lcmd[MAX_INPUT_TOKEN_SIZE];
    strncpy(lcmd, str, MAX_INPUT_TOKEN_SIZE);

    /* Convert command to lower case */
    to_lower(lcmd);

    if(strcmp(lcmd, "help") == 0) 
    {
        status = CMD_HELP;
    }
    else if(strcmp(lcmd, "exit") == 0) 
    {
        status = CMD_EXIT;
    }
    else if(strcmp(lcmd, "hk") == 0) 
    {
        status = CMD_HK;
    }
    else if(strcmp(lcmd, "h") == 0) 
    {
        status = CMD_HK;
    }
    else if(strcmp(lcmd, "torque") == 0) 
    {
        status = CMD_TORQUE;
    }
    else if(strcmp(lcmd, "t") == 0) 
    {
        status = CMD_TORQUE;
    }
    return status;
}


int process_command(int cc, int num_tokens, char tokens[MAX_INPUT_TOKENS][MAX_INPUT_TOKEN_SIZE])
{
    int32_t status = OS_SUCCESS;
    int32_t exit_status = OS_SUCCESS;
    uint32_t config;

    /* Process command */
    switch(cc) 
    {	
        case CMD_HELP:
            print_help();
            break;
        
        case CMD_EXIT:
            exit_status = OS_ERROR;
            break;

        case CMD_HK:
            if (check_number_arguments(num_tokens, 0) == OS_SUCCESS)
            {
                // TODO - print current values of torquer
            }
            break;

        case CMD_TORQUE:
            if (check_number_arguments(num_tokens, 0) == OS_SUCCESS)
            {
                // TODO - set the torque value
                //status = GENERIC_TORQUER_RequestData(&Generic_torquerUart, &Generic_torquerData);
                //if (status == OS_SUCCESS)
                //{
                //    OS_printf("GENERIC_TORQUER_RequestData command success\n");
                //}
                //else
                //{
                //    OS_printf("GENERIC_TORQUER_RequestData command failed!\n");
                //}
            }
            break;

        default: 
            OS_printf("Invalid command format, type 'help' for more info\n");
            break;
    }
    return exit_status;
}


int main(int argc, char *argv[]) 
{
    int status = OS_SUCCESS;
    char input_buf[MAX_INPUT_BUF];
    char input_tokens[MAX_INPUT_TOKENS][MAX_INPUT_TOKEN_SIZE];
    int num_input_tokens;
    int cmd;    
    char* token_ptr;
    uint8_t run_status = OS_SUCCESS;

    /* Initialize HWLIB */
    #ifdef _NOS_ENGINE_LINK_
        nos_init_link();
    #endif

    /* Open device specific protocols */
    // TODO - take from app side as it already exist

    //Generic_torquerUart.deviceString = GENERIC_TORQUER_CFG_STRING;
    //Generic_torquerUart.handle = GENERIC_TORQUER_CFG_HANDLE;
    //Generic_torquerUart.isOpen = PORT_CLOSED;
    //Generic_torquerUart.baud = GENERIC_TORQUER_CFG_BAUDRATE_HZ;
    //status = uart_init_port(&Generic_torquerUart);
    //if (status == OS_SUCCESS)
    //{
    //    printf("UART device %s configured with baudrate %d \n", Generic_torquerUart.deviceString, Generic_torquerUart.baud);
    //}
    //else
    //{
    //    printf("UART device %s failed to initialize! \n", Generic_torquerUart.deviceString);
    //    run_status = OS_ERROR;
    //}

    /* Main loop */
    print_help();
    while(run_status == OS_SUCCESS) 
    {
        num_input_tokens = -1;
        cmd = CMD_UNKNOWN;

        /* Read user input */
        printf(PROMPT);
        fgets(input_buf, MAX_INPUT_BUF, stdin);

        /* Tokenize line buffer */
        token_ptr = strtok(input_buf, " \t\n");
        while((num_input_tokens < MAX_INPUT_TOKENS) && (token_ptr != NULL)) 
        {
            if(num_input_tokens == -1) 
            {
                /* First token is command */
                cmd = get_command(token_ptr);
            }
            else 
            {
                strncpy(input_tokens[num_input_tokens], token_ptr, MAX_INPUT_TOKEN_SIZE);
            }
            token_ptr = strtok(NULL, " \t\n");
            num_input_tokens++;
        }

        /* Process command if valid */
        if(num_input_tokens >= 0)
        {
            /* Process command */
            run_status = process_command(cmd, num_input_tokens, input_tokens);
        }
    }

    // Close the device 
    // TODO - close torquer device
    //uart_close_port(&Generic_torquerUart);

    #ifdef _NOS_ENGINE_LINK_
        nos_destroy_link();
    #endif

    OS_printf("Cleanly exiting generic_torquer application...\n\n"); 
    return 1;
}


/*
** Generic Functions
*/
int check_number_arguments(int actual, int expected)
{
    int status = OS_SUCCESS;
    if (actual != expected)
    {
        status = OS_ERROR;
        OS_printf("Invalid command format, type 'help' for more info\n");
    }
    return status;
}

void to_lower(char* str)
{
    char* ptr = str;
    while(*ptr)
    {
        *ptr = tolower((unsigned char) *ptr);
        ptr++;
    }
    return;
}

