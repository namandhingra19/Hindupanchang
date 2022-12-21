#include<bits/stdc++.h>
using namespace std;
const double pi=3.14159265358979;
const double tpi=6.28318530717958;
const double degs=57.2957795130823;
const double rads=1.74532925199433E-02;

double Degsin(double x) {return sin(rads*x);}
double Degcos(double x) {return cos(rads*x);}
double DegTan(double x) {return tan(rads*x);}
double DegArcsin(double x) {return degs*asin(x);}
double DegArccos(double x) {return degs*acos(x);}
double DegAcrtan(double x) {return degs*atan(x);}
string arr_of_tithis[16]={"Pratham","Dwitiya","Tritiya","Chaturthi","Panchami","Shashthi","Saptami","Ashtami","Navami","Dashami","Ekadashi","Dwadashi","Trayodashi","Chaturdashi","Amavasya","Purnima"};
string arr_of_nakshtr[27]={"Ashvini","Bharani","Krittika","Rohini","Mrigashirsha","Ardra","Punarvasu","Pushya","Āshleshā","Maghā","Pūrva Phalgunī","Uttara Phalgunī","Hasta","Chitra","Svati","Vishakha","Anuradha","Jyeshtha","Mula","Purva Ashadha","Uttara Ashadha","Sravana","Dhanishta","Shatabhisha","Purva Bhadrapada","Uttara Bhadrapada","Revati"};
string arr_of_rashi[12]={"Mesha (Aries)","Vrishabha (Taurus)","Mithun (Gemini)","Karka (Cancer)","Simha / Sinh (Leo)","Kanya (Vigro)","Tula (Libra)","Vruschika (Scorpius)","Dhanu (Sagittarius)","Makar (Capricorn)","Kumbha (Aquarius)","Meena (Pisces)"};
double DegArctan2(double y,double x){
    double t=degs*atan2(x,y);
    if(t<0) t=t+360;
    return t;
}

double range2pi(double x)
{
    return x-(tpi*int(x/tpi));
}

double range360(double x)
{
    return x-360*floor(x/360);
}

double range21600(double x)
{
    return x-21600*floor(x/21600);
}

double day2000(int year,int month,int day,double hour=-5,double min=-30,double sec=0,int greg=1)
{
    double a;
    int b;
    a=(10000*year)+(100*month)+day;
    if(month<=2){
        month+=12;
        year+=-1;
    }
    if(greg==0){
        b=-2+floor((year+4716)/4)-1179;
    }
    else b=floor(year/400)-floor(year/100)+floor(year/4);
    a=(365*year)-730548.5;
    return a+b+floor(30.6001*(month+1))+day+(hour+(min/60)+(sec/3600))/24;
}

double ssun(double d,int index)
{
    double g;
    double l;
    g = range360(357.528 + 0.9856003 * d);
    l = range360(280.461 + 0.9856474 * d);
    switch (index)
    {
        case 1:
            return 1.00014 - 0.01671 * Degcos(g) - 0.00014 * Degcos(2 * g);
            break;
        case 2:
            return 0;
            break;
        case 3:
            return range360(l + 1.915 * Degsin(g) + 0.02 * Degsin(2 * g));
            break;
        default:
            break;
    }
    return 0;
}

