

#include "../include/tree.h"
#include "../include/database.h"

Node* do_data_loading(const char *const data_file)
{
    assert (data_file);

    Node* fake_root = tree_construct();

    FILE* in_file = fopen(data_file, "r");

    load_node(fake_root, in_file);

    fclose(in_file);

    Node* real_root = fake_root->left_son;

    real_root->mother = nullptr;

    free(fake_root);

    return real_root;
}

void load_node(Node* node, FILE* in_file)
{
    assert (in_file);

    if (!node)
        return;

    //printf("hello");

    char bracket_case = '\01';

    //char cell[WORLD_LENGTH] = {};

    fscanf(in_file, " %c", &bracket_case);

    if (bracket_case == '{')
    {
        Node* son = (Node*) calloc(1, sizeof(Node));

        //son->cell = (char*) calloc(WORLD_LENGTH, sizeof (char));

        son->mother = node;

        if (node->left_son)
        {
            if (!node->right_son)
                node->right_son = son;
            else
                assert (SYNTAX_ERROR);
        }
        else
            node->left_son = son;

        son->left_son  = nullptr;
        son->right_son = nullptr;


        //fscanf(in_file, " " CELL_FMT, cell);

        //printf(CELL_FMT, cell);

        //strcpy(son->cell, cell);

        scanf_string(in_file, &son->cell);

        fscanf(in_file, " %c", &bracket_case);

        if (bracket_case == '{')
        {
            //printf("2");

            ungetc(bracket_case, in_file);

            load_node(son, in_file);
        }
        else if (bracket_case == '}')    //add else
        {
            //printf("1");

            //ungetc(bracket_case, in_file);

            load_node(node, in_file);
        }
        else
            assert (SYNTAX_ERROR);       //add bugs
    }
    else if (bracket_case == '}' || bracket_case == '\01')
       load_node(node->mother, in_file);
    else
        assert (SYNTAX_ERROR);
}

void do_data_push(Node* root, const char *const data_file, const char *const mode)
{
     if (mode && data_file && !strcmp(mode, SECRET_MODE))
     {
        if (!strcmp(data_file, CONSOLE))
        {
            secure_print_node(root, 0, stdout);

            return;
        }

        FILE* out_file = fopen(data_file, "w");

        assert (out_file);

        secure_print_node(root, 0, out_file);

        fclose(out_file);

        return;
     }

     if (data_file)
     {
        if (!strcmp(data_file, CONSOLE))
        {
            print_node(root, 0, stdout);
        }
        else
        {
            FILE* out_file = fopen(data_file, "w");

            assert (out_file);

            print_node(root, 0, out_file);

            fclose(out_file);
        }

        return;
     }


     //system("git ");



}


void print_node(Node* node, size_t indent, FILE* out_file) //print_pre
{
    if (!node)
		return;

    fprintf(out_file, "%*s", indent, "{");

    indent += INDENT_STEP;

    fprintf(out_file, " " CELL_FMT " ", node->cell);

    if (node->left_son || node->right_son)
    {
        fprintf(out_file, "\n");

        print_node(node->left_son, indent, out_file);

        if (node->right_son)
            fprintf(out_file, "\n");

        print_node(node->right_son, indent, out_file);

        fprintf(out_file, "\n%*s", indent -= INDENT_STEP, "}");
    }
    else
    {
        /*print_node(node->left_son, indent);    commented

        if (node->right_son)
            printf("\n");

        print_node(node->right_son, indent);

        //printf("\n%*s", indent -= 4, "}");*/

        fprintf(out_file, "}");
    }
}




Secret secret_identificator(Node* root, const char *const password)
{
    if (!root)
    return denied;

    assert (password);

    //printf("IIIIII");

    static Node* inMemorySecretRoot = nullptr;

    static bool secret_key = false;

    bool match_key = !strcmp(password, "buravko");

    if (match_key && secret_key == false)
    {
        do_secret_loading(root);

        inMemorySecretRoot = root;

        secret_key = true;

        voice_assistant("Secret tree is load!\n");

        return init;
    }
    else if (match_key && secret_key == true && inMemorySecretRoot == root)
    {
        voice_assistant("Success!\n");

        return success;
    }

    return denied;
}

