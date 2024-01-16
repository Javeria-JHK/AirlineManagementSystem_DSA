#include<iostream>
#include<list>
#include <limits.h>


using namespace std;
#define table_SIZE 10

void CustomerMenu();
void travelAgentMenu();
struct path
{
    int destinationCountryID;
    double distance;
    path* pathNext;
    path* pathPrev;


};

struct country{
    int countryCode;
    string CountryName;
    country *next;
    country* prev;
    path* firstPath = NULL;    //country contains the list of all connected paths
    path* lastPath = NULL;
    bool visited;
    int weight;


};


struct date{
    int day;
    int month;
    int year;

    date(){

    }

    date(int d, int m, int y){
        day = d;
        month = m;
        year = y;
    }

    void diplaydate(){
        cout<<day<<"/"<<month<<"/"<<year;
    }
};
struct route{
public:
    int fromID;
    int toID;




};

struct passenger{


    string firstName;
    string lastName;
    string Email;
    string ph_number;
    int age;
    int PNR;
    int seatNumber;





};


struct Bookings
{

public:
    int front;
    int rear;
    int size;
    passenger passengerList[100];


    Bookings()
    {
        front = -1;
        rear = -1;
        size = 100;
    }
    bool isFull()
    {
        if((front==0)&&(rear==size-1))
        {
            return true;
        }
        else
            return false;
    }
    bool isEmpty()
    {
        if((front==-1)&&(rear==-1))
        {
            return true;
        }else
            return false;
    }
    void Enqueue(passenger x)
    {
        if (isFull())
        {
            cout<<"No space"<<endl;
        }else
        if (isEmpty())
        {
            front = 0; rear = 0;
            passengerList[rear] = x;

        }else
        {
            rear++;
            passengerList[rear] = x;
        }
    }
    passenger Dequeue()
    {
        passenger x;
        if (isEmpty())
        {
            cout<<"No value"<<endl;

        }else
        {
            x = passengerList[front];
            front++;


        }
        return x;

    }

};

struct Flight{
public:
    string flightNumber;
    route flightRoute;
    string flightsStatus;
    date flightDate;
    Flight* next_f;
    Flight* prev_f;
    Bookings b;





    Flight(){

    }
    Flight(route r, date d,string name, string status){
        flightRoute =r;
        flightDate = d;
        flightNumber = name;
        flightsStatus = status;

    }

    void displayFlight(){
        cout<< flightNumber <<" from "<< flightRoute.fromID <<" to "+ flightRoute.toID<<"is "<<flightsStatus <<"at "; flightDate.diplaydate();
    }


};

struct map
{
    country* first = NULL ;
    country* last = NULL;
    Flight *h[table_SIZE];
    Flight* flightFirst;
    Flight* flightLast = NULL;
    int pnr = 4321;
    int seatNo = 1;


    void initBookings(){
        for (int i = 0; i < table_SIZE; i++) {
            if (h[i]!=NULL){
                Flight *temp = h[i];
                while (temp!=NULL){
                    temp->b.rear = -1;
                    temp->b.front = -1;
                    temp->b.size = 50;

                    temp= temp->next_f;

                }


            }

        }


    }

    //All graph operations will be coded here

    void addCountry(int id, string name)
    {

        bool check = checkIfcountryAlreadyRegistered(id);

        if (check)
        {
            cout<<"\n Country with the given ID is already Registered."<<endl;
        }else {
            country* newCountry = new country;
            newCountry->countryCode = id;
            newCountry->CountryName = name;
            newCountry->visited = false;
            newCountry->weight = INT_MAX;

            if (first==NULL){
                first = newCountry;
                last =newCountry;
                last->next = NULL;
            }else
            {
                newCountry->prev = last;
                last->next = newCountry;
                last=newCountry;
                last->next = NULL;

            }
            cout << "\n Country has been Registered." << endl;
        }

    }
    // This function will check if the given Country is already registered in Map or not.
    bool checkIfcountryAlreadyRegistered(int c_ID)
    {
        country* f = first;
        if (f==NULL)
        {
            return false;
        }else {
            while (f != NULL) {
                if (f->countryCode == c_ID) {
                    return true;
                }

                f=f->next;
            }
            return false;
        }

    }