double smoon(double d,int index)
{
    double Nm,im,wm,am,ecm,Mm,em,Ms,ws,xv,yv,vm,rm,x,y,z,lon,lat,ls,lm,dm,F,dlon,dlat;
    d = d + 1.5;

    //moon elements
    Nm = range360(125.1228 - 0.0529538083 * d) * rads;
    im = 5.1454 * rads;
    wm = range360(318.0634 + 0.1643573223 * d) * rads;
    am = 60.2666;
    ecm = 0.0549;
    Mm = range360(115.3654 + 13.0649929509 * d) * rads;

    //position of elements
    em = Mm + ecm * sin(Mm) * (1 + ecm * cos(Mm));
    xv = am * (cos(em) - ecm);
    yv = am * (sqrt(1 - ecm * ecm) * sin(em));
    vm = atan2(yv,xv);
    rm = sqrt(xv * xv + yv * yv);

    x = rm * ((cos(Nm) * cos(vm + wm)) - (sin(Nm) * sin(vm + wm) * cos(im)));
    y = rm * ((sin(Nm) * cos(vm + wm)) + (cos(Nm) * sin(vm + wm) * cos(im)));
    z = rm * (sin(vm + wm) * sin(im));

    lon = atan2(y, x);
    if(lon < 0) lon = tpi + lon;
    lat = atan(z / sqrt(x * x + y * y));
  
    ws = range360(282.9404 + 0.0000470935 * d) * rads;
    Ms = range360(356.047 + 0.9856002585 * d) * rads;

    ls = Ms + ws;       
    lm = Mm + wm + Nm;  
    dm = lm - ls;        
    F = lm - Nm;        

    switch(index)
    {
        case 1:
            rm = rm - 0.58 * cos(Mm - 2 * dm);
            rm = rm - 0.46 * cos(2 * dm);
            return rm;
        case 2:
            dlat = -0.173 * sin(F - 2 * dm);
            dlat = dlat - 0.055 * sin(Mm - F - 2 * dm);
            dlat = dlat - 0.046 * sin(Mm + F - 2 * dm);
            dlat = dlat + 0.033 * sin(F + 2 * dm);
            dlat = dlat + 0.017 * sin(2 * Mm + F);
            return dlat;
        case 3:
            dlon = -1.274 * sin(Mm - 2 * dm);      
            dlon = dlon + 0.658 * sin(2 * dm);      
            dlon = dlon - 0.186 * sin(Ms);          
            dlon = dlon - 0.059 * sin(2 * Mm - 2 * dm);
            dlon = dlon - 0.057 * sin(Mm - 2 * dm + Ms);
            dlon = dlon + 0.053 * sin(Mm + 2 * dm);
            dlon = dlon + 0.046 * sin(2 * dm - Ms);
            dlon = dlon + 0.041 * sin(Mm - Ms);
            dlon = dlon - 0.035 * sin(dm);
            dlon = dlon - 0.031 * sin(Mm + Ms);
            dlon = dlon - 0.015 * sin(2 * F - 2 * dm);
            dlon = dlon + 0.011 * sin(Mm - 4 * dm);
            return lon * degs + dlon;
    }
    return 0;
}

string today(int x){
    int y=x%7;
    switch (y)
    {
    case 0:                                                                                                                      
        return "Sunday";
        break;
    case 1:
        return "Monday";
        break;
    case 2:
        return "Tuesday";
        break;
    case 3:
        return "Wednesday";
        break;
    case 4:
        return "Thursday";
        break;
    case 5:
        return "Friday";
        break;
    case 6:
        return "Saturday";
        break;
    
    default:
        break;
    }
    return 0;

}

string tithi(int year,int month,int day,int hour,int min){

    double input=day2000(year,month,day,hour,min);
    double x=range360(smoon(input,3)-ssun(input,3))/12;
    double temp;
    temp=x;
    if (temp>15) temp=temp-15;
    int y=floor(temp);

    switch(y)
    {
        case 14:
        if(x>15) return arr_of_tithis[y];
        return arr_of_tithis[y+1];
        break;

        default:
        return arr_of_tithis[y];
        break;
    }
    return 0;
}

int range_month(double input1,double input2)
{
    int lastchange=floor(input2);
    if(input1>input2) lastchange+=(floor(input1)+1);
    return lastchange;
}

string paksh(double x){
    if(x>15) return "Krishna Paksh";
    else return "Shukl Paksh";
}

int tithi_hours(int beg,int end,int year,int month,int day,int hours=-5,int minutes=-30)
{
    double day1=day2000(year,month,day,beg-5,-30);
    double input1=range360(smoon(day1,3)-ssun(day1,3))/12;
    int firstchange=floor(input1);
    // cout<<"\n"<<firstchange;
    int mid=beg+(end-beg)/2;
    int lastchange,ans;
    while(beg<=end)
    {
        double day2=day2000(year,month,day,mid-5);
        double input2=range360(smoon(day2,3)-ssun(day2,3))/12;
        lastchange=range_month(input1,input2);
        // cout<<"las"<<lastchange<<" "<<"mid"<<mid;
        if(lastchange>firstchange) end=mid-1;

        else beg=mid+1;
        mid=beg+(end-beg)/2;
        ans=mid;
    }
    return ans-1;
}

