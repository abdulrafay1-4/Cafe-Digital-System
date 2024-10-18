#include"header.h"

#ifndef notification_H
#define notification_H

class notification  {
private:
    int notificationID;
    string message;
public:
    notification(int = 0, string = "");
    
    void addNotification(int, string);
    void removeNotification(int);
    
    ~notification();

    friend ostream& operator<<(ostream&, const notification&);
};

#endif