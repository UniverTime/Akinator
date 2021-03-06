
#ifndef DATABASE_

#define DATABASE_

#include "tree.h"
#include "config.h"

typedef enum Secret{

    denied  = 0,
    init    = 1,
    success = 2,

} Secret;

//===============================================

const size_t SYNTAX_ERROR       = 0;
const char *const secret_file   = "Vsecret";
const char HASH_ELEMENT         = 'A';

//===============================================

void    load_node       (Node* node, FILE* in_file);
Node*   do_data_loading (const char *const data_file);
void    print_node      (Node* node, size_t indent, FILE* out_file);
void    do_data_push    (Node* root, const char *const data_file = nullptr,
                         const char *const mode = nullptr);

bool    file_decoder    (const char *const dec_file);
bool    file_coder      (const char *const cod_file);

Secret  secret_identificator    (Node* root, const char *const password);
bool    do_secret_loading       (Node* root);
void    secure_print_node       (Node* node, size_t indent, FILE* out_file);

#endif // DATABASE_