    void addPath(int fromCountry, int toCountry, double distance)
    {
        bool check1 = checkIfcountryAlreadyRegistered(fromCountry);
        bool check2 = checkIfcountryAlreadyRegistered(toCountry);

        if (check1 && check2)
        {
            bool check3 = checkIfPathExist(fromCountry, toCountry);
            if (check3)
            {
                cout << "\nPath between " << getCountryByID(fromCountry)->CountryName << "(" << fromCountry
                     << ") and " << getCountryByID(toCountry)->CountryName << "(" << toCountry << ") Already Exists" << endl;
            }else
            {
                country* p = first;
                while (p!=NULL){

                    if (p->countryCode == fromCountry){

                        path* newPath = new path();
                        newPath->destinationCountryID = toCountry;
                        newPath->distance = distance;

                        // initialize firstPath and lastPath if they are null
                        if (p->firstPath==NULL)
                        {
                            p->firstPath = newPath;
                            p->lastPath = newPath;
                            newPath->pathPrev =NULL;
                            newPath->pathNext =NULL;
                        }
                        else
                        {
                            newPath->pathPrev = p->lastPath;
                            p->lastPath->pathNext = newPath;
                            p->lastPath = newPath;
                            newPath->pathNext =NULL;
                        }
                    }else  if (p->countryCode == toCountry){

                        path* newPath = new path();
                        newPath->destinationCountryID = fromCountry;
                        newPath->distance = distance;

                        // initialize firstPath and lastPath if they are null
                        if (p->firstPath==NULL)
                        {
                            p->firstPath = newPath;
                            p->lastPath = newPath;
                            newPath->pathPrev =NULL;
                            newPath->pathNext =NULL;
                        }
                        else
                        {
                            newPath->pathPrev = p->lastPath;
                            p->lastPath->pathNext = newPath;
                            p->lastPath = newPath;
                            newPath->pathNext =NULL;
                        }
                    }

                    p=p->next;

                }

                cout << "\nPath between " << getCountryByID(fromCountry)->CountryName << "(" << fromCountry
                     << ") and " << getCountryByID(toCountry)->CountryName << "(" << toCountry << ") has been added Successfully." << endl;

            }
        }else
            cout<<"\nEntered country ID does not Exist"<<endl;

    }

    bool checkIfPathExist(int Id1,int Id2)
    {
        country* temp = first;
        while (temp!=NULL){
            if (temp->countryCode==Id1){
                path* p = temp->firstPath;
                if (p==NULL){
                    return false;
                }else
                {
                    while(p!=NULL){
                        if (p->destinationCountryID == Id2){
                            return true;
                        }
                        p=p->pathNext;
                    }
                }
            }
            temp=temp->next;
        }
        return false;
    }

    country* getCountryByID(int Id){
        if (checkIfcountryAlreadyRegistered(Id)){
            country* temp = first;
            while (temp!=NULL)
            {
                if (temp->countryCode == Id)
                {
                    return temp;
                }
                temp=temp->next;

            }

        }
        return NULL;
    }


    // This function will delete the path between two Countries.

    void deletePath(int fromCountry, int toCountry)
    {
        bool check = checkIfPathExist(fromCountry, toCountry);
        if (check)
        {
            country* p = first;
            while (p!=NULL)
            {
                if (p->countryCode == fromCountry)
                {
                    path* myPath = p->firstPath;
                    while (myPath!=NULL)
                    {
                        if (myPath->destinationCountryID == toCountry)
                        {
                            path* prev = myPath->pathPrev;
                            path* next = myPath->pathNext;

                            // path* temp = prev;
                            prev->pathNext = next;
                            next->pathPrev = prev;
                            delete myPath;
                            break;
                        }
                        myPath= myPath->pathNext;
                    }
                }else if (p->countryCode == toCountry)
                {
                    path* myPath = p->firstPath;
                    while (myPath!=NULL)
                    {
                        if (myPath->destinationCountryID == fromCountry)
                        {
                            path* prev = myPath->pathPrev;
                            path* next = myPath->pathNext;

                            // path* temp = prev;
                            prev->pathNext = next;
                            next->pathPrev = prev;
                            delete myPath;
                            break;
                        }
                        myPath= myPath->pathNext;
                    }
                }
                p= p->next;
            }
            cout<<"\nThe path has been Deleted Successfully."<<endl;
        }else
            cout << "\nPath between " << getCountryByID(fromCountry)->CountryName << "(" << fromCountry
                 << ") and " << getCountryByID(toCountry)->CountryName << "(" << toCountry << ") Does not Exists" << endl;


    }

    // This function will update the distance of path between two Countries.

