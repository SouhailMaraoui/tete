void cmd_clean_help()
{
    println("- clean\t\t Remove the intermediate files of the previous build");
    println("     \t\t Usage: ./gitus clean\n");
}

void cmd_clean()
{
    removeFolder("intermediate");
}