int tithi_minutes(int beg,int end,int year,int month,int day,int hours=-5,int minutes=-30)
{
    double day1=day2000(year,month,day,hours,minutes);
    double input1=range360(smoon(day1,3)-ssun(day1,3))/12;
    int firstchange=floor(input1);
    int mid=beg+(end-beg)/2;
    int lastchange,ans;

    while(beg<=end)
    {
        double day2=day2000(year,month,day,hours,mid-30);
        double input2=range360(smoon(day2,3)-ssun(day2,3))/12;

        lastchange=range_month(input1,input2);

        if(lastchange>firstchange) end=mid-1;

        else beg=mid+1;        
        mid=beg+(end-beg)/2;
        ans=mid;
    }
    return ans-1;
}

string print_time(int begh,int endh,int begm,int endm,int year,int month,int day,int temp=7)
{
    string s;
    int ans=tithi_hours(begh,endh,year,month,day);
    int ans2=tithi_minutes(begm,endm,year,month,day,ans-5);
    s+="-(";
    s+=to_string(ans);
    s+=":";
    s+=to_string(ans2);
    s+=")---";
    s+=tithi(year,month,day,ans,ans2+1);
    return s;
}

string tithi_timeline(int year,int month,int day,int hour ,int minutes)
{
    double day1=day2000(year,month,day,hour-5,minutes-30);
    double input1=range360(smoon(day1,3)-ssun(day1,3))/12;

    double day3=day2000(year,month,day,24-5,-30);
    double input3=range360(smoon(day3,3)-ssun(day3,3))/12;

    int lastchange=range_month(input1,input3);
    int firstchange=floor(input1);
    string s;
    //cout<<lastchange<<" "<<firstchange;
    switch(lastchange-firstchange)
    {
        case 0:
            s+=tithi(year,month,day,hour-5,minutes-30);
            s+="---";
            break;

        case 1:
            s+=tithi(year,month,day,hour-5,minutes-30);
            s+=print_time(hour,24,minutes,60,year,month,day);
            s+="---";
            break;
        case 2:
            int ans=tithi_hours(0,24,year,month,day,0);
            s+=tithi(year,month,day,-5,-30);
            s+=print_time(0,24,0,60,year,month,day,0);
            s+=print_time(ans+1,24,0,60,year,month,day);
            s+="---";
            break;
    }
    return s;
}

string nakshatra(double moonangle)
{
    double x=range21600((moonangle*60)-1450)/800;
    int h=floor(x);
    return arr_of_nakshtr[h];
}

string rashi_moon(double moonangle)
{
    double x=range21600((moonangle*60)-1450)/1800;
    int h=floor(x);
    return arr_of_rashi[h];
}

string rashi_sun(double sunangle)
{
    double x=range21600((sunangle*60)-1450)/1800;
    int h=floor(x);
    return arr_of_rashi[h];
}

int main()
{   
    int year,month,day;
    double hour,min;
    
    cout<<"Date:";
    cin>>day;
    cout<<"Month:";
    cin>>month;
    cout<<"Year:";
    cin>>year;
    cout<<"Hour:";
    cin>>hour;
    cout<<"Minutes:";
    cin>>min;

    double input=day2000(year,month,day,hour-5,min-30);
    double input2=day2000(year,month,day);
    double input3=range360(smoon(input,3)-ssun(input,3))/12;
    printf("\nTotal Days:%f\n",input);
    printf("\nTotal Days:%f\n",input2);
    printf("\nTotal Days:%f\n",input3);
    printf("Sun:%f\n",ssun(input,3));
    printf("Moon:%f\n\n",smoon(input,3));

    // cout<<endl<<input<<endl<<input2<<endl<<input3;
    cout<<"TIthi:           "<<tithi_timeline(year,month,day,hour,min)<<"\n";
    cout<<"Paksh:           "<<paksh(input3)<<"\n";
    cout<<"Nakshatra:       "<<nakshatra(smoon(input,3))<<"\n";
    cout<<"Vaar:            "<<today(floor(input2))<<"\n";
    cout<<"Chandra Rashi:   "<<rashi_moon(smoon(input,3))<<"\n";
    cout<<"Surya Rashi:     "<<rashi_sun(ssun(input,3))<<"\n"; 
}