bool do_secret_loading(Node* root)
{
    assert (root);

    file_decoder(secret_file);

    Node* secret_root = do_data_loading(secret_file); //secret

    file_coder(secret_file);

    Node* port_root = (Node*) calloc(1, sizeof(Node));

    port_root->cell = (char*) calloc(8, sizeof (char));

    if (!secret_root || !port_root)
        return false;

    strcpy(port_root->cell, "SECRET!");

    port_root->mother = root;
    port_root->right_son = secret_root;
    port_root->left_son = root->right_son;

    secret_root->mother = port_root;
    port_root->left_son->mother = port_root;

    root->right_son = port_root;

    return true;
}

bool file_decoder(const char *const dec_file)
{
    if (!dec_file)
        return false;

    FILE* in_file = fopen(dec_file, "rb");

    fseek(in_file, 0, SEEK_END);

    size_t in_size = ftell(in_file);

    fseek(in_file, 0, SEEK_SET);

    char* buffer = (char*) calloc(in_size + 1 , sizeof (char));

    fread(buffer, sizeof (char), in_size, in_file);

    fclose(in_file);

    buffer[0] = buffer[0] ^ HASH_ELEMENT;

    for (size_t ind = in_size  - 1; ind > 0; ind--)
    {
        buffer[ind] = buffer[ind] ^ buffer[ind - 1] ^ HASH_ELEMENT;
    }

    in_file = fopen(dec_file, "wb");

    //fprintf(in_file, "%s", buffer);

    fwrite(buffer, sizeof (char), in_size, in_file);

    fclose(in_file);

    return true;
}

bool file_coder(const char *const cod_file)
{
    if (!cod_file)
        return false;

    FILE* in_file = fopen(cod_file, "rb");

    fseek(in_file, 0, SEEK_END);

    size_t in_size = ftell(in_file);

    fseek(in_file, 0, SEEK_SET);

    char* buffer = (char*) calloc(in_size + 1 , sizeof (char));

    fread(buffer, sizeof (char), in_size, in_file);

    fclose(in_file);

    //buffer[0] = buffer[0] ^ HASH_ELEMENT;

    for (size_t ind = 1; ind < in_size; ind++)
    {
        buffer[ind] = buffer[ind] ^ buffer[ind - 1] ^ HASH_ELEMENT;
    }

    buffer[0] = buffer[0] ^ HASH_ELEMENT;

    in_file = fopen(cod_file, "wb");

    //fprintf(in_file, "%s", buffer);

    fwrite(buffer, sizeof (char), in_size, in_file);

    fclose(in_file);

    return true;
}



void secure_print_node(Node* node, size_t indent, FILE* out_file) //print_pre
{
    if (!node)
		return;

    if (!strcmp(node->cell, "SECRET!"))
    {
        FILE* out_secret_file = fopen(secret_file, "w");

        print_node(node->left_son, indent, out_file);

        print_node(node->right_son, 0, out_secret_file);

        fclose(out_secret_file);

        file_coder(secret_file);

        return;
    }


    fprintf(out_file, "%*s", indent, "{");

    indent += INDENT_STEP;

    fprintf(out_file, " " CELL_FMT " ", node->cell);

    if (node->left_son || node->right_son)
    {
        fprintf(out_file, "\n");

        secure_print_node(node->left_son, indent, out_file);

        if (node->right_son)
            fprintf(out_file, "\n");

        secure_print_node(node->right_son, indent, out_file);

        fprintf(out_file, "\n%*s", indent -= INDENT_STEP, "}");
    }
    else
    {
        /*print_node(node->left_son, indent);    commented

        if (node->right_son)
            printf("\n");

        print_node(node->right_son, indent);

        //printf("\n%*s", indent -= 4, "}");*/

        fprintf(out_file, "}");
    }
}
