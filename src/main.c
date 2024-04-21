#include "gtree.h"
#include "cli.h"
#include "commands.h"


int main(void)
{
    char* HELP_TEXT = "Welocme to generic tree cli!\nHere you can do some operations with this tree";
    cli_handle_t cli = cli_init(HELP_TEXT, 100);
    tree_t tree = tree_init();
    tree_args* tree_command_args = malloc(sizeof(tree_args));
    tree_command_args->tree = &tree;
    cli_add_command(cli, get_add_command_config(tree_command_args));
    cli_add_command(cli, get_delete_command_config(tree_command_args));
    cli_add_command(cli, get_print_command_config(tree_command_args));
    cli_add_command(cli, get_task_command_config(tree_command_args));
    cli_run_until_eof(cli);
    cli_destroy(cli);
    free(tree_command_args);
    tree_destroy(&tree);
}