    void updatePathDistance(int fromCountry, int toCountry, double dist)
    {
        bool check = checkIfPathExist(fromCountry, toCountry);
        if (check)
        {
            country* p = first;
            while(p!=NULL)
            {
                if (p->countryCode == fromCountry)
                {
                    path* pth = p->firstPath;
                    while (pth!=NULL)
                    {
                        if (pth->destinationCountryID == toCountry)
                        {
                            pth->distance==dist;
                            break;
                        }
                    }
                }else if (p->countryCode == toCountry)
                {
                    path* pth = p->firstPath;
                    while (pth!=NULL)
                    {
                        if (pth->destinationCountryID == fromCountry)
                        {
                            pth->distance==dist;
                            break;
                        }
                    }
                }
                p=p->next;
            }
            cout<<"\nThe path has been Updated Successfully."<<endl;
        }else
            cout << "\nPath between " << getCountryByID(fromCountry)->CountryName << "(" << fromCountry
                 << ") and " << getCountryByID(toCountry)->CountryName << "(" << toCountry << ") Does not Exists" << endl;


    }

    //This function will delete country and its adjacent paths.
    void DeleteCountry(int c_Id)
    {
        country* tempCountry = first;
        while (tempCountry != NULL)
        {
            if (tempCountry->countryCode == c_Id)
            {
                country* previousCity = tempCountry->prev;
                country* nextCity = tempCountry->next;

                previousCity->next = nextCity;
                nextCity->prev = previousCity;
                break;

            }

            tempCountry=tempCountry->next;
        }

        cout<<"\nThe country has been deleted Successfully"<<endl;
    }

    //This Function will Update the Name of Country.
    void UpdateCountry(int c_id, string n){
        bool check = checkIfcountryAlreadyRegistered(c_id);
        if (check)
        {
            country* temp = first;
            while (temp!=NULL)
            {
                if (temp->countryCode == c_id)
                {
                    temp->CountryName= n;
                    break;
                }
                temp=temp->next;

            }
        }
        cout<<"\nCountry Name has been Updates Successfully."<<endl;

    }

    //This Function will display all Neighbours of the Country.
    void printNeighbours(int c_id)
    {
        cout << getCountryByID(c_id)->CountryName << " (" << c_id << ") --> ";
        country* temp = first;
        while(temp!=NULL)
        {
            if (temp->countryCode == c_id)
            {
                path* p = temp->firstPath;
                cout<<"[ ";
                while (p!=NULL){
                    cout << getCountryByID(p->destinationCountryID)->CountryName << "(" << p->destinationCountryID << ")" << "-->(" << p->distance << ")-- ";
                    p=p->pathNext;
                }
                cout<<" ]"<<endl;

                //temp->printPathList();
                break;
            }
            temp=temp->next;

        }
    }

    void printAllGraphData()   //This function will display all possible travels.
    {
        country* temp = first;
        while (temp!=NULL)
        {
            cout << temp->CountryName << " (" << temp->countryCode << ") --> ";
            path* p = temp->firstPath;
            cout<<"[";
            while(p!=NULL)
            {
                cout << getCountryByID(p->destinationCountryID)->CountryName << "(" << p->destinationCountryID << ")" << "-->(" << p->distance << ")-- ";

                p= p->pathNext;
            }
            cout<<"]"<<endl;

            temp = temp->next;
        }

    }
    //Using Hash Table for Storing Flight Details
    void init()
    {
        for (int i = 0; i < table_SIZE; i++)
        {
            h[i]=NULL;
        }

    }

    bool SearchForFlight(date d, int fromID, int toID){
        int key, h_key, i;
        key = d.day;

        //calculate hash key value
        h_key = key % table_SIZE;
        if (h[h_key]==NULL){
            return false;
        }
        Flight* temp = h[h_key];
        while (temp!=NULL){

            if ((temp->flightRoute.fromID == fromID) && (temp->flightRoute.toID == toID)){
                return true;

            }
            temp= temp->next_f;
        }
        return false;


    }

    void AddFlight(route* r,date d,string name , string status) {

        int key = d.day;
        int h_key = key % table_SIZE;

        Flight* newFlight = new Flight();
        newFlight->flightNumber = name;
        newFlight->flightRoute = *r;
        newFlight->flightDate = d;
        newFlight->flightsStatus = status;
        newFlight->next_f = NULL;

        if (h[h_key] == NULL) {
            h[h_key] = newFlight;
        } else {
            Flight* temp = h[h_key];
            while (temp->next_f != NULL) {
                temp = temp->next_f;
            }
            temp->next_f = newFlight;
        }

    }

