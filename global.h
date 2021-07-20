#ifndef GLOBAL_H
#define GLOBAL_H

#define CHECK_OK (1)
#define CHECK_FAILED (0)

typedef enum{
    LEVEL_NORMAL=1,
    LEVEL_OK,
    LEVEL_WARNING,
    LEVEL_ERROR,
}DEBUG_LEVEL;

typedef struct{
    QString host;
    QString username;
    QString password;
    QString port;

    bool remerber_me;
}User, *pUser;

#endif // GLOBAL_H
