#include"header.h"

#ifndef complaints_H
#define complaints_H

//link with admin and customer
class complaints
{

private:
    int complaintID;
    string complaint;
    string complaintStatus;
    string response;
public:
    complaints(int = 0, string = "", string = "", string = "");

    void addComplaint(int, string);
    void removeComplaint(int);
    int displayComplaints() const;
    void updateComplaintStatus(int, string);
    int findComplaint(int);
    void addResponse(int, string);

    int getComplaintID() const;
    string getComplaint() const;

    ~complaints();

    friend int operator<<(ostream&, complaints&);
};

#endif