    void UpdateFlight(route r,date d,string name , string status)
    {
        int key, index, h_key, i;
        key = d.day;

        //calculate hash key value
        h_key = key % table_SIZE;
        Flight* temp = h[h_key];

        while (temp!=NULL && temp->flightNumber!=name){
            temp= temp->next_f;
        }
        if (temp!=NULL) {
            temp->flightsStatus = status;
            temp->flightRoute = r;
        }

    }

    void CancelFlight(date d, string name){
        int key, index, h_key, i;
        key = d.day;

        //calculate hash key value
        h_key = key % table_SIZE;
        Flight* temp = h[h_key];

        while (temp!=NULL && temp->flightNumber==name){
            temp= temp->next_f;
        }
        if (temp!=NULL) {
            temp->prev_f->next_f=temp->next_f;
            temp->next_f->prev_f = temp->prev_f;
            delete temp;

        }
    }


    void BookFlight(string f_name,string l_name, string email,string ph, int a,date d,int id1,int id2,string fl){
        passenger p;
        p.firstName= f_name;
        p.lastName = l_name;
        p.Email = email;
        p.ph_number = ph;
        p.age = a;
        p.PNR = ++pnr;
        p.seatNumber = seatNo++;

            int key, index, h_key, i;
            key = d.day;

            //calculate hash key value
            h_key = key % table_SIZE;

                 Flight *temp = h[h_key];

                 while (temp != NULL ) {
                     if (temp->flightNumber == fl) {
                         temp->b.Enqueue(p);
                     }
                     temp = temp->next_f;
                 }

        cout << "======================================\n";
        cout << "|                                    |\n";
        cout << "|        Booking Successful          |\n";
        cout << "|                                    |\n";
        cout << "|        Your PNR is :"<<pnr<<"       |\n";
        cout << "|                                    |\n";
        cout << "======================================\n";






    }

    void CancelBooking(int pnr,date d,string flightName){

        int key, h_key, i;
        key = d.day;
        Bookings* tempBooking = new Bookings();


        //calculate hash key value
        h_key = key % table_SIZE;
        Flight* temp = h[h_key];

        while (temp!=NULL){
            if (temp->flightNumber==flightName){
                while (!temp->b.isEmpty()) {
                    passenger p = temp->b.Dequeue();
                    if (p.PNR != pnr) {
                        tempBooking->Enqueue(p);
                    }
                    temp->b = *tempBooking;
                }
                temp->b = *tempBooking;
                break;
            }
            temp= temp->next_f;
        }

    }

    void PrintTicket(int pnr, date d, string flightName) {
        int key, h_key;
        key = d.day;
        Bookings* tempBooking = new Bookings();

        //calculate hash key value
        h_key = key % table_SIZE;
        Flight *temp = h[h_key];

        while (temp != NULL) {
            if (temp->flightNumber == flightName) {
                while (!temp->b.isEmpty()) {
                    passenger p = temp->b.Dequeue();
                    if (p.PNR == pnr) {
                        cout << "\n===========================================================================\n";
                        cout << " *===========================     TICKET    ==============================*" << endl;
                        cout << "\n\n Flight Name : " << flightName;
                        cout << "\n Flight Date : ";
                        temp->flightDate.diplaydate();
                        cout << "\n Passenger Name : " << p.firstName << " " << p.lastName;
                        cout << "\n Age : " << p.age << "year(s)";
                        cout << "\n Email : " << p.Email;
                        cout << "\n Contact Number : " << p.ph_number;
                        cout << "\n PNR : " << p.PNR;
                        cout << "\n Seat Number : " << p.seatNumber;
                        cout << "\n\n";
                        cout << "============================================================================" << endl;
                        cout<<"\n\n\n";
                        break;
                    }
                        tempBooking->Enqueue(p);
                }
                temp->b = *tempBooking;
                break;
            }
            temp = temp->next_f;
        }


        delete tempBooking;
    }




    int findMinVertex()
    {
        country* temp = first;

        //initialize min value
        int min = INT_MAX;
        int min_ID;
        //finding minimum node from countries
        while (temp!=NULL){
            if ((temp->visited==false) && (temp->weight <= min)){
                min = temp->weight;
                min_ID = temp->countryCode;
            }
            temp= temp->next;
        }
        return min_ID;

    }
    int getDistance(int Id1, int Id2){
        country* c = first;
        while( c!=NULL){
            if (c->countryCode==Id1){
                path* p = c->firstPath;
                while(p!=NULL){
                    if (p->destinationCountryID == Id2){
                        return p->distance;
                    }
                    p=p->pathNext;
                }
            }
            c=c->next;
        }
        return INT_MAX;
    }

