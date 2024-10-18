#include "complaints.h"
#include "header.h"

complaints::complaints(int cID, string comp, string compStat, string resp)
{
    complaintID = cID;
    complaint = comp;
    complaintStatus = compStat;
    response = resp;
}

void complaints::addComplaint(int cID, string comp)
{
    complaints c(cID, comp, "Pending", "");

    ofstream wF("complaints.dat", ios::binary | ios::app);
    if(!wF)
    {
        cout<<"File not found"<<endl;
        return;
    }
    else
    {
        wF.write(reinterpret_cast<char*>(&c), sizeof(c));
        wF.close();
    }
}

void complaints::removeComplaint(int compID)
{
    complaints c;
    int objs = 0;
    ifstream rF("complaints.dat", ios::binary);
    if(!rF)
    {
        cout<<"File not found"<<endl;
        return;
    }
    else
    {
        while(rF.read(reinterpret_cast<char*>(&c), sizeof(c)))
        {
            objs++;
        }
        rF.close();
    }
    rF.close();    
    int j = findComplaint(compID);

    complaints *cArr = new complaints[objs];

    if(j != -1)
    {
        ofstream oF("complaints.dat", ios::binary);
        for(int i = 0; i < objs; i++)
        {
            if(i != j)
            {
                oF.write(reinterpret_cast<char*>(&cArr[i]), sizeof(cArr[i]));
            }
        }
        oF.close();
    }
    else
    {
        cout<<"Complaint not found"<<endl;
    }
    delete[] cArr;
}

int complaints::displayComplaints() const
{
    complaints c;
    int rows = 0;
    ifstream iF("complaints.dat", ios::binary);
    if(!iF)
    {
        cout<<"File not found"<<endl;
        return 0;
    }
    else
    {
        while(iF.read(reinterpret_cast<char*>(&c), sizeof(c)))
        {
            cout<<"\nComplaint ID: "<<c.complaintID<<endl;
            cout<<"Complaint: "<<c.complaint<<endl;
            cout<<"Complaint Status: "<<c.complaintStatus<<endl;
            cout<<"Response: "<<c.response<<endl;
            cout<<endl;
            rows++;
        }
        iF.close();
    }
    return rows;
}

void complaints::updateComplaintStatus(int cID, string status)
{
    complaints c;
    int objs = 0;
    ifstream rF("complaints.dat", ios::binary);
    if(!rF)
    {
        cout<<"File not found"<<endl;
        return;
    }
    else
    {
        while(rF.read(reinterpret_cast<char*>(&c), sizeof(c)))
        {
            objs++;
        }
        rF.close();
    }
    rF.close();    
    int j = findComplaint(cID);

    complaints *cArr = new complaints[objs];

    ifstream iF("complaints.dat", ios::binary);
    if(!iF)
    {
        cout<<"File not found"<<endl;
        return;
    }
    else
    {
        for(int i = 0; i < objs; i++)
        {
            iF.read(reinterpret_cast<char*>(&cArr[i]), sizeof(cArr[i]));
        }
        iF.close();
    }

    if(j != -1)
    {
        cArr[j].complaintStatus = status;

        ofstream wF("complaints.dat", ios::binary);
        for(int i = 0; i < objs; i++)
        {
            wF.write(reinterpret_cast<char*>(&cArr[i]), sizeof(cArr[i]));
        }
        delete[] cArr;
    }   
    else
    {
        cout<<"Complaint not found"<<endl;
        delete[] cArr;
        return;
    } 
}

int complaints::findComplaint(int compID)
{
    complaints c;
    int objs = 0;
    ifstream rF("complaints.dat", ios::binary);
    if(!rF)
    {
        cout<<"File not found"<<endl;
        return -1;
    }
    else
    {
        while(rF.read(reinterpret_cast<char*>(&c), sizeof(c)))
        {
            objs++;
        }
        rF.close();
    }
    rF.close();

    complaints *cArr = new complaints[objs];
    ifstream iF("complaints.dat", ios::binary);
    if(!iF)
    {
        cout<<"File not found"<<endl;

        return 0;
    }
    else
    {
        for(int i = 0; i < objs; i++)
        {
            iF.read(reinterpret_cast<char*>(&cArr[i]), sizeof(cArr[i]));
        }
        iF.close();
    }

    int j = 0;
    bool found = false;
    while(!found && j < objs)
    {
        if(cArr[j].complaintID == compID)
        {
            found = true;
        }
        else
        {
            j++;
        }
    }

    if(found)
    {
        delete[] cArr;
        return j;
    }
    else
    {
        delete[] cArr;
        return -1;
    }    

    return -1;

    delete[] cArr;
}


void complaints::addResponse(int cID, string resp)
{
    complaints c;
    int objs = 0;
    ifstream rF("complaints.dat", ios::binary);
    if(!rF)
    {
        cout<<"File not found"<<endl;
        return;
    }
    else
    {
        while(rF.read(reinterpret_cast<char*>(&c), sizeof(c)))
        {
            objs++;
        }
        rF.close();
    }
    rF.close();    
    int j = findComplaint(cID);

    complaints *cArr = new complaints[objs];

    ifstream iF("complaints.dat", ios::binary);
    if(!iF)
    {
        cout<<"File not found"<<endl;
        return;
    }
    else
    {
        for(int i = 0; i < objs; i++)
        {
            iF.read(reinterpret_cast<char*>(&cArr[i]), sizeof(cArr[i]));
        }
        iF.close();
    }

    if(j != -1)
    {
        cArr[j].response = resp;
        
        ofstream wF("complaints.dat", ios::binary);
        for(int i = 0; i < objs; i++)
        {
            wF.write(reinterpret_cast<char*>(&cArr[i]), sizeof(cArr[i]));
        }
        delete[] cArr;
    }   
    else
    {
        cout<<"Complaint not found"<<endl;
        delete[] cArr;
        return;
    } 
}

int complaints::getComplaintID() const
{
    return complaintID;
}

string complaints::getComplaint() const
{
    return complaint;
}

complaints::~complaints()
{
}

int operator<<(ostream &out, complaints &)
{
    complaints c;
    int rows = 0;
    ifstream iF("complaints.dat", ios::binary);
    if(!iF)
    {
        out<<"File not found"<<endl;
        return 0;
    }
    else
    {
        while(iF.read(reinterpret_cast<char*>(&c), sizeof(c)))
        {
            rows++;
            out<<"\nComplaint ID: "<<c.complaintID<<endl;
            out<<"Complaint: "<<c.complaint<<endl;
            out<<"Complaint Status: "<<c.complaintStatus<<endl;
            out<<"Response: "<<c.response<<endl;
            out<<endl;
        }
        iF.close();
    }
    return rows;
}
