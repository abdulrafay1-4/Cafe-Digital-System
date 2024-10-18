#include "notifcation.h"
#include"header.h"

notification::notification(int nID, string mes)
{
    notificationID = nID;
    message = mes;
}

void notification::addNotification(int nID, string mes)
{
    
    notification n(nID, mes);

    ofstream oF("notification.dat", ios::binary | ios::app);
    oF.write(reinterpret_cast<char*>(&n), sizeof(notification));
    oF.close();

}

void notification::removeNotification(int nID)
{
    int objs = 0;
    notification n;
    ifstream iF("notification.dat", ios::binary);

    while(iF.read(reinterpret_cast<char*>(&n), sizeof(notification)))
    {
        objs++;
    }

    notification* nArray = new notification[objs];
    iF.seekg(0, ios::beg);
    iF.read(reinterpret_cast<char*>(nArray), sizeof(notification));

    ofstream oF("notification.dat", ios::binary);
    for(int i = 0; i < objs; i++)
    {
        if(nArray[i].notificationID != nID)
        {
            oF.write(reinterpret_cast<char*>(&nArray[i]), sizeof(notification));
        }
    }

    iF.close();
}

notification::~notification()
{
}

ostream &operator<<(ostream &out, const notification &N)
{
    notification n;
    ifstream iF("notification.dat", ios::binary);

    while(iF.read(reinterpret_cast<char*>(&n), sizeof(notification)))
    {
        out << "Notification ID: " << n.notificationID << endl;
        out << "Message: " << n.message << endl;
    }

    iF.close();
    return out;
}