    void dijkstraAlgo(int departureID, int arrivalID)
    {
        // Initialize all nodes with a weight of infinity and unvisited
        country* temp = first;
        while (temp != NULL) {
            temp->weight = INT_MAX;
            temp->visited = false;
            temp = temp->next;
        }


        // Set the weight of the departure node to 0
        country* departure = getCountryByID(departureID);

        departure->weight = 0;


        country* t = first;
        // Repeat the algorithm until all nodes have been visited
        while (t!=NULL){ // update...
            int minID = findMinVertex();
            country* update = getCountryByID(minID);
            update->visited = true;

            // Relax all unvisited neighbors of the current node
            country* p = first;
            while (p!=NULL){
                if ((!p->visited)&&(update->weight!=INT_MAX)){
                    if (getDistance(update->countryCode,p->countryCode)!=INT_MAX){
                        int dist = update->weight + getDistance(update->countryCode, p->countryCode);
                        if (dist <= p->weight)
                        {
                            p->weight = dist;

                        }

                    }

                }
                p=p->next;
            }

            t = t->next;
        }

        cout << "Shortest path Distance from " << getCountryByID(departureID)->CountryName <<"("<<departureID<<")"
             << " to " << getCountryByID(arrivalID)->CountryName <<"("<<arrivalID<<")" << ": ";
        cout<<1*getCountryByID(arrivalID)->weight<<endl;

        cout << " Total Cost : PKR "<< 20 * (getCountryByID(arrivalID)->weight)<< endl;
    }



} g;


void travelAgentLogin()
{
    string username;
    string password;
    cout<<"\n *========================== Travel Agent Menu ==========================*"<<endl;
    cout<<"||                                                                        || "<<endl;
    cout<<"|                                                                          | "<<endl;
    cout<<"|                                                                          | "<<endl;
    cout<<"|                                                                          | "<<endl;
    cout<<"    Enter Username: ";
    cin>>username;
    cout<<"    Enter Password: ";
    cin>>password;
    cout<<"|                                                                          | "<<endl;
    cout<<"|                                                                          | "<<endl;
    cout<<"|                                                                          | "<<endl;
    cout<<"|                                                                          | "<<endl;
    cout<<"============================================================================"<<endl;

    if ((username=="Admin")&&(password=="Admin123")){
        cout<<"======================================\n";
        cout<<"|                                    |\n";
        cout<<"|        LOGIN SUCCESSFUL            |\n";
        cout<<"|                                    |\n";
        cout<<"======================================\n";

        cout<<"\n\n\n\n";

        travelAgentMenu();



    }else{
        cout<<"======================================\n";
        cout<<"|                                    |\n";
        cout<<"|  Invalid Username Or Password      |\n";
        cout<<"|          Try Again!                |\n";
        cout<<"======================================\n";
        travelAgentLogin();

    }



}

