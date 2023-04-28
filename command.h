//
// Created by asbpo on 28-04-2023.
//

#ifndef INC_02322PROJEKT2_YUKON_COMMAND_H
#define INC_02322PROJEKT2_YUKON_COMMAND_H

#endif //INC_02322PROJEKT2_YUKON_COMMAND_H


typedef struct{
    char *moveFrom;
    char *moveTo;
    char *card;
    struct command *prevCommand;
    struct command *nextCommand;
}command;