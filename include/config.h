
#ifndef AKIN_CONFIG_

#define AKIN_CONFIG_

#include <stdlib.h>
#include <stdio.h>

#define speach_setting  "<speak version='1.0' xmlns='http://www.w3.org/2001/10/synthesis' xml:lang='EN'>"
#define voice_end       "</speak>"

#define LITE_MODE //return;

//===============================================

const size_t INDENT_STEP    =  4,
             WORLD_LENGTH   = 20;

const char *const CONSOLE       = "stdout",
           *const SECRET_MODE   = "secret";

const size_t MUSIC_SIZE = 3;

const char* music[] = {"sound/chill.wav", "sound/freedom.wav",
                       "sound/soul.wav" , "sound/yesterday.wav"
                      };

//===============================================

void scanf_string       (FILE* in_file, char** string);
void voice_assistant    (const char *const ex_phrase, const char *const add_phrase = nullptr);
void questions_assistant(const char *const ex_phrase, const char *const add_phrase);

#endif // AKIN_CONFIG_