void HomeScreen(){


    while (true){
        cout<<" *================== WELCOME TO INTERNATIONAL AIRLINE  ===================*"<<endl;
        cout<<"||                                                                        || "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"|| Login As                                                                | "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"|  1- Travel Agent                                                         | "<<endl;
        cout<<"|  2- Customer                                                             | "<<endl;
        cout<<"|  0- Exit                                                                 | "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"============================================================================"<<endl;


        int opt;
        cout<<"\n your Option: ";cin>>opt;
        switch (opt) {
            case 1:
                travelAgentLogin();
                break;
            case 2:
                CustomerMenu();
                break;
            case 0:
                exit(0);
                break;
            default:
                cout<<" Choose correct Option"<<endl;
        }
    }

}
void RoutesManagementByTravelAgent(){



    string c_name;
    int id1, id2, dist;
    int option;
    bool check;

    do {

        cout<<" *========================= Travel Agent Menu  ==========================*"<<endl;
        cout<<"||                                                                        || "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"|  1- ADD Country                                                          | "<<endl;
        cout<<"|  2- Update Country                                                       | "<<endl;
        cout<<"|  3- Delete Country                                                       | "<<endl;
        cout<<"|  4- ADD Path                                                             | "<<endl;
        cout<<"|  5- Update Path                                                          | "<<endl;
        cout<<"|  6- Delete Path                                                          | "<<endl;
        cout<<"|  7- Check If Two Countries are connected                                 | "<<endl;
        cout<<"|  8- Display All Connected Countries                                      | "<<endl;
        cout<<"|  9- Display All Possible Travels                                         | "<<endl;
        cout<<"|  0- Back                                                                 | "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"============================================================================"<<endl;

        cout<<"\n\n Your Option: ";
        cin >> option;

        switch (option) {
            case 0:
                travelAgentMenu();
                break;

            case 1:
                cout << "\n\n Enter Country ID   :";
                cin >> id1;
                cout << "\n\n Enter Country Name :";
                cin >> c_name;

                g.addCountry(id1,c_name);
                break;

            case 2:
                cout << "\n\n Enter Country ID to Update   :";
                cin >> id1;
                cout << "\n\n Enter Country Name :";
                cin >> c_name;
                g.UpdateCountry(id1, c_name);

                break;

            case 3:
                cout << "\n\n Enter Country ID to Delete   :";
                cin >> id1;
                g.DeleteCountry(id1);

                break;

            case 4:
                cout << "\n\n Enter ID of Source Country : ";
                cin >> id1;
                cout << "\n\n Enter ID of Destination Country: ";
                cin >> id2;
                cout << "\n\n Enter Distance of Path: ";
                cin >> dist;
                g.addPath(id1, id2, dist);

                break;

            case 5:
                cout << "\n\n Enter ID of Source Country: ";
                cin >> id1;
                cout << "\n\n Enter ID of Destination Country: ";
                cin >> id2;
                cout << "\n\n Enter UPDATED distance of Path: ";
                cin >> dist;
                g.updatePathDistance(id1, id2, dist);

                break;

            case 6:
                cout << "\n\n Enter ID of Source Country: ";
                cin >> id1;
                cout << "\n\n Enter ID of Destination Country: ";
                cin >> id2;
                g.deletePath(id1, id2);

                break;

            case 7:
                cout << "\n\n Enter ID of Source Country: ";
                cin >> id1;
                cout << "\n\n Enter ID of Destination Country: ";
                cin >> id2;
                check = g.checkIfPathExist(id1, id2);
                if (check) {
                    cout << "countries are Connected (Path exist)";
                } else {
                    cout << "Countries are NOT Connected (Path does NOT exist)";
                }

                break;

            case 8:
                cout << "\n\n Enter ID of Country to fetch all Neighbours : ";
                cin >> id1;
                g.printNeighbours(id1);

                break;

            case 9:
                cout << "\n\n Printing all Possible Travel Data Operation -\n\n" << endl;
                g.printAllGraphData();

                break;
            default:
                cout << "\n\n Enter Proper Option number " << endl;
        }
        cout << endl;

    } while (option != 0);



}
void FlightsManagementByTravelAgent(){
    int id1,id2,d,m,y;
    date FlightDate;
    route* flightRoute = new route();
    string n,s;


    int option;
    do {

        cout<<" *========================= Travel Agent Menu  ==========================*"<<endl;
        cout<<"||                                                                        || "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"|  1- Add Flight                                                           | "<<endl;
        cout<<"|  2- Update Flight                                                        | "<<endl;
        cout<<"|  3- Cancel Flight                                                        | "<<endl;
        cout<<"|  0- Back                                                                 | "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"============================================================================"<<endl;

        cout<<"\n\n Your Option: ";
        cin >> option;

        switch (option) {
            case 0:
                travelAgentMenu();
                break;

            case 1: {

                cout << "\n\n Enter Date to Schedule Flight:  ";
                cout << "\n Day:  ";
                cin >> FlightDate.day;
                cout << " Month:  ";
                cin >> FlightDate.month;
                cout << " Year:  ";
                cin >> FlightDate.year;

                cout << "\n\n Enter Route:  ";
                cout << "\n Enter Departure Country Code:  ";
                cin >> id1;
                cout << "\n Enter Arrival Country Code:  ";
                cin >> id2;

                flightRoute->toID = id2;
                flightRoute->fromID = id1;

                cout << "\n Enter Flight name :  ";
                cin >> n;
                cout << "\n Enter Flight Status :  ";
                cin >> s;


                g.AddFlight(flightRoute, FlightDate, n, s);
                cout << "======================================\n";
                cout << "|                                    |\n";
                cout << "|        Flight Scheduled            |\n";
                cout << "|                                    |\n";
                cout << "======================================\n";
            }
                break;

            case 2:
            {

                cout << "\n\n Enter Date of Flight:  ";
                cout << "\n Day:  ";
                cin >> d;
                cout << "\n Month:  ";
                cin >> m;
                cout << "\n Year:  ";
                cin >> y;
                FlightDate = *new date(d, m, y);

                cout << "\n Enter Flight name to Update:  ";
                cin >> n;
                cout << "\n\n Enter Route Update Details :  ";
                cout << "\n Enter Departure Country Code:  ";
                cin >> id1;
                cout << "\n Enter Arrival Country Code:  ";
                cin >> id2;

                flightRoute->toID = id1;
                flightRoute->fromID = id2;

                cout << "\n Enter updated Flight Status :  ";
                cin >> s;


                g.UpdateFlight(*flightRoute, FlightDate, n, s);
                cout << "======================================\n";
                cout << "|                                    |\n";
                cout << "|        Flight Updated              |\n";
                cout << "|                                    |\n";
                cout << "======================================\n";
            }
                break;

            case 3:
                cout << "\n\n Enter Date of Flight to Cancel:  ";
                cout << "\n Day:  ";
                cin >> d;
                cout << "\n Month:  ";
                cin >> m;
                cout << "\n Year:  ";
                cin >> y;
                FlightDate = *new date(d, m, y);

                cout << "\n Enter Flight name to Cancel Flight:  ";
                cin >> n;

                g.CancelFlight(FlightDate,n);
                cout << "======================================\n";
                cout << "|                                    |\n";
                cout << "|        Flight Cancelled            |\n";
                cout << "|                                    |\n";
                cout << "======================================\n";

                break;
            default:
                cout << "\n\n Enter Proper Option number " << endl;
        }
        cout << endl;

    } while (option != 0);


}

void travelAgentMenu(){

    while (true){
        cout<<" *========================= Travel Agent Menu ===========================*"<<endl;
        cout<<"||                                                                        || "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"|  1- Manage Routes and Travels                                            | "<<endl;
        cout<<"|  2- Manage Flights                                                       | "<<endl;
        cout<<"|  0- Back                                                                 | "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"|                                                                          | "<<endl;
        cout<<"============================================================================"<<endl;


        int opt;
        cout<<"\n\nyour Option: ";cin>>opt;
        switch (opt) {
            case 1:
                RoutesManagementByTravelAgent();
                break;
            case 2:
                FlightsManagementByTravelAgent();
                break;
            case 0:
                HomeScreen();
                break;
            default:
                cout<<" Choose correct Option"<<endl;
        }
    }

}

void CustomerMenu(){
    int d,m,y;
    int id1,id2;
    date FlightDate;
    string f,l,e,fl_name;
    int a,pnr;
    string ph;

        while (true){
            cout<<" *============================== Customer Menu ===============================*"<<endl;
            cout<<" |                                                                            |"<<endl;
            cout<<" |  1- Search for a Flight                                                    |"<<endl;
            cout<<" |  2- Book a Flight                                                          |"<<endl;
            cout<<" |  3- Print Ticket                                                           |"<<endl;
            cout<<" |  4- Cancel Booking                                                         |"<<endl;
            cout<<" |  5- Check Travel cost                                                      |"<<endl;
            cout<<" |  0- Back                                                                   |"<<endl;
            cout<<" |                                                                            |"<<endl;
            cout<<" |                                                                            |"<<endl;
            cout<<" |                                                                            |"<<endl;
            cout<<" =============================================================================="<<endl;


            int opt;
            cout<<"\n\nyour Option: ";cin>>opt;
            switch (opt) {
                case 1:{

                    cout << "\n\n Enter Date to Search Flight:  ";
                    cout << "\n Day:  ";
                    cin >> FlightDate.day;
                    cout << " Month:  ";
                    cin >> FlightDate.month;
                    cout << " Year:  ";
                    cin >> FlightDate.year;

                    cout << "\n\n Enter Route:  ";
                    cout << "\n Enter Departure Country Code:  ";
                    cin >> id1;
                    cout << "\n Enter Destination Country Code:  ";
                    cin >> id2;

                    bool check = g.SearchForFlight(FlightDate, id1, id2);
                    if (check) {
                        cout << "======================================\n";
                        cout << "|                                    |\n";
                        cout << "|        Flight Available             |\n";
                        cout << "|                                    |\n";
                        cout << "======================================\n";

                    } else if(!check) {
                        cout << "======================================\n";
                        cout << "|                                    |\n";
                        cout << "|        Flight Not Available        |\n";
                        cout << "|                                    |\n";
                        cout << "======================================\n";
                    }
                 }
                    break;
                case 2: {

                    cout << "\n\n Enter Date to Book Flight:  ";
                    cout << "\n Day:  ";
                    cin >> FlightDate.day;
                    cout << " Month:  ";
                    cin >> FlightDate.month;
                    cout << " Year:  ";
                    cin >> FlightDate.year;

                    cout << "\n\n Enter Route:  ";
                    cout << "\n Enter Departure Country Code:  ";
                    cin >> id1;
                    cout << "\n Enter Destination Country Code:  ";
                    cin >> id2;
                    bool check = g.SearchForFlight(FlightDate, id1, id2);
                    if (check) {
                        cout << "\n=============== Personal Details =================  ";
                        cout << "\n First Name:  ";
                         cin>> f;
                        cout << "\n Last Name:  ";
                        cin>> l;
                        cout << "\n Your Age:  ";
                        cin>> a;
                        cout << "\n Email:  ";
                        cin>> e;
                        cout << "\n Phone Number:  ";
                        cin>> ph;
                        cout << "\n Enter Flight Name:  ";
                        cin>> fl_name;

                        g.BookFlight(f,l,e,ph,a,FlightDate,id1,id2,fl_name);

                    } else {
                        cout << "======================================\n";
                        cout << "|                                    |\n";
                        cout << "|        Flight Not Available        |\n";
                        cout << "|                                    |\n";
                        cout << "======================================\n";
                    }


                }
                    break;
                case 3:

                    cout << "\n\n Enter Date of Flight:  ";
                    cout << "\n Day:  ";
                    cin >> FlightDate.day;
                    cout << " Month:  ";
                    cin >> FlightDate.month;
                    cout << " Year:  ";
                    cin >> FlightDate.year;

                    cout << "\n Enter Flight Name:  ";
                    cin>> fl_name;
                    cout<<"\nEnter you PNR : ";
                    cin>>pnr;

                    g.PrintTicket(pnr,FlightDate,fl_name);

                    break;
                case 4:

                    cout << "\n\n Enter Date to Schedule Flight:  ";
                    cout << "\n Day:  ";
                    cin >> FlightDate.day;
                    cout << " Month:  ";
                    cin >> FlightDate.month;
                    cout << " Year:  ";
                    cin >> FlightDate.year;


                    cout<<"\nEnter Flight Name: ";
                    cin>>fl_name;
                    cout<<"\nEnter you PNR for cancellation: ";
                    cin>>pnr;

                    g.CancelBooking(pnr,FlightDate,fl_name);
                    cout<<"\n\n";

                    cout << "======================================\n";
                    cout << "|                                    |\n";
                    cout << "|        Booking Cancelled           |\n";
                    cout << "|                                    |\n";
                    cout << "======================================\n";


                    break;
                case 5:
                    cout << "\n\n Enter Route:  ";
                    cout << "\n Enter Departure Country Code:  ";
                    cin >> id1;
                    cout << "\n Enter Destination Country Code:  ";
                    cin >> id2;
                    g.dijkstraAlgo(id1,id2);

                    break;
                case 0:
                    HomeScreen();
                    break;
                default:
                    cout<<" Choose correct Option"<<endl;
            }
        }


}


int main(){
    g.init();
    g.addCountry(92,"Pakistan");
    g.addCountry(97,"Dubai");
    g.addCountry(90,"Turkey"); g.addCountry(49,"Frankfurt"); g.addCountry(44,"England");
    g.addCountry(94,"Qatar"); g.addCountry(71,"Manchester"); g.addCountry(41,"Switzerland");
    g.addCountry(27,"Africa"); g.addCountry(55,"Brazil");
    g.addCountry(1,"Canada"); g.addCountry(86,"China"); g.addCountry(82,"South Korea");
    g.addCountry(66, "Thailand"); g.addCountry(81,"Japan"); g.addCountry(61,"Austrailia");
    g.addCountry(64,"Newzealand");

    g.addPath(92,97,1490);
    g.addPath(49,1,4195);
    g.addPath(94,61,5405);
    g.addPath(90,44,2555);
    g.addPath(27,41,6532);
    g.addPath(61,41,2312);
    g.addPath(97,90,2998);
    g.addPath(66,81,4320);
    g.addPath(81,61,8764);


    g.addPath(92,86,3312);

    g.addPath(49,44,637);
    g.addPath(49,71,1560);
    g.addPath(92,66,3600);
    g.addPath(92,94,1163);
    g.addPath(92,90,3336);

    g.addPath(81,94,4567);
    g.addPath(61,64,1356);
    g.addPath(64,82,9778);
    g.addPath(82,86,1143);
    g.addPath(94,27,4276);
    g.addPath(94,61,5405);
    g.addPath(27,55,7000);

    cout<<"\n\n\n\n\n\n\n\n\n\n\n\n";
    HomeScreen();
    return 0